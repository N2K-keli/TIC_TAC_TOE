#include "SaveManager.hpp"
#include <sstream>

const std::string SaveManager::SAVE_FILE = "save/savegame.txt";

bool SaveManager::saveExists()
{
    std::ifstream file(SAVE_FILE);
    return file.good();
}

void SaveManager::save(const SaveData& data)
{
    std::ofstream file(SAVE_FILE);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open save file for writing\n";
        return;
    }

    file << "level=" << data.level << "\n";
    file << "gridSize=" << data.gridSize << "\n";
    file << "playerScore=" << data.playerScore << "\n";
    file << "cpuScore=" << data.cpuScore << "\n";
    file << "roundNumber=" << data.roundNumber << "\n";
    file << "playerTurn=" << (data.playerTurn ? 1 : 0) << "\n";
    file << "board=\n";

    for (const auto& row : data.boardData)
    {
        for (int c = 0; c < (int)row.size(); c++)
        {
            file << row[c];
            if (c < (int)row.size() - 1) file << ",";
        }
        file << "\n";
    }

    std::cout << "Game saved successfully\n";
}

SaveData SaveManager::load()
{
    SaveData data;
    std::ifstream file(SAVE_FILE);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open save file for reading\n";
        return data;
    }

    std::string line;
    bool readingBoard = false;

    while (std::getline(file, line))
    {
        if (line.find("level=") == 0) data.level = std::stoi(line.substr(6));
        else if (line.find("gridSize=") == 0) data.gridSize = std::stoi(line.substr(9));
        else if (line.find("playerScore=") == 0) data.playerScore = std::stoi(line.substr(12));
        else if (line.find("cpuScore=") == 0) data.cpuScore = std::stoi(line.substr(9));
        else if (line.find("roundNumber=") == 0) data.roundNumber = std::stoi(line.substr(12));
        else if (line.find("playerTurn=") == 0) data.playerTurn = std::stoi(line.substr(11)) == 1;
        else if (line == "board=") readingBoard = true;
        else if (readingBoard && !line.empty())
        {
            std::vector<int> row;
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ','))
                row.push_back(std::stoi(cell));
            data.boardData.push_back(row);
        }
    }

    std::cout << "Game loaded successfully\n";
    return data;
}

void SaveManager::resetSave(int level, int gridSize)
{
    SaveData data;
    data.level = level;
    data.gridSize = gridSize;
    data.playerScore = 0;
    data.cpuScore = 0;
    data.roundNumber = 1;
    data.playerTurn = true;

    //  fill board with zeros
    data.boardData.assign(gridSize, std::vector<int>(gridSize, 0));

    save(data);
    std::cout << "Save reset for level " << level << " gridSize " << gridSize << "\n";
}