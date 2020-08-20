#include <architecture\x86\x86Disassembler.h>
#include <architecture\x86\x86Instruction.h>
#include <architecture\x86\x86InstructionPrototype.h>
#include <architecture\x86\x86InstructionPrototypeList.h>

X86Disassembler::X86Disassembler() = default;
X86Disassembler::X86Disassembler(X86Disassembler&) = default;
X86Disassembler::X86Disassembler(X86Disassembler&&) = default;
X86Disassembler::~X86Disassembler() = default;
        
std::unique_ptr<Instruction> X86Disassembler::decodeInstruction(BidirectionalIterator<std::byte>& bytesToDecode) const{
        std::vector<X86InstructionPrefix> prefixList = decodeInstructionPrefixes(bytesToDecode);
        X86InstructionOpcode opcode = retrieveInstructionOpcode(bytesToDecode);
        X86InstructionPrototype instructionPrototype = decodeInstructionPrototype(prefixList, opcode, bytesToDecode);


       // std::vector<InstructionParameter> parameters = decodeInstructionParameters(prefixes, opcode, bytesToDecode);


        //return std::make_unique<X86Instruction>(prefixes, opcode, parameters);

        return std::make_unique<X86Instruction>(instructionPrototype.getInstructionName(), prefixList);
}





std::vector<X86InstructionPrefix> X86Disassembler::decodeInstructionPrefixes(BidirectionalIterator<std::byte>& bytesToDecode) const{
        std::vector<X86InstructionPrefix> prefixList;
        
        if (!bytesToDecode.isValid()){
                throw std::range_error("Ran out of bytes to decode while decoding instruction prefixes.");
        }

        std::optional<X86InstructionPrefix> possiblePrefix = decodeX86InstructionPrefix(*bytesToDecode);
        while (possiblePrefix.has_value()){
                prefixList.push_back(possiblePrefix.value());

                ++bytesToDecode;
                if (bytesToDecode.isValid()){
                        possiblePrefix = decodeX86InstructionPrefix(*bytesToDecode);       
                }
                else{
                        throw std::range_error("Ran out of bytes to decode while decoding instruction prefixes.");
                }
        }

        return prefixList;
}


X86InstructionOpcode X86Disassembler::retrieveInstructionOpcode(BidirectionalIterator<std::byte>& bytesToDecode) const{
        const static std::byte twoByteOpcodeEscapeByte = std::byte(0x0f);
        const static std::byte threeByteOpcodeEscapeByte1 = std::byte(0x38);
        const static std::byte threeByteOpcodeEscapeByte2 = std::byte(0x3a);


        if (!bytesToDecode.isValid()){
                throw std::range_error("Ran out of bytes to decode while retreiving the instruction opcode.");
        }

        std::byte currentByte = *(bytesToDecode++);
        X86InstructionOpcode opcode = 0 + static_cast<X86InstructionOpcode>(currentByte);

        // Check if we are dealing with a longer opcode
        if (currentByte == twoByteOpcodeEscapeByte){
                if (!bytesToDecode.isValid()){
                        throw std::range_error("Ran out of bytes to decode while retreiving the instruction opcode.");
                }
                currentByte = *(bytesToDecode++);

                opcode *= 256;
                opcode += static_cast<X86InstructionOpcode>(currentByte);

                // Check if we are dealing with a three byte opcode
                if (currentByte == threeByteOpcodeEscapeByte1 || currentByte == threeByteOpcodeEscapeByte2){
                        if (!bytesToDecode.isValid()){
                                throw std::range_error("Ran out of bytes to decode while retreiving the instruction opcode.");
                        }
                        currentByte = *(bytesToDecode++);

                        opcode *= 256;
                        opcode += static_cast<X86InstructionOpcode>(currentByte);
                }
        }

        return opcode;
}

X86InstructionPrototype X86Disassembler::decodeInstructionPrototype(const std::vector<X86InstructionPrefix>& prefixList, const X86InstructionOpcode opcode, BidirectionalIterator<std::byte>& bytesToDecode) const{
        auto found = std::find_if(X86InstructionPrototypeList.begin(), X86InstructionPrototypeList.end(), [](const auto&){
                return true;
        });
        if (found != X86InstructionPrototypeList.end()){
                return *found;
        }

        if (bytesToDecode.isValid() && found != X86InstructionPrototypeList.end() && !prefixList.empty() && opcode == X86InstructionOpcode()){
                return X86InstructionPrototype();
        }
        return *found;
}