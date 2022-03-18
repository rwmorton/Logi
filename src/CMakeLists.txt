add_compile_options(-std=c++2a)

# add_subdirectory(xyz)

add_executable(main main.cpp)

add_library(Bytecode_obj Bytecode.cpp)
add_library(InstructionSet_obj InstructionSet.cpp)
add_library(RAM_obj RAM.cpp)
add_library(Registers_obj Registers.cpp)
add_library(Stream_obj Stream.cpp)
add_library(Transform_obj Transform.cpp)
add_library(VirtualMachine_obj VirtualMachine.cpp)

target_link_libraries(main VirtualMachine_obj)
target_link_libraries(main Bytecode_obj)
target_link_libraries(main InstructionSet_obj)
target_link_libraries(main RAM_obj)
target_link_libraries(main Stream_obj)
target_link_libraries(main Registers_obj)
target_link_libraries(main Transform_obj)

# target_include_directories(main PUBLIC xyz)
