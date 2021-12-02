#ifndef PLAYER_H_
#define PLAYER_H_



struct Player {
	
	char *previous_char;
	int treasure;
	int x;
	int y; 
	
	};
	

struct Player* constructPlayer(int x, int y);

struct Player* pUp(struct Player* p); 

struct Player* pDown(struct Player* p);

struct Player* pLeft(struct Player* p); 

struct Player* pRight(struct Player* p); 



#endif
