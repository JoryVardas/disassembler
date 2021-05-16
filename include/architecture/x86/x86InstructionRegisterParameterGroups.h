#ifndef ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERGROUPS_H
#define ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERGROUPS_H

#include <vector>

#include "x86InstructionRegisterParameter.h"
#include "x86InstructionRegisterParameterList.h"

typedef std::vector<X86InstructionRegisterParameter>
    X86InstructionRegisterParameterGroup;

#define REGISTER(name) X86InstructionRegisterParameterList.at(#name)

const std::vector<X86InstructionRegisterParameterGroup>
    X86InstructionRegisterParameterGroups{
        {REGISTER(AL), REGISTER(AX), REGISTER(EAX), REGISTER(MM0),
         REGISTER(XMM0)},
        {REGISTER(CL), REGISTER(CX), REGISTER(ECX), REGISTER(MM1),
         REGISTER(XMM1)},
        {REGISTER(DL), REGISTER(DX), REGISTER(EDX), REGISTER(MM2),
         REGISTER(XMM2)},
        {REGISTER(BL), REGISTER(BX), REGISTER(EBX), REGISTER(MM3),
         REGISTER(XMM3)},
        {REGISTER(AH), REGISTER(SP), REGISTER(ESP), REGISTER(MM4),
         REGISTER(XMM4)},
        {REGISTER(CH), REGISTER(BP), REGISTER(EBP), REGISTER(MM5),
         REGISTER(XMM5)},
        {REGISTER(DH), REGISTER(SI), REGISTER(ESI), REGISTER(MM6),
         REGISTER(XMM6)},
        {REGISTER(BH), REGISTER(DI), REGISTER(EDI), REGISTER(MM7),
         REGISTER(XMM7)}};

const std::vector<X86InstructionRegisterParameter> X86SibScaledRegisterList{
    X86InstructionRegisterParameterList.at("EAX"),
    X86InstructionRegisterParameterList.at("ECX"),
    X86InstructionRegisterParameterList.at("EDX"),
    X86InstructionRegisterParameterList.at("EBX"),
    X86InstructionRegisterParameter(),
    X86InstructionRegisterParameterList.at("EBP"),
    X86InstructionRegisterParameterList.at("ESI"),
    X86InstructionRegisterParameterList.at("EDI"),
};
const std::vector<X86InstructionRegisterParameter>
    X86SibDisplacementRegisterList{
        X86InstructionRegisterParameterList.at("EAX"),
        X86InstructionRegisterParameterList.at("ECX"),
        X86InstructionRegisterParameterList.at("EDX"),
        X86InstructionRegisterParameterList.at("EBX"),
        X86InstructionRegisterParameterList.at("ESP"),
        X86InstructionRegisterParameterList.at("EBP"),
        X86InstructionRegisterParameterList.at("ESI"),
        X86InstructionRegisterParameterList.at("EDI"),
    };

const std::vector<X86InstructionRegisterParameterGroup>
    X86ModrmAddressBaseRegisterList{
        {
            REGISTER(BX),
            REGISTER(EAX),
        },
        {
            REGISTER(BX),
            REGISTER(ECX),
        },
        {
            REGISTER(BP),
            REGISTER(EDX),
        },
        {
            REGISTER(BP),
            REGISTER(EBX),
        },
        {
            REGISTER(SI),
            {},
        },
        {
            REGISTER(DI),
            REGISTER(EBP),
        },
        {
            REGISTER(BP),
            REGISTER(ESI),
        },
        {
            REGISTER(BX),
            REGISTER(EDI),
        },
    };

const std::vector<X86InstructionRegisterParameterGroup>
    X86SibAddressBaseRegisterList{
        {
            REGISTER(EAX),
        },
        {
            REGISTER(ECX),
        },
        {
            REGISTER(EDX),
        },
        {
            REGISTER(EBX),
        },
        {
            {},
        },
        {
            REGISTER(EBP),
        },
        {
            REGISTER(ESI),
        },
        {
            REGISTER(EDI),
        },
    };

#undef REGISTER

#endif