#include "BoardRender.hpp"

void BoardRender::init(int size, sf::RenderWindow& window, const std::string& backgroundPath)
{
    gridSize = size;

    if (!backgroundTexture.loadFromFile(backgroundPath))
        std::cerr << "Error: Could not load background: " << backgroundPath << "\n";
    else
        std::cout << "SUCCESS! Background loaded: " << backgroundPath << "\n";

    sf::Vector2u windowSize = window.getSize();
    float winW = (float)windowSize.x;
    float winH = (float)windowSize.y;

    // background scales to fill entire window
    backgroundSprite.emplace(backgroundTexture);
    backgroundSprite->setScale({
        winW / backgroundTexture.getSize().x,
        winH / backgroundTexture.getSize().y
        });

    //  panels are 20% of window width each side
    float panelWidth = winW * 0.20f;

    //  board area is the middle 60% of window width, 90% of height
    float boardAreaWidth = winW * 0.60f;
    float boardAreaHeight = winH * 0.90f;

    //  cell size based on smallest dimension to keep cells square
    cellSize = std::min(boardAreaWidth, boardAreaHeight) / gridSize;

    //  center board in middle zone proportionally
    float boardTotalSize = cellSize * gridSize;
    boardStartX = panelWidth + (boardAreaWidth - boardTotalSize) / 2.f;
    boardStartY = (winH - boardTotalSize) / 2.f; //  vertically centered

    std::cout << "BoardRender initialized — gridSize: " << gridSize
        << " cellSize: " << cellSize << "\n";
}

void BoardRender::draw(sf::RenderWindow& window, Board& board, Player& player, CPU& cpu,
    int cursorRow, int cursorCol)
{
    drawBackground(window);
    drawGrid(window, board, player, cpu, cursorRow, cursorCol);
}

void BoardRender::drawBackground(sf::RenderWindow& window)
{
    if (backgroundSprite.has_value())
        window.draw(*backgroundSprite);
}

void BoardRender::drawGrid(sf::RenderWindow& window, Board& board, Player& player, CPU& cpu,
    int cursorRow, int cursorCol)
{
    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
        {
            sf::RectangleShape cell({ cellSize, cellSize });
            cell.setPosition({
                boardStartX + col * cellSize,
                boardStartY + row * cellSize
                });

            //  highlight cursor cell golden yellow, rest stay brown
            if (row == cursorRow && col == cursorCol)
                cell.setFillColor(sf::Color(255, 215, 0)); // golden yellow
            else
                cell.setFillColor(cellColor);

            cell.setOutlineColor(borderColor);
            cell.setOutlineThickness(3.f);
            window.draw(cell);

            CellState state = board.getCell(row, col);
            if (state == CellState::player)
                drawSymbol(window, player.getSymbolTexture(), row, col);
            else if (state == CellState::cpu)
                drawSymbol(window, cpu.getSymbolTexture(), row, col);
        }
    }
}

void BoardRender::drawSymbol(sf::RenderWindow& window, sf::Texture& texture, int row, int col)
{
    sf::Sprite symbol(texture);
    float padding = cellSize * 0.1f;
    float symbolSize = cellSize - (padding * 2.f);
    sf::Vector2u texSize = texture.getSize();
    symbol.setScale({ symbolSize / texSize.x, symbolSize / texSize.y });
    symbol.setPosition({
        boardStartX + col * cellSize + padding,
        boardStartY + row * cellSize + padding
        });
    window.draw(symbol);
}