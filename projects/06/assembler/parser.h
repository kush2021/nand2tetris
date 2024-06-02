/**
 * Created by Kush Padalia on May 24, 2024
 */

#ifndef HACK_ASSEMBLER_PARSER_H
#define HACK_ASSEMBLER_PARSER_H

#include <string>
#include <fstream>
#include "commandType.h"

namespace assembler {

  /**
   * A parser for the assembler.
   *
   * Encapsulates access to the input code. Reads an assembly program and provides access to its components.
   */
  class parser {
  public:

    /**
     * Constructor for the class.
     *
     * @param fileName (str): The file name/path for the `.asm` program.
     */
    explicit parser(const std::string &fileName);

    /**
     * Destructor for the class. Closes the file stream.
     */
    virtual ~parser();

    /**
     * Checks if there are more commands in the input.
     *
     * @returns A Boolean representing whether there are more commands in the input file from the current line.
     */
    bool hasMoreCommands();

    /**
     * Get the currently set command.
     * @return The string representing the current command being parsed. Empty string if no command is set.
     */
    const std::string &getCurrentCommand() const;

    /**
     * Reads the next command from the file and makes it the current command.
     */
    void advance();

    /**
     * Checks the type of command that the current command is set to.
     *
     * @returns A `commandType` enumeration depending on which command is set.
     */
    assembler::commandType commandType() const;

    /**
     * Checks the symbol of the current command. Only works when the current command is an A or L command.
     *
     * @returns The string representing the symbol of the current command.
     */
    std::string symbol() const;

    /**
     * Checks the destination of the current command. Only works when the current command is a C command.
     *
     * @returns The string representing the `dest` mnemonic.
     */
    std::string dest() const;

    /**
     * Checks the computation of the current command. Only works when the current command is a C command.
     *
     * @returns The string representing the `comp` mnemonic.
     */
    std::string comp() const;

    /**
     * Checks the jump of the current command. Only works when the current command is a C command.
     *
     * @returns The string representing the `jump` mnemonic.
     */
    std::string jump() const;

    /**
     * Resets the file to the beginning.
     */
    void reset();

  private:
    std::ifstream file; // Input stream for the `.asm` program.
    std::string currentCommand; // The current command the parser is referencing.
  };

}

#endif //HACK_ASSEMBLER_PARSER_H
