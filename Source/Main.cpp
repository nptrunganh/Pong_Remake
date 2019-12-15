#include <sstream>
#include <math.h>
#include "Bat.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "time.h"
#include <iostream>
#include "SnowFall.h"
#include <string>
#include <ctime>
#include "Menu.h"
#include "list"
#include "saveGame.h"
#include <fstream>

using namespace std;

using namespace sf;
const int windowWidth = 960;
const int windowHeight = 720;




void saveScore(int x)
{
	ofstream file;
	file.open("history.txt", ios::out | ios::app);
	file << x << endl;
	file.close();
}
void reset(Bat &Player1, Bat& Player2, Ball &ball, int batWidth, int batHeight, int batHeight2, Color color1, Color color2)
{
	int ballSize = 20;
	Player1.setPosition(50, windowHeight / 2 - batHeight / 2);
	Player2.setPosition(windowWidth - 50 - batWidth, windowHeight / 2 - batHeight / 2);
	Player1.update(50, windowHeight / 2 - batHeight / 2, batWidth, batHeight, color1);
	Player2.update(windowWidth - 50 - batWidth, windowHeight / 2 - batHeight / 2, batWidth, batHeight2, color2);
	ball.setPosition(windowWidth / 2, windowHeight / 2 - ballSize);
	
	// Set toc do ban dau cho qua bong
	srand(time(NULL));
	int arr[2] = { -1, 1 };
	int random0 = rand() % 2;
	int random1 = rand() % 2;
	ball.setVelocity(200.f * arr[random0], 200.f * arr[random1]);
	
}
void level(list<Sprite>& sprites, Texture &text1)
{
	sprites.clear();
	int temp11, temp22;

	IntRect inrecttext(0, 0, 60, 58);
	IntRect inrecttext1(60, 0, 60, 58);
	IntRect inrecttext3(120, 0, 60, 58);
	IntRect inrecttext4(0, 60, 60, 58);
	IntRect inrecttext5(120, 0, 60, 58);
	IntRect inrecttext6(0, 60, 60, 58);
	text1.loadFromFile("image/gam.png");
	int temp = 1 + rand() % 3;
	int Ox, Oy;
	switch (temp)
	{
	case 1: 
		Ox = windowWidth / 1.5;
		Oy = windowHeight / 10;


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (i % 2 == 0)
				{
					Sprite sprite1(text1, inrecttext);
					sprite1.setPosition(Vector2f(Ox + i * (60 + 5), Oy + j * (58 + 5)));
					sprites.push_back(sprite1);
				}
				else
				{
					Sprite sprite1(text1, inrecttext1);
					sprite1.setPosition(Vector2f(Ox + i * (60 + 5), Oy + j * (58 + 5)));
					sprites.push_back(sprite1);
				}
			}
		}
		break;
	case 2:
		Ox = windowWidth / 1.5;
		Oy = windowHeight / 10;
		
		temp11 = 0; temp22 = 10;
		for (int i = 0; i < 4; i++)
		{
			for (int j = temp11; j < temp22; j++)
			{
				if (i % 2 == 0)
				{
					Sprite sprite1(text1, inrecttext3);
					sprite1.setPosition(Vector2f(Ox + i * (60 + 5), Oy + j * (58 + 5)));
					sprites.push_back(sprite1);
				}
				else
				{
					Sprite sprite1(text1, inrecttext4);
					sprite1.setPosition(Vector2f(Ox + i * (60 + 5), Oy + j * (58 + 5)));
					sprites.push_back(sprite1);
				}
			}
			temp11++; temp22--;
		}
		break;
	case 3:
		Ox = windowWidth / 1.5;
		Oy = 20;
		
		temp11 = 0; temp22 = 10;
		for (int i = 4; i > 0; i--)
		{
			for (int j = temp22; j > temp11; j--)
			{
				if (i % 2 == 0)
				{
					Sprite sprite1(text1, inrecttext5);
					sprite1.setPosition(Vector2f(Ox + i * (60 + 5), Oy + j * (58 + 5)));
					sprites.push_back(sprite1);
				}
				else
				{
					Sprite sprite1(text1, inrecttext6);
					sprite1.setPosition(Vector2f(Ox + i * (60 + 5), Oy + j * (58 + 5)));
					sprites.push_back(sprite1);
				}
			}
			temp11++; temp22--;
		}
		break;
	}
	
}

