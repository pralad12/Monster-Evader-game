#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "cavern.h"

int main(int argc, char** argv){
	
	int turn = 0;
	struct Player* p;
	struct Cavern* c = readMap(argv[1], p);
	struct Cavern* c2 = readMap(argv[1], p);
	display(c);
	char* moves;
	int game_finished = 0;
	int eaten = 0;
	
	printf("Welcome to Monster Evader! the '@' represents the player, the '*' represents the monsters, the '$' represents the treasure, 'X' represents a closed door, '-' represents an open door, and '#' represents a cavern wall. To move your player type 'u, d, l, or r' to move up, down, left, and right (You can make up to 5 moves at once but it accounts for 5 turns). To open closed doors, press 't,' and you can skip your turn by pressing '.' . The goal is to get all the treasures. If you step on top of a monster, you kill the monster, but if the monster steps on you, you die and its game over. Have fun!\n");
	while (1) {
		if (game_finished == 1) {
		printf("%s", "You got all the treasures! Congratulations you win!\n");
		break; }
		if (eaten == 1) {
		printf("The monster ate you! Game Over!\n"); 
		break;}
		moves = getMoves();
		for (int i=0; i < strlen(moves); i++) {
		movePlayer(c, c2, moves[i]);
		moveMonster(c, c2);
		display(c);
		if (c->endgame == 1) {
			eaten = 1;
			break;
			}
		if (c->player->treasure >= c->t_num) {
			game_finished = 1;
			break; }
		}
	free(moves);}

free(c->player->previous_char);
free(c->player);
free(c2->player->previous_char);
free(c2->player);
free(c->data);
free(c);
free(c2->data);
free(c2);
return 0;

}
