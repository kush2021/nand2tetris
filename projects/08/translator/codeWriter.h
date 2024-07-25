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
     * @param fileName (`const std::string &`): The file name to open for writing.
     */
    explicit codeWriter(const std::string &fileName);

    /**
     * Closes the output file/stream.
     */
    virtual ~codeWriter();

    /**
     * Writes the assembly code that is the translation of the given arithmetic command.
     *
     * @param command (`const std::string &`): The arithmetic command to translate.
     */
    void writeArithmetic(const std::string_view &command);

    /**
     * Writes the assembly code that is the translation of the given `command`, where `command` is either
     * `commandType::Push` or `commandType::Pop`.
     *
     * @param command (`const commandType &`): The type of command.
     * @param segment (`const std::string &`): The segment of memory.
     * @param index (`const int &`): The index of memory.
     * @param fileName (`const std::string fileName &`): The current VM file name.
     */
    void writePushPop(const commandType &command, const std::string_view &segment, const int &index,
                      const std::string_view &fileName);

    /**
     * Writes the assembly code that effects the VM initialization, also called bootstrap code. This code is placed at the beginning of the output file.
     */
    void writeInit();

    /**
     * Writes the assembly code that effects the `label` command.
     *
     * @param label (`const std::string_view &`): The label to create.
     */
    void writeLabel(const std::string_view &label);

    /**
     * Writes the assembly code that effects the `goto` command.
     *
     * @param label (`const std::string_view &`): The label to branch to.
     */
    void writeGoto(const std::string_view &label);

    /**
     * Writes the assembly code that effects the `if-goto` command.
     *
     * @param label (`const std::string_view &`): The label to conditionally branch to.
     */
    void writeIf(const std::string_view &label);

    /**
     * Writes the assembly code that effects the `call` command.
     *
     * @param functionName (`const std::string &`): The function to call.
     * @param numArgs (`const int &`): The number of arguments being supplied to the function.
     */
    void writeCall(const std::string &functionName, const int &numArgs);

    /**
     * Writes the assembly code that effects the `return` command.
     */
    void writeReturn();

    /**
     * Writes the assembly code that effects the `function` command.
     *
     * @param functionName (`const std::string_view &`): The function to call.
     * @param numLocals (`const int &`): The number of arguments for the function.
     */
    void writeFunction(const std::string_view &functionName, const int numLocals);

  private:
    std::ofstream output; // Output file.
    int jumpCount = 0; // Arithmetic jump counter.
    static const int tempOffset = 5;

    /**
     * Writes the assembly code that pushes the value of `segment[index]` onto the stack.
     *
     * @param segment (`const std::string_view &`): The segment of memory.
     * @param index (`const int &`): The index of memory.
     * @param fileName (`const std::string fileName &`): The current VM file name.
     */
    void writePush(const std::string_view &segment, const int &index, const std::string_view &fileName);

    /**
     * Writes the assembly code that pops the value of the stack into `segment[index]`.
     *
     * @param segment (`const std::string_view &`): The segment of memory.
     * @param index (`const int &`): The index of memory.
     * @param fileName (`const std::string fileName &`): The current VM file name.
     */
    void writePop(const std::string_view &segment, const int &index, const std::string_view &fileName);

    /**
     * Writes the assembly code to initialize the value of the stack pointer.
     */
    void initStack();

    /**
     * Write the end section of a `push` command.
     */
    void writePushEnd();

    /**
     * Write the start section of a `pop` command.
     */
    void writePopStart();
  };
}


#endif //TRANSLATOR_CODEWRITER_H
