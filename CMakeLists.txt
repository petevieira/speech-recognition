
# specifiy minimum required cmake version
cmake_minimum_required(VERSION 2.6)

# set project name
project(speech-recognition)

#-------------------
#    VARIABLES
#-------------------
set(LIBRARY_INSTALL_PATH /usr/local/lib/)
set(BINARY_INSTALL_PATH /usr/local/bin/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

#--------------------------
#   SET COMPILER OPTIONS
#--------------------------
#list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall")
list(APPEND CMAKE_C_FLAGS "-std=gnu99 -Wall")
set(CMAKE_VERBOSE_MAKEFILE true)

#----------------------
#      ADD PATHS
#----------------------
set(POCKETSPHINX_INCLUDE_DIR "/usr/local/include/pocketsphinx")
set(SPHINXBASE_INCLUDE_DIR "/usr/local/include/sphinxbase")
set(SPHINX_LIBS_DIR "/usr/local/lib")
include_directories(${POCKETSPHINX_INCLUDE_DIR} ${SPHINXBASE_INCLUDE_DIR} include)


#-----------------------------
#   FIND PATH AND PACKAGES
#-----------------------------
find_path(POCKETSPHINX_INCLUDE pocketsphinx.h ${POCKETSPHINX_INCLUDE_DIR})
find_library(SPHINX_LIBS sphinxbase pocketsphinx sphinxad ${SPHINX_LIBS_DIR})
find_package(PkgConfig REQUIRED)

#------------------------------
#   GET LANGUAGE MODELS PATH
#------------------------------
add_definitions(-DMODELDIR="/usr/local/share/pocketsphinx/model")

#-------------------------
#     BUILD LIBRARIES
#-------------------------
add_library(ears src/ears.cpp include/ears.h)
target_link_libraries(ears pocketsphinx sphinxbase sphinxad)

#-------------------------
#    CREATE EXECUTABLES
#-------------------------
add_executable(hello-world_sphinx "src/hello-world_sphinx.c")
target_link_libraries(hello-world_sphinx pocketsphinx sphinxbase sphinxad)

add_executable(test-text2speech "src/test-text2speech.cpp")
add_executable(alsa-test "src/alsa-test.cpp")
target_link_libraries(alsa-test asound)
