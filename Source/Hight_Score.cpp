#include "Hight_Score.h"

Hight_Score::Hight_Score()
{
	delete Score;
}

Hight_Score::Hight_Score(float width, float height)
{
	readFile();
	Sort();
	font.loadFromFile("font140.otf");
	string strScore0 = to_string(Score[0]);//Chuyen so sang ki ki tu
	hight[0].setFont(font);
	hight[0].setFillColor(Color::Red);
	hight[0].setString(strScore0);
	hight[0].setPosition(width / 2.5, height / 2);

	hight[1].setFont(font);
	string strScore1 = to_string(Score[1]);
	hight[1].setFillColor(Color::White);
	hight[1].setString(strScore1);
	hight[1].setPosition(width / 2.5, height / 1.7);

	hight[2].setFont(font);
	string strScore2 = to_string(Score[2]);
	hight[2].setFillColor(Color::White);
	hight[2].setString(strScore2);
	hight[2].setPosition(width / 2.5, height / 1.5);
}

Hight_Score::~Hight_Score()
{
}

void Hight_Score::Draw(RenderWindow& window)
{
	Font font;
	font.loadFromFile("font140.otf");
	Text text;
	text.setFont(font);
	text.setPosition(400, 20);
	text.setFillColor(Color::Red);
	text.setString("MENU");
	text.setPosition(960 / 2.5, 720 / 2.5);
	window.draw(text);
	for (int i = 0; i < 3; i++)
	{
		window.draw(hight[i]);
	}
}

void Hight_Score::readFile()
{
	int temp = 0;
	ifstream file;
	file.open("history.txt", ios::in);
	while (!file.eof())
	{
		file >> Score[temp];
		temp++;
		n++;
		if (file.eof())break;
	}
	file.close();
}

void Hight_Score::save()
{
	Sort();
	ofstream file;
	file.open("history.txt");
	for (int i = 0; i < n; i++)
	{
		file << Score[i] << endl;
	}
	file.close();
}

void Hight_Score::Sort()
{
	int n = sizeof(Score);
	int tg;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (Score[i] < Score[j]) {
				tg = Score[i];
				Score[i] = Score[j];
				Score[j] = tg;
			}
		}
	}
}
