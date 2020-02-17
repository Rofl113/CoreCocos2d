cmake_minimum_required(VERSION 3.5)

add_subdirectory(CoreCocos2d)

# CoreCocos2d root path
target_include_directories(CoreCocos2d_LIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
