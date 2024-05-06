"""
A parser for the assembler.

Responsible for parsing an input assembly language program and providing
convenient access to the commands used in the program.
"""

from . import utils
from typing import TextIO


class Parser:
  """
  A parser for the assembler.

  Encapsulates access to the input code. Reads an assembly propgram and
  provides access to its components.

  Attributes:
    filename (str): The filename/path of the assembly language file.
    file (TextIO): The text file that has been opened for reading.
    currentCommand (str): The current command of the assembly file.
  """

  def __init__(self, file: TextIO) -> None:
    """
    Initializes the parser based on an assembly file.

    Args:
      file (TextIO): The assembly file opened in read mode.
    """
    self._file = file
    self.currentCommand = None

  def hasMoreCommands(self) -> bool:
    """
    Checks if there are more commands in the input.

    Returns:
      A bool representing whether or not there are more commands in the input
      file from the current line. Note that whitespace and comments do not
      count.
    """
    return utils.peek(self._file)

  def advance(self) -> None:
    """
    Reads the next command from the file and makes it the current command. Only
    works when `hasMoreCommands` is true.
    """
    if self.hasMoreCommands():
      self.currentCommand = self._file.readline()
    else:
      self.currentCommand = None

  def commandType(self) -> utils.COMMAND_TYPE:
    """
    Checks the type of command that the current command is set to.

    Returns a `COMMAND_TYPE` enumeration depending on which command is set.
    """
    if not self.currentCommand:
      return utils.COMMAND_TYPE.NON_COMMAND
    elif self.currentCommand.strip() == "":
      return utils.COMMAND_TYPE.NON_COMMAND
    elif self.currentCommand.strip()[0] == '@':
      return utils.COMMAND_TYPE.A_COMMAND
    elif self.currentCommand[0] == '(':
      return utils.COMMAND_TYPE.L_COMMAND
    elif self.currentCommand.strip()[0] == '/':
      return utils.COMMAND_TYPE.NON_COMMAND
    return utils.COMMAND_TYPE.C_COMMAND

  def symbol(self) -> str:
    """
    Returns the symbol of the current command.

    Returns a string representing the symbol of the current command. Only works
    for A or L commands.
    """
    if not self.currentCommand:
      return
    commandType = self.commandType()
    line = self.currentCommand.strip()
    if commandType == utils.COMMAND_TYPE.A_COMMAND:
      return line[1:].strip()
    elif commandType == utils.COMMAND_TYPE.L_COMMAND:
      return line[1:-1]

  def dest(self) -> str:
    """
    Returns the destination of the current command.

    Returns a string representing the `dest` mnemonic. Only works for C
    commands.
    """
    i = self.currentCommand.find('=')
    if self.commandType() == utils.COMMAND_TYPE.C_COMMAND and i > 0:
      return self.currentCommand[:i].strip()
    return ""

  def comp(self) -> str:
    """
    Returns the computation of the current command.

    Returns a string representing the `comp` mnemonic. Only works for C
    commands.
    """
    if self.commandType() == utils.COMMAND_TYPE.C_COMMAND:
      i = self.currentCommand.find('=') + 1
      j = self.currentCommand.find(';')
      return self.currentCommand[i:j].strip()

  def jump(self) -> str:
    """
    Returns the jump of the current command.

    Returns a string representing the `jump` mnemonic. Only works for C
    commands.
    """
    if self.commandType() == utils.COMMAND_TYPE.C_COMMAND:
      i = self.currentCommand.find(';')
      if i != -1:
        return self.currentCommand[i + 1:].strip()
      return ""

  def reset(self) -> None:
    """
    Resets the file pointer to the beginning.
    """
    self._file.seek(0)
