//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_ELEMENTFACTORY_H
#define GHERMENEUS_ELEMENTFACTORY_H

#include <memory>
#include <vector>
#include <optional>

#include "ghermeneus/Token.h"
#include "ghermeneus/AST/Element.h"

namespace ghermeneus {
using shared_opt_elem_t = std::optional<shared_elem_t>;

class ElementFactory
{
public:
  [[nodiscard]] static shared_opt_elem_t newElement(const Token& token);

  [[nodiscard]] static shared_opt_elem_t newElement(const std::vector<Token>& line);

  [[nodiscard]] static shared_opt_elem_t newElement(const std::vector<Token>& line, const shared_opt_elem_t& parent);

protected:
  [[nodiscard]] static shared_opt_elem_t newCommandElement(const std::vector<Token>& line, const shared_opt_elem_t& parent);

  [[nodiscard]] static shared_opt_elem_t newMachineElement(const std::vector<Token>& line, shared_opt_elem_t parent);

  [[nodiscard]] static shared_opt_elem_t newToolElement(const std::vector<Token>& line, shared_opt_elem_t parent);

  [[nodiscard]] static shared_opt_elem_t newCommentElement(const std::vector<Token>& line, shared_opt_elem_t parent);
};
}// namespace ghermeneus

#endif//GHERMENEUS_ELEMENTFACTORY_H
