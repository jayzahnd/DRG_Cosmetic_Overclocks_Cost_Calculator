// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include "Resource_cost_calculator.h"

void checkForKeyAndAdd(std::unordered_map<std::string, int>& umap, std::string keyStr)
{
    for (auto x : umap)
    {
        size_t found = keyStr.find(x.first);
        if (found != std::string::npos)
        {
            // We assume that the integer will be the only one on the line. Add this number to the value
            std::stringstream ss;
            ss << keyStr;   // insert operator
            std::string temp_str;
            int temp_int;
            while (!ss.eof()) {
                ss >> temp_str;
                if (std::stringstream(temp_str) >> temp_int)
                {
                    umap[x.first] = x.second + temp_int;
                }
                temp_str = "";
            }
            break;
        }
    }
}

void countItems(std::string line, int& counter)
{
    std::stringstream iss(line);
    std::string word;
    // extract all words separated by white space
    while (iss >> word) {
        // compare with wanted
        if (counterRef == word) {  // counterRef is "Credit.png", so it will always return the total item count
            ++counter;
        }
    }
}

bool isCountedToAdd(int currentCount, int dwarfClass)
{
    // -1 : all classes
    // dwarfclass is modulo 4 with :
    // 0 : Driller
    // 1 : Engineer
    // 2 : Gunner
    // 3 : Scout
    if (dwarfClass < 0)
    {   return true; }
    else
    {   return (currentCount % 4 == dwarfClass); }
}

int AskWhichDwarfClassToAnalyse(int& dwarfClass)
{
    std::string conInput;
    std::cout << "Which class do you want to check? \n";
    std::cout << "Options: 0 = all , 1 = Driller, 2 = Engineer, 3 = Gunner, 4 = Scout \n";
    std::cin >> conInput;
    if (isNumericValue(conInput) && (std::stoi(conInput) < dwarvesLength))
    {
        dwarfClass = std::stoi(conInput) - 1; // Moving [0;4] to [-1;3] interval to later use modulo 4 check
    }
    else
    {
        std::cout << conInput << " is not a valid input \n";
        dwarfClass = -2;
    }

    return dwarfClass;
}

std::string FetchCosmeticTypePriceInfoFileName()
{
    std::stringstream fileNameStream;
    fileNameStream << "wiki data/DRG_Wiki_Costs_";

    std::cout << "Which cosmetic type do you want to analyse for " << dwarves[DwarfClass + 1] << "? \n";
    std::cout << "Options: 0/all, 1/headgear, 2/moustaches, 3/beards, 4/sideburns, 5/poses, 6/paintjobs \n";// | type 'current' to view all currently crafted OCs' \n";
    std::cin >> askInput;

    if ("current" == askInput)
    {
        askInput = "";
        std::cout << "Which currently crafted OC category do you want to analyse for " << dwarves[DwarfClass + 1] << "? \n";
        std::cout << "Options for current: 0/all, 1/headgear, 2/moustaches, 3/beards, 4/sideburns, 5/poses, 6/paintjobs \n";
        fileNameStream << "current_";
        std::cin >> askInput;
    }
    if (isNumericValue(askInput) && (std::stoi(askInput) < cosmeticTypesLength))
    {
        fileNameStream << cosmeticTypes[std::stoi(askInput)] << ".txt";
        return fileNameStream.str();
    }

    std::cout << askInput << " is not a valid input \n";
    return "";
}

void ProcessFile(std::fstream& dataFile, std::string fileName)
{
    dataFile.open(fileName, std::ios::in);
    if (dataFile.is_open()) {
        std::cout << " \n";
        std::cout << "File opened...\n";
        std::string currentLine;

        while (getline(dataFile, currentLine))
        {
            // Count items
            countItems(currentLine, itemCount);

            // Search string that corresponds to an existing key. If found, and if class corresponds, add the number on that line to the value.                
            if (isCountedToAdd(itemCount, DwarfClass)) {
                checkForKeyAndAdd(playerResources, currentLine);
            }
        }
        dataFile.close();
    }
}

int main()
{
    std::fstream wikiDataFileStream;
    std::cout << "Hit Return key to continue. \n";

    while (getline(std::cin, askInput)) {

        do
        {
            AskWhichDwarfClassToAnalyse(DwarfClass);
        } while (-2 == DwarfClass);

        std::string fileNameNew;
        do
        {
            fileNameNew = FetchCosmeticTypePriceInfoFileName();
        } while (fileNameNew.empty());

        // Reset item count every time we do a new search.
        itemCount = 0;
        for (auto x : playerResources)
        {
            playerResources[x.first] = 0;
        }

        // Open text file to read line by line
        ProcessFile(wikiDataFileStream, fileNameNew);

        if ((DwarfClass + 1) != 0) // equivalent of: if(dwarves[DwarfClass + 1] != dwarves[0])
        {
            float tmp = (float)(itemCount /= 4.0);
            std::cout << "Total items found for " << dwarves[DwarfClass + 1] << ": " << tmp << " \n";
        }
        else
        {
            std::cout << "Total items found for all classes: " << itemCount << " \n";
        }

        std::cout << " \n";
        std::cout << "Total cost: \n";
        std::cout << creditsName << " : " << playerResources[creditsName] << std::endl;
        std::cout << croppaName << " : " << playerResources[croppaName] << std::endl;
        std::cout << jadizName << " : " << playerResources[jadizName] << std::endl;
        std::cout << magniteName << " : " << playerResources[magniteName] << std::endl;
        std::cout << umaniteName << " : " << playerResources[umaniteName] << std::endl;
        std::cout << enorPearlName << " : " << playerResources[enorPearlName] << std::endl;
        std::cout << bismorName << " : " << playerResources[bismorName] << std::endl;
        std::cout << " \n";
    }
    return 0;
}