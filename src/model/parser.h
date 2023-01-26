#ifndef MODEL_PARSER_H_
#define MODEL_PARSER_H_

#include <fstream>
#include <sstream>

#include "figure.h"

namespace model {

// Class to actually parse an object file
class Parser {
 public:
  using SizeType = Figure::SizeType;

  Parser();
  ~Parser();
  Parser(const Parser&) = delete;
  Parser(Parser&&) = delete;
  Parser& operator=(const Parser&) = delete;
  Parser& operator=(Parser&&) = delete;

  void CountVF(std::ifstream& file);

  Figure* GetFigureByPath(const std::string& path);
  Figure* GetFigure() const;

  void CloseFigure();

 private:
  bool IsVertexLine(const std::string& line);
  bool IsFacetLine(const std::string& line);

  void ParseFile(std::ifstream& file);
  void ParseVertex(const std::string& line);
  void ParseFacet(const std::string& line);

  Figure* figure_;
  std::pair<std::size_t, std::size_t> sizes_;
};

}  // namespace model

#endif  // MODEL_PARSER_H_
