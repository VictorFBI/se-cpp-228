#include "vector.h"
namespace geometry {
int64_t ScalarMult(const Vector& first, const Vector& second) {
    return first.x_coord_ * second.x_coord_ + first.y_coord_ * second.y_coord_;
}
int64_t VectorMult(const Vector& first, const Vector& second) {
    return first.x_coord_ * second.y_coord_ - first.y_coord_ * second.x_coord_;
}
double Length(Vector vector) {
    return std::sqrt(vector.x_coord_ * vector.x_coord_ + vector.y_coord_ * vector.y_coord_);
}
}  // namespace geometry
geometry::Vector::Vector() : Vector(0, 0) {
}
geometry::Vector::Vector(int64_t x, int64_t y) {
    x_coord_ = x;
    y_coord_ = y;
}
int64_t geometry::Vector::GetX() const {
    return x_coord_;
}
int64_t geometry::Vector::GetY() const {
    return y_coord_;
}
geometry::Vector geometry::Vector::operator+(const geometry::Vector& other) const {
    return Vector(x_coord_ + other.x_coord_, y_coord_ + other.y_coord_);
}
geometry::Vector geometry::Vector::operator-(const geometry::Vector& other) const {
    return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
}
geometry::Vector geometry::Vector::operator+() const {
    return Vector(x_coord_, y_coord_);
}
geometry::Vector geometry::Vector::operator-() const {
    return Vector(-x_coord_, -y_coord_);
}
geometry::Vector geometry::Vector::operator*(int64_t number) const {
    return Vector(x_coord_ * number, y_coord_ * number);
}
geometry::Vector geometry::Vector::operator/(int64_t number) const {
    return Vector(x_coord_ / number, y_coord_ / number);
}
geometry::Vector& geometry::Vector::operator+=(const geometry::Vector& other) {
    x_coord_ += other.x_coord_;
    y_coord_ += other.y_coord_;
    return *this;
}
geometry::Vector& geometry::Vector::operator-=(const geometry::Vector& other) {
    x_coord_ -= other.x_coord_;
    y_coord_ -= other.y_coord_;
    return *this;
}
geometry::Vector& geometry::Vector::operator*=(int64_t number) {
    x_coord_ *= number;
    y_coord_ *= number;
    return *this;
}
geometry::Vector& geometry::Vector::operator/=(int64_t number) {
    x_coord_ /= number;
    y_coord_ /= number;
    return *this;
}
bool geometry::Vector::operator==(const geometry::Vector& other) const {
    return other.x_coord_ == x_coord_ && other.y_coord_ == y_coord_;
}
