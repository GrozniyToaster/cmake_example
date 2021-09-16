cmake_minimum_required(VERSION 3.10)



project( ${TREE_T} VERSION 0.3 LANGUAGES C )


add_definitions(-Wall  -std=c99 -pedantic)


add_library( ${TREE_T} STATIC 
	"${TREE_T_PATH}/${TREE_T_SOURCE}" )
target_include_directories( ${TREE_T}
	PUBLIC 
		"${LAB_STRUCT_PATH}"
)

target_link_libraries(  ${TREE_T}  ${LAB_STRUCT} )







