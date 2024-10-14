#pragma once
#include "geometry/coord.hpp";
#include <cmath>

Coord::Coord(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

double Coord::distanceTo(const Coord &other) const {
    double xDiff = other.x - this->x;
    double yDiff = other.y - this->y;
    double zDiff = other.z - this->z;
    return std::sqrt(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff);
}

double Coord::magnitude() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Coord Coord::unitize() const {
    double mag = magnitude();
    return Coord(this->x / mag, this->y / mag, this->z / mag);
}

Coord Coord::cross(const Coord &other) const {
    return Coord(this->y * other.z - this->z * other.y, this->x * other.z - this->z * other.x, this->x * other.y - this->y * other.x);
}

double Coord::dot(const Coord &other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Coord Coord::operator +(const Coord &other) const {
    return Coord(this->x + other.x, this->y + other.y, this->z + other.z);
}

Coord Coord::operator -(const Coord &other) const {
    return operator +(Coord(-other.x, -other.y, -other.z));
}

Coord Coord::operator -() const {
    return Coord(-this->x, -this->y, -this->z);
}

Coord operator *(double scalar, const Coord &multiple) {
    return Coord(multiple.x * scalar, multiple.y * scalar, multiple.z * scalar);
}