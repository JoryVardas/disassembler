#include <architecture/x86/x86InstructionPrefix.h>


X86InstructionRexPrefix::X86InstructionRexPrefix(const std::byte byte) : _prefix(byte){};
X86InstructionRexPrefix::X86InstructionRexPrefix(const X86InstructionRexPrefix&) = default;
X86InstructionRexPrefix::X86InstructionRexPrefix(X86InstructionRexPrefix&&) = default;
X86InstructionRexPrefix::~X86InstructionRexPrefix() = default;
X86InstructionRexPrefix& X86InstructionRexPrefix::operator=(const X86InstructionRexPrefix&) = default;
X86InstructionRexPrefix& X86InstructionRexPrefix::operator=(X86InstructionRexPrefix&&) = default;


std::byte X86InstructionRexPrefix::getW() const {return (_prefix & std::byte(0b00001000)) >> 3;}
std::byte X86InstructionRexPrefix::getR() const {return (_prefix & std::byte(0b00000100)) >> 2;}
std::byte X86InstructionRexPrefix::getX() const {return (_prefix & std::byte(0b00000010)) >> 1;}
std::byte X86InstructionRexPrefix::getB() const {return (_prefix & std::byte(0b00000001));}


std::optional<X86InstructionPrefix> decodeX86InstructionPrefix(const std::byte byteToDecode){
        if((byteToDecode & X86InstructionRexPrefix::IdentifierMask) == X86InstructionRexPrefix::Identifier)
                return X86InstructionRexPrefix(byteToDecode);
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
                        return std::optional<X86InstructionPrefix>();
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


bool operator ==(const X86InstructionRawPrefix& a, const X86InstructionPrefix& b){
        if(!std::holds_alternative<X86InstructionRawPrefix>(b)) return false;
        return std::get<X86InstructionRawPrefix>(b) == a;
};
bool operator ==(const X86InstructionPrefix& a, const X86InstructionRawPrefix& b){
        if(!std::holds_alternative<X86InstructionRawPrefix>(a)) return false;
        return std::get<X86InstructionRawPrefix>(a) == b;
};
bool operator ==(const X86InstructionPrefix& a, const X86InstructionPrefix& b){
        if(a.index() != b.index()) return false;
        if(std::holds_alternative<X86InstructionRawPrefix>(a))
                return std::get<X86InstructionRawPrefix>(a) == std::get<X86InstructionRawPrefix>(b);
        if(std::holds_alternative<X86InstructionRexPrefix>(a))
                return std::get<X86InstructionRexPrefix>(a) == std::get<X86InstructionRexPrefix>(b);
        return false;
};