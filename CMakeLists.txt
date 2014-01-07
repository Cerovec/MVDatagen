project(MVDatagen)
cmake_minimum_required(VERSION 2.8)

# Additional depencies
local_dependencies(GPUMVToolset MVToolset CoreUtils)

set(EXCLUDES "")

if(MSVC)
	list(APPEND EXCLUDES "Main.cpp")
endif()

# Obtain all source files
get_sources_from_dir(SOURCES ${SOURCE_DIR} "${EXCLUDES}")

add_definitions(-DALL_SEEDS)

build_static_library(${PROJECT_NAME} ${SOURCES})
if(NOT MSVC)
    build_exe(${PROJECT_NAME}-exe ${SOURCES})
    if(${PHOTOPAY_BUILD_EXE})
        set_target_properties(${PROJECT_NAME}-exe PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
    endif()
endif()
