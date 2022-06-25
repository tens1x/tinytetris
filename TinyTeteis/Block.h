#pragma once
#include <easyx.h>
#include "interface.h"

#define BLOCK_WIDTH 20

extern bool blockData[7][4][4];
void generateBlockData();

class Block
{
public:
	Block(const int& x = (MAP_WIDTH - 4) / 2 , const int& y = 0);
	bool move(const unsigned char& direction = 0);
	void draw();
	void clear();
	void addMap();
	void rotate();
	bool checkCollision();
	void reset(const bool& isRandType = 1, const int& x = (MAP_WIDTH - 4) / 2, const int& y = 0);

private:
	int x;
	int y;
	unsigned char type;
	bool direction;
	bool block[4][4];
	COLORREF color;

};