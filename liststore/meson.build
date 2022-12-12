project(
    'testgtk',
    ['cpp'],
    version : '1.0',
    license : 'GPL-2.0',
    default_options : [
        'cpp_std=c++11',
    ],
)

    #'-DGDK_DISABLE_DEPRECATED',
    #'-DGTK_DISABLE_DEPRECATED',

cpp_args = [
    '-Wall',
    '-fno-rtti',
    '-fno-exceptions',
    '-O2',
]

#link_args = ['-Wl,--copy-dt-needed-entries',
#]

#prefix = '/usr/local'
#includedir = prefix + '/include'
#libdir = prefix + '/lib/x86_64-linux-gnu'

#winui_dep = declare_dependency(
#    include_directories : include_directories(includedir),
#    link_args : [
#        '-L' + libdir,
#        '-l:libwinui.a'
#    ],
#)

cc = meson.get_compiler('cpp')

tinycpp_dep = declare_dependency(
    include_directories : include_directories('.'),
    dependencies : cc.find_library('tinycpp'),
)

tinyui_dep = declare_dependency(
    include_directories : include_directories('.'),
    dependencies : cc.find_library('tinyui'),
)

app_deps = [
    dependency('gtk+-3.0'),
    #dependency('tinycpp', static : true),
    tinycpp_dep,
    tinyui_dep,
]

app_sources = [
    'main.cpp',
    'MainActions.cpp',
    'MainWindow.cpp',
]

executable(
    'testgtk',
    cpp_args : cpp_args,
    dependencies : app_deps,
    sources : app_sources,
)


