#pragma once

constexpr int MAX_NAME_SIZE = 64;
constexpr int MAX_MOVEMENT = 20;
constexpr int MAX_HEADERSIZE = 10;
constexpr int MAX_STATE = 3;

struct Movement
{
    int moveCount;
    int moveIndex;

    bool xHalf;
    bool yHalf;
    bool yOver;

    int moveData[MAX_MOVEMENT][2];
    char name[MAX_NAME_SIZE];
};