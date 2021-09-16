cmake_minimum_required(VERSION 3.10)



project( lab24 VERSION 0.3 LANGUAGES C )



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

)
target_link_libraries( ${PROJECT_NAME} PRIVATE
	${STACK_T} 
	${QUEUE_T} 
	${TREE_T} 
	${LAB_STRUCT} )

