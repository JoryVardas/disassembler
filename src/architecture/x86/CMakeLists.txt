target_sources(Disassembler PRIVATE 
        x86Disassembler.cpp
        x86Instruction.cpp
        x86InstructionPrefix.cpp
        x86InstructionPrototype.cpp
        x86InstructionPrototypeList.cpp
        x86InstructionImmediateParameter.cpp
        x86InstructionRegisterParameter.cpp
        x86InstructionAddressParameter.cpp
        x86InstructionRegisterParameterGroups.cpp
        x86InstructionRegisterParameterPrototype.cpp
        X86InstructionImmediateParameterPrototype.cpp
        X86InstructionRegisterParameterList.cpp
        x86InstructionAddressParameterPrototype.cpp
        x86Modrm.cpp
)