/*
	main.cpp
	
		・エンコーディングをshift-jisに変更: 2021.3.21
*/

#include "Nimotsu.h"

int main( int argc, char* argv[] ) {
	Nimotsu* nimotsu;
	
	if( argc < 2 ){
		nimotsu = new Nimotsu();
	}else{
		nimotsu = new Nimotsu( argv[1] );
	}
	
	if( nimotsu->initialize() ) {
		nimotsu->isGameClear();
		nimotsu->drawGame();
//		if( nimotsu->isWin() ){
//		}else{
			while( nimotsu->isGameRunning() ) {
//				if ( nimotsu->isGameClear() ) {
//					break;
//				}
				if( nimotsu->isGameClear() ) break;
				nimotsu->run();
//			}
		}
		nimotsu->drawGame();
	}
	nimotsu->finalize();
	delete nimotsu;
	
    return 0;
}
