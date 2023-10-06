#include "segment.h"

#include "vector.h"
geometry::Vector operator/(geometry::Point p2, geometry::Point p1) {
    return geometry::Vector(p2.GetX() - p1.GetX(), p2.GetY() - p1.GetY());
}

namespace geometry {
Segment::Segment() {
    start_ = Point();
    end_ = Point();
}
Segment::Segment(Point x, Point y) {
    start_ = x;
    end_ = y;
}
Point Segment::GetStart() const {
    return start_;
}
Point Segment::GetEnd() const {
    return end_;
}
Segment* Segment::Clone() const {
    Segment* segment = new Segment(start_, end_);
    return segment;
}
bool Segment::ContainsPoint(const geometry::Point& point) const {
    int64_t min_x = std::min(start_.GetX(), end_.GetX());
    int64_t max_x = std::max(start_.GetX(), end_.GetX());
    int64_t min_y = std::min(start_.GetY(), end_.GetY());
    int64_t max_y = std::max(start_.GetY(), end_.GetY());
    int64_t x = point.GetX();
    int64_t y = point.GetY();
    return VectorMult(Vector(point.GetX() - start_.GetX(), point.GetY() - start_.GetY()),
                      Vector(end_.GetX() - point.GetX(), end_.GetY() - point.GetY())) == 0 &&
           x >= min_x && x <= max_x && y >= min_y && y <= max_y;
}
bool Segment::CrossesSegment(const geometry::Segment& segment) const {
    if (ContainsPoint(segment.start_) || ContainsPoint(segment.end_) || segment.ContainsPoint(start_) ||
        segment.ContainsPoint(end_)) {
        return true;
    }
    Point a = start_;
    Point b = end_;
    Point c = segment.start_;
    Point d = segment.end_;
    Vector ba = a / b;
    Vector ca = a / c;
    Vector da = a / d;
    Vector dc = c / d;
    Vector ac = c / a;
    Vector bc = c / b;
    if (VectorMult(ba, ca) * VectorMult(ba, da) >= 0 || VectorMult(dc, ac) * VectorMult(dc, bc) >= 0) {
        return false;
    }
    return true;
}
Segment& Segment::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
}  // namespace geometry