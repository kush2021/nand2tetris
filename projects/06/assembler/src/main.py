"""
This file will convert a given Hack assembly lanuage program into Hack machine
code.

It will utilize the Parser and Code modules to complete this task.

Args:
  sys.argv[1]: The name/path to the Hack assembly language program.
"""


import sys
from . import utils
from .parser import Parser
from .code import Code
from typing import TextIO


def main():
  if areArgsValid():
    inputFile = open(sys.argv[1], "r")
    outputFile = open(parseOutputFileName(), "w")
    parser = Parser(inputFile)
    code = Code()
    while parser.hasMoreCommands():
      convertLine(parser, code, outputFile)
    inputFile.close()
    outputFile.close()


def areArgsValid() -> bool:
  """
  Checks if the arguments are valid. Only one argument is accepted: the path to
  the assembly file.

  Returns true if the arguments are valid. False otherwise.
  """
  if len(sys.argv) != 2:
    print("Exactly one argument is required.")
    print("Please supply the filepath to the assembly program.")
    return False
  return True


def parseOutputFileName() -> str:
  """
  Creates the output file name based on the input file. For example, "prog.asm"
  will become "prog.hack".

  Returns a string representing the output file name.
  """
  return sys.argv[1].replace(".asm", ".hack")


def convertLine(parser: Parser, code: Code, output: TextIO) -> None:
  """
  Converts the next line in the input file to binary code.

  Args:
    parser (Parser): The parser for the input file.
    code (Code): The conversion module for the Hack language.
    output (TextIO): The output file to write to.
  """
  parser.advance()
  conversion = ""
  if parser.commandType() == utils.COMMAND_TYPE.NON_COMMAND:
    return
  elif parser.commandType() == utils.COMMAND_TYPE.C_COMMAND:
    conversion = convertCCommand(parser, code, output)
  elif parser.commandType() == utils.COMMAND_TYPE.A_COMMAND:
    conversion = convertACommand(parser, code, output)
  output.write(conversion + '\n')


def convertCCommand(parser: Parser, code: Code, output: TextIO) -> str:
  """
  Converts the C command to its binary equivalent.

  Args:
    parser (Parser): The parser for the input file.
    code (Code): The conversion module for the Hack language.
    output (TextIO): The output file to write to.

  Returns the 16-bit binary string.
  """
  return (
      "111"
      + code.comp(parser.comp())
      + code.dest(parser.dest())
      + code.jump(parser.jump())
  )


def convertACommand(parser: Parser, code: Code, output: TextIO) -> str:
  """
  Converts the A command to its binary equivalent.

  Args:
    parser (Parser): The parser for the input file.
    code (Code): The conversion module for the Hack language.
    output (TextIO): The output file to write to.

  Returns the 16-bit binary string.
  """
  return format(int(parser.symbol()), "016b")


if __name__ == "__main__":
  main()
