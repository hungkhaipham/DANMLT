﻿#include "Header.h"


void FixConsoleWindow() {

	HWND consoleWindow = GetConsoleWindow();

	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);

	SetWindowLong(consoleWindow, GWL_STYLE, style);

}

void GotoXY(int x, int y) {

	COORD coord;

	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void DrawBoard(int pSize) {

	for (int i = 0; i <= pSize; i++) {

		for (int j = 0; j <= pSize; j++) {

			GotoXY(LEFT + 4 * i, TOP + 2 * j);

			printf(",");

		}
	}
}

void ResetData() {
	for (int i = 0; i < BOARD_SIZE; i++) {

		for (int j = 0; j < BOARD_SIZE; j++) {

			_A[i][j].x = 4 * j + LEFT + 2; // Trùng với hoành độ màn hình bàn cờ

			_A[i][j].y = 2 * i + TOP + 1; // Trùng với tung độ màn hình bàn cờ

			_A[i][j].c = 0; // 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
			//định như sau: -1 là lượt true đánh, 1 là lượt false đánh

		}

	}
	_TURN = true; _COMMAND = -1; // Gán lượt và phím mặc định
	_X = _A[0][0].x; _Y = _A[0][0].y; // Thiết lập lại tọa độ hiện hành ban đầu

}


int ProcessFinish(int pWhoWin) {

	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2); // Nhảy tới vị trí
	 // thích hợp để in chuỗi thắng/thua/hòa

	switch (pWhoWin) {

	case -1:

		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", true, false);

		break;

	case 1:

		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", false, true);

		break;
	case 0:
		printf("Nguoi choi %d da hoa nguoi choi %d\n", false, true);
		break;
	case 2:
		_TURN = !_TURN; // Đổi lượt nếu không có gì xảy ra

	}
	GotoXY(_X, _Y); // Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;

}

int AskContinue() {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	printf("Nhan 'y/n' de tiep tuc/dung: ");
	return toupper(_getch());
}


void StartGame() {

	system("cls");

	ResetData(); // Khởi tạo dữ liệu gốc

	DrawBoard(BOARD_SIZE); // Vẽ màn hình game

}

void GabageCollect()

{

	// Dọn dẹp tài nguyên nếu có khai báo con trỏ

}

//Hàm thoát game (hàm nhóm Control)

void ExitGame() {

	system("cls");

	GabageCollect();
	//Có thể lưu game trước khi exit

}

int TestBoard()
{
	return 1;
}
//int TestBoard()
//{
//	
//		if (<Ma trận đầy>) return 0; // Hòa
//	
//		else {
//			
//				if (<tồn tại điều kiện thắng theo luật caro>)
//					
//					return (_TURN == true ? -1 : 1); // -1 nghĩa là lượt ‘true’ thắng
//				Else
//			
//				return 2; // 2 nghĩa là chưa ai thắng
//			
//		}
//}

int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) _A[i][j].c = -1; // Nếu lượt hiện hành là true thì c = -1
				else _A[i][j].c = 1; // Nếu lượt hiện hành là false thì c = 1
				return _A[i][j].c;

			}

		}

	}
	return 0;
}


void MoveRight() {

	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)

	{

		_X += 4;

		GotoXY(_X, _Y);

	}

}

void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= 4;
		GotoXY(_X, _Y);

	}

}
void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += 2;
		GotoXY(_X, _Y);
	}
}

void MoveUp() {
	 if (_Y > _A[0][0].y) {
		 _Y -= 2;
		 GotoXY(_X, _Y);
		
	}

}
