#include "polygon.h"

#include "line.h"
#include "segment.h"
#include "vector.h"
namespace geometry {
Polygon::Polygon() {
    num_points_ = 0;
    points_ = std::vector<Point>();
}
Polygon::Polygon(std::vector<Point> points) {
    points_ = points;
    num_points_ = points.size();
}
Polygon& Polygon::Move(const Vector& vector) {
    for (auto& el : points_) {
        el.Move(vector);
    }
    return *this;
}
bool Polygon::ContainsPoint(const Point& point) const {
    Point start = point;
    size_t intersections = 0;
    for (size_t i = 0; i < num_points_ - 1; ++i) {
        if (Segment(points_[i], points_[i + 1]).ContainsPoint(start)) {
            return true;
        }
    }
    if (Segment(points_[num_points_ - 1], points_[0]).ContainsPoint(start)) {
        return true;
    }
    const int64_t difference = 1000000;
    int64_t multiplier = 1;
    Point end(point.GetX() + difference, point.GetY());
    Segment segment(start, end);
    for (size_t i = 0; i < num_points_; ++i) {
        if (segment.ContainsPoint(points_[i])) {
            segment = Segment(start, Point(end.GetX(), end.GetY() + multiplier));
            ++multiplier;
            i = 0;
        }
    }
    for (size_t i = 0; i < num_points_ - 1; ++i) {
        if (Segment(points_[i], points_[i + 1]).CrossesSegment(segment)) {
            ++intersections;
        }
    }
    if (Segment(points_[num_points_ - 1], points_[0]).CrossesSegment(segment)) {
        ++intersections;
    }
    return intersections % 2 == 1;
}
bool Polygon::CrossesSegment(const Segment& segment) const {
    for (size_t i = 0; i < num_points_ - 1; ++i) {
        if (Segment(points_[i], points_[i + 1]).CrossesSegment(segment)) {
            return true;
        }
    }
    return Segment(points_[num_points_ - 1], points_[0]).CrossesSegment(segment);
}
Polygon* Polygon::Clone() const {
    Polygon* polygon = new Polygon(points_);
    return polygon;
}
}  // namespace geometry