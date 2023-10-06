#include "circle.h"

#include "line.h"
#include "segment.h"
namespace geometry {
Circle::Circle() {
    centre_ = Point();
    radius_ = 0;
}
Circle::Circle(Point centre, int64_t radius) {
    centre_ = centre;
    radius_ = radius;
}
Circle& Circle::Move(const Vector& vector) {
    centre_.Move(vector);
    return *this;
}
bool Circle::ContainsPoint(const Point& point) const {
    int64_t x = point.GetX();
    int64_t y = point.GetY();
    return (x - centre_.GetX()) * (x - centre_.GetX()) + (y - centre_.GetY()) * (y - centre_.GetY()) -
               radius_ * radius_ <=
           0;
}
bool Circle::CrossesSegment(const Segment& segment) const {
    if (!ContainsPoint(segment.GetStart()) && !ContainsPoint(segment.GetEnd())) {
        Line line = Line(segment.GetStart(), segment.GetEnd());
        return line.Distance(centre_) <= static_cast<double>(radius_);
    }
    int64_t x = segment.GetStart().GetX();
    int64_t y = segment.GetStart().GetY();
    bool contains_start_in_circle =
        (x - centre_.GetX()) * (x - centre_.GetX()) + (y - centre_.GetY()) * (y - centre_.GetY()) - radius_ * radius_ <
        0;
    x = segment.GetEnd().GetX();
    y = segment.GetEnd().GetY();
    bool contains_end_in_circle =
        (x - centre_.GetX()) * (x - centre_.GetX()) + (y - centre_.GetY()) * (y - centre_.GetY()) - radius_ * radius_ <
        0;
    return !(contains_start_in_circle && contains_end_in_circle);
}
Circle* Circle::Clone() const {
    return new Circle(centre_, radius_);
}
int64_t Circle::GetRadius() const {
    return radius_;
}
Point Circle::GetCenter() const {
    return centre_;
}
}  // namespace geometry