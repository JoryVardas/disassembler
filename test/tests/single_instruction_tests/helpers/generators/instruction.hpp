#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_INSTRUCTION_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_INSTRUCTION_HPP

#include <catch2/generators/catch_generators.hpp>
#include <optional>
#include <variant>
#include <vector>

#include "../instruction.hpp"
#include "../prefix.h"
#include "resettable.hpp"
#include "selector.hpp"

namespace Testing::Helpers::Generators {

class InstructionGenerator : public Catch::Generators::IGenerator<Instruction> {
  public:
    using PrefixList = std::vector<std::optional<prefix_t>>;
    using PrefixListGenerator = Catch::Generators::GeneratorWrapper<PrefixList>;
    using ParameterGenerator = std::unique_ptr<ResettableGenerator<Parameter>>;
    using ParameterGeneratorSelectorType =
        GeneratorSelector<ResettableGenerator<Parameter>, PrefixList,
                          X86Environment>;
    using ParameterGeneratorSelector =
        std::unique_ptr<ParameterGeneratorSelectorType>;
    using InstructionParameterGenerator =
        std::variant<ParameterGenerator, ParameterGeneratorSelector>;

  private:
    std::string_view instructionName;
    opcode_bytes instructionOpcode;
    PrefixListGenerator instructionPrefixListGenerator;
    Instruction currentInstruction;
    std::optional<InstructionParameterGenerator> instructionParameter1;
    std::optional<InstructionParameterGenerator> instructionParameter2;
    std::optional<InstructionParameterGenerator> instructionParameter3;
    std::optional<InstructionParameterGenerator> instructionParameter4;
    X86Environment instructionEnvironment;

    const Parameter&
    getParameter(InstructionParameterGenerator& parameterGenerator) const {
        return std::visit(
            [&](auto& arg) -> const Parameter& {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, ParameterGenerator>)
                    return arg->get();
                if constexpr (std::is_same_v<T, ParameterGeneratorSelector>)
                    return arg->get(instructionPrefixListGenerator.get(),
                                    instructionEnvironment);
                throw std::logic_error("Unknown type in "
                                       "InstructionParameterGenerator.");
            },
            parameterGenerator);
    }
    bool nextParameter(InstructionParameterGenerator& parameterGenerator) {
        return std::visit(
            [&](auto& arg) -> bool {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, ParameterGenerator>)
                    return arg->next();
                if constexpr (std::is_same_v<T, ParameterGeneratorSelector>)
                    return arg->next(instructionPrefixListGenerator.get(),
                                     instructionEnvironment);
                throw std::logic_error("Unknown type in "
                                       "InstructionParameterGenerator.");
            },
            parameterGenerator);
    }
    void resetParameter(InstructionParameterGenerator& parameterGenerator) {
        return std::visit(
            [&](auto& arg) -> void {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, ParameterGenerator>)
                    return arg->reset();
                if constexpr (std::is_same_v<T, ParameterGeneratorSelector>)
                    return arg->reset();
                throw std::logic_error("Unknown type in "
                                       "InstructionParameterGenerator.");
            },
            parameterGenerator);
    }
    void setNextInstruction() {
        if (instructionParameter1 && instructionParameter2 &&
            instructionParameter3 && instructionParameter4) {
            auto prefixList = instructionPrefixListGenerator.get();
            currentInstruction =
                Instruction{instructionName,
                            prefixList,
                            instructionOpcode,
                            getParameter(instructionParameter1.value()),
                            getParameter(instructionParameter2.value()),
                            getParameter(instructionParameter3.value()),
                            getParameter(instructionParameter4.value()),
                            instructionEnvironment._endianness};
        } else if (instructionParameter1 && instructionParameter2 &&
                   instructionParameter3) {
            auto prefixList = instructionPrefixListGenerator.get();
            currentInstruction =
                Instruction{instructionName,
                            prefixList,
                            instructionOpcode,
                            getParameter(instructionParameter1.value()),
                            getParameter(instructionParameter2.value()),
                            getParameter(instructionParameter3.value()),
                            instructionEnvironment._endianness};
        } else if (instructionParameter1 && instructionParameter2) {
            auto prefixList = instructionPrefixListGenerator.get();
            currentInstruction =
                Instruction{instructionName,
                            prefixList,
                            instructionOpcode,
                            getParameter(instructionParameter1.value()),
                            getParameter(instructionParameter2.value()),
                            instructionEnvironment._endianness};
        } else if (instructionParameter1) {
            auto prefixList = instructionPrefixListGenerator.get();
            currentInstruction =
                Instruction{instructionName, prefixList, instructionOpcode,
                            getParameter(instructionParameter1.value()),
                            instructionEnvironment._endianness};
        } else {
            currentInstruction = Instruction{
                instructionName, instructionPrefixListGenerator.get(),
                instructionOpcode};
        }
    }

  public:
    InstructionGenerator(
        X86Environment environment, std::string_view name,
        PrefixListGenerator&& prefixGenerator, opcode_bytes&& opcode,
        std::optional<InstructionParameterGenerator> op1Generator =
            std::nullopt,
        std::optional<InstructionParameterGenerator> op2Generator =
            std::nullopt,
        std::optional<InstructionParameterGenerator> op3Generator =
            std::nullopt,
        std::optional<InstructionParameterGenerator> op4Generator =
            std::nullopt)
        : instructionName(name), instructionOpcode(std::move(opcode)),
          instructionPrefixListGenerator(std::move(prefixGenerator)),
          instructionParameter1(std::move(op1Generator)),
          instructionParameter2(std::move(op2Generator)),
          instructionParameter3(std::move(op3Generator)),
          instructionParameter4(std::move(op4Generator)),
          instructionEnvironment(environment) {

        setNextInstruction();
    }

    const Instruction& get() const override { return currentInstruction; }
    bool next() override {
        if (!instructionParameter4 ||
            !nextParameter(instructionParameter4.value())) {
            if (instructionParameter4)
                resetParameter(instructionParameter4.value());
            if (!instructionParameter3 ||
                !nextParameter(instructionParameter3.value())) {
                if (instructionParameter3)
                    resetParameter(instructionParameter3.value());
                if (!instructionParameter2 ||
                    !nextParameter(instructionParameter2.value())) {
                    if (instructionParameter2)
                        resetParameter(instructionParameter2.value());
                    if (!instructionParameter1 ||
                        !nextParameter(instructionParameter1.value())) {
                        if (instructionParameter1)
                            resetParameter(instructionParameter1.value());
                        if (!instructionPrefixListGenerator.next())
                            return false;
                    }
                }
            }
        }
        setNextInstruction();
        return true;
    }
};

