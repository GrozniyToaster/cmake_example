cmake_minimum_required(VERSION 3.10)



project( ${LAB_STRUCT} VERSION 0.3 LANGUAGES C )

add_definitions(-Wall  -std=c99 -pedantic)



add_library( ${LAB_STRUCT} STATIC 
	"${LAB_STRUCT_PATH}/${LAB_STRUCT_SOURCE}" )









