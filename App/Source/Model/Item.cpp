#include "Item.h"
#include "CommonInclude.h"



Color RarityColor(Rarity rarity)
{
	switch (rarity)
	{
	case Rarity::COMMON:    return GRAY;
	case Rarity::UNCOMMON:  return GREEN;
	case Rarity::RARE:      return BLUE;
	case Rarity::EPIC:      return PURPLE;
	case Rarity::LEGENDARY: return ORANGE;
	default: return WHITE;
	}
}

int RaritySides(Rarity rarity)
{
	switch (rarity)
	{
	case Rarity::COMMON:    return 4;
	case Rarity::UNCOMMON:  return 5;
	case Rarity::RARE:      return 6;
	case Rarity::EPIC:      return 7;
	case Rarity::LEGENDARY: return 8;
	default: return 6;
	}
}

const char* RarityName(Rarity rarity)
{
	switch (rarity)
	{
	case Rarity::COMMON:    return "Common";
	case Rarity::UNCOMMON:  return "Uncommon";
	case Rarity::RARE:      return "Rare";
	case Rarity::EPIC:      return "Epic";
	case Rarity::LEGENDARY: return "Legendary";
	default: return "Unknown";
	}
}

namespace 
{
	vector<Item> BuildCatalog() 
	{
		vector<Item> catalog;

		catalog.push_back({ "Sneakers", "Increases movement speed by 30.", Rarity::COMMON,
		[](Loadout& loadout) { loadout.playerSpeed = +30; }});



		return catalog;
	}
}

vector<Item>& GetAllItems()
{
	static vector<Item> catalog = BuildCatalog();
	return catalog;
}

vector<Item> RollItems(int count, int playerLevel)
{
	auto& catalog = GetAllItems();

	if (catalog.empty() || count <= 0)
		return { };

	auto weightedItems = [&](Rarity rarity) -> float
	{
		float lvl = (float)playerLevel;
		switch (rarity)
		{	
		case Rarity::COMMON:	return max(5.0f, 60.0f - lvl * 5);
		case Rarity::UNCOMMON:	return max(5.0f, 30.0f - lvl * 5);
		case Rarity::RARE:		return min(25.0f, 8.0f + lvl * 2.5f);
		case Rarity::EPIC:		return min(15.0f, 1.0f + lvl * 1.8f);
		case Rarity::LEGENDARY:	return min(10.0f, lvl * 0.7f);
		default:				return 1;
		}
	};

	vector<Item> rolledItems;
	vector<bool> used(catalog.size(), false);

	for (int n = 0; n < count; ++n)
	{
		float total = 0.0f;

		for (int i = 0; i < catalog.size(); ++i)
		{
			if (used[i])
				continue;

			total += weightedItems(catalog[i].rarity);
		}
		if (total <= 0.0f)
			break;

		float r = GetRandomValue(0, (int)(total * 100)) / 100.0f;

		int index = -1;

		for (int i = 0; i < catalog.size(); ++i)
		{
			if (used[i])
				continue;

			float w = weightedItems(catalog[i].rarity);

			if (r < w)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
			break;

		used[index] = true;
		rolledItems.push_back(catalog[index]);
	}

	return rolledItems;
}
