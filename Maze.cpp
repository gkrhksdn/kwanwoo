#include "Maze.h"

bool CMaze::IsValidMazeSize()
{
	if (m_sizeHeight > SIZE_Y || m_sizeHeight < 0 ||
		m_sizeWidth > SIZE_X || m_sizeWidth < 0)
		return false;
	else
		return true;
}

void CMaze::Init()
{
	if (IsValidMazeSize())
	{
		for (int i = 0; i < m_sizeHeight; i++)
		{
			for (int j = 0; j < m_sizeWidth; j++)
			{
				if (j == 0 && i == 1)
				{
					//시작점
					m_Board[j][i].SetX(0);
					m_Board[j][i].SetY(1);
					m_Board[j][i].SetStatus(eMazeBlackStatus::START);
				}
				else if (j == m_sizeWidth - 1 && i == m_sizeHeight - 2)
				{
					// 출구
					m_Board[j][i].SetX(m_sizeWidth);
					m_Board[j][i].SetY(m_sizeHeight - 1);
					m_Board[j][i].SetStatus(eMazeBlackStatus::END);
				}
				else
				{
					m_Board[j][i].SetX(j);
					m_Board[j][i].SetY(i);
					m_Board[j][i].SetStatus(eMazeBlackStatus::WALL);	
				}

			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "error" << std::endl;
		return;
	}
	
}

CMazeBlock CMaze::GetBoard()
{
	//return m_Board[m_sizeWidth][m_sizeHeight];
}


