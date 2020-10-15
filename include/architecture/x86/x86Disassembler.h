#ifndef ARCHITECTURE_X86_X86DISASSEMBLER_H
#define ARCHITECTURE_X86_X86DISASSEMBLER_H

#include <memory>

#include <disassembler.h>
#include "x86InstructionPrefix.h"
#include "x86InstructionPrototype.h"
#include "x86Environment.h"

#include <common.h>

class X86Disassembler : public Disassembler {
public:


        X86Disassembler() = delete;
        X86Disassembler(X86Environment& disassemblerEnvironment);
        X86Disassembler(X86Disassembler&);
        X86Disassembler(X86Disassembler&&);
        ~X86Disassembler();
        
        std::unique_ptr<Instruction> decodeInstruction(BidirectionalIterator<std::byte>& bytesToDecode) const override;

        void operator=(X86Disassembler&) = delete;
        void operator=(X86Disassembler&&) = delete;

private:
        X86Environment _disassemblerEnvirionment;

        std::vector<X86InstructionPrefix> decodeInstructionPrefixes(BidirectionalIterator<std::byte>& bytesToDecode) const;
        X86InstructionOpcode retrieveInstructionOpcode(BidirectionalIterator<std::byte>& bytesToDecode) const;
        X86InstructionPrototype decodeInstructionPrototype(const std::vector<X86InstructionPrefix>& prefixList, const X86InstructionOpcode opcode, BidirectionalIterator<std::byte>& bytesToDecode) const;
        std::vector<std::shared_ptr<InstructionParameter>> decodeInstructionParameters(const X86InstructionPrototype& instructionPrototype, const std::vector<X86InstructionPrefix>& prefixList, BidirectionalIterator<std::byte>& bytesToDecode) const;
};

#endif