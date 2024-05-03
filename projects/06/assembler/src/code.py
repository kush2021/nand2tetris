"""
A conversion module for the assembler.


Responsible for translating Hack assembly language mnemonics into binary codes.
"""


class Code:
  """
  A conversion class for the assembler.

  Encapsulates access to the conversion mechanism for the assembler.

  Attributes
    destConversions (dict): A dictionary defining the mnemonic to binary
    conversions for the destination.
    jumpConversions (dict): A dictionary defining the mnemonic to binary
    conversions for the jump.
  """

  _destConversions = {
      "null": "000",
      "M": "001",
      "D": "010",
      "MD": "011",
      "A": "100",
      "AM": "101",
      "AD": "110",
      "AMD": "111"
  }

  _jumpConversions = {
      "null": "000",
      "JGT": "001",
      "JEQ": "010",
      "JGE": "011",
      "JLT": "100",
      "JNE": "101",
      "JLE": "110",
      "JMP": "111"
  }

  _compConversions = {
      "0": "0101010",
      "1": "0111111",
      "-1": "0111010",
      "D": "0001100",
      "A": "0110000",
      "!D": "0001101",
      "!A": "0110001",
      "-D": "0001111",
      "-A": "0110011",
      "D+1": "0011111",
      "A+1": "0110111",
      "D-1": "0001110",
      "A-1": "0110010",
      "D+A": "0000010",
      "D-A": "0010011",
      "D&A": "0000000",
      "D|A": "0010101",
      "M": "1110000",
      "!M": "1110001",
      "-M": "1110011",
      "M+1": "1110111",
      "M-1": "1110010",
      "D+M": "1000010",
      "D-M": "1010011",
      "M-D": "1000111",
      "D&M": "1000000",
      "D|M": "1010101"
  }

  def dest(self, mnemonic: str) -> str:
    """
    Converts the given destination mnemonic into binary.

    Args:
      mnemonic (str): The given destination mnemonic.

    Returns the binary equivalent as a string.
    """
    return self._destConversions[mnemonic]

  def jump(self, mnemonic: str) -> str:
    """
    Converts the given jump mnemonic into binary.

    Args:
      mnemonic (str): The given jump mnemonic.

    Returns the binary equivalent as a string.
    """
    return self._jumpConversions[mnemonic]

  def comp(self, mnemonic: str) -> str:
    """
    Converts the given computation mnemonic into binary.

    Args:
      mnemonic (str): The given computation mnemonic.

    Returns the binary equivalent as a string.
    """
    return self._compConversions[mnemonic]
