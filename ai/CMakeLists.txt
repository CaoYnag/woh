cmake_minimum_required(VERSION 3.10)

project(ai)
message(STATUS "ais of woh.")

set(SRC
    ${PROJECT_SOURCE_DIR}/minmon.cpp
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

set(LIB_NAME ai)
add_library(${LIB_NAME} STATIC ${SRC})
target_link_libraries(${LIB_NAME} woh)