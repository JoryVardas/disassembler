#include <architecture\x86\x86InstructionPrefix.h>

std::optional<X86InstructionRawPrefix> decodeX86InstructionPrefix(const std::byte byteToDecode){
        switch (static_cast<int>(byteToDecode)){
                case static_cast<int>(X86InstructionRawPrefix::ADDRESS_SIZE_OVERRIDE) :
                        return X86InstructionRawPrefix::ADDRESS_SIZE_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::OPERAND_SIZE_OVERRIDE) :
                        return X86InstructionRawPrefix::OPERAND_SIZE_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::CS_SEGMENT_OVERRIDE) :
                        return X86InstructionRawPrefix::CS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::SS_SEGMENT_OVERRIDE) :
                        return X86InstructionRawPrefix::SS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::DS_SEGMENT_OVERRIDE) :
                        return X86InstructionRawPrefix::DS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::ES_SEGMENT_OVERRIDE) :
                        return X86InstructionRawPrefix::ES_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::FS_SEGMENT_OVERRIDE) :
                        return X86InstructionRawPrefix::FS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::GS_SEGMENT_OVERRIDE) :
                        return X86InstructionRawPrefix::GS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionRawPrefix::LOCK) :
                        return X86InstructionRawPrefix::LOCK;
                case static_cast<int>(X86InstructionRawPrefix::REPNZ) :
                        return X86InstructionRawPrefix::REPNZ;
                case static_cast<int>(X86InstructionRawPrefix::REP) :
                        return X86InstructionRawPrefix::REP;
                default:
                        return std::optional<X86InstructionRawPrefix>();
        }
}

std::string X86InstructionPrefixToString(const X86InstructionRawPrefix prefix, const bool useBranchHintsInsteadOfSegmentOverrides){
        switch (prefix){
                case X86InstructionRawPrefix::ADDRESS_SIZE_OVERRIDE :
                        return "";
                case X86InstructionRawPrefix::OPERAND_SIZE_OVERRIDE :
                        return "";
                case X86InstructionRawPrefix::CS_SEGMENT_OVERRIDE :
                        return useBranchHintsInsteadOfSegmentOverrides ? "/BRANCH NOT TAKEN/" : "CS : ";
                case X86InstructionRawPrefix::SS_SEGMENT_OVERRIDE :
                        return "SS : ";
                case X86InstructionRawPrefix::DS_SEGMENT_OVERRIDE :
                        return useBranchHintsInsteadOfSegmentOverrides ? "/BRANCH TAKEN/" : "CS : ";
                case X86InstructionRawPrefix::ES_SEGMENT_OVERRIDE :
                        return "ES : ";
                case X86InstructionRawPrefix::FS_SEGMENT_OVERRIDE :
                        return "FS : ";
                case X86InstructionRawPrefix::GS_SEGMENT_OVERRIDE :
                        return "GS : ";
                case X86InstructionRawPrefix::LOCK :
                        return "LOCK";
                case X86InstructionRawPrefix::REPNZ :
                        return "REPNZ";
                case X86InstructionRawPrefix::REP :
                        return "REP";
        }
        
        return "";
}