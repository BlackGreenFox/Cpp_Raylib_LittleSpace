#pragma once
#include "raylib.h"
#include "Loadout.h"

#include <string>
#include <vector>
#include <functional>
#include <algorithm>

enum class Rarity
{
	COMMON,
	UNCOMMON,
	RARE,
	EPIC,
	LEGENDARY
};


Color RarityColor(Rarity rarity);
int RaritySides(Rarity rarity);
const char* RarityName(Rarity rarity);

using std::vector;
using std::string;
using std::function;
using std::max;
using std::min;

struct Item
{
	string name;
	string description;
	Rarity rarity;
	function<void(Loadout&)> apply;
};

vector<Item>& GetAllItems();
vector<Item> RollItems(int count, int playerLevel);
