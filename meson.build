# (C) 2021 by Domenico Panella <pandom79@gmail.com>
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3.
# See http://www.gnu.org/licenses/gpl-3.0.html for full license text.

project('wrapper', 'c', version: '2.0.1', default_options: ['warning_level=3', 'prefix=/usr'] )
add_global_arguments(['-Wno-incompatible-pointer-types'], language: 'c')

prj_name = 'wrapper'
ver = '2.0.1'
so_ver = '2'

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
libwrapper = library(prj_name, 'string_wrapper.c', 'array_wrapper.c', 'datetime_wrapper.c',
                     version: ver, soversion: so_ver,
                     install: true, dependencies : math_dep
                     )

# Generate pc file
pkg = import('pkgconfig')
pkg.generate(libwrapper,
             description : 'This library provides some functions to handle strings and array in C language.',
             subdirs : prj_name
             )

# Install Header
install_headers('wrapper.h', subdir : prj_name)

# Install documentation
install_data('LICENSE', install_dir: doc_path)
install_data('README.md', install_dir: doc_path)

# Only for test
#executable('wrapper', 'main.c',
#           link_with: libwrapper, install: true
#          )
