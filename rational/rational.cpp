#include "rational.h"

Rational::Rational() {
    Set(0, 1);
}
Rational::Rational(int value) {  // NOLINT
    Set(value, 1);
}
Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}
int Rational::GetNumerator() const {
    return numer_;
}
int Rational::GetDenominator() const {
    return denom_;
}
void Rational::SetNumerator(int value) {
    Set(value, denom_);
}
void Rational::SetDenominator(int value) {
    Set(numer_, value);
}
void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int gcd = std::gcd(static_cast<int>(numer), static_cast<int>(denom));
    numer /= gcd;
    denom /= gcd;
    if (denom < 0) {
        numer *= -1;
        denom *= -1;
    }
    numer_ = static_cast<int>(numer);
    denom_ = static_cast<int>(denom);
}
Rational operator+(const Rational &ratio) {
    auto tmp = ratio;
    return tmp;
}
Rational &operator/=(Rational &lhs, const Rational &rhs) {
    lhs *= Rational(1) / rhs;
    return lhs;
}
Rational operator+(const Rational &lhs, const Rational &rhs) {
    int num = lhs.GetNumerator() * rhs.GetDenominator() + lhs.GetDenominator() * rhs.GetNumerator();
    int den = lhs.GetDenominator() * rhs.GetDenominator();
    return Rational(num, den);
}
Rational &operator*=(Rational &lhs, const Rational &rhs) {
    int num = lhs.GetNumerator() * rhs.GetNumerator();
    int den = lhs.GetDenominator() * rhs.GetDenominator();
    lhs.Set(num, den);
    return lhs;
}
Rational operator-(const Rational &ratio) {
    auto tmp = ratio * Rational(-1);
    return tmp;
}
Rational &operator-=(Rational &lhs, const Rational &rhs) {
    lhs += Rational(-1) * rhs;
    return lhs;
}
Rational operator-(const Rational &lhs, const Rational &rhs) {
    return lhs + Rational(-1) * rhs;
}
Rational operator*(const Rational &lhs, const Rational &rhs) {
    int num = lhs.GetNumerator() * rhs.GetNumerator();
    int den = lhs.GetDenominator() * rhs.GetDenominator();
    return Rational(num, den);
}
Rational operator/(const Rational &lhs, const Rational &rhs) {
    if (rhs == Rational(0)) {
        throw RationalDivisionByZero{};
    }
    int num = lhs.GetNumerator() * rhs.GetDenominator();
    int den = lhs.GetDenominator() * rhs.GetNumerator();
    return Rational(num, den);
}
Rational operator++(Rational &ratio, int) {
    Rational tmp = ratio;
    ratio += Rational(1);
    return tmp;
}
Rational operator--(Rational &ratio, int) {
    Rational tmp = ratio;
    ratio -= Rational(1);
    return tmp;
}
bool operator>(const Rational &lhs, const Rational &rhs) {
    return (lhs - rhs).GetNumerator() > 0;
}
bool operator<=(const Rational &lhs, const Rational &rhs) {
    return !(lhs > rhs);
}
bool operator>=(const Rational &lhs, const Rational &rhs) {
    return !(lhs < rhs);
}
Rational &operator++(Rational &ratio) {
    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());
    return ratio;
}
bool operator<(const Rational &lhs, const Rational &rhs) {
    return (lhs - rhs).GetNumerator() < 0;
}
bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs >= rhs && lhs <= rhs;
}
std::ostream &operator<<(std::ostream &os, const Rational &ratio) {
    if (ratio.GetDenominator() == 1) {
        os << ratio.GetNumerator();
    } else {
        os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
    }
    return os;
}
Rational &operator+=(Rational &lhs, const Rational &rhs) {
    int num = lhs.GetNumerator() * rhs.GetDenominator() + lhs.GetDenominator() * rhs.GetNumerator();
    int den = lhs.GetDenominator() * rhs.GetDenominator();
    lhs.Set(num, den);
    return lhs;
}
Rational &operator--(Rational &ratio) {
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());
    return ratio;
}
std::istream &operator>>(std::istream &is, Rational &ratio) {
    int num = 0;
    int den = 1;
    is >> num;
    if (is.peek() == '/') {
        is.ignore(1);
        is >> den;
    }
    ratio = Rational(num, den);
    return is;
}
bool operator!=(const Rational &lhs, const Rational &rhs) {
    return !(lhs == rhs);
}