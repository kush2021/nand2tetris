/**
* Created by Kush Padalia on May 24, 2024
*/

#include <iostream>
#include <regex>
#include <fstream>
#include <bitset>
#include "parser.h"
#include "symbolTable.h"
#include "code.h"

namespace assembler {

  /**
   * Checks if a string is a number.
   *
   * @param s (std::string_view): The string to check.
   *
   * @returns A Boolean representing whether the string is a number.
   */
  bool isNumber(const std::string_view &s) {
    auto it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
  }

  /**
   * Checks if the arguments are valid. Only one argument is accepted: the path to the assembly file.
   *
   * @returns A Boolean representing the validity of the input argument.
   */
  bool areArgsValid(int argc) {
    bool isValid = true;
    if (argc != 2) {
      std::cout << "Usage: ./hack_assembler file_name" << std::endl;
      std::cout << "The file name must be a path to the hack assembly program." << std::endl;
      isValid = false;
    }
    return isValid;
  }

  /**
   * Creates the output file name based on the input file. For example, `prog.asm` will become `prog.hack`.
   *
   * @param inputFileName (std::string): The input file name.
   *
   * @returns An output file name.
   */
  std::string parseOutputFileName(const std::string &inputFileName) {
    return std::regex_replace(inputFileName, std::regex("\\.asm"), ".hack"); // NOLINT(clion-misra-cpp2008-2-13-1)
  }

  /**
   * Completes a first pass of the input program and initializes a symbol table.
   *
   * @param symbolTable (symbolTable): The symbol table to initialize.
   * @param parser (parser): The parser for the input file.
   */
  void initSymbolTable(symbolTable &symbolTable, parser &parser) {
    int rom = -1;
    while (parser.hasMoreCommands()) {
      parser.advance();
      const commandType commandType = parser.commandType();
      if (commandType == commandType::CCommand || commandType == commandType::ACommand) rom++;
      else if (commandType == commandType::LCommand) symbolTable.addEntry(parser.symbol(), rom + 1);
    }
    parser.reset();
  }

  /**
   * Converts the C command to its binary equivalent.
   *
   * @param parser (parser): The parser for the input file.
   * @param code (code): The conversion module for the Hack language.
   *
   * @returns The compiled machine code for the C command as a string.
   */
  std::string convertCCommand(const parser &parser) {
    return "111" + code::comp(parser.comp()) + code::dest(parser.dest()) + code::jump(parser.jump());
  }

  /**
   * Converts the A command to its binary equivalent.
   *
   * @param parser (parser): The parser for the input file.
   * @param symbolTable (symbolTable): The symbol table for the input file.
   * @param nextRamAddr (int): The next RAM address for new symbols.
   */
  std::string convertACommand(const parser &parser, symbolTable &symbolTable, int &nextRamAddr) {
    const std::string symbol = parser.symbol();
    std::string conversion;
    if (isNumber(symbol)) conversion = std::bitset<16>(std::stoi(symbol)).to_string();
    else {
      if (!symbolTable.contains(symbol)) {
        symbolTable.addEntry(symbol, nextRamAddr);
        nextRamAddr++;
      }
      conversion = std::bitset<16>(symbolTable.getAddress(symbol)).to_string();
    }
    return conversion;
  }

/**
   * Converts the next line in the input file to binary code.
   *
   * @param parser (parser): The parser for the input file.
   * @param symbolTable (symbolTable): The symbol table for the input file.
   * @param output (std::ofstream): The output file to write to.
   * @param nextRamAddr (int): The next RAM address for new symbols.
   */
  void convertLine(parser &parser, symbolTable &symbolTable, std::ofstream &output, int &nextRamAddr) {
    parser.advance();
    if (const commandType commandType = parser.commandType(); commandType != commandType::NonCommand &&
                                                              commandType != commandType::LCommand) {
      std::string conversion;
      if (commandType == commandType::CCommand) conversion = convertCCommand(parser);
      else if (commandType == commandType::ACommand) conversion = convertACommand(parser, symbolTable, nextRamAddr);
      output << conversion << std::endl;
    }
  }
}

/**
 * Driver code to run the assembler.
 */
int main(int argc, char **argv) {
  if (assembler::areArgsValid(argc)) {
    const std::string input = argv[1];
    std::ofstream output(assembler::parseOutputFileName(input));
    assembler::parser parser(input);
    assembler::symbolTable symbolTable;
    assembler::initSymbolTable(symbolTable, parser);
    int nextRamAddr = 16;
    while (parser.hasMoreCommands()) assembler::convertLine(parser, symbolTable, output, nextRamAddr);
    output.close();
  } else {
    return EXIT_FAILURE;
  }
}

