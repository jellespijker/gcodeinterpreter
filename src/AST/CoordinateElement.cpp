//
// Created by Jelle Spijker on 02-05-21.
//
#include <gcode/AST/CoordinateElement.h>

namespace gcode {

row_t CoordinateElement::eval() const { return row_t{}; }

bool CoordinateElement::isParent() const { return true; }

}// namespace gcode
