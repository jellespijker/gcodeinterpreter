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
  /*!
   * @brief create a new Element from a single token, currently used to create the top-level Machine Element
   * @param token the Machine token.
   * @return an Element smart pointer or a nullopt
   */
  [[nodiscard]] static shared_opt_elem_t newElement(const Token& token);

  /*!
   * @brief Create a new element from a line, which consist of multiple tokens.
   *
   * Create a new element from a line, which could consist of multiple tokens. Where the first token is the parent.
   * e.q. AST-subtree for a "line" token sequence:
   *
   * COMMAND[G0] VARIABLE[X] VALUE[100] VARIABLE[Y] VALUE[10] COMMENT[remark] LINE[]
   *
   *                                MotionElement (G0)
   *                                     |
   *            ------------------------------------------------------
   *           |                        |                            |
   * CoordinateElement(X)     CoordinateElement(Y)     CommentElement(remark)
   *          |                        |
   *  NumericElement(100)       NumericElement(10)
   *
   * @param line a sequence of line tokens
   * @return The parent top-level Element.
   */
  [[nodiscard]] static shared_opt_elem_t newElement(const std::vector<Token>& line);

  /*!
   * @brief Create a new element from a line, which consist of multiple tokens.
   *
   * Create a new element from a line, which could consist of multiple tokens. Where the first token is the parent.
   * e.q. AST-subtree for a "line" token sequence:
   *
   * COMMAND[G0] VARIABLE[X] VALUE[100] VARIABLE[Y] VALUE[10] COMMENT[remark] LINE[]
   *
   *                                 ParentElement
   *                                      |
   *                                MotionElement (G0)
   *                                     |
   *            ------------------------------------------------------
   *           |                        |                            |
   * CoordinateElement(X)     CoordinateElement(Y)     CommentElement(remark)
   *          |                        |
   *  NumericElement(100)       NumericElement(10)
   *
   * @param line a sequence of line tokens
   * @return The parent top-level Element.
   */
  [[nodiscard]] static shared_opt_elem_t newElement(const std::vector<Token>& line, const shared_opt_elem_t& parent);

protected:
  /*!
   * @brief Create a new CommandElement
   * @param cmd
   * @param args
   * @return
   */
  [[nodiscard]] static shared_opt_elem_t newCommandElement(const Token& cmd, const std::vector<Token>& args);

  [[nodiscard]] static shared_opt_elem_t newMotionElement(const Token& cmd, const std::vector<Token>& args);

  [[nodiscard]] static shared_opt_elem_t newCoordinateElement(const Token& arg, const Token& value);

  [[nodiscard]] static shared_opt_elem_t newCommentElement(const Token& cmd);

  [[nodiscard]] static shared_opt_elem_t newToolElement(const Token& cmd, const Token& arg);
};
}// namespace ghermeneus

#endif// GHERMENEUS_ELEMENTFACTORY_H
