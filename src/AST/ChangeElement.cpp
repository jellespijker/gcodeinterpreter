//
// Created by Jelle Spijker on 02-05-21.
//

#include "ghermeneus/AST/ChangeElement.h"

namespace ghermeneus {

row_t ChangeElement::eval() const { return row_t{}; }

bool ChangeElement::isParent() const { return true; }

}// namespace ghermeneus
