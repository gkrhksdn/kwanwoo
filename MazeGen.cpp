#include "MazeGen.h"

MazeGen::MazeGen(CMaze & _maze)
{
}

void MazeGen::Gen(CMaze & _maze)
{
	// 열린 목록을 싹 비워라!!
	// 닫힌 목록은 비어있으며 열린목록은 아직 안가본 모든곳들이 다 차있다.
	srand(time(NULL));

	int dir = 0;
	int PosX = 0;
	int PosY = 1;

	CurrentPoint = _maze.GetBoard(PosX, PosY);

	// 1. 미로 초기화
	_maze.Init();

	SetStartPoint(PosX, PosY); // 시작점 설정

	// 2. 열린 목록에 갈 수 있는 모든 길을 넣는다.
	for (int i = 1; i < SIZE_Y-1; ++i)
	{
		for (int j = 1; j < SIZE_X-1; ++j)
		{
			m_NotInvite.push_back(_maze.GetBoard(j,i));
		}
	}
	
	while (true)
	{
		dir = rand() % 4 + 1;
		//std::deque<CMazeBlock>::iterator iter;
		if (dir == 1) // 북
		{
			if (PosY <= 0) // 맨 위인 경우
				continue;	 
			
			else if (std::find(m_NotInvite.begin(), m_NotInvite.end(), m_Invite) != m_NotInvite.end()) // 열린 목록에 있다면
			{
				InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

				//DeleteNotInvite(PosX, PosY); // 열린목록에있는것을 제거
				// 제거해야할 대상의 위치를 찾아야하는데 위치를 반환하는 법을 모르겠습니다.

				PosY--;
			}
			else // 다시 돌아오는 경우
			{
				DeleteInvite(_maze.GetBoard(PosX, PosY));

				InsertNotInvite(_maze.GetBoard(PosX, PosY));
				PosY++;
			}
			
		}
		
		if (dir == 2) // 동
		{
			
		}

		if (dir == 3) // 남
		{
			
		}

		if (dir == 4) // 서
		{
			
		}
	}
}

void MazeGen::Print(const CMaze & maze)
{

}

bool MazeGen::InsertInvite(const int Width, const int Height)
{
	if (m_Invite.size() > SIZE_X - 1 * SIZE_Y - 1)
		return false;
	else
	{
		m_Invite.push({CurrentPoint});

		return true;
	}
}

bool MazeGen::DeleteInvite(const int Width, const int Height)
{
	// 닫힌 목록 제거
	if (m_Invite.empty())
		return false;
	else
	{
		m_Invite.pop();
		return true;
	}
}

bool MazeGen::InsertNotInvite(const int Width, const int Height)
{
	// 열린 목록 삽입
	if (m_NotInvite.size() > SIZE_X - 1 * SIZE_Y - 1)
		return false;
	else
	{
		m_NotInvite.push_back({ Width, Height });
		return true;
	}
}

bool MazeGen::InsertInvite(const CMazeBlock & block)
{
	// 닫힌 목록에 넣는다.
	if (m_Invite.size() > SIZE_X - 1 * SIZE_Y - 1)
		return false;

	else
	{
		m_Invite.push(block);
		return true;
	}
}

bool MazeGen::DeleteInvite(const CMazeBlock & block)
{
	// 닫힌 목록 제거
	if (m_Invite.empty())
		return false;
	else
	{
		m_Invite.pop();
		return true;
	}
}

bool MazeGen::InsertNotInvite(const CMazeBlock & block)
{
	// 열린목록 삽입
	if (m_Invite.size() > SIZE_X - 1 * SIZE_Y - 1)
		return false;
	else
	{
		m_NotInvite.push_back(block);
		return true;
	}
}

bool MazeGen::DeleteNotInvite(const int Width, const int Height, CMaze& _maze)
{
	// 열린 목록에있는것을 제거 
	if (m_NotInvite.empty())
		return false;
	
	else
	{
		//std::deque<CMazeBlock>::iterator iter;
		//iter = std::find(m_NotInvite.begin(), m_NotInvite.end(), _maze.GetBoard(Width,Height));
		
		//m_NotInvite.erase(); // 이안에 들어갈 인자값을 어떻게 구해야할지 모르겠습니다.
		return true;
	}
}

bool MazeGen::MakeEmpty(const int Width, const int Height)
{
	return true;
}

bool MazeGen::MakeEmpty(const CMazeBlock & block)
{
	return false;
}

void MazeGen::SetStartPoint(const int Width, const int Height)
{
	CurrentPoint.SetX(Width);
	CurrentPoint.SetY(Height);
	CurrentPoint.SetStatus(eMazeBlockStatus::START);
}

void MazeGen::SetEndPoint(const int Width, const int Height, CMaze& _maze)
{
	EndPoint = _maze.GetBoard(Width, Height);
	EndPoint.SetX(Width);
	EndPoint.SetY(Height);
	EndPoint.SetStatus(eMazeBlockStatus::END);
}
