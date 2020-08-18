#ifndef INSTRUCTIONPARAMETER_H
#define INSTRUCTIONPARAMETER_H

#include <string>

enum class InstructionParameterType {
        UNUSED = 0,
        REGISTER,
        IMMEDIATE,
        ADDRESS
};

enum class InstructionParameterDirection {
        IN = 1,
        OUT = 2,
        IN_OUT = 3
};

class InstructionParameter{
public:
        InstructionParameter();
        InstructionParameter(InstructionParameter&);
        InstructionParameter(InstructionParameter&&);
        virtual ~InstructionParameter();

        virtual std::string toString() const = 0;

        InstructionParameter& operator=(InstructionParameter&);
        InstructionParameter& operator=(InstructionParameter&&);
protected:
        InstructionParameterType _paramterType = InstructionParameterType::UNUSED;
        InstructionParameterDirection _parameterDirection = InstructionParameterDirection::IN_OUT;
};

#endif