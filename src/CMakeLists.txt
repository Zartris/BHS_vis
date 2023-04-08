file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(bhs_vis ${SOURCES})

target_include_directories(bhs_vis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
