#pragma once
#include "geometry/coord.hpp";
#include <optional>

/**
 * A sphere, intended for use as a bounding bubble that encloses a more complex 3D shape.
*/
class BoundingSphere {
    private:
        Coord center;
        double radius;

    public:
        BoundingSphere(Coord &center, double radius);

        /**
         * "Envelop" a point. This is done by finding the smallest sphere that can contain both this sphere and the provided point,
         * and updating this sphere with those values. Note that this almost always involves altering the center coordinates.
         * 
         * @param target The point to envelop.
        */
        void envelop(const Coord &target);

        friend class Collision;
};