#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>

#include "EnemyType.h"

#include "StageInfo.h"


#define MOVEMENT_SIZE 128
#define ENEMYTYPES_SIZE 128

#define MAX_BUFFER_SIZE 1024
#define MAX_LEVEL_SIZE 12

#define EXT ".txt"

StageInfo StageInfo::_global;

char* StageInfo::getFile(const char* fileName)
{
    std::ifstream ifs;
    ifs.open(fileName, std::ios::in | std::ios::ate);

    if (!ifs.is_open())
    {
        std::cerr << "Failed to open the " << fileName << '\n';
        return nullptr;
    }

    std::streamsize size = ifs.tellg();
    ifs.seekg(0);

    char* buffer = (char*)malloc((size_t)size);

    ifs.read(buffer, size);
    std::streamsize readSize = ifs.gcount();

    if (buffer)
        buffer[readSize] = '\0';

    ifs.close();


    return buffer;
}
bool StageInfo::my_atoi(int* ret, char* str)
{
    int k = 0;
    int sign = 1;

    if (!str)
        return false;

    if (str[0] == '-')
    {
        sign = -1;
        str++;
    }

    while (*str) {

        if ((*str) < '0' || (*str) > '9')
            return false;

        k = (k * 10) + (*str) - '0';
        str++;
    }

    *ret = k * sign;
    return true;
}
void StageInfo::my_itoa(int val, char* buf)
{
    int d;
    int k = 10;
    int cnt = 1;

    if (val < 0)
    {
        *buf = '-';
        ++buf;
        val *= -1;
    }

    while (k <= val)
    {
        cnt++;
        k *= 10;
    }

    k /= 10;

    while (cnt-- > 0)
    {
        d = (val / k);
        *buf = d + '0';

        val -= d * k;
        k /= 10;
        ++buf;
    }

    *buf = '\0';

}
int  StageInfo::getTokenList(char* data, const char* del, char** tokenList)
{
    char* context = nullptr;
    char* token;
    int tokenNum = 0;

    token = strtok_s(data, del, &context);
    while (token)
    {
        tokenList[tokenNum++] = token;
        token = strtok_s(nullptr, del, &context);
    }

    return tokenNum;
}

// movement
bool StageInfo::setMoveData(Movement* mp, char* moveStr, char** moveList, int* index)
{
    int xpos, ypos, vpos;
    int posNum = getTokenList(moveStr, " ,()", moveList);

    if (!(my_atoi(&xpos, moveList[0]) &&
          my_atoi(&ypos, moveList[1])))
    {
        std::cerr << "The coordinates are incorrect\n";
        return false;
    }

    if (posNum > 2)
    {
        if (!my_atoi(&vpos, moveList[3]))
        {
            std::cerr << "The coordinates are incorrect\n";
            return false;
        }

        switch (moveList[2][0])
        {
        case 'x':
            for (int i{ 0 }; i < vpos; ++i)
            {
                mp->moveData[*index][0] = xpos;
                mp->moveData[*index][1] = ypos;
                (*index)++;
            }
        }
    }
    else
    {
        mp->moveData[*index][0] = xpos;
        mp->moveData[*index][1] = ypos;
        (*index)++;
    }

    return true;
}
bool StageInfo::setMovementField(Movement* mp, char* fileName, char* fileDetail)
{
    const char* del = " .*";
    char* tokenList[MAX_MOVEMENT];
    char* moveList[MAX_MOVEMENT];

    int code;
    int moveCount = 0;

    int tokenNum = getTokenList(fileDetail, del, tokenList);
    my_atoi(&code, tokenList[0]);

    switch (code)
    {
    case 1:
        strcpy_s(mp->name, tokenList[1]);
        return true;
    case 2:
        for (int i = 1; i < tokenNum; ++i)
        {
            if (!setMoveData(mp, tokenList[i], moveList, &moveCount))
                return false;
        }
        mp->moveCount = moveCount;
        return true;
    case 3:
        if (strlen(tokenList[1]) < MAX_STATE)
        {
            std::cerr << "Movement stateFields are incorrect\n";
            return false;
        }

        if (tokenList[1][0] == '1')
            mp->xHalf = true;
        else
            mp->xHalf = false;

        if (tokenList[1][1] == '1')
            mp->yHalf = true;
        else
            mp->yHalf = false;

        if (tokenList[1][2] == '1')
            mp->yOver = true;
        else
            mp->yOver = false;

        return true;
    default:
        std::cerr << "The file " << fileName << " format is incorrect" << '\n';
        return false;
    }
}
bool StageInfo::makeMoves(EnemyType* et, char* filename)
{
    char moveName[MAX_NAME_SIZE]{ "mov_" };
    strcat_s(moveName, MAX_NAME_SIZE, filename);
    strcat_s(moveName, MAX_NAME_SIZE, EXT);

    char* buf = getFile(moveName);
    std::stringstream ss(buf);
    char line[MAX_BUFFER_SIZE];

    et->_mv.moveIndex = 0;
    while (ss.getline(line, MAX_BUFFER_SIZE))
    {
        if (!setMovementField(&(et->_mv), filename, line))
            return false;
    }
    

    free(buf);
    return true;
}

