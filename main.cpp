#include <SFML/Graphics.hpp>
#include <cctype>
#include <string>
#include "Board.h"
#include <chrono>
using namespace std;

int main()
{
    ifstream dimension("files/board_config.cfg");
    bool quit = false;
    bool pauseGame = false;
    int column;
    int row;
    int mine;
    if (dimension.is_open()) {
        dimension >> column;
        dimension >> row;
        dimension >> mine;
    }
    else {return 0;}
    int width = column * 32;
    int height = row * 32 + 100;
    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper (Welcome)", sf::Style::Close);
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text text;
    sf::Text text2;
    text.setFont(font);
    text2.setFont(font);
    text.setString("WELCOME TO MINESWEEPER!");
    text2.setString("Enter your name:");
    text.setCharacterSize(24);
    text2.setCharacterSize(20);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text2.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition((float)width/2.0f, (float)height/2.0f-150);
    sf::FloatRect textRect2 = text2.getLocalBounds();
    text2.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top + textRect2.height/2.0f);
    text2.setPosition((float)width/2.0f, (float)height/2.0f-75);
    sf::Text name;
    string str;
    name.setFont(font);
    name.setString(str+"|");
    name.setCharacterSize(18);
    name.setStyle(sf::Text::Bold);
    name.setFillColor(sf::Color::Yellow);
    sf::FloatRect usrName = name.getLocalBounds();
    name.setOrigin(usrName.left + usrName.width/2.0f, usrName.top + usrName.height/2.0f);
    name.setPosition((float)width/2.0f, (float)height/2.0f-45);
    sf::Texture hiddenTexture;
    hiddenTexture.loadFromFile("files/images/tile_hidden.png", sf::IntRect(0,0,32,32));
    sf::Texture happyTexture;
    happyTexture.loadFromFile("files/images/face_happy.png", sf::IntRect(0, 0, 64, 64));
    sf::Texture loserTexture;
    loserTexture.loadFromFile("files/images/face_lose.png", sf::IntRect(0, 0, 64, 64));
    sf::Texture winTexture;
    winTexture.loadFromFile("files/images/face_win.png", sf::IntRect(0, 0, 64, 64));
    sf::Texture mineTexture;
    mineTexture.loadFromFile("files/images/mine.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture revealTexture;
    revealTexture.loadFromFile("files/images/tile_revealed.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture debugTexture;
    debugTexture.loadFromFile("files/images/debug.png", sf::IntRect(0,0,64,64));
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("files/images/pause.png", sf::IntRect(0, 0, 64, 64));
    sf::Texture playTexture;
    playTexture.loadFromFile("files/images/play.png", sf::IntRect(0, 0, 64, 64));
    sf::Texture leaderboardTexture;
    leaderboardTexture.loadFromFile("files/images/leaderboard.png", sf::IntRect(0, 0, 64, 64));
    sf::Texture one;
    one.loadFromFile("files/images/number_1.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture two;
    two.loadFromFile("files/images/number_2.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture three;
    three.loadFromFile("files/images/number_3.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture four;
    four.loadFromFile("files/images/number_4.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture five;
    five.loadFromFile("files/images/number_5.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture six;
    six.loadFromFile("files/images/number_6.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture seven;
    seven.loadFromFile("files/images/number_7.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture eight;
    eight.loadFromFile("files/images/number_8.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture flagTexture;
    flagTexture.loadFromFile("files/images/flag.png", sf::IntRect(0, 0, 32, 32));
    sf::Texture digitsTexture;
    digitsTexture.loadFromFile("files/images/digits.png");
    sf::Sprite counter;
    counter.setTexture(digitsTexture);
    while (welcomeWindow.isOpen() && !quit)
    {
        sf::Event event{};
        while (welcomeWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                welcomeWindow.close();
                quit = true;
            }
            if (event.type == sf::Event::TextEntered) {
                if (str.length() < 10) {
                    if (isalpha((char)event.text.unicode)) {
                        if (str.empty()) {str += (char)toupper((char)event.text.unicode);}
                        else {str += (char)tolower((char)event.text.unicode);}
                        name.setString(str+"|");
                        sf::FloatRect usrName0 = name.getLocalBounds();
                        name.setOrigin(usrName0.left + usrName0.width/2.0f, usrName0.top + usrName0.height/2.0f);
                        name.setPosition((float)width/2.0f, (float)height/2.0f-45);
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    if (!str.empty()) {
                        str.pop_back();
                        name.setString(str+"|");
                        sf::FloatRect usrName1 = name.getLocalBounds();
                        name.setOrigin(usrName1.left + usrName1.width/2.0f, usrName1.top + usrName1.height/2.0f);
                        name.setPosition((float)width/2.0f, (float)height/2.0f-45);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !str.empty()) {
                    welcomeWindow.close();
                }
            }
        }
        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(text);
        welcomeWindow.draw(text2);
        welcomeWindow.draw(name);
        welcomeWindow.display();
        if (!welcomeWindow.isOpen() and !quit) {
            sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper (In-Game)", sf::Style::Close);
            sf::Sprite happyButton;
            happyButton.setTexture(happyTexture);
            happyButton.setPosition(((float)column/2)*32-32, 32*((float)row+0.5f));
            sf::Sprite debugButton;
            debugButton.setTexture(debugTexture);
            debugButton.setPosition((float)column*32-304, 32*((float)row+0.5f));
            sf::Sprite pauseButton;
            pauseButton.setTexture(pauseTexture);
            pauseButton.setPosition((float)column*32-240, 32*((float)row+0.5f));
            sf::Sprite playButton;
            playButton.setTexture(playTexture);
            playButton.setPosition((float)column*32-240, 32*((float)row+0.5f));
            sf::Sprite leaderBoardButton;
            leaderBoardButton.setTexture(leaderboardTexture);
            leaderBoardButton.setPosition((float)column*32-176, 32*((float)row+0.5f));
            sf::Sprite lose;
            lose.setTexture(loserTexture);
            lose.setPosition(((float)column/2)*32-32, 32*((float)row+0.5f));
            sf::Sprite win;
            win.setTexture(winTexture);
            win.setPosition(((float)column/2)*32-32, 32*((float)row+0.5f));
            Board minesweeper(row, column, mine);
            vector<sf::Sprite> tiles;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    sf::Sprite tile;
                    tile.setTexture(hiddenTexture);
                    tile.setPosition((float)j*32, (float)i*32);
                    tiles.push_back(tile);
                }
            }
            vector<sf::Sprite> revealTiles;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    sf::Sprite tileRe;
                    tileRe.setTexture(revealTexture);
                    tileRe.setPosition((float)j*32, (float)i*32);
                    revealTiles.push_back(tileRe);
                }
            }
            vector<sf::Sprite> mineDebug;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    if (minesweeper.gameBoard[i][j] == 1) {
                        sf::Sprite mineSprite;
                        mineSprite.setTexture(mineTexture);
                        mineSprite.setPosition((float)j*32, (float)i*32);
                        mineDebug.push_back(mineSprite);
                    }
                }
            }
            vector<sf::Sprite> mineCounts;
            vector<bool> flaggedMines(row*column, false);
            int pauseCounter = 0;
            int toggleDebug = 0;
            bool debug = false;
            bool firstClick = true;
            bool timer = true;
            bool leaderboardOpen = false;
            bool gameOver = false;
            bool youWon = false;
            int seconds = 0;
            int minutes = 0;
            int hundredth = 0;
            int tens = 0;
            int ones = 0;
            int mineCounter = mine;
            vector<string> playerTime;
            auto startTime = chrono::steady_clock::now();
            auto elapsedTime = chrono::duration<int>::zero();
            auto pausedTime = chrono::duration<int>::zero();
            bool stop = false;
            bool emptyFile = false;
            while (gameWindow.isOpen()) {
                sf::Event gameEvent{};
                while (gameWindow.pollEvent(gameEvent)) {
                    if (gameEvent.type == sf::Event::Closed) {
                        updateLeaderboard("files/leaderboard.txt");
                        gameWindow.close();
                    }
                    if (gameEvent.type == sf::Event::MouseButtonPressed) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                            auto clickPos = sf::Mouse::getPosition(gameWindow);
                            if (clickPos.y <= (height - 100) and !pauseGame and !gameOver) {
                                int col_index = floor((clickPos.x / 32));
                                int row_index = floor((clickPos.y / 32));
                                int tileIndex = row_index * column + col_index;
                                if (!minesweeper.revealBoard[row_index][col_index]) {
                                    if (flaggedMines[tileIndex]) {
                                        flaggedMines[tileIndex] = false;
                                        mineCounter++;
                                    }
                                    else {flaggedMines[tileIndex] = true; mineCounter--;}
                                }
                            }
                        }
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            auto clickPos = sf::Mouse::getPosition(gameWindow);
                            int col_index = floor((clickPos.x / 32));
                            int row_index = floor((clickPos.y / 32));
                            if (clickPos.y <= (height - 100) and !pauseGame and !flaggedMines[row_index*column+col_index] and !gameOver) {
                                mineCounts = checkMines(minesweeper.gameBoard, row, column, one, two, three, four, five, six, seven, eight, revealTexture);
                                if (firstClick) {
//                                    minesweeper.first_click(row_index, col_index, row, column);
                                    mineDebug.clear();
                                    for (int i = 0; i < row; i++) {
                                        for (int j = 0; j < column; j++) {
                                            if (minesweeper.gameBoard[i][j] == 1) {
                                                sf::Sprite mineSprite;
                                                mineSprite.setTexture(mineTexture);
                                                mineSprite.setPosition((float)j*32, (float)i*32);
                                                mineDebug.push_back(mineSprite);
                                            }
                                        }
                                    }
                                    recursiveOpen(row_index, col_index, minesweeper.gameBoard, minesweeper.revealBoard, row, column, flaggedMines);
                                    firstClick = false;
                                }
                                if (minesweeper.gameBoard[row_index][col_index] == 0) {
                                    recursiveOpen(row_index, col_index, minesweeper.gameBoard, minesweeper.revealBoard, row, column, flaggedMines);
                                    sf::Sprite revealedTile;
                                    revealedTile.setTexture(revealTexture);
                                    for (int i = 0; i < row; i++) {
                                        for (int j = 0; j < column; j++) {
                                            if (minesweeper.revealBoard[i][j] and !flaggedMines[i*column+j]) {
                                                int tile_index = (i * column) + j;
                                                revealedTile.setPosition((float)j*32, (float)i*32);
                                                tiles.at(tile_index) = revealedTile;
                                            }
                                        }
                                    }
                                }
                                else {
                                    gameOver = true;
                                }
                            }
                            else {
                                if (happyButton.getGlobalBounds().contains((float) clickPos.x, (float) clickPos.y)) {
                                    updateLeaderboard("files/leaderboard.txt");
                                    pauseCounter = 0;
                                    toggleDebug = 0;
                                    mineCounter = mine;
                                    stop = false;
                                    gameOver = false;
                                    youWon = false;
                                    debug = false;
                                    pauseGame = false;
                                    emptyFile = false;
                                    firstClick = true;
                                    timer = true;
                                    startTime = chrono::steady_clock::now();
                                    pausedTime = chrono::duration<int>::zero();
                                    minesweeper.randomize();
                                    playerTime.clear();
                                    mineDebug.clear();
                                    tiles.clear();
                                    flaggedMines.clear();
                                    for (int i = 0; i < row; i++) {
                                        for (int j = 0; j < column; j++) {
                                            if (minesweeper.gameBoard[i][j] == 1) {
                                                sf::Sprite mineSprite;
                                                mineSprite.setTexture(mineTexture);
                                                mineSprite.setPosition((float)j*32, (float)i*32);
                                                mineDebug.push_back(mineSprite);
                                            }
                                            sf::Sprite tile;
                                            tile.setTexture(hiddenTexture);
                                            tile.setPosition((float)j*32, (float)i*32);
                                            tiles.push_back(tile);
                                            flaggedMines.push_back(false);
                                        }
                                    }
                                }
                                if (debugButton.getGlobalBounds().contains((float) clickPos.x, (float) clickPos.y) and
                                    !pauseGame) {
                                    if (toggleDebug % 2 == 0) {
                                        debug = true;
                                    }
                                    else {
                                        debug = false;
                                    }
                                    toggleDebug++;
                                }
                                if ((pauseButton.getGlobalBounds().contains((float) clickPos.x, (float) clickPos.y) ||
                                    playButton.getGlobalBounds().contains((float) clickPos.x, (float) clickPos.y)) and !gameOver) {
                                    if (pauseCounter % 2 == 0) {
                                        pauseGame = true;
                                        timer = false;
                                    } else {
                                        pauseGame = false;
                                        timer = true;
                                    }
                                    pauseCounter++;
                                }
                                if (leaderBoardButton.getGlobalBounds().contains((float) clickPos.x, (float) clickPos.y)) {
                                    int lbWidth = column * 16;
                                    int lbHeight = (row * 16) + 50;
                                    sf::RenderWindow leaderBoard(sf::VideoMode(lbWidth, lbHeight),
                                                                 "Minesweeper (Leaderboard)", sf::Style::Close);
                                    sf::Text leaderBoardTitle;
                                    leaderBoardTitle.setFont(font);
                                    leaderBoardTitle.setString("LEADERBOARD");
                                    leaderBoardTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
                                    leaderBoardTitle.setCharacterSize(20);
                                    sf::FloatRect lbTitle = leaderBoardTitle.getLocalBounds();
                                    leaderBoardTitle.setOrigin(lbTitle.left + lbTitle.width / 2.0f,
                                                               lbTitle.top + lbTitle.height / 2.0f);
                                    leaderBoardTitle.setPosition((float) lbWidth / 2.0f, (float) lbHeight / 2.0f - 120);
                                    string playerString;
                                    string leaderboardStr;
                                    sf::Text players;
                                    ifstream lbFile("files/leaderboard.txt");
                                    if (lbFile.is_open()) {
                                        while (getline(lbFile, playerString)) {
                                            playerTime.push_back(playerString);
                                        }
                                    }
                                    for (int i = 0; i < playerTime.size(); i++) {
                                        string str_1 = playerTime.at(i).substr(0, playerTime.at(i).find(',')) + "\t";
                                        string str_2 = playerTime.at(i).substr(playerTime.at(i).find(',') + 1, playerTime.at(i).length()) + "\n\n";
                                        auto place = to_string(i+1) + ".\t";
                                        leaderboardStr += place;
                                        leaderboardStr += str_1;
                                        leaderboardStr += str_2;
                                        if (i == 4) {
                                            break;
                                        }
                                    }
                                    players.setFont(font);
                                    players.setString(leaderboardStr);
                                    players.setStyle(sf::Text::Bold);
                                    players.setCharacterSize(18);
                                    sf::FloatRect playerRect = players.getLocalBounds();
                                    players.setOrigin(playerRect.left + playerRect.width / 2.0f,
                                                      playerRect.top + playerRect.height / 2.0f);
                                    players.setPosition((float) lbWidth / 2.0f, (float) lbHeight / 2.0f + 20);
                                    while (leaderBoard.isOpen()) {
                                        leaderboardOpen = true;
                                        sf::Event lbEvent{};
                                        while (leaderBoard.pollEvent(lbEvent)) {
                                            if (lbEvent.type == sf::Event::Closed) {
                                                leaderboardOpen = false;
                                                playerTime.clear();
                                                leaderBoard.close();
                                            }
                                        }
                                        auto currentTime = std::chrono::steady_clock::now();
                                        pausedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime) - elapsedTime;
                                        leaderBoard.clear(sf::Color::Blue);
                                        leaderBoard.draw(leaderBoardTitle);
                                        leaderBoard.draw(players);
                                        leaderBoard.display();
                                        if (!gameOver) {gameWindow.draw(playButton);}
                                        for (const auto & tileRe : revealTiles) {
                                            gameWindow.draw(tileRe);
                                        }
                                        gameWindow.display();
                                    }
                                }
                            }
                        }
                    }
                }
                int visitCounter = 0;
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < column; j++) {
                        int tileIndex = i * column + j;
                        if (minesweeper.revealBoard[i][j]) {
                            visitCounter++;
                        }
                    }
                }
                if (mineCounter >= 0) {
                    hundredth = mineCounter / 100;
                    tens = mineCounter / 10 % 10;
                    ones = mineCounter % 10;
                }
                else {
                    hundredth = -mineCounter / 100;
                    tens = -mineCounter / 10 % 10;
                    ones = -mineCounter % 10;
                }
                sf::Sprite hundo, diez, uno, min_tenth, min_one, sec_ten, sec_one, negative_sign;
                hundo = drawCounter(counter, hundredth);
                diez = drawCounter(counter, tens);
                uno = drawCounter(counter, ones);
                min_tenth = drawCounter(counter, minutes / 10);
                min_one = drawCounter(counter, minutes % 10);
                sec_ten = drawCounter(counter, seconds / 10);
                sec_one = drawCounter(counter, seconds % 10);
                negative_sign = drawCounter(counter, -1);
                hundo.setPosition(33, 32*((float)row+0.5f)+16);
                diez.setPosition(54, 32*((float)row+0.5f)+16);
                uno.setPosition(75, 32*((float)row+0.5f)+16);
                min_tenth.setPosition(((float)column*32)-97, 32*((float)row+0.5f)+16);
                min_one.setPosition(((float)column*32)-76, 32*((float)row+0.5f)+16);
                sec_ten.setPosition(((float)column*32)-54, 32*((float)row+0.5f)+16);
                sec_one.setPosition(((float)column*32)-33, 32*((float)row+0.5f)+16);
                negative_sign.setPosition(12, 32*((float)row+0.5f)+16);
                gameWindow.clear(sf::Color::White);
                for (const auto & tile : tiles) {
                    gameWindow.draw(tile);
                }
                for (int r = 0; r < row; r++) {
                    for (int c = 0; c < column; c++) {
                        int tileIndex = r * column + c;
                        if (minesweeper.revealBoard[r][c] and !flaggedMines[tileIndex]) {
                            gameWindow.draw(mineCounts[tileIndex]);
                        }
                        if (flaggedMines[tileIndex]) {
                            sf::Sprite flag;
                            flag.setTexture(flagTexture);
                            flag.setPosition((float)c*32, (float)r*32);
                            gameWindow.draw(flag);
                        }
                    }
                }
                gameWindow.draw(hundo);
                gameWindow.draw(diez);
                gameWindow.draw(uno);
                gameWindow.draw(min_tenth);
                gameWindow.draw(min_one);
                gameWindow.draw(sec_ten);
                gameWindow.draw(sec_one);
                if (mineCounter < 0) {
                    gameWindow.draw(negative_sign);
                }
                if (debug) {
                    for (const auto & i : mineDebug) {
                        gameWindow.draw(i);
                    }
                }
                gameWindow.draw(debugButton);
                if (!pauseGame or pauseCounter == 0) {
                    gameWindow.draw(pauseButton);
                }
                else {
                    gameWindow.draw(playButton);
                    for (const auto & tileRe : revealTiles) {
                        gameWindow.draw(tileRe);
                    }
                }
                gameWindow.draw(leaderBoardButton);
                if (!gameOver) {
                    gameWindow.draw(happyButton);
                    if (timer and !leaderboardOpen) {
                        auto currentTime = std::chrono::steady_clock::now();
                        elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime) - pausedTime;
                        seconds = (int)elapsedTime.count() % 60;
                        minutes = (int)elapsedTime.count() / 60;
                    }
                    else {
                        auto currentTime = std::chrono::steady_clock::now();
                        pausedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime) - elapsedTime;
                    }
                }
                else {
                    if (youWon) {
                        debug = false;
                        gameWindow.draw(win);
                        if (!stop) {
                            ifstream lbFile("files/leaderboard.txt");
                            playerTime.clear();
                            string playerString;
                            int usrMin = 0;
                            int usrSec = 0;
                            if (file_is_empty(lbFile) or !lbFile.is_open()) {
                                emptyFile = true;
                            }
                            else {
                                while (getline(lbFile, playerString)) {
                                    playerTime.push_back(playerString);
                                }
                            }
                            int index = (int)playerTime.size();
                            if (!emptyFile) {
                                for (int i = 0; i < playerTime.size(); i++) {
                                    string str_1 = playerTime.at(i).substr(0, playerTime.at(i).find(':'));
                                    string str_2 = playerTime.at(i).substr(playerTime.at(i).find(':') + 1, 2);
                                    usrMin = stoi(str_1);
                                    usrSec = stoi(str_2);
                                    if ((minutes < usrMin) || (minutes == usrMin && seconds <= usrSec)) {
                                        index = i;
                                        break;
                                    }
                                }
                            }
                            string minuteStr;
                            string secondStr;
                            if (minutes / 10 == 0) {
                                minuteStr = "0" + to_string(minutes) + ":";
                            }
                            else {minuteStr = to_string(minutes);}
                            if (seconds / 10 == 0) {
                                secondStr = "0" + to_string(seconds);
                            }
                            else {secondStr = to_string(seconds);}
                            string newPlayer = minuteStr + secondStr;
                            newPlayer += ",";
                            newPlayer += str + "*";
                            if (index == playerTime.size()) {playerTime.push_back(newPlayer);}
                            else {playerTime.insert(playerTime.begin()+index, newPlayer);}
                            ofstream update("files/leaderboard.txt", ofstream::trunc);
                            if (update.is_open()) {
                                for (const auto & i : playerTime) {
                                    update << i << endl;
                                }
                            }
                            update.close();
                            int lbWidth = column * 16;
                            int lbHeight = (row * 16) + 50;
                            sf::RenderWindow leaderBoard(sf::VideoMode(lbWidth, lbHeight),
                                                         "Minesweeper (Leaderboard)", sf::Style::Close);
                            sf::Text leaderBoardTitle;
                            leaderBoardTitle.setFont(font);
                            leaderBoardTitle.setString("LEADERBOARD");
                            leaderBoardTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
                            leaderBoardTitle.setCharacterSize(20);
                            sf::FloatRect lbTitle = leaderBoardTitle.getLocalBounds();
                            leaderBoardTitle.setOrigin(lbTitle.left + lbTitle.width / 2.0f,
                                                       lbTitle.top + lbTitle.height / 2.0f);
                            leaderBoardTitle.setPosition((float) lbWidth / 2.0f, (float) lbHeight / 2.0f - 120);
                            string leaderboardStr;
                            sf::Text players;
                            for (int i = 0; i < playerTime.size(); i++) {
                                string str_1 = playerTime.at(i).substr(0, playerTime.at(i).find(',')) + "\t";
                                string str_2 = playerTime.at(i).substr(playerTime.at(i).find(',') + 1, playerTime.at(i).length()) + "\n\n";
                                auto place = to_string(i+1) + ".\t";
                                leaderboardStr += place;
                                leaderboardStr += str_1;
                                leaderboardStr += str_2;
                                if (i == 4) {
                                    break;
                                }
                            }
                            players.setFont(font);
                            players.setString(leaderboardStr);
                            players.setStyle(sf::Text::Bold);
                            players.setCharacterSize(18);
                            sf::FloatRect playerRect = players.getLocalBounds();
                            players.setOrigin(playerRect.left + playerRect.width / 2.0f,
                                              playerRect.top + playerRect.height / 2.0f);
                            players.setPosition((float) lbWidth / 2.0f, (float) lbHeight / 2.0f + 20);
                            while (leaderBoard.isOpen()) {
                                sf::Event lbEvent{};
                                while (leaderBoard.pollEvent(lbEvent)) {
                                    if (lbEvent.type == sf::Event::Closed) {
                                        stop = true;
                                        playerTime.clear();
                                        leaderBoard.close();
                                    }
                                }
                                leaderBoard.clear(sf::Color::Blue);
                                leaderBoard.draw(leaderBoardTitle);
                                leaderBoard.draw(players);
                                leaderBoard.display();
                                gameWindow.draw(win);
                                gameWindow.draw(hundo);
                                gameWindow.draw(diez);
                                gameWindow.draw(uno);
                                for (int r = 0; r < row; r++) {
                                    for (int c = 0; c < column; c++) {
                                        int tileIndex = r * column + c;
                                        if (flaggedMines[tileIndex]) {
                                            sf::Sprite flag;
                                            flag.setTexture(flagTexture);
                                            flag.setPosition((float)c*32, (float)r*32);
                                            gameWindow.draw(tiles[tileIndex]);
                                            gameWindow.draw(flag);
                                        }
                                    }
                                }
                                gameWindow.display();
                            }
                        }
                    }
                    else {
                        gameWindow.draw(lose);
                        for (int r = 0; r < row; r++) {
                            for (int c = 0; c < column; c++) {
                                int tileIndex = r * column + c;
                                if (minesweeper.gameBoard[r][c] == 1) {
                                    sf::Sprite tileRe;
                                    tileRe.setTexture(revealTexture);
                                    tileRe.setPosition((float)c*32, (float)r*32);
                                    tiles[tileIndex] = tileRe;
                                }
                            }
                        }
                        for (const auto &i: mineDebug) {
                            gameWindow.draw(i);
                        }
                    }
                }
                if (visitCounter == row * column - mine) {
                    gameOver = true;
                    youWon = true;
                    mineCounter = 0;
                    for (int r = 0; r < row; r++) {
                        for (int c = 0; c < column; c++) {
                            int tileIndex = r * column + c;
                            if (minesweeper.gameBoard[r][c] == 1) {
                                flaggedMines[tileIndex] = true;
                            }
                        }
                    }
                }
                gameWindow.display();
            }
        }
    }
}
