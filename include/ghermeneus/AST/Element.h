//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_ELEMENT_H
#define GHERMENEUS_ELEMENT_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "ghermeneus/Token.h"

namespace ghermeneus {

using row_t = std::map<const std::string, double>;

class Element
{
public:
  explicit Element(const Token& token);

  Element(const Token& token, const std::shared_ptr<Element>& variable);

  Element(const Token& token, std::vector<std::shared_ptr<Element>>  variables);

  virtual ~Element() = default;

  [[nodiscard]] virtual row_t eval() const = 0;

  [[nodiscard]] virtual bool isParent() const = 0;

  virtual void push_back_child(const std::shared_ptr<Element>& child);

private:
  const Token m_token;
  std::vector<std::shared_ptr<Element>> m_children;
};

using shared_elem_t = std::shared_ptr<Element>;
using elem_vec_t = std::vector<shared_elem_t>;

}// namespace ghermeneus

#endif// GHERMENEUS_ELEMENT_H
