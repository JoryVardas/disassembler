#include <architecture\x86\x86InstructionPrototype.h>

#include <algorithm>
#include <utility>

#include <architecture\x86\x86Modrm.h>


X86InstructionPrototype::X86InstructionPrototype() = default;
X86InstructionPrototype::X86InstructionPrototype(const X86InstructionPrototype&) = default;
X86InstructionPrototype::X86InstructionPrototype(X86InstructionPrototype&&) = default;

X86InstructionPrototype::X86InstructionPrototype(const std::string& name, const X86Environment::X86InstructionMode validMode, const X86InstructionOpcode opcode) :
    _instructionName(name), _validMode(validMode), _requiredPrefixes(std::vector<X86InstructionPrefix>()), _instructionOpcode(opcode) {}
X86InstructionPrototype::X86InstructionPrototype(const std::string& name, const X86Environment::X86InstructionMode validMode, const std::optional<std::vector<X86InstructionPrefix>>& requiredPrefixList, const X86InstructionOpcode opcode, const std::optional<customComparisonFunction>& customComparison) :
    _instructionName(name), _validMode(validMode), _requiredPrefixes(requiredPrefixList), _instructionOpcode(opcode), _customComparison(customComparison) {}
X86InstructionPrototype::X86InstructionPrototype(const std::string& name, const X86Environment::X86InstructionMode validMode, const std::optional<std::vector<X86InstructionPrefix>>& requiredPrefixList, const X86InstructionOpcode opcode, const std::vector<InstructionParameterPrototype>& possibleInstructionParameters, const std::optional<customComparisonFunction>& customComparison) :
    _instructionName(name), _validMode(validMode), _requiredPrefixes(requiredPrefixList), _instructionOpcode(opcode), _instructionParameterPossibilities(std::move(possibleInstructionParameters)), _customComparison(customComparison) {}
X86InstructionPrototype::X86InstructionPrototype(const std::string& name, const X86Environment::X86InstructionMode validMode, const std::optional<std::vector<X86InstructionPrefix>>& requiredPrefixList, const X86InstructionOpcode opcode, const uint8_t modrmOpcodeExtension, const std::vector<InstructionParameterPrototype>& possibleInstructionParameters, const std::optional<customComparisonFunction>& customComparison) :
    _instructionName(name), _validMode(validMode), _requiredPrefixes(requiredPrefixList), _instructionOpcode(opcode), _modrmOpcodeExtensionValue(modrmOpcodeExtension), _instructionParameterPossibilities(std::move(possibleInstructionParameters)), _customComparison(customComparison) {}

X86InstructionPrototype::~X86InstructionPrototype() = default;


bool X86InstructionPrototype::isMatch(const X86Environment::X86InstructionMode currentInstructionMode, const std::vector<X86InstructionPrefix>& prefixList, const X86InstructionOpcode opcode, BidirectionalIterator<std::byte>& bytesToDecode) const{
    if(currentInstructionMode == X86Environment::X86InstructionMode::X64 && _validMode == X86Environment::X86InstructionMode::LEGACY) return false;
    else if (currentInstructionMode == X86Environment::X86InstructionMode::LEGACY && _validMode == X86Environment::X86InstructionMode::X64) return false;
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
            return static_cast<std::byte>(_modrmOpcodeExtensionValue.value()) == getModrmReg(static_cast<modrm_t>(*bytesToDecode));
        }
        return true;
    }
    return false;
}

const std::string& X86InstructionPrototype::getInstructionName() const {
    return _instructionName;
}

const std::vector<InstructionParameterPrototype> X86InstructionPrototype::getPossibleInstructionParameters() const{
    return _instructionParameterPossibilities;
}

const X86Environment::X86InstructionMode X86InstructionPrototype::getValidMode() const{
    return _validMode;
}


X86InstructionPrototype& X86InstructionPrototype::operator=(X86InstructionPrototype&) = default;
X86InstructionPrototype& X86InstructionPrototype::operator=(X86InstructionPrototype&&) = default;