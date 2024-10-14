#pragma once
#include "geometry/coord.hpp";
#include "geometry/tri.hpp";
#include "geometry/capsule.hpp";

/**
 * A math library of collision functions for various geometry objects.
*/
class Collision {
    private:
        Collision();
        /**
         * Finds the distance from a specific point to the provided Tri.
         * 
         * @param first The Tri to find the distance to.
         * @param lineStart The specific point to find the distance from.
         * @param unitVector The direction to move from lineStart
         * 
         * @return The distance to the intersection point on the Tri, or nothing if the line doesn't intersect.
        */
        static std::optional<double> triVectorMagnitude(const Tri &first, const Coord &lineStart, const Coord &unitVector);
        
        /**
         * Finds the distance from a specific point to the provided BoundingSphere.
         * 
         * @param first The BoundingSphere to find the distance to.
         * @param lineStart The specific point to find the distance from.
         * @param unitVector The direction to move from lineStart.
         * 
         * @return The distance to the intersection point on the BoundingSphere, or nothing if the line doesn't intersect.
        */
        static std::optional<double> sphereVectorMagnitude(const BoundingSphere &first, const Coord &lineStart, const Coord &unitVector);

        /**
         * Creates a unit vector matching the axis and direction in the provided Ray.
         * 
         * @param line the ray to find a unit vector for.
         * 
         * @return A Coord representing a unit vector along the x, y, or z axis, with direction decided by the ray.
        */
        static Coord rayVector(const Ray &line);

    public:
        static bool triTri(const Tri &first, const Tri &other);
        static bool triSegment(const Tri &first, const Coord &lineStart, const Coord &lineEnd);
        static bool triRay(const Tri &first, const Ray &line);

        static bool sphereSphere(const BoundingSphere &first, const BoundingSphere &other);
        static bool spherePoint(const BoundingSphere &first, const Coord &point);
        static bool sphereSegment(const BoundingSphere &first, const Coord &startLine, const Coord &endLine);
        static bool sphereRay(const BoundingSphere &first, const Ray &line);
        static bool sphereCapsule(const BoundingSphere &first, const RayCapsule &other);
        //1 -> on negative axis, 0 -> on positive axis, -1 -> intersects axis
        static int sphereAxisSign(const BoundingSphere &first, const Axis &direction, const double position);
};

/**
 * A representation of the X, Y, or Z axis
*/
typedef enum Axis {
    X, Y, Z
} Axis;

/**
 * A ray is a line that extends infinitely from a point. This object is a ray that is additionally parallel to an axis.
*/
typedef struct Ray {
    Coord startPoint;
    Axis direction;
    bool isPositiveDirection;
} Ray;