#include "block.h"
#include <iostream>
using namespace std;
bool blockData[7][4][4] = { 0 };

void generateBlockData() {
	blockData[0][1][0] = blockData[0][1][1] = blockData[0][1][2] = blockData[0][1][3] = 1;//长条
	blockData[1][0][0] = blockData[1][1][0] = blockData[1][1][1] = blockData[1][1][2] = 1;//正七
	blockData[2][2][0] = blockData[2][1][0] = blockData[2][1][1] = blockData[2][1][2] = 1;//反七
	blockData[3][1][0] = blockData[3][1][1] = blockData[3][0][1] = blockData[3][2][1] = 1;//凸字
	blockData[4][0][0] = blockData[4][1][0] = blockData[4][1][1] = blockData[4][0][1] = 1;//田字
	blockData[5][0][0] = blockData[5][1][0] = blockData[5][1][1] = blockData[5][2][1] = 1;//正z
	blockData[6][2][0] = blockData[6][1][0] = blockData[6][1][1] = blockData[6][0][1] = 1;//反z
}

Block::Block(const int& x, const int& y) : x(x), y(y) {
	type = rand() % 7;
	direction = 1;
	switch (type) {
	case 0:
		color = BLUE;
		break;

	case 1:
		color = GREEN;
		break;

	case 2:
		color = PINK;
		break;

	case 3:
		color = YELLOW;
		break;
	
	case 4:
		color = RED;
		break;

	case 5:
		color = CYAN;
		break;

	case 6:
		color = MAGENTA;
		break;

	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			block[i][j] = blockData[type][i][j];
	}
}

bool Block::move(const unsigned char& direction) {
	switch (direction) {
	case 0 ://s
		y++;
		if (checkCollision()) {
			y--;
			return 1;
		}
		break;
	case 1://a
		x--;
		if (checkCollision()) {
			x++;
			return 1;
		}
		break;
	case 2://d
		x++;
		if (checkCollision()) {
			x--;
			return 1;
		}
		break;
	}
	return 0;
}

void Block::draw() {
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (block[i][j])
				if (j + y >= 0) {
					setfillcolor(color);
					int left = 20 + BLOCK_WIDTH * (x + i), top = 20 + BLOCK_WIDTH * (j + y);//给一个坐标上的方块上色
					fillrectangle(left, top, left + BLOCK_WIDTH, top + BLOCK_WIDTH);
				}
		}

}

void Block::clear() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (block[i][j]) {
				int left = 20 + BLOCK_WIDTH * (x + i), top = 20 + BLOCK_WIDTH * (j + y);
				clearrectangle(left, top, left + BLOCK_WIDTH, top + BLOCK_WIDTH);
			}
		}

}

void Block::addMap() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) 
			if (block[i][j]) {
				map[x + i][y + j] = block[i][j];
			}
}

void Block::rotate() {
	if (type != 4) {
		bool temp;
		if (direction == 0) { //顺时针旋转
			temp = block[0][0];
			block[0][0] = block[2][0];
			block[2][0] = block[2][2];
			block[2][2] = block[0][2];
			block[0][2] = temp;

			temp = block[1][0];
			block[1][0] = block[2][1];
			block[2][1] = block[1][2];
			block[1][2] = block[0][1];
			block[0][1] = temp;
		}
		else {
			temp = block[0][0];
			block[0][0] = block[0][2];
			block[0][2] = block[2][2];
			block[2][2] = block[2][0];
			block[2][0] = temp;

			temp = block[1][0];
			block[1][0] = block[0][1];
			block[0][1] = block[1][2];
			block[1][2] = block[2][1];
			block[2][1] = temp;
		}
		switch (type) {
		case 0:
			if (block[1][3]) {
				block[1][3] = 0;
				block[3][1] = 1;
			}
			else
			{
				block[1][3] = 1;
				block[3][1] = 0;
			}
			
		case 5:
		case 6:
			if (!checkCollision())
				direction = !direction;

		}

		if (checkCollision()) {
			if (direction == 1) { //逆时针旋转
				temp = block[0][0];
				block[0][0] = block[0][2];
				block[0][2] = block[2][2];
				block[2][2] = block[2][0];
				block[2][0] = temp;

				temp = block[1][0];
				block[1][0] = block[0][1];
				block[0][1] = block[1][2];
				block[1][2] = block[2][1];
				block[2][1] = temp;
			}
			else {
				temp = block[0][0];
				block[0][0] = block[2][0];
				block[2][0] = block[2][2];
				block[2][2] = block[0][2];
				block[0][2] = temp;

				temp = block[1][0];
				block[1][0] = block[2][1];
				block[2][1] = block[1][2];
				block[1][2] = block[0][1];
				block[0][1] = temp;
			}
			if (type == 0) {
				if (block[1][3]) {
					block[1][3] = 0;
					block[3][1] = 1;
				}
				else
				{
					block[1][3] = 1;
					block[3][1] = 0;
				}
			}
		}
	}


}

bool Block::checkCollision() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			if ((map[x + i][y + j] || 20 + BLOCK_WIDTH * (x + i)  < 20 || 20 + BLOCK_WIDTH * (x + i) + BLOCK_WIDTH > 220 || 20 + BLOCK_WIDTH + BLOCK_WIDTH * (j + y)  > 420) && block[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

void Block::reset(const bool& isRandType, const int& x, const int& y) {
	this->x = x;
	this->y = y;
	if (isRandType) {
		type = rand() % 7;
	}
	direction = 1;

	switch (type) {
	case 0:
		color = BLUE;
		break;

	case 1:
		color = GREEN;
		break;

	case 2:
		color = BLACK;
		break;

	case 3:
		color = YELLOW;
		break;

	case 4:
		color = RED;
		break;

	case 5:
		color = CYAN;
		break;

	case 6:
		color = MAGENTA;
		break;

	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			block[i][j] = blockData[type][i][j];
	}
}