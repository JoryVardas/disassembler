namespace InstructionDataGen
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.opType1 = new System.Windows.Forms.ComboBox();
            this.opType2 = new System.Windows.Forms.ComboBox();
            this.opType3 = new System.Windows.Forms.ComboBox();
            this.opType4 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.operandEncoding = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.instructionEnvironment = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.prefixContext = new System.Windows.Forms.ComboBox();
            this.opcode = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.instruction = new System.Windows.Forms.TextBox();
            this.saveBtn = new System.Windows.Forms.Button();
            this.instructionInfoData = new System.Windows.Forms.RichTextBox();
            this.operandEncodingData = new System.Windows.Forms.RichTextBox();
            this.operandData = new System.Windows.Forms.RichTextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // opType1
            // 
            this.opType1.FormattingEnabled = true;
            this.opType1.Location = new System.Drawing.Point(129, 149);
            this.opType1.Name = "opType1";
            this.opType1.Size = new System.Drawing.Size(195, 21);
            this.opType1.TabIndex = 4;
            // 
            // opType2
            // 
            this.opType2.FormattingEnabled = true;
            this.opType2.Location = new System.Drawing.Point(129, 176);
            this.opType2.Name = "opType2";
            this.opType2.Size = new System.Drawing.Size(195, 21);
            this.opType2.TabIndex = 5;
            // 
            // opType3
            // 
            this.opType3.FormattingEnabled = true;
            this.opType3.Location = new System.Drawing.Point(129, 203);
            this.opType3.Name = "opType3";
            this.opType3.Size = new System.Drawing.Size(195, 21);
            this.opType3.TabIndex = 6;
            // 
            // opType4
            // 
            this.opType4.FormattingEnabled = true;
            this.opType4.Location = new System.Drawing.Point(129, 230);
            this.opType4.Name = "opType4";
            this.opType4.Size = new System.Drawing.Size(195, 21);
            this.opType4.TabIndex = 7;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(39, 152);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Operand 1 Type";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(39, 179);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(84, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Operand 2 Type";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(39, 206);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Operand 3 Type";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(39, 233);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(84, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Operand 4 Type";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(27, 110);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(96, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Operand Encoding";
            // 
            // operandEncoding
            // 
            this.operandEncoding.FormattingEnabled = true;
            this.operandEncoding.Items.AddRange(new object[] {
            "NA",
            "IMPLIED_AX_IMM",
            "R_RM",
            "RM_R",
            "RM_IMM",
            "R_VEC_RM",
            "R_RM_IMM",
            "R_RM_VEC",
            "R_RM_IMPLIED_ZMM0",
            "IMM"});
            this.operandEncoding.Location = new System.Drawing.Point(129, 107);
            this.operandEncoding.Name = "operandEncoding";
            this.operandEncoding.Size = new System.Drawing.Size(195, 21);
            this.operandEncoding.TabIndex = 3;
            this.operandEncoding.Text = "NA";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(5, 282);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(118, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "Instruction Environment";
            // 
            // instructionEnvironment
            // 
            this.instructionEnvironment.FormattingEnabled = true;
            this.instructionEnvironment.Items.AddRange(new object[] {
            "MODRM_REG_0",
            "MODRM_REG_1",
            "MODRM_REG_2",
            "MODRM_REG_3",
            "MODRM_REG_4",
            "MODRM_REG_5",
            "MODRM_REG_6",
            "MODRM_REG_7",
            "OPCODE_HAS_REG",
            "REQUIRES_PREFIX_66",
            "REQUIRES_PREFIX_67"});
            this.instructionEnvironment.Location = new System.Drawing.Point(129, 279);
            this.instructionEnvironment.Name = "instructionEnvironment";
            this.instructionEnvironment.Size = new System.Drawing.Size(195, 21);
            this.instructionEnvironment.TabIndex = 8;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(51, 77);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(72, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Prefix Context";
            // 
            // prefixContext
            // 
            this.prefixContext.FormattingEnabled = true;
            this.prefixContext.Items.AddRange(new object[] {
            "PREFIX_NOT_REQUIRED",
            "PREFIX_F0",
            "PREFIX_F2",
            "PREFIX_F3",
            "PREFIX_2E",
            "PREFIX_36",
            "PREFIX_3E",
            "PREFIX_26",
            "PREFIX_64",
            "PREFIX_65",
            "PREFIX_66",
            "PREFIX_67",
            "REX",
            "REX_W0",
            "REX_W1",
            "VEX",
            "VEX_W0",
            "VEX_W1",
            "VEX_IMPLIED_0F",
            "VEX_IMPLIED_0F38",
            "VEX_IMPLIED_0F3A",
            "VEX_128",
            "VEX_256",
            "EVEX",
            "EVEX_IMPLIED_0F",
            "EVEX_IMPLIED_0F38",
            "EVEX_IMPLIED_0F3A",
            "EVEX_W0",
            "EVEX_W1",
            "EVEX_128",
            "EVEX_256",
            "EVEX_512",
            "VEX_128_66_0F"});
            this.prefixContext.Location = new System.Drawing.Point(129, 69);
            this.prefixContext.Name = "prefixContext";
            this.prefixContext.Size = new System.Drawing.Size(195, 21);
            this.prefixContext.TabIndex = 2;
            // 
            // opcode
            // 
            this.opcode.Location = new System.Drawing.Point(129, 35);
            this.opcode.Name = "opcode";
            this.opcode.Size = new System.Drawing.Size(100, 20);
            this.opcode.TabIndex = 1;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(78, 38);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(45, 13);
            this.label8.TabIndex = 15;
            this.label8.Text = "Opcode";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(67, 9);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(56, 13);
            this.label9.TabIndex = 17;
            this.label9.Text = "Instruction";
            // 
            // instruction
            // 
            this.instruction.Location = new System.Drawing.Point(129, 6);
            this.instruction.Name = "instruction";
            this.instruction.Size = new System.Drawing.Size(100, 20);
            this.instruction.TabIndex = 0;
            // 
            // saveBtn
            // 
            this.saveBtn.Location = new System.Drawing.Point(8, 335);
            this.saveBtn.Name = "saveBtn";
            this.saveBtn.Size = new System.Drawing.Size(75, 23);
            this.saveBtn.TabIndex = 9;
            this.saveBtn.Text = "Save";
            this.saveBtn.UseVisualStyleBackColor = true;
            this.saveBtn.Click += new System.EventHandler(this.SaveBtn_Click);
            // 
            // instructionInfoData
            // 
            this.instructionInfoData.Location = new System.Drawing.Point(330, 35);
            this.instructionInfoData.Name = "instructionInfoData";
            this.instructionInfoData.Size = new System.Drawing.Size(195, 323);
            this.instructionInfoData.TabIndex = 18;
            this.instructionInfoData.Text = "";
            // 
            // operandEncodingData
            // 
            this.operandEncodingData.Location = new System.Drawing.Point(531, 35);
            this.operandEncodingData.Name = "operandEncodingData";
            this.operandEncodingData.Size = new System.Drawing.Size(195, 323);
            this.operandEncodingData.TabIndex = 19;
            this.operandEncodingData.Text = "";
            // 
            // operandData
            // 
            this.operandData.Location = new System.Drawing.Point(732, 35);
            this.operandData.Name = "operandData";
            this.operandData.Size = new System.Drawing.Size(195, 323);
            this.operandData.TabIndex = 20;
            this.operandData.Text = "";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(376, 9);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(100, 13);
            this.label10.TabIndex = 21;
            this.label10.Text = "InstructionInfo Data";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(572, 9);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(122, 13);
            this.label11.TabIndex = 22;
            this.label11.Text = "Operand Encoding Data";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(803, 9);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(74, 13);
            this.label13.TabIndex = 23;
            this.label13.Text = "Operand Data";
            // 
            // Form1
            // 
            this.AcceptButton = this.saveBtn;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(955, 369);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.operandData);
            this.Controls.Add(this.operandEncodingData);
            this.Controls.Add(this.instructionInfoData);
            this.Controls.Add(this.saveBtn);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.instruction);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.opcode);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.prefixContext);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.instructionEnvironment);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.operandEncoding);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.opType4);
            this.Controls.Add(this.opType3);
            this.Controls.Add(this.opType2);
            this.Controls.Add(this.opType1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox opType1;
        private System.Windows.Forms.ComboBox opType2;
        private System.Windows.Forms.ComboBox opType3;
        private System.Windows.Forms.ComboBox opType4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox operandEncoding;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox instructionEnvironment;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox prefixContext;
        private System.Windows.Forms.TextBox opcode;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox instruction;
        private System.Windows.Forms.Button saveBtn;
        private System.Windows.Forms.RichTextBox instructionInfoData;
        private System.Windows.Forms.RichTextBox operandEncodingData;
        private System.Windows.Forms.RichTextBox operandData;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label13;
    }
}

