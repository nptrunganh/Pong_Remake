#include "saveGame.h"

saveGame::saveGame()
{
}

void saveGame::SaveGame(float width, float height)
{
	font.loadFromFile("font140.otf");
	int n1 = Score.front();
	string strScore0 = to_string(n1);
	save[0].setString(strScore0);
	save[0].setFont(font);
	save[0].setFillColor(Color::Red);
	save[0].setPosition(width / 2, height / 3);

	Score.pop_front();
	int n2 = Score.front();
	string strScore1 = to_string(n2);
	save[1].setFont(font);
	save[1].setFillColor(Color::White);
	save[1].setString(strScore1);
	save[1].setPosition(width / 2, height / 2.5);

	Score.pop_front();
	int n3 = Score.front();
	string strScore2 = to_string(n3);
	save[2].setFont(font);
	save[2].setFillColor(Color::White);
	save[2].setString(strScore2);
	save[2].setPosition(width / 2, height / 2 );
}

saveGame::~saveGame()
{

}

void saveGame::ReadFile()
{
	int temp;
	ifstream file;
	file.open("history.txt");
	while (!file.eof())
	{
		file >> temp;
		Score.push_back(temp);
		if (file.eof()) break;
	}
}

void saveGame::update()
{
	Score.clear();
	ReadFile();
	Score.sort();
	Score.reverse();
}

void saveGame::Draw(RenderWindow& window)
{
	Font font;
	font.loadFromFile("font140.otf");
	Text text;
	text.setFont(font);
	text.setPosition(960/3, 720/4);
	text.setFillColor(Color::White);
	text.setString(" T O P  3  H I G H T  S C O R E\n\n\n\n\n\n\n\nPress  E N T E R  to  P L A Y\n\n\nOr  B A C K S P A C E  to  R E T U R N");
	window.draw(text);

	for (int i = 0; i < 3; i++)
	{
		window.draw(save[i]);
	}
}
