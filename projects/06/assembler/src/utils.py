"""
A utility module for the assembler.

Contains various helpful functions and classes that will be used elsewhere in
the assembler.
"""

from typing import TextIO
from enum import Enum


class COMMAND_TYPE(Enum):
  """
  An enumeration representing assembly command types.

  Attributes
    A_COMMAND: Commands using `@Xxx` where `Xxx` is either a symbol or a
    decimal.
    C_COMMAND: Commands using `dest=comp;jump`.
    L_COMMAND: Commands using `(Xxx)` where `Xxx` is a symbol.
    Non-Command: Lines of whitespace or comments.
  """
  A_COMMAND = "A Command"
  C_COMMAND = "C Command"
  L_COMMAND = "L Command"
  NON_COMMAND = "Non-Command"


def peek(file: TextIO) -> str:
  """
  Peeks a line of a file without advancing the file position.

  Args:
    file (TextIO): The file that has been opened for reading.

  Returns:
    A string of the next line of the file.
  """
  pos = file.tell()
  line = file.readline()
  file.seek(pos)
  return line
