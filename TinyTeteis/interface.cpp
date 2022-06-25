#include "interface.h"
#include "record.h"

bool map[MAP_WIDTH][MAP_HEIGHT] = { 0 };
int score = 0;
int bestScore = 0;
unsigned gameTime = 0;

void drawMap() {
	roundrect(10, 10, 340, 430, 10, 10);
	roundrect(20, 20, 220, 420, 10, 10);

	setfillcolor(LIGHTCYAN);
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (map[i][j]) {
				int left = 20 + 20 * i, top = 20 + 20 * j;
				fillrectangle(left, top, left + 20, top + 20);
			}
		}
	}
}

void drawPrompt() {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	wcscpy_s(f.lfFaceName, L"微软雅黑");
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);

	outtextxy(225, 20, L"下一个方块");
	roundrect(240, 60, 320, 140, 10, 10);

	f.lfHeight = 25;
	settextstyle(&f);
	wchar_t str[20];
	wsprintf(str, L"Score : %u", score);
	outtextxy(230, 160, str);
	bestScore = getHighestRecode();
	wsprintf(str, L"Best : %u ", bestScore);//秒后面变分钟
	outtextxy(230, 185, str);
}

bool checkLine(const unsigned char& line) {
	for (int i = 0; i < MAP_WIDTH; i++) {
		if (map[i][line] == 0)
			return 0;
	}
	return 1;
}

void clearLine() {
	signed char line = -1;
	for (int j = 0; j < MAP_HEIGHT; j++)
		if (checkLine(j))
			line = j;
	if (line != -1) {
		for (int j = line; j > 0; j--)
			for (int i = 0; i < MAP_WIDTH; i++)
				map[i][j] = map[i][j - 1];
		score += 10;
	}	
	drawPrompt();
	storeScore(score);
}	