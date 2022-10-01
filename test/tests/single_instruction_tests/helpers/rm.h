#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_RM_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_RM_HELPERS_H

#include <optional>
#include <variant>
#include <vector>

#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <fmt/format.h>

#include "imm.hpp"
#include "prefix.h"

namespace Testing::Helpers {
struct RegisterParameter {
    std::string name;
    uint8_t size;
    std::byte mod_r;

    RegisterParameter(std::string n, uint8_t s, std::byte r)
        : name(n), size(s), mod_r(r){};

    bool operator==(const RegisterParameter&) const = default;
};
} // namespace Testing::Helpers

#define REGISTER(name, size, mod_r)                                            \
    RegisterParameter {                                                        \
#name, size, std::byte { mod_r }                                       \
    }
#define REGISTER8(name, mod_r) REGISTER(name, 8, mod_r)
#define REGISTER16(name, mod_r) REGISTER(name, 16, mod_r)
#define REGISTER32(name, mod_r) REGISTER(name, 32, mod_r)
#define REGISTER64(name, mod_r) REGISTER(name, 64, mod_r)
#define REGISTER80(name, mod_r)                                                \
    register_parameter_t { name, 80, mod_r }
#define REGISTER128(name, mod_r) REGISTER(name, 128, mod_r)
#define REGISTER256(name, mod_r) REGISTER(name, 256, mod_r)
#define REGISTER512(name, mod_r) REGISTER(name, 512, mod_r)

#define AL_REGISTER REGISTER8(AL, 0)
#define AH_REGISTER REGISTER8(AH, 4)
#define BL_REGISTER REGISTER8(BL, 3)
#define BH_REGISTER REGISTER8(BH, 7)
#define CL_REGISTER REGISTER8(CL, 1)
#define CH_REGISTER REGISTER8(CH, 5)
#define DL_REGISTER REGISTER8(DL, 2)
#define DH_REGISTER REGISTER8(DH, 6)
#define BPL_REGISTER REGISTER8(BPL, 255)
#define SIL_REGISTER REGISTER8(SIL, 255)
#define R8B_REGISTER REGISTER8(R8B, 0)
#define R9B_REGISTER REGISTER8(R9B, 1)
#define R10B_REGISTER REGISTER8(R10B, 2)
#define R11B_REGISTER REGISTER8(R11B, 3)
#define DIL_REGISTER REGISTER8(DIL, 255)
#define SPL_REGISTER REGISTER8(SPL, 255)
#define R12B_REGISTER REGISTER8(R12B, 4)
#define R13B_REGISTER REGISTER8(R13B, 5)
#define R14B_REGISTER REGISTER8(R14B, 6)
#define R15B_REGISTER REGISTER8(R15B, 7)

#define AX_REGISTER REGISTER16(AX, 0)
#define BX_REGISTER REGISTER16(BX, 3)
#define CX_REGISTER REGISTER16(CX, 1)
#define DX_REGISTER REGISTER16(DX, 2)
#define BP_REGISTER REGISTER16(BP, 5)
#define SI_REGISTER REGISTER16(SI, 6)
#define R8W_REGISTER REGISTER16(R8W, 0)
#define R9W_REGISTER REGISTER16(R9W, 1)
#define R10W_REGISTER REGISTER16(R10W, 2)
#define R11W_REGISTER REGISTER16(R11W, 3)
#define DI_REGISTER REGISTER16(DI, 7)
#define SP_REGISTER REGISTER16(SP, 4)
#define R12W_REGISTER REGISTER16(R12W, 4)
#define R13W_REGISTER REGISTER16(R13W, 5)
#define R14W_REGISTER REGISTER16(R14W, 6)
#define R15W_REGISTER REGISTER16(R15W, 7)
#define IP_REGISTER REGISTER16(IP, 255)
#define MSW_REGISTER REGISTER16(MSW, 255)
#define CW_REGISTER REGISTER16(CW, 255)
#define FP_IP_REGISTER REGISTER16(FP_IP, 255)
#define FP_DP_16_REGISTER REGISTER16(FP_DP, 255)
#define FP_CS_16_REGISTER REGISTER16(FP_CS, 255)
#define SW_REGISTER REGISTER16(SW, 255)
#define TW_REGISTER REGISTER16(TW, 255)
#define FP_DS_REGISTER REGISTER16(FP_DS, 255)
#define FP_OPC_REGISTER REGISTER16(FP_OPC, 255)
#define CS_REGISTER REGISTER16(CS, 255)
#define SS_REGISTER REGISTER16(SS, 255)
#define DS_REGISTER REGISTER16(DS, 255)
#define ES_REGISTER REGISTER16(ES, 255)
#define FS_REGISTER REGISTER16(FS, 255)
#define GS_REGISTER REGISTER16(GS, 255)
#define GDTR_REGISTER REGISTER16(GDTR, 255)
#define IDTR_REGISTER REGISTER16(IDTR, 255)
#define TR_REGISTER REGISTER16(TR, 255)
#define LDTR_REGISTER REGISTER16(LDTR, 255)
#define FLAGS_REGISTER REGISTER16(FLAGS, 255)

