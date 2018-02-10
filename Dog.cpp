#include "Dog.hpp"


Dog::Dog(const std::string name)
{
	_dogPos = {
		static_cast<float>(WINDOW_WIDTH / 2 - _width / 2),
		static_cast<float>(HEIGHT / 2 - _height / 2)
		};
	_willFlip = false;
	_lookingLeft = true;

	_name = name;

	changeState(State_Idle);
}

Dog::Dog(const std::string name, const Texture * texture)
{
	_dogPos = {
		static_cast<float>(WINDOW_WIDTH / 2 - _width / 2),
		static_cast<float>(HEIGHT / 2 - _height / 2)
	};
	_willFlip = false;
	_lookingLeft = true;

	changeState(State_Idle);

	_name = name;

	_texture = texture;
}


Dog::~Dog()
{

}

void Dog::act()
{
	switch (this->_state) 
	{
		case State_Walking:
			walk();
			break;
		case State_Idle:
			idle();
			break;
	}
}

void Dog::render() const
{
	if (_texture != nullptr)
	{
		int noSprites = 4;
		switch (_state)
		{
		case State_Barking:
			noSprites = 4;
			break;
		case State_Walking:
			noSprites = 6;
			break;
		case State_Running:
			noSprites = 5;
			break;
		case State_Sat:
			noSprites = 4;
			break;
		case State_Sitting:
			noSprites = 3;
			break;
		case State_Idle:
			noSprites = 4;
			break;
		}

		const int sprite = SDL_GetTicks() / 100 % noSprites;

		SDL_Rect clipRect = {sprite * 90, _state * 58, 90, 58};

		const auto flip = _lookingLeft ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

		_texture->render(
			static_cast<int>(_dogPos.x),
			static_cast<int>(_dogPos.y),
			&clipRect,
			0,
			nullptr,
			flip
		);
	}
}

Pointf Dog::getPosf() const
{
	return _dogPos;
}

Pointi Dog::getPosi() const
{
	return Pointi{static_cast<int>(_dogPos.x), static_cast<int>(_dogPos.y)};
}

void Dog::setTexture(const Texture * texture)
{
	_texture = texture;
}

void Dog::setPosition(const Pointi position)
{
	_dogPos = {
		static_cast<float>(position.x),
		static_cast<float>(position.y)
	};
}

uint32_t Dog::getWidth() const
{
	return _width;
}

uint32_t Dog::getHeight() const
{
	return _height;
}

void Dog::changeState(const State newState)
{
	const std::uniform_real_distribution<> distribution(_minStateTime, _maxStateTime);
	_desiredStateTime = distribution(gRng);

	_state = newState;
	_stateTime = 0;

	_willFlip = std::uniform_int_distribution<std::mt19937::result_type>(1, 4)(gRng) == 1;
	if (_willFlip)
	{
		_timeBeforeFlip = std::uniform_real_distribution<>(0, _desiredStateTime)(gRng);
	}
	
#ifdef DEBUG
	std::cout << _name <<" now " << (_state == State_Idle ? "idle" : "walking") << " <===> ";
	std::cout << "Desired state time: " << _desiredStateTime << " seconds." << " <===> ";
	std::cout << (_willFlip ? std::string("Will change direction in ") + std::to_string(_timeBeforeFlip) : "Will not change direction") << ". <===> ";
	std::cout << "Dog position: " << _dogPos.x << " " << _dogPos.y << "\n";
#endif
}

void Dog::idle()
{
	_stateTime += Time::getDeltaTimeSeconds();

	if (_willFlip && _stateTime >= _timeBeforeFlip)
	{
		changeDirection();
	}
	if (_stateTime >= _desiredStateTime)
	{
		changeState(State_Walking);
	}
}

void Dog::walk()
{
	_stateTime += Time::getDeltaTimeSeconds();

	if (_willFlip && _stateTime >= _timeBeforeFlip)
	{
		changeDirection();
	}
	if (_stateTime >= _desiredStateTime)
	{
		changeState(State_Idle);
	}
	else
	{
		_dogPos.x += _speed * Time::getDeltaTimeSeconds() * (_lookingLeft ? -1 : 1);
		if (_dogPos.x + _width >= static_cast<float>(WINDOW_WIDTH))
		{
			_dogPos.x = static_cast<float>(WINDOW_WIDTH - _width);
			_willFlip = false;

			changeDirection();
		}
		else if (_dogPos.x <= 0.0f)
		{
			_dogPos.x = 0.0f;
			_willFlip = false;

			changeDirection();
		}
	}
}

void Dog::changeDirection()
{
#ifdef DEBUG
	std::cout << _name <<" changed direction.\n";
#endif
	_lookingLeft = !_lookingLeft;

	_willFlip = false;
}

