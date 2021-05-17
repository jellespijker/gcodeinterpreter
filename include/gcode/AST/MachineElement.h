//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GCODE_MACHINEELEMENT_H
#define GCODE_MACHINEELEMENT_H

#include "Element.h"

namespace gcode {

class MachineElement : public Element
{
public:
  explicit MachineElement(const Token& token) noexcept : Element{ token } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};

}// namespace gcode
#endif// GCODE_MACHINEELEMENT_H
