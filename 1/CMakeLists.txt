cmake_minimum_required(VERSION 3.10)


project( Lab24 VERSION 0.1 LANGUAGES C )

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library( stack24 STATIC stack_token.c )
add_library( queue24 STATIC queue_token.c )

add_library( tree24 STATIC tree_token.c )
add_library( struct24 STATIC lab24_struct.c )

add_executable(${PROJECT_NAME} lab24.c)

add_definitions(-Wall  -std=c99 -pedantic)


target_link_libraries( ${PROJECT_NAME} stack24 queue24 tree24 struct24 )
