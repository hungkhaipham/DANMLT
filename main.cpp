﻿#include "Header.h"

int main()
{
	FixConsoleWindow();
	StartGame();
	bool validEnter = true;

	while (1)

	{

		_COMMAND = toupper(_getch());

		if (_COMMAND == 27)

		{
			ExitGame();

			return 0;

		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 13) {// Người dùng đánh dấu trên màn hình bàn cờ
				switch (CheckBoard(_X, _Y)) {

				case -1:

					printf("X"); break;

				case 1:
					printf("O"); break;
				case 0: validEnter = false; // Khi đánh vào ô đã đánh rồi

				}
				// Tiếp theo là kiểm tra và xử lý thắng/thua/hòa/tiếp tục
				if (validEnter == true) {

					switch (ProcessFinish(TestBoard())) {

					case -1: case 1: case 0:
						if (AskContinue() != 'Y') {

							ExitGame();
							return 0;

						}

						else StartGame();

					}

				}
				validEnter = true; // Mở khóa

			}

		}

	}
}