//
// Created by Jelle Spijker on 02-05-21.
//

#include "gcode/AST/ChangeElement.h"

namespace gcode {

row_t ChangeElement::eval() const { return row_t{}; }

bool ChangeElement::isParent() const { return true; }

}// namespace gcode
