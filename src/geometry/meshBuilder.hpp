#pragma once
#include "geometry/tri.hpp";
#include "geometry/mesh3d.hpp";
#include <vector>

/**
 * Recieves multiple tris and (planar) quads, converting them into a single large 3D mesh object.
*/
class MeshBuilder {
    private:
        std::vector<Tri> addedTris;
        BoundingSphere minimumBound;

    public:
        MeshBuilder();

        /**
         * Adds a triangle to the 3D mesh.
         * @param point1 @param point2 @param point3 Points of the triangle
        */
        void addTri(Coord &point1, Coord &point2, Coord &point3);

        /**
         * Adds a planar quad to the 3D mesh.
         * @param point1 @param point2 @param point3 @param point4 points of the quad.
        */
        void addQuad(Coord &point1, Coord &point2, Coord &point3, Coord &point4);

        /**
         * Build a 3D mesh from the provided tris and quads.
         * 
         * @return The built 3D Mesh.
        */
        Mesh3D build();
};