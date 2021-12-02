#include "player.h"
#include "cavern.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Cavern* constructCavern(int w, int h, struct Player* p) {
	
	struct Cavern* cave = (struct Cavern*)malloc(sizeof(struct Cavern));
	cave->data = (char*)malloc(sizeof(char) * w * h);
	cave->width = w;
	cave->height = h;
	cave->player = p;
	cave->right = 0;
	cave->down = 0;
	cave->t_num = 0;
	
	return cave;
}

struct Cavern* readMap(char filename[15], struct Player* p) {
	char line[40];
	FILE* f = fopen(filename, "r");
	
	
	char widthNum[2];
	fscanf(f, "%s", widthNum);
	int wth = atoi(widthNum);
	
	char heightNum[2];
	fscanf(f, "%s", heightNum);
	int hgt = atoi(heightNum);
	
	struct Cavern* c = constructCavern(wth, hgt, p);
	
	fgets(line, 40, f);
	for (int y=0; y < hgt; y++) {
		fgets(line, 40, f);
		for(int x=0; x < wth; x++) {
			if (line[x] == '@') {
			c->player = constructPlayer(x, y);
			setPoint(c, line[x], x, y);}
			else if (line[x] == '$') {
			c->t_num++;
			setPoint(c, line[x], x, y); }
			else {
			setPoint(c, line[x], x, y);		
		}
	}
}
	fclose(f);
	return c;}
	
void display(struct Cavern* c) {
	for(int y=0; y < c->height; y++) {
		for(int x=0; x < c->width; x++) { 
			printf("%c", get(c, x, y));
			}
		printf("%c\n", (char)0);}
	}
	
void setPoint(struct Cavern* c, char v, int x, int y) {
	c->data[x + y * c->width] = v;
	}
	
char get(struct Cavern* c, int x, int y) {
	return c->data[x + y * c->width];
	}

	
char* getMoves() {

	char* data = (char*)malloc(sizeof(char) * 6);
	printf("%s", "Please enter your moves (You may pick up to five at once): ");
	scanf("%5s", data);
	
	return data;

}  

