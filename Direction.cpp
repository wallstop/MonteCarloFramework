
#include "Direction.h"
#include <map>

static const std::map<Direction::Heading, CoordinateXY> DIRECTION_COORDINATE_MAP = 
    {
        {Direction::DIRECTION_NORTH,        {0, 1}}, 
        {Direction::DIRECTION_NORTH_EAST,   {1, 1}}, 
        {Direction::DIRECTION_EAST,         {1, 0}},
        {Direction::DIRECTION_SOUTH_EAST,   {1, -1}},
        {Direction::DIRECTION_SOUTH,        {0, -1}},
        {Direction::DIRECTION_SOUTH_WEST,   {-1, -1}},
        {Direction::DIRECTION_WEST,         {-1, 0}},
        {Direction::DIRECTION_NORTH_WEST,   {-1, 1}}
    };

static const std::map<Direction::Heading, const Direction&> HEADING_DIRECTION_MAP = 
    {
        {Direction::DIRECTION_NORTH,        Direction::north()}, 
        {Direction::DIRECTION_NORTH_EAST,   Direction::northEast()}, 
        {Direction::DIRECTION_EAST,         Direction::east()},
        {Direction::DIRECTION_SOUTH_EAST,   Direction::southEast()},
        {Direction::DIRECTION_SOUTH,        Direction::south()},
        {Direction::DIRECTION_SOUTH_WEST,   Direction::southWest()},
        {Direction::DIRECTION_WEST,         Direction::west()},
        {Direction::DIRECTION_NORTH_WEST,   Direction::northWest()}
    };

inline Direction::Heading Direction::heading() const
{
    return m_heading;
}

inline const Direction& Direction::opposite() const
{
    return HEADING_DIRECTION_MAP.at((Heading)(((int)m_heading + 4) % 8));
}

const CoordinateXY& Direction::coordinate() const
{
    return DIRECTION_COORDINATE_MAP.at(m_heading);
}

const Direction& Direction::north()
{
    static Direction north(DIRECTION_NORTH);
    return north;
}

const Direction& Direction::northEast()
{
    static Direction northEast(DIRECTION_NORTH_EAST);
    return northEast;
}

const Direction& Direction::east()
{
    static Direction east(DIRECTION_EAST);
    return east;
}

const Direction& Direction::southEast()
{
    static Direction southEast(DIRECTION_SOUTH_EAST);
    return southEast;
}

const Direction& Direction::south()
{
    static Direction south(DIRECTION_SOUTH);
    return south;
}

const Direction& Direction::southWest()
{
    static Direction southWest(DIRECTION_SOUTH_WEST);
    return southWest;
}

const Direction& Direction::west()
{
    static Direction west(DIRECTION_WEST);
    return west;
}

const Direction& Direction::northWest()
{
    static Direction northWest(DIRECTION_NORTH_WEST);
    return northWest;
}

Direction::Direction(const Heading& heading) : m_heading(heading)
{
}

