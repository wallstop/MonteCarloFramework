
#pragma once

#include <map>

// TODO: Move into class so we stop polluting the global namespace

// DO NOT CHANGE THE ORDER OF THESE (necessary for getOppositeDirection(...))
enum Direction
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

typedef std::pair<unsigned int, unsigned int> Coordinate;

static const std::map<Direction, Coordinate>& generateDirectionMap()
{
    static std::map<Direction, std::pair<unsigned int, unsigned int>> ret;
    if(ret.size() == 0)
    {
        ret[DIRECTION_NORTH] = Coordinate(0, 1);
        ret[DIRECTION_NORTH_EAST] = Coordinate(1, 1);
        ret[DIRECTION_EAST] = Coordinate(1, 0);
        ret[DIRECTION_SOUTH_EAST] = Coordinate(1, -1);
        ret[DIRECTION_SOUTH] = Coordinate(0, -1);
        ret[DIRECTION_SOUTH_WEST] = Coordinate(-1, -1);
        ret[DIRECTION_WEST] = Coordinate(-1, 0);
        ret[DIRECTION_NORTH_WEST] = Coordinate(-1, 1);
    }

    return ret;
}

static const std::map<Direction, Coordinate>& DIRECTION_MAP = generateDirectionMap();

inline Direction getOppositeDirection(const Direction& direction)
{
    return ((Direction)(((int)direction + 4) % 8));
}

unsigned int xIncrementFor(const Direction& direction)
{
    return DIRECTION_MAP.at(direction).first;
}

unsigned int yIncrementFor(const Direction& direction)
{
    return DIRECTION_MAP.at(direction).second;
}

Coordinate getCoordinateFor(const Direction& direction)
{
    return DIRECTION_MAP.at(direction);
}

Coordinate operator+(const Coordinate& lhs, const Coordinate& rhs)
{
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}
