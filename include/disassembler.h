#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <cstddef>
#include <vector>
#include <memory>

#include "Instruction.h"
#include "bidirectionalIterator.h"


class Disassembler{
public:
        Disassembler();
        Disassembler(Disassembler&);
        Disassembler(Disassembler&&);
        virtual ~Disassembler();

        virtual std::unique_ptr<Instruction> decodeInstruction(BidirectionalIterator<std::byte>& bytesToDecode) const = 0;

        void operator=(Disassembler&) = delete;
        void operator=(Disassembler&&) = delete;
protected:
};

#endif