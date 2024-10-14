#pragma once
#include "geometry/tri.hpp";
#include "geometry/boundingSphere.hpp";
#include <vector>

class Mesh3D {
    private:
        std::vector<Tri> tris;
        BoundingSphere minimumBound;
    
        Mesh3D(std::vector<Tri> &tris, BoundingSphere &boundary);

    public:
        BoundingSphere getMinimumBoundingSphere();

    friend class MeshBuilder;
};