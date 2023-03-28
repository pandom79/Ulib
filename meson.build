# (C) 2021 by Domenico Panella <pandom79@gmail.com>
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3.
# See http://www.gnu.org/licenses/gpl-3.0.html for full license text.

project('ulib', 'c', version: '3.0.0', default_options: ['warning_level=3', 'prefix=/usr'] )
add_global_arguments(['-Wno-incompatible-pointer-types'], language: 'c')

prj_name = 'ulib'
ver = '3.0.0'
so_ver = '3'

# Get paths
prefix = get_option('prefix')
datadir = get_option('datadir')

# Set paths
doc_path = get_option('DOC_PATH')
if doc_path == ''
    doc_path  = prefix/datadir/'doc'/prj_name+'-'+ver
endif

# Dependencies
math_dep = meson.get_compiler('c').find_library('m', required : true)

# Library
ulib = library(prj_name, 'ustring.c', 'uarray.c', 'udatetime.c',
               version: ver, soversion: so_ver,
               install: true, dependencies: math_dep
              )

# Generate pc file
pkg = import('pkgconfig')
pkg.generate(ulib,
             description: 'This library provides some functions to handle strings and array in C language.',
             subdirs: prj_name
            )

# Install Header
install_headers('ulib.h', subdir: prj_name)

# Install documentation
install_data('LICENSE', install_dir: doc_path)
install_data('README.md', install_dir: doc_path)

# Test
test_string_new = executable('test_string_new', 'test/string_new.c', link_with: ulib)
test_string_append = executable('test_string_append', 'test/string_append.c', link_with: ulib)
test_string_equals = executable('test_string_equals', 'test/string_equals.c', link_with: ulib)
test_string_split = executable('test_string_split', 'test/string_split.c', link_with: ulib)
test('Test string new', test_string_new)
test('Test string append', test_string_append)
test('Test string equals', test_string_equals)
test('Test string split', test_string_split)
