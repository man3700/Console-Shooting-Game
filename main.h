#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "value.h"

//좌표이동
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//텍스트색상
void textC(int foreground, int background) {
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//sleep
void mySleep(int a_milli_second) {
	clock_t start_clk = clock();
	a_milli_second--;
	while (1) {
		if ((clock() - start_clk) > a_milli_second) break;
	}
}

//수치 랜더링
void renderLife() {
	gotoxy(10, 51);
	textC(RED, BLACK);
	printf("♥LIFE %01d", life);
}
void renderBomb() {
	gotoxy(20, 51);
	textC(DARKGRAY, BLACK);
	printf("●SCORE %08d", bomb);
}
void renderMvS() {
	gotoxy(30, 51);
	textC(CYAN, BLACK);
	printf("↗MVSPD %01d", 6 - (moveSpeed / 40));
}
void renderAtkS() {
	gotoxy(41, 51);
	textC(YELLOW, BLACK);
	printf("★ATKSPD %01d", 6 - (atkSpeed / 40));
}
void renderAtkDmg() {
	gotoxy(52, 51);
	textC(LIGHTBLUE, BLACK);
	printf("＊ATKDMG %01d", atkDmg);
}

//가장자리
void border() {
	system("cls");
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 49; j++) {
			if (i == 0 || i == 33 || j == 0 || j == 48) {
				textC(WHITE, BLACK);
				gotoxy(2 + i * 2, 1 + j);
				printf("▒");
			}
		}
	}
	renderLife();
	renderBomb();
}