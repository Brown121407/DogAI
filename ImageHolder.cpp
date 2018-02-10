#include "ImageHolder.hpp"
#include <iostream>


ImageHolder::ImageHolder()
{
}


ImageHolder::~ImageHolder()
{
}

void ImageHolder::loadFromFile(const std::string& path, std::string imageID)
{
	Texture* texture = new Texture;

	if (texture->loadFromFile(path))
	{
		_images.insert(std::pair<std::string, Texture*>(imageID, texture));
	}
	else
	{
		std::cout << "Could not load image.\n";
	}
}

void ImageHolder::free(std::string imageID)
{
	const auto it = _images.find(imageID);
	if (it != _images.end())
	{
		it->second->free();
		delete it->second;

		_images.erase(it);
	}
}

void ImageHolder::freeAll()
{
	for (auto const& x : _images)
	{
		x.second->free();
		delete x.second;
	}
	_images.clear();
}

const Texture* ImageHolder::getTexture(const std::string& imageID) const
{
	const auto it = _images.find(imageID);
	if (it != _images.end())
	{
		return it->second;
	}
	return nullptr;
}
