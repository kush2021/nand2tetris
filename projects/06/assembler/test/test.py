from ..src.parser import Parser
from ..src.utils import COMMAND_TYPE
from ..src.code import Code
from ..src.symbolTable import SymbolTable
import unittest

FILE_LEN = 24


class ParserTest(unittest.TestCase):
  file = None
  parser = None

  def setUp(self):
    self.file = open("assembler/test/test.asm", "r")
    self.parser = Parser(self.file)

  def tearDown(self):
    self.file.close()

  def testHasMoreCommands(self):
    self.assertTrue(self.parser.hasMoreCommands())

  def testHasNoMoreCommands(self):
    self.advanceUntilEnd()
    self.assertFalse(self.parser.hasMoreCommands())

  def testAdvance(self):
    self.assertIsNone(self.parser.currentCommand)
    self.parser.advance()
    self.assertEqual(self.parser.currentCommand, "@i\n")

  def testCannotAdvance(self):
    self.assertIsNone(self.parser.currentCommand)
    self.advanceUntilEnd()
    self.assertIsNone(self.parser.currentCommand)

  def testACommand(self):
    self.parser.advance()
    self.assertIsInstance(
        self.parser.commandType(),
        type(COMMAND_TYPE.A_COMMAND)
    )

  def testCCommand(self):
    self.parser.advance()
    self.parser.advance()
    self.assertIsInstance(
        self.parser.commandType(),
        type(COMMAND_TYPE.C_COMMAND)
    )

  def testLCommand(self):
    for _ in range(5):
      self.parser.advance()
    self.assertIsInstance(
        self.parser.commandType(),
        type(COMMAND_TYPE.L_COMMAND)
    )

  def testNonCommand1(self):
    for _ in range(6):
      self.parser.advance()
    self.assertIsInstance(
        self.parser.commandType(),
        type(COMMAND_TYPE.NON_COMMAND)
    )

  def testnonCommand2(self):
    self.assertIsInstance(
        self.parser.commandType(),
        type(COMMAND_TYPE.NON_COMMAND)
    )

  def testASymbol(self):
    self.parser.advance()
    self.assertEqual('i', self.parser.symbol())

  def testLSymbol(self):
    for _ in range(5):
      self.parser.advance()
    self.assertEqual("LOOP", self.parser.symbol())

  def testNoSymbol(self):
    self.advanceUntilEnd()
    self.assertIsNone(self.parser.symbol())

  def testDest(self):
    self.parser.advance()
    self.parser.advance()
    self.assertEqual('M', self.parser.dest())

  def testNoDest(self):
    self.parser.advance()
    self.assertEqual("", self.parser.dest())

  def testComp(self):
    self.parser.advance()
    self.parser.advance()
    self.assertEqual('1', self.parser.comp())

  def testNoComp(self):
    self.parser.advance()
    self.assertIsNone(self.parser.comp())

  def testJump(self):
    for _ in range(12):
      self.parser.advance()
    self.assertEqual('JGT', self.parser.jump())

  def testNoJump(self):
    self.parser.advance()
    self.assertIsNone(self.parser.jump())

  def advanceUntilEnd(self):
    for _ in range(FILE_LEN):
      self.parser.advance()


class CodeTest(unittest.TestCase):
  code = Code()

  def testDest(self):
    self.assertEqual("111", self.code.dest("AMD"))

  def testJump(self):
    self.assertEqual("111", self.code.jump("JMP"))

  def testComp(self):
    self.assertEqual("1010101", self.code.comp("D|M"))


class SymbolTableTest(unittest.TestCase):
  symbolTable = SymbolTable()

  def testAddEntry(self):
    self.symbolTable.addEntry("TEST", 100)
    self.assertEqual(self.symbolTable._symbolToAddress["TEST"], 100)

  def testContains(self):
    self.symbolTable.addEntry("TEST", 100)
    self.assertTrue(self.symbolTable.contains("TEST"))

  def testNotContains(self):
    self.assertFalse(self.symbolTable.contains("NON EXISTENT"))

  def testGetAddress(self):
    self.symbolTable._symbolToAddress["TEST"] = 100
    self.assertEqual(100, self.symbolTable.getAddress("TEST"))


if __name__ == "__main__":
  unittest.main()
