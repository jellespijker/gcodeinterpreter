//
// Created by Jelle Spijker on 16-05-21.
//

#include "ghermeneus/AST/TextElement.h"

namespace ghermeneus {

row_t TextElement::eval() const { return ghermeneus::row_t(); }

bool TextElement::isParent() const { return false; }
}// namespace ghermeneus
