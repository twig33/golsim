project('golsim', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

gtkmmdep = dependency('gtkmm-3.0')

executable('golsim',
           'main.cpp',
           dependencies: gtkmmdep,
           install : true)
