#include "MazeGen.h"

MazeGen::MazeGen(CMaze & _maze)
{
}

void MazeGen::Gen(CMaze & _maze)
{
	// ���� ����� �� �����!!
	// ���� ����� ��������� ��������� ���� �Ȱ��� �������� �� ���ִ�.
	srand(time(NULL));

	int dir = 0;
	int PosX = 0;
	int PosY = 1;

	CurrentPoint = _maze.GetBoard(PosX, PosY);

	// 1. �̷� �ʱ�ȭ
	_maze.Init();

	SetStartPoint(PosX, PosY); // ������ ����

	// 2. ���� ��Ͽ� �� �� �ִ� ��� ���� �ִ´�.
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
		if (dir == 1) // ��
		{
			if (PosY <= 0) // �� ���� ���
				continue;	 
			
			else if (std::find(m_NotInvite.begin(), m_NotInvite.end(), m_Invite) != m_NotInvite.end()) // ���� ��Ͽ� �ִٸ�
			{
				InsertInvite(_maze.GetBoard(PosX, PosY)); // ������Ͽ� �ִ´�.

				//DeleteNotInvite(PosX, PosY); // ������Ͽ��ִ°��� ����
				// �����ؾ��� ����� ��ġ�� ã�ƾ��ϴµ� ��ġ�� ��ȯ�ϴ� ���� �𸣰ڽ��ϴ�.

				PosY--;
			}
			else // �ٽ� ���ƿ��� ���
			{
				DeleteInvite(_maze.GetBoard(PosX, PosY));

				InsertNotInvite(_maze.GetBoard(PosX, PosY));
				PosY++;
			}
			
		}
		
		if (dir == 2) // ��
		{
			
		}

		if (dir == 3) // ��
		{
			
		}

		if (dir == 4) // ��
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
	// ���� ��� ����
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
	// ���� ��� ����
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
	// ���� ��Ͽ� �ִ´�.
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
	// ���� ��� ����
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
	// ������� ����
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
	// ���� ��Ͽ��ִ°��� ���� 
	if (m_NotInvite.empty())
		return false;
	
	else
	{
		//std::deque<CMazeBlock>::iterator iter;
		//iter = std::find(m_NotInvite.begin(), m_NotInvite.end(), _maze.GetBoard(Width,Height));
		
		//m_NotInvite.erase(); // �̾ȿ� �� ���ڰ��� ��� ���ؾ����� �𸣰ڽ��ϴ�.
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
