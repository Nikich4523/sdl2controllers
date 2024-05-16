cmake_minimum_required(VERSION 3.16)

project(sdl2controllers)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${sdl2controllers_SOURCE_DIR})

############################
find_package(SDL2 REQUIRED)
if ( SDL2_FOUND )
    list (APPEND SDL2CONTROLLERS_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
    list (APPEND SDL2CONTROLLERS_LIBRARIES ${SDL2_LIBRARY})
endif( SDL2_FOUND )

find_package(SDL2_image REQUIRED)
if ( SDL2_image_FOUND )
    list (APPEND SDL2CONTROLLERS_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIRS})
    list (APPEND SDL2CONTROLLERS_LIBRARIES ${SDL2_IMAGE_LIBRARIES})
endif( SDL2_image_FOUND )
############################

set(SDL2CONTROLLERS_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/base/DummyWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/base/DummyWindow.h

	# getting started
	${CMAKE_CURRENT_SOURCE_DIR}/src/0_getting_started/getting_started.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/0_getting_started/getting_started.h

	# rotate arrpw
	${CMAKE_CURRENT_SOURCE_DIR}/src/1_rotate_arrow/RotateArrow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/1_rotate_arrow/RotateArrow.h

)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable(sdl2controllers ${SDL2CONTROLLERS_SOURCES})

target_link_libraries(sdl2controllers ${SDL2CONTROLLERS_LIBRARIES})

