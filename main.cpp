#include "main.h"

void setGame();
void startMenu();
void gameRender();
void renderPilot();
void keyPilot();
void bulletMove();
void renderEnemy();
void createEnemy();
void hitBullet();
void hitEnemy();
void gameOver();

int main() {
	setGame();
	startMenu();
	gameRender();
}

void setGame() {
	system("mode con:cols=72 lines=53");
	life = 3; bomb = 3; moveSpeed = 100; atkSpeed = 100; atkDmg = 1; moveDelay = 0; atkDelay = 0;
	xPos = 15; yPos = 43; xOld = 0; yOld = 0;
	for (int i = 0; i < 31; i++)
		for (int j = 0; j < 46; j++) bulletArr[i][j] == 0;
	for (int i = 0; i < 31; i++)
		for (int j = 0; j < 46; j++) enemyArr[i][j] == 0;
	srand(time(NULL));
}

void startMenu() {
	border();
	gotoxy(32, 22);
	textC(BLACK, YELLOW);
	printf("슈팅게임");
	gotoxy(17, 45);
	textC(DARKGRAY, BLACK);
	printf("A를 눌러 총알 발사, 방향키로 이동 하기");
	gotoxy(24, 46);
	printf("빨간색은 적, 파란색은 자신");
	gotoxy(22, 47);
	printf("한/영이 한글로 되어있으면 안됨");
	int time = 0;
	while (1) {
		mySleep(1);
		time++;
		moveDelay--;
		atkDelay++;
		if (time % 2000 == 1000) {
			gotoxy(17, 27);
			textC(WHITE, BLACK);
			printf("게임을 시작하려면 space bar를 누르세요");
		}
		else if (time % 2000 == 0) {
			gotoxy(17, 27);
			textC(BLACK, BLACK);
			printf("게임을 시작하려면 space bar를 누르세요");
		}
		if (_kbhit()) {
			if (_getch() == 32) {
				textC(BLACK, BLACK);
				return;
			}
		}
	}
}

void gameRender() {
	border();
	int time = 0;
	while (1) {
		mySleep(1);
		if (time % 1000 == 0) bomb++;
		time++;
		hitBullet();
		hitEnemy();
		if (time % 1000 == 0) for (int i = 0; i <= time / 10000; i++)createEnemy();
		if (moveDelay > 0) moveDelay--;
		if (atkDelay > 0) atkDelay--;
		renderPilot();
		keyPilot();
		if (time % 200 == 0)renderEnemy();
		if (time % 20 == 0) bulletMove();
		if (life == 0) gameOver();
		renderBomb();
	}
}

void renderPilot() {
	if (xPos != xOld || yPos != yOld) {
		gotoxy((xOld * 2) + 5, yOld + 2);
		textC(BLACK, BLACK);
		printf("  ");
		gotoxy((xOld * 2) + 4, yOld + 2);
		textC(BLUE, BLACK);
		printf(" ");
		gotoxy((xOld * 2) + 7, yOld + 2);
		textC(BLACK, BLACK);
		printf(" ");
		gotoxy((xPos * 2) + 5, yPos + 2);
		textC(BLUE, BLACK);
		printf("◈");
		gotoxy((xPos * 2) + 4, yPos + 2);
		textC(WHITE, BLACK);
		printf("<");
		gotoxy((xPos * 2) + 7, yPos + 2);
		textC(WHITE, BLACK);
		printf(">");
		xOld = xPos;
		yOld = yPos;
	}
}

void keyPilot() {
	if (_kbhit()) {
		int num = 0;
		int input = _getch();
		if (input == 224 && moveDelay <= 0) {
			moveDelay = moveSpeed;
			input = _getch();
			switch (input) {
			case 72://위
				if (yPos > 0) yPos--;
				break;
			case 80://아래
				if (yPos < 46) yPos++;
				break;
			case 75://왼쪽
				if (xPos > 0) xPos--;
				break;
			case 77://오른쪽
				if (xPos < 30) xPos++;
				break;
			}
		}
		else if (input == 97 && atkDelay <= 0) {//발사(A)
			atkDelay = atkSpeed;
			if (yPos != 0) bulletArr[xPos][yPos - 1] = 1;
		}
	}
}

void bulletMove() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 46; j++) {
			if (bulletArr[i][j] == 1) {
				gotoxy((i * 2) + 5, j + 2);
				textC(WHITE, BLACK);
				printf("＊");
				bulletArr[i][j] = 2;
				if (j != 0) bulletArr[i][j - 1] = 1;
			}
			else if (bulletArr[i][j] == 2) {
				gotoxy((i * 2) + 5, j + 2);
				textC(BLACK, BLACK);
				printf("  ");
				bulletArr[i][j] = 0;
			}
		}
	}
}

void renderEnemy() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 46; j++) {
			if (enemyArr[i][j] == 1) {
				gotoxy((i * 2) + 5, j + 2);
				textC(RED, BLACK);
				printf("▣");
				gotoxy((i * 2) + 4, j + 2);
				textC(RED, BLACK);
				printf("[");
				gotoxy((i * 2) + 7, j + 2);
				textC(RED, BLACK);
				printf("]");
				enemyArr[i][j] = 5;
				if (j != 45) {
					if (i <= 0) enemyArr[i + 1][j + 1] = 4;
					else enemyArr[i - 1][j + 1] = 1;
				}else enemyArr[i][0] = 1;
			}else if (enemyArr[i][j] == 2) {
				gotoxy((i * 2) + 5, j + 2);
				textC(RED, BLACK);
				printf("▣");
				gotoxy((i * 2) + 4, j + 2);
				textC(RED, BLACK);
				printf("[");
				gotoxy((i * 2) + 7, j + 2);
				textC(RED, BLACK);
				printf("]");
				enemyArr[i][j] = 5;
				if (j != 45) {
					if (i >= 30) enemyArr[i - 1][j + 1] = 1;
					else enemyArr[i + 1][j + 1] = 4;
				}else enemyArr[i][0] = 2;
			}else if (enemyArr[i][j] == 4) {
				enemyArr[i][j] = 2;
			}
			else if (enemyArr[i][j] == 5) {
				gotoxy((i * 2) + 5, j + 2);
				textC(BLACK, BLACK);
				printf("  ");
				gotoxy((i * 2) + 4, j + 2);
				textC(BLACK, BLACK);
				printf(" ");
				gotoxy((i * 2) + 7, j + 2);
				textC(BLACK, BLACK);
				printf(" ");
				enemyArr[i][j] = 0;
			}
		}
	}
}

void createEnemy() {
	enemyArr[rand() % 31][0] = (rand() % 2) + 1;
}

void hitBullet() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 46; j++) {
			if ((enemyArr[i][j] == 1 || enemyArr[i][j] == 2 || enemyArr[i][j] == 4) && (bulletArr[i-1][j] == 1 || bulletArr[i][j] == 1 || bulletArr[i+1][j] == 1)) {
				bomb += 100;
				enemyArr[i][j] = 0;
				bulletArr[i][j] = 0;
			}
		}
	}
}

void hitEnemy() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 46; j++) {
			if ((enemyArr[i][j] == 1 || enemyArr[i][j] == 2 || enemyArr[i][j] == 4) && (((xPos == i-1 || xPos == i || xPos == i+1)) && (yPos == j))) {
				enemyArr[i][j] = 0;
				life--;
				renderLife();
			}
		}
	}
}

void gameOver() {
	textC(BLACK, BLACK);
	system("cls");
	gotoxy(32, 22);
	textC(BLACK, YELLOW);
	printf("게임오버");
	textC(BLACK, BLACK);
	exit(0);
}