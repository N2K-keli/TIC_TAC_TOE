#include "BoardRender.hpp"

void BoardRender::init(int size, sf::RenderWindow& window, const std::string& backgroundPath)
{
    gridSize = size;

    if (!backgroundTexture.loadFromFile(backgroundPath))
        std::cerr << "Error: Could not load background: " << backgroundPath << "\n";
    else
        std::cout << "SUCCESS! Background loaded: " << backgroundPath << "\n";

    sf::Vector2u windowSize = window.getSize();
    float scaleX = (float)windowSize.x / backgroundTexture.getSize().x;
    float scaleY = (float)windowSize.y / backgroundTexture.getSize().y;

    backgroundSprite.emplace(backgroundTexture); //  create sprite with texture
    backgroundSprite->setScale({ scaleX, scaleY });

    float boardAreaWidth = (float)windowSize.x - 400.f;
    float boardAreaHeight = (float)windowSize.y - 100.f;
    cellSize = std::min(boardAreaWidth, boardAreaHeight) / gridSize;

    float boardTotalSize = cellSize * gridSize;
    boardStartX = 200.f + (boardAreaWidth - boardTotalSize) / 2.f;
    boardStartY = 50.f + (boardAreaHeight - boardTotalSize) / 2.f;

    std::cout << "BoardRender initialized — gridSize: " << gridSize
        << " cellSize: " << cellSize << "\n";
}

void BoardRender::draw(sf::RenderWindow& window, Board& board, Player& player, CPU& cpu)
{
    drawBackground(window);
    drawGrid(window, board, player, cpu);
}

void BoardRender::drawBackground(sf::RenderWindow& window)
{
    if (backgroundSprite.has_value())
        window.draw(*backgroundSprite); //  dereference with *
}

void BoardRender::drawGrid(sf::RenderWindow& window, Board& board, Player& player, CPU& cpu)
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
    sf::Sprite symbol(texture); //  constructed with texture directly — no optional needed
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