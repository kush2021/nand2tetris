/**
 * Created by Kush Padalia on June 9, 2024.
 */

#ifndef TRANSLATOR_CODEWRITER_H
#define TRANSLATOR_CODEWRITER_H

#include <string>
#include <fstream>
#include "commandType.h"

namespace translator {

  /**
   * Translates VM commands into Hack assembly code.
   */
  class codeWriter {
  public:

    /**
     * Opens the output file/stream and gets ready to write into it.
     *
     * @param fileName (`std::string`): The file name to open for writing.
     */
    explicit codeWriter(const std::string &fileName);

    /**
     * Closes the output file/stream.
     */
    virtual ~codeWriter();

    /**
     * Writes the assembly code that is the translation of the given arithmetic command.
     *
     * @param command (`std::string`): The arithmetic command to translate.
     */
    void writeArithmetic(const std::string_view &command);

    /**
     * Writes the assembly code that is the translation of the given `command`, where `command` is either
     * `commandType::Push` or `commandType::Pop`.
     *
     * @param command (`commandType`): The type of command.
     * @param segment (`std::string`): The segment of memory.
     * @param index (`int`): The index of memory.
     */
    void writePushPop(const commandType &command, const std::string_view &segment, const int &index);

  private:
    std::ofstream output; // Output file.
    int jumpCount = 0; // Arithmetic jump counter.
  };

}


#endif //TRANSLATOR_CODEWRITER_H
