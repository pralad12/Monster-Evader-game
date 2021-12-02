#ifndef CAVERN_H_
#define CAVERN_H_

struct Cavern {
	
	struct Player* player;
	char* data;
	int width;
	int height;
	int right;
	int down;
	int endgame;
	int t_num;
	
	};
	
struct Cavern* constructCavern(int w, int h, struct Player* p);

struct Cavern* readMap(char filename[15], struct Player* p);

void setPoint(struct Cavern* c, char v, int x, int y);
	
char get(struct Cavern* c, int x, int y);

void display(struct Cavern* c);

void movePlayer(struct Cavern* c, struct Cavern* c2, char v);

char* getMoves();

int monsterDirection(struct Cavern* c, int monster_x, int monster_y);

void moveMonster(struct Cavern* c, struct Cavern* c2);

int getTreasure(struct Cavern* c);




	
//int passibleAt(struct Cavern* c, int x, int y);

//struct Player* getPlayer(struct Cavern* c);

#endif
