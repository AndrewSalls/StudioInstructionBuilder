/**
 * A point in 3D space, which can also represent a vector from 0, 0, 0.
*/
class Coord {
    public:
        double x, y, z;

        Coord(double x, double y, double z);
        double distanceTo(const Coord &other) const;
        double magnitude() const;
        Coord unitize() const;
        Coord cross(const Coord &other) const;
        double dot(const Coord &other) const;

        Coord operator +(const Coord &other) const;
        Coord operator -(const Coord &other) const;
        Coord operator -() const;
};

static constexpr double EPSILON = 1E-9;
Coord operator *(double scalar, const Coord &multiple);