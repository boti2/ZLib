#pragma once

#include <cmath>

class Vec4 {
    public:
        Vec4(double nx, double ny, double nz, double nw) : x(nx), y(ny), z(nz), w(nw) {};

        double x, y, z, w;
};

class Vec3 {
    public:
        Vec3(double nx, double ny, double nz) : x(nx), y(ny), z(nz) {};

        operator Vec4() const { return Vec4(x, y, z, 0); }

        double x, y, z;
};

class Vec2 {
    public:
        Vec2(double nx, double ny) : x(nx), y(ny) {};

        operator Vec3() const { return Vec3(x, y, 0); }
        operator Vec4() const { return Vec4(x, y, 0, 0); }

        double x, y;

        Vec2 operator+(const Vec2& a) const { return Vec2(x+a.x, y+a.y); }
        Vec2 operator-(const Vec2& a) const { return Vec2(x-a.x, y-a.y); }
        Vec2 operator*(double s)      const { return Vec2(x*s,   y*s  ); }
        Vec2 operator/(double s)      const { return Vec2(x/s,   y/s  ); }

        double operator*(const Vec2& a) const { return x*a.x + y*a.y; } // Dot Product

        Vec2& operator+=(const Vec2& a)  { x += a.x; y += a.y; return *this; }
        Vec2& operator-=(const Vec2& a)  { x -= a.x; y -= a.y; return *this; }
        Vec2& operator*=(double s)       { x *= s;   y *= s;   return *this; }
        Vec2& operator/=(double s)       { x /= s;   y /= s;   return *this; }

        double sqlen() const { return x*x + y*y; }
        double len() const { return std::sqrt(sqlen()); }

        Vec2 norm() const { return *this / len(); }
};
