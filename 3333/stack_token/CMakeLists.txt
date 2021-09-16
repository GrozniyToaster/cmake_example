cmake_minimum_required(VERSION 3.10)



project( ${STACK_T} VERSION 0.3 LANGUAGES C )



add_definitions(-Wall  -std=c99 -pedantic)


add_library( ${STACK_T} STATIC 
	"${STACK_T_PATH}/${STACK_T_SOURCE}" 
)

target_include_directories( ${STACK_T} 
	PUBLIC 
		"${LAB_STRUCT_PATH}" #этой библиотеке нужна линковка с другой
)

target_link_libraries(  ${STACK_T}  ${LAB_STRUCT} ) 







