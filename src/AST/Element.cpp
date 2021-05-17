//
// Created by Jelle Spijker on 02-05-21.
//

#include "gcode/AST/Element.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <utility>

namespace gcode {

Element::Element(const Token& token) : m_token{ token }, m_children{ elem_vec_t{} }
{
  spdlog::debug("Parsing token: {}", token);
}

Element::Element(const Token& token, elem_vec_t variables) : m_token{ token }, m_children{ std::move(variables) }
{
  spdlog::debug("Parsing token: {}", token);
}

Element::Element(const Token& token, const std::shared_ptr<Element>& variable) : m_token{ token }, m_children{ { variable } }
{
  spdlog::debug("Parsing token: {}", token);
}

void Element::push_back_child(const std::shared_ptr<Element>& child) { m_children.push_back(child); }

}// namespace ghermeneus
