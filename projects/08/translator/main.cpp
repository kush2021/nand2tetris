/**
* Created by Kush Padalia on June 9, 2024.
*/

#include <iostream>
#include <filesystem>
#include "parser.h"
#include "codeWriter.h"
#include "commandType.h"
#include <argparse/argparse.hpp>

namespace translator {

  /**
   * Sets up the argument parser.
   *
   * @param argumentParser (`argparse::ArgumentParser &`): The argument parser to set up.
   */
  void setupArgumentParser(argparse::ArgumentParser &argumentParser) {
    argumentParser.add_description("Translator for Hack VM files.");
    argumentParser.add_argument("directory")
        .help("Directory containing the VM files to translate.");
    argumentParser.add_argument("output")
        .help("Output file name.");
  }

  /**
   * Checks if a given file is a VM file.
   *
   * @param extension (`const std::string_view &`): The file to check.
   *
   * @returns A `bool` representing whether the file is a VM file.
   */
  bool isVmFile(const std::string_view &extension) {
    return extension == ".vm";
  }

  /**
   * Gets the VM files from the provided directory.
   *
   * @param directory (`const std::string &): The directory to search within.
   *
   * @returns A `std::vector<std::string>` representing the list of VM file paths.
   */
  std::vector<std::string> getVmFiles(const std::string &directory) {
    std::vector<std::string> vmFiles;
    for (const auto &file: std::filesystem::directory_iterator(directory)) {
      if (isVmFile(file.path().extension().string())) vmFiles.push_back(file.path().string());
    }
    return vmFiles;
  }

}

int main(int argc, char **argv) {
  argparse::ArgumentParser argumentParser("translator");
  translator::setupArgumentParser(argumentParser);
  try {
    argumentParser.parse_args(argc, argv);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    std::cerr << argumentParser << std::endl;
    return 1;
  }
  translator::codeWriter codeWriter(argumentParser.get("output"));
  codeWriter.writeInit();
  for (const auto &file: translator::getVmFiles(argumentParser.get("directory"))) {
    translator::parser parser(file);
    while (parser.hasMoreCommands()) {
      using enum translator::commandType;
      parser.advance();
      const enum translator::commandType commandType = parser.commandType();
      if (commandType == Arithmetic) codeWriter.writeArithmetic(parser.arg1());
      else if (commandType == Push || commandType == Pop)
        codeWriter.writePushPop(commandType, parser.arg1(),
                                std::stoi(parser.arg2()), file);
      else if (commandType == Label) codeWriter.writeLabel(parser.arg1());
      else if (commandType == Goto) codeWriter.writeGoto(parser.arg1());
      else if (commandType == If) codeWriter.writeIf(parser.arg1());
      else if (commandType == Function)
        codeWriter.writeFunction(parser.arg1(), std::stoi
            (parser.arg2()));
      else if (commandType == Return) codeWriter.writeReturn();
      else if (commandType == Call)
        codeWriter.writeCall(parser.arg1(), std::stoi(parser.arg2
            ()));
    }
  }
}
