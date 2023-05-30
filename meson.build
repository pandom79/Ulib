# (C) 2021 by Domenico Panella <pandom79@gmail.com>
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3.
# See http://www.gnu.org/licenses/gpl-3.0.html for full license text.

project('ulib', 'c', version: '4.0.1', default_options: ['warning_level=3', 'prefix=/usr'] )
add_global_arguments(['-Wno-incompatible-pointer-types'], language: 'c')

prj_name = 'ulib'
ver = '4.0.1'
so_ver = '4'

# Get paths
prefix = get_option('prefix')
datadir = get_option('datadir')
build_root = meson.global_build_root()

# Get test option
no_test = get_option('NO_TEST')

# Get doxygen options
doxy_latex = get_option('DOXY_LATEX')
conf_doxy_latex = 'YES'
doxy_html = get_option('DOXY_HTML')
conf_doxy_html = 'YES'

# Set paths
doc_path = get_option('DOC_PATH')
if doc_path == ''
    doc_path  = prefix/datadir/'doc'/prj_name+'-'+ver
endif

# Dependencies
math_dep = meson.get_compiler('c').find_library('m', required : true)
if doxy_html == true or doxy_latex == true
    find_program('doxygen', required: true)
    if (doxy_latex == false)
        conf_doxy_latex = 'NO'
    endif
    if (doxy_html == false)
        conf_doxy_html = 'NO'
    endif
    # Configuration
    conf_doxy = configuration_data()
    conf_doxy.set('BUILD_ROOT', build_root)
    conf_doxy.set('LATEX', conf_doxy_latex)
    conf_doxy.set('HTML', conf_doxy_html)
    configure_file(input: 'Doxyfile.in', output: 'Doxyfile', configuration: conf_doxy)
    message('Building the documentation ... ')
    run_command('doxygen', build_root/'Doxyfile', check: true)
endif

# Library
ulib = library(prj_name,
               'ustring/ustring.c',
               'uarray/uarray.c',
               'udatetime/udatetime.c',
               'uhashtable/uhashtable.c',
               version: ver,
               soversion: so_ver,
               install: true,
               dependencies: math_dep
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

# Install doxy documentation
if (doxy_html == true)
    install_subdir(build_root/'html', install_dir: doc_path)
endif
if (doxy_latex == true)
    install_subdir(build_root/'latex', install_dir: doc_path)
endif

# Test
if (no_test == false)
    test_string_new = executable('test_string_new', 'test/string_new.c', link_with: ulib)
    test_string_append = executable('test_string_append', 'test/string_append.c', link_with: ulib)
    test_string_equals = executable('test_string_equals', 'test/string_equals.c', link_with: ulib)
    test_string_split = executable('test_string_split', 'test/string_split.c', link_with: ulib)
    test_array_str_copy = executable('test_array_str_copy', 'test/array_str_copy.c', link_with: ulib)
    test_array_str_contains = executable('test_array_str_contains', 'test/array_str_contains.c', link_with: ulib)
    test_array_release = executable('test_array_release', 'test/array_release.c', link_with: ulib)
    test_ht_release = executable('test_ht_release', 'test/ht_release.c', link_with: ulib)
    test_ht_release_no_alloc = executable('test_ht_release_no_alloc', 'test/ht_release_no_alloc.c', link_with: ulib)
    test_ht_get_iterator = executable('test_ht_get_iterator', 'test/ht_get_iterator.c', link_with: ulib)
    test('test_string_new', test_string_new)
    test('test_string_append', test_string_append)
    test('test_string_equals', test_string_equals)
    test('test_string_split', test_string_split)
    test('test_array_str_copy', test_array_str_copy)
    test('test_array_str_contains', test_array_str_contains)
    test('test_array_release', test_array_release)
    test('test_ht_release', test_ht_release)
    test('test_ht_release_no_alloc ', test_ht_release_no_alloc)
    test('test_ht_get_iterator', test_ht_get_iterator)
endif
