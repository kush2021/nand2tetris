/**
* Created by Kush Padalia on May 24, 2024
*/

#include <gtest/gtest.h>
#include "parser.h"
#include "code.h"
#include "symbolTable.h"

void advanceUntilEnd(assembler::parser &parser) {
  for (int i = 0; i < 24; i++) {
    parser.advance();
  }
}

class parserTest : public testing::Test {
protected:
  parserTest() : parser("/Users/kushpadalia/extracurriculars/nand2tetris/projects/06/assembler/test.asm") {}

  assembler::parser parser;
};

class codeTest : public testing::Test {
protected:
  codeTest() : code() {}

  assembler::code code;
};

class symbolTableTest : public testing::Test {
protected:
  symbolTableTest() : symbolTable() {}

  assembler::symbolTable symbolTable;
};

TEST_F(parserTest, hasMoreCommandsTest) {
  ASSERT_TRUE(parser.hasMoreCommands());
}

TEST_F(parserTest, hasNoMoreCommandsTest) {
  advanceUntilEnd(parser);
  ASSERT_FALSE(parser.hasMoreCommands());
}

TEST_F(parserTest, advanceTest) {
  parser.advance();
  ASSERT_EQ(parser.getCurrentCommand(), "@i");
  parser.advance();
  ASSERT_EQ(parser.getCurrentCommand(), "M=1");
}

TEST_F(parserTest, aCommandTest) {
  parser.advance();
  ASSERT_EQ(parser.commandType(), assembler::commandType::ACommand);
}

TEST_F(parserTest, cCommandTest) {
  parser.advance();
  parser.advance();
  ASSERT_EQ(parser.commandType(), assembler::commandType::CCommand);
}

TEST_F(parserTest, lCommandTest) {
  for (int i = 0; i < 5; i++) {
    parser.advance();
  }
  ASSERT_EQ(parser.commandType(), assembler::commandType::LCommand);
}

TEST_F(parserTest, nonCommandTest) {
  ASSERT_EQ(parser.commandType(), assembler::commandType::NonCommand);
  for (int i = 0; i < 6; i++) {
    parser.advance();
  }
  ASSERT_EQ(parser.commandType(), assembler::commandType::NonCommand);
}

TEST_F(parserTest, aSymbolTest) {
  parser.advance();
  ASSERT_EQ(parser.symbol(), "i");
}

TEST_F(parserTest, lSymbolTest) {
  for (int i = 0; i < 5; i++) {
    parser.advance();
  }
  ASSERT_EQ(parser.symbol(), "LOOP");
}

TEST_F(parserTest, noSymbolTest) {
  advanceUntilEnd(parser);
  ASSERT_EQ(parser.symbol(), "");
}

TEST_F(parserTest, destTest) {
  parser.advance();
  parser.advance();
  ASSERT_EQ(parser.dest(), "M");
}

TEST_F(parserTest, noDestTest) {
  parser.advance();
  ASSERT_EQ(parser.dest(), "");
}

TEST_F(parserTest, compTest) {
  parser.advance();
  parser.advance();
  ASSERT_EQ(parser.comp(), "1");
}

TEST_F(parserTest, noCompTest) {
  parser.advance();
  ASSERT_EQ(parser.comp(), "");
}

TEST_F(parserTest, jumpTest) {
  for (int i = 0; i < 12; i++) {
    parser.advance();
  }
  ASSERT_EQ(parser.jump(), "JGT");
}

TEST_F(parserTest, noJumpTest) {
  parser.advance();
  ASSERT_EQ(parser.jump(), "");
}

TEST_F(codeTest, destTest) {
  ASSERT_EQ(code.dest("AMD"), "111");
}

TEST_F(codeTest, jumpTest) {
  ASSERT_EQ(code.jump("JMP"), "111");
}

TEST_F(codeTest, compTest) {
  ASSERT_EQ(code.comp("D|M"), "1010101");
}

TEST_F(symbolTableTest, addEntryTest) {
  symbolTable.addEntry("TEST", 16);
  ASSERT_EQ(symbolTable.getAddress("TEST"), 16);
}

TEST_F(symbolTableTest, containsTest) {
  symbolTable.addEntry("TEST", 12);
  ASSERT_TRUE(symbolTable.contains("TEST"));
}

TEST_F(symbolTableTest, notContainsTest) {
  ASSERT_FALSE(symbolTable.contains("TEST"));
}

TEST_F(symbolTableTest, getAddressTest) {
  symbolTable.addEntry("TEST", 100);
  ASSERT_EQ(symbolTable.getAddress("TEST"), 100);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
