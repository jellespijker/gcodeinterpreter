//
// Created by Jelle Spijker on 02-05-21.
//

#include "ghermeneus/AST/ToolElement.h"

namespace ghermeneus {

row_t ToolElement::eval() const { return row_t{}; }

bool ToolElement::isParent() const { return true; }

}// namespace ghermeneus
