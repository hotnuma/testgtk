project(
    'testgtk',
    ['c'],
    version : '1.0',
    license : 'GPL-2.0',
    default_options : [
        'c_std=c11',
    ],
)

c_args = [
    '-Wall',
    '-Wextra',
]

if get_option('buildtype') == 'plain'
  c_args += '-O2'
endif

app_deps = [
    dependency('gtk+-3.0'),
    dependency('tinyc'),
]

app_sources = [
    'application.c',
    'main.c',
    'preferences.c',
    'window.c',
]

executable(
    'testgtk',
    c_args : c_args,
    dependencies : app_deps,
    sources : app_sources,
)


