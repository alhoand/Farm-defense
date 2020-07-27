cmake_minimum_required(VERSION 2.8.9)
project (TowerDefense)

set(EXECUTABLE_NAME TowerDefense)

# This is for the paths to work correctly 
cmake_policy(SET CMP0076 NEW)


#add the executable with an empty list of sources
add_executable(${EXECUTABLE_NAME} "")


## In most cases better set in the CMake cache
# this is to tell where to find sfml if not in a "normal" place
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")


## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

# Detect and add SFML
#Find any version 2.X of SFML
find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)

add_subdirectory(src)

target_compile_options(${EXECUTABLE_NAME} PRIVATE -std=c++11 -Wall -Wextra -pedantic -Werror -g)
target_link_libraries(${EXECUTABLE_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

# For installing targets (not mandatory)
install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
