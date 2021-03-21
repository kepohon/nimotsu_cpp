/*
	File.h
	
		・エンコーディングをshift-jisに変更: 2021.3.21
*/

#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class File {

public:
	File();
	~File();
	FILE* open( char* fname );
	bool isSuccess();
	bool isError();
	void close();
	
	char readCh();
	bool eof();

protected:
	char moji;
	bool endOfFile;
	FILE* fp;
	char* fileName;
	bool fileOpenSuccess;
	bool fileOpenError;
};

#endif  // _FILE_H_

