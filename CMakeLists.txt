cmake_minimum_required(VERSION 2.8.3)

project(FlexSEA-Stack-Plan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set some system-wide defaults
if(WIN32)
	set(OUT_PREF "win")
else()
	set(OUT_PREF "unix")	
endif()

if(CMAKE_SIZEOF_VOID_P GREATER 4)
	set(OUT_PREF "${OUT_PREF}_64")
endif()

# This projects source files
#  We'll add to this in each of the sub-directories
set(SRCS
	src/flexsea_board.c
	src/flexsea_config.c
	src/trapez.c
)

# Point to all the place sto find header files
include_directories (
	inc
	flexsea-comm/inc
	flexsea-projects/inc
	flexsea-projects/ActPack/inc
	flexsea-projects/Rigid/inc
	flexsea-system/inc
)

# Add the individual libraries (projects)
add_subdirectory(flexsea-comm)
add_subdirectory(flexsea-system)
add_subdirectory(flexsea-projects)

add_definitions(-DBUILD_SHARED_LIB_DLL -DTEST_PC -DINCLUDE_UPROJ_ACTPACK -DBOARD_TYPE_FLEXSEA_PLAN)
#add_definitions(-DDEPHY)

add_library(FlexSEA-Stack-Plan_shared SHARED 
	${SRCS}
	${COMM_LIB_SRCS}
	${PROJECTS_LIB_SRCS}
	${SYSTEM_LIB_SRCS})
set_property(TARGET FlexSEA-Stack-Plan_shared PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(FlexSEA-Stack-Plan STATIC
	${SRCS}
	${COMM_LIB_SRCS}
	${PROJECTS_LIB_SRCS}
	${SYSTEM_LIB_SRCS})
set_property(TARGET FlexSEA-Stack-Plan PROPERTY POSITION_INDEPENDENT_CODE ON)

set_target_properties( FlexSEA-Stack-Plan_shared 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUT_PREF}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUT_PREF}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUT_PREF}"
)

set_target_properties( FlexSEA-Stack-Plan
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUT_PREF}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUT_PREF}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUT_PREF}"
)
