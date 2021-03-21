# makefile    (エンコードをshift-jisに変更: 2021.3.21)
#	2021.2.2
#
# $@  ターゲットのファイル名を表します
# $<  最初の必須項目のファイル名を表します
# $?  ターゲットよりも後で更新された必須の項目を、スペースで区切ったリストで表します
# $^  すべての必須項目をスペースで区切ったリストで表します
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
#CFLAGS=-finput-charset=UTF-8 -fexec-charset=CP932 -I include  # -I は、インクルードファイルのフォルダを指定

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
