#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <limits>
#include <cstdlib>
#include <filesystem>

#include <architecture\x86\x86InstructionPrototypeList.h>
#include <architecture\x86\x86Disassembler.h>

std::random_device rd;
std::mt19937 random(rd());
std::uniform_int_distribution<unsigned short> distributionOver0to7(0, 7);
std::uniform_int_distribution<unsigned short> distributionOverByte(0, std::numeric_limits<unsigned char>::max());
std::uniform_int_distribution<unsigned short> distributionOverWord(0, std::numeric_limits<unsigned short>::max());
std::uniform_int_distribution<unsigned int> distributionOverDWord(0, std::numeric_limits<unsigned int>::max());
std::uniform_int_distribution<unsigned long long> distributionOverQWord(0, std::numeric_limits<unsigned long long>::max());

template <typename A>
std::vector<std::vector<A>> cartesian_product(const std::vector<A>& vecA, const std::vector<A>& vecB){
    std::vector<std::vector<A>> ret;
    std::for_each(std::cbegin(vecA), std::cend(vecA), [&ret, &vecB](const A& a){
        std::for_each(std::cbegin(vecB), std::cend(vecB), [&ret, &a](const A& b){
            std::vector<A> cur;
            cur.emplace_back(a);
            cur.emplace_back(b);
            ret.emplace_back(cur);
        });
    });
    return ret;
}
template <typename A>
std::vector<std::vector<A>> cartesian_product(const std::vector<A>& vecA, const std::vector<std::vector<A>>& vecB){
    std::vector<std::vector<A>> ret;
    std::for_each(std::cbegin(vecA), std::cend(vecA), [&ret, &vecB](const A& a){
        std::for_each(std::cbegin(vecB), std::cend(vecB), [&ret, &a](const std::vector<A>& b){
            std::vector<A> cur;
            cur.emplace_back(a);
            std::for_each(std::cbegin(b), std::cend(b), [&cur](const A& bItem){
                cur.emplace_back(bItem);
            });
            ret.emplace_back(cur);
        });
    });
    return ret;
}

template <typename T>
uint16_t getParameterPrototypeSize(const T& proto){
    if (auto registerParameterPrototype = std::get_if<std::shared_ptr<X86InstructionRegisterParameterPrototype>>(&proto)){
        return (*registerParameterPrototype)->size();
    }
    else if(auto addressParameterPrototype = std::get_if<std::shared_ptr<X86InstructionAddressParameterPrototype>>(&proto)){
        switch((*addressParameterPrototype)->size()){
            case X86InstructionAddressParameterSize::BYTE_PTR:
                return static_cast<uint16_t>(8);
            case X86InstructionAddressParameterSize::WORD_PTR:
                return static_cast<uint16_t>(16);
            case X86InstructionAddressParameterSize::DWORD_PTR:
                return static_cast<uint16_t>(32);
            case X86InstructionAddressParameterSize::QWORD_PTR:
                return static_cast<uint16_t>(64);
            case X86InstructionAddressParameterSize::XMM_PTR:
                return static_cast<uint16_t>(128);
            case X86InstructionAddressParameterSize::YMM_PTR:
                return static_cast<uint16_t>(256);
            case X86InstructionAddressParameterSize::ZMM_PTR:
                return static_cast<uint16_t>(512);
        }
        return 0;
    }
    else if (auto immediateParameterPrototype = std::get_if<std::shared_ptr<X86InstructionImmediateParameterPrototype>>(&proto)){
        return static_cast<uint16_t>((*immediateParameterPrototype)->size()) /** 8*/;
    }

    else{
        return 0;
    }
}

