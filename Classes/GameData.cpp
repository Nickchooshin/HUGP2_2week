#include "GameData.h"
#include "cocos2d.h"

USING_NS_CC;

void GameData::saveData()
{
	std::string filePath = FileUtils::sharedFileUtils()->getWritablePath();
	filePath.append("Data.dat");

	FILE *data;
	data = fopen(filePath.c_str(), "w");

	fprintf(data, "%d", isStageOpen);

	fclose(data);
}

void GameData::loadData()
{
	std::string filePath = FileUtils::sharedFileUtils()->getWritablePath();
	filePath.append("Data.dat");

	FILE *data;
	data = fopen(filePath.c_str(), "r");
	if (data == NULL)
	{
		data = fopen(filePath.c_str(), "w");
		fprintf(data, "0");
		fclose(data);
		data = fopen(filePath.c_str(), "r");
	}

	fscanf(data, "%d", &isStageOpen);

	fclose(data);
}