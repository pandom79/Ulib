# (C) 2021 by Domenico Panella <pandom79@gmail.com>
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3.
# See http://www.gnu.org/licenses/gpl-3.0.html for full license text.

project('wrapper', 'c', version: '1.0.0', default_options: ['warning_level=3', 'prefix=/usr'] )
add_global_arguments(['-Wno-incompatible-pointer-types'], language: 'c')

prj_name = 'wrapper'
ver = '1.0.0'
so_ver = '1'

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

# Header
install_headers('wrapper.h', subdir : prj_name)

# Only for test
#executable('wrapper', 'main.c',
#           link_with: libwrapper, install: true
#          )
