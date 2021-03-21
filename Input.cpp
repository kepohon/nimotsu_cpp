/*
	Input.cpp
	
		�E�G���R�[�f�B���O��shift-jis�ɕύX: 2021.3.21
*/

#include "Input.h"


Input::Input() : pressedKey(0) {}
Input::~Input() {}

// �����L�[�������ꂽ��A���̓L�[���L������
void Input::getKey() {
	if( isHitKey() )
		pressedKey = getch();
}

int		Input::isHitKey() { return kbhit(); }
char	Input::isPressedKey() { return pressedKey; }
void	Input::clearPressedKey() { 	pressedKey = 0; }

