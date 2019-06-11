#pragma once

#include "gameobject.h"

class Item : public GameObject
{
protected:
	std::string desc;
	std::string handle;
public:
	std::string get_desc();
	std::string get_handle();
};