std::string generateRegisterParameterTestAssembly(const std::shared_ptr<X86InstructionRegisterParameterPrototype> parameterPrototype){
    return parameterPrototype->specify(X86InstructionRegisterParameterGroups.at(static_cast<std::size_t>(distributionOver0to7(random)))).toString();
}
std::string generateAddressParameterTestAssembly(const X86Environment& targetEnvironment, const std::shared_ptr<X86InstructionAddressParameterPrototype> parameterPrototype){
    const modrm_t generatedModrm = [](){
            while(true){
                modrm_t potentialModrm = static_cast<modrm_t>(distributionOverByte(random));
                if (getModrmMod(potentialModrm) != std::byte(3)) return potentialModrm;
            }
        }();
        const sib_t generatedSib = [&targetEnvironment, &generatedModrm](){
            if(targetEnvironment._defaultAdressMode == X86Environment::X86AddressMode::X16) return sib_t(0);
            if(getModrmRM(generatedModrm) != std::byte(4)) return sib_t(0);
            
            while(true){
                sib_t potentialSib = static_cast<sib_t>(distributionOverByte(random));
                if(getSibIndex(potentialSib) != std::byte(4)) return potentialSib;
            }
        }();
        const uint64_t generatedDisplacement = [&generatedModrm, &targetEnvironment](){
            if(getModrmMod(generatedModrm) == std::byte(1)){
                return static_cast<uint64_t>(distributionOverByte(random));
            }
            else if(getModrmMod(generatedModrm) == std::byte(0) || getModrmMod(generatedModrm) == std::byte(2)){
                switch(targetEnvironment._defaultAdressMode){
                    case X86Environment::X86AddressMode::X16:
                        return static_cast<uint64_t>(distributionOverWord(random));
                    case X86Environment::X86AddressMode::X32:
                        return static_cast<uint64_t>(distributionOverDWord(random));
                    case X86Environment::X86AddressMode::X64:
                        return static_cast<uint64_t>(distributionOverQWord(random));
                }
            }
            return static_cast<uint64_t>(0);
        }();

        return parameterPrototype->specify(targetEnvironment._defaultAdressMode, generatedModrm, generatedSib, generatedDisplacement).toString();
}
std::string generateImmediateParameterTestAssembly(const std::shared_ptr<X86InstructionImmediateParameterPrototype> parameterPrototype){
    uint64_t generatedImmediate = static_cast<uint64_t>(distributionOverByte(random));
        switch(parameterPrototype->size() / 8){
            case 1:
                break;
            case 2:
                generatedImmediate = static_cast<uint64_t>(distributionOverWord(random));
                break;
            case 4:
                generatedImmediate = static_cast<uint64_t>(distributionOverDWord(random));
                break;
            case 8:
                generatedImmediate = static_cast<uint64_t>(distributionOverQWord(random));
                break;
        }
        return parameterPrototype->specify(generatedImmediate).toString();
}

std::string generateParameterTestAssembly(const X86Environment& targetEnvironment, const X86InstructionParameterPrototype& parameterPrototype){
    if (auto registerParameterPrototype = std::get_if<std::shared_ptr<X86InstructionRegisterParameterPrototype>>(&parameterPrototype)){
        return generateRegisterParameterTestAssembly(*registerParameterPrototype);
    }
    else if(auto addressParameterPrototype = std::get_if<std::shared_ptr<X86InstructionAddressParameterPrototype>>(&parameterPrototype)){
        return generateAddressParameterTestAssembly(targetEnvironment, *addressParameterPrototype);
    }
    else if (auto immediateParameterPrototype = std::get_if<std::shared_ptr<X86InstructionImmediateParameterPrototype>>(&parameterPrototype)){
        return generateImmediateParameterTestAssembly(*immediateParameterPrototype);
    }

    return "UNKOWN PARAMETER PROTOTYPE";
};

