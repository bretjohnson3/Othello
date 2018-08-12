#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector> 
#include <cstdlib>
#include <stdlib.h>
#include "common.hpp"
#include "board.hpp"

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Board* board;

    int spaces_left(Board* board);
    int mini_score(int depth, int max_depth, Side side, Board* board);
    Move* minimax(int depth, int max_depth, Side side, Board* board);
    Move* minimax_naive();
    int get_num_moves(Side side);
    int heuristicScore(Move* move, Board* board, Side side);
    int naiveHeuristic(Move* move, Board* board, Side side);
    Move *randomMove(vector<Move*> moves);
    vector<Move*> get_moves(Side side, Board* board);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;


private:
	Side my_side;
	Side opposite_side;
};

#endif
