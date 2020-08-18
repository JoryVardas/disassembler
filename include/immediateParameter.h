#ifndef IMMEDIATEPARAMETER_H
#define IMMEDIATEPARAMETER_H

#include "instructionParameter.h"

struct ImmediateParameter{
        ImmediateParameter();
        ImmediateParameter(ImmediateParameter&);
        ImmediateParameter(ImmediateParameter&&);
        virtual ~ImmediateParameter();

        virtual std::string toString() const;

        ImmediateParameter& operator=(ImmediateParameter&);
        ImmediateParameter& operator=(ImmediateParameter&&);
protected:
        int64_t _value;
};

#endif