
#pragma once

#include "MonteCarloAIExport.h"

template <typename T>
struct MONTE_CARLO_EXPORT Coordinate2D
{
    T x;
    T y;

    Coordinate2D operator+(const Coordinate2D& rhs) const;
};

template <typename T>
inline Coordinate2D<T> Coordinate2D<T>::operator+(const Coordinate2D& rhs) const
{
    return {x + rhs.x, y + rhs.y};
}

typedef Coordinate2D<int> CoordinateXY;

class MONTE_CARLO_EXPORT Direction
{
public:
    enum Heading
    {
        DIRECTION_NORTH         = 0,
        DIRECTION_NORTH_EAST    = 1,
        DIRECTION_EAST          = 2,
        DIRECTION_SOUTH_EAST    = 3,
        DIRECTION_SOUTH         = 4,
        DIRECTION_SOUTH_WEST    = 5,
        DIRECTION_WEST          = 6,
        DIRECTION_NORTH_WEST    = 7
    };

    Heading                 heading() const;
    const Direction&        opposite() const;
    const CoordinateXY&     coordinate() const;

    static const Direction& north();
    static const Direction& northEast();
    static const Direction& east();
    static const Direction& southEast();
    static const Direction& south();
    static const Direction& southWest();
    static const Direction& west();
    static const Direction& northWest();

private:
    Direction(const Heading& heading);
    Direction(const Direction& copy);
    Direction(Direction&& move);

    Heading m_heading;
};
