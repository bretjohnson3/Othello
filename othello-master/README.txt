Week 1:

Aaron set up the github repository and made the inital commits and other set up duties. He also did research on othello and common 
strategies and heuristics. He helped tweak the heuristic based on how it was performing.

Bret got everything running by first setting up a random player that did the work. He then wrote the initial heuristic which he and 
Aaron later changed and tweaked. He also wrote the minimax function and got it to where it passed the test and functioned properly.

Week 2:

Aaron continued to research strategy and make adjustments based on how we think our bot would best compete against other bots. He 
helped work to modify the minimax function.

Bret worked to adapt the minimax function so that it could go to greater depth. He attended the recitation with the Othello 
champion (Jack Sealy?) to get new ideas for implementation. He also did research on opening books and attempted to implement a
simple version.

Strategy:
Our heuristic takes into account mobility, corner pieces, edge pieces, tokens taken, and "bad spaces". We weight certain board
spots based on how we think the spots are generally favorable or unfavorable. We used this heuristic when we use our minimax
implementation. This way, we look several moves ahead and determine if that is the best board state for us.