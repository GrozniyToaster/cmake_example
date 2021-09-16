cmake_minimum_required(VERSION 3.10)



project( ${QUEUE_T} VERSION 0.3 LANGUAGES C )


add_definitions(-Wall  -std=c99 -pedantic)


add_library( ${QUEUE_T} STATIC 
	"${QUEUE_T_PATH}/${QUEUE_T_SOURCE}" )

target_include_directories( ${QUEUE_T} 
	PUBLIC 
		"${LAB_STRUCT_PATH}"
)

target_link_libraries(  ${QUEUE_T}  ${LAB_STRUCT} )







