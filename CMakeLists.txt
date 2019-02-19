cmake_minimum_required(VERSION 2.8.3)

project(FlexSEA-Stack-Plan)

set(SRCS
	src/flexsea_board.c
	src/flexsea_config.c
	src/trapez.c
	src/revision.c
)

include_directories (
	inc
	flexsea-comm/inc
	flexsea-projects/inc
	flexsea-projects/ActPack/inc
	flexsea-projects/Rigid/inc
	flexsea-system/inc
	flexsea-dephy/inc
	flexsea-dephy/DpEb42/inc
	flexsea-dephy/inc
	flexsea-dephy/CycleTester/inc
)

add_subdirectory(flexsea-comm)
add_subdirectory(flexsea-system)
add_subdirectory(flexsea-projects)
add_subdirectory(flexsea-dephy)

set(FLEXSEA_SRCFILES ${SRCS})
add_library(FlexSea_objs OBJECT ${FLEXSEA_SRCFILES})

add_definitions(-DBUILD_SHARED_LIB_DLL -DTEST_PC -DINCLUDE_UPROJ_ACTPACK -DBOARD_TYPE_FLEXSEA_PLAN)
#add_definitions(-DDEPHY -DACTIVE_DEPHY_PROJECT=PRJ_DEPHY_DPEB42 -DINCLUDE_UPROJ_DPEB42 -DINCLUDE_UPROJ_CYCLE_TESTER)

add_library(FlexSEA-Stack-Plan_shared SHARED $<TARGET_OBJECTS:FlexSea_objs>)
add_library(FlexSEA-Stack-Plan STATIC $<TARGET_OBJECTS:FlexSea_objs>)
set_property(TARGET FlexSea_objs PROPERTY POSITION_INDEPENDENT_CODE ON)

## Force generation of the revsion header file BEFORE building the targets
##  Create a psuedo-target to be created before the library
IF(WIN32)
add_custom_target(
	revisionTarget
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/update_revs.bat ${CMAKE_CURRENT_SOURCE_DIR}/inc/git_rev_data.h
	COMMENT "Updating revision information"
)
ELSE()
add_custom_target(
	revisionTarget
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/update_revs.sh ${CMAKE_CURRENT_SOURCE_DIR}/git-revision.py ${CMAKE_CURRENT_SOURCE_DIR}/inc/git_rev_data.h
	COMMENT "Updating revision informatio"
)
ENDIF()

add_dependencies(FlexSea_objs revisionTarget)

if(WIN32)
	set(OUT_PREF "win")
else()
	set(OUT_PREF "unix")	
endif()

if(CMAKE_SIZEOF_VOID_P GREATER 4)
	set(OUT_PREF "${OUT_PREF}_64")
endif()

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
