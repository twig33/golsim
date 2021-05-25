project('golsim', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

gtkmmdep = dependency('gtkmm-3.0')

executable('golsim',
           'main.cpp',
           'gol_simulator.cpp',
           dependencies: gtkmmdep,
           install : true)

configure_file(input: 'golsim.glade', output: 'golsim.glade', copy: true)
