//
// Created by Kush Padalia on 2024-06-09.
//

#include <vector>
#include <format>
#include "codeWriter.h"

namespace translator {

  codeWriter::codeWriter(const std::string &fileName) {
    output = std::ofstream(fileName);
  }

  codeWriter::~codeWriter() {
    output.close();
  }

  void codeWriter::writeArithmetic(const std::string_view &command) {
    output << "@SP" << std::endl;
    output << "A=M-1" << std::endl;
    if (command == "neg") output << "M=-M" << std::endl;
    else if (command == "not") output << "M=!M" << std::endl;
    else {
      output << "D=M" << std::endl;
      output << "A=A-1" << std::endl;
      if (command == "add") output << "M=M+D" << std::endl;
      else if (command == "sub") output << "M=M-D" << std::endl;
      else if (command == "and") output << "M=M&D" << std::endl;
      else if (command == "or") output << "M=M|D" << std::endl;
      else {
        output << "D=M-D" << std::endl;
        output << "@JUMP_START_" << jumpCount << std::endl;
        if (command == "eq") output << "D;JEQ" << std::endl;
        else if (command == "gt") output << "D;JGT" << std::endl;
        else output << "D;JLT" << std::endl;
        output << "@SP" << std::endl;
        output << "D=M-1" << std::endl;
        output << "D=D-1" << std::endl;
        output << "A=D" << std::endl;
        output << "M=0" << std::endl;
        output << "@JUMP_END_" << jumpCount << std::endl;
        output << "0;JMP" << std::endl;
        output << "(JUMP_START_" << jumpCount << ")" << std::endl;
        output << "@SP" << std::endl;
        output << "D=M-1" << std::endl;
        output << "D=D-1" << std::endl;
        output << "A=D" << std::endl;
        output << "M=-1" << std::endl;
        output << "(JUMP_END_" << jumpCount << ")" << std::endl;
        jumpCount++;
      }
      output << "@SP" << std::endl;
      output << "M=M-1" << std::endl;
    }
  }

  void codeWriter::writePushPop(const commandType &command, const std::string_view &segment, const int &index,
                                const std::string_view &fileName) {
    const std::string_view parsedFileName = fileName.substr(fileName.find_last_of('/') + 1);
    if (command == commandType::Push) {
      this->writePush(segment, index, parsedFileName);
    } else {
      this->writePop(segment, index, parsedFileName);
    }
  }

  void codeWriter::writePush(const std::string_view &segment, const int &index, const std::string_view &fileName) {
    if (segment == "constant") {
      output << "@" << index << std::endl;
      output << "D=A" << std::endl;
    } else if (segment == "static" || segment == "temp") {
      if (segment == "static") output << "@" << fileName << '.' << index << std::endl;
      else output << "@" << (index + tempOffset) << std::endl;
      output << "D=M" << std::endl;
    } else if (segment == "pointer") {
      if (index) output << "@THAT" << std::endl;
      else output << "@THIS" << std::endl;
      output << "D=M" << std::endl;
    } else {
      if (segment == "argument") output << "@ARG" << std::endl;
      else if (segment == "this") output << "@THIS" << std::endl;
      else if (segment == "that") output << "@THAT" << std::endl;
      else output << "@LCL" << std::endl;
      output << "A=M" << std::endl;
      if (index) {
        for (int i = 0; i < index; i++) output << "A=A+1" << std::endl;
      }
      output << "D=M" << std::endl;
    }
    this->writePushEnd();
  }

  void codeWriter::writePop(const std::string_view &segment, const int &index, const std::string_view &fileName) {
    this->writePopStart();
    if (segment == "static") output << "@" << fileName << '.' << index << std::endl;
    else if (segment == "temp") output << "@" << (index + tempOffset) << std::endl;
    else if (segment == "pointer") {
      if (index) output << "@THAT" << std::endl;
      else output << "@THIS" << std::endl;
    } else {
      if (segment == "argument") output << "@ARG" << std::endl;
      else if (segment == "this") output << "@THIS" << std::endl;
      else if (segment == "that") output << "@THAT" << std::endl;
      else output << "@LCL" << std::endl;
      output << "A=M" << std::endl;
      if (index) {
        for (int i = 0; i < index; i++) output << "A=A+1" << std::endl;
      }
    }
    output << "M=D" << std::endl;
  }