void movePlayer(struct Cavern* c, struct Cavern* c2, char v) {
	char *previous_char = c->player->previous_char;
	int x = c->player->x;
	int y = c->player->y;
	//up
	if (v == 'u') {
		if (get(c, x, y-1) == '#' || get(c,x,y-1) == 'X') {
			printf("%s", "Invalid move, there is a wall or a closed door in the way. Your turn has been skipped\n");
			return;
			}
		else {
			if (get(c2, x, y-1) == '$') {
				c->player->treasure++;
				setPoint(c, '@', x, y-1);
				setPoint(c2, '.', x, y-1);
				setPoint(c, previous_char[0], x, y);
				c->player = pUp(c->player);
				}
			else if (get(c, x, y-1) == '-') {
				previous_char[0] =  get(c,x,y-1);
				setPoint(c, '@', x, y-1);
				setPoint(c, '.', x, y);
				c->player = pUp(c->player);
				}
			else {
				setPoint(c, '@', x, y-1);
				if (previous_char[0] == '-') { 
				setPoint(c, '-', x, y);
				} else { setPoint(c, '.', x, y); }
				previous_char[0] = '.';
				 c->player = pUp(c->player);}
				}
			}
	//down	
	else if (v == 'd') {
		if (get(c, x, y+1) == '#' || get(c,x,y+1) == 'X') {
			printf("%s", "Invalid move, there is a wall or a closed door in the way. Your turn has been skipped\n");
			return;
			}
		else {
			if (get(c2, x, y+1) == '$') {
				c->player->treasure++;
				setPoint(c, '@', x, y+1);
				setPoint(c2, '.', x, y+1);
				setPoint(c, previous_char[0], x, y);
				c->player = pDown(c->player);
				}
			else if (get(c, x, y+1) == '-') {
				previous_char[0] =  get(c,x,y+1);
				setPoint(c, '@', x, y+1);
				setPoint(c, '.', x, y);
				c->player = pDown(c->player);
				}
			else {
				setPoint(c, '@', x, y+1);
				if (previous_char[0] == '-') { 
				setPoint(c, '-', x, y);
				} else { setPoint(c, '.', x, y); }
				previous_char[0] = '.';
				c->player = pDown(c->player); }
				}
		
			}
			
		 //left		
	else if (v == 'l') {
		if (get(c, x-1, y) == '#' || get(c,x-1,y) == 'X') {
			printf("%s", "Invalid move, there is a wall or a closed door in the way. Your turn has been skipped\n"); 
			return;}
		else {
			if (get(c2, x-1, y) == '$') {
				c->player->treasure++;
				setPoint(c, '@', x-1, y);
				setPoint(c2, '.', x-1, y);
				setPoint(c, previous_char[0], x, y);
				c->player = pLeft(c->player);
				}
			else if (get(c, x-1, y) == '-') {
				previous_char[0] =  get(c,x-1,y);
				setPoint(c, '@', x-1, y);
				setPoint(c, '.', x, y);
				c->player = pLeft(c->player);
				}
			else {
				setPoint(c, '@', x-1, y);
				if (previous_char[0] == '-') { 
				setPoint(c, '-', x, y);
				} else { setPoint(c, '.', x, y); }
				previous_char[0] = '.';
				c->player = pLeft(c->player); }
				}
			} 
		//right		
	else if (v == 'r' && v != 't') {
		if (get(c, x+1, y) == '#' || get(c,x+1,y) == 'X') {
			printf("%s", "Invalid move, there is a wall or a closed door in the way. Your turn has been skipped\n");
			return;
			}
		else {
			if (get(c2, x+1, y) == '$') {
				c->player->treasure++;
				setPoint(c, '@', x+1, y);
				setPoint(c2, '.', x+1, y);
				setPoint(c, '.', x, y);
				c->player = pRight(c->player);
				}
			else if (get(c, x+1, y) == '-') {
				previous_char[0] =  get(c,x+1,y);
				setPoint(c, '@', x+1, y);
				setPoint(c, '.', x, y);
				c->player = pRight(c->player);
				}
			else {
				setPoint(c, '@', x+1, y);
				if (previous_char[0] == '-') { 
				setPoint(c, '-', x, y);
				} else { setPoint(c, '.', x, y); }
				previous_char[0] = '.';
				c->player = pRight(c->player); }
				}
			}
	
			
	//open/close door		
	else if (v == 't') {
		if (get(c, x+1, y) == 'X') {
			setPoint(c, '-', x+1, y);
			setPoint(c2, '-', x+1, y);
			}
		else if(get(c, x-1, y) == 'X') {
			setPoint(c, '-', x-1, y);
			setPoint(c2, '-', x-1, y);
			}
		else if(get(c, x, y+1) == 'X') {
			setPoint(c, '-', x, y+1);
			setPoint(c2, '-', x, y+1);
			}
		else if(get(c, x, y-1) == 'X') {
			setPoint(c, '-', x, y-1);	
			setPoint(c2, '-', x, y-1);
		}
		else if (get(c, x+1, y) == '-') {
			setPoint(c, 'X', x+1, y);
			setPoint(c2, 'X', x+1, y);
			}
		else if(get(c, x-1, y) == '-') {
			setPoint(c, 'X', x-1, y);
			setPoint(c2, 'X', x-1, y);
			}
		else if(get(c, x, y+1) == '-') {
			setPoint(c, 'X', x, y+1);
			setPoint(c2, 'X', x, y+1);
			}
		else if(get(c, x, y-1) == '-') {
			setPoint(c, 'X', x, y-1);
				setPoint(c2, 'X', x, y-1);
		}
	return;}
	
	else if (v == '.') {
		printf("%s", "Your turn has been successfully skipped\n"); 
		return;}
	
	else { printf("%s", "ERROR: Invalid character, your turn has been skipped\n"); 
		return;}
}

int monsterDirection(struct Cavern* c, int monster_x, int monster_y) {
    int dx = abs(c->player->x - monster_x);
    int dy = abs(c->player->y - monster_y);
    if(dx<dy) {
        if(c->player->y < monster_y) {
            return 1; //up
        } else {
            return 2; //down
        }
    } else {
        if(c->player->x < monster_x) {
            return 3; //left
        } else {
            return 4; //right
        }
    }
    
}


