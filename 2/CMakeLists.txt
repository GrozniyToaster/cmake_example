cmake_minimum_required(VERSION 3.10)



project( lab24 VERSION 0.2 LANGUAGES C )



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

#include_directories("${LAB_STRUCT_PATH}")
#include_directories("${STACK_T_PATH}")
#include_directories("${QUEUE_T_PATH}")
#include_directories("${TREE_T_PATH}")

add_library( ${LAB_STRUCT} STATIC 
	"${LAB_STRUCT_PATH}/${LAB_STRUCT_SOURCE}" )


add_library( ${STACK_T} STATIC 
	"${STACK_T_PATH}/${STACK_T_SOURCE}" 
)

target_include_directories( ${STACK_T} 
	PUBLIC 
		"${LAB_STRUCT_PATH}" #этой библиотеке нужна линковка с другой
)

target_link_libraries(  ${STACK_T}  ${LAB_STRUCT} ) 


add_library( ${QUEUE_T} STATIC 
	"${QUEUE_T_PATH}/${QUEUE_T_SOURCE}" )

target_include_directories( ${QUEUE_T} 
	PUBLIC 
		"${LAB_STRUCT_PATH}"
)

target_link_libraries(  ${QUEUE_T}  ${LAB_STRUCT} )


add_library( ${TREE_T} STATIC 
	"${TREE_T_PATH}/${TREE_T_SOURCE}" )
target_include_directories( ${TREE_T}
	PUBLIC 
		"${LAB_STRUCT_PATH}"
)

target_link_libraries(  ${TREE_T}  ${LAB_STRUCT} )


file(GLOB
	PROJ_SOURC "*.c")

add_executable(${PROJECT_NAME} ${PROJ_SOURC})

add_definitions(-Wall  -std=c99 -pedantic)



target_include_directories( ${PROJECT_NAME}
	PUBLIC
		${LAB_STRUCT_PATH}
		${STACK_T_PATH}
		${QUEUE_T_PATH}
		${TREE_T_PATH}

)
target_link_libraries( ${PROJECT_NAME} PUBLIC 
	${STACK_T} 
	${QUEUE_T} 
	${TREE_T} 
	${LAB_STRUCT} )

