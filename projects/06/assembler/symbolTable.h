/**
 * Created by Kush Padalia on May 30, 2024
 */

#ifndef HACK_ASSEMBLER_SYMBOLTABLE_H
#define HACK_ASSEMBLER_SYMBOLTABLE_H

#include <string>
#include <unordered_map>

namespace assembler {

  /**
   * A symbol table for the assembler. Utilizes a hash map to maintain links between symbols and their memory addresses.
   */
  class symbolTable {
  public:

    explicit symbolTable();

    /**
     * Adds the pair `(symbol, address)` to the table.
     *
     * @param symbol (std::string): The symbol to add.
     * @param address (int): The address of the symbol.
     */
    void addEntry(const std::string &symbol, int address);

    /**
     * Checks whether or not a given symbol is in the table.
     *
     * @param symbol (std::string): The symbol to check for.
     *
     * @returns A Boolean representing the existence of `symbol` in the table.
     */
    [[nodiscard]] bool contains(const std::string &symbol) const;

    /**
     * Finds the address of a given symbol.
     *
     * @param symbol (std::string) The symbol to find the address for.
     *
     * @returns An integer representing the address of the symbol.
     */
    int getAddress(const std::string &symbol);

  private:
    std::unordered_map<std::string, int> symbolToAddress; // A hash map of symbols to addresses.

    /**
     * Initializes the symbol table.
     *
     * @returns A hash map representing the initial table with default symbols.
     */
    static std::unordered_map<std::string, int> initTable();
  };


}

#endif //HACK_ASSEMBLER_SYMBOLTABLE_H
