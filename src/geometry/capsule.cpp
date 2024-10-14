#pragma once
#include "geometry/capsule.hpp";

Capsule::Capsule() {
    this->radius = 0;
}

SegmentCapsule::SegmentCapsule(double radius, Coord &segmentStart, Coord &segmentEnd) : start(segmentStart), end(segmentEnd) {
    this->radius = radius;
}

 RayCapsule::RayCapsule(double radius, Ray &line) : line(line) {
    this->radius = radius;
 }