"""
A utility module for the translator.

Contains various helpful functions and classes that will be used elsewhere in the translator.
"""

from enum import Enum


class CommandType(Enum):
    """
    An enumeration representing VM command types.

    Attributes:
      - C_ARITHMETIC: A command that performs arithmetic or logical operations.
      - C_PUSH: A command that pushes a value.
      - C_POP: A command that pops a value.
      - C_LABEL: A command that represents a label declaration.
      - C_GOTO: A command that results in an unconditional branch.
      - C_IF: A command that results in a conditional branch.
      - C_FUNCTION: A command that represents a function declaration.
      - C_RETURN: A command that transfers control to the calling function.
      - C_CALL: A command that calls a function.
      - C_NON_COMMAND: Anything that isn't one of the above commands.
    """

    C_ARITHMETIC = "arithmetic"
    C_PUSH = "push"
    C_POP = "pop"
    C_LABEL = "label"
    C_GOTO = "goto"
    C_IF = "if"
    C_FUNCTION = "function"
    C_RETURN = "return"
    C_CALL = "call"
    C_NON_COMMAND = "non-command"