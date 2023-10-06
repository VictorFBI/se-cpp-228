#include "segment.h"

#include "vector.h"
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
    double xa1 = static_cast<double>(start_.GetX());
    double ya1 = static_cast<double>(start_.GetY());
    double xb1 = static_cast<double>(end_.GetX());
    double yb1 = static_cast<double>(end_.GetY());
    double xa2 = static_cast<double>(segment.start_.GetX());
    double ya2 = static_cast<double>(segment.start_.GetY());
    double xb2 = static_cast<double>(segment.end_.GetX());
    double yb2 = static_cast<double>(segment.end_.GetY());
    if (xa1 == xb1 && xa2 == xb2) {
        double min_y1 = std::min(ya1, yb1);
        double max_y1 = std::max(ya1, yb1);
        double min_y2 = std::min(ya2, yb2);
        double max_y2 = std::max(ya2, yb2);
        return (min_y1 >= min_y2 && min_y1 <= max_y2) || (min_y2 >= min_y1 && min_y2 <= max_y1);
    }
    if (xa1 == xb1) {
        double k2 = (ya2 - yb2) / (xa2 - xb2);
        double b2 = ya2 - k2 * xa2;
        return (ya1 - k2 * xa1 - b2) * (yb1 - k2 * xb1 - b2) <= 0 && (xa2 - xa1) * (xb2 - xa1) <= 0;
    }
    if (xa2 == xb2) {
        double k1 = (ya1 - yb1) / (xa1 - xb1);
        double b1 = ya1 - k1 * xa1;
        return (ya2 - k1 * xa2 - b1) * (yb2 - k1 * xb2 - b1) <= 0 && (xa1 - xa2) * (xb1 - xa2) <= 0;
    }
    double k1 = (ya1 - yb1) / (xa1 - xb1);
    double b1 = ya1 - k1 * xa1;
    double k2 = (ya2 - yb2) / (xa2 - xb2);
    double b2 = ya2 - k2 * xa2;
    return (ya1 - k2 * xa1 - b2) * (yb1 - k2 * xb1 - b2) <= 0 && (ya2 - k1 * xa2 - b1) * (yb2 - k1 * xb2 - b1) <= 0;
}
Segment& Segment::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
}  // namespace geometry