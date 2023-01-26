#include "parser.h"

namespace model {

Parser::Parser() : figure_(nullptr), sizes_{0UL, 0UL} {}

Parser::~Parser() { delete figure_; }

void Parser::CountVF(std::ifstream& file) {
  sizes_ = std::pair{0UL, 0UL};
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    if (IsVertexLine(line)) {
      ++sizes_.first;
    } else if (IsFacetLine(line)) {
      ++sizes_.second;
    }
  }
}

Figure* Parser::GetFigureByPath(const std::string& path) {
  SizeType last_dot = path.rfind('.');
  if (last_dot != std::string::npos && path.substr(last_dot) != ".obj")
    return nullptr;
  std::ifstream file(path);
  if (!file) return nullptr;
  CountVF(file);
  if (!sizes_.first) return nullptr;
  file.close();
  file.open(path);
  Figure* prev_figure = figure_;
  figure_ =
      new Figure(path, sizes_.first, sizes_.second, 0, sizes_.second * 10);
  ParseFile(file);
  if (figure_) {
    delete prev_figure;
    figure_->Shrink();
  } else {
    figure_ = prev_figure;
  }
  return figure_;
}

Figure* Parser::GetFigure() const { return figure_; }

void Parser::CloseFigure() {
  delete figure_;
  figure_ = nullptr;
}

bool Parser::IsVertexLine(const std::string& line) {
  return line.length() > 2 && line.substr(0, 2) == "v ";
}

bool Parser::IsFacetLine(const std::string& line) {
  return line.length() > 2 && line.substr(0, 2) == "f ";
}

void Parser::ParseFile(std::ifstream& file) {
  while (figure_ && !file.eof()) {
    std::string line;
    std::getline(file, line);
    bool is_fail = file.fail();
    if (is_fail) return;
    if (IsVertexLine(line)) {
      ParseVertex(line);
    } else if (IsFacetLine(line)) {
      ParseFacet(line);
    }
  }
}

void Parser::ParseVertex(const std::string& line) {
  std::stringstream reader(line);
  reader.ignore(2);  // skipping "v "
  Point3D readed_point;
  reader >> readed_point.x;
  reader >> readed_point.y;
  reader >> readed_point.z;
  if (reader.fail()) {
    delete figure_;
    figure_ = nullptr;
    return;
  }
  if (figure_) figure_->AppendVertex(readed_point);
}

void Parser::ParseFacet(const std::string& line) {
  std::stringstream reader(line);
  reader.ignore(2);  // skipping "f "
  Figure::IndexType start = 0;
  unsigned facet_size = 0;
  while (!reader.eof()) {
    Figure::IndexType index;
    reader >> index;
    if (reader.fail() || index < 1 || index > sizes_.first) {
      if (reader.eof()) break;
      delete figure_;
      figure_ = nullptr;
      return;
    }
    if (start == 0) start = index;
    figure_->AppendFacetIndex(index, facet_size);
    figure_->IncreaseEdgesCount();
    ++facet_size;
    while (reader.peek() != ' ' && !reader.eof()) reader.ignore(1);
  }
  figure_->LoopFacet(start, facet_size);
}

}  // namespace model
