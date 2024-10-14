#pragma once
#include "geometry/coord.hpp";
#include "geometry/boundingSphere.hpp";
#include <optional>

/**
 * A representation of a triangle in 3d space. Three points are also the minimum amount to define a unique 3d plane.
*/
class Tri {
    private:
        Coord corner1, corner2, corner3;
    
    public:
        Tri(Coord &corner1, Coord &corner2, Coord &corner3);

        /**
         * Divides a planar quad into two tris
         * @param corner1 @param corner2 @param corner3 @param corner4 Corners of the quad.
         * Two adjacent corners must create a line segment that does not overlap any other segment of the quad.
         * 
         * @return A pair of tris that do not intersect
        */
        static std::pair<Tri, Tri> divide(Coord &corner1, Coord &corner2, Coord &corner3, Coord &corner4);

    friend class Collision;
};