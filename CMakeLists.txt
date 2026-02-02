cmake_minimum_required(VERSION 3.10)
project(td_animation)

# C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Plugin name
set(PLUGIN_NAME "td_animation")

# Source files
set(SOURCE_FILES
    main.cpp
    TDAnimation.cpp
)

# Header files
set(HEADER_FILES
    TDAnimation.h
)

# SA-MP SDK path (adjust this to your SA-MP SDK location)
set(SAMP_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDK")

# Include directories
include_directories(
    ${SAMP_SDK_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Platform-specific settings
if(WIN32)
    # Windows
    add_library(${PLUGIN_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
    set_target_properties(${PLUGIN_NAME} PROPERTIES
        PREFIX ""
        SUFFIX ".dll"
        OUTPUT_NAME ${PLUGIN_NAME}
    )
    
    # Windows-specific compile options
    target_compile_definitions(${PLUGIN_NAME} PRIVATE
        WIN32
        _WINDOWS
        _USRDLL
        _CRT_SECURE_NO_WARNINGS
    )
    
elseif(UNIX)
    # Linux
    add_library(${PLUGIN_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
    set_target_properties(${PLUGIN_NAME} PROPERTIES
        PREFIX ""
        SUFFIX ".so"
        OUTPUT_NAME ${PLUGIN_NAME}
    )
    
    # Linux-specific compile options
    target_compile_options(${PLUGIN_NAME} PRIVATE
        -m32
        -fPIC
        -O3
    )
    
    target_link_options(${PLUGIN_NAME} PRIVATE
        -m32
    )
    
    # Link pthread for threading
    target_link_libraries(${PLUGIN_NAME} pthread)
endif()

# Output directory
set_target_properties(${PLUGIN_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install target
install(TARGETS ${PLUGIN_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
)

# Install include file
install(FILES td_animation_plugin.inc
    DESTINATION include
)
