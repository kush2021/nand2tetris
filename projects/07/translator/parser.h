/**
 * Created by Kush Padalia on June 3, 2024.
 *
 */

#ifndef TRANSLATOR_PARSER_H
#define TRANSLATOR_PARSER_H

#include <string>
#include <fstream>
#include <unordered_set>
#include "commandType.h"

namespace translator {

  /**
   * A parser for the translator.
   *
   * Responsible for parsing a single VM file and encapsulating access to the input code. Reads a VM program and
   * provides access to its components.
   */
  class parser {
  public:

    /**
     * Constructor for the class.
     *
     * @param fileName (std::string): The file name/path for the `.vm` program.
     */
    explicit parser(const std::string &fileName);

    /**
     * Destructor for the class. Closes the file stream.
     */
    virtual ~parser();

    /**
     * Checks if there are more commads in the input file.
     *
     * @returns A Boolean representing whether there are more commands in the input file.
     */
    bool hasMoreCommands();

    /**
     * Reads the next command from the file and makes it the current command. Only works when `hasMoreCommands`
     * returns `true`.
     */
    void advance();

    /**
     * Checks the type of the current VM command. `commandType::Arithmetic` is returned for all the arithmetic commands.
     *
     * @returns A `commandType` corresponding to the current VM command's type.
     */
    commandType commandType() const;

    /**
     * Returns the first argument of the current command. In the case of `commandType::Arithmetic`, the command
     * itself (`add`, `sub`, etc.) is returned. Should not be called if the current command is `commandType::Return`.
     *
     * @returns (`std::string`): The first argument of the current command.
     */
    std::string arg1() const;

    /**
     * Returns the second argument of the current command. Should be called only if the current command is
     * `commandType::Push`, `commandType::Pop`, `commandType::Function`, or `commandType::Call`.
     *
     * @returns (`std::string`): The second argument of the current command.
     */
    std::string arg2() const;

  private:
    std::ifstream file; //Input stream for the `.vm` program.
    std::string currentCommand; // The current command the parser is referencing.
  };
}

#endif //TRANSLATOR_PARSER_H
