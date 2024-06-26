/**
 * Created by Kush Padalia on May 25, 2024.
 */

#include "code.h"
#include <unordered_map>
#include <string>

namespace assembler {
  std::unordered_map<std::string, std::string> code::destConversions = {
      {"", "000"},
      {"null", "000"},
      {"M", "001"},
      {"D", "010"},
      {"MD", "011"},
      {"A", "100"},
      {"AM", "101"},
      {"AD", "110"},
      {"AMD", "111"}
  };

  std::unordered_map<std::string, std::string> code::jumpConversions = {
      {"", "000"},
      {"null", "000"},
      {"JGT", "001"},
      {"JEQ", "010"},
      {"JGE", "011"},
      {"JLT", "100"},
      {"JNE", "101"},
      {"JLE", "110"},
      {"JMP", "111"}
  };

  std::unordered_map<std::string, std::string> code::compConversions = {
      {"",    "0000000"},
      {"0",   "0101010"},
      {"1",   "0111111"},
      {"-1",  "0111010"},
      {"D",   "0001100"},
      {"A",   "0110000"},
      {"!D",  "0001101"},
      {"!A",  "0110001"},
      {"-D",  "0001111"},
      {"-A",  "0110011"},
      {"D+1", "0011111"},
      {"A+1", "0110111"},
      {"D-1", "0001110"},
      {"A-1", "0110010"},
      {"D+A", "0000010"},
      {"D-A", "0010011"},
      {"D&A", "0000000"},
      {"D|A", "0010101"},
      {"M",   "1110000"},
      {"!M",  "1110001"},
      {"-M",  "1110011"},
      {"M+1", "1110111"},
      {"M-1", "1110010"},
      {"D+M", "1000010"},
      {"D-M", "1010011"},
      {"M-D", "1000111"},
      {"D&M", "1000000"},
      {"D|M", "1010101"}
  };

  std::string code::dest(const std::string &mnemonic) {
    return destConversions[mnemonic];
  }

  std::string code::jump(const std::string &mnemonic) {
    return jumpConversions[mnemonic];
  }

  std::string code::comp(const std::string &mnemonic) {
    return compConversions[mnemonic];
  }
}
