#ifndef INSTRUCTIONPARAMETER_H
#define INSTRUCTIONPARAMETER_H

#include <string>
#include <variant>

enum class InstructionParameterType { REGISTER, IMMEDIATE, ADDRESS };

enum class InstructionParameterDirection { IN = 1, OUT, IN_OUT };

class InstructionParameter {
  public:
    InstructionParameter();
    InstructionParameter(const InstructionParameterType type,
                         const InstructionParameterDirection direction =
                             InstructionParameterDirection::IN);
    InstructionParameter(const InstructionParameter&);
    InstructionParameter(InstructionParameter&&);
    virtual ~InstructionParameter();

    virtual std::string toString() const = 0;
    virtual InstructionParameterType getType() const;
    virtual InstructionParameterDirection getDirection() const;

    InstructionParameter& operator=(const InstructionParameter&);
    InstructionParameter& operator=(InstructionParameter&&);

  protected:
    InstructionParameterType _parameterType =
        InstructionParameterType::IMMEDIATE;
    InstructionParameterDirection _parameterDirection =
        InstructionParameterDirection::IN;
};

#endif