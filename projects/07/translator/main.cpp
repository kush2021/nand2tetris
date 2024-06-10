/**
* Created by Kush Padalia on June 9, 2024.
*/

#include <iostream>
#include "parser.h"
#include "codeWriter.h"
#include "commandType.h"


namespace translator {

  /**
   * Checks if the arguments are valid. Only one argument is accepted: the path to the VM file.
   *
   * @returns (`bool`): Whether the arguments are valid.
   */
  bool areArgsValid(int argc) {
    bool isValid = true;
    if (argc != 2) {
      std::cout << "Usage: ./translator file_name" << std::endl;
      std::cout << "The file name must be a path to the Hack VM program." << std::endl;
      isValid = false;
    }
    return isValid;
  }
}

int main(int argc, char **argv) {
  if (translator::areArgsValid(argc)) {
    translator::parser parser(argv[1]);
    translator::codeWriter codeWriter("test.asm");
    while (parser.hasMoreCommands()) {
      parser.advance();
      const enum translator::commandType commandType = parser.commandType();
      if (commandType == translator::commandType::Arithmetic) codeWriter.writeArithmetic(parser.arg1());
      else if (commandType == translator::commandType::Push)
        codeWriter.writePushPop(commandType, parser.arg1(),
                                std::stoi(parser.arg2()));
    }
  } else {
    return EXIT_FAILURE;
  }
}
