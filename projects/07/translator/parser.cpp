/**
 * Created by Kush Padalia on June 3, 2024.
 */

#include "parser.h"
#include <unordered_set>
#include <boost/algorithm/string.hpp>
#include <string>

namespace translator {


  parser::parser(const std::string &fileName) {
    file.open(fileName);
  }

  parser::~parser() {
    file.close();
  }

  bool parser::hasMoreCommands() {
    return file.peek() != EOF;
  }

  void parser::advance() {
    (void) std::getline(file, currentCommand);
  }

  commandType parser::commandType() const {
    static const std::unordered_set<std::string> arithmeticCommands({"add", "sub", "neg", "eq", "gt", "lt", "and",
                                                                     "or", "not"});
    const std::string trimmedCommand = boost::trim_copy(currentCommand);
    const std::string command = trimmedCommand.substr(0, trimmedCommand.find(' '));
    enum commandType commandType;
    if (arithmeticCommands.find(command) != arithmeticCommands.end()) commandType = commandType::Arithmetic;
    else if (command == "push") commandType = commandType::Push;
    else if (command == "pop") commandType = commandType::Pop;
    else if (command == "label") commandType = commandType::Label;
    else if (command == "goto") commandType = commandType::Goto;
    else if (command == "if-goto") commandType = commandType::If;
    else if (command == "function") commandType = commandType::Function;
    else if (command == "return") commandType = commandType::Return;
    else if (command == "call") commandType = commandType::Call;
    else commandType = commandType::NonCommand;
    return commandType;
  }

  std::string parser::arg1() const {
    const enum commandType commandType = this->commandType();
    const std::string trimmedCommand = boost::trim_copy(currentCommand);
    std::string arg1;
    if (commandType == commandType::Arithmetic) {
      arg1 = trimmedCommand;
    } else {
      auto start = trimmedCommand.find_first_of(' ');
      auto end = trimmedCommand.find_first_of(' ', start + 1);
      arg1 = trimmedCommand.substr(start + 1, end - start - 1);
    }
    return arg1;
  }

  std::string parser::arg2() const {
    const std::string trimmedCommand = boost::trim_copy(currentCommand);
    auto start = trimmedCommand.find_last_of(' ');
    return trimmedCommand.substr(start + 1);
  }
}
