#pragma once
#include "SFML-2.6.1/include/SFML/Graphics.hpp"
#include "SFML-2.6.1/include/SFML/Window.hpp"
#include "SFML-2.6.1/include/SFML/System.hpp"

class Entity
{
public:
	float dx, dy, x, y, speed;
	int health;
	bool life;
	std::string name;
	sf::Texture* texture;
	sf::Sprite sprite;

	Entity(sf::Image* Image, int countSprite, float X, float Y, std::string Name)
	{
		this->name = Name;
		this->health = 1;
		this->life = true;
		this->dx = 0;
		this->dy = 0;
		this->speed = 0;
		this->x = X;
		this->y = Y;
		this->texture = new sf::Texture[countSprite];
		for (int i = 0; i < countSprite; i++)
		{
			this->texture[i].loadFromImage(Image[i]);
		}
		this->sprite.setTexture(this->texture[0]);
	}
	~Entity() {};

	float getPositionX()
	{
		return this->x;
	}
	float getPositionY()
	{
		return this->y;
	}
};