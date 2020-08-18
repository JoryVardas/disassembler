#include <architecture\x86\x86Disassembler.h>
#include <architecture\x86\x86Instruction.h>

X86Disassembler::X86Disassembler() = default;
X86Disassembler::X86Disassembler(X86Disassembler&) = default;
X86Disassembler::X86Disassembler(X86Disassembler&&) = default;
X86Disassembler::~X86Disassembler() = default;
        
std::unique_ptr<Instruction> X86Disassembler::decodeInstruction(BidirectionalIterator<std::byte>& bytesToDecode) const{
        std::vector<X86InstructionPrefix> prefixList = decodeInstructionPrefixes(bytesToDecode);
       // X86InstructionOpcode opcode = decodeInstructionOpcode(prefixes, bytesToDecode);
       // std::vector<InstructionParameter> parameters = decodeInstructionParameters(prefixes, opcode, bytesToDecode);


        //return std::make_unique<X86Instruction>(prefixes, opcode, parameters);

        return std::make_unique<X86Instruction>(prefixList);
}





std::vector<X86InstructionPrefix> X86Disassembler::decodeInstructionPrefixes(BidirectionalIterator<std::byte>& bytesToDecode) const{
        std::vector<X86InstructionPrefix> prefixList;
        
        std::optional<X86InstructionPrefix> possiblePrefix = decodeX86InstructionPrefix(*(bytesToDecode++));
        while(possiblePrefix.has_value()){
                prefixList.push_back(possiblePrefix.value());

                if(bytesToDecode.isValid()){
                        possiblePrefix = decodeX86InstructionPrefix(*(bytesToDecode++));
                }
                else{
                        break;
                }
        }

        return prefixList;
}
