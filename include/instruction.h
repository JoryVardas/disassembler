#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include <memory>

#include "instructionParameter.h"

class Instruction {
public:
        Instruction();
        Instruction(Instruction&);
        Instruction(Instruction&&);

        Instruction(const std::string& name);

        virtual ~Instruction();

        virtual std::string toString() const = 0;

        void operator=(Instruction&) = delete;
        void operator=(Instruction&&) = delete;
protected:
        std::vector<std::shared_ptr<InstructionParameter>> _parameters;
        std::string _name;
};

#endif