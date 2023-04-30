file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(bhs_vis_lib STATIC ${SOURCES})

target_include_directories(bhs_vis_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