void moveMonster(struct Cavern* c, struct Cavern* c2) {
	
	for (int y=0; y < c->height; y++) {
		for (int x=0; x < c->width; x++) {
			if (get(c, x, y) == '*') {
				if (get(c, x, y-1) != '#' && get(c,x,y-1) != 'X' && monsterDirection(c, x, y) == 1) {
					if (get(c, x, y-1) == '@') {
						c->endgame = 1;
						printf("%s", "The monster ate you! Game Over :( \n");
						setPoint(c, '*', x, y-1);
						if (get(c2, x, y) == '-' || get(c2, x, y) == '$') {
					setPoint(c, get(c2, x, y), x, y); }
					else { setPoint(c, '.', x, y); }
						return;
						}
					setPoint(c, '*', x, y-1);
					if (get(c2, x, y) == '-' || get(c2, x, y) == '$') {
					setPoint(c, get(c2, x, y), x, y); }
					else { setPoint(c, '.', x, y); }
					}
			 	 if (get(c, x, y+1) != '#' && get(c,x,y+1) != 'X' && monsterDirection(c, x, y) == 2) {
			 	 	c->down = 1;
			 	 	if (get(c, x, y+1) == '@') {
			 	 		c->endgame = 1;
						printf("%s", "The monster ate you! Game Over :( \n");
						setPoint(c, '*', x, y-1);
						if (get(c2, x, y) == '-' || get(c2, x, y) == '$') {
					setPoint(c, get(c2, x, y), x, y);}
					else { setPoint(c, '.', x, y); }
						return;
						}
					setPoint(c, '*', x, y+1);
					if (get(c2, x, y) == '-' || get(c2, x, y) == '$') {
					setPoint(c, get(c2, x, y), x, y);}
					else { setPoint(c, '.', x, y); }
					if (c->down == 1) {
						y++;
						c->down = 0; }
			 	}
			 	 if (get(c, x-1, y) != '#' && get(c,x-1,y) != 'X' && monsterDirection(c, x, y) == 3) {
			 	 	if (get(c, x, y-1) == '@') {
			 	 		c->endgame = 1;
						printf("%s", "The monster ate you! Game Over :( \n");
						setPoint(c, '*', x, y-1);
						if (get(c2, x, y) == '-' || get(c2, x, y) == '$') {
					setPoint(c, get(c2, x, y), x, y);} 
					else { setPoint(c, '.', x, y); }
						return;
						}
					setPoint(c, '*', x-1, y);
					if (get(c2, x, y) == '-' || get(c2, x, y) == '$') {
					setPoint(c, get(c2, x, y), x, y);} 
					else { setPoint(c, '.', x, y); }
			 	}
			 	 if (get(c, x+1, y) != '#' && get(c,x+1,y) != 'X' && monsterDirection(c, x, y) == 4) {
			 	 	if (get(c, x, y-1) == '@') {
			 	 		c->endgame = 1;
						printf("%s", "The monster ate you! Game Over :( \n");
						setPoint(c, '*', x, y-1);
						if (get(c2, x+1, y) == '-' || get(c2, x+1, y) == '$' ) {
					setPoint(c, get(c2, x, y), x, y);  }
					else { setPoint(c, '.', x, y); }
						return;
						}
			 	 	c->right = 1;
					setPoint(c, '*', x+1, y);
					if (get(c2, x, y) == '-' || get(c2, x, y) == '$' ) {
					setPoint(c, get(c2, x, y), x, y);  }
					else { setPoint(c, '.', x, y); }
					if (c->right == 1) {
						x++;
						c->right = 0;
						}
					}  
				}
			}
		}
	}
	

int getTreasure(struct Cavern* c) {
	int t_count = 0;
	for (int y=0; y < c->height; y++) {
		for (int x=0; x < c->width; x++) {
			if (get(c, x, y) == '$') {
			t_count++;
			}
		}	
	}
return t_count;}
	

