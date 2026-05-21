#pragma once
#include "raylib.h"
#include "Loadout.h"
#include "Utility/Rarity.h"

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

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
