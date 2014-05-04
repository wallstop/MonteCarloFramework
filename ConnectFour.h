
#pragma once

#include "AbstractDeterministicGame.h"
#include "Direction.h"

#include <array>
#include <list>

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
        static const int ROW_SIZE = 6;
        static const int COLUMN_SIZE = 7;

        bool isInBounds(const Move& move) const;
        bool isInBounds(const CoordinateXY& coordinate) const;
        bool checkMove(const CoordinateXY& coordinate, const Player& player) const;
        unsigned int recursiveCheckMove(const CoordinateXY& coordinate, const Player& player, const Direction& direction) const;

        std::array<std::list<Player>, ROW_SIZE> m_board;
        unsigned int                            m_filledColumns;
        // Not an owned pointer (DO NOT DELETE)
        const Player*                           m_winningPlayer;
        bool                                    m_solved;
    };

private:
    Board   m_board;
    std::list<Move> m_moves;
};
