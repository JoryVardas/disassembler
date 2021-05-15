#include <architecture/x86/x86Disassembler.h>

#include <algorithm>

#include <architecture/x86/x86Instruction.h>
#include <architecture/x86/x86InstructionPrototype.h>
#include <architecture/x86/x86InstructionPrototypeList.h>

#include <architecture/x86/x86Modrm.h>

X86Disassembler::X86Disassembler(X86Environment& environment) : _disassemblerEnvirionment(environment) {}
X86Disassembler::X86Disassembler(X86Disassembler&) = default;
X86Disassembler::X86Disassembler(X86Disassembler&&) = default;
X86Disassembler::~X86Disassembler() = default;
        
std::unique_ptr<Instruction> X86Disassembler::decodeInstruction(BidirectionalIterator<std::byte>& bytesToDecode) const{
        std::vector<X86InstructionPrefix> prefixList = decodeInstructionPrefixes(bytesToDecode);
        X86InstructionOpcode opcode = retrieveInstructionOpcode(bytesToDecode);
        X86InstructionPrototype instructionPrototype = decodeInstructionPrototype(prefixList, opcode, bytesToDecode);
        std::vector<std::shared_ptr<InstructionParameter>> params = decodeInstructionParameters(instructionPrototype, prefixList, bytesToDecode);


       // std::vector<InstructionParameter> parameters = decodeInstructionParameters(prefixes, opcode, bytesToDecode);


        //return std::make_unique<X86Instruction>(prefixes, opcode, parameters);

        return std::make_unique<X86Instruction>(instructionPrototype.getInstructionName(), prefixList, params);
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
        const X86Environment::X86InstructionMode currentInstructionMode = _disassemblerEnvirionment._defaultInstructionMode;
        auto found = std::find_if(X86InstructionPrototypeList.begin(), X86InstructionPrototypeList.end(), [&currentInstructionMode, &prefixList, &opcode, &bytesToDecode](const X86InstructionPrototype& currentInstructionPrototype){
                return currentInstructionPrototype.isMatch(currentInstructionMode, prefixList, opcode, bytesToDecode);
        });
        if (found != X86InstructionPrototypeList.end()){
                return *found;
        }
        return X86InstructionPrototype();
}


