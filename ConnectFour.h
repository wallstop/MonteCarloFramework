
#pragma once

#include "AbstractDeterministicGame.h"
#include "Direction.h"

#include <array>
#include <list>

#if defined ROW_SIZE
    #undef  ROW_SIZE
#endif
#define     ROW_SIZE 7u


#if defined COLUMN_SIZE
    #undef  COLUMN_SIZE
#endif
#define     COLUMN_SIZE 6u

class ConnectFour : public AbstractDeterministicGame
{
public:

    class Player
    {
    public:
        enum Type
        {
            PLAYER_TYPE_UNKNOWN,
            PLAYER_TYPE_AI,
            PLAYER_TYPE_HUMAN
        };

        Player(const Player& copy);

        static const Player&    getAI();
        static const Player&    getHuman();
        static const Player&    getInvalid();
        const Player&           getOpposite() const;

    private:
        Player();
        Player(Player&& move);
        Player(const Type& type);

        const Type m_type;
    };

    class Move : public AbstractMove
    {
    public:
        Move();
        Move(const Move& copy);
        Move(Move&& move);
        Move(const Player& player, unsigned int column);
        
        unsigned int            column() const;
        const Player&           player() const;
        static const Move&      getInvalid();

    private:
        const Player&           m_owner;
        const unsigned int      m_column;
    };

    class Board
    {
    public:
        Board();
        Board(const Board& copy);
        Board(Board&& move);
        Board(const std::list<Move>& moves);
        Board(const Board& board, const Move& move);

        bool addMove(const Move& move);
        bool testMove(const Move& move) const;
        bool isSolved() const;
        bool isFull() const;

    private:
        bool isInBounds(const Move& move) const;
        bool isInBounds(const Coordinate& coordinate) const;
        bool checkMove(const Coordinate& coordinate, const Player& player, const Direction& direction) const;
        unsigned int recursiveCheckMove(const Coordinate& coordinate, const Player& player, const Direction& direction) const;

        std::array<std::list<Player>, ROW_SIZE> m_board;
        unsigned int                            m_filledColumns;
        Player                                  m_winningPlayer;
        bool                                    m_solved;
    };

private:
    Board   m_board;
    std::list<Move> m_moves;


};