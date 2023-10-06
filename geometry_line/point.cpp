#include "point.h"

#include "segment.h"
namespace geometry {
int64_t Point::GetX() const {
    return x_coord_;
}
int64_t Point::GetY() const {
    return y_coord_;
}
void Point::SetX(int64_t t) {
    x_coord_ = t;
}
void Point::SetY(int64_t t) {
    y_coord_ = t;
}
Point &Point::Move(const Vector &vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}
bool Point::ContainsPoint(const Point &point) const {
    return x_coord_ == point.x_coord_ && y_coord_ == point.y_coord_;
}
bool Point::CrossesSegment(const Segment &segment) const {
    return segment.ContainsPoint(*this);
}
Point *Point::Clone() const {
    Point *p = new Point(x_coord_, y_coord_);
    return p;
}
Point::Point(int64_t x, int64_t y) {
    SetX(x);
    SetY(y);
}
Vector Point::operator-(Point other) const {
    return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
}
}  // namespace geometry
