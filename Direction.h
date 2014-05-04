
#pragma once

#include <map>

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

typedef std::pair<unsigned int, unsigned int> XYPair;

static const std::map<Direction, XYPair>& generateDirectionMap()
{
    static std::map<Direction, std::pair<unsigned int, unsigned int>> ret;
    if(ret.size() == 0)
    {
        ret[DIRECTION_NORTH] = XYPair(0, 1);
        ret[DIRECTION_NORTH_EAST] = XYPair(1, 1);
        ret[DIRECTION_EAST] = XYPair(1, 0);
        ret[DIRECTION_SOUTH_EAST] = XYPair(1, -1);
        ret[DIRECTION_SOUTH] = XYPair(0, -1);
        ret[DIRECTION_SOUTH_WEST] = XYPair(-1, -1);
        ret[DIRECTION_WEST] = XYPair(-1, 0);
        ret[DIRECTION_NORTH_WEST] = XYPair(-1, 1);
    }

    return ret;
}

static const std::map<Direction, XYPair>& DIRECTION_MAP = generateDirectionMap();

inline Direction getOppositeDirection(const Direction& direction)
{
    return ((Direction)(((int)direction + 4) % 8));
}
