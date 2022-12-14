#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <cstddef>
#include <memory>
#include <vector>

#include "bidirectionalIterator.h"
#include "instruction.h"

class Disassembler {
  public:
    Disassembler();
    Disassembler(Disassembler&);
    Disassembler(Disassembler&&);
    virtual ~Disassembler();

    virtual std::unique_ptr<Instruction> decodeInstruction(
        BidirectionalIterator<std::byte>& bytesToDecode) const = 0;

    void operator=(Disassembler&) = delete;
    void operator=(Disassembler&&) = delete;

  protected:
};

#endif