#pragma once
#include "header.h"
class CMaze
{
private:
	int m_sizeWidth = SIZE_X;
	int m_sizeHeight = SIZE_Y;
	

	CMazeBlock m_Board[SIZE_X][SIZE_Y];
	

public:
	CMaze() {};
	CMaze(const int width, const int height) :
		m_sizeWidth(width), m_sizeHeight(height) {};

	virtual ~CMaze() {};

	bool IsValidMazeSize(); //사이즈가 맞는지 판단
	void Init();
	CMazeBlock GetBoard(int Width, int Height);
	void SetBoardStatus(int Width, int Height, eMazeBlockStatus Status);
	

};