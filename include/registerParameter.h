#ifndef REGISTERPARAMETER_H
#define REGISTERPARAMETER_H

#include <string>

#include "instructionParameter.h"
#include "common.h"

struct RegisterParameter : public InstructionParameter {
public:
        RegisterParameter();
        RegisterParameter(RegisterParameter&);
        RegisterParameter(RegisterParameter&&);
        virtual ~RegisterParameter();

        virtual std::string toString() const;

        RegisterParameter& operator=(RegisterParameter&);
        RegisterParameter& operator=(RegisterParameter&&);
protected:
        std::string _name;
        int _size;
        PADDING(4);
};

#endif