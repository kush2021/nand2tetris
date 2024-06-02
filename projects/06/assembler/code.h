/**
* Created by Kush Padalia on May 25, 2024.
*/

#ifndef HACK_ASSEMBLER_CODE_H
#define HACK_ASSEMBLER_CODE_H

#include <unordered_map>

namespace assembler {

  /**
   * A conversion class for the Hack assembler. Encapsulates access to the conversion mechanism for the assembler.
   */
  class code {
  public:

    /**
     * Converts the given destination mnemonic into binary.
     *
     * @param mnemonic (str): The destination mnemonic.
     *
     * @returns The binary equivalent as a string.
     */
    static std::string dest(const std::string &mnemonic);

    /**
     * Converts the given jump mnemonic into binary.
     *
     * @param mnemonic (str): The jump mnemonic.
     *
     * @returns The binary equivalent as a string.
     */
    static std::string jump(const std::string &mnemonic);

    /**
     * Converts the given computation mnemonic into binary.
     *
     * @param mnemonic (str): The computation mnemonic.
     *
     * @returns The binary equivalent as a string.
     */
    static std::string comp(const std::string &mnemonic);

  private:
    static std::unordered_map<std::string, std::string> destConversions; // A map defining the mnemonic to binary
    // conversions for the destination.
    static std::unordered_map<std::string, std::string> jumpConversions; // A map defining the mnemonic to binary
    // conversions for the jump.
    static std::unordered_map<std::string, std::string> compConversions; // A map defining the mnemonic to binary
    // conversions for the computation.
  };
}

#endif  //HACK_ASSEMBLER_CODE_H
