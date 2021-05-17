//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GCODE_COMMENTELEMENT_H
#define GCODE_COMMENTELEMENT_H

#include "Element.h"

namespace gcode {
class CommentElement : public Element
{
public:
  explicit CommentElement(const Token& token) : Element{ token } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace gcode

#endif// GCODE_COMMENTELEMENT_H
