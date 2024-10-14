#pragma once
#include "geometry/meshBuilder.hpp";

MeshBuilder::MeshBuilder() : minimumBound(Coord(0, 0, 0), 0) {
    this->addedTris = {};
}

void MeshBuilder::addTri(Coord &point1, Coord &point2, Coord &point3) {
    if(this->addedTris.size() == 0) {
        this->minimumBound = BoundingSphere(0.5 * (point2 + point1), point1.distanceTo(point2) * 0.5);
    }

    this->addedTris.push_back(Tri(point1, point2, point3));
    this->minimumBound.envelop(point1);
    this->minimumBound.envelop(point2);
    this->minimumBound.envelop(point3);
}

void MeshBuilder::addQuad(Coord &point1, Coord &point2, Coord &point3, Coord &point4) {
    if(this->addedTris.size() == 0) {
        this->minimumBound = BoundingSphere(0.5 * (point2 + point1), point1.distanceTo(point2) * 0.5);
    }

    std::pair<Tri, Tri> tris = Tri::divide(point1, point2, point3, point4);
    this->addedTris.push_back(tris.first);
    this->addedTris.push_back(tris.second);
    this->minimumBound.envelop(point1);
    this->minimumBound.envelop(point2);
    this->minimumBound.envelop(point3);
    this->minimumBound.envelop(point4);
}

Mesh3D MeshBuilder::build() {
    return Mesh3D(this->addedTris, this->minimumBound);
}