namespace {
Catch::Generators::GeneratorWrapper<Instruction> generate_instruction(
    std::string_view name,
    InstructionGenerator::PrefixListGenerator&& prefixGenerator,
    opcode_bytes&& opcode, X86Environment environment) {
    return Catch::Generators::GeneratorWrapper<Instruction>(
        Catch::Detail::make_unique<InstructionGenerator>(
            environment, name, std::move(prefixGenerator), std::move(opcode)));
};

Catch::Generators::GeneratorWrapper<Instruction> generate_instruction(
    std::string_view name,
    InstructionGenerator::PrefixListGenerator&& prefixGenerator,
    opcode_bytes&& opcode,
    InstructionGenerator::InstructionParameterGenerator&& op1Generator,
    X86Environment environment) {
    return Catch::Generators::GeneratorWrapper<Instruction>(
        Catch::Detail::make_unique<InstructionGenerator>(
            environment, name, std::move(prefixGenerator), std::move(opcode),
            std::move(op1Generator)));
};
Catch::Generators::GeneratorWrapper<Instruction> generate_instruction(
    std::string_view name,
    InstructionGenerator::PrefixListGenerator&& prefixGenerator,
    opcode_bytes&& opcode,
    InstructionGenerator::InstructionParameterGenerator&& op1Generator,
    InstructionGenerator::InstructionParameterGenerator&& op2Generator,
    X86Environment environment) {
    return Catch::Generators::GeneratorWrapper<Instruction>(
        Catch::Detail::make_unique<InstructionGenerator>(
            environment, name, std::move(prefixGenerator), std::move(opcode),
            std::move(op1Generator), std::move(op2Generator)));
};
Catch::Generators::GeneratorWrapper<Instruction> generate_instruction(
    std::string_view name,
    InstructionGenerator::PrefixListGenerator&& prefixGenerator,
    opcode_bytes&& opcode,
    InstructionGenerator::InstructionParameterGenerator&& op1Generator,
    InstructionGenerator::InstructionParameterGenerator&& op2Generator,
    InstructionGenerator::InstructionParameterGenerator&& op3Generator,
    X86Environment environment) {
    return Catch::Generators::GeneratorWrapper<Instruction>(
        Catch::Detail::make_unique<InstructionGenerator>(
            environment, name, std::move(prefixGenerator), std::move(opcode),
            std::move(op1Generator), std::move(op2Generator),
            std::move(op3Generator)));
};
Catch::Generators::GeneratorWrapper<Instruction> generate_instruction(
    std::string_view name,
    InstructionGenerator::PrefixListGenerator&& prefixGenerator,
    opcode_bytes&& opcode,
    InstructionGenerator::InstructionParameterGenerator&& op1Generator,
    InstructionGenerator::InstructionParameterGenerator&& op2Generator,
    InstructionGenerator::InstructionParameterGenerator&& op3Generator,
    InstructionGenerator::InstructionParameterGenerator&& op4Generator,
    X86Environment environment) {
    return Catch::Generators::GeneratorWrapper<Instruction>(
        Catch::Detail::make_unique<InstructionGenerator>(
            environment, name, std::move(prefixGenerator), std::move(opcode),
            std::move(op1Generator), std::move(op2Generator),
            std::move(op3Generator), std::move(op4Generator)));
};
} // namespace
} // namespace Testing::Helpers::Generators

#endif
