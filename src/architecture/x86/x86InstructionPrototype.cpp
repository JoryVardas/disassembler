#include <architecture\x86\x86InstructionPrototype.h>

#include <algorithm>


X86InstructionPrototype::X86InstructionPrototype() = default;
X86InstructionPrototype::X86InstructionPrototype(const X86InstructionPrototype&) = default;
X86InstructionPrototype::X86InstructionPrototype(X86InstructionPrototype&&) = default;

X86InstructionPrototype::X86InstructionPrototype(const std::string& name, const X86InstructionOpcode opcode) :
    _instructionName(name), _requiredPrefixes(std::vector<X86InstructionPrefix>()), _instructionOpcode(opcode) {}
X86InstructionPrototype::X86InstructionPrototype(const std::string& name, const std::optional<std::vector<X86InstructionPrefix>>& requiredPrefixList, const X86InstructionOpcode opcode, const std::optional<customComparisonFunction>& customComparison) :
    _instructionName(name), _requiredPrefixes(requiredPrefixList), _instructionOpcode(opcode), _customComparison(customComparison) {}
X86InstructionPrototype::X86InstructionPrototype(const std::string& name, const std::optional<std::vector<X86InstructionPrefix>>& requiredPrefixList, const X86InstructionOpcode opcode, const uint8_t modrmOpcodeExtension, const std::optional<customComparisonFunction>& customComparison) :
    _instructionName(name), _requiredPrefixes(requiredPrefixList), _instructionOpcode(opcode), _modrmOpcodeExtensionValue(modrmOpcodeExtension), _customComparison(customComparison) {}

X86InstructionPrototype::~X86InstructionPrototype() = default;


bool X86InstructionPrototype::isMatch(const std::vector<X86InstructionPrefix>& prefixList, const X86InstructionOpcode opcode, BidirectionalIterator<std::byte>& bytesToDecode) const{
    if(_customComparison) return _customComparison.value()(*this, prefixList, opcode, bytesToDecode);

    return prefixListMatches(prefixList) && opcodeMatches(opcode, bytesToDecode);
}


bool X86InstructionPrototype::prefixListMatches(const std::vector<X86InstructionPrefix>& prefixList) const {
    if(!_requiredPrefixes) return prefixList.empty();

    if(_requiredPrefixes.value().empty()) return true;

    return std::all_of(_requiredPrefixes.value().cbegin(), _requiredPrefixes.value().cend(), [prefixList](const auto& currentPrefix){
        return std::find(prefixList.cbegin(), prefixList.cend(), currentPrefix) != prefixList.cend();
    });
}
bool X86InstructionPrototype::opcodeMatches(const X86InstructionOpcode opcode, BidirectionalIterator<std::byte> bytesToDecode) const {
    if( _instructionOpcode == opcode){
        if(_modrmOpcodeExtensionValue){
            return static_cast<std::byte>(_modrmOpcodeExtensionValue.value()) == ((*bytesToDecode) & static_cast<std::byte>(0b00111000));
        }
        return true;
    }
    return false;
}

const std::string& X86InstructionPrototype::getInstructionName() const {
    return _instructionName;
}


X86InstructionPrototype& X86InstructionPrototype::operator=(X86InstructionPrototype&) = default;
X86InstructionPrototype& X86InstructionPrototype::operator=(X86InstructionPrototype&&) = default;