project(MVDatagen)
cmake_minimum_required(VERSION 2.8)

# Additional depencies
local_dependencies(GPUMVToolset MVToolset CoreUtils)

# Obtain all source files
get_sources_from_dir(SOURCES ${SOURCE_DIR})

add_definitions(-DALL_SEEDS)

build_static_library(${PROJECT_NAME} ${SOURCES})
build_exe(${PROJECT_NAME}-exe ${SOURCES})
set_target_properties(${PROJECT_NAME}-exe PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
