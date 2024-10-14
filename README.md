(WIP)

LEGO Studio is a 3D LEGO modelling software. It contains the ability to generate instructions, however, the built-in tool for dividing parts into steps is a simple bottom-up placement scheme. This is a flawed approach for more complex builds, as it often results in needing to place parts between already placed parts.

To fix this, this program reads the 3D geometry of each part, and checks if it is possible to place the parts by moving them in a straight line along a cardinal direction, or alternatively, if it is possible to place a part by moving it in a straight line orthogonal to its intended placement, then if there is enough space around the part to slide it into place (e.g., placing a part inside of a building. There isn't enough space to directly place it, but you can "reach around" a wall to place it)
