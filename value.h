//색상
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

//파일럿
int life, bomb, moveSpeed, atkSpeed, atkDmg, moveDelay, atkDelay;
int xPos, yPos, xOld, yOld;
int bulletArr[31][46];
int enemyArr[31][46];