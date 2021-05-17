//
// Created by Jelle Spijker on 02-05-21.
//

#include "gcode/AST/NumericElement.h"

namespace gcode {

row_t NumericElement::eval() const { return gcode::row_t(); }

bool NumericElement::isParent() const { return false; }
}// namespace gcode
