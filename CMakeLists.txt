cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(bhs_vis VERSION 1.0.0 LANGUAGES CXX)

if (NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold "${Esc}[1m")
    set(Red "${Esc}[31m")
    set(Green "${Esc}[32m")
    set(Yellow "${Esc}[33m")
    set(Blue "${Esc}[34m")
    set(Magenta "${Esc}[35m")
    set(Cyan "${Esc}[36m")
    set(White "${Esc}[37m")
    set(BoldRed "${Esc}[1;31m")
    set(BoldGreen "${Esc}[1;32m")
    set(BoldYellow "${Esc}[1;33m")
    set(BoldBlue "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan "${Esc}[1;36m")
    set(BoldWhite "${Esc}[1;37m")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

set(THE_EXE_NAME bhs_visualization)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building in debug mode")
    add_definitions(-DDEBUG -URELEASE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    # comment this if you want to remove the verbose output
    #    add_definitions(-DVERBOSE)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building in release mode")
    add_definitions(-DRELEASE -UVERBOSE -UDEBUG)
    # comment this if you want to remove the verbose output
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    message("Building in release mode")
    add_definitions(-DRELEASE -DVERBOSE-UDEBUG)
    # comment this if you want to remove the verbose output
else ()
    message(WARNING "Building in something mode???????")

    # comment this if you want to remove the verbose output
    #    add_definitions(-DVERBOSE)
endif ()

# allow for the use of the -pthread flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
# For eigen multithreaded
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found")
    message(STATUS "OpenMP_CXX_FLAGS: ${OpenMP_CXX_FLAGS}")
    message(STATUS "USED FOR Eigen multithreading")
endif ()


# ============================================================================
# Vulkan
# ============================================================================
message("${Cyan}Attempting auto locate Vulkan using CMake......${ColourReset}")

# Find Vulkan Path using CMake's Vulkan Module
# This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
# Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
find_package(Vulkan)
# Try extracting VulkanSDK path from ${Vulkan_INCLUDE_DIRS}
if (NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
    set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
    STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
endif ()

if (NOT Vulkan_FOUND)
    # CMake may fail to locate the libraries but could be able to
    # provide some path in Vulkan SDK include directory variable
    # 'Vulkan_INCLUDE_DIRS', try to extract path from this.
    message(STATUS "Failed to locate Vulkan SDK, retrying again...")
    if (EXISTS "${VULKAN_PATH}")
        message(STATUS "Successfully located the Vulkan SDK: ${VULKAN_PATH}")
    else ()
        message("Error: Unable to locate Vulkan SDK. Please turn off auto locate option by specifying 'AUTO_LOCATE_VULKAN' as 'OFF'")
        message("and specify manually path using 'VULKAN_SDK' and 'VULKAN_VERSION' variables in the CMakeLists.txt.")
        return()
    endif ()
endif ()

# Add any required preprocessor definitions here
#add_definitions(-DVK_USE_PLATFORM_)

# vulkan-1 library for build Vulkan application.
#set(VULKAN_LIB_LIST "vulkan-1")
# Note I could not make the above work:
set(VULKAN_LIB_LIST "vulkan")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Include Vulkan header files from Vulkan SDK
    include_directories(AFTER ${VULKAN_PATH}/Include)
    # Link directory for vulkan-1
    link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib;)
endif ()

# Define directories and the contained folder and files inside.
if (WIN32)
    source_group("include" REGULAR_EXPRESSION "include/*")
    source_group("source" REGULAR_EXPRESSION "source/*")
endif (WIN32)

# ============================================================================
# GLFW
# ============================================================================

# ============================================================================
# GLM
# ============================================================================
set(GML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm)

# ============================================================================
# ImGui
# ============================================================================
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)
#ImGui is not added as a subdirectory because it is not a library but a header only library
set(IMGUI_FILES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
        )
# ============================================================================
# Torch (PyTorch)
# ============================================================================
find_package(Torch REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/BHS_game/third_party/libtorch)
if (NOT Torch_FOUND)
    message(FATAL_ERROR "PyTorch Not Found!")
endif (NOT Torch_FOUND)

# ============================================================================
# BHS_vis
# ============================================================================

set(SOURCE_FILES main.cpp ${IMGUI_FILES})
add_executable(${THE_EXE_NAME} ${SOURCE_FILES})

message(STATUS "Attempting to add subdirectories")
# needed for src
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GML_DIR}
        ${IMGUI_DIR}
        #        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw
        # BHS_game require us to include its third_party folders... This must not be correct but i need to get this working
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/BHS_game/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/BHS_game/third_party/eigen
        ${TORCH_INCLUDE_DIRS}
)
add_subdirectory(third_party/BHS_game)
add_subdirectory(src)
add_subdirectory(third_party/glfw)
#add_subdirectory(third_party/glm)
message(STATUS "Finished adding subdirectories")
# Find the BHS_game package

#find_package(bhs_game_lib REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/BHS_game/cmake-build-debug)
# Link the BHS::bhs_game target to your executable or library
#target_link_libraries(your_target PRIVATE BHS::bhs_game)


target_link_libraries(${THE_EXE_NAME} PRIVATE
        bhs_vis_lib
        # Local third party:
        bhs_game_lib  # <--- this is the library that is built in the my_library subdirectory
        glfw
        # Vulkan;
        ${VULKAN_LIB_LIST}
        ${TORCH_LIBRARIES}
        # threading:
        dl
        OpenMP::OpenMP_CXX
        )

enable_testing()
add_subdirectory(tests)
