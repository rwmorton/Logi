add_library(identifyTokens_obj identifyTokens.cpp)
add_library(loadASM_obj loadASM.cpp)

target_include_directories(identifyTokens_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(loadASM_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
