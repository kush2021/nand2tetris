//
// Created by Kush Padalia on 2024-06-09.
//

#include <iostream>
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

  void codeWriter::writePushPop(const commandType &command, const std::string_view &segment, const int &index) {
    if (command == commandType::Push && segment == "constant") {
      output << "@" << index << std::endl;
      output << "D=A" << std::endl;
      output << "@SP" << std::endl;
      output << "A=M" << std::endl;
      output << "M=D" << std::endl;
      output << "@SP" << std::endl;
      output << "M=M+1" << std::endl;
    }
  }
}
