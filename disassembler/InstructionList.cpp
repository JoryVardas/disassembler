#include "Instructions.h"

#define INSTRUCTION(name, op) {name, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, op, INSTRUCTION_ENVIRONMENT_NO_ENVIRONMENT}
#define INSTRUCTION_P(name, prefix, op) {name, prefix, op, INSTRUCTION_ENVIRONMENT_NO_ENVIRONMENT}
#define INSTRUCTION_PE(name, prefix, op, env) {name, prefix, op, env}
#define INSTRUCTION_E(name, op, env) {name, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, op, env}

InstructionInfo instructionList[] = {
//UNKNOWN INSTRUCTION
INSTRUCTION(UNKNOWN_STR, 0x0),

//AAA
INSTRUCTION(AAA_STR, 0x37),

//AAD
INSTRUCTION(AAD_STR, 0xD5),

//AAM
INSTRUCTION(AAM_STR, 0xD4),

//AAS
INSTRUCTION(AAS_STR, 0x3F),

//ADC
INSTRUCTION(ADC_STR, 0x14),
INSTRUCTION(ADC_STR, 0x15),
INSTRUCTION_E(ADC_STR, 0x80, INSTRUCTION_ENVIRONMENT_MODRM_REG_2),
INSTRUCTION_E(ADC_STR, 0x81, INSTRUCTION_ENVIRONMENT_MODRM_REG_2),
INSTRUCTION_E(ADC_STR, 0x83, INSTRUCTION_ENVIRONMENT_MODRM_REG_2),
INSTRUCTION(ADC_STR, 0x10),
INSTRUCTION(ADC_STR, 0x11),
INSTRUCTION(ADC_STR, 0x12),
INSTRUCTION(ADC_STR, 0x13),

//ADCX
INSTRUCTION_PE(ADCX_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F38F6, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),

//ADD
INSTRUCTION(ADD_STR, 0x04),
INSTRUCTION(ADD_STR, 0x05),
INSTRUCTION_E(ADD_STR, 0x80, INSTRUCTION_ENVIRONMENT_MODRM_REG_0),
INSTRUCTION_E(ADD_STR, 0x81, INSTRUCTION_ENVIRONMENT_MODRM_REG_0),
INSTRUCTION_E(ADD_STR, 0x83, INSTRUCTION_ENVIRONMENT_MODRM_REG_0),
INSTRUCTION(ADD_STR, 0x00),
INSTRUCTION(ADD_STR, 0x01),
INSTRUCTION(ADD_STR, 0x02),
INSTRUCTION(ADD_STR, 0x03),

//ADDPD
INSTRUCTION_PE(ADDPD_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F58, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VADDPD_STR, PREFIX_CONTEXT_VEX_66_0F, 0x58),
INSTRUCTION_P(VADDPD_STR, PREFIX_CONTEXT_EVEX_66_0F_W1, 0x58),

//ADDPS
INSTRUCTION_P(ADDPS_STR, PREFIX_CONTEXT_NO_PREFIX, 0x0F58),
INSTRUCTION_P(VADDPS_STR, PREFIX_CONTEXT_VEX_0F, 0x58),
INSTRUCTION_P(VADDPS_STR, PREFIX_CONTEXT_EVEX_0F_W0, 0x58),

//ADDSD
INSTRUCTION_P(ADDSD_STR, PREFIX_CONTEXT_PREFIX_F2, 0x0F58),
INSTRUCTION_P(VADDSD_STR, PREFIX_CONTEXT_VEX_F2_0F, 0x58),
INSTRUCTION_P(VADDSD_STR, PREFIX_CONTEXT_EVEX_F2_0F_W1, 0x58),

//ADDSS
INSTRUCTION_P(ADDSS_STR, PREFIX_CONTEXT_PREFIX_F3, 0x0F58),
INSTRUCTION_P(VADDSS_STR, PREFIX_CONTEXT_VEX_F3_0F, 0x58),
INSTRUCTION_P(VADDSS_STR, PREFIX_CONTEXT_EVEX_F3_0F_W0, 0x58),

//ADDSUBPD
INSTRUCTION_PE(ADDSUBPD_STR, PREFIX_CONTEXT_PREFIX_66, 0x0FD0, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VADDSUBPD_STR, PREFIX_CONTEXT_VEX_66_0F, 0xD0),

//ADDSUBPS
INSTRUCTION_P(ADDSUBPS_STR, PREFIX_CONTEXT_PREFIX_F2, 0x0FD0),
INSTRUCTION_P(VADDSUBPS_STR, PREFIX_CONTEXT_VEX_F2_0F, 0xD0),

//ADOX
INSTRUCTION_P(ADOX_STR, PREFIX_CONTEXT_PREFIX_F3, 0x0F38F6),

//AESDEC
INSTRUCTION_PE(AESDEC_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F38DE, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VAESDEC_STR, PREFIX_CONTEXT_VEX_66_0F38, 0xDE),

//AESDECLAST
INSTRUCTION_PE(AESDECLAST_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F38DF, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VAESDECLAST_STR, PREFIX_CONTEXT_VEX_66_0F38, 0xDF),

//AESENC
INSTRUCTION_PE(AESENC_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F38DC, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VAESENC_STR, PREFIX_CONTEXT_VEX_66_0F38, 0xDC),

//AESENCLAST
INSTRUCTION_PE(AESENCLAST_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F38DD, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VAESENCLAST_STR, PREFIX_CONTEXT_VEX_66_0F38, 0xDD),

//AESIMC
INSTRUCTION_PE(AESIMC_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F38DB, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VAESIMC_STR, PREFIX_CONTEXT_VEX_66_0F38, 0xDB),

//AESKEYGENASSIST
INSTRUCTION_PE(AESKEYGENASSIST_STR, PREFIX_CONTEXT_PREFIX_66, 0x0F3ADF, INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66),
INSTRUCTION_P(VAESKEYGENASSIST_STR, PREFIX_CONTEXT_VEX_66_0F3A, 0xDF),

//AND
INSTRUCTION_P(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x24),
INSTRUCTION_P(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x25),
INSTRUCTION_PE(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x80, INSTRUCTION_ENVIRONMENT_MODRM_REG_4),
INSTRUCTION_PE(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x81, INSTRUCTION_ENVIRONMENT_MODRM_REG_4),
INSTRUCTION_PE(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x83, INSTRUCTION_ENVIRONMENT_MODRM_REG_4),
INSTRUCTION_P(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x20),
INSTRUCTION_P(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x21),
INSTRUCTION_P(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x22),
INSTRUCTION_P(AND_STR, PREFIX_CONTEXT_PREFIX_NOT_REQUIRED, 0x23),
};


//uint64_t instructionListLength = 15;
uint64_t instructionListLength = COUNT_OF(instructionList);