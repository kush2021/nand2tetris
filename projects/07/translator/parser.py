"""
A parser for the translator.

Responsible for parsing a single VM file and encapsulating access to the input code. It reads VM commands,
parses them, and provides convenient access to their components. In addition, it removes all white space and comments
It reads VM commands, parses them, and provides convenient access to their components. In addition, it removes all
white space and comments.
"""

from typing import TextIO


class Parser:
    """
    A parser for the translator.

    Encapsulates access to the input code. Reads a VM program and provides access to its components.

    Attributes:
      - file (TextIO): The input VM file that has been opened with read permissions.
    """

    def __init__(self, file: TextIO) -> None:
        """
        Initializes the parser using an input file.

        Args:
          - file (TextIO): The assembly file opened in read mode.
        """
        self._file = file
        self._current_command = None

    def has_more_commands(self) -> bool:
        """
        Checks if there are more commands in the input file.

        Returns:
          A Boolean representing whether there are more commands in the input file.
        """
        pos = self._file.tell()
        next_line = bool(self._file.readline())
        self._file.seek(pos)
        return next_line

    def advance(self) -> None:
        """
        Reads the next command from the file and makes it the current command. Only works when `has_more_commands` is
        true.
        """
        if self.has_more_commands():
            self._current_command = self._file.readline()
        else:
            self._current_command = None