//
// Created by Jelle Spijker on 02-05-21.
//

#include <range/v3/view/tail.hpp>
#include <range/v3/all.hpp>
#include <range/v3/range/conversion.hpp>

#include "gcode/ElementFactory.h"
#include "gcode/AST/MotionElement.h"
#include "gcode/AST/ToolElement.h"
#include "gcode/AST/CommentElement.h"
#include "gcode/AST/ChangeElement.h"
#include "gcode/AST/NumericElement.h"
#include "gcode/AST/MachineElement.h"
#include "gcode/AST/CoordinateElement.h"
#include "gcode/AST/TextElement.h"


namespace rg = ranges;
namespace rv = ranges::views;

namespace gcode {


shared_opt_elem_t ElementFactory::newElement(const Token& token)
{
  switch (token.getType()) {
  case Token::MACHINE:
    return std::make_shared<MachineElement>(token);
  default:
    return std::nullopt;
  }
}

shared_opt_elem_t ElementFactory::newElement(const std::vector<Token>& line, const shared_opt_elem_t& parent)
{
  auto elem = ElementFactory::newElement(line);
  if (parent.has_value() && elem.has_value()) { parent.value()->push_back_child(elem.value()); }
  return elem;
}

shared_opt_elem_t ElementFactory::newElement(const std::vector<Token>& line)
{
  const auto cmd_view = line | rv::take(1);
  const auto args = line | rv::tail | rg::to_vector;
  const auto cmd = *cmd_view.begin();
  switch (cmd.getType()) {
  case Token::TOOL:// A TOOL token
    return newToolElement(cmd, args.front());
  case Token::COMMAND:// COMMAND TOKENS such as G0, M280 etc.
    return newCommandElement(cmd, args);
  case Token::COMMENT:// A COMMENT TOKEN, doesn't handle command comments yet.
    return newCommentElement(cmd);
  default:
    return std::nullopt;
  }
}

shared_opt_elem_t ElementFactory::newCommandElement(const Token& cmd, const std::vector<Token>& args)
{
  if (cmd.getWord() == "G0" || cmd.getWord() == "G1")// MotionElement
  {
    return newMotionElement(cmd, args);
  }
  return std::nullopt;
}

shared_opt_elem_t ElementFactory::newCommentElement(const Token& cmd)
{
  if (cmd.getWord().starts_with(";"))// TODO: check if this is generic enough for now
  {
    return std::make_shared<TextElement>(cmd);
  }
  // TODO: Handle comments that are actually commands
  return std::nullopt;
}

shared_opt_elem_t ElementFactory::newCoordinateElement(const Token& arg, const Token& value)
{
  const auto& value_elem = std::make_shared<NumericElement>(value);
  return std::make_shared<CoordinateElement>(arg, value_elem);
}

shared_opt_elem_t ElementFactory::newMotionElement(const Token& cmd, const std::vector<Token>& args)
{
  const auto& coord_tokens = args | rv::chunk(2);
  elem_vec_t arg_elems;
  for (const auto& coord_token : coord_tokens) {
    const auto& p = coord_token | rg::to_vector;
    const auto& s = newCoordinateElement(p.front(), p.back());
    if (s.has_value()) { arg_elems.emplace_back(s.value()); }
  }
  return std::make_shared<MotionElement>(cmd, arg_elems);
}

shared_opt_elem_t ElementFactory::newToolElement(const Token& cmd, const Token& arg)
{
  const auto value_elem = std::make_shared<NumericElement>(arg);
  auto tool_elem = std::make_shared<ToolElement>(cmd);
  tool_elem->push_back_child(value_elem);
  return tool_elem;
}

}// namespace ghermeneus
