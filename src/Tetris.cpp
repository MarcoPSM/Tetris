//
// Created by MarcoPSM on 09-02-2023.
//
#include "Tetris.h"


Tetris::Tetris() {

    dirX  = {0};
    color = {1};
    score = {0};
    rotate = {false};
    gameOver = {false};
    timerCount = {0.f};
    delay = SPEED_DELAY;

    font.loadFromFile(FONT_FILENAME);
    txtScore.setFont(font);
    txtScore.setPosition(TXT_SCORE_POS_X, TXT_SCORE_POS_Y);
    txtScore.setString(SCORE_TXT + std::to_string(score));
    txtScore.setCharacterSize(TXT_SCORE_SIZE);
    txtScore.setOutlineThickness(TXT_SCORE_THICKNESS);

    txtGameOver.setFont(font);
    txtGameOver.setPosition(TXT_GAMEOVER_POS_X, TXT_GAMEOVER_POS_Y);
    txtGameOver.setString(END_TXT);
    txtGameOver.setCharacterSize(TXT_GAMEOVER_SIZE);
    txtGameOver.setOutlineThickness(TXT_GAMEOVER_THICKNESS);

    area.resize(LINES);
    for (std::size_t i = {0}; i < area.size() ; ++i) {
        area[i].resize(COLUMNS);
    }

    forms = {
            {1,3,5,7}, // I
            {2,4,5,7}, // Z
            {3,5,4,6}, // S
            {3,5,4,7}, // T
            {2,3,5,7}, // L
            {3,5,7,6}, // J
            {2,3,4,5}, // O
    };

    window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
            TITLE_TXT,
            sf::Style::Titlebar | sf::Style::Close
            );
    window->setPosition(sf::Vector2i(WINDOW_POS_X, WINDOW_POS_Y));
    tiles.loadFromFile(SQUARES_FILENAME);
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
    sprite->setTextureRect(sf::IntRect(0, 0,
                                       SQUARE_SIDE,SQUARE_SIDE));
    grid.loadFromFile(GRID_FILENAME);
    bgGrid = std::make_shared<sf::Sprite>();
    bgGrid->setTexture(grid);
    std::uint32_t number = std::rand() % SHAPES;
    for (std::size_t i {0}; i < SQUARES ; ++i) {
        z[i].x = forms[number][i] % 2 + COLUMNS / 2 - 1;
        z[i].y = forms[number][i] / 2;
    }
}

void Tetris::events() {

    float time = clock1.getElapsedTime().asSeconds();
    clock1.restart();
    timerCount += time;

    auto event = std::make_shared<sf::Event>();
    while (window->pollEvent(*event)) {
        if (event->type == sf::Event::Closed) {
            window->close();
        }
        if (event->type == sf::Event::KeyPressed) {
            if (event->key.code == sf::Keyboard::Up) {
                rotate = true;
            } else if (event->key.code == sf::Keyboard::Right){
                ++dirX;
            } else if (event->key.code == sf::Keyboard::Left){
                --dirX;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        delay = SPEED_DELAY*0.2;
    }
}

void Tetris::draw() {
    window->clear(sf::Color::Black);
    for (std::size_t i {0}; i < LINES; ++i) {
        for (std::size_t j {0}; j < COLUMNS; ++j) {
            if (area[i][j] != 0) {
                sprite->setTextureRect(sf::IntRect((int) (area[i][j] * SQUARE_SIDE), 0,
                                                   SQUARE_SIDE,SQUARE_SIDE));
                sprite->setPosition((float) j * SQUARE_SIDE, (float) i * SQUARE_SIDE);
                window->draw(*sprite);
            }
        }
    }
    for (std::size_t i {0}; i < SQUARES; ++i) {
        sprite->setTextureRect(sf::IntRect((int) (color*SQUARE_SIDE), 0,
                                           SQUARE_SIDE,SQUARE_SIDE));
        sprite->setPosition((float) z[i].x * SQUARE_SIDE, (float) z[i].y * SQUARE_SIDE);
        window->draw(*sprite);
    }
    window->draw(*bgGrid);
    window->draw(txtScore);
    if (gameOver) {
        window->draw(txtGameOver);
    }
    window->display();
}

void Tetris::run() {
    while (window->isOpen()) {
        events();
        if (!gameOver) {
            changePosition();
            setRotate();
            moveDown();
            setScore();
            resetValues();
        }
        draw();
    }
}

void Tetris::moveDown() {
    if (timerCount > delay) {
        for (std::size_t i {0}; i < SQUARES; ++i) {
            tmp[i] = z[i];
            ++z[i].y;
        }
        if (maxLimit()) {
            for (std::size_t i {0}; i < SQUARES ; ++i) {
                area[tmp[i].y][tmp[i].x] = color;
            }
            color = std::rand() % SHAPES + 1;
            std::uint32_t number = std::rand() % SHAPES;
            for (std::size_t i {0}; i < SQUARES ; ++i) {
                z[i].x = forms[number][i] % 2 + COLUMNS / 2 - 1;
                z[i].y = forms[number][i] / 2;
            }
        }
        timerCount = 0;
    }
}

void Tetris::setRotate() {
    if (rotate) {
        Coords coords = z[1];
        for (std::size_t i {0}; i < SQUARES ; ++i) {
            std::uint32_t x = z[i].y - coords.y;
            std::uint32_t y = z[i].x - coords.x;
            z[i].x = coords.x-x;
            z[i].y = coords.y+y;

        }
        if (maxLimit()) {
            for (std::size_t i = 0; i < SQUARES ; ++i) {
                z[i] = tmp[i];
            }
        }
    }
}

void Tetris::resetValues() {
    rotate = false;
    dirX = 0;
    delay = SPEED_DELAY;
}

void Tetris::changePosition() {
    for (std::size_t i {0}; i < SQUARES; ++i) {
        tmp[i] = z[i];
        z[i].x += dirX;
    }
    if (maxLimit()) {
        for (std::size_t i = 0; i < SQUARES ; ++i) {
            z[i] = tmp[i];
        }
    }
}

bool Tetris::maxLimit() {
    for (std::size_t i {0}; i < SQUARES ; ++i) {
        if (z[i].x < 0 || z[i].x >= COLUMNS ||
            z[i].y >= LINES ||
            area[z[i].y][z[i].x]) {
            return true;
        }
    }
    return false;
}

void Tetris::setScore() {
    std::uint32_t match = LINES - 1;
    for (std::size_t i = match; i > 0; --i) {
        std::uint32_t sum {0};
        for (std::size_t j {0}; j < COLUMNS; ++j) {
            if (area[i][j]) {
                if (i == 1) {
                    gameOver = true;
                }
                ++sum;
            }
            area[match][j] = area[i][j];
        }

        if (sum < COLUMNS) {
            --match;
        } else {
            txtScore.setString("SCORE: " + std::to_string(++score));
        }
    }
}