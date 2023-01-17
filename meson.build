project(
    'testgtk',
    ['c'],
    version : '1.0',
    license : 'GPL-2.0',
    default_options : [
        'c_std=c99',
    ],
)

c_args = [
    '-Wall',
    '-Wextra',
]

if get_option('buildtype') == 'plain'
  c_args += '-O2'
endif

# examples
#dependency('libusb'),
#dependency('dbus-1'),
#dependency('gudev-1.0'),
#dependency('libxml-2.0'),

app_deps = [
    dependency('gtk+-3.0'),
    dependency('tinyc'),
    #dependency('libpcre'),
    #dependency('glib-2.0'),
    #dependency('gio-2.0'),
]

app_src = [
    'main.c',
]

executable(
    'testgtk',
    c_args : c_args,
    dependencies : app_deps,
    sources : app_src,
    install : false,
)