#define EAX_REGISTER REGISTER32(EAX, 0)
#define EBX_REGISTER REGISTER32(EBX, 3)
#define ECX_REGISTER REGISTER32(ECX, 1)
#define EDX_REGISTER REGISTER32(EDX, 2)
#define EBP_REGISTER REGISTER32(EBP, 5)
#define ESI_REGISTER REGISTER32(ESI, 6)
#define R8D_REGISTER REGISTER32(R8D, 0)
#define R9D_REGISTER REGISTER32(R9D, 1)
#define R10D_REGISTER REGISTER32(R10D, 2)
#define R11D_REGISTER REGISTER32(R11D, 3)
#define EDI_REGISTER REGISTER32(EDI, 7)
#define ESP_REGISTER REGISTER32(ESP, 4)
#define R12D_REGISTER REGISTER32(R12D, 4)
#define R13D_REGISTER REGISTER32(R13D, 5)
#define R14D_REGISTER REGISTER32(R14D, 6)
#define R15D_REGISTER REGISTER32(R15D, 7)
#define EIP_REGISTER REGISTER32(EIP, 255)
#define MXCSR_REGISTER REGISTER32(MXCSR, 255)
#define FP_DP_32_REGISTER REGISTER32(FP_DP, 255)
#define FP_IP_32_REGISTER REGISTER32(FP_IP, 255)
#define EFLAGS_REGISTER REGISTER32(EFLAGS, 255)

#define RAX_REGISTER REGISTER64(RAX, 0)
#define RBX_REGISTER REGISTER64(RBX, 3)
#define RCX_REGISTER REGISTER64(RCX, 1)
#define RDX_REGISTER REGISTER64(RDX, 2)
#define RBP_REGISTER REGISTER64(RBP, 5)
#define RSI_REGISTER REGISTER64(RSI, 6)
#define R8_REGISTER REGISTER64(R8, 0)
#define R9_REGISTER REGISTER64(R9, 1)
#define R10_REGISTER REGISTER64(R10, 2)
#define R11_REGISTER REGISTER64(R11, 3)
#define RDI_REGISTER REGISTER64(RDI, 7)
#define RSP_REGISTER REGISTER64(RSP, 4)
#define R12_REGISTER REGISTER64(R12, 4)
#define R13_REGISTER REGISTER64(R13, 5)
#define R14_REGISTER REGISTER64(R14, 6)
#define R15_REGISTER REGISTER64(R15, 7)
#define RIP_REGISTER REGISTER64(RIP, 255)
#define CR0_REGISTER REGISTER64(CR0, 255)
#define CR1_REGISTER REGISTER64(CR1, 255)
#define CR2_REGISTER REGISTER64(CR2, 255)
#define CR3_REGISTER REGISTER64(CR3, 255)
#define CR4_REGISTER REGISTER64(CR4, 255)
#define CR5_REGISTER REGISTER64(CR5, 255)
#define CR6_REGISTER REGISTER64(CR6, 255)
#define CR7_REGISTER REGISTER64(CR7, 255)
#define CR8_REGISTER REGISTER64(CR8, 255)
#define CR9_REGISTER REGISTER64(CR9, 255)
#define CR10_REGISTER REGISTER64(CR10, 255)
#define CR11_REGISTER REGISTER64(CR11, 255)
#define CR12_REGISTER REGISTER64(CR12, 255)
#define CR13_REGISTER REGISTER64(CR13, 255)
#define CR14_REGISTER REGISTER64(CR14, 255)
#define CR15_REGISTER REGISTER64(CR15, 255)
#define RFLAGS_REGISTER REGISTER64(RFLAGS, 255)
#define DR0_REGISTER REGISTER64(DR0, 255)
#define DR1_REGISTER REGISTER64(DR1, 255)
#define DR2_REGISTER REGISTER64(DR2, 255)
#define DR3_REGISTER REGISTER64(DR3, 255)
#define DR4_REGISTER REGISTER64(DR4, 255)
#define DR5_REGISTER REGISTER64(DR5, 255)
#define DR6_REGISTER REGISTER64(DR6, 255)
#define DR7_REGISTER REGISTER64(DR7, 255)
#define DR8_REGISTER REGISTER64(DR8, 255)
#define DR9_REGISTER REGISTER64(DR9, 255)
#define DR10_REGISTER REGISTER64(DR10, 255)
#define DR11_REGISTER REGISTER64(DR11, 255)
#define DR12_REGISTER REGISTER64(DR12, 255)
#define DR13_REGISTER REGISTER64(DR13, 255)
#define DR14_REGISTER REGISTER64(DR14, 255)
#define DR15_REGISTER REGISTER64(DR15, 255)
#define MM0_REGISTER REGISTER64(MM0, 0)
#define MM1_REGISTER REGISTER64(MM1, 1)
#define MM2_REGISTER REGISTER64(MM2, 2)
#define MM3_REGISTER REGISTER64(MM3, 3)
#define MM4_REGISTER REGISTER64(MM4, 4)
#define MM5_REGISTER REGISTER64(MM5, 5)
#define MM6_REGISTER REGISTER64(MM6, 6)
#define MM7_REGISTER REGISTER64(MM7, 7)

