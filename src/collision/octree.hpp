#pragma once
#include "geometry/mesh3d.hpp";
#include "geometry/capsule.hpp";
#include <memory>

// The maximum number of elements in a Node's values vector before creating new leaf nodes.
static constexpr int MAX_NODE_COUNT = 8;

// The minimum number of child nodes before calling rebalance
static constexpr int MIN_SIZE_FOR_REBALANCE = 32;

// In addition to having enough children, the node must also have at least one child
// containing over this percentage of the total children to rebalance
static constexpr int PERCENTAGE_FOR_REBALANCE = 0.4;

//MINUS X = 1, MINUS Y = 2, MINUS Z = 4, bitfield
typedef enum Octant : int {
    PLUS_XYZ = 0,
    PLUS_XY_MINUS_Z = 1,
    PLUS_XZ_MINUS_Y = 2,
    PLUS_YZ_MINUS_X = 4,
    PLUS_X_MINUS_YZ = 3,
    PLUS_Y_MINUS_XZ = 5,
    PLUS_Z_MINUS_XY = 6,
    MINUS_XYZ = 7
};

/**
 * A recursive tree that divides 3D space into octants, placing 3D meshes into a specific octant based on their BoundingSpheres.
*/
class Octree {
    private:
        // For our purposes 0 is positive
        std::vector<std::shared_ptr<Mesh3D>> xPosValues, yPosValues, zPosValues, xNegValues, yNegValues, zNegValues;
        std::vector<std::shared_ptr<Mesh3D>> values;
        int totalChildren;
        Coord minCorner, center, maxCorner;
        //plusXYZ, plusXYminusZ, plusXZminusY, plusYZminusX, plusXminusYZ, plusYminusXZ, plusZminusXY, minusXYZ
        std::unique_ptr<Octree> children[8];

        /**
         * Splits the current values into balanced children. Do not use if children already exist.
        */
        void splitValues();
        /**
         * Adds the mesh to the axes it intersects (if any), and the general value vector.
        */
        void addToAxes(int xSign, int ySign, int zSign, Mesh3D &toAdd);

    public:
        Octree(Coord &minBound, Coord &maxBound);
        void addNode(Mesh3D &toAdd);
        std::vector<Mesh3D> getCollisions(BoundingSphere &bound);
        std::vector<Mesh3D> getCollisions(RayCapsule &bound);

        /**
         * Returns the number of 3D meshs in this node and all of its children.
         * 
         * @return the number of children of the node and all children.
        */
        int getChildrenCount();

        /**
         * Attempts to shift nodes and their x, y, and z axis lines to minimize the tree depth.
         * 
         * This will, in most cases, take a long time.
        */
        void rebalance();

        /**
         * Returns true if the octree node has no children.
         * 
         * @return true if the node has children, false otherwise.
        */
        bool isLeaf();
};