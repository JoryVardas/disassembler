#ifndef ADDRESSPARAMETER_H
#define ADDRESSPARAMETER_H

#include "registerParameter.h"
#include "common.h"

enum class AddressParameterType {
        REGISTER,
        VALUE,
        VALUE_REGISTER_SCALE
};

struct AddressParameter {
public:
        AddressParameter();
        AddressParameter(AddressParameter&);
        AddressParameter(AddressParameter&&);
        virtual ~AddressParameter();

        virtual std::string toString() const;

        AddressParameter& operator=(AddressParameter&);
        AddressParameter& operator=(AddressParameter&&);
private:
        RegisterParameter _addressRegister;
        int64_t _addressValue;
        int64_t _addressScale;
        AddressParameterType _addressType;
        PADDING(4);
};

#endif