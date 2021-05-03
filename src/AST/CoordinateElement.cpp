//
// Created by Jelle Spijker on 02-05-21.
//
#include <ghermeneus/AST/CoordinateElement.h>

namespace ghermeneus {

row_t CoordinateElement::eval() const
{
  return row_t{};
}

bool CoordinateElement::isParent() const
{
  return true;
}

}// namespace ghermeneus
