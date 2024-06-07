#pragma once

//Note: this is not built with C++17, so I didn't use string_view or inline for the string literals
namespace constantNames
{
	// "Credit.png" appears once per unique item in our text file from the wiki page, which is a decent item to use as a counter.
	constexpr auto& counterRef = "Credit.png";
	
	// The names of our resources
	constexpr auto& creditsName = "Credits";
	constexpr auto& croppaName = "Croppa";
	constexpr auto& jadizName = "Jadiz";
	constexpr auto& magniteName = "Magnite";
	constexpr auto& umaniteName = "Umanite";
	constexpr auto& enorPearlName = "Enor Pearl";
	constexpr auto& bismorName = "Bismor";
}

extern std::array<std::string, 5> const dwarves;
int dwarvesLength;
extern std::array<std::string, 7> const cosmeticTypes;
int cosmeticTypesLength;


extern std::unordered_map<std::string, int> playerResources;
// The text file to read line by line
std::fstream wikiDataFile;
// Console input
std::string askInput;

int itemCount;
int DwarfClass = -2;
// -2 : invalid value (default)
// -1 : all classes    
// 0 : Driller
// 1 : Engineer
// 2 : Gunner
// 3 : Scout

void checkForKeyAndAdd(std::unordered_map<std::string, int>& umap, std::string keyStr);

// Scans the line. If it finds "Credit.png", add 1 to the item counter.
void countItems(std::string line, int& counter);

bool isNumericValue(std::string input);

// Add if it corresponds to the class or classes we wish to examine.
bool canItBeAdded(int currentCount, int dwarfClass);

int AskWhichDwarfClassToAnalyse(int& dwarfClass);

std::string FetchCosmeticTypePriceInfoFileName();



