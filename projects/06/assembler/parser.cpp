/**
 * Created by Kush Padalia on May 24, 2024
 */

#include "parser.h"
#include <iostream>
#include "commandType.h"
#include <boost/algorithm/string.hpp>

namespace assembler {
  parser::parser(const std::string &fileName) {
    file.open(fileName);
  }

  parser::~parser() {
    file.close();
  }

  void parser::advance() {
    (void) std::getline(file, currentCommand);
  }

  const std::string &parser::getCurrentCommand() const {
    return currentCommand;
  }

  assembler::commandType parser::commandType() const {
    const std::string trimmedCurrentCommand = boost::trim_copy(currentCommand);
    assembler::commandType commandType;
    if (const int i = 0; currentCommand.empty() || trimmedCurrentCommand.empty() || trimmedCurrentCommand[i] == '/') {
      commandType = assembler::commandType::NonCommand;
    } else if (trimmedCurrentCommand[i] == '@') {
      commandType = assembler::commandType::ACommand;
    } else if (trimmedCurrentCommand[i] == '(') {
      commandType = assembler::commandType::LCommand;
    } else {
      commandType = assembler::commandType::CCommand;
    }
    return commandType;
  }

  std::string parser::symbol() const {
    std::string symbol;
    assembler::commandType commandType = parser::commandType();
    std::string command = boost::trim_copy(currentCommand);
    if (commandType == assembler::commandType::ACommand) {
      symbol = boost::trim_copy(command.substr(1));
    } else if (commandType == assembler::commandType::LCommand) {
      symbol = command.substr(1, command.size() - 2);
    } else {
      symbol = "";
    }
    return symbol;
  }

  std::string parser::dest() const {
    std::basic_string<char>::size_type equalPos = currentCommand.find('=');
    std::string dest;
    if (parser::commandType() == assembler::commandType::CCommand && equalPos < currentCommand.size()) {
      dest = boost::trim_copy(currentCommand.substr(0, equalPos));
    } else {
      dest = "";
    }
    return dest;
  }

  std::string parser::comp() const {
    std::string comp;
    if (parser::commandType() == assembler::commandType::CCommand) {
      const size_t i = currentCommand.find('=') + static_cast<size_t>(1);
      const size_t j = currentCommand.find(';');
      comp = boost::trim_copy(currentCommand.substr(i, (j - i)));
    } else {
      comp = "";
    }
    return comp;
  }

  std::string parser::jump() const {
    std::string jump;
    if (parser::commandType() == assembler::commandType::CCommand) {
      const std::basic_string<char>::size_type i = currentCommand.find(';');
      jump = (i != -1) ? (boost::trim_copy(currentCommand.substr(i + 1))) :
             "";
    } else {
      jump = "";
    }
    return jump;
  }

  void parser::reset() {
    file.clear();
    (void) file.seekg(0);
  }

  bool parser::hasMoreCommands() {
    return file.peek() != EOF;
  }
}
