//
// Created by Jelle Spijker on 02-05-21.
//

#include "gcode/AST/ToolElement.h"

namespace gcode {

row_t ToolElement::eval() const { return row_t{}; }

bool ToolElement::isParent() const { return true; }

}// namespace gcode
