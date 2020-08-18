#include <architecture\x86\x86InstructionPrefix.h>

std::optional<X86InstructionPrefix> decodeX86InstructionPrefix(const std::byte byteToDecode){
        switch (static_cast<int>(byteToDecode)){
                case static_cast<int>(X86InstructionPrefix::ADDRESS_SIZE_OVERRIDE) :
                        return X86InstructionPrefix::ADDRESS_SIZE_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::OPERAND_SIZE_OVERRIDE) :
                        return X86InstructionPrefix::OPERAND_SIZE_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::CS_SEGMENT_OVERRIDE) :
                        return X86InstructionPrefix::CS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::SS_SEGMENT_OVERRIDE) :
                        return X86InstructionPrefix::SS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::DS_SEGMENT_OVERRIDE) :
                        return X86InstructionPrefix::DS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::ES_SEGMENT_OVERRIDE) :
                        return X86InstructionPrefix::ES_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::FS_SEGMENT_OVERRIDE) :
                        return X86InstructionPrefix::FS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::GS_SEGMENT_OVERRIDE) :
                        return X86InstructionPrefix::GS_SEGMENT_OVERRIDE;
                case static_cast<int>(X86InstructionPrefix::LOCK) :
                        return X86InstructionPrefix::LOCK;
                case static_cast<int>(X86InstructionPrefix::REPNZ) :
                        return X86InstructionPrefix::REPNZ;
                case static_cast<int>(X86InstructionPrefix::REP) :
                        return X86InstructionPrefix::REP;
                default:
                        return std::optional<X86InstructionPrefix>();
        }
}

std::string X86InstructionPrefixToString(const X86InstructionPrefix prefix, const bool useBranchHintsInsteadOfSegmentOverrides){
        switch (prefix){
                case X86InstructionPrefix::ADDRESS_SIZE_OVERRIDE :
                        return "";
                case X86InstructionPrefix::OPERAND_SIZE_OVERRIDE :
                        return "";
                case X86InstructionPrefix::CS_SEGMENT_OVERRIDE :
                        return useBranchHintsInsteadOfSegmentOverrides ? "/BRANCH NOT TAKEN/" : "CS : ";
                case X86InstructionPrefix::SS_SEGMENT_OVERRIDE :
                        return "SS : ";
                case X86InstructionPrefix::DS_SEGMENT_OVERRIDE :
                        return useBranchHintsInsteadOfSegmentOverrides ? "/BRANCH TAKEN/" : "CS : ";
                case X86InstructionPrefix::ES_SEGMENT_OVERRIDE :
                        return "ES : ";
                case X86InstructionPrefix::FS_SEGMENT_OVERRIDE :
                        return "FS : ";
                case X86InstructionPrefix::GS_SEGMENT_OVERRIDE :
                        return "GS : ";
                case X86InstructionPrefix::LOCK :
                        return "LOCK";
                case X86InstructionPrefix::REPNZ :
                        return "REPNZ";
                case X86InstructionPrefix::REP :
                        return "REP";
        }
        
        return "";
}