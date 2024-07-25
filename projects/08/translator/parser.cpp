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
    using enum translator::commandType;
    static const std::unordered_set<std::string> arithmeticCommands({"add", "sub", "neg", "eq", "gt", "lt", "and",
                                                                     "or", "not"});
    const std::string trimmedCommand = boost::trim_copy(currentCommand);
    const std::string command = trimmedCommand.substr(0, trimmedCommand.find(' '));
    enum commandType commandType;
    if (arithmeticCommands.contains(command)) commandType = Arithmetic;
    else if (command == "push") commandType = Push;
    else if (command == "pop") commandType = Pop;
    else if (command == "label") commandType = Label;
    else if (command == "goto") commandType = Goto;
    else if (command == "if-goto") commandType = If;
    else if (command == "function") commandType = Function;
    else if (command == "return") commandType = Return;
    else if (command == "call") commandType = Call;
    else commandType = NonCommand;
    return commandType;
  }

  std::string parser::arg1() const {
    const enum commandType commandType = this->commandType();
    const std::string trimmedCommand = boost::trim_copy(currentCommand);
    std::string arg1;
    if (commandType == commandType::Arithmetic) {
      arg1 = trimmedCommand.substr(0, trimmedCommand.find_first_of(' '));
    } else {
      auto start = trimmedCommand.find_first_of(' ');
      auto end = trimmedCommand.find_first_of(' ', start + 1);
      arg1 = trimmedCommand.substr(start + 1, end - start - 1);
    }
    return arg1;
  }

  std::string parser::arg2() const {
    const std::string trimmedCommand = boost::trim_copy(currentCommand);
    std::basic_string<char>::size_type start = 0;
    for (int i = 0; i < 2; i++) start = trimmedCommand.find_first_of(' ', start + 1);
    return trimmedCommand.substr(start + 1, trimmedCommand.size() - trimmedCommand.find_first_of(' ', start + 1) - 1);
  }
}
