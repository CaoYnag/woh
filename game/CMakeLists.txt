cmake_minimum_required(VERSION 3.10)

project(test_color)

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

set(SRC
    ${PROJECT_SOURCE_DIR}/main.cpp
)

add_executable(game ${SRC})
target_link_libraries(game woh ai)