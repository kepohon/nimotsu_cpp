/*
	Input.cpp
	
		・エンコーディングをshift-jisに変更: 2021.3.21
*/

#include "Input.h"


Input::Input() : pressedKey(0) {}
Input::~Input() {}

// 何かキーが押されたら、入力キーを記憶する
void Input::getKey() {
	if( isHitKey() )
		pressedKey = getch();
}

int		Input::isHitKey() { return kbhit(); }
char	Input::isPressedKey() { return pressedKey; }
void	Input::clearPressedKey() { 	pressedKey = 0; }

