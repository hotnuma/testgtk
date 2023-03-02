project(
    'testroot',
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

app_deps = [
    dependency('gtk+-3.0'),
    dependency('tinyc'),
]

app_src = [
    'main.c',
]

executable(
    meson.project_name(),
    c_args : c_args,
    dependencies : app_deps,
    sources : app_src,
    install : true,
)

install_data(
    'data/org.hotnuma.testroot.policy',
    install_dir: '/usr/share/polkit-1/actions/',
)

install_data(
    'data/testroot.desktop',
    install_dir: get_option('datadir') / 'applications',
)


