#pragma once
#include "Entity.hpp"
#include "map.hpp"

class Player : public Entity
{
public:
	int playerScore = 0;
	enum { left, right, up, down, stay } state;

	Player(sf::Image* Image, int countSprite, float X, float Y, std::string Name) :Entity(Image, countSprite, X, Y, Name)
	{
		state = stay;
		this->playerScore = 0;
	}

	void control()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			state = left;
			this->speed = 0.1;
			//CurrentFrame += 0.005 * time;
			/*if (CurrentFrame > 4)
				CurrentFrame -= 4;
			pac_man.sprite.setTexture(pac_man.texture[static_cast<int>(CurrentFrame)]);
			pac_man.sprite.setRotation(180);*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			state = right;
			this->speed = 0.1;
			/*CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4)
				CurrentFrame -= 4;
			pac_man.sprite.setTexture(pac_man.texture[static_cast<int>(CurrentFrame)]);
			pac_man.sprite.setRotation(0);*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			state = up;
			this->speed = 0.1;
			/*CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4)
				CurrentFrame -= 4;
			pac_man.sprite.setTexture(pac_man.texture[static_cast<int>(CurrentFrame)]);
			pac_man.sprite.setRotation(270);*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			state = down;
			this->speed = 0.1;
			/*CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4)
				CurrentFrame -= 4;
			pac_man.sprite.setTexture(pac_man.texture[static_cast<int>(CurrentFrame)]);
			pac_man.sprite.setRotation(90);*/
		}

	}


	void update(float time)
	{
		this->control();
		switch (state)
		{
		case(left):this->dx = -speed; this->dy = 0; break;
		case(right):this->dx = speed; this->dy = 0; break;
		case(down):this->dx = 0; this->dy = speed; break;
		case(up):this->dx = 0; this->dy = -speed; break;
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		this->sprite.setOrigin(16, 16);
		sprite.setPosition(x, y);
		interactionWithMap();
		if (this->health <= 0) { life = false; }
	}

	void interactionWithMap()
	{
		for (int i = (this->y - 16) / 40; i < (y + 16) / 40; i++)
			for (int j = (this->x - 16) / 40; j < (x + 16) / 40; j++)
			{
				if (TileMap[i][j] == '#')
				{
					if (this->dy > 0)
						this->y = i * 40 - 16;
					if (this->dy < 0)
						this->y = i * 40 + 56;
					if (this->dx > 0)
						this->x = j * 40 - 16;
					if (this->dx < 0)
						this->x = j * 40 + 56;
				}

				if (TileMap[i][j] == '.')
				{
					if (this->dy > 0)
						(((i * 40 + 18) - this->y) < 2) ? TileMap[i][j] = ' ' : TileMap[i][j] = '.';
					if (this->dy < 0)
						((this->y - (i * 40 + 24)) < 2) ? TileMap[i][j] = ' ' : TileMap[i][j] = '.';
					if (this->dx > 0)
						(((j * 40 + 18) - this->x) < 2) ? TileMap[i][j] = ' ' : TileMap[i][j] = '.';
					if (this->dx < 0)
						((this->x - (j * 40 + 24)) < 2) ? TileMap[i][j] = ' ' : TileMap[i][j] = '.';
					TileMap[i][j] == ' ' ? this->playerScore++ : this->playerScore;
				}

				if (TileMap[i][j] == '!')
				{
					if (this->dx > 0)
					{
						this->x = 40;
					}
					if (this->dx < 0)
					{
						this->x = 960;
					}
				}
			}
	}


	~Player()
	{
		delete[] this->texture;
	}
};