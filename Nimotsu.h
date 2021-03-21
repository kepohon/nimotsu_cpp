/*
	Nimotsu.h
	
		・エンコーディングをshift-jisに変更: 2021.3.21
*/

#ifndef _NIMOTSU_H_
#define _NIMOTSU_H_

#include "Game.h"

enum Object {
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_GOAL,
	OBJ_BLOCK,
	OBJ_BLOCK_ON_GOAL,
	OBJ_MAN,
	OBJ_MAN_ON_GOAL,
	OBJ_UNKNOWN,
};


class Nimotsu : public Game {

public:
	Nimotsu();
	Nimotsu( char* stageDataFileName );
	~Nimotsu();
	bool	initialize();
	bool	finalize();
	void	run();
	bool	isGameRunning();
	
	void	updateGame();
	void	drawGame();
	void	inputGame();
	bool	isGameClear();
	bool	isWin();
	
protected:
	Game* game;
	char* stageFileName;
	char* stageArray;
	Object* stateArray;
	int stageWidth;
	int stageHeight;
	int key;
	bool win;
	
	void getStageWidthHeight();
	void createStageArray();
	void createStateArray();
};

#endif  // NIMOTSU_H_

