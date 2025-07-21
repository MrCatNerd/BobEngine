project('glad',
    'c',
    version: '0.1.36',
    license: 'MIT'
)

add_project_arguments('-w', language: 'c') # Disable all warnings

glad_inc = include_directories('include')

glad_lib = static_library('glad', 'src/glad.c',
    include_directories: glad_inc,
)

glad_dep = declare_dependency(
    include_directories: glad_inc,
    link_with: glad_lib,
)
