cmake_minimum_required(VERSION 3.16)

project(LOGI CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-std=c++2a)

add_subdirectory(types)
add_subdirectory(instructionset)
add_subdirectory(virtualmachine)
add_subdirectory(debugger)

add_library(Types_obj Types.cpp)
add_library(Bytecode_obj Bytecode.cpp)
add_library(InstructionSet_obj InstructionSet.cpp)
add_library(RAM_obj RAM.cpp)
add_library(Registers_obj Registers.cpp)
add_library(Stream_obj Stream.cpp)
add_library(Transform_obj Transform.cpp)
add_library(Validator_obj Validator.cpp)
add_library(VirtualMachine_obj VirtualMachine.cpp)
add_library(Debugger_obj Debugger.cpp)

add_executable(main main.cpp)
# debugger
target_link_libraries(main instruction_obj)
#
target_link_libraries(main Byte_obj)
target_link_libraries(main Word_obj)
target_link_libraries(main DWord_obj)
target_link_libraries(main QWord_obj)
target_link_libraries(main Float_obj)
target_link_libraries(main Types_obj)
#
target_link_libraries(main VirtualMachine_obj)
# virtualmachine
target_link_libraries(main Transform_obj)
target_link_libraries(main validatebytecode_obj)
#
target_link_libraries(main Validator_obj)
target_link_libraries(main Bytecode_obj)
target_link_libraries(main Debugger_obj)
target_link_libraries(main InstructionSet_obj)
target_link_libraries(main RAM_obj)
target_link_libraries(main Stream_obj)
target_link_libraries(main Registers_obj)
# instructionset
target_link_libraries(main bitwise_obj)
target_link_libraries(main dblmath_obj)
target_link_libraries(main fltmath_obj)
target_link_libraries(main intmath_obj)
target_link_libraries(main jump_obj)
target_link_libraries(main interrupt_obj)
target_link_libraries(main load_obj)
target_link_libraries(main move_obj)
target_link_libraries(main pushpop_obj)
target_link_libraries(main shift_obj)
target_link_libraries(main store_obj)

target_include_directories(main PUBLIC types)