std::string generateInstructionTestAssembly(const X86Environment& targetEnvironment, const X86InstructionPrototype& instruction){
    std::stringstream generatedAssembly;
    
    const auto& instructionParameterPrototypeList = instruction.getPossibleInstructionParameters();

    if(std::size(instructionParameterPrototypeList) == 0){
        generatedAssembly << instruction.getInstructionName() << "\n";
        return generatedAssembly.str();
    }

    
    auto parameterCombinations = [&instructionParameterPrototypeList](){
        switch(std::size(instructionParameterPrototypeList)){
        case 1:
            {
                std::vector<InstructionParameterGroup> ret;
                ret.emplace_back(instructionParameterPrototypeList.at(0).second);
                return ret;
            }
        case 2:
            return cartesian_product(instructionParameterPrototypeList.at(0).second, instructionParameterPrototypeList.at(1).second);
        case 3:
            return cartesian_product(instructionParameterPrototypeList.at(0).second, cartesian_product(instructionParameterPrototypeList.at(1).second, instructionParameterPrototypeList.at(2).second));
        case 4:
            return cartesian_product(instructionParameterPrototypeList.at(0).second, cartesian_product(instructionParameterPrototypeList.at(1).second, cartesian_product(instructionParameterPrototypeList.at(2).second, instructionParameterPrototypeList.at(3).second)));
        default:
            return std::vector<InstructionParameterGroup>();
        }

    }();

    parameterCombinations.erase(
        std::remove_if(std::begin(parameterCombinations), std::end(parameterCombinations), [](const InstructionParameterGroup& group){
            uint16_t firstParamSize = getParameterPrototypeSize(group.at(0));
            return std::count_if(++std::begin(group), std::end(group), [&firstParamSize](const auto& param){
                return getParameterPrototypeSize(param) > firstParamSize;
            }) > 0;
        }),
        std::end(parameterCombinations));

    std::for_each(std::begin(parameterCombinations), std::end(parameterCombinations), [&generatedAssembly, &instruction, &targetEnvironment](const InstructionParameterGroup& group){
        generatedAssembly << instruction.getInstructionName() << " ";

        generatedAssembly << generateParameterTestAssembly(targetEnvironment, group.at(0));

        std::for_each(++std::begin(group), std::end(group), [&generatedAssembly, &targetEnvironment](const auto& param){
            generatedAssembly << ", " << generateParameterTestAssembly(targetEnvironment, param);
        });
        generatedAssembly << "\n";
    });

    return generatedAssembly.str();
}

void generateTestData(std::string assemblerLocation){
    try{
        std::ofstream assemblyFile("test_data.asm", std::ofstream::trunc);

        X86Environment targetEnvironment;
        targetEnvironment._defaultAdressMode = X86Environment::X86AddressMode::X32;
        targetEnvironment._defaultInstructionMode = X86Environment::X86InstructionMode::LEGACY;
        targetEnvironment._defaultParameterMode = X86Environment::X86ParameterMode::X32;

        if(targetEnvironment._defaultInstructionMode == X86Environment::X86InstructionMode::LEGACY){
            assemblyFile << "[BITS 32]\n";
        }
        else {
            assemblyFile << "[BITS 64]\n";
        }

        for(const auto& instructionPrototype : X86InstructionPrototypeList){
            if(instructionPrototype.getValidMode() == targetEnvironment._defaultInstructionMode || instructionPrototype.getValidMode() == X86Environment::X86InstructionMode::BOTH){
                assemblyFile << generateInstructionTestAssembly(targetEnvironment, instructionPrototype) << "\n";
            }
        }
        assemblyFile.close();
    }
    catch(const std::exception& e){
        std::cerr << "Error opening/writing file to store generated assembly data for x86Tests.\n"
                    "Error Description: \n"
                    "\t" << e.what(); 
        return;
    }

    try{
        std::stringstream assembleCommand;
        assembleCommand << "\"" << assemblerLocation << "\"";
        assembleCommand << " -f bin -O0 -o test_data.bin test_data.asm";
        std::system(assembleCommand.str().c_str());
    }
    catch(const std::exception& e){
        std::cerr << "Error generating binary file from generated assembly data for x86Tests.\n"
                    "Error Description: \n"
                    "\t" << e.what(); 
        return;
    }
}

