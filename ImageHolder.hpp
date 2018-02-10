#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include <sstream>
#include "Texture.hpp"

class ImageHolder
{
public:
	ImageHolder();
	~ImageHolder();

	void loadFromFile(const std::string& path, std::string imageID);

	void free(std::string imageID);

	void freeAll();

	const Texture* getTexture(const std::string& imageID) const;

private:
	std::map<std::string, Texture*> _images;
};

