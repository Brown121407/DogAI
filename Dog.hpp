#pragma once

#include "globals.hpp"
#include "Time.hpp"
#include "Texture.hpp"

#ifdef DEBUG
#include <iostream>
#endif


class Dog
{
private:
	enum State
	{
		State_Barking,
		State_Walking,
		State_Running,
		State_Sat,
		State_Sitting,
		State_Idle,
	};

	const float _minStateTime = 1;
	const float _maxStateTime = 5;
	
	const uint32_t _width = 90;
	const uint32_t _height = 58;

	const float _speed = 50.0f;

public:
	Dog(std::string name = "Dog");
	Dog(std::string name = "Dog", const Texture* texture = nullptr);
	~Dog();

	void act();

	void render() const;

	Pointf getPosf() const;
	Pointi getPosi() const;

	void setTexture(const Texture* texture);
	void setPosition(const Pointi position);

	uint32_t getWidth() const;
	uint32_t getHeight() const;

private:
	void idle();
	void walk();
	void changeDirection();

	void changeState(State newState);
	
	Pointf _dogPos;

	State _state;
	float _stateTime;
	float _desiredStateTime;

	bool _lookingLeft;
	bool _willFlip;
	float _timeBeforeFlip;

	const Texture* _texture;

	std::string _name;
};

