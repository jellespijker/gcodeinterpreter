//
// Created by Jelle Spijker on 02-05-21.
//

#include <range/v3/view/tail.hpp>
#include <range/v3/all.hpp>
#include <range/v3/range/conversion.hpp>

#include <ghermeneus/ElementFactory.h>
#include "ghermeneus/AST/MotionElement.h"
#include "ghermeneus/AST/ToolElement.h"
#include "ghermeneus/AST/CommentElement.h"
#include "ghermeneus/AST/ChangeElement.h"
#include "ghermeneus/AST/NumericElement.h"
#include "ghermeneus/AST/MachineElement.h"

namespace rg = ranges;
namespace rv = ranges::views;

namespace ghermeneus {

shared_opt_elem_t ElementFactory::newElement(const Token& token)
{
  switch (token.getType()) {
  case Token::MACHINE:
    return std::make_unique<MachineElement>(token);
    break;
  default:
    return std::nullopt;
  }
}

shared_opt_elem_t ElementFactory::newElement(const std::vector<Token>& line)
{
  const auto cmd_view = line | rv::take(1);
  const auto args_view = line | rv::tail;
  const auto cmd = *cmd_view.begin();
  for (const auto& args : args_view) {

  }
  return std::nullopt;
}

shared_opt_elem_t ElementFactory::newElement(const std::vector<Token>& line, const shared_opt_elem_t& parent)
{
  auto elem = ElementFactory::newElement(line);
  if (parent.has_value() && elem.has_value()) {
    parent.value()->push_back_child(elem.value());
  }
  return elem;
}

shared_opt_elem_t ElementFactory::newCommandElement(const std::vector<Token>& line, const shared_opt_elem_t& parent = std::nullopt)
{
  const auto cmd_word = line.front().getWord();
  const auto var = line | rv::tail | rg::to_vector;
  if (cmd_word == "G0" || cmd_word == "G1") {
    auto elem = std::make_unique<MotionElement>(line.front());
    elem->setVariables(var);
    return elem;
  } else if (cmd_word == "M82") {
    auto elem = std::make_unique<ChangeElement>(line.front());
    elem->setVariables(var);
  }
  return std::nullopt;
}

shared_opt_elem_t ElementFactory::newToolElement(const std::vector<Token>& line, shared_opt_elem_t parent = std::nullopt)
{
  auto elem = std::make_unique<ToolElement>(line.front());
  elem->setVariables(line | rv::tail | rg::to_vector);
  return elem;
}

shared_opt_elem_t ElementFactory::newCommentElement(const std::vector<Token>& line, shared_opt_elem_t parent = std::nullopt)
{
  auto elem = std::make_unique<CommentElement>(line.front());
  elem->setVariables(line | rv::tail | rg::to_vector);
  return elem;
}
shared_opt_elem_t ElementFactory::newMachineElement(const std::vector<Token>& line, shared_opt_elem_t parent)
{
  return ghermeneus::shared_opt_elem_t();
}

}// namespace ghermeneus
