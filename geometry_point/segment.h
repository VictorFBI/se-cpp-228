#pragma once
#include "i_shape.h"
#include "point.h"

namespace geometry {
class Segment : public IShape {
private:
    Point start_;
    Point end_;

public:
    Segment();

    Segment(Point, Point);

    Point GetStart() const;

    Point GetEnd() const;

    Segment& Move(const Vector&) override;

    bool ContainsPoint(const Point&) const override;

    bool CrossesSegment(const Segment&) const override;

    Segment* Clone() const override;
};
}  // namespace geometry
