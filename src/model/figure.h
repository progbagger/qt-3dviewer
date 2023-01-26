#ifndef MODEL_FIGURE_H_
#define MODEL_FIGURE_H_

#include <filesystem>
#include <string>
#include <vector>

#include "point3d.h"

namespace model {

// Vertex and facet arrays storage acceptable by OpenGL
class Figure {
 public:
  using SizeType = std::size_t;
  using IndexType = unsigned;
  using ValueType = Point3D::ValueType;
  using VertexStorageType = std::vector<ValueType>;
  using FacetStorageType = std::vector<IndexType>;

  Figure() = delete;
  Figure(const std::string &path, SizeType vertexes_count = 0UL,
         SizeType facets_count = 0UL, SizeType edges_count = 0UL,
         SizeType facets_index_count = 0UL);

  const ValueType *GetVertexes() const;
  const IndexType *GetFacets() const;

  SizeType GetVertexCount() const;
  SizeType GetEdgesCount() const;
  SizeType GetFacetsIndexCount() const;
  SizeType GetFacetsCount() const;

  const Rectangle3D &GetRectangle() const;

  const std::string &GetPath() const;
  const std::string GetName() const;

  void IncreaseEdgesCount();

  void AppendVertex(const Point3D &vertex);
  void AppendFacetIndex(IndexType index, unsigned facet_size);
  void LoopFacet(IndexType start, unsigned facet_size);

  void Shrink();

 private:
  void UpdateRectangle(const Point3D &point);

  VertexStorageType vertexes_;
  FacetStorageType facets_;
  SizeType facets_count_;
  SizeType edges_count_;
  Rectangle3D rectangle_;
  std::string path_to_file_;
};

}  // namespace model

#endif  // MODEL_FIGURE_H_
