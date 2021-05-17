//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GCODE_CHANGEELEMENT_H
#define GCODE_CHANGEELEMENT_H

#include "Element.h"

namespace gcode {
class ChangeElement : public Element
{
public:
  explicit ChangeElement(const Token& token) : Element{ token } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace gcode

#endif// GCODE_CHANGEELEMENT_H
