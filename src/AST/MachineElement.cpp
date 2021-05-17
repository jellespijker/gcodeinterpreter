//
// Created by Jelle Spijker on 02-05-21.
//

#include "gcode/AST/MachineElement.h"

namespace gcode {

row_t MachineElement::eval() const { return row_t{}; }

bool MachineElement::isParent() const { return true; }

}// namespace gcode
