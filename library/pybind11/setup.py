from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import fnmatch
import os
import re

"""The idea here is to compile C++ source into static library first.
Then, link the library to this Python wrapper, i.e.
CPP_SRC = None
LIB_LIST = ["lcc_static"]

Otherwise, compile from source when building this Python wrapper, i.e.
CPP_SRC = "../src"
LIB_LIST = []
"""
__version__ = "0.0.1"
MODULE_NAME = "lcclib"
# Root directory to search for all *.cpp source to be wrapped
CPP_SRC = None
# Root directory to search for all *.h source to be wrapped
CPP_INC = "../inc"
# List of directory to search for external linked libraries
LIB_DIR = ["../lib"]
# List of externally linked libraries
LIB_LIST = ["lcc_static"]

def search_file(search_dir, file_pattern, excludes=None):
    """
    Recursively search a directory for files, excluding any specified sub-directories.

    Args:
        search_dir (str): Path to root directory to search.
        file_pattern (:obj:`list` of str): File patterns to search for.
        excludes (:obj:`list` of str): Sub-directories patterns to exclude from the search.

    Returns:
        :obj:`list` of str: List of files found.
    """
    # transform glob patterns to regular expressions
    file_pattern = r'|'.join([fnmatch.translate(x) for x in file_pattern])

    if excludes is not None:
        excludes = r'|'.join([fnmatch.translate(x) for x in excludes]) or r'$.'

    fname = []
    for root, dirs, files in os.walk(search_dir):
        # exclude dirs
        if excludes is not None:
            dirs[:] = [os.path.join(root, d) for d in dirs]
            dirs[:] = [d for d in dirs if not re.match(excludes, d)]

        # exclude/include files
        files = [os.path.join(root, f) for f in files]
        if excludes is not None:
            files = [f for f in files if not re.match(excludes, f)]
        files = [f for f in files if re.match(file_pattern, f)]

        fname.extend(files)

    return fname


class get_pybind_include(object):
    """Helper class to determine the pybind11 include path

    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)

src_list = ["wrapper.cpp"]
if CPP_SRC is not None:
    src_list.extend(search_file(CPP_SRC, ["*.cpp"]))

ext_modules = [
    Extension(
        name="_" + MODULE_NAME,
        sources=src_list,
        include_dirs=[
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True),
            CPP_INC
        ],
        define_macros=[('TARGET_OS_MAC', '1'),
                      ],
        libraries=LIB_LIST,
        library_dirs=LIB_DIR,
        language="c++"
    ),
]


# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.

    The c++14 is prefered over c++11 (when it is available).
    """
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }

    if sys.platform == 'darwin':
        c_opts['unix'] += ['-stdlib=libc++', '-mmacosx-version-min=10.7']

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
        for ext in self.extensions:
            ext.extra_compile_args = opts
        build_ext.build_extensions(self)

setup(
    name=MODULE_NAME,
    version=__version__,
    author='chiong.lai',
    author_email='chiong.lai@gmail.com',
    url='https://',
    description='Python wrapper for LCC lib',
    long_description='',
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.2'],
    cmdclass={'build_ext': BuildExt},
    zip_safe=False,
)
