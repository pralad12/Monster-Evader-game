#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

	
struct Player* constructPlayer(int x, int y) { 
	struct Player* p = (struct Player*)malloc(sizeof(struct Player));
	p->x = x;
	p->y = y;
	p->treasure = 0;
	p->previous_char = (char*)malloc(sizeof(char));
	p->previous_char[0] = '.';
	return p; 
	}
	
struct Player* pUp(struct Player* p) {
	p->y = p->y-1;
	return p;
	}
	
struct Player* pDown(struct Player* p) {
	p->y = p->y+1;
	return p;
	}
	
struct Player* pLeft(struct Player* p) {
	p->x = p->x-1;
	return p;;
	}
	
struct Player* pRight(struct Player* p) {
	p->x = p->x+1;
	return p;
	}
	


