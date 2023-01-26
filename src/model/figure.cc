#include "figure.h"

namespace model {

Figure::Figure(const std::string &path, SizeType vertexes_count,
               SizeType facets_count, SizeType edges_count,
               SizeType facets_index_count)
    : vertexes_(),
      facets_(),
      facets_count_(facets_count),
      edges_count_(edges_count),
      rectangle_(),
      path_to_file_(path) {
  vertexes_.reserve(vertexes_count * 3);
  facets_.reserve(facets_index_count);
}

const Figure::ValueType *Figure::GetVertexes() const {
  return vertexes_.data();
}

const Figure::IndexType *Figure::GetFacets() const { return facets_.data(); }

Figure::SizeType Figure::GetVertexCount() const { return vertexes_.size() / 3; }

Figure::SizeType Figure::GetEdgesCount() const { return edges_count_; }

Figure::SizeType Figure::GetFacetsIndexCount() const { return facets_.size(); }

Figure::SizeType Figure::GetFacetsCount() const { return facets_count_; }

const Rectangle3D &Figure::GetRectangle() const { return rectangle_; }

const std::string &Figure::GetPath() const { return path_to_file_; }

const std::string Figure::GetName() const {
  auto delim_pos = GetPath().rfind(std::filesystem::path::preferred_separator);
  if (delim_pos == std::string::npos) return GetPath();
  return GetPath().substr(delim_pos + 1);
}

void Figure::IncreaseEdgesCount() { ++edges_count_; }

void Figure::AppendVertex(const Point3D &vertex) {
  vertexes_.push_back(vertex.x);
  vertexes_.push_back(vertex.y);
  vertexes_.push_back(vertex.z);
  UpdateRectangle(vertex);
}

void Figure::AppendFacetIndex(IndexType index, unsigned facet_size) {
  if (facet_size < 2) {
    facets_.push_back(index - 1);
  } else {
    facets_.push_back(facets_.back());
    facets_.push_back(index - 1);
  }
}

void Figure::LoopFacet(IndexType start, unsigned facet_size) {
  if (facet_size > 2) AppendFacetIndex(start, facet_size);
}

void Figure::Shrink() {
  facets_.shrink_to_fit();
  vertexes_.shrink_to_fit();
}

void Figure::UpdateRectangle(const Point3D &point) {
  rectangle_.UpdateBorders(point);
}

}  // namespace model