#define ST0_REGISTER REGISTER80("ST(0)", 255)
#define ST1_REGISTER REGISTER80("ST(1)", 255)
#define ST2_REGISTER REGISTER80("ST(2)", 255)
#define ST3_REGISTER REGISTER80("ST(3)", 255)
#define ST4_REGISTER REGISTER80("ST(4)", 255)
#define ST5_REGISTER REGISTER80("ST(5)", 255)
#define ST6_REGISTER REGISTER80("ST(6)", 255)
#define ST7_REGISTER REGISTER80("ST(7)", 255)

#define XMM0_REGISTER REGISTER128(XMM0, 0)
#define XMM1_REGISTER REGISTER128(XMM1, 1)
#define XMM2_REGISTER REGISTER128(XMM2, 2)
#define XMM3_REGISTER REGISTER128(XMM3, 3)
#define XMM4_REGISTER REGISTER128(XMM4, 4)
#define XMM5_REGISTER REGISTER128(XMM5, 5)
#define XMM6_REGISTER REGISTER128(XMM6, 6)
#define XMM7_REGISTER REGISTER128(XMM7, 7)
#define XMM8_REGISTER REGISTER128(XMM8, 0)
#define XMM9_REGISTER REGISTER128(XMM9, 1)
#define XMM10_REGISTER REGISTER128(XMM10, 2)
#define XMM11_REGISTER REGISTER128(XMM11, 3)
#define XMM12_REGISTER REGISTER128(XMM12, 4)
#define XMM13_REGISTER REGISTER128(XMM13, 5)
#define XMM14_REGISTER REGISTER128(XMM14, 6)
#define XMM15_REGISTER REGISTER128(XMM15, 7)

#define YMM0_REGISTER REGISTER256(YMM0, 0)
#define YMM1_REGISTER REGISTER256(YMM1, 1)
#define YMM2_REGISTER REGISTER256(YMM2, 2)
#define YMM3_REGISTER REGISTER256(YMM3, 3)
#define YMM4_REGISTER REGISTER256(YMM4, 4)
#define YMM5_REGISTER REGISTER256(YMM5, 5)
#define YMM6_REGISTER REGISTER256(YMM6, 6)
#define YMM7_REGISTER REGISTER256(YMM7, 7)
#define YMM8_REGISTER REGISTER256(YMM8, 0)
#define YMM9_REGISTER REGISTER256(YMM9, 1)
#define YMM10_REGISTER REGISTER256(YMM10, 2)
#define YMM11_REGISTER REGISTER256(YMM11, 3)
#define YMM12_REGISTER REGISTER256(YMM12, 4)
#define YMM13_REGISTER REGISTER256(YMM13, 5)
#define YMM14_REGISTER REGISTER256(YMM14, 6)
#define YMM15_REGISTER REGISTER256(YMM15, 7)

