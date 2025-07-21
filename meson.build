project(
  'BobEngine',
  'cpp',
  version: run_command('cat', join_paths(meson.project_source_root(), 'VERSION'), check: true).stdout().strip(),
  default_options: [
    'warning_level=3',
    'b_ndebug=if-release',
    'buildtype=release',
  ],
)

deps = [ dependency('glfw3'), dependency('glm'), dependency('spdlog') ,subproject('glad-0.1.36').get_variable('glad_dep')]
include_dirs = include_directories('src')
link_args = []
src_files = []

subdir('src')


pch_files = [join_paths('src', 'pch.h')]

executable(
  meson.project_name(),
  src_files,
  link_args: link_args,
  cpp_pch: pch_files,
  dependencies: deps,
  include_directories: include_dirs,
  install: true,
)
