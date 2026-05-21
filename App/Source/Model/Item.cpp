#include "Item.h"
#include "CommonInclude.h"

namespace 
{
	float clamp_min(float v, float mn) { return v < mn ? mn : v; }

	vector<Item> BuildCatalog() 
	{
		vector<Item> catalog;

		catalog.push_back({ "Sneakers", "+30 speed",                Rarity::COMMON,
			  [](Loadout& loadout) { loadout.playerSpeed += 30.0f; } });
		catalog.push_back({ "Boots",    "+60 speed",                Rarity::UNCOMMON,
		  [](Loadout& loadout) { loadout.playerSpeed += 60.0f; } });
		catalog.push_back({ "Magnet",   "+60 EXP attract range",    Rarity::COMMON,
		  [](Loadout& loadout) { loadout.expAttractRange += 60.0f; } });
		catalog.push_back({ "Vacuum",   "+120 attract, +30 pickup", Rarity::RARE,
		  [](Loadout& loadout) { loadout.expAttractRange += 120.0f; loadout.expPickupRange += 30.0f; } });
		catalog.push_back({ "Diet Pills", "-10 player size",        Rarity::COMMON,
		  [](Loadout& loadout) { loadout.playerSize = clamp_min(loadout.playerSize - 10.0f, 14.0f); } });
		catalog.push_back({ "Trigger Finger", "Faster fire rate",   Rarity::UNCOMMON,
		  [](Loadout& loadout) { loadout.fireRate = clamp_min(loadout.fireRate * 0.8f, 0.05f); } });
		catalog.push_back({ "Auto-Loader", "Much faster fire rate", Rarity::RARE,
		  [](Loadout& loadout) { loadout.fireRate = clamp_min(loadout.fireRate * 0.6f, 0.05f); } });
		catalog.push_back({ "Iron Will", "+50 max HP",              Rarity::UNCOMMON,
		  [](Loadout& loadout) { loadout.playerMaxHealth += 50.0f; } });


		catalog.push_back({ "Heavy Round", "+5 bullet damage",      Rarity::UNCOMMON,
		  [](Loadout& loadout) { loadout.bulletDamage += 5.0f; } });
		catalog.push_back({ "Magnum",      "+10 dmg, +50 speed",    Rarity::RARE,
		  [](Loadout& loadout) { loadout.bulletDamage += 10.0f; loadout.bulletSpeed += 50.0f; } });
		catalog.push_back({ "Devastator",  "+25 bullet damage",     Rarity::LEGENDARY,
		  [](Loadout& loadout) { loadout.bulletDamage += 25.0f; } });
		catalog.push_back({ "Long Barrel", "+500 bullet range",     Rarity::UNCOMMON,
		  [](Loadout& loadout) { loadout.bulletDistance += 500.0f; } });
		catalog.push_back({ "Sharpshooter","-50% spread",           Rarity::COMMON,
		  [](Loadout& loadout) { loadout.shootSpread = clamp_min(loadout.shootSpread * 0.5f, 0.0f); } });
		catalog.push_back({ "Wild Aim",    "+10 spread, +3 dmg",    Rarity::COMMON,
		  [](Loadout& loadout) { loadout.shootSpread += 10.0f; loadout.bulletDamage += 3.0f; } });
		catalog.push_back({ "Bigger Slugs","+3 bullet size, +1 dmg", Rarity::COMMON,
		  [](Loadout& loadout) { loadout.bulletSize += 3.0f; loadout.bulletDamage += 1.0f; } });
		catalog.push_back({ "Speed Demon", "+150 bullet speed",     Rarity::COMMON,
		  [](Loadout& loadout) { loadout.bulletSpeed += 150.0f; } });


		catalog.push_back({ "Twin Tap", "+1 shot count",            Rarity::UNCOMMON,
		  [](Loadout& loadout) { loadout.shootCount += 1; loadout.shootCount += 4.0f; } });
		catalog.push_back({ "Shotgun",  "+2 shots, +12 spread",     Rarity::RARE,
		  [](Loadout& loadout) { loadout.shootCount += 2; loadout.shootCount += 12.0f; } });
		catalog.push_back({ "Backshot", "Fire also behind you",     Rarity::EPIC,
		  [](Loadout& loadout) { loadout.shootBackwards = true; } });
		catalog.push_back({ "Pyro",       "Bullets explode on hit", Rarity::EPIC,
		  [](Loadout& loadout) { loadout.explodes = true; } });
		catalog.push_back({ "Splitter",   "Bullets split on hit",   Rarity::EPIC,
		  [](Loadout& loadout) { loadout.splits = true; } });
		catalog.push_back({ "Bird Brain", "Homing bullets",         Rarity::EPIC,
		  [](Loadout& loadout) { loadout.homing = true; } });


		catalog.push_back({ "Wavy", "Bullets travel in wave", Rarity::UNCOMMON,
		  [](Loadout& loadout) { loadout.trajectory = TrajectoryKind::Wave; } });


		catalog.push_back({ "Mom's Eye",  "Bullets become laser",   Rarity::LEGENDARY,
		  [](Loadout& loadout) {
			loadout.shotType = ShotType::Laser;

			loadout.fireRate = clamp_min(loadout.fireRate * 1.5f + 0.3f, 0.4f);
			loadout.bulletColor = MAIN_BAD_COLOR;
		  } });

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
		std::cout << "Rolling item " << (n + 1) << " of " << count << "..." << std::endl;
		float total = 0.0f;

		for (int i = 0; i < catalog.size(); ++i)
		{
			if (used[i])
				continue;

			total += weightedItems(catalog[i].rarity);
		}
		if (total <= 0.0f)
			break;

		float r = GetRandomValue(0, 1000000.0f) / (int)(total * 100000);

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
