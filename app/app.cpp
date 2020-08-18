#include <vector>
#include <iostream>

#include <algorithm>

#include <bidirectionalIterator.h>

#include <architecture/x86/x86Disassembler.h>
#include <architecture/x86/x86Instruction.h>

int main(/*int argc, char* argv[]*/){

        std::vector<std::byte> test = {std::byte(X86InstructionPrefix::LOCK), std::byte(0)};

        BidirectionalIterator<std::byte> start ( test.begin()._Ptr, 2 );

        X86Disassembler disasm;
        std::unique_ptr<Instruction> instruction = disasm.decodeInstruction(start);
        std::cout << instruction->toString();
        
        return 0;
}