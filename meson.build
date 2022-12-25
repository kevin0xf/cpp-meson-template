project('Vortex', 'cpp', default_options: ['cpp_std=c++20'])

# thread_dep = dependency('threads')

compiler = meson.get_compiler('cpp')
# pwd = meson.current_source_dir()
# message(pwd/'dependencies/lib/GLFW')
# glfw_lib = compiler.find_library('glfw')
# glew_lib = compiler.find_library('GLEW')

subdir('src')

thread_dep = dependency('threads')

executable('Vortex', sources,
    dependencies: [thread_dep],
    include_directories: ['src/'],
    link_args: ['-lGL', '-lglfw', '-lGLEW', '-lvulkan', '-std=c++20']
)
