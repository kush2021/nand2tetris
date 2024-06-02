//
// Created by Kush Padalia on 2024-05-25.
//

#ifndef HACK_ASSEMBLER_COMMANDTYPE_H
#define HACK_ASSEMBLER_COMMANDTYPE_H

namespace assembler {

  /**
   * An enumeration representing Hack assembly command types.
   *
   * @attributes
   * ACommand: Commands using `@Xxx` where `Xxx` is either a symbol or a decimal.
   * CCommand: Commands using `dest=comp;jump`.
   * LCommand: Commands using `(Xxx)` where `Xxx` is a symbol.
   * NonCommand: Lines of whitespace or comments.
   */
  enum class commandType {
    ACommand,
    CCommand,
    LCommand,
    NonCommand
  };
}

#endif //HACK_ASSEMBLER_COMMANDTYPE_H
