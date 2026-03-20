#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Board.hpp"

struct SaveData
{
    int  level = 1;
    int  gridSize = 3;
    int  playerScore = 0;
    int  cpuScore = 0;
    int  roundNumber = 1;
    bool playerTurn = true;
    std::vector<std::vector<int>> boardData; 
};

class SaveManager
{
public:
    static void save(const SaveData& data);          
    static SaveData load();                          
    static bool saveExists();                        
    static void resetSave(int level, int gridSize);  

private:
    static const std::string SAVE_FILE; 
};