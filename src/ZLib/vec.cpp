#include <ZLib/vec.h>
#include <cmath>


Vec2 Vec2::operator+(const Vec2& a) const { return Vec2(x+a.x, y+a.y); }
Vec2 Vec2::operator-(const Vec2& a) const { return Vec2(x-a.x, y-a.y); }
Vec2 Vec2::operator*(double s)      const { return Vec2(x*s,   y*s  ); }
Vec2 Vec2::operator/(double s)      const { return Vec2(x/s,   y/s  ); }

double Vec2::operator*(const Vec2& a) const { return x*a.x + y*a.y; } // Dot Product

Vec2& Vec2::operator+=(const Vec2& a)  { x += a.x; y += a.y; return *this; }
Vec2& Vec2::operator-=(const Vec2& a)  { x -= a.x; y -= a.y; return *this; }
Vec2& Vec2::operator*=(double s)       { x *= s;   y *= s;   return *this; }
Vec2& Vec2::operator/=(double s)       { x /= s;   y /= s;   return *this; }

double Vec2::sqlen() const { return x*x + y*y; }
double Vec2::len() const { return std::sqrt(sqlen()); }

Vec2 Vec2::norm() const { return *this / len(); }