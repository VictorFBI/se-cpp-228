#include "line.h"

#include "segment.h"
#include "vector.h"
namespace geometry {
Line::Line() {
    start_ = Point();
    end_ = Point();
}
int64_t Line::GetA() const {
    return end_.GetY() - start_.GetY();
}
int64_t Line::GetB() const {
    return start_.GetX() - end_.GetX();
}
int64_t Line::GetC() const {
    return -GetA() * start_.GetX() - GetB() * start_.GetY();
}
Line::Line(Point start, Point end) {
    start_ = start;
    end_ = end;
}
double Line::Distance(Point point) const {
    return static_cast<double>(std::abs(GetA() * point.GetX() + GetB() * point.GetY() + GetC())) /
           std::sqrt(GetA() * GetA() + GetB() * GetB());
}
Line& Line::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
bool Line::ContainsPoint(const Point& point) const {
    return VectorMult(Vector(point.GetX() - start_.GetX(), point.GetY() - start_.GetY()),
                      Vector(end_.GetX() - point.GetX(), end_.GetY() - point.GetY())) == 0;
}
bool Line::CrossesSegment(const Segment& segment) const {
    double min_x = static_cast<double>(std::min(segment.GetStart().GetX(), segment.GetEnd().GetX()));
    double max_x = static_cast<double>(std::max(segment.GetStart().GetX(), segment.GetEnd().GetX()));
    double min_y = static_cast<double>(std::min(segment.GetStart().GetY(), segment.GetEnd().GetY()));
    double max_y = static_cast<double>(std::max(segment.GetStart().GetY(), segment.GetEnd().GetY()));
    if (min_x == max_x) {
        if (GetB() == 0) {
            return min_x == static_cast<double>(-GetC()) / static_cast<double>(GetA());
        }
        double y = (static_cast<double>(-GetC()) - min_x * static_cast<double>(GetA())) / static_cast<double>(GetB());
        return y >= min_y && y <= max_y;
    }
    double ks = static_cast<double>(max_y - min_y) / static_cast<double>(max_x - min_x);
    double bs = min_y - ks * min_x;
    double delta = static_cast<double>(-GetA()) - ks * static_cast<double>(GetB());
    double delta_x = static_cast<double>(GetC()) + static_cast<double>(GetB()) * bs;
    double delta_y = -static_cast<double>(GetA()) * bs + static_cast<double>(GetC()) * ks;
    if (delta == 0) {
        if (GetA() * segment.GetStart().GetX() + GetB() * segment.GetStart().GetY() + GetC() == 0) {
            return true;
        }
        return false;
    }
    double ans_x = delta_x / delta;
    double ans_y = delta_y / delta;
    return ans_x >= min_x && ans_x <= max_x && ans_y >= min_y && ans_y <= max_y;
}
Line* Line::Clone() const {
    Line* line = new Line(start_, end_);
    return line;
}
}  // namespace geometry