#define ZMM0_REGISTER REGISTER512(ZMM0, 0)
#define ZMM1_REGISTER REGISTER512(ZMM1, 1)
#define ZMM2_REGISTER REGISTER512(ZMM2, 2)
#define ZMM3_REGISTER REGISTER512(ZMM3, 3)
#define ZMM4_REGISTER REGISTER512(ZMM4, 4)
#define ZMM5_REGISTER REGISTER512(ZMM5, 5)
#define ZMM6_REGISTER REGISTER512(ZMM6, 6)
#define ZMM7_REGISTER REGISTER512(ZMM7, 7)
#define ZMM8_REGISTER REGISTER512(ZMM8, 0)
#define ZMM9_REGISTER REGISTER512(ZMM9, 1)
#define ZMM10_REGISTER REGISTER512(ZMM10, 2)
#define ZMM11_REGISTER REGISTER512(ZMM11, 3)
#define ZMM12_REGISTER REGISTER512(ZMM12, 4)
#define ZMM13_REGISTER REGISTER512(ZMM13, 5)
#define ZMM14_REGISTER REGISTER512(ZMM14, 6)
#define ZMM15_REGISTER REGISTER512(ZMM15, 7)
#define ZMM16_REGISTER REGISTER512(ZMM16, 0)
#define ZMM17_REGISTER REGISTER512(ZMM17, 1)
#define ZMM18_REGISTER REGISTER512(ZMM18, 2)
#define ZMM19_REGISTER REGISTER512(ZMM19, 3)
#define ZMM20_REGISTER REGISTER512(ZMM20, 4)
#define ZMM21_REGISTER REGISTER512(ZMM21, 5)
#define ZMM22_REGISTER REGISTER512(ZMM22, 6)
#define ZMM23_REGISTER REGISTER512(ZMM23, 7)
#define ZMM24_REGISTER REGISTER512(ZMM24, 0)
#define ZMM25_REGISTER REGISTER512(ZMM25, 1)
#define ZMM26_REGISTER REGISTER512(ZMM26, 2)
#define ZMM27_REGISTER REGISTER512(ZMM27, 3)
#define ZMM28_REGISTER REGISTER512(ZMM28, 4)
#define ZMM29_REGISTER REGISTER512(ZMM29, 5)
#define ZMM30_REGISTER REGISTER512(ZMM30, 6)
#define ZMM31_REGISTER REGISTER512(ZMM31, 7)

#define MODRM_NO_SEG std::nullopt
#define MODRM_NO_DISP std::nullopt

#define INTERNAL_MODRM16(str, mod, rm, ptr, segment, disp)                     \
    address_t { str, std::byte{mod}, std::byte{rm}, ptr, segment, disp }
#define MODRM16_RM_0_0(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + SI]", std::byte{0}, std::byte{0x00}, ptr,     \
                     seg, MODRM_NO_DISP)
#define MODRM16_RM_0_1(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + DI]", std::byte{0}, std::byte{0x01}, ptr,     \
                     seg, MODRM_NO_DISP)
#define MODRM16_RM_0_2(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + SI]", std::byte{0}, std::byte{0x02}, ptr,     \
                     seg, MODRM_NO_DISP)
#define MODRM16_RM_0_3(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + DI]", std::byte{0}, std::byte{0x03}, ptr,     \
                     seg, MODRM_NO_DISP)
#define MODRM16_RM_0_4(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[SI]", std::byte{0}, std::byte{0x04}, ptr, seg,     \
                     MODRM_NO_DISP)
#define MODRM16_RM_0_5(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[DI]", std::byte{0}, std::byte{0x05}, ptr, seg,     \
                     MODRM_NO_DISP)
#define MODRM16_RM_0_6(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[{:#x}]", std::byte{0}, std::byte{0x06}, ptr, seg,  \
                                                                               \
                     disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_0_7(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX]", std::byte{0}, std::byte{0x07}, ptr, seg,     \
                     MODRM_NO_DISP)

