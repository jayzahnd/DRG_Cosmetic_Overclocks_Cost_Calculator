#pragma once

const std::string counterRef = "Credit.png";

const std::string dwarves[5] =
{
	"all 4 dwarves",
	"the Driller",
	"the Engineer",
	"the Gunner",
	"the Scout"
};
const int dwarvesLength = 5;
const std::string cosmeticTypes[7] =
{
	"all",
	"headgear",
	"moustaches",
	"beards",
	"sideburns",
	"poses",
	"paintjobs"
};
const int cosmeticTypesLength = 7;

const std::string creditsName = "Credits";
const std::string croppaName = "Croppa";
const std::string jadizName = "Jadiz";
const std::string magniteName = "Magnite";
const std::string umaniteName = "Umanite";
const std::string enorPearlName = "Enor Pearl";
const std::string bismorName = "Bismor";

std::unordered_map<std::string, int> playerResources =
{
	{creditsName, 0},		// Try "Credit.png" in case of problem
	{croppaName, 0},
	{jadizName, 0},
	{magniteName, 0},
	{umaniteName, 0},
	{enorPearlName, 0},
	{bismorName, 0}
};
// The text file to read line by line
std::fstream wikiDataFile;
// Console input
std::string askInput;

int itemCount;
int DwarfClass = -2;
// -2 : invalid value
// -1 : all classes    
// 0 : Driller
// 1 : Engineer
// 2 : Gunner
// 3 : Scout

bool isNumericValue(std::string input)
{
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

void checkForKeyAndAdd(std::unordered_map<std::string, int>& umap, std::string keyStr);

void countItems(std::string line, int& counter);

bool isCountedToAdd(int currentCount, int dwarfClass);

int AskWhichDwarfClassToAnalyse(int& dwarfClass);

std::string FetchCosmeticTypePriceInfoFileName();



