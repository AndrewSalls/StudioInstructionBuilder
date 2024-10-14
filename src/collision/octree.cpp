#pragma once
#include "collision/octree.hpp";
#include <stdexcept>


Octree::Octree(Coord &minBound, Coord &maxBound) : minCorner(minBound), maxCorner(maxBound) , center(0.5 * (minBound + maxBound)) {
}

void Octree::splitValues() {
    //Initialize all children
}

void Octree::addNode(Mesh3D &toAdd) {
    this->totalChildren++;
    BoundingSphere bSphere = toAdd.getMinimumBoundingSphere();
    int xSign = Collision::sphereAxisSign(bSphere, X, this->center.x);
    int ySign = Collision::sphereAxisSign(bSphere, Y, this->center.y);
    int zSign = Collision::sphereAxisSign(bSphere, Z, this->center.z);

    if(this->totalChildren <= MAX_NODE_COUNT) {
        this->values.push_back(std::make_shared<Mesh3D>(toAdd));

        if(this->totalChildren == MAX_NODE_COUNT) {
            this->splitValues();
        }

        addToAxes(xSign, ySign, zSign, toAdd);
    }

    if(xSign == -1 || ySign == -1 || zSign == -1) {
        addToAxes(xSign, ySign, zSign, toAdd);

        if(this->values.size() > MIN_SIZE_FOR_REBALANCE && this->values.size() > PERCENTAGE_FOR_REBALANCE * this->totalChildren) {
            this->rebalance();
        }
    } else {
        Octant childDirection = static_cast<Octant>(xSign + 2 * ySign + 4 * zSign);
        if(this->children[childDirection]) {
            this->children[childDirection].get()->addNode(toAdd);
        } else {
            throw std::runtime_error("splitValues should be called before attempting to add to children, or children should be manually initialized.");
        }

        if(this->children[childDirection].get()->totalChildren > MIN_SIZE_FOR_REBALANCE
        && this->children[childDirection].get()->totalChildren > PERCENTAGE_FOR_REBALANCE * this->totalChildren) {
            this->rebalance();
        }
    }
}

void Octree::addToAxes(int xSign, int ySign, int zSign, Mesh3D &toAdd) {
    std::shared_ptr<Mesh3D> ptr = std::make_shared<Mesh3D>(toAdd);
    switch(xSign) {
        case 1:
            xNegValues.push_back(ptr);
            break;
        case 0:
            xPosValues.push_back(ptr);
            break;
        case -1:
            xNegValues.push_back(ptr);
            xPosValues.push_back(ptr);
            break;
    }

    switch(ySign) {
        case 1:
            yNegValues.push_back(ptr);
            break;
        case 0:
            yPosValues.push_back(ptr);
            break;
        case -1:
            yNegValues.push_back(ptr);
            yPosValues.push_back(ptr);
            break;
    }

    switch(zSign) {
        case 1:
            zNegValues.push_back(ptr);
            break;
        case 0:
            zPosValues.push_back(ptr);
            break;
        case -1:
            zNegValues.push_back(ptr);
            zPosValues.push_back(ptr);
            break;
    }

    values.push_back(ptr);
}

std::vector<Mesh3D> Octree::getCollisions(BoundingSphere &bound) {

}

std::vector<Mesh3D> Octree::getCollisions(RayCapsule &bound) {

}

void Octree::rebalance() {

}

bool Octree::isLeaf() {
    return this->totalChildren < MAX_NODE_COUNT;
}