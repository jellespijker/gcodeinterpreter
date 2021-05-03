//
// Created by Jelle Spijker on 02-05-21.
//

#include "ghermeneus/AST/MachineElement.h"

namespace ghermeneus {

row_t MachineElement::eval() const
{
  return row_t {};
}

bool MachineElement::isParent() const
{
  return true;
}
}