#define MODRM16_RM_1_0(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + SI + {:#x}]", std::byte{0x40},                \
                     std::byte{0x00}, ptr, seg, disp_t{GET_IMM8(dispset)})
#define MODRM16_RM_1_1(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + DI + {:#x}]", std::byte{0x40},                \
                     std::byte{0x01}, ptr, seg, disp_t{GET_IMM8(dispset)})
#define MODRM16_RM_1_2(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + SI + {:#x}]", std::byte{0x40},                \
                     std::byte{0x02}, ptr, seg, disp_t{GET_IMM8(dispset)})
#define MODRM16_RM_1_3(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + DI + {:#x}]", std::byte{0x40},                \
                     std::byte{0x03}, ptr, seg, disp_t{GET_IMM8(dispset)})
#define MODRM16_RM_1_4(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[SI + {:#x}]", std::byte{0x40}, std::byte{0x04},    \
                     ptr, seg, disp_t{GET_IMM8(dispset)})
#define MODRM16_RM_1_5(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[DI + {:#x}]", std::byte{0x40}, std::byte{0x05},    \
                     ptr, seg, disp_t{GET_IMM8(dispset)})
#define MODRM16_RM_1_6(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + {:#x}]", std::byte{0x40}, std::byte{0x06},    \
                     ptr, seg, disp_t{GET_IMM8(dispset)})
#define MODRM16_RM_1_7(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + {:#x}]", std::byte{0x40}, std::byte{0x07},    \
                     ptr, seg, disp_t{GET_IMM8(dispset)})

#define MODRM16_RM_2_0(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + SI + {:#x}]", std::byte{0x80},                \
                     std::byte{0x00}, ptr, seg, disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_2_1(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + DI + {:#x}]", std::byte{0x80},                \
                     std::byte{0x01}, ptr, seg, disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_2_2(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + SI + {:#x}]", std::byte{0x80},                \
                     std::byte{0x02}, ptr, seg, disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_2_3(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + DI + {:#x}]", std::byte{0x80},                \
                     std::byte{0x03}, ptr, seg, disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_2_4(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[SI + {:#x}]", std::byte{0x80}, std::byte{0x04},    \
                     ptr, seg, disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_2_5(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[DI + {:#x}]", std::byte{0x80}, std::byte{0x05},    \
                     ptr, seg, disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_2_6(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BP + {:#x}]", std::byte{0x80}, std::byte{0x06},    \
                     ptr, seg, disp_t{GET_IMM16(dispset)})
#define MODRM16_RM_2_7(ptr, seg, dispset)                                      \
    INTERNAL_MODRM16("{} {}[BX + {:#x}]", std::byte{0x80}, std::byte{0x07},    \
                     ptr, seg, disp_t{GET_IMM16(dispset)})

#define BYTE_PTR "BYTE"
#define WORD_PTR "WORD"
#define DWORD_PTR "DWORD"
#define QWORD_PTR "QWORD"

// dispset, ptr, seg_offset

#define INTERNAL_MODRM16_WRAPPER(macro_to_call)                                \
    std::function<address_t(std::string, std::optional<prefix_t>, disp_set)> { \
                                                                               \
        [](std::string ptr, std::optional<prefix_t> seg, disp_set dispset) {   \
            return macro_to_call(ptr, seg, dispset);                           \
        }                                                                      \
    }

#define ALL_MODRM16_RM                                                         \
    concatinate(INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_0),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_1),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_2),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_3),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_4),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_5),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_6),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_0_7),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_0),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_1),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_2),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_3),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_4),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_5),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_6),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_1_7),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_0),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_1),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_2),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_3),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_4),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_5),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_6),                      \
                INTERNAL_MODRM16_WRAPPER(MODRM16_RM_2_7))

#define GENERATE_MODRM16_RM(ptr, dispset, /*optional seg*/...)                 \
    GENERATE(ALL_MODRM16_RM) \ (ptr, ON_EMPTY(std::nullopt, __VA_ARGS__,\
    __VA_ARGS__), dispset)

#define FIXED_R(val) REGISTER("", 0, std::byte{val})
#define MODRM(disassembler, rm, r)                                             \
    modrm(rm, r, DISASSEMBLER_ENDIANNESS_NATIVE(disassembler))

#endif