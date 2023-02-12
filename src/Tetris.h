//
// Created by MarcoPSM on 09-02-2023.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

// sudo apt install libsfml-dev
//https://www.sfml-dev.org/tutorials/2.1/start-linux.php
#include <SFML/Graphics.hpp>
#include <memory>


class Tetris {
private:
    static const std::uint32_t LINES   {20};
    static const std::uint32_t COLUMNS {10};
    static const std::uint32_t SQUARES {4};
    static const std::uint32_t SHAPES  {7};
    static const std::uint32_t SQUARE_SIDE {36};

    static const std::uint32_t WINDOW_POS_X {100};
    static const std::uint32_t WINDOW_POS_Y {100};
    static constexpr std::uint32_t WINDOW_WIDTH  {SQUARE_SIDE*10};
    static constexpr std::uint32_t WINDOW_HEIGHT {SQUARE_SIDE*20};

    static constexpr float TXT_SCORE_POS_X {100.0};
    static constexpr float TXT_SCORE_POS_Y {10.0};
    static const std::uint32_t TXT_SCORE_SIZE {30};
    static const std::uint32_t TXT_SCORE_THICKNESS {3};

    static constexpr float TXT_GAMEOVER_POS_X {45.0};
    static constexpr float TXT_GAMEOVER_POS_Y {300.0};
    static const std::uint32_t TXT_GAMEOVER_SIZE {50};
    static const std::uint32_t TXT_GAMEOVER_THICKNESS {3};

    static constexpr float SPEED_DELAY {0.3};

    inline static const std::string FONT_FILENAME = {"./../resources/font/aloevera-font/Aloevera-OVoWO.ttf"};
    inline static const std::string SQUARES_FILENAME = {"./../resources/img/squares.png"};
    inline static const std::string GRID_FILENAME = {"./../resources/img/grid.png"};

    inline static const std::string TITLE_TXT = {"MarcoPSM Tetris"};
    inline static const std::string SCORE_TXT = {"SCORE: "};
    inline static const std::string END_TXT   = {"Game Over"};

    std::uint32_t dirX, color, score;
    bool rotate, gameOver;
    float timerCount, delay;

    std::vector<std::vector<std::uint32_t >> area;
    std::vector<std::vector<std::uint32_t >> forms;

    struct Coords {
        std::uint32_t x, y;
    } z[SQUARES], tmp[SQUARES];

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Sprite> sprite, bgGrid;
    sf::Texture tiles, grid;
    sf::Clock clock1;
    sf::Font font;
    sf::Text txtScore, txtGameOver;


protected:
    void events();
    void draw();
public:
    Tetris();
    void run();
    void moveDown();
    void setRotate();
    void resetValues();
    void changePosition();
    bool maxLimit();
    void setScore();
};

#endif //TETRIS_TETRIS_H
