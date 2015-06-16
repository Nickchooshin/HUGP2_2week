#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include "Singleton.h"

class GameData : public Singleton < GameData >
{
public :
	int isStageOpen;
	int PersonType;

public :
	void saveData();
	void loadData();
};

#endif