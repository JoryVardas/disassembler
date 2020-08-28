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

std::string generateParameterTestAssembly(const X86Environment& targetEnvironment, const X86InstructionParameterPrototype& parameterPrototype){
    if (auto registerParameterPrototype = std::get_if<std::shared_ptr<X86InstructionRegisterParameterPrototype>>(&parameterPrototype)){
        return (*registerParameterPrototype)->specify(X86InstructionRegisterParameterGroups.at(static_cast<std::size_t>(distributionOver0to7(random)))).toString();
    }
    else if(auto addressParameterPrototype = std::get_if<std::shared_ptr<X86InstructionAddressParameterPrototype>>(&parameterPrototype)){
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

        return (*addressParameterPrototype)->specify(targetEnvironment._defaultAdressMode, generatedModrm, generatedSib, generatedDisplacement).toString();
    }
    else if (auto immediateParameterPrototype = std::get_if<std::shared_ptr<X86InstructionImmediateParameterPrototype>>(&parameterPrototype)){
        uint64_t generatedImmediate = static_cast<uint64_t>(distributionOverByte(random));
        switch((*immediateParameterPrototype)->size() / 8){
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
        return (*immediateParameterPrototype)->specify(generatedImmediate).toString();
    }

    return "UNKOWN PARAMETER PROTOTYPE";
};

std::string generateInstructionTestAssembly(const X86Environment& targetEnvironment, const X86InstructionPrototype& instruction){
    std::stringstream generatedAssembly;
    
    const auto& instructionParameterList = instruction.getPossibleInstructionParameters();

    if(std::size(instructionParameterList) == 0){
        generatedAssembly << instruction.getInstructionName() << "\n";
        return generatedAssembly.str();
    }

    const size_t longestParameterListSize = std::size((*std::max_element(std::cbegin(instructionParameterList), std::cend(instructionParameterList), [](const InstructionParameterPrototype& a, const InstructionParameterPrototype& b){
        return std::size(a.second) < std::size(b.second);
    })).second);

    for(size_t i = 0; i < longestParameterListSize; ++i){
        generatedAssembly << instruction.getInstructionName() << " ";

        auto& parameterListIterator = std::begin(instructionParameterList);
        const auto& parameterListEnd = std::cend(instructionParameterList);

        generatedAssembly << generateParameterTestAssembly(targetEnvironment, (std::size((*parameterListIterator).second) <= i) ? (*parameterListIterator).second.at(0) : (*parameterListIterator).second.at(i));
        ++parameterListIterator;

        std::for_each(parameterListIterator, parameterListEnd, [&targetEnvironment, &generatedAssembly, &i](const auto& parameterList){
            generatedAssembly << ", " << generateParameterTestAssembly(targetEnvironment, (std::size(parameterList.second) <= i) ? parameterList.second.at(0) : parameterList.second.at(i));
        });

        generatedAssembly << "\n";
    }

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

void runTests(){
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
                std::cout << "Test Faild:\n"
                            "\tDecoded instruction : " << decodedInstructionString << "\n"
                            "\tOriginal instruciion: " << line << "\n";
                return;
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
            runTests();
            return 0;
        }
    }

    printHelp();

    return 0;
}