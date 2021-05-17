//
// Created by Jelle Spijker on 16-05-21.
//

#include "gcode/AST/TextElement.h"

namespace gcode {

row_t TextElement::eval() const { return gcode::row_t(); }

bool TextElement::isParent() const { return false; }
}// namespace gcode
