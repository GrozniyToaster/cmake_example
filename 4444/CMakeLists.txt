cmake_minimum_required(VERSION 3.10)



project( lab24 LANGUAGES C ) # project( lab24 VERSION 0.3 LANGUAGES C ) можно задатть версию так

option(bug "Включает отладучную информацию" OFF)
message( STATUS "Dbug:" ${bug} " чтобы включить отладочный релиз запустить с ключом -Dbug=ON" )

if ( bug )
    add_definitions( -g3 )
    set ( CMAKE_BUILD_TYPE Debug )
endif( bug )

set( STACK_T stack24)
set( STACK_T_SOURCE stack_token.c )
set( STACK_T_PATH "${PROJECT_SOURCE_DIR}/stack_token" )

set( QUEUE_T queue24  )
set( QUEUE_T_SOURCE queue_token.c )
set( QUEUE_T_PATH "${PROJECT_SOURCE_DIR}/queue_token" )

set( TREE_T tree24  )
set( TREE_T_SOURCE tree_token.c )
set( TREE_T_PATH "${PROJECT_SOURCE_DIR}/tree_token" )

set( LAB_STRUCT struct24  )
set( LAB_STRUCT_SOURCE lab24_struct.c )
set( LAB_STRUCT_PATH "${PROJECT_SOURCE_DIR}/lab_struct" )


set(${PROJECT_NAME}_VERSION_PATCH 4 )
set(${PROJECT_NAME}_VERSION_MAJOR 1 )

set( ${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_PATCH}" )

message("Alrady done")

add_subdirectory( "${LAB_STRUCT_PATH}" )
add_subdirectory( "${QUEUE_T_PATH}" )
add_subdirectory( "${STACK_T_PATH}" )
add_subdirectory( "${TREE_T_PATH}" )
file(GLOB
	PROJ_SOURC "*c")

add_executable(${PROJECT_NAME} ${PROJ_SOURC})

add_definitions(  -Wall  -std=c99 -pedantic)



target_include_directories( ${PROJECT_NAME} PRIVATE
		${LAB_STRUCT_PATH}
		${STACK_T_PATH}
		${QUEUE_T_PATH}
		${TREE_T_PATH}
		${PROJECT_BINARY_DIR}

)


target_link_libraries( ${PROJECT_NAME} PRIVATE
	${STACK_T} 
	${QUEUE_T} 
	${TREE_T} 
	${LAB_STRUCT} )


configure_file(
            "${PROJECT_SOURCE_DIR}/includes/version.h.in"
            "${PROJECT_BINARY_DIR}/version.h"
            )
message( " MAKE файл для ${PROJECT_NAME} успешно собран \t версия ${${PROJECT_NAME}_VERSION}\n" )

