#pragma once
#include "geometry/boundingSphere.hpp";

BoundingSphere::BoundingSphere(Coord &center, double radius) : center(center) {
    this->radius = radius;
}

BoundingSphere::BoundingSphere(double x, double y, double z, double radius) : center(x, y, z) {
    this->radius = radius;
}

void BoundingSphere::envelop(const Coord &target) {
    double distance = this->center.distanceTo(target);
    if(distance <= this->radius + EPSILON) {
        // Already enveloped
        return;
    }

    double newRadius = (distance + this->radius) / 2;

    this->center = this->center + ((newRadius - this->radius) / distance) * (target - this->center);
    this->radius = newRadius;
}