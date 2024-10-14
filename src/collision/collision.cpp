#pragma once
#include "collision/collision.hpp";
#include <cmath>

Coord Collision::rayVector(const Ray &line) {
    switch(line.direction) {
        case X:
            return Coord(-1 + 2 * line.isPositiveDirection, 0, 0);
        case Y:
            return Coord(0, -1 + 2 * line.isPositiveDirection, 0);
        case Z:
        default:
            return Coord(0, 0, -1 + 2 * line.isPositiveDirection);
    }
}

bool Collision::triTri(const Tri &first, const Tri &other) {
    return triSegment(first, other.corner1, other.corner2) || triSegment(first, other.corner2, other.corner3) || triSegment(first, other.corner3, other.corner1);
}

bool Collision::triSegment(const Tri &first, const Coord &lineStart, const Coord &lineEnd) {
    Coord diff = lineEnd - lineStart;
    std::optional<double> mag = triVectorMagnitude(first, lineStart, diff.unitize());
    return mag.has_value() && mag.value() >= EPSILON && mag.value() <= 1 + EPSILON;
}

bool Collision::triRay(const Tri &first, const Ray &line) {
    std::optional<double> mag = triVectorMagnitude(first, line.startPoint, rayVector(line));
    return mag.has_value() && mag.value() >= EPSILON;
}

std::optional<double> Collision::triVectorMagnitude(const Tri &first, const Coord &lineStart, const Coord &unitVector) {
    Coord edge1 = first.corner2 - first.corner1;
    Coord edge2 = first.corner3 - first.corner1;
    Coord edge2Cross = unitVector.cross(edge2);
    double det = edge1.dot(edge2Cross);

    //TODO: Check for any errors if line passes through triangle while parallel
    if(det > -EPSILON && det < EPSILON)
        return false;

    double inv_det = 1.0 / det;
    Coord offset1 = lineStart - first.corner1;
    double linearCoeff1 = inv_det * offset1.dot(edge2Cross);

    //Coefficients of linear combination are positive and sum to 1.
    if(linearCoeff1 < 0 || linearCoeff1 > 1)
        return false;

    Coord offset2 = offset1.cross(edge1);
    double linearCoeff2 = inv_det * unitVector.dot(offset2);

    //Coefficients positive, sum to 1
    if(linearCoeff2 < 0 || linearCoeff2 > 1)
        return false;

    return inv_det * edge2.dot(offset2);
}

bool Collision::sphereSphere(const BoundingSphere &first, const BoundingSphere &other) {
    return first.center.distanceTo(other.center) <= first.radius + other.radius;
}

bool Collision::spherePoint(const BoundingSphere &first, const Coord &point) {
    return first.center.distanceTo(point) <= first.radius;
}

bool Collision::sphereSegment(const BoundingSphere &first, const Coord &startLine, const Coord &endLine) {
    if(spherePoint(first, startLine) || spherePoint(first, endLine))
        return true;

    Coord diff = endLine - startLine;
    std::optional<double> point = sphereVectorMagnitude(first, startLine, diff.unitize());
    return point.has_value() && point.value() >= EPSILON && point.value() <= diff.magnitude();
}

bool Collision::sphereRay(const BoundingSphere &first, const Ray &line) {
    if(spherePoint(first, line.startPoint))
        return true;

    std::optional<double> point = sphereVectorMagnitude(first, line.startPoint, rayVector(line));
    return point.has_value() && point.value() >= EPSILON;
}

bool Collision::sphereCapsule(const BoundingSphere &first, const RayCapsule &other) {
    std::optional<double> point = sphereVectorMagnitude(first, other.line.startPoint, rayVector(other.line));
    return point.has_value() && point.value() <= first.radius + other.radius;
}

std::optional<double> Collision::sphereVectorMagnitude(const BoundingSphere &first, const Coord &lineStart, const Coord &unitVector) {
    Coord offset = lineStart - first.center;
    double sum = unitVector.dot(offset);
    double mag = offset.x * offset.x + offset.y * offset.y + offset.z * offset.z - first.radius * first.radius;
    double tri = sum * sum - mag;

    if(tri < 0) {
        return {};
    }

    return -sum + std::sqrt(tri);
}

int Collision::sphereAxisSign(const BoundingSphere &first, const Axis &direction, const double position) {
    double self;
    switch(direction) {
        case X:
            self = first.center.x;
            break;
        case Y:
            self = first.center.y;
            break;
        case Z:
        default:
            self = first.center.z;
            break;
    }

    
    if(self + first.radius < position)
        return 1;
    if(self - first.radius > position)
        return 0;
    
    return -1;
}