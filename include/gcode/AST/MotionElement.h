//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GCODE_MOTIONELEMENT_H
#define GCODE_MOTIONELEMENT_H

#include "Element.h"

namespace gcode {

class MotionElement : public Element
{
public:
  MotionElement(const Token& token, const elem_vec_t& variables) : Element{ token, variables } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};

}// namespace gcode

#endif// GCODE_MOTIONELEMENT_H