void main()
{
	int ballSize = 20;
	int batWidth = 10; int batHeight = 200;
	int temp1 = batHeight; int temp2 = batHeight;
	RenderWindow window(VideoMode(windowWidth, windowHeight), "pingPong", Style::Close); // Thiet lap cua so game
	window.setFramerateLimit(60); // Gioi han so luong khung hinh chay trong 1s
	Menu menu(windowWidth, windowHeight);
	saveGame saveG;
	// Load man hinh nen
	Texture texture;
	texture.loadFromFile("image/background.png");
	IntRect SourceSprite(0, 0, windowWidth, windowHeight);
	Sprite sprite(texture, SourceSprite);



	Texture text1;
	
	
	list<Sprite> sprites;
	
	// Khoi tao thanh truot va bong
	Bat Player1(50, windowHeight / 2 - batHeight / 2, batWidth, batHeight, Color::White);
	Bat Player2(windowWidth - 50 - batWidth, windowHeight / 2 - batHeight / 2, batWidth, batHeight, Color::White);
	Ball ball(windowWidth / 2, windowHeight / 2 - ballSize, ballSize);




	// Khoi tao vector va cac bien xu li hieu ung tuyet roi
	unsigned int elapsed = 0;
	srand((unsigned int)time(0));
	std::vector<CircleShape> vt;
	int num = 200;
	int delay = 5;
	vt.reserve(num);

	// Van ban
	Text hud;
	Font font;
	font.loadFromFile("font140.otf");
	hud.setFont(font);
	hud.setCharacterSize(40);
	hud.setFillColor(sf::Color::White);


	Text huda;
	font.loadFromFile("font140.otf");
	huda.setFont(font);
	huda.setCharacterSize(40);
	huda.setFillColor(sf::Color::White);
	huda.setString("Your Score: ");
	huda.setPosition(Vector2f(windowWidth / 2 - 100, windowHeight / 6));

	int intScore1 = 0;
	Text textScore1;
	string strScore1 = to_string(intScore1);
	textScore1.setString(strScore1);
	textScore1.setFont(font);
	textScore1.setCharacterSize(40);
	textScore1.setFillColor(Color::Red);
	textScore1.setPosition(Vector2f(windowWidth / 2.f - 100, 0.f));

	int intScore2 = 0;
	Text textScore2;
	string strScore2 = to_string(intScore2);
	textScore2.setString(strScore2);
	textScore2.setFont(font);
	textScore1.setFillColor(Color::Blue);
	textScore2.setCharacterSize(40);
	textScore2.setPosition(windowWidth / 2 + 100, 0.f);


	int intScore = 0;
	Text textScore;
	string strScore = to_string(intScore);
	textScore.setString(strScore);
	textScore.setFont(font);
	textScore.setCharacterSize(40);
	textScore.setFillColor(Color::Red);
	textScore.setPosition(Vector2f(windowWidth / 2.f , 0.f));

	Text Score;
	Score.setFont(font);
	Score.setCharacterSize(40);
	Score.setFillColor(sf::Color::White);
	Score.setString("Your score: ");
	Score.setPosition(Vector2f(windowWidth / 2.f - 200, 0.f));


	Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(80);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("S N O W Y");

	Text Single;
	Single.setFont(font);
	Single.setCharacterSize(40);
	Single.setFillColor(sf::Color::White);
	Single.setString("Single player");

	Text Multi;
	Multi.setFont(font);
	Multi.setCharacterSize(40);
	Multi.setFillColor(sf::Color::White);
	Multi.setString("Multi player");

	Text Single2;
	Single2 .setFont(font);
	Single2.setCharacterSize(40);
	Single2.setFillColor(sf::Color::White);
	Single2.setString("Get Score");



	int selected = -1;
	bool leftKey = Keyboard::isKeyPressed(Keyboard::Key::Left);
	bool rightKey = Keyboard::isKeyPressed(Keyboard::Key::Right);
	bool Enter = Keyboard::isKeyPressed(Keyboard::Key::Enter);

	// Am thanh
	Music music;
	music.openFromFile("sound/music.ogg");
	music.play();
	music.setLoop(true);
	SoundBuffer soundbuffer1, soundbuffer2, soundbuffer0, soundbuffer3;
	soundbuffer1.loadFromFile("sound/hitbat.ogg");
	Sound hitbat(soundbuffer1);
	hitbat.setVolume(50);
	soundbuffer2.loadFromFile("sound/hitwall.ogg");
	Sound hitwall(soundbuffer2);
	hitwall.setVolume(50);
	soundbuffer0.loadFromFile("sound/end.ogg");
	Sound end(soundbuffer0);
	soundbuffer3.loadFromFile("sound/laugh.ogg");
	Sound enter(soundbuffer3);

	// Secret
	Music secret_music;
	secret_music.openFromFile("sound/secret.ogg");
	secret_music.setLoop(true);
	Texture secret_texture;
	secret_texture.loadFromFile("image/secret.png");
	Sprite secret(secret_texture, IntRect(0, 0, windowWidth, windowWidth));

	Clock animation; // Dieu chinh toc do animation cua background
	Clock clock; // Tinh thoi gian de game co the chay phu hop voi tung loai may tinh
	bool isPlaying = false;
	bool check = false;
	bool check1 = false;
	int tempcheck = 0;
	bool checkChange = false;
	int tempch = 0;
	while (window.isOpen())
	{
		elapsed++;

		Event event;
		while (window.pollEvent(event)) // Kiem tra xem co tin hieu nao gui den OS khong
		{
			if (!isPlaying)
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !leftKey)
				{
					hitbat.play();
					menu.MoveDown();
					selected = menu.Getpress();

				}

				if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !rightKey)
				{
					hitbat.play();
					menu.MoveUp();
					selected = menu.Getpress();
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter) && !Enter) // Nhan Enter de bat dau choi
				{
						enter.play();
						// Reset lai vi tri cua cac doi tuong khi bat dau mot game moi
						reset(Player1, Player2, ball, batWidth, batHeight, batHeight, Color::White, Color::White);
						// Bat dau lai tro choi
						temp1 = temp2 = batHeight;
						textScore.setPosition(Vector2f(windowWidth / 2.f, 0.f));
						level(sprites, text1);
						intScore1 = intScore2 = intScore = 0;
						string strScore2 = to_string(intScore2);//Chuyen so sang ki ki tu
						textScore2.setString(strScore2);
						string strScore1 = to_string(intScore1);//Chuyen so sang ki ki tu
						textScore1.setString(strScore1); 
						string strScore = to_string(intScore);//Chuyen so sang ki ki tu
						textScore.setString(strScore);
						isPlaying = true;
						clock.restart();
				}
				if (selected == 2)
				{
					if (Keyboard::isKeyPressed(Keyboard::BackSpace))
					{
						intScore = 0;
						string strScore = to_string(intScore);
						textScore.setString(strScore);
						checkChange = true;
					}
				}
			}
		}
		if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) // Tin hieu dong
		{
			window.close(); // Cua so se duoc dong
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			check = true;
			music.stop();
			secret_music.play();
			pauseMessage.setFillColor(Color::Red);
			pauseMessage.setString("The End");
		}

		// Chay hinh nen dong
		if (animation.getElapsedTime().asSeconds() > .1f)
		{
			if (SourceSprite.top == windowHeight * 7)
				SourceSprite.top = 0;
			else
				SourceSprite.top += windowHeight;
			sprite.setTextureRect(SourceSprite);
			animation.restart();
		}
		if (selected == 2)
		{
			saveG.Score.clear();
			saveG.update();
			saveG.SaveGame(windowWidth, windowHeight);
		}
		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();
			
			// Dieu khien nguoi choi 1
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (Player1.getPosition().top > 5)
					Player1.moveUp(deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (Player1.getPosition().top + Player1.getPosition().height < windowHeight - 5)
					Player1.moveDown(deltaTime);
			}

			// Dieu khien nguoi choi 2
			if (selected == 1)
			{
				Player2.setbatSpeed(400.f);
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					if (Player2.getPosition().top > 5)
						Player2.moveUp(deltaTime);
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					if (Player2.getPosition().top + Player2.getPosition().height < windowHeight- 5)
						Player2.moveDown(deltaTime);
				}
			}

			// Xu li nguoi choi may tinh (computer player)
			if (selected == 0)
			{
				Player2.setbatSpeed(550.f);
				if (ball.getPosition().left >= 150)
				{
					if ((Player2.getPosition().top + batHeight) < (ball.getPosition().top + ballSize + ballSize / 2))
					{
						if (Player2.getPosition().top + batHeight < windowHeight - 5)
							Player2.moveDown(deltaTime);
					}
					else if (Player2.getPosition().top > (ball.getPosition().top - ballSize / 2))
					{
						if (Player2.getPosition().top > 5)
							Player2.moveUp(deltaTime);
					}
				}
			}
			check1 = false;
			// Banh vuot qua mot trong hai thanh truot
			if (ball.getPosition().left < 50)
			{
				temp1 -= 100;
				if (!check)
					end.play();
				if (ballSize > 15)
				{
					ballSize -= 5;
				}
				reset(Player1, Player2, ball, batWidth, temp1, temp2, Color::White, Color::Red);
				ball.update(ballSize, Color::Green);
				intScore2++;
				string strScore2 = to_string(intScore2);//Chuyen so sang ki ki tu
				textScore2.setString(strScore2);//Thiet lap doi tuong ki tu
			}
			if (selected != 2)
			{
				if (ball.getPosition().left + ballSize > windowWidth - 50)
				{
					temp2 -= 100;
					if (ballSize > 15)
					{
						ballSize -= 5;
					}
					if (!check)
						end.play();
					reset(Player1, Player2, ball, batWidth, temp1, temp2, Color::Red, Color::White);
					ball.update(ballSize, Color::Blue);
					intScore1++;
					string strScore1 = to_string(intScore1);//Chuyen so sang ki ki tu
					textScore1.setString(strScore1);//Thiet lap doi tuong ki tu
				}
			}
			if (selected != 2)
			{
				if (temp1 == 0 || temp2 == 0)
				{
					temp1 == 0 ? hud.setString("Nguoi choi 2 thang!") : hud.setString("Nguoi choi 1 thang!");
					isPlaying = false;
				}
			}
			else if(temp1 <= 0)
			{	
				saveScore(intScore);
					textScore.setPosition(Vector2f(windowWidth / 1.6 , windowHeight / 6));
					saveG.Score.clear();
					saveG.update();
					saveG.SaveGame(windowWidth, windowHeight);
					isPlaying = false;
			}
			// Banh va cham vao tuong
			if (ball.getPosition().top <= 0 || ball.getPosition().top + ballSize >= windowHeight)
			{
				ball.reboundSides(deltaTime);
				hitwall.play();
			}
			//xu li va chap s2
			if (selected == 2)
			{
					for (auto& it : sprites)
					{
						if (ball.getPosition().intersects(it.getGlobalBounds()))
						{
							ball.reboundBat(deltaTime);
							hitbat.play();
							ball.setVelocity(ball.getXVelocity() * 1, ball.getYVelocity() * 1);
							if (tempcheck != 0)
							{
								it.move(Vector2f(windowWidth + 1000, windowHeight + 1000));
								intScore++;
								string strScore = to_string(intScore);//Chuyen so sang ki ki tu
								textScore.setString(strScore);//Thi
							}
						}
					}
			}
			// Banh va cham vao thanh truot
			if (selected != 2)
			{
				if (ball.getPosition().intersects(Player2.getPosition()))
				{
					tempcheck = 2;
					ball.reboundBat(deltaTime);
					hitbat.play();
					ball.setVelocity(ball.getXVelocity() * 1, ball.getYVelocity() * 1);
				}
			}
			else
			{
				if (ball.getPosition().left + ballSize >= windowWidth)
				{
					ball.reboundBat(deltaTime);
					hitbat.play();
					ball.setVelocity(ball.getXVelocity() * 1.1, ball.getYVelocity() * 1.1);
				}
			}
			if (ball.getPosition().intersects(Player1.getPosition()))
			{
				tempcheck = 1;
				ball.reboundBat(deltaTime);
				hitbat.play();
				ball.setVelocity(ball.getXVelocity() * 1.1, ball.getYVelocity() * 1.1);
				temp1 = temp1 * 0.9;
				Player1.upsize(batWidth, temp1);//Tang do kho(Banh va cham vao thanh giam 10% chieu dai)
			}
			if (intScore == 40 || intScore == 68)
			{
				level(sprites, text1);
			}
			// Gioi han toc do cua qua bong
			if (ball.getXVelocity() > (200.f * pow(1.1, 10)) && ball.getYVelocity() > (200.f * pow(1.1, 10)))
				ball.setVelocity(ball.getXVelocity() / 1.1, ball.getYVelocity() / 1.1);

			// Cap nhat vi tri cho cac doi tuong Ball, Bat
			ball.update(deltaTime);
			Player1.update();
			Player2.update();
		}

		// Dieu chinh vi tri cua tung doan van ban
		pauseMessage.setPosition(window.getSize().x / 2 - pauseMessage.getLocalBounds().width / 2, window.getSize().y / 6);
		Single.setPosition(window.getSize().x / 4 - Single.getLocalBounds().width / 2, window.getSize().y / 1.8);
		Multi.setPosition(window.getSize().x * .75f - Multi.getLocalBounds().width / 2, window.getSize().y / 1.8);
		hud.setPosition(windowWidth / 2 - hud.getLocalBounds().width / 2, windowHeight / 2 - 90);
		Single2.setPosition(window.getSize().x / 2 - Single.getLocalBounds().width / 2, window.getSize().y / 1.5);

		if (isPlaying)
		{
			if (check)
				window.draw(secret);
			else
				window.draw(sprite);

			
			// Xu li hieu ung tuyet roi
			
			if (elapsed >= delay && vt.size() < num)
			{
				if (check)
					createSnow(vt, windowWidth, Color::Red);
				else
					createSnow(vt, windowWidth, Color::White);
				elapsed = 0;
			}
			for (int i = 0; i < vt.size(); i++)
			{
				vt[i].move(.0f, vt[i].getRadius() * .4f);
				window.draw(vt[i]);

				if (vt[i].getPosition().y > windowHeight)
					vt.erase(vt.begin() + i);
			}

			// Hien thi thanh truot va qua bong len man hinh
			
			window.draw(Player1.getShape());
			if (selected != 2)
			{
				window.draw(Player2.getShape());
				window.draw(textScore1);
				window.draw(textScore2);
			}
			else
			{
				for (auto& it : sprites)
				{
					window.draw(it);
				}
				window.draw(textScore);
				window.draw(Score);
			}
			window.draw(ball.getShape());
		}
		else
		{
			window.clear();
			if (selected != 2)
			{
				// Hien thi cac van ban len man hinh
				window.draw(hud);
				window.draw(pauseMessage);
				menu.Draw(window);
			}
			else
			{
				window.draw(huda);
				saveG.Draw(window);
				window.draw(textScore);
			}
			if (checkChange)
			{
				window.clear();
				if(selected != 2)
				window.draw(hud);
				window.draw(pauseMessage);
				menu.Draw(window);
			}
			
			//window.draw(Single);
			//window.draw(Multi);
			//window.draw(Single2);
		}

		// Ket thuc khung hinh va hien thi noi dung len man hinh
		window.display();
	}
}