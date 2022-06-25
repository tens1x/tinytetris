#include "record.h"
#include <fstream>
using namespace std;
int getHighestRecode() {
	int score = 0;
	ifstream out("score.txt", ios::out);
	out >> score;
	out.close();
	return score;
}

void storeScore(int& score) {
	int highestscore = getHighestRecode();
	if (score > highestscore) {
		ofstream in("score.txt", ios::in);
		in << score << endl;
		in.close();
	}
}