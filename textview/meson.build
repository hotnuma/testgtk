project(
    'testgtk',
    ['cpp'],
    version : '1.0',
    license : 'GPL-2.0',
    default_options : [
        'cpp_std=c++11',
    ],
)

cpp_args = [
    '-Wall',
    '-fno-rtti',
    '-fno-exceptions',
    '-O2',
]

cc = meson.get_compiler('cpp')

tinycpp_dep = declare_dependency(
    dependencies : cc.find_library('tinycpp'),
)

tinyui_dep = declare_dependency(
    dependencies : cc.find_library('tinyui'),
)

testgtk_dep = [
    dependency('gtk+-3.0'),
    tinycpp_dep,
    tinyui_dep,
]

testgtk_src = [
    'main.cpp',
    'MainActions.cpp',
    'MainWindow.cpp',
]

executable(
    'testgtk',
    cpp_args : cpp_args,
    dependencies : testgtk_dep,
    sources : testgtk_src,
)


