#pragma once
#include <easyx.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 20	

extern bool map[MAP_WIDTH][MAP_HEIGHT];
extern unsigned score;
extern unsigned gameTime;

void drawMap();
void drawPrompt();
bool checkLine(const unsigned char& line);
void clearLine();