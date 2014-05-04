
#include "ConnectFour.h"

#include <limits>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// Helper functions and constants

static const unsigned int INVALID_COLUMN = UINT_MAX;
static const unsigned int NUM_TO_WIN = 4;

static const std::list<const Direction*> ITERABLE_DIRECTIONS = {&(Direction::north()), &(Direction::northEast()), &(Direction::east()), &(Direction::southEast())};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// ConnectFour::Player impl

const ConnectFour::Player& ConnectFour::Player::getAI()
{
    static Player ai(PLAYER_TYPE_AI);
    return ai;
}

const ConnectFour::Player& ConnectFour::Player::getHuman()
{
    static Player human(PLAYER_TYPE_HUMAN);
    return human;
}

const ConnectFour::Player& ConnectFour::Player::getInvalid()
{
    static Player invalid(PLAYER_TYPE_UNKNOWN);
    return invalid;
}

const ConnectFour::Player& ConnectFour::Player::getOpposite() const
{
    switch(m_type)
    {
    case PLAYER_TYPE_AI:
        return getHuman();
    case PLAYER_TYPE_HUMAN:
        return getAI();
    case PLAYER_TYPE_UNKNOWN:
    default:
        return getInvalid();
    }
}

ConnectFour::Player::Player() : m_type(PLAYER_TYPE_UNKNOWN)
{
}

ConnectFour::Player::Player(const Player& copy) : m_type(copy.m_type)
{
}

ConnectFour::Player::Player(Player&& move) : m_type(move.m_type)
{
}

ConnectFour::Player::Player(const Type& type) : m_type(type)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// ConnectFour::Move impl

ConnectFour::Move::Move() : m_owner(Player::getAI()), m_column(INVALID_COLUMN)
{
}

ConnectFour::Move::Move(const Move& copy) : m_owner(copy.m_owner), m_column(copy.m_column)
{
}

ConnectFour::Move::Move(Move&& move) : m_owner(move.m_owner), m_column(move.m_column)
{
}

ConnectFour::Move::Move(const Player& player, unsigned int column) : m_owner(player), m_column(column)
{
}

unsigned int ConnectFour::Move::column() const
{
    return m_column;
}

const ConnectFour::Player& ConnectFour::Move::player() const
{
    return m_owner;
}

const ConnectFour::Move& ConnectFour::Move::getInvalid()
{
    static Move invalid;
    return invalid;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// ConnectFour::Board impl

ConnectFour::Board::Board() : m_filledColumns(0), m_winningPlayer(&(Player::getInvalid())), m_solved(false)
{
}

ConnectFour::Board::Board(const Board& copy) 
    : m_board(copy.m_board), m_filledColumns(copy.m_filledColumns), 
        m_winningPlayer(copy.m_winningPlayer), m_solved(copy.m_solved)
{
}

ConnectFour::Board::Board(Board&& move) : m_board(move.m_board), m_filledColumns(move.m_filledColumns),
    m_winningPlayer(move.m_winningPlayer), m_solved(move.m_solved)
{
}

ConnectFour::Board::Board(const std::list<Move>& moves) : m_winningPlayer(&(Player::getInvalid())), m_solved(false)
{
    for(const Move& move : moves)
        addMove(move);
}

ConnectFour::Board::Board(const Board& board, const Move& move) : m_board(board.m_board), m_filledColumns(board.m_filledColumns),
    m_winningPlayer(board.m_winningPlayer), m_solved(board.m_solved)
{
    addMove(move);
}

bool ConnectFour::Board::addMove(const Move& move)
{
    if(!isInBounds(move))
        return false;

    m_solved = m_solved || testMove(move);
    m_board[move.column()].push_back(move.player());

    if(m_solved)
        m_winningPlayer = &(move.player());
    if(m_board[move.column()].size() == COLUMN_SIZE)
        ++m_filledColumns;

    return m_solved;
}

bool ConnectFour::Board::testMove(const Move& move) const
{
    if(!isInBounds(move))
        return false;

    unsigned int x = move.column();
    // The move comes in on top of the column, so its (size - 1) + 1
    unsigned int y = (unsigned int)m_board[x].size();

    return checkMove({x, y}, move.player());
}

inline bool ConnectFour::Board::isSolved() const
{
    return m_solved;
}

inline bool ConnectFour::Board::isFull() const
{
    return m_filledColumns == m_board.size();
}

inline bool ConnectFour::Board::isInBounds(const Move& move) const
{
    return move.column() < m_board.size()
        && m_board[move.column()].size() < COLUMN_SIZE;
}

inline bool ConnectFour::Board::isInBounds(const CoordinateXY& coordinate) const
{
    return coordinate.x < (int)m_board.size()
        && coordinate.y < COLUMN_SIZE;
}

bool ConnectFour::Board::checkMove(const CoordinateXY& coordinate, const Player& player) const
{
    bool ret = false;
    for(auto& direction : ITERABLE_DIRECTIONS)
    {
        if(direction == nullptr)
            continue;
        ret = ret || ((recursiveCheckMove(coordinate, player, *direction) + recursiveCheckMove(coordinate, player, direction->opposite())) + 1 >= NUM_TO_WIN);
    }

    return ret;
}

unsigned int ConnectFour::Board::recursiveCheckMove(const CoordinateXY& coordinate, const Player& player, const Direction& direction) const
{
    const CoordinateXY& newCoordinate = coordinate + direction.coordinate();
    if(isInBounds(newCoordinate))
        return recursiveCheckMove(newCoordinate, player, direction) + 1;

    return 0;
}






