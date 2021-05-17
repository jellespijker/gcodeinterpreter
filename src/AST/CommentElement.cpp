//
// Created by Jelle Spijker on 02-05-21.
//

#include <map>
#include <vector>
#include <gcode/AST/CommentElement.h>

namespace gcode {

row_t CommentElement::eval() const { return row_t{}; }

bool CommentElement::isParent() const
{
  return false;// FIXME for headers
}

}// namespace gcode
