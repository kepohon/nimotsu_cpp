/*
	File.cpp
	
		・エンコーディングをshift-jisに変更: 2021.3.21
*/

#include "File.h"

File::File() :
	fp(0),
	endOfFile(false),
	moji(0)
{}

FILE* File::open( char* fname ) {
	fileName = new char[strlen(fname)+1];
	strcpy( fileName, fname );
	
	fp = fopen( fileName, "r" );
	if( !fp ){
		cerr << "can't open : " << fileName << endl;
		fileOpenSuccess = false;
		fileOpenError = true;
	}else{
		fileOpenSuccess = true;
		fileOpenError = false;
	}
	return fp;
}

bool File::isSuccess(){
	return fileOpenSuccess;
}

bool File::isError(){
	return fileOpenError;
}

void File::close() {
	if( fileOpenSuccess )
		fclose( fp );
}

File::~File(){
	delete [] fileName;
	fileName = 0;
}


char File::readCh(){
	moji = fgetc( fp );
	if( moji == -1 )
		endOfFile = true;
	else
		endOfFile = false;
	return moji;
}

bool File::eof() {
	return endOfFile;
}

