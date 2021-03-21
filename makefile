# makefile    (�G���R�[�h��shift-jis�ɕύX: 2021.3.21)
#	2021.2.2
#
# $@  �^�[�Q�b�g�̃t�@�C������\���܂�
# $<  �ŏ��̕K�{���ڂ̃t�@�C������\���܂�
# $?  �^�[�Q�b�g������ōX�V���ꂽ�K�{�̍��ڂ��A�X�y�[�X�ŋ�؂������X�g�ŕ\���܂�
# $^  ���ׂĂ̕K�{���ڂ��X�y�[�X�ŋ�؂������X�g�ŕ\���܂�
#
# vpath pattern directory-list
#   example =>  vpath %.c src
#

NAME=main
SRC=main.cpp Nimotsu.cpp Game.cpp Input.cpp File.cpp
OBJ=${SRC:.cpp=.o}
EXE=${NAME}.exe

CC=g++

CLFAGS=
#CFLAGS=-finput-charset=UTF-8 -fexec-charset=CP932
#CFLAGS=-finput-charset=UTF-8 -fexec-charset=CP932 -I include  # -I �́A�C���N���[�h�t�@�C���̃t�H���_���w��

LFLAGS=


all: ${NAME}.exe

${NAME}.exe: ${OBJ}
	${CC} -o $@ $^ ${LFLAGS}

.cpp.o:
	${CC} -o $@ -c $< ${CFLAGS}

Nimotsu.o: Nimotsu.h
Game.o: Game.h
Input.o: Input.h
File.o: File.h

clean:
	del *.o
#	del *.exe
