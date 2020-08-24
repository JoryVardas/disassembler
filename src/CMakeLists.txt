target_sources(Disassembler PRIVATE 
        disassembler.cpp
        instruction.cpp
        instructionParameter.cpp
)

add_subdirectory(architecture/x86)