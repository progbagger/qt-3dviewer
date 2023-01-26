#ifndef MODEL_POINT3D_H_
#define MODEL_POINT3D_H_

#include <cmath>

namespace model {

struct Point3D {
  using ValueType = float;

  Point3D();
  Point3D(float vx, float vy, float vz);

  bool IsNan() const;

  bool operator==(const Point3D &other) const;

  ValueType x, y, z;
};

class Rectangle3D {
 public:
  using ValueType = Point3D::ValueType;

  Rectangle3D();

  const Point3D &GetLeftTop() const;
  const Point3D &GetRightBottom() const;

  void UpdateBorders(const Point3D &point);

  ValueType Height() const;
  ValueType Width() const;
  ValueType Depth() const;

  ValueType Volume() const;

 private:
  Point3D left_top_;
  Point3D right_bottom_;
};

}  // namespace model

#endif  // MODEL_POINT3D_H_
