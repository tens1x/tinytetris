#include "Block.h"
#include "record.h"
#include <ctime>
#include <iostream>
using namespace std;
int main() {
	SetWindowText(initgraph(350, 440), L"Tetris");

	//�ײ��������
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);

	//������Ϸ���������
	srand(time(NULL));
	generateBlockData();
	drawMap();
	drawPrompt();

	Block b;
	Block nextBlock(11, 2);
	clock_t start = 0;
	clock_t end;
	
	nextBlock.draw();
	
	BeginBatchDraw();
	while (1) {

		b.clear();//��շ���
		clearrectangle(20, 20, 220, 420);//��ջ���
		drawMap();

		//�������
		if (GetAsyncKeyState(VK_UP) & 0x8000)
			b.rotate();
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (b.move()) {
				b.addMap();
				b = nextBlock;
				b.reset(0);
				nextBlock.clear();
				nextBlock.reset(1, 11, 2);//��promopt����һ������
				nextBlock.draw();

				if (b.checkCollision()) {
					MessageBox(GetHWnd(), L"Game Over.", L"tips", MB_ICONWARNING);
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			b.move(1);
		}
			
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			b.move(2);
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;

		//ÿ��500msˢ��
		end = clock();
		if ((double)(end - start ) / CLOCKS_PER_SEC > 1) {
			if (b.move()) 
			{
				b.addMap();//��ײ�����map
				b = nextBlock;
				b.reset(0);
				nextBlock.clear();
				nextBlock.reset(1, 11, 2);
				nextBlock.draw();
			}
			start = clock();
		}
		
		b.draw();
		FlushBatchDraw();
		clearLine();
		FlushBatchDraw();
		Sleep(100);
	}
	EndBatchDraw();
	
} 