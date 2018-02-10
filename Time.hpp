#pragma once

class Time
{
public:
	static float getDeltaTime();
	static void setDeltaTime(float dt);

	static float getDeltaTimeSeconds();

private:
	static float _deltaTime;
};

inline float Time::getDeltaTime()
{
	return _deltaTime;
}

inline void Time::setDeltaTime(float dt)
{
	_deltaTime = dt;
}

inline float Time::getDeltaTimeSeconds()
{
	return _deltaTime / 1000;
}

