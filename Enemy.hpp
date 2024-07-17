#pragma once
#include "Entity.hpp"
#include "map.hpp"

class Enemy : public Entity
{
public:
	bool left, right, up, down;

	Enemy(sf::Image* Image, int countSprite, float X, float Y, std::string Name) :Entity(Image, countSprite, X, Y, Name)
	{
		left = false;
		right = false;
		up = false;
		down = false;
	}
	~Enemy()
	{
		delete[] this->texture;
	}

	void checkPosition()
	{
		TileMap[int((this->y + 16) / 40)][int((this->x-16) / 40)] != '#' ? this->down = true : this->down = false;
		TileMap[int((this->y-16) / 40)][int((this->x + 16) / 40)] != '#' ? this->right = true : this->right = false;
		TileMap[int((this->y - 16) / 40)][int((this->x-56) / 40)] != '#' ? this->up = true : this->up = false;
		TileMap[int((this->y -56) / 40)][int((this->x - 16) / 40)] != '#' ? this->left = true : this->left = false;
	}

	void logic(Player &player)
	{
	
		if (this->x == player.getPositionX() && this->y < player.getPositionY())
		{
			this->down ? this->dy = 0.1 : this->dy = -0.1;
			this->dx = 0;
		}
		if (this->x == player.getPositionX() && this->y > player.getPositionY())
		{
			this->up ? this->dy = -0.1 : this->dy = 0.1;
			this->dx = 0;
		}
		if (this->x < player.getPositionX() && this->y == player.getPositionY())
		{
			this->right ? this->dx = 0.1 : this->dx = -0.1;
			this->dy = 0;
		}
		if (this->x > player.getPositionX() && this->y == player.getPositionY())
		{
			this->left ? this->dx = -0.1 : this->dx = 0.1;
			this->dy = 0;
		}

		if (this->x < player.getPositionX() && this->y < player.getPositionY())
		{
			if (this->right)
			{
				this->dx = 0.1;
				this->dy = 0;
			}
			else if (this->down)
			{
				this->dy = 0.1;
				this->dx = 0;
			}
		}
		if (this->x > player.getPositionX() && this->y > player.getPositionY())
		{
			if (this->left)
			{
				this->dx = -0.1;
				this->dy = 0;
			}
			else if (this->up)
			{
				this->dy = -0.1;
				this->dx = 0;
			}
		}
		if (this->x < player.getPositionX() && this->y > player.getPositionY())
		{
			if (this->right)
			{
				this->dx = 0.1;
				this->dy = 0;
			}
			else if (this->up)
			{
				this->dy = -0.1;
				this->dx = 0;
			}
		}
		if (this->x > player.getPositionX() && this->y < player.getPositionY())
		{
			if (this->left)
			{
				this->dx = -0.1;
				this->dy = 0;
			}
			else if (this->down)
			{
				this->dy = 0.1;
				this->dx = 0;
			}
		}

	}

	void interactionWithMap()
	{
		for (int i = (this->y - 16) / 40; i < (y + 16) / 40; i++)
			for (int j = (this->x - 16) / 40; j < (x + 16) / 40; j++)
			{
				if (TileMap[i][j] == '#')
				{
					if (this->dy > 0)
					{
						this->y = i * 40 - 16;
						this->dy = 0;
					}
					if (this->dy < 0)
					{
						this->y = i * 40 + 56;
						this->dy = 0;
					}
					if (this->dx >= 0)
					{
						this->x = j * 40 - 16;
						this->dx = 0;
					}
					if (this->dx < 0)
					{
						this->x = j * 40 + 56;
						this->dx = 0;
					}
				}

				
			}
	}

	void update(float time, Player& player)
	{
		if (this->name == "Blinky")
		{
			interactionWithMap();
			logic(player);
			x += dx * time;
			y += dy * time;
			checkPosition();
			this->sprite.setOrigin(16, 16);
			sprite.setPosition(x, y);
			if (this->health <= 0) { this->life = false; }
		}
	}
};