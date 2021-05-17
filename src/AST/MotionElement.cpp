//
// Created by Jelle Spijker on 02-05-21.
//

#include "gcode/AST/MotionElement.h"

namespace gcode {

row_t MotionElement::eval() const { return row_t{}; }

bool MotionElement::isParent() const { return false; }

}// namespace gcode
