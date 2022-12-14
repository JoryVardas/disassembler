#ifndef ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERLIST_H
#define ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERLIST_H

#include <map>
#include <string>

#include "x86InstructionRegisterParameter.h"

#define REGISTER(name, size)                                                   \
    {                                                                          \
#name, { #name, size }                                                 \
    }
#define REGISTER8(name) REGISTER(name, 8)
#define REGISTER16(name) REGISTER(name, 16)
#define REGISTER32(name) REGISTER(name, 32)
#define REGISTER64(name) REGISTER(name, 64)
#define REGISTER80(name) REGISTER(name, 80)
#define REGISTER128(name) REGISTER(name, 128)
#define REGISTER256(name) REGISTER(name, 256)
#define REGISTER512(name) REGISTER(name, 512)

const std::map<std::string, X86InstructionRegisterParameter>
    X86InstructionRegisterParameterList{
        REGISTER8(AL),         REGISTER8(AH),         REGISTER8(BL),
        REGISTER8(BH),         REGISTER8(CL),         REGISTER8(CH),
        REGISTER8(DL),         REGISTER8(DH),         REGISTER8(BPL),
        REGISTER8(SIL),        REGISTER8(R8B),        REGISTER8(R9B),
        REGISTER8(R10B),       REGISTER8(R11B),       REGISTER8(DIL),
        REGISTER8(SPL),        REGISTER8(R12B),       REGISTER8(R13B),
        REGISTER8(R14B),       REGISTER8(R15B),

        REGISTER16(AX),        REGISTER16(BX),        REGISTER16(CX),
        REGISTER16(DX),        REGISTER16(BP),        REGISTER16(SI),
        REGISTER16(R8W),       REGISTER16(R9W),       REGISTER16(R10W),
        REGISTER16(R11W),      REGISTER16(DI),        REGISTER16(SP),
        REGISTER16(R12W),      REGISTER16(R13W),      REGISTER16(R14W),
        REGISTER16(R15W),      REGISTER16(IP),        REGISTER16(MSW),
        REGISTER16(CW),        REGISTER16(FP_IP),     REGISTER16(FP_DP),
        REGISTER16(FP_CS),     REGISTER16(SW),        REGISTER16(TW),
        REGISTER16(FP_DS),     REGISTER16(FP_OPC),    REGISTER16(CS),
        REGISTER16(SS),        REGISTER16(DS),        REGISTER16(ES),
        REGISTER16(FS),        REGISTER16(GS),        REGISTER16(GDTR),
        REGISTER16(IDTR),      REGISTER16(TR),        REGISTER16(LDTR),
        REGISTER16(FLAGS),

        REGISTER32(EAX),       REGISTER32(EBX),       REGISTER32(ECX),
        REGISTER32(EDX),       REGISTER32(EBP),       REGISTER32(ESI),
        REGISTER32(R8D),       REGISTER32(R9D),       REGISTER32(R10D),
        REGISTER32(R11D),      REGISTER32(EDI),       REGISTER32(ESP),
        REGISTER32(R12D),      REGISTER32(R13D),      REGISTER32(R14D),
        REGISTER32(R15D),      REGISTER32(EIP),       REGISTER32(MXCSR),
        REGISTER32(FP_DP),     REGISTER32(FP_IP),     REGISTER32(EFLAGS),

        REGISTER64(RAX),       REGISTER64(RBX),       REGISTER64(RCX),
        REGISTER64(RDX),       REGISTER64(RBP),       REGISTER64(RSI),
        REGISTER64(R8),        REGISTER64(R9),        REGISTER64(R10),
        REGISTER64(R11),       REGISTER64(RDI),       REGISTER64(RSP),
        REGISTER64(R12),       REGISTER64(R13),       REGISTER64(R14),
        REGISTER64(R15),       REGISTER64(RIP),       REGISTER64(CR0),
        REGISTER64(CR1),       REGISTER64(CR2),       REGISTER64(CR3),
        REGISTER64(CR4),       REGISTER64(CR5),       REGISTER64(CR6),
        REGISTER64(CR7),       REGISTER64(CR8),       REGISTER64(CR9),
        REGISTER64(CR10),      REGISTER64(CR11),      REGISTER64(CR12),
        REGISTER64(CR13),      REGISTER64(CR14),      REGISTER64(CR15),
        REGISTER64(RFLAGS),    REGISTER64(DR0),       REGISTER64(DR1),
        REGISTER64(DR2),       REGISTER64(DR3),       REGISTER64(DR4),
        REGISTER64(DR5),       REGISTER64(DR6),       REGISTER64(DR7),
        REGISTER64(DR8),       REGISTER64(DR9),       REGISTER64(DR10),
        REGISTER64(DR11),      REGISTER64(DR12),      REGISTER64(DR13),
        REGISTER64(DR14),      REGISTER64(DR15),      REGISTER64(MM0),
        REGISTER64(MM1),       REGISTER64(MM2),       REGISTER64(MM3),
        REGISTER64(MM4),       REGISTER64(MM5),       REGISTER64(MM6),
        REGISTER64(MM7),

        REGISTER("ST(0)", 80), REGISTER("ST(1)", 80), REGISTER("ST(2)", 80),
        REGISTER("ST(3)", 80), REGISTER("ST(4)", 80), REGISTER("ST(5)", 80),
        REGISTER("ST(6)", 80), REGISTER("ST(7)", 80),

        REGISTER128(XMM0),     REGISTER128(XMM1),     REGISTER128(XMM2),
        REGISTER128(XMM3),     REGISTER128(XMM4),     REGISTER128(XMM5),
        REGISTER128(XMM6),     REGISTER128(XMM7),     REGISTER128(XMM8),
        REGISTER128(XMM9),     REGISTER128(XMM10),    REGISTER128(XMM11),
        REGISTER128(XMM12),    REGISTER128(XMM13),    REGISTER128(XMM14),
        REGISTER128(XMM15),

        REGISTER256(YMM0),     REGISTER256(YMM1),     REGISTER256(YMM2),
        REGISTER256(YMM3),     REGISTER256(YMM4),     REGISTER256(YMM5),
        REGISTER256(YMM6),     REGISTER256(YMM7),     REGISTER256(YMM8),
        REGISTER256(YMM9),     REGISTER256(YMM10),    REGISTER256(YMM11),
        REGISTER256(YMM12),    REGISTER256(YMM13),    REGISTER256(YMM14),
        REGISTER256(YMM15),

        REGISTER512(XMM0),     REGISTER512(XMM1),     REGISTER512(XMM2),
        REGISTER512(XMM3),     REGISTER512(XMM4),     REGISTER512(XMM5),
        REGISTER512(XMM6),     REGISTER512(XMM7),     REGISTER512(XMM8),
        REGISTER512(XMM9),     REGISTER512(XMM10),    REGISTER512(XMM11),
        REGISTER512(XMM12),    REGISTER512(XMM13),    REGISTER512(XMM14),
        REGISTER512(XMM15),    REGISTER512(XMM16),    REGISTER512(XMM17),
        REGISTER512(XMM18),    REGISTER512(XMM19),    REGISTER512(XMM20),
        REGISTER512(XMM21),    REGISTER512(XMM22),    REGISTER512(XMM23),
        REGISTER512(XMM24),    REGISTER512(XMM25),    REGISTER512(XMM26),
        REGISTER512(XMM27),    REGISTER512(XMM28),    REGISTER512(XMM29),
        REGISTER512(XMM30),    REGISTER512(XMM31)};

#undef REGISTER
#undef REGISTER8
#undef REGISTER16
#undef REGISTER32
#undef REGISTER64
#undef REGISTER80
#undef REGISTER128
#undef REGISTER256
#undef REGISTER512

#endif