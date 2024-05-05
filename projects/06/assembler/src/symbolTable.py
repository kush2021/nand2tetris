"""
A symbol table for the assembler.

Responsible for creating and maintaining correspondence between symbols and
their numeric addresses.
"""


class SymbolTable:
  """
  A symbol table for the assembler.

  Utilizes a hash map to maintain links between symbols and their memory
  addresses.

  Attributes:
    symbolToAddress (dict): A hash map of symbols to addresses.
  """

  _symbolToAddress = {
      "SP": 0,
      "LCL": 1,
      "ARG": 2,
      "THIS": 3,
      "THAT": 4,
      "R0": 0,
      "R1": 1,
      "R2": 2,
      "R3": 3,
      "R4": 4,
      "R5": 5,
      "R6": 6,
      "R7": 7,
      "R8": 8,
      "R9": 9,
      "R10": 10,
      "R11": 11,
      "R12": 12,
      "R13": 13,
      "R14": 14,
      "R15": 15,
      "SCREEN": 16384,
      "KBD": 24576
  }

  def addEntry(self, symbol: str, address: int) -> None:
    """
    Adds the pair `(symbol, address)` to the table.

    Args:
      symbol (str): The symbol to add.
      address (int): The address of the symbol.
    """
    self._symbolToAddress[symbol] = address

  def contains(self, symbol: str) -> bool:
    """
    Checks whether or not a given symbol is in the table.

    Args:
      symbol (str): The symbol to check for.

    Returns:
      A Boolean representing the existence of `symbol` in the table.
    """
    return symbol in self._symbolToAddress

  def getAddress(self, symbol: str) -> int:
    """
    Finds the address of a given symbol.

    Args:
      symbol (str): The symbol to find the address for.

    Returns:
      An integer value representing the address of the symbol.
    """
    return self._symbolToAddress[symbol]
