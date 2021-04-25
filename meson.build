project(
  'logging',
  'cpp',
  default_options : [
    'buildtype=release',
    'cpp_std=c++17',
    'warning_level=1'
  ]
)

logging_headers = [
  'include/logging/formatters/formatter.h',
  'include/logging/formatters/text.h',
  'include/logging/level.h',
  'include/logging/log.h',
  'include/logging/manager.h',
  'include/logging/record.h',
  'include/logging/sinks/cerr.h',
  'include/logging/sinks/cout.h',
  'include/logging/sinks/file.h',
  'include/logging/sinks/sink.h'
]

install_headers(
  logging_headers,
  subdir : 'logging'
)

logging_include_directories = include_directories('include')

logging_sources = [
  'src/formatters/text.cpp',
  'src/level.cpp',
  'src/log.cpp',
  'src/manager.cpp',
  'src/sinks/cerr.cpp',
  'src/sinks/cout.cpp',
  'src/sinks/file.cpp',
  'src/sinks/sink.cpp'
]

logging_library = static_library(
  'logging',
  logging_sources,
  include_directories : logging_include_directories
)

logging_dep = declare_dependency(
  include_directories : logging_include_directories,
  link_with : logging_library
)

logging_test = executable(
  'logging',
  'test/logging.cpp',
  include_directories : logging_include_directories,
  link_with : logging_library,
  dependencies : dependency('threads')
)
