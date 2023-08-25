#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
using namespace std;

bool isValid(int row_index, int col_index, int row_count, int col_count);
int checkAdjacent(vector<vector<int>>& board, int i, int j);
void recursiveOpen(int row_index, int col_index, vector<vector<int>>& board, vector<vector<bool>>& revealedTile, int rows, int cols);

struct Board {
    int col = 0;
    int row = 0;
    int mine = 0;
    int mine_count = 0;
    vector<vector<int>> gameBoard;
    vector<vector<bool>> revealBoard;
    Board(int num_rows, int column, int mines) {
        row = num_rows;
        col = column;
        mine = mines;
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(0.0, row);
        uniform_real_distribution<double> dist2(0.0, col);
        vector<int> rows(col, 0);
        vector<vector<int>> board(row, rows);
        while (mine_count != mine) {
            int index1 = (int)dist(mt);
            int index2 = (int)dist2(mt);
            if (board[index1][index2] == 0) {
                board[index1][index2] = 1;
                mine_count++;
            }
        }
        vector<bool> boolBoardRows(col, false);
        vector<vector<bool>> boolBoard(row, boolBoardRows);
        gameBoard = board;
        revealBoard = boolBoard;
    }
    void randomize() {
        int new_mine_count = 0;
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(0.0, row);
        uniform_real_distribution<double> dist2(0.0, col);
        srand(time(NULL));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                gameBoard[i][j] = 0;
                revealBoard[i][j] = false;
            }
        }
        while (new_mine_count != mine) {
//            int index1 = (int)dist(mt);
//            int index2 = (int)dist2(mt);
            int index1 = rand() % row;
            int index2 = rand() % col;
            if (gameBoard[index1][index2] == 0) {
                gameBoard[index1][index2] = 1;
                new_mine_count++;
            }
        }
    }
//    vector<vector<int>>& first_click(int i, int j, int row_count, int col_count) {
//        if (gameBoard[i][j] == 1) {
//            gameBoard[i][j] = 0;
//            if (i == 0 and j == 0) {
//                for (int r = 0; r < row_count; r++) {
//                    for (int c = 1; c < col_count; c++) {
//                        if (gameBoard[r][c] == 0) {
//                            gameBoard[r][c] = 1;
//                            return gameBoard;
//                        }
//                    }
//                }
//            }
//            else {
//                for (int r = 0; r < row_count; r++) {
//                    for (int c = 0; c < col_count; c++) {
//                        if (gameBoard[r][c] == 0) {
//                            gameBoard[r][c] = 1;
//                            return gameBoard;
//                        }
//                    }
//                }
//            }
//        }
//        return gameBoard;
//    }
};

bool isValid(int row_index, int col_index, int row_count, int col_count) {
    if (row_index < 0 || col_index < 0 || row_index > row_count - 1 || col_index > col_count -1) {
        return false;
    }
    return true;
}

int checkAdjacent(vector<vector<int>>& board, int i, int j) {
    int row_count = (int)board.size();
    int col_count = (int)board[0].size();
    int mine_count = 0;

    if (board[i][j] == 0) {
        if (isValid(i-1, j-1, row_count, col_count) and board[i-1][j-1] == 1) {
            mine_count++;
        }
        if (isValid(i - 1, j, row_count, col_count) and board[i-1][j] == 1) {
            mine_count++;
        }
        if (isValid(i - 1, j + 1, row_count, col_count) and board[i-1][j+1] == 1) {
            mine_count++;
        }
        if (isValid(i, j - 1, row_count, col_count) and board[i][j-1] == 1) {
            mine_count++;
        }
        if (isValid(i, j + 1, row_count, col_count) and board[i][j+1] == 1) {
            mine_count++;
        }
        if (isValid(i + 1, j - 1, row_count, col_count) and board[i+1][j-1] == 1) {
            mine_count++;
        }
        if (isValid(i + 1, j, row_count, col_count) and board[i+1][j] == 1) {
            mine_count++;
        }
        if (isValid(i + 1, j + 1, row_count, col_count) and board[i+1][j+1] == 1) {
            mine_count++;
        }
    }
    return mine_count;
}

vector<sf::Sprite> checkMines(vector<vector<int>> gameBoard, int row, int col, sf::Texture& one, sf::Texture& two,
                              sf::Texture& three, sf::Texture& four, sf::Texture& five, sf::Texture& six,
                              sf::Texture& seven, sf::Texture& eight, sf::Texture& reveal) {
    vector<sf::Sprite> mineIndicator;
    sf::Sprite num;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (checkAdjacent(gameBoard, i, j) == 1) {
                num.setTexture(one);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else if (checkAdjacent(gameBoard, i, j) == 2) {
                num.setTexture(two);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else if (checkAdjacent(gameBoard, i, j) == 3) {
                num.setTexture(three);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else if (checkAdjacent(gameBoard, i, j) == 4) {
                num.setTexture(four);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else if (checkAdjacent(gameBoard, i, j) == 5) {
                num.setTexture(five);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else if (checkAdjacent(gameBoard, i, j) == 6) {
                num.setTexture(six);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else if (checkAdjacent(gameBoard, i, j) == 7) {
                num.setTexture(seven);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else if (checkAdjacent(gameBoard, i, j) == 8) {
                num.setTexture(eight);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
            else{
                num.setTexture(reveal);
                num.setPosition((float)j*32, (float)i*32);
                mineIndicator.push_back(num);
            }
        }
    }
    return mineIndicator;
}

void recursiveOpen(int row_index, int col_index, vector<vector<int>>& board, vector<vector<bool>>& revealedTile, int rows, int cols, vector<bool> flaggedMines) {
    if (board[row_index][col_index] == 1 || revealedTile[row_index][col_index] || flaggedMines[row_index*cols+col_index]) {
        return;
    }
    revealedTile[row_index][col_index] = true;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <=1; j++) {
            int row_count = row_index + i;
            int col_count = col_index + j;
            if (row_count >= 0 && row_count < rows && col_count < cols && col_count >= 0 && checkAdjacent(board, row_index, col_index) == 0) {
                recursiveOpen(row_count, col_count, board, revealedTile, rows, cols, flaggedMines);
            }
        }
    }
}

sf::Sprite drawCounter(sf::Sprite counter, int num) {
    sf::Sprite finCounter;
    if (num < 0) {
        counter.setTextureRect(sf::IntRect(210, 0, 21, 32));
    }
    else if (num < 10){
        counter.setTextureRect(sf::IntRect(num*21, 0, 21, 32));
    }
    finCounter = counter;
    return finCounter;
}

bool file_is_empty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

void updateLeaderboard(const string& filename) {
    vector<string> tempVec;
    string lines;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        while (getline(inFile, lines)) {
            tempVec.push_back(lines);
        }
        for (auto& user : tempVec) {
            if (user.find("*") != string::npos) {user.pop_back();}
        }
    }
    ofstream update(filename, ofstream::trunc);
    if (update.is_open()) {
        for (const auto & i : tempVec) {
            update << i << endl;
        }
    }
}
