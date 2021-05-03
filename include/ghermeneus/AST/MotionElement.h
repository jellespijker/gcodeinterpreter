//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_MOTIONELEMENT_H
#define GHERMENEUS_MOTIONELEMENT_H

#include "Element.h"

namespace ghermeneus {

class MotionElement : public Element
{
public:
  explicit MotionElement(const Token& token, const elem_vec_t& variables) : Element(token, variables) {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};

}// namespace ghermeneus

#endif//GHERMENEUS_MOTIONELEMENT_H
