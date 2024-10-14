#pragma once
#include "geometry/tri.hpp";

Tri::Tri(Coord &corner1, Coord &corner2, Coord &corner3) : corner1(corner1), corner2(corner2), corner3(corner3) {
}

std::pair<Tri, Tri> Tri::divide(Coord &corner1, Coord &corner2, Coord &corner3, Coord &corner4) {
    return { Tri(corner1, corner2, corner3), Tri(corner1, corner3, corner4) };
}