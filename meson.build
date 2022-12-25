project('Vortex', 'cpp', default_options: ['cpp_std=c++20'])

subdir('src')

thread_dep = dependency('threads')

executable('Vortex', sources,
    dependencies: [thread_dep],
    include_directories: ['src/'],
    link_args: ['-lGL', '-lglfw', '-lGLEW', '-lvulkan']
)
