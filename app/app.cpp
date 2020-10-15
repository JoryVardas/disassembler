#include <vector>
#include <iostream>

#include <algorithm>

#include <bidirectionalIterator.h>

#include <architecture/x86/x86Disassembler.h>
#include <architecture/x86/x86Instruction.h>

int main(/*int argc, char* argv[]*/){
        try{

                std::vector<std::byte> test = {
                        std::byte(0x80), std::byte(0xd1), std::byte(0x02),
                        std::byte(0x81), std::byte(0xd1), std::byte(0x04), std::byte(0x00), std::byte(0x00), std::byte(0x00),
                        std::byte(0x81), std::byte(0x14), std::byte(0x41), std::byte(0x04), std::byte(0x00), std::byte(0x00), std::byte(0x00),
                        std::byte(0x81), std::byte(0x54), std::byte(0x41), std::byte(0x04), std::byte(0x04), std::byte(0x00), std::byte(0x00), std::byte(0x00),
                        std::byte(0xd5), std::byte(0x0a),
                        std::byte(X86InstructionPrefix::LOCK), std::byte(0x37)
                };

                BidirectionalIterator<std::byte> byteStream ( std::begin(test)._Ptr, static_cast<const int64_t>(std::size(test)));

                X86Environment env;
                env._defaultAdressMode = X86Environment::X86AddressMode::X32;
                env._defaultInstructionMode = X86Environment::X86InstructionMode::LEGACY;
                env._defaultParameterMode = X86Environment::X86ParameterMode::X32;
                env._endianness = X86Environment::X86Endianness::LITTLE_ENDIAN;
                X86Disassembler disasm(env);
                std::vector<std::unique_ptr<Instruction>> decodedInstructions;
                decodedInstructions.emplace_back(disasm.decodeInstruction(byteStream));
                decodedInstructions.emplace_back(disasm.decodeInstruction(byteStream));
                decodedInstructions.emplace_back(disasm.decodeInstruction(byteStream));
                decodedInstructions.emplace_back(disasm.decodeInstruction(byteStream));
                decodedInstructions.emplace_back(disasm.decodeInstruction(byteStream));
                decodedInstructions.emplace_back(disasm.decodeInstruction(byteStream));
                for(const auto& instruction : decodedInstructions){
                        std::cout << instruction->toString() << "\n";
                }
        }
        catch(const std::exception& e){
                std::cout << "ERROR: " << e.what() << std::endl;
        }

        return 0;
}