
# specifiy minimum required cmake version
cmake_minimum_required(VERSION 2.6)

# set project name
project(speech-recognition)

# set include directory
include_directories(include)

# install path variables
set(LIBRARY_INSTALL_PATH /usr/local/lib/)
set(BINARY_INSTALL_PATH /usr/local/bin/)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# set c compiler
set(CMAKE_C_FLAGS "-std=gnu99")

# set make compilation to verbose mode
set(CMAKE_VERBOSE_MAKEFILE true)

# set include directories
set(POCKETSPHINX_INCLUDE_DIR "/usr/local/include/pocketsphinx")
set(SPHINXBASE_INCLUDE_DIR "/usr/local/include/sphinxbase")

# set library directory
set(SPHINX_LIBS_DIR "/usr/local/lib")

find_path(POCKETSPHINX_INCLUDE pocketsphinx.h ${POCKETSPHINX_INCLUDE_DIR})
if(${POCKETSPHINX_INCLUDE} STREQUAL POCKETSPHINX_INCLUDE-NOTFOUND)
    message("\n-- INFO: could not find pocketsphinx includes.\n")
else()
    message("\n-- found pocketsphinx includes at ${POCKETSPHINX_INCLUDE_DIR}\n")
endif()

find_library(SPHINX_LIBS sphinxbase pocketsphinx sphinxad ${SPHINX_LIBS_DIR})
if(${SPHINX_LIBS} STREQUAL SPHINX_LIBS-NOTFOUND)
    message("\n-- INFO: could not find sphinx libs.\n")
else()
    message("\n-- found sphinx libs at ${SPHINX_LIBS_DIR}\n")
endif()


# add executables
#add_executable(hello-world_sphinx "src/hello-world_sphinx.c")
#target_link_libraries(hello-world_sphinx pocketsphinx sphinxbase sphinxad)

add_executable(test-text2speech "src/test-text2speech.cpp")
add_executable(alsa-test "src/alsa-test.cpp")
target_link_libraries(alsa-test asound)
