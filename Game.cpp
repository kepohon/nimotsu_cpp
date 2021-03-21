#include "Game.h"


Game::Game() :	nowRunning(true),
				drawScreen(true),
				letsDraw(true) {
	input = new Input();
	file = new File();
}


Game::~Game() {
	delete file;
	delete input;
}


bool	Game::initialize() {
    // attempt to set up high resolution timer
    if(QueryPerformanceFrequency(&timerFreq) == false){
        cout << "qpc error" << endl;  /* error */
		return false;
	}
    QueryPerformanceCounter( &timeStart );        // get starting time
	return true;
}



bool	Game::finalize() { return true; }



bool	Game::isGameRunning()	{ return nowRunning; }
bool	Game::isLetsDraw()		{ return letsDraw; }
void	Game::clearLetsDraw()	{ letsDraw = false; }
void	Game::setLetsDraw()		{ letsDraw = true; }
void	Game::stopRunning()		{ nowRunning = false; }



void	Game::run() {
	
	// ここでFPS時間の計算が必要
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / (float)timerFreq.QuadPart;
    // Power saving code, requires winmm.lib
    // if not enough time has elapsed for desired frame rate
    if (frameTime < MIN_FRAME_TIME) {
		/*
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime)*1000);
        timeBeginPeriod(1);         // Request 1mS resolution for windows timer
        Sleep(sleepTime);           // release cpu for sleepTime
        timeEndPeriod(1);           // End 1mS timer resolution
		*/
        return;
    }
    if (frameTime > 0.0) {
        fps = (fps*0.99f) + (0.01f/frameTime);  // average fps
	}
    if (frameTime > MAX_FRAME_TIME) { // if frame rate is very slow
        frameTime = MAX_FRAME_TIME; // limit maximum frameTime
	}
    timeStart = timeEnd;
	
	drawGame();
	inputGame();
	updateGame();
}

/*
Game::inputGame(){
	input->getKey();
	if( char c=input->isPressedKey() ) {
		if(	c == '\x1b') {
			nowRunning = false;
		}
		drawScreen = true;
		letsDraw = true;
		input->clearPressedKey();
	}
}
*/

/*
void Game::update()
{
	// cout << "update Game" << endl;
}
*/

/*
void Game::draw()
{
	if( letsDraw ){
		system("cls");
		cout << "MIN_FRAME_TIME:" << MIN_FRAME_TIME << endl;
		cout << "frameTime(sec):" << frameTime << endl;
		cout << "MAX_FRAME_TIME:" << MAX_FRAME_TIME << endl;
		cout << "draw Game" << endl;
		drawScreen = false;
		letsDraw = false;
	}
}
*/



