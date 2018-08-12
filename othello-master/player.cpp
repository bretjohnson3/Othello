#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */





/*

HI AARON!!!!!!!! CAN YOU SEE THIS ?!?!?!?!?!??!!?!!?!?!?!?! 
*/

// howdy do

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board;
    my_side = side;

    if (side == WHITE)
    {
    	opposite_side = BLACK;
    }
    else
    {
    	opposite_side = WHITE;
    }


   
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */

int Player::get_num_moves(Side side)
{
	int count = 0;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Move* move = new Move(i, j);
			if (board->checkMove(move, side) == true)
			{
				count++;
			}
			else
			{
				delete move;
			}
		}
	}
	//cerr << "number of moves ==" << count << endl;
	return count;
}



vector<Move*> Player::get_moves(Side side, Board* b)
{
	vector<Move*> moves;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Move* move = new Move(i, j);
			if (b->checkMove(move, side) == true)
			{
				moves.push_back(move);
			}
			else
			{
				delete move;
			}
			
		}
	}
	//cerr << "checking-----" << endl;
	//cerr << moves.size() << endl;
	return moves;

}

Move *Player::randomMove(vector<Move*> moves)
{
	unsigned int random = rand() % moves.size();
	Move* my_move = moves[random];
	return my_move;

}

int Player::naiveHeuristic(Move* move, Board* b, Side side)
{
	int my_tokens, opp_tokens, difference;

	Board* copy = b->copy();
	copy->doMove(move, side);

	my_tokens = copy->count(my_side);
	opp_tokens = copy->count(opposite_side);

	difference = my_tokens - opp_tokens;

	return difference;
}




int Player::heuristicScore(Move* move, Board* board, Side side)
{
	int my_moves;
	int opp_moves;
	int mobility;
	//int score;

	Side opp_side;
	if (side == WHITE)
	{
		opp_side = BLACK;
	}
	else
	{
		opp_side = WHITE;
	}
	
	// get mobility
	Board* copy = board->copy();
	copy->doMove(move, side);

	my_moves = get_num_moves(side);
	opp_moves = get_num_moves(opp_side);
	mobility = my_moves - opp_moves;


	//getting tokens taken on turn
	int tokens_before;
	int tokens_after;
	int tokens_taken;
	tokens_before = board->count(side);
	tokens_after = copy->count(side);
	tokens_taken = tokens_after - tokens_before;

	//cerr << "mobility:" << mobility << endl << "tokens:" << tokens_taken << endl;

	//checking corners
	int corner = 0;
	int x, y;
	x = move->x;
	y = move->y;
	if ((x==0 && y == 0) || (x==7 && y==7) || (x==0 && y==7) || (x==7 && y==0))
	{
		corner = 90;
		//cerr << "CORNER" << endl;
		
	}

	

	//checking *bad* spots
	int bad = 0;
	if ( (x==1 && y==1) || (x==6 && y==6) || (x==1 && y==6) || (x==6 && y ==1))
	{
		bad = -13;
	}
	int other_bad = 0;
	
	if  ((x+y==1) || (x+y==13) || (x==0 && y==6) || (x==6 && y==0) || (x==1 && y==7) || (x==7 && y==1))
	{
		other_bad = -8;
	}

	//checking edges
	int edge = 0;
	if (    (  (x==0) || (x==7) || (y == 0) || (y==7)  ) && (other_bad == 0)  )
	{
		edge = 3;
	}


	return (mobility * 2)  + (tokens_taken *1.5 ) + corner + edge + bad + other_bad;
}


