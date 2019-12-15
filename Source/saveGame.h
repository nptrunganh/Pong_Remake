#ifndef __saveGame_h__
#define __saveGame_h__
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <list>
using namespace std;
using namespace sf;
class saveGame
{
private:
	int selectIndex;
	Font font;
	Text save[3];
	
public:
	list<int> Score;
	saveGame();
	void SaveGame(float width, float height);
	~saveGame();
	void ReadFile();
	void update();
	
	void Draw(RenderWindow& window);
};
#endif