// enemyType
bool StageInfo::setCharField(char* field, const char* str, const char* fieldName)
{
    if (str[0] < 33 || str[0] > 126)
    {
        std::cerr << "Failed to extractt the " << fieldName << " field\n";
        return false;
    }
    field[0] = str[0];

    return true;
}
bool StageInfo::setIntField(int* field, char* snum, const char* fieldName)
{
    if (!my_atoi(field, snum))
    {
        std::cerr << "Failed to extract the " << fieldName << " field\n";
        return false;
    }
    return true;
}
bool StageInfo::setEnemyTypeField(EnemyType* et, char* field)
{
    const char* del = " .:";
    char* tokenList[20];

    int tokenNum = getTokenList(field, del, tokenList);
    int fieldNum;

    if (tokenNum == 0)
    {
        std::cerr << "Failed to extract field\n";
        return false;
    }

    my_atoi(&fieldNum, tokenList[0]);

    switch (fieldNum)
    {
    case 1:
        return setCharField(&et->shape, tokenList[2], "shape");
    case 2:
        return setCharField(&et->attackShape, tokenList[2], "attackShape");
    case 3:
        return setIntField(&et->cooldown, tokenList[2], "cooldown");
    case 4:
        return setIntField(&et->perAttackCount, tokenList[2], "perAttackCount");
    case 5:
        if (!makeMoves(et, tokenList[2]))
            return false;
        break;
    default:
        std::cerr << "Failed to extract field\n";
        return false;
    }

    return true;
}
bool StageInfo::makeEnemyTypes(char* filename)
{
    char enemyTypeName[MAX_NAME_SIZE];
    strcpy_s(enemyTypeName, MAX_NAME_SIZE, filename);
    strcat_s(enemyTypeName, MAX_NAME_SIZE, EXT);

    char* buf = getFile(enemyTypeName);
    std::stringstream ss(buf);
    char line[MAX_BUFFER_SIZE];

    EnemyType et;
    while (ss.getline(line, MAX_BUFFER_SIZE))
    {
        if (!setEnemyTypeField(&et, line))
            return false;
    }

    _enemyTypes.push_back(et);
    free(buf);
    return true;
}

// stage
bool StageInfo::setStage(char* line, int row)
{
    size_t len = strlen(line);
   
    if (len > COL)
    {
        for (size_t col{ COL }; col < len; ++col)
        {
            if (line[col] != ' ' && line[col] != '\0')
            {
                std::cerr << "There is an enemy that exceeds the range\n";
                return false;
            }
        }
    }

    for (int col{ 0 }; col < COL; ++col)
    {
        if (line[col] == ' ')
            continue;

        if (line[col] == '\0')
            break;

        if (_stages.size() >= MAX_ENEMY_COUNT)
        {
            std::cerr << "Maximum enemy count exceeded\n";
            return false;
        }

        std::size_t i = 0;
        for (; i < _enemyTypes.size(); ++i)
        {
            if (_enemyTypes[i].shape == line[col])
            {
                _stages.push_back(Stage{ _enemyTypes[i].shape, col , row });
                break;
            }
        }
    }

    return true;

}
bool StageInfo::loadStage()
{
    char stageName[MAX_NAME_SIZE]{ "stage" };
    char level[MAX_LEVEL_SIZE];
    
    my_itoa(_stageLevel, level);
    strcat_s(stageName, MAX_NAME_SIZE, level);
    strcat_s(stageName, MAX_NAME_SIZE, EXT);

    char* buf = getFile(stageName);
    std::stringstream ss(buf);
    char line[MAX_BUFFER_SIZE];

    ss.getline(line, MAX_BUFFER_SIZE);
    if (strcmp(line, "#begin") == 0)
    {
         ss.getline(line, MAX_BUFFER_SIZE);
         while (strcmp(line, "#end") != 0)
         {
             if (!makeEnemyTypes(line))
                 return false;
             ss.getline(line, MAX_BUFFER_SIZE);
         }
    }
    else
    {
        std::cerr << stageName << " file format incorrect!\n";
        return false;
    }

    int row = 0;
    while (ss.getline(line, MAX_BUFFER_SIZE))
    {
        if (!setStage(line, row++))
            return false;
    }

    free(buf);
    return true;
}
void StageInfo::increaseStageLevel()
{
    curStageClear();
    _stageLevel++;
}

// level
bool StageInfo::getStagesLevel()
{
    char stages[MAX_NAME_SIZE]{ "stages" };
    strcat_s(stages, MAX_NAME_SIZE, EXT);

    char* buf = getFile(stages);
    std::stringstream ss(buf);
    char line[MAX_BUFFER_SIZE];

    const char* del = " .:";
    char* tokenList[20];
    int fieldNum;
   
    while (ss.getline(line, MAX_BUFFER_SIZE))
    {
        int tokenNum = getTokenList(line, del, tokenList);
 
        if (!my_atoi(&fieldNum, tokenList[0]))
        {
            std::cerr << "stages format is incorrect!\n";
            return false;
        }

        switch (fieldNum)
        {
            case 1:
                my_atoi(&_stageMaxLevel, tokenList[2]);
                break;
        }

    }

    return true;

}
bool StageInfo::isAllClear()
{
    curStageClear();
    return (_stageLevel == _stageMaxLevel);
}

StageInfo::StageInfo(int stageLevel)
    : _stageLevel{ stageLevel }
{
    getStagesLevel();
    _enemyTypes.reserve(ENEMYTYPES_SIZE);
    _stages.reserve(MAX_ENEMY_COUNT);
}
void StageInfo::curStageClear()
{
    _enemyTypes.clear();
    _stages.clear();
}