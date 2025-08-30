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

        Vec2 operator+(const Vec2& a) const;
        Vec2 operator-(const Vec2& a) const;
        Vec2 operator*(double s)      const;
        Vec2 operator/(double s)      const;

        double operator*(const Vec2& a) const;

        Vec2& operator+=(const Vec2& a);
        Vec2& operator-=(const Vec2& a);
        Vec2& operator*=(double s);
        Vec2& operator/=(double s);

        double sqlen() const;
        double len() const;

        Vec2 norm() const;
};
