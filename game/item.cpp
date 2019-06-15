#include "item.h"

Item::~Item() {}

std::string Item::get_desc()
{
	return desc;
}

Item::Rarity Item::get_rarity()
{
	return rarity;
}

std::string Item::get_rarity_str()
{
	switch (rarity)
	{
		case Item::Rarity::common:
			return "common";
		case Item::Rarity::rare:
			return "rare";
		case Item::Rarity::epic:
			return "epic";
		case Item::Rarity::legendary:
			return "legendary";
	}
}