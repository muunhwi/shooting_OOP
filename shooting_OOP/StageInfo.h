#pragma once
#include <vector>
#include "EnemyObject.h"
#include "Stage.h"

class StageInfo
{
public:
	static StageInfo* getInstance() { return &_global; }

	const std::vector<EnemyType>& getEnemyTypes() const { return _enemyTypes; }
	const std::vector<Stage>& getStages() const { return _stages; }
	void setStageLevel(int stage) { curStageClear(); _stageLevel = stage; }
	int getMaxLevel() const { return _stageMaxLevel; }
	bool isLoadStage() const { return _stages.size() > 0; }

	void increaseStageLevel();
	bool isAllClear();
	bool loadStage();

private:
	char* getFile(const char* fileName);
	bool my_atoi(int* ret, char* str);
	void my_itoa(int val, char* buf);
	int getTokenList(char* data, const char* del, char** tokenList);
	void curStageClear();

	bool setMovementField(Movement* mp, char* fileName, char* fileDetail);
	bool setMoveData(Movement* mp, char* moveStr, char** moveList, int* index);
	bool makeMoves(EnemyType* et, char* filename);

	bool setCharField(char* field, const char* str, const char* fieldName);
	bool setIntField(int* field, char* snum, const char* fieldName);
	bool setEnemyTypeField(EnemyType* et, char* field);
	bool makeEnemyTypes(char* filename);

	bool setStage(char* line, int row);
	bool getStagesLevel();
	StageInfo(int stageLevel = 1);

private:
	static StageInfo _global;

	int _stageMaxLevel;
	int _stageLevel;
	std::vector<EnemyType> _enemyTypes;
	std::vector<Stage> _stages;
	
};
