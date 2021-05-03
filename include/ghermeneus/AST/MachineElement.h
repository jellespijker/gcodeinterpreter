//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_MACHINEELEMENT_H
#define GHERMENEUS_MACHINEELEMENT_H

#include "Element.h"

namespace ghermeneus {

class MachineElement : public Element
{
public:
  explicit MachineElement(const Token& token) : Element(token){};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};

}// namespace ghermeneus
#endif//GHERMENEUS_MACHINEELEMENT_H
