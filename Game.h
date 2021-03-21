/*
	Game.h
	
		・エンコーディングをshift-jisに変更: 2021.3.21
*/

#ifndef _GAME_H_

#define _GAME_H_

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "Input.h"
#include "File.h"

using namespace std;

class Game {

public:
	Game();
	~Game();
	bool	initialize();		// 高精度タイマーの初期化
	bool	finalize();
	
	bool	isGameRunning();
	bool	isLetsDraw();
	void	clearLetsDraw();
	void	setLetsDraw();
	void	stopRunning();
	
	void	run();
	
	void	virtual	drawGame()=0;
	void	virtual	updateGame()=0;
	void	virtual inputGame()=0;

protected:
	Input*	input;
	File*	file;
	
	bool	nowRunning;					// 
	bool	drawScreen;				//
	bool	letsDraw;
	
    LARGE_INTEGER timeStart;        // Performance Counter start value
    LARGE_INTEGER timeEnd;          // Performance Counter end value
    LARGE_INTEGER timerFreq;        // Performance Counter frequency
    float	frameTime;              // time required for last frame
    float	fps;                    // frames per second};

	const float FRAME_RATE = 240.0f;                // the target frame rate (frames/sec)
	const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
	const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
	const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

};

#endif  // GAME_H_

