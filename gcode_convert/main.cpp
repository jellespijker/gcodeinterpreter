//
// Created by Jelle Spijker on 10/10/20.
//

#include <string_view>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>
#include <map>

#include "gcode/Lexer.h"
#include "gcode/Parser.h"

using namespace gcode;

constexpr char USAGE[] =
  R"(gcode_convert

    Usage:
      gcode_convert (-h | --help)
      gcode_convert --version
      gcode_convert [-o FILE] [--quiet | --verbose] INPUT

    Options:
      -o --output FILE  specify output file [default: ./output.csv]
      -h --help         Show this screen
      --verbose         print more text
      --quiet           print less text
      --version         Show version
)";

int main(int argc, char* argv[])
{
  std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
    { argv + 1, argv + argc },
    true,
    "gcode_convert 0.1");

  spdlog::set_level(spdlog::level::info);
  const auto verbose = args.at("--verbose").asBool();
  const auto quiet = args.at("--quiet").asBool();
  if (verbose) {
    spdlog::set_level(spdlog::level::debug);
  } else if (quiet) {
    spdlog::set_level(spdlog::level::warn);
  }

  const auto input_file = args.at("INPUT").asString();
  spdlog::info("Using {} as input", input_file);

  std::ifstream gcode_file(input_file);

  gcode::Lexer lexer;
  lexer << gcode_file;

  gcode::Parser parser;
  parser << lexer;
}