std::vector<std::shared_ptr<InstructionParameter>> X86Disassembler::decodeInstructionParameters(const X86InstructionPrototype& instructionPrototype, const std::vector<X86InstructionPrefix>& prefixList, BidirectionalIterator<std::byte>& bytesToDecode) const{
        std::vector<InstructionParameterPrototype> instructionParameterPrototypes = instructionPrototype.getPossibleInstructionParameters();

        using ParameterMode = X86Environment::X86ParameterMode;
        using AddressMode = X86Environment::X86AddressMode;
        const ParameterMode currentParameterMode = [&instructionPrototype, &prefixList](const ParameterMode& defaultParameterMode){
                if(!instructionPrototype.requiresNoPrefix()
                && !instructionPrototype.requiresPrefix(X86InstructionRawPrefix::OPERAND_SIZE_OVERRIDE)
                && std::find(std::cbegin(prefixList), std::cend(prefixList), X86InstructionRawPrefix::OPERAND_SIZE_OVERRIDE) != std::cend(prefixList)){
                        switch (defaultParameterMode){
                                case ParameterMode::X16:
                                        return ParameterMode::X32;
                                case ParameterMode::X32:
                                        return ParameterMode::X16;
                                case ParameterMode::X64:
                                        return ParameterMode::X32;
                        }
                }
                return defaultParameterMode;
        }(_disassemblerEnvirionment._defaultParameterMode);
        const AddressMode currentAddressMode = [&instructionPrototype, &prefixList](const AddressMode& defaultAddressMode){
                if(!instructionPrototype.requiresNoPrefix()
                && !instructionPrototype.requiresPrefix(X86InstructionRawPrefix::ADDRESS_SIZE_OVERRIDE)
                && std::find(std::cbegin(prefixList), std::cend(prefixList), X86InstructionRawPrefix::ADDRESS_SIZE_OVERRIDE) != std::cend(prefixList)){
                        switch (defaultAddressMode){
                                case AddressMode::X16:
                                        return AddressMode::X32;
                                case AddressMode::X32:
                                        return AddressMode::X16;
                                case AddressMode::X64:
                                        return AddressMode::X32;
                        }
                }
                return defaultAddressMode;
        }(_disassemblerEnvirionment._defaultAdressMode);

        const auto rexPrefix = [&prefixList](){
                auto i = std::find_if(std::cbegin(prefixList), std::cend(prefixList), [](const auto& prefix){
                        return std::holds_alternative<X86InstructionRexPrefix>(prefix);
                });
                if(i != std::cend(prefixList))
                        return std::get<X86InstructionRexPrefix>(*i);
                return X86InstructionRexPrefix(std::byte(0));
        }();
        
        const auto [modrm, sib] = [&instructionParameterPrototypes, &currentAddressMode, &bytesToDecode](){
                auto parameterPrototypeNeedsModrm = [](const InstructionParameterPrototype& currentParameterPrototype){
                        return currentParameterPrototype.first == X86InstructionParameterLocation::MODRM_REG || currentParameterPrototype.first == X86InstructionParameterLocation::MODRM_RM;
                };

                if(std::find_if(instructionParameterPrototypes.cbegin(), instructionParameterPrototypes.cend(), parameterPrototypeNeedsModrm) != instructionParameterPrototypes.cend()){
                        modrm_t modrm = *(bytesToDecode++);
                        sib_t sib = [&modrm, &currentAddressMode, &bytesToDecode](){
                                if (currentAddressMode != AddressMode::X16){
                                        if(getModrmMod(modrm) != std::byte(3)){
                                                if(getModrmRM(modrm) == std::byte(4)){
                                                        return *(bytesToDecode++);
                                                }
                                        }
                                }
                                return sib_t();
                        }();
                        return std::pair(modrm, sib);
                }
                return std::pair<modrm_t, sib_t>(modrm_t(),sib_t());
        }();

        auto removeRegisterOrMemoryCandidates = [&modrm](const X86InstructionParameterPrototype& candidateParameter){
                if(getModrmMod(modrm) == std::byte(3) && holds_any_alternative<X86InstructionAddressParameterPrototype_t>(candidateParameter)){
                        return true;
                }
                else if(getModrmMod(modrm) != std::byte(3) && holds_any_alternative<X86InstructionRegisterParameterPrototype_t>(candidateParameter)){
                        return true;
                }
                return false;
        };
        auto removeRegisterSizes = [&currentParameterMode](const X86InstructionParameterPrototype& candidateParameter){
                if (!holds_any_alternative<X86InstructionRegisterParameterPrototype_t>(candidateParameter)) return false;

                switch (currentParameterMode){
                        case ParameterMode::X16:
                                return std::get<RegisterSize>(std::visit(x86InstructionRegisterParameterPrototypeGetSize, candidateParameter)) != 16;
                        case ParameterMode::X32:
                                return std::get<RegisterSize>(std::visit(x86InstructionRegisterParameterPrototypeGetSize, candidateParameter)) != 32;
                        case ParameterMode::X64:
                                return std::get<RegisterSize>(std::visit(x86InstructionRegisterParameterPrototypeGetSize, candidateParameter)) != 64;
                }
                
                return false;
        };
        auto removeAddressSizes = [&currentParameterMode](const X86InstructionParameterPrototype& candidateParameter){
                if (!holds_any_alternative<X86InstructionAddressParameterPrototype_t>(candidateParameter)) return false;

                switch (currentParameterMode){
                        case ParameterMode::X16:
                                return std::get<X86InstructionAddressParameterSize>(std::visit(x86InstructionAddressParameterPrototypeGetSize, candidateParameter)) != X86InstructionAddressParameterSize::WORD_PTR;
                        case ParameterMode::X32:
                                return std::get<X86InstructionAddressParameterSize>(std::visit(x86InstructionAddressParameterPrototypeGetSize, candidateParameter)) != X86InstructionAddressParameterSize::DWORD_PTR;
                        case ParameterMode::X64:
                                return std::get<X86InstructionAddressParameterSize>(std::visit(x86InstructionAddressParameterPrototypeGetSize, candidateParameter)) != X86InstructionAddressParameterSize::QWORD_PTR;
                }
                
                return false;
        };
        auto removeImmediateSizes = [&currentParameterMode](const X86InstructionParameterPrototype& candidateParameter){
                if (!holds_any_alternative<X86InstructionImmediateParameterPrototype_t>(candidateParameter)) return false;

                switch (currentParameterMode){
                        case ParameterMode::X16:
                                return std::get<InstructionImmediateSize>(std::visit(x86InstructionImmediateParameterPrototypeGetSize, candidateParameter)) != 16;
                        case ParameterMode::X32:
                                return std::get<InstructionImmediateSize>(std::visit(x86InstructionImmediateParameterPrototypeGetSize, candidateParameter)) != 32;
                        case ParameterMode::X64:
                                return std::get<InstructionImmediateSize>(std::visit(x86InstructionImmediateParameterPrototypeGetSize, candidateParameter)) != 64;
                }
                
                return false;
        };

        for (auto& parameterPrototypeList : instructionParameterPrototypes) {
                const X86InstructionParameterLocation parameterLocation = parameterPrototypeList.first;
                auto& prototypeList = parameterPrototypeList.second;
                if(std::size(prototypeList) <= 1) continue;

                if(parameterLocation == X86InstructionParameterLocation::MODRM_RM){
                        erase_if(prototypeList, removeRegisterOrMemoryCandidates);
                }
                else if(parameterLocation == X86InstructionParameterLocation::IMPLIED){
                        erase_if(prototypeList, removeRegisterSizes);
                }

                if(std::size(prototypeList) <= 1) continue;
                
                erase_if(prototypeList, removeRegisterSizes);
                
                if(std::size(prototypeList) <= 1) continue;
                
                erase_if(prototypeList, removeAddressSizes);
                
                if(std::size(prototypeList) <= 1) continue;

                erase_if(prototypeList, removeImmediateSizes);
        }

        std::vector<std::shared_ptr<InstructionParameter>> specifiedParameterList;

        for(const auto& parameterPrototypeList : instructionParameterPrototypes){
                const auto& parameterLocation = parameterPrototypeList.first;
                const auto& prototypeList = parameterPrototypeList.second;
                if(std::size(prototypeList) == 0){
                        throw std::runtime_error("All candidate parameter prototypes were removed!");
                }
                if(std::size(prototypeList) > 1){
                        throw std::runtime_error("Multiple candidate parameter prototypes still remaining!");
                }

                auto prototype = prototypeList.at(0);
                
                if(holds_any_alternative<X86InstructionRegisterParameterPrototype_t>(prototype)){
                        if (parameterLocation == X86InstructionParameterLocation::MODRM_REG){
                                specifiedParameterList.emplace_back(std::visit(std::bind(x86InstructionParameterPrototypeSpecify, std::placeholders::_1, X86InstructionRegisterParameterGroups.at(static_cast<std::size_t>(getModrmReg(modrm)))), prototype));
                        }
                        else if(parameterLocation == X86InstructionParameterLocation::MODRM_RM){
                                specifiedParameterList.emplace_back(std::visit(std::bind(x86InstructionParameterPrototypeSpecify, std::placeholders::_1, X86InstructionRegisterParameterGroups.at(static_cast<std::size_t>(getModrmRM(modrm)))), prototype));
                        }
                        else if(parameterLocation == X86InstructionParameterLocation::IMPLIED){
                                specifiedParameterList.emplace_back(std::visit(std::bind(x86InstructionParameterPrototypeSpecify, std::placeholders::_1, X86InstructionRegisterParameterGroups.at(0)), prototype));
                        }
                }
                else if(holds_any_alternative<X86InstructionAddressParameterPrototype_t>(prototype)){
                        uint64_t displacementValue = 0;
                        if (_disassemblerEnvirionment._endianness==std::endian::big){
                                switch(getDisplacementSizeRequiredByModrm(modrm, sib, currentAddressMode) / 8){
                                        case 4:
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                displacementValue *= 256;
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                displacementValue *= 256;
                                        case 2:
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                displacementValue *= 256;
                                        case 1:
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                break;
                                }
                        }
                        else if (_disassemblerEnvirionment._endianness==std::endian::little){
                                switch(getDisplacementSizeRequiredByModrm(modrm, sib, currentAddressMode) / 8){
                                        case 4:
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256;
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256 * 256;
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256 * 256 * 256;
                                                break;
                                        case 2:
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256;
                                                break;
                                        case 1:
                                                displacementValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                break;
                                }
                        }
                        specifiedParameterList.emplace_back(std::visit(std::bind(x86InstructionParameterPrototypeSpecify, std::placeholders::_1, currentAddressMode, modrm, sib, displacementValue), prototype));
                }
                else if (holds_any_alternative<X86InstructionImmediateParameterPrototype_t>(prototype)){
                        uint64_t immediateValue = 0;
                        if (_disassemblerEnvirionment._endianness==std::endian::big){
                                switch(std::get<InstructionImmediateSize>(std::visit(x86InstructionImmediateParameterPrototypeGetSize, prototype)) / 8){
                                        case 4:
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                immediateValue *= 256;
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                immediateValue *= 256;
                                        case 2:
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                immediateValue *= 256;
                                        case 1:
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                break;
                                }
                        }
                        else if (_disassemblerEnvirionment._endianness==std::endian::little){
                                switch(std::get<InstructionImmediateSize>(std::visit(x86InstructionImmediateParameterPrototypeGetSize, prototype)) / 8){
                                        case 4:
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256;
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256 * 256;
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256 * 256 * 256;
                                                break;
                                        case 2:
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++)) * 256;
                                                break;
                                        case 1:
                                                immediateValue += static_cast<uint64_t>(*(bytesToDecode++));
                                                break;
                                }
                        }

                        specifiedParameterList.emplace_back(std::visit(std::bind(x86InstructionParameterPrototypeSpecify, std::placeholders::_1, immediateValue), prototype));
                }
        }

        return specifiedParameterList;
}