  void codeWriter::writeInit() {
    this->initStack();
    this->writeCall("Sys.init", 0);
  }

  void codeWriter::initStack() {
    output << "@256" << std::endl;
    output << "D=A" << std::endl;
    output << "@SP" << std::endl;
    output << "M=D" << std::endl;
  }

  void codeWriter::writeLabel(const std::string_view &label) {
    output << "(" << label << ")" << std::endl;
  }

  void codeWriter::writeGoto(const std::string_view &label) {
    output << "@" << label << std::endl;
    output << "0;JMP" << std::endl;
  }

  void codeWriter::writeIf(const std::string_view &label) {
    this->writePopStart();
    output << "@" << label << std::endl;
    output << "// JUMPING" << std::endl;
    output << "D;JNE" << std::endl;
  }

  void codeWriter::writeCall(const std::string &functionName, const int &numArgs) {
    const std::string returnAddr = std::format("{}$return.{}", functionName, std::to_string(jumpCount));
    jumpCount++;
    output << "@" << returnAddr << std::endl;
    output << "D=A" << std::endl;
    this->writePushEnd();
    output << "@LCL" << std::endl;
    output << "D=M" << std::endl;
    this->writePushEnd();
    output << "@ARG" << std::endl;
    output << "D=M" << std::endl;
    this->writePushEnd();
    output << "@THIS" << std::endl;
    output << "D=M" << std::endl;
    this->writePushEnd();
    output << "@THAT" << std::endl;
    output << "D=M" << std::endl;
    this->writePushEnd();
    output << "@SP" << std::endl;
    output << "D=M" << std::endl;
    output << "@" << numArgs << std::endl;
    output << "D=D-A" << std::endl;
    output << "@5" << std::endl;
    output << "D=D-A" << std::endl;
    output << "@ARG" << std::endl;
    output << "M=D" << std::endl;
    output << "@SP" << std::endl;
    output << "D=M" << std::endl;
    output << "@LCL" << std::endl;
    output << "M=D" << std::endl;
    this->writeGoto(functionName);
    this->writeLabel(returnAddr);
  }

  void codeWriter::writePushEnd() {
    output << "@SP" << std::endl;
    output << "A=M" << std::endl;
    output << "M=D" << std::endl;
    output << "@SP" << std::endl;
    output << "M=M+1" << std::endl;
  }

  void codeWriter::writeReturn() {
    output << "@LCL" << std::endl;
    output << "D=M" << std::endl;
    output << "@R13" << std::endl;
    output << "M=D" << std::endl;
    output << "@5" << std::endl;
    output << "A=D-A" << std::endl;
    output << "D=M" << std::endl;
    output << "@R14" << std::endl;
    output << "M=D" << std::endl;
    this->writePopStart();
    output << "@ARG" << std::endl;
    output << "A=M" << std::endl;
    output << "M=D" << std::endl;
    output << "@ARG" << std::endl;
    output << "D=M+1" << std::endl;
    output << "@SP" << std::endl;
    output << "M=D" << std::endl;
    for (const std::vector<std::string> segments{"THAT", "THIS", "ARG", "LCL"}; const auto &segment: segments) {
      output << "@R13" << std::endl;
      output << "AM=M-1" << std::endl;
      output << "D=M" << std::endl;
      output << "@" << segment << std::endl;
      output << "M=D" << std::endl;
    }
    output << "@R14" << std::endl;
    output << "A=M" << std::endl;
    output << "0;JMP" << std::endl;
  }

  void codeWriter::writePopStart() {
    output << "@SP" << std::endl;
    output << "A=M-1" << std::endl;
    output << "D=M" << std::endl;
    output << "@SP" << std::endl;
    output << "M=M-1" << std::endl;
  }

  void codeWriter::writeFunction(const std::string_view &functionName, const int numLocals) {
    this->writeLabel(functionName);
    for (int i = 0; i < numLocals; i++) {
      this->writePush("constant", 0, "");
    }
  }
}
