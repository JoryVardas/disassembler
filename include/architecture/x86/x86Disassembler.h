#ifndef ARCHITECTURE_X86_X86DISASSEMBLER_H
#define ARCHITECTURE_X86_X86DISASSEMBLER_H

#include <disassembler.h>
#include "x86InstructionPrefix.h"
#include "x86InstructionPrototype.h"

class X86Disassembler : public Disassembler {
public:
        X86Disassembler();
        X86Disassembler(X86Disassembler&);
        X86Disassembler(X86Disassembler&&);
        ~X86Disassembler();
        
        std::unique_ptr<Instruction> decodeInstruction(BidirectionalIterator<std::byte>& bytesToDecode) const override;

        void operator=(X86Disassembler&) = delete;
        void operator=(X86Disassembler&&) = delete;
private:
        std::vector<X86InstructionPrefix> decodeInstructionPrefixes(BidirectionalIterator<std::byte>& bytesToDecode) const;
        X86InstructionOpcode retrieveInstructionOpcode(BidirectionalIterator<std::byte>& bytesToDecode) const;
        X86InstructionPrototype decodeInstructionPrototype(const std::vector<X86InstructionPrefix>& prefixList, const X86InstructionOpcode opcode, BidirectionalIterator<std::byte>& bytesToDecode) const;
};

#endif