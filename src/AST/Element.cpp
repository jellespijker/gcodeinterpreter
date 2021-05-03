//
// Created by Jelle Spijker on 02-05-21.
//

#include "ghermeneus/AST/Element.h"

namespace ghermeneus {

Element::Element(const Token& token) : m_token(token), m_children(elem_vec_t{})
{
}

Element::Element(const Token& token, elem_vec_t variables) : m_token(token), m_children(variables)
{
}

void Element::push_back_child(const std::shared_ptr<Element>& child)
{
  m_children.push_back(child);
}
}// namespace ghermeneus
