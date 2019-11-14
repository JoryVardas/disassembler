using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InstructionDataGen
{
    public partial class Form1 : Form
    {
        private object[] PossibleOperandTypes = {
            "NO_OPERANDS",
            "REL8",
            "REL16",
            "REL32",
            "PTR16",
            "PTR32",
            "PTR16_16",
            "PTR16_32",
            "R8",
            "R16",
            "R32",
            "R64",
            "IMM8",
            "IMM16",
            "IMM32",
            "IMM64",
            "M8",
            "M16",
            "M32",
            "M64",
            "M128",
            "M16_16",
            "M16_32",
            "M16_64",
            "M16__32",
            "M16__16",
            "M32__32",
            "M16__64",
            "MOFFS8",
            "MOFFS16",
            "MOFFS32",
            "MOFFS64",
            "SREG",
            "M32FP",
            "M64FP",
            "M80FP",
            "M16INT",
            "M32INT",
            "M64INT",
            "ST0",
            "ST",
            "MM",
            "XMM",
            "YMM",
            "M256",
            "BND",
            "MIB",
            "ZMM",
            "_K_Z_",
            "_K_",
            "K",
            "MV",
            "VM32",
            "VM64",
            "M32BCST",
            "M64BCST",
            "IMPLICIT_AL",
            "IMPLICIT_AX",
            "IMPLICIT_EAX",
            "IMPLICIT_RAX",
            "IMPLICIT_XMM0",
            "IMPLICIT_YMM0",
            "IMPLICIT_ZMM0",
            "R16_32_64",
            "M16_32_64",
            "RM16_32_64",
            "RM8",
            "RM16",
            "RM32",
            "RM64",
            "IMM16_32",
            "R32_64",
            "RM32_64",
            "IMPLICIT_AX_EAX_RAX",
            "XMM_M128",
            "IMPLICIT_XMM0_YMM0_ZMM0",
            "XMM_YMM_ZMM"};
        public Form1()
        {
            InitializeComponent();

            opType1.Items.AddRange(PossibleOperandTypes);
            opType2.Items.AddRange(PossibleOperandTypes);
            opType3.Items.AddRange(PossibleOperandTypes);
            opType4.Items.AddRange(PossibleOperandTypes);

        }

        private void SaveBtn_Click(object sender, EventArgs e)
        {
            instructionInfoData.Text += "\n";
            if(prefixContext.Text == "" && instructionEnvironment.Text == "")
            {
                instructionInfoData.Text += "INSTRUCTION(" + instruction.Text.ToUpper() + "_STR, 0x" + opcode.Text.ToUpper() + "),";
            }
            else if (prefixContext.Text == "" && instructionEnvironment.Text != "")
            {
                instructionInfoData.Text += "INSTRUCTION_E(" + instruction.Text.ToUpper() + "_STR, 0x" + opcode.Text.ToUpper() + ", INSTRUCTION_ENVIRONMENT_" + instructionEnvironment.Text.ToUpper() + "),";
            }
            else if (prefixContext.Text != "" && instructionEnvironment.Text == "")
            {
                instructionInfoData.Text += "INSTRUCTION_P(" + instruction.Text.ToUpper() + "_STR, PREFIX_CONTEXT_" + prefixContext.Text.ToUpper() + ", 0x" + opcode.Text.ToUpper() + "),";
            }
            else if (prefixContext.Text != "" && instructionEnvironment.Text != "")
            {
                instructionInfoData.Text += "INSTRUCTION_PE(" + instruction.Text.ToUpper() + "_STR, PREFIX_CONTEXT_" + prefixContext.Text.ToUpper() + ", 0x" + opcode.Text.ToUpper() + ", INSTRUCTION_ENVIRONMENT_" + instructionEnvironment.Text.ToUpper() + "),";
            }



            operandEncodingData.Text += "\n";
            operandEncodingData.Text += "INSTRUCTION_OPERAND_ENCODING_" + operandEncoding.Text.ToUpper() + ",";


            operandData.Text += "\n";
            if(opType1.Text == "" && opType2.Text == "" && opType3.Text == "" && opType4.Text == "")
            {
                operandData.Text += "NO_OPERANDS,";
            }
            else if (opType2.Text == "" && opType3.Text == "" && opType4.Text == "")
            {
                operandData.Text += "_1_OPERANDS(OPERAND_TYPE_" + opType1.Text.ToUpper() + "),";
            }
            else if (opType3.Text == "" && opType4.Text == "")
            {
                operandData.Text += "_2_OPERANDS(OPERAND_TYPE_" + opType1.Text.ToUpper() + ", OPERAND_TYPE_" + opType2.Text.ToUpper() + "),";
            }
            else if (opType4.Text == "")
            {
                operandData.Text += "_3_OPERANDS(OPERAND_TYPE_" + opType1.Text.ToUpper() + ", OPERAND_TYPE_" + opType2.Text.ToUpper() + ", OPERAND_TYPE_" + opType3.Text.ToUpper() + "),";
            }
            else
            {
                operandData.Text += "_3_OPERANDS(OPERAND_TYPE_" + opType1.Text.ToUpper() + ", OPERAND_TYPE_" + opType2.Text.ToUpper() + ", OPERAND_TYPE_" + opType3.Text.ToUpper() + ", OPERAND_TYPE_" + opType4.Text.ToUpper() + "),";
            }
        }
    }
}
