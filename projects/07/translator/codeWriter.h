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
     * @param fileName (`const std::string`): The file name to open for writing.
     */
    explicit codeWriter(const std::string &fileName);

    /**
     * Closes the output file/stream.
     */
    virtual ~codeWriter();

    /**
     * Writes the assembly code that is the translation of the given arithmetic command.
     *
     * @param command (`const std::string`): The arithmetic command to translate.
     */
    void writeArithmetic(const std::string_view &command);

    /**
     * Writes the assembly code that is the translation of the given `command`, where `command` is either
     * `commandType::Push` or `commandType::Pop`.
     *
     * @param command (`const commandType`): The type of command.
     * @param segment (`const std::string`): The segment of memory.
     * @param index (`const int`): The index of memory.
     * @param (`const std::string fileName`): The current VM file name.
     */
    void writePushPop(const commandType &command, const std::string_view &segment, const int &index,
                      const std::string_view &fileName);

  private:
    std::ofstream output; // Output file.
    int jumpCount = 0; // Arithmetic jump counter.
    static const int tempOffset = 5;

    /**
     * Writes the assembly code that pushes the value of `segment[index]` onto the stack.
     *
     * @param segment (`const std::string_view`): The segment of memory.
     * @param index (`const int`): The index of memory.
     * @param fileName (`const std::string fileName`): The current VM file name.
     */
    void writePush(const std::string_view &segment, const int &index, const std::string_view &fileName);

    /**
     * Writes the assembly code that pops the value of the stack into `segment[index]`.
     *
     * @param segment (`const std::string_view`): The segment of memory.
     * @param index (`const int`): The index of memory.
     * @param fileName (`const std::string fileName`): The current VM file name.
     */
    void writePop(const std::string_view &segment, const int &index, const std::string_view &fileName);
  };

}


#endif //TRANSLATOR_CODEWRITER_H
