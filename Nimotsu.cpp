#include "Nimotsu.h"

const char* defaultStageFile = "stageData.txt";

Nimotsu::Nimotsu() {
	stageFileName = new char[strlen(defaultStageFile)+1];
	strcpy( stageFileName, defaultStageFile );
}

Nimotsu::Nimotsu( char* stageDataFileName ){
	stageFileName = new char[strlen( stageDataFileName )+1];
	strcpy( stageFileName, stageDataFileName );
}

Nimotsu::~Nimotsu() {
	if( stageFileName ){
		delete [] stageFileName;
		stageFileName = 0;
	}
}

bool Nimotsu::initialize() {
	bool r;
	r = Game::initialize();
	
	getStageWidthHeight();
	createStageArray();
	createStateArray();
	
	key = 0;
	win = false;
	return r;
}

void Nimotsu::getStageWidthHeight() {
	// get stage width and height
	int x;
	int y;
	
	file->open( stageFileName );
	stageWidth = 0;
	stageHeight = 0;
	x = 0;
	y = 0;
	char c;
	while(true){
		c = file->readCh();
		if( c == -1 ) {
			stageHeight = y;
			break;
		} else if( 	c == '#' ||
					c == '.' ||
					c == 'o' ||
					c == 'O' ||
					c == 'p' ||
					c == 'P' ||
					c == ' ') {
			x++;
		} else if(	c == '\n') {
			stageWidth = x;
			x = 0;
			y++;
		} else {
		}
	}
	file->close();
	cout << "stageWidth :" << stageWidth << endl;
	cout << "stageHeight :" << stageHeight << endl;
//	int input;
//	cin >> input;
}

void Nimotsu::createStageArray() {
	// get stage width and height
	int x;
	int y;
	
	stageArray = new char[stageWidth * stageHeight];
	
	file->open( stageFileName );
//	stageWidth = 0;
//	stageHeight = 0;
	x = 0;
	y = 0;
	char c;
	while(true){
		c = file->readCh();
		if( c == -1 ) {
			stageHeight = y;
			break;
		} else if( 	c == '#' ||
					c == '.' ||
					c == 'o' ||
					c == 'O' ||
					c == 'p' ||
					c == 'P' ||
					c == ' ') {
			stageArray[ y * stageWidth + x ] = c;
			x++;
		} else if(	c == '\n') {
			stageWidth = x;
			x = 0;
			y++;
		} else {
		}
	}
	file->close();
	
	for( y=0; y<stageHeight; y++ ) {
		for( x=0; x<stageWidth; x++ ) {
			cout << stageArray[ y * stageWidth + x] ;
		}
		cout << endl;
	}
//	int i;
//	cin >> i;
}

void Nimotsu::createStateArray() {
	// create state array
	int x;
	int y;
	
	stateArray = new Object[stageWidth * stageHeight];
	
//	file->open( stageFileName );
//	stageWidth = 0;
//	stageHeight = 0;
	x = 0;
	y = 0;
	char c;
	for( int j = 0; j < stageHeight; j++ ) {
		for( int i = 0; i < stageWidth; i++ ) {
			c = stageArray[ y * stageWidth + x ];
			switch( c ) {
			case '#' : stateArray[ y * stageWidth + x] = OBJ_WALL; x++; break;
			case '.' : stateArray[ y * stageWidth + x] = OBJ_GOAL; x++; break;
			case 'o' : stateArray[ y * stageWidth + x] = OBJ_BLOCK; x++; break;
			case 'O' : stateArray[ y * stageWidth + x] = OBJ_BLOCK_ON_GOAL; x++; break;
			case 'p' : stateArray[ y * stageWidth + x] = OBJ_MAN; x++; break;
			case 'P' : stateArray[ y * stageWidth + x] = OBJ_MAN_ON_GOAL; x++; break;
			case ' ' : stateArray[ y * stageWidth + x] = OBJ_SPACE; x++; break;
			default: break;
			}
		}
	}
	
	for( y=0; y<stageHeight; y++ ) {
		for( x=0; x<stageWidth; x++ ) {
			cout << (int)stateArray[ y * stageWidth + x] ;
		}
		cout << endl;
	}
//	int input;
//	cin >> input;
}

bool Nimotsu::finalize() {
	if( stateArray ) {
		delete [] stateArray;
		stateArray = 0;
	}
	if( stageArray ) {
		delete [] stageArray;
		stageArray = 0;
	}
	return Game::finalize();
}

void Nimotsu::run() { Game::run(); }
bool Nimotsu::isGameRunning() { return Game::nowRunning; }






