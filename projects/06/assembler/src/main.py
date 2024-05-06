"""
This file will convert a given Hack assembly lanuage program into Hack machine
code.

It will utilize the Parser and Code modules to complete this task.

Args:
  sys.argv[1]: The name/path to the Hack assembly language program.
"""


import sys
from typing import TextIO
from . import utils
from .parser import Parser
from .code import Code
from .symbolTable import SymbolTable


nextRAMAddr = 16


def main():
  if areArgsValid():
    inputFile = open(sys.argv[1], "r")
    outputFile = open(parseOutputFileName(), "w")
    parser = Parser(inputFile)
    symbolTable = SymbolTable()
    code = Code()
    initSymbolTable(symbolTable, parser)
    while parser.hasMoreCommands():
      convertLine(parser, code, symbolTable, outputFile)
    inputFile.close()
    outputFile.close()


def areArgsValid() -> bool:
  """
  Checks if the arguments are valid. Only one argument is accepted: the path to
  the assembly file.

  Returns:
    A Boolean representing the validity of the input arguments.
  """
  if len(sys.argv) != 2:
    print("Exactly one argument is required.")
    print("Please supply the filepath to the assembly program.")
    return False
  return True


def initSymbolTable(symbolTable: SymbolTable, parser: Parser) -> None:
  """
  Completes a first pass of the input program and initializes a symbol table.

  Args:
    symbolTable (SymbolTable): The symbol table to initialize.
    parser (Parser): The parser for the input file.
  """
  rom = -1
  while parser.hasMoreCommands():
    parser.advance()
    if parser.commandType() in [
        utils.COMMAND_TYPE.C_COMMAND,
        utils.COMMAND_TYPE.A_COMMAND
    ]:
      rom += 1
    elif parser.commandType() == utils.COMMAND_TYPE.L_COMMAND:
      symbolTable.addEntry(parser.symbol(), rom + 1)
  parser.reset()


def parseOutputFileName() -> str:
  """
  Creates the output file name based on the input file. For example, "prog.asm"
  will become "prog.hack".

  Returns:
    An output file name.
  """
  return sys.argv[1].replace(".asm", ".hack")


def convertLine(
    parser: Parser,
    code: Code,
    symbolTable: SymbolTable,
    output: TextIO
) -> None:
  """
  Converts the next line in the input file to binary code.

  Args:
    parser (Parser): The parser for the input file.
    code (Code): The conversion module for the Hack language.
    symbolTable (SymbolTable): The symbol table for the input file.
    output (TextIO): The output file to write to.
  """
  parser.advance()
  conversion = ""
  if parser.commandType() == utils.COMMAND_TYPE.NON_COMMAND:
    return
  elif parser.commandType() == utils.COMMAND_TYPE.L_COMMAND:
    return
  elif parser.commandType() == utils.COMMAND_TYPE.C_COMMAND:
    conversion = convertCCommand(parser, code, output)
  elif parser.commandType() == utils.COMMAND_TYPE.A_COMMAND:
    conversion = convertACommand(parser, code, symbolTable, output)
  output.write(conversion + '\n')


def convertCCommand(parser: Parser, code: Code, output: TextIO) -> str:
  """
  Converts the C command to its binary equivalent.

  Args:
    parser (Parser): The parser for the input file.
    code (Code): The conversion module for the Hack language.
    output (TextIO): The output file to write to.

  Returns:
    The compiled machine code for the C command.
  """
  return (
      "111"
      + code.comp(parser.comp())
      + code.dest(parser.dest())
      + code.jump(parser.jump())
  )


def convertACommand(
    parser: Parser,
    code: Code,
    symbolTable: SymbolTable,
    output: TextIO
) -> str:
  """
  Converts the A command to its binary equivalent.

  Args:
    parser (Parser): The parser for the input file.
    code (Code): The conversion module for the Hack language.
    symbolTable (SymbolTable): The symbol table for the input file.
    output (TextIO): The output file to write to.

  Returns:
    The compiled machine code for the A command.
  """
  symbol = parser.symbol()
  if symbol.isdigit():
    return format(int(parser.symbol()), "016b")
  if not symbolTable.contains(symbol):
    global nextRAMAddr
    symbolTable.addEntry(symbol, nextRAMAddr)
    nextRAMAddr += 1
  return format(symbolTable.getAddress(symbol), "016b")


if __name__ == "__main__":
  main()
