//
// Created by Jelle Spijker on 02-05-21.
//

#include "ghermeneus/AST/NumericElement.h"

namespace ghermeneus {

row_t NumericElement::eval() const
{
  return ghermeneus::row_t();
}

bool NumericElement::isParent() const
{
  return false;
}
}
