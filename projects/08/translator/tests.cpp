/**
* Created by Kush Padalia on Jube 3, 2024.
*/

#include <gtest/gtest.h>
#include "parser.h"
#include "commandType.h"

class parserTest : public testing::Test {
protected:
  parserTest() : parser("/Users/kushpadalia/extracurriculars/nand2tetris/projects/07/translator/test.vm") {}

  translator::parser parser;
};

TEST_F(parserTest, hasMoreCommandsTest) {
  ASSERT_TRUE(parser.hasMoreCommands());
}

TEST_F(parserTest, hasNoMoreCommandsTest) {
  while (parser.hasMoreCommands()) {
    parser.advance();
  }
  ASSERT_FALSE(parser.hasMoreCommands());
}

TEST_F(parserTest, arithemticCommandTest) {
  for (int i = 0; i < 12; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Arithmetic);
}

TEST_F(parserTest, pushCommandTest) {
  for (int i = 0; i < 3; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Push);
}

TEST_F(parserTest, popCommandTest) {
  for (int i = 0; i < 5; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Pop);
}

TEST_F(parserTest, labelCommandTest) {
  for (int i = 0; i < 9; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Label);
}

TEST_F(parserTest, gotoCommandTest) {
  for (int i = 0; i < 25; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Goto);
}

TEST_F(parserTest, ifCommandTest) {
  for (int i = 0; i < 14; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::If);
}

TEST_F(parserTest, functionCommandTest) {
  for (int i = 0; i < 2; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Function);
}

TEST_F(parserTest, returnCommandTest) {
  for (int i = 0; i < 29; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Return);
}

TEST_F(parserTest, callCommandTest) {
  for (int i = 0; i < 30; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::Call);
}

TEST_F(parserTest, nonCommandTest) {
  for (int i = 0; i < 1; i++) parser.advance();
  ASSERT_EQ(parser.commandType(), translator::commandType::NonCommand);
}

TEST_F(parserTest, arithmeticArg1Test) {
  for (int i = 0; i < 12; i++) parser.advance();
  ASSERT_EQ(parser.arg1(), "eq");
}

TEST_F(parserTest, oneArg1Test) {
  for (int i = 0; i < 25; i++) parser.advance();
  ASSERT_EQ(parser.arg1(), "loop");
}

TEST_F(parserTest, twoarg1Test) {
  for (int i = 0; i < 2; i++) parser.advance();
  ASSERT_EQ(parser.arg1(), "mult");
}

TEST_F(parserTest, arg2Test) {
  for (int i = 0; i < 2; i++) parser.advance();
  ASSERT_EQ(parser.arg2(), "2");
}
