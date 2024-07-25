/**
 * Created by Kush Padalia on June 3, 2024.
 */

#ifndef TRANSLATOR_COMMANDTYPE_H
#define TRANSLATOR_COMMANDTYPE_H

namespace translator {

  /**
   * An enumeration representing Hack VM language command types.
   *
   * @enum Arithmetic: Arithmetic commands.
   * @enum Push: Push command.
   * @enum Pop: Pop command.
   * @enum Label: Label command.
   * @enum Goto: Go-to command.
   * @enum If: If command.
   * @enum Function: Command representing a function.
   * @enum Return: Command returning from a function.
   * @enum Call: Command calling a function.
   * @enum NonCommand: Any command containing whitespace or comments.
   */
  enum class commandType {
    Arithmetic,
    Push,
    Pop,
    Label,
    Goto,
    If,
    Function,
    Return,
    Call,
    NonCommand
  };
}

#endif //TRANSLATOR_COMMANDTYPE_H
