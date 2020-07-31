cmake_minimum_required(VERSION 3.10)

project(woh)
message(STATUS "war of heats main library.")

set(SRC
    ${PROJECT_SOURCE_DIR}/defs.cpp
    ${PROJECT_SOURCE_DIR}/player.cpp
    ${PROJECT_SOURCE_DIR}/ui.cpp
    ${PROJECT_SOURCE_DIR}/cui.cpp
    ${PROJECT_SOURCE_DIR}/game.cpp
)

if(WIN32)
	if($ENV{LIB_BASE})
	else()
		include_directories(
			$ENV{LIB_BASE}/include
		)
		link_directories(
			$ENV{LIB_BASE}/lib
		)
	endif()
endif()

set(LIB_NAME woh)
add_library(${LIB_NAME} STATIC ${SRC})