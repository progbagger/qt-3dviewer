#include "point3d.h"

namespace model {

Point3D::Point3D() : Point3D(NAN, NAN, NAN) {}

Point3D::Point3D(float vx, float vy, float vz) : x(vx), y(vy), z(vz) {}

bool Point3D::IsNan() const {
  return std::isnan(x) || std::isnan(y) || std::isnan(z);
}

bool Point3D::operator==(const Point3D &other) const {
  return x == other.x && y == other.y && z == other.z;
}

Rectangle3D::Rectangle3D()
    : left_top_{NAN, NAN, NAN}, right_bottom_{NAN, NAN, NAN} {}

const Point3D &Rectangle3D::GetLeftTop() const { return left_top_; }
const Point3D &Rectangle3D::GetRightBottom() const { return right_bottom_; }

void Rectangle3D::UpdateBorders(const Point3D &point) {
  if (GetLeftTop().IsNan()) {
    left_top_ = point;
  } else {
    if (point.x < GetLeftTop().x) left_top_.x = point.x;
    if (point.y > GetLeftTop().y) left_top_.y = point.y;
    if (point.z > GetLeftTop().z) left_top_.z = point.z;
  }
  if (GetRightBottom().IsNan()) {
    right_bottom_ = point;
  } else {
    if (point.x > GetRightBottom().x) right_bottom_.x = point.x;
    if (point.y < GetRightBottom().y) right_bottom_.y = point.y;
    if (point.z < GetRightBottom().z) right_bottom_.z = point.z;
  }
}

Rectangle3D::ValueType Rectangle3D::Height() const {
  return left_top_.y - right_bottom_.y;
}
Rectangle3D::ValueType Rectangle3D::Width() const {
  return right_bottom_.x - left_top_.x;
}
Rectangle3D::ValueType Rectangle3D::Depth() const {
  return left_top_.z - right_bottom_.z;
}

Rectangle3D::ValueType Rectangle3D::Volume() const {
  return Height() * Width() * Depth();
}

}  // namespace model
