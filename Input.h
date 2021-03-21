/*
	Input.h
	
		・エンコーディングをshift-jisに変更: 2021.3.21
*/

#ifndef _INPUT_H_
#define _INPUT_H_

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

class Input {

public:
	Input();
	~Input();
	int		isHitKey();
	void	getKey();
	char	isPressedKey();
	void	clearPressedKey();
	
private:
	char	pressedKey;			// getKey()内でセットされる
	
};

#endif  // INPUT_H_