void Nimotsu::updateGame() {
	if( key == 0 ) return;
	// cout << "update Nimotsu" << endl;
	
	// 移動方向
	int dx = 0;
	int dy = 0;
	
	switch( key ) {
	case 'a': dx = -1; break;	// left
	case 's': dx = 1; break;	// right
	case 'w': dy = -1; break;	// up
	case 'z': dy = 1; break;	// down
	}
	key = 0;
//	setLetsDraw();
	
	// search player
	int i = -1;
	for ( i = 0; i < stageWidth*stageHeight; i++ ) {
		if( stateArray[ i ] == OBJ_MAN || stateArray[ i ] == OBJ_MAN_ON_GOAL ) {
			break;
		}
	}
	// player (x, y)
	int x = i % stageWidth;
	int y = i / stageWidth;
	
	// 移動後の座標 (tx, ty)
	int tx = x + dx;
	int ty = y + dy;
	// 座標の最大最小のチェック。 外れていれば不許可
	if( tx < 0 || ty < 0 || tx >= stageWidth || ty >= stageHeight ){
		return;
	}
	
	// 移動先が空白まがはゴールなら、人が移動
	int p = y * stageWidth + x;		// player
	int tp = ty * stageWidth + tx;	// target
	if( stateArray[ tp ] == OBJ_SPACE || stateArray[ tp ] == OBJ_GOAL ) {
		// 移動先がゴールならゴールの人に
		stateArray[ tp ] = ( stateArray[ tp ] == OBJ_GOAL )? OBJ_MAN_ON_GOAL : OBJ_MAN;
		// 移動元がゴールなら、ゴールに
		stateArray[ p ] = ( stateArray[ p ] == OBJ_MAN_ON_GOAL )? OBJ_GOAL : OBJ_SPACE;
	} else if ( stateArray[ tp ] == OBJ_BLOCK || stateArray[ tp ] == OBJ_BLOCK_ON_GOAL ) {
		// 2マス先が範囲内かチェック
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if( tx2 < 0 || ty2 < 0 || tx2 >= stageWidth || ty2 >= stageHeight ) {
			return;		// 押せない
		}
		int tp2 = ( ty + dy ) * stageWidth + ( tx + dx );	// 2マス先が範囲内かチェック
		if( stateArray[ tp2 ] == OBJ_SPACE || stateArray[ tp2 ] == OBJ_GOAL ) {
			// 順次入替
			stateArray[ tp2 ] = ( stateArray[ tp2 ] == OBJ_GOAL )? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;
			stateArray[ tp ] = ( stateArray[ tp ] == OBJ_BLOCK_ON_GOAL )? OBJ_MAN_ON_GOAL : OBJ_MAN;
			stateArray[ p ] = ( stateArray[ p ] == OBJ_MAN_ON_GOAL )? OBJ_GOAL : OBJ_SPACE;
		}
	}
}


void Nimotsu::drawGame() {
	if( isLetsDraw() ) {
		system("cls");
//		cout << "MIN_FRAME_TIME:" << MIN_FRAME_TIME << endl;
//		cout << "frameTime(sec):" << frameTime << endl;
//		cout << "MAX_FRAME_TIME:" << MAX_FRAME_TIME << endl;
		cout << "NimotsuKun" << endl;
//		Game::drawScreen = false;
		clearLetsDraw();
//		Game::letsDraw = false;

		const char font[] = { ' ', '#', '.', 'o', 'O', 'p', 'P' };
		
		for( int y = 0; y < stageHeight; y++ ){
			for( int x = 0; x < stageWidth; x++ ) {
				Object o = stateArray[ y * stageWidth + x ];
				cout << font[ o ];
			}
			cout << endl;
		}
		
		cout << "a:left s:right w:up z:down. command?" << endl;
		
//		if( isGameClear() ){
		if( win ){
			cout << "you WIN!!" << endl;
		}
	}
}

void Nimotsu::inputGame() {
	input->getKey();
	if( char pressedKey=input->isPressedKey() ) {
		if(	pressedKey == '\x1b') {
			stopRunning();
		}
		key = pressedKey;
		setLetsDraw();
		input->clearPressedKey();
	}
}


bool Nimotsu::isGameClear() {
	for ( int i = 0; i < stageWidth * stageHeight; i++ ) {
		if( stateArray[ i ] == OBJ_BLOCK ) {
			return false;
		}
	}
	win = true;
	return true;
}

bool Nimotsu::isWin() {
	return win;
}
