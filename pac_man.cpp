
#include "Entity.hpp"
#include "map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <string>
#include <sstream>


const float WIDTH = 1300;
const float HEIGHT = 1000;
const float PAC_MAN_X = PAC_MAN_ON_MAP.x * 40 + 20;
const float PAC_MAN_Y = PAC_MAN_ON_MAP.y * 40 + 20;
const float BLINKY_X = BLINKY_ON_MAP.x * 40 + 20;
const float BLINKY_Y = BLINKY_ON_MAP.y * 40 + 20;


std::string Pac_File[]={ "pac_man_0.png","pac_man_1.png","pac_man_2.png","pac_man_3.png" };
std::string Blinky_File[] = { "spr_ghost_red_0.png","spr_ghost_red_1.png" };

int main()
{
	sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "Pacman");
	float CurrentFrame = 0;
	sf::Image pac_image[4];
	for (int i = 0; i < 4; i++)
		pac_image[i].loadFromFile("src/" + Pac_File[i]);
	Player pac_man(pac_image, 4, PAC_MAN_X, PAC_MAN_Y, "Pacman");

	sf::Image blinky_image[2];
	for (int i = 0; i < 2; i++)
		blinky_image[i].loadFromFile("src/" + Blinky_File[i]);
	Enemy blinky(blinky_image, 2, BLINKY_X, BLINKY_Y, "Blinky");

	sf::Image map_img_1;
	sf::Image map_img_2;
	map_img_1.loadFromFile("src/map_1.png");
	map_img_2.loadFromFile("src/map_2.png");
	sf::Texture map_txtr[2];
	map_txtr[0].loadFromImage(map_img_1);
	map_txtr[1].loadFromImage(map_img_2);
	sf::Sprite map_sprite;
	map_sprite.setTexture(map_txtr[0]);

	sf::Image pill_img;
	pill_img.loadFromFile("src/spr_pill_0.png");
	sf::Texture pill_txtr;
	pill_txtr.loadFromImage(pill_img);
	sf::Sprite pill_sprite;
	pill_sprite.setTexture(pill_txtr);
	pill_sprite.setOrigin(4, 4);

	sf::Font font;
	font.loadFromFile("src/comic.ttf");
	sf::Text text("",font,20);
	text.setColor(sf::Color::Yellow);
	text.setStyle(sf::Text::Bold);

	sf::Clock clock;
	while (win.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;
		sf::Event event;
		while (win.pollEvent(event))
			if (event.type == sf::Event::Closed)
				win.close();
		if (pac_man.life)
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4)
				CurrentFrame -= 4;
			pac_man.sprite.setTexture(pac_man.texture[static_cast<int>(CurrentFrame)]);
			/*pac_man.dx < 0 ? pac_man.sprite.setRotation(180) : pac_man.sprite.setRotation(0);
			pac_man.dy < 0 ? pac_man.sprite.setRotation(270) : pac_man.sprite.setRotation(0);
			pac_man.dy > 0 ? pac_man.sprite.setRotation(90) : pac_man.sprite.setRotation(0);*/
		}
		if (pac_man.playerScore == 273 || !pac_man.life)
		{
			win.close();
		}
		pac_man.update(time);
		blinky.update(time, pac_man);
		win.clear();

		for(int i =0; i<MAP_HEIGHT;i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (TileMap[i][j] == '!')
					continue;
				if (TileMap[i][j] == '#')
					map_sprite.setTexture(map_txtr[1]);
				if (TileMap[i][j] == ' ' || TileMap[i][j]=='.')
					map_sprite.setTexture(map_txtr[0]);
				map_sprite.setPosition((j * 40), (i * 40));
				win.draw(map_sprite);
				if (TileMap[i][j] == '.')
				{
					pill_sprite.setPosition(j * 40 + 20, i * 40 + 20);
					win.draw(pill_sprite);
				}
			}

		std::ostringstream playerScoreStr;
		playerScoreStr << pac_man.playerScore;
		text.setString("Your Score " + playerScoreStr.str());
		text.setPosition(1010,50);
		win.draw(text);

		std::ostringstream playerHealthStr;
		playerHealthStr << pac_man.health;
		text.setString("Health " + playerHealthStr.str());
		text.setPosition(1010, 100);
		win.draw(text);

		win.draw(pac_man.sprite);
		win.draw(blinky.sprite);
		win.display();
	}
	return 0;
}