void runTests(bool outputSuccess){
    try{
        std::filesystem::path assemblyFilePath(".\\test_data.asm");
        std::filesystem::path binaryFilePath(".\\test_data.bin");
        std::ifstream assemblyFile(assemblyFilePath);
        std::ifstream binaryFile(binaryFilePath, std::ifstream::binary);

        bool assemblyFileIsOpen = assemblyFile.is_open();
        bool assemblyFileIsGood = assemblyFile.good();

        if(!assemblyFileIsOpen || !assemblyFileIsGood){
            throw std::runtime_error("Could not open test_data.asm");
        }
        if(!binaryFile.is_open() || !binaryFile.good()){
            throw std::runtime_error("Could not open test_data.bin");
        }

        auto assemblyFileSize = std::filesystem::file_size(assemblyFilePath);
        auto binaryFileSize = std::filesystem::file_size(binaryFilePath);

        auto assemblyFileBuffer = std::make_unique<char[]>(assemblyFileSize);
        auto binaryFileBuffer = std::make_unique<std::byte[]>(binaryFileSize); 

        assemblyFile.read(assemblyFileBuffer.get(), assemblyFileSize);
        binaryFile.read(reinterpret_cast<char*>(binaryFileBuffer.get()), binaryFileSize);

        assemblyFile.close();
        binaryFile.close();

        BidirectionalIterator<char> assemblyFileIterator(assemblyFileBuffer.get(), assemblyFileSize);
        BidirectionalIterator<std::byte> binaryFileIterator(binaryFileBuffer.get(), binaryFileSize);

        auto getAssemblyLine = [&assemblyFileIterator](){
            std::stringstream line;
            while(true){
                char cur = *(assemblyFileIterator++);
                if(cur == '\n') break;
                line << cur;
            }
            return line.str();
        };

        X86Environment targetEnvironment;
        targetEnvironment._defaultAdressMode = X86Environment::X86AddressMode::X32;
        targetEnvironment._defaultInstructionMode = X86Environment::X86InstructionMode::LEGACY;
        targetEnvironment._defaultParameterMode = X86Environment::X86ParameterMode::X32;

        X86Disassembler disassembler(targetEnvironment);

        uint64_t currentLine = 0;

        while(assemblyFileIterator.isValid() && binaryFileIterator.isValid()){
            //get the text line
            std::string line = getAssemblyLine();
            currentLine++;
            if(std::size(line) == 0) continue;
            if(line.find("[BITS", 0) == 0) continue;

            auto decodedInstruction = disassembler.decodeInstruction(binaryFileIterator);
            std::string decodedInstructionString = decodedInstruction->toString();

            if(decodedInstructionString != line){
                std::cout << "Test Failed:\n"
                            "\tDecoded instruction : " << decodedInstructionString << "\n"
                            "\tOriginal instruction: " << line << "\n";
                return;
            }
            else if (outputSuccess){
                std::cout << "Test Succeded:\n"
                             "\tDecoded instruction : " << decodedInstructionString << "\n"
                             "\tOriginal instruction: " << line << "\n";
            }
        }

        std::cout << "Test Success";
    }
    catch(const std::exception& e){
        std::cerr << "Error opening/reading test data for x86Tests.\n"
                    "Error Description: \n"
                    "\t" << e.what(); 
        return;
    }
}


std::vector<std::string> convertMainArgsToStrings(int argc, const char* argv[]){
    std::vector<std::string> argumentList(argc);

    for (int i = 0; i < argc; ++i){
        argumentList.emplace_back(argv[i]);
    }

    return argumentList;
}

void printHelp(){
    std::cout << "Usage: <command> [arguments] \n"
        "Commands:\n"
        "\t --generate <assembler location> \n"
        "\t\t Will generate the test data required for the tests.\n"
        "\t --run\n"
        "\t\t Will run the tests.\n"
        << std::endl;
}

int main(int argc, const char* argv[]){
    std::vector<std::string> arguments = convertMainArgsToStrings(argc, argv);
    auto currentArgument = std::cbegin(arguments);
    
    for(;currentArgument != std::cend(arguments); ++currentArgument){
        if(*currentArgument == "--generate"){
            generateTestData(*(++currentArgument));
            return 0;
        }
        else if(*currentArgument == "--run"){
            bool outputSuccess = std::any_of(std::cbegin(arguments), std::cend(arguments), [](const auto& argument){
                return argument == "--output-success";
            });
            runTests(outputSuccess);
            return 0;
        }
    }

    printHelp();

    return 0;
}