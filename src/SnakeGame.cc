//
// Created by cjn on 2018/4/22.
//

#include "SnakeGame.h"

SnakeGame::SnakeGame(int width, int height, vector<pair<int, int>> food) {
    this->width = width;
    this->height = height;
    this->food = food;
    score = 0;
    snake.push_back({0, 0});
}
int SnakeGame::move(string direction) {
    auto head = snake.front(), tail = snake.back();
    //move tail first
    snake.pop_back();
    if (direction == "U") --head.first;
    else if (direction == "L") --head.second;
    else if (direction == "R") ++head.second;
    else if (direction == "D") ++head.first;
    if (count(snake.begin(), snake.end(), head) || head.first < 0 || head.first >= height || head.second < 0 || head.second >= width) {
        return -1;
    }
    //move head
    snake.insert(snake.begin(), head);
    //check food
    if (!food.empty() && head == food.front()) {
        food.erase(food.begin());
        snake.push_back(tail);
        ++score;
    }
    return score;
}