int Player::mini_score(int depth, int max_depth, Side side, Board* board)
{
	Side opp_side;
	if (side == WHITE)
	{
		opp_side = BLACK;
	}
	else
	{
		opp_side = WHITE;
	}



	while (depth < max_depth - 1)
	{
		//cerr << "in here" << endl;
		vector<Move*> moves = get_moves(opp_side, board);
		if (moves.size() == 0)
		{
			//cerr << "got here!" << endl;
			return 1000;
		}

		
		int best;
		int best_index = 0;
		int current;
		best = heuristicScore(moves[0], board, opp_side);
		
		for (unsigned int i = 1; i < moves.size(); i++)
		{
			current = heuristicScore(moves[i], board, opp_side);
			if (current > best)
			{
				best = current;
				best_index = i;
			}
		}
		board->doMove(moves[best_index], opp_side);

		vector<Move*> our_moves = get_moves(side, board);
		if (our_moves.size()==0)
		{
			return -100;
		}
		int our_best;
		int our_best_index = 0;
		int our_current;

		our_best = heuristicScore(our_moves[0], board, side);
		for (unsigned int j = 1; j<our_moves.size(); j++)
		{
			our_current = heuristicScore(our_moves[j], board, side);
			if (our_current > our_best)
			{
				our_best = our_current;
				our_best_index = j;
			}
		}
		board->doMove(our_moves[our_best_index], side);
	}
	vector<Move*> moves1 = get_moves(opp_side, board);
	if (moves1.size() == 0)
	{
		return 100;
	}


		
	int best1;
	int best_index1 = 0;
	int current1;
	best1 = heuristicScore(moves1[0], board, opp_side);
	
	for (unsigned int i = 1; i < moves1.size(); i++)
	{
		current1 = heuristicScore(moves1[i], board, opp_side);
		if (current1 > best1)
		{
			best1 = current1;
			best_index1 = i;
		}
	}
	board->doMove(moves1[best_index1], opp_side);
	int opp_tokens, our_tokens;
	opp_tokens = board->count(opp_side);
	our_tokens = board->count(side);
	return (our_tokens - opp_tokens);

}


Move* Player::minimax(int depth, int max_depth, Side side, Board* b)
{
	Side opp_side;
	if (side == WHITE)
	{
		opp_side = BLACK;
	}
	else
	{
		opp_side = WHITE;
	}

	int opp_moves;

	vector<Move*> moves = get_moves(side, b);

	int best_score= -100;
	int index=0;
	int current =-101;
	for (unsigned int i=0; i<moves.size(); i++)
	{
		Board* copy = b->copy();
		copy->doMove(moves[i], side);
		opp_moves = get_num_moves(opp_side);
		if (opp_moves == 0)
		{
			return moves[i];
		}

		current = mini_score(depth + 1, max_depth, side, copy);
		if (current > best_score)
		{
			best_score = current;
			index = i;
		}
	}
    return moves[index];

}




Move* Player::minimax_naive()
{
	vector<Move*> moves = this->get_moves(this->my_side, board);
	Move* current_move;
	Move* best_move;
	int temp_score = -700;

	if (moves.size() == 0)
	{
		return nullptr;
	}

	for (unsigned int i =0; i < moves.size(); i++)
	{
		//cerr << "HI" << endl;
		current_move = moves[i];
		//cerr << current_move->x << endl;
		Board* copy = this->board->copy();
		copy->doMove(current_move, this->my_side);
		
		vector<Move*> opp_moves = this->get_moves(this->opposite_side, copy);
		//cerr<<opp_moves.size()<<endl;


		if (opp_moves.size() == 0)
		{
			return current_move;
		}

		// looping thru opponent moves and storing their best move in best_opp_move
		int best_opp_move = naiveHeuristic(opp_moves[0], copy, opposite_side);
		for (unsigned int j = 0; j<opp_moves.size(); j++)
		{
			//cerr << "!!!!!!" << endl;
			int current_opp_move = naiveHeuristic(opp_moves[j], copy, opposite_side);
			//cerr << current_opp_move << "  <- current opponent move" << endl;
			
			if (current_opp_move < best_opp_move)
			{
				best_opp_move = current_opp_move;
			}
		}

		int aggregate = best_opp_move;
		//cerr << aggregate <<endl;

		if (aggregate > temp_score)
		{	
			
			best_move = current_move;
			temp_score = aggregate;
		}
	}
	return best_move;

}

int Player::spaces_left(Board* board)
{
	int count, white, black, remaining;

	white = board->countWhite();
	black = board->countBlack();
	count = black + white;
	remaining = 64 - count;


	return remaining;
}





Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
    
	
    /*if (msLeft == 0)
    {
    	cerr << ":(" << endl;
    	return nullptr;
    }
	*/

	this->board->doMove(opponentsMove, opposite_side);
	Move* myMove;

	vector<Move*> moves = this->get_moves(this->my_side, this->board);
	
	if (moves.size() == 0)
	{
		//cerr << "zero moves" << endl;
		return nullptr;
	}
	/*else if (moves.size() == 1)
	{
		cerr << "hi" << endl;
		return moves[0];
	}
	*/

	int remaining;
	remaining = spaces_left(this->board);
	if (remaining <= 6) 
	{
		//cerr << "Here" << endl;
		myMove = this->minimax_naive();
		//cerr << myMove << endl;
	}
	

	else
	{
		//cerr << "minim" << endl;
		myMove = minimax(0, 8, this->my_side, this->board);
	}
	
	


	this->board->doMove(myMove, my_side);


	return myMove;
}
