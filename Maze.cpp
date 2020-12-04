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
				{
					if (j == 0 && i == 1)
					{
						m_Board[j][i].SetX(j);
						m_Board[j][i].SetY(i);
						m_Board[j][i].SetStatus(eMazeBlockStatus::START);
					}
					else if (j == (m_sizeWidth-1) && i == (m_sizeHeight - 2))
					{
						m_Board[j][i].SetX(j);
						m_Board[j][i].SetY(i);
						m_Board[j][i].SetStatus(eMazeBlockStatus::END);
					}
					else
					{
						m_Board[j][i].SetX(j);
						m_Board[j][i].SetY(i);
						m_Board[j][i].SetStatus(eMazeBlockStatus::WALL);
					}	
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

CMazeBlock CMaze::GetBoard(int Width, int Height)
{
	return m_Board[Width][Height];
}

void CMaze::SetBoardStatus(int Width, int Height, eMazeBlockStatus Status)
{
	m_Board[Width][Height].SetStatus(Status);
}




