#pragma once
#include "geometry/coord.hpp";
#include "collision/collision.hpp";

/**
 * A capsule is the set of points within radius R of a specified line.
*/
class Capsule {
    protected:
        double radius;
        Capsule();

    friend class Collision;
};

/**
 * A fixed-length capsule, which uses a line segment as a base.
*/
class SegmentCapsule : Capsule {
    private:
        Coord start, end;

    public:
        SegmentCapsule(double radius, Coord &segmentStart, Coord &segmentEnd);

    friend class Collision;
};

/**
 * An infinite-length capsule, which uses a ray as a base.
*/
class RayCapsule : Capsule {
    private:
        Ray line;

    public:
        RayCapsule(double radius, Ray &line);

    friend class Collision;
};