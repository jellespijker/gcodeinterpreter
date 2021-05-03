//
// Created by Jelle Spijker on 02-05-21.
//

#include "ghermeneus/AST/MotionElement.h"

namespace ghermeneus {

row_t MotionElement::eval() const
{
  return row_t {};
}

bool MotionElement::isParent() const
{
  return false;
}

}// namespace ghermeneus
