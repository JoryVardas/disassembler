target_sources(Disassembler PRIVATE 
        disassembler.cpp
        instruction.cpp
        instructionParameter.cpp
        registerParameter.cpp
        immediateParameter.cpp
        addressParameter.cpp
)

add_subdirectory(architecture/x86)