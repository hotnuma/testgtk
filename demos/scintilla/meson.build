project(
    'testgtk',
    ['c', 'cpp'],
    version : '1.0',
    license : 'GPL-2.0',
    default_options : [
        'c_std=c99',
    ],
)

c_args = [
    '-Wall',
    '-O2',
    '-DGTK',
]

link_args = [
    '-Wl,--copy-dt-needed-entries',
]

incdir = '/usr/local/include'
cc = meson.get_compiler('cpp')
scintilla_dep = declare_dependency(
    include_directories : include_directories(incdir + '/scintilla'),
    dependencies : cc.find_library('scintilla'),
)

testgtk_dep = [
    dependency('gtk+-3.0'),
    scintilla_dep,
    dependency('tinyc'),
]

testgtk_src = [
    'main.c',
#    'MainActions.cpp',
#    'MainWindow.cpp',
]

executable(
    meson.project_name(),
    c_args : c_args,
    link_args : link_args,
    dependencies : testgtk_dep,
    sources : testgtk_src,
)


