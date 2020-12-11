#include "MazeGen.h"

MazeGen::MazeGen(CMaze & _maze)
{
}

void MazeGen::Gen(CMaze & _maze)
{
	// 열린 목록 전부 비울것
	// 닫힌 목록은 비어있으며 열린목록은 아직 안가본 모든곳들이 다 차있다.
	srand(time(NULL));

	int dir = 0;
	int PosX = 0;
	int PosY = 1;
	int Key = 0;

	CurrentPoint = _maze.GetBoard(PosX, PosY);

	// 1. 미로 초기화
	_maze.Init();

	SetStartPoint(PosX, PosY); // 시작점 설정
	SetEndPoint(SIZE_X, SIZE_Y - 2);

	// 2. 열린 목록에 갈 수 있는 모든 길을 넣는다.
	for (int i = 1; i < SIZE_Y-1; ++i)
	{
		for (int j = 1; j < SIZE_X-1; ++j)
		{
			InsertNotInvite(_maze.GetBoard(j, i), Key);
		}
	}

	PosX = 1;
	
	int count = 0;

	while (true)
	{
		dir = rand() % 4 + 1;
		count++;

		//임시
		if (count > 500000)
			break;

		// 탈출조건
		if (MakeEmpty(CurrentPoint))
			break;

		if (dir == 1) // 북
		{

			if (PosY -2 <= 0) // 맨 위인 경우
				continue;

			else if (_maze.GetBoard(PosX,PosY-1).GetStatus() != _maze.GetBoard(PosX,PosY-2).GetStatus()) 
			{
				
				InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.
				
				DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거
				
				PosY--;

				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

				InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

				DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거

				PosY--;

				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
			}

			else // 갈 수 없을때는 4방향 다 검사 해야한다. 
			{
				// 동, 남, 서 만 검사
				
				if (_maze.GetBoard(PosX + 1, PosY).GetStatus() != _maze.GetBoard(PosX + 2, PosY).GetStatus())
				{
					if (PosX + 2 >= SIZE_X)
						continue;
					
					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY)); // 현재위치를 닫힌 목록에 넣는다.
						DeleteNotInvite(PosX, PosY, _maze);
						PosX++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));
						DeleteNotInvite(PosX, PosY, _maze);
						PosX++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
		
				}

				else if (_maze.GetBoard(PosX, PosY + 1).GetStatus() != _maze.GetBoard(PosX, PosY + 2).GetStatus())
				{
					if (PosY + 2 >= SIZE_Y)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosY++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosY++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}

				else if (_maze.GetBoard(PosX - 1, PosY).GetStatus() != _maze.GetBoard(PosX - 2, PosY).GetStatus())
				{
					if (PosX - 2 <= 0)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosX--;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosX--;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}
 
 				else
 				{
 					DeleteInvite(_maze.GetBoard(PosX, PosY));
 
 					PosY++;
 				}
 			
 			}
 		}
 			
 		
		if (dir == 2) // 동
		{
			if (PosX +2 >= SIZE_X)
				continue;

			else if (_maze.GetBoard(PosX + 1, PosY).GetStatus() != _maze.GetBoard(PosX + 2, PosY).GetStatus())
			{
				InsertInvite(_maze.GetBoard(PosX, PosY)); // 현재위치를 닫힌 목록에 넣는다.
				DeleteNotInvite(PosX, PosY, _maze);
				PosX++;
				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

				InsertInvite(_maze.GetBoard(PosX, PosY));
				DeleteNotInvite(PosX, PosY, _maze);
				PosX++;
				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
			}

			else
			{
				if (_maze.GetBoard(PosX, PosY + 1).GetStatus() != _maze.GetBoard(PosX, PosY + 2).GetStatus())
				{
					if (PosY + 2 >= SIZE_Y)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosY++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosY++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}
				
				else if (_maze.GetBoard(PosX - 1, PosY).GetStatus() != _maze.GetBoard(PosX - 2, PosY).GetStatus())
				{
					if (PosX - 2 <= 0)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosX--;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosX--;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
					
				}

				else if (_maze.GetBoard(PosX, PosY - 1).GetStatus() != _maze.GetBoard(PosX, PosY - 2).GetStatus())
				{
					if (PosY - 2 <= 0)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

						DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거

						PosY--;

						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

						DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거

						PosY--;

						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}

				else
				{
					DeleteInvite(_maze.GetBoard(PosX, PosY));

					PosX--;
				}
			}
		}

		if (dir == 3) // 남
		{
			if (PosY + 2 >= SIZE_Y)
				continue;

			else if (_maze.GetBoard(PosX, PosY + 1).GetStatus() != _maze.GetBoard(PosX, PosY + 2).GetStatus())
			{
				InsertInvite(_maze.GetBoard(PosX, PosY));

				DeleteNotInvite(PosX, PosY, _maze);

				PosY++;
				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

				InsertInvite(_maze.GetBoard(PosX, PosY));

				DeleteNotInvite(PosX, PosY, _maze);

				PosY++;
				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
			}

			else
			{
				if (_maze.GetBoard(PosX - 1, PosY).GetStatus() != _maze.GetBoard(PosX - 2, PosY).GetStatus())
				{
					if (PosX - 2 <= 0)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosX--;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosX--;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}

				else if (_maze.GetBoard(PosX, PosY - 1).GetStatus() != _maze.GetBoard(PosX, PosY - 2).GetStatus())
				{
					if (PosY - 2 <= 0)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

						DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거

						PosY--;

						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

						DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거

						PosY--;

						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
					
				}

				else if (_maze.GetBoard(PosX + 1, PosY).GetStatus() != _maze.GetBoard(PosX + 2, PosY).GetStatus())
				{
					if (PosX + 2 >= SIZE_X)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY)); // 현재위치를 닫힌 목록에 넣는다.
						DeleteNotInvite(PosX, PosY, _maze);
						PosX++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));
						DeleteNotInvite(PosX, PosY, _maze);
						PosX++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}

				else
				{
					DeleteInvite(_maze.GetBoard(PosX, PosY));

					PosY--;
				}
			
			}
		}

		if (dir == 4) // 서
		{
			if (PosX - 2 <= 0)
				continue;

			else if (_maze.GetBoard(PosX - 1, PosY).GetStatus() != _maze.GetBoard(PosX - 2, PosY).GetStatus())
			{
				InsertInvite(_maze.GetBoard(PosX, PosY));

				DeleteNotInvite(PosX, PosY, _maze);

				PosX--;
				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

				InsertInvite(_maze.GetBoard(PosX, PosY));

				DeleteNotInvite(PosX, PosY, _maze);

				PosX--;
				_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
			}

			else 
			{
				if (_maze.GetBoard(PosX, PosY - 1).GetStatus() != _maze.GetBoard(PosX, PosY - 2).GetStatus())
				{
					if (PosY - 2 <= 0)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

						DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거

						PosY--;

						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY)); // 닫힌목록에 넣는다.

						DeleteNotInvite(PosX, PosY, _maze); // 열린목록에있는것을 제거

						PosY--;

						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}

				else if (_maze.GetBoard(PosX + 1, PosY).GetStatus() != _maze.GetBoard(PosX + 2, PosY).GetStatus())
				{
					if (PosX + 2 >= SIZE_X)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY)); // 현재위치를 닫힌 목록에 넣는다.
						DeleteNotInvite(PosX, PosY, _maze);
						PosX++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));
						DeleteNotInvite(PosX, PosY, _maze);
						PosX++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
				
				}

				else if (_maze.GetBoard(PosX, PosY + 1).GetStatus() != _maze.GetBoard(PosX, PosY + 2).GetStatus())
				{
					if (PosY + 2 >= SIZE_Y)
						continue;

					else
					{
						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosY++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);

						InsertInvite(_maze.GetBoard(PosX, PosY));

						DeleteNotInvite(PosX, PosY, _maze);

						PosY++;
						_maze.SetBoardStatus(PosX, PosY, eMazeBlockStatus::EMPTY);
					}
					
				}

				else
				{
					DeleteInvite(_maze.GetBoard(PosX, PosY));
					PosX++;
				}
		
			}
		}
	}
	/*for (int i = 0; i < SIZE_Y; i++)
	{
		for (int j = 0; j < SIZE_X; j++)
		{
			_maze.SetBoardStatus(j, i, eMazeBlockStatus::EMPTY);
		}
	}*/

	//////////////////
	for (int i = 0; i < SIZE_Y; i++)
	{
		for (int j = 0; j < SIZE_X; j++)
		{
			if (_maze.GetBoard(j, i).GetStatus() == eMazeBlockStatus::START)
				std::cout << "★";
			else if (_maze.GetBoard(j, i).GetStatus() == eMazeBlockStatus::WALL)
				std::cout << "■";
			else if (_maze.GetBoard(j, i).GetStatus() == eMazeBlockStatus::EMPTY)
				std::cout << "□";
			else if (_maze.GetBoard(j, i).GetStatus() == eMazeBlockStatus::END)
				std::cout << "☆";
		}
		std::cout << std::endl;
	}
	system("pause");
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
		//m_NotInvite.push_back({ Width,Height, Key});
		//m_NotInvite.insert(std::make_pair<int, CMazeBlock>(Key, { Width, Height }));
		return true;
	}
	return true;
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

bool MazeGen::InsertNotInvite(const CMazeBlock & block, const int key)
{
	// 열린목록 삽입
	if (m_Invite.size() > SIZE_X - 1 * SIZE_Y - 1)
		return false;
	else
	{
		m_NotInvite.push_back(block);
		//m_NotInvite.insert(std::make_pair(key, block));
		return true;
	}
}

bool MazeGen::DeleteNotInvite(const int Width, const int Height, CMaze& _maze) //현재위치의 x와 y를받아와서
{
	// 열린 목록에있는것을 제거 
	if (m_NotInvite.empty())
		return false;
	
	else
	{
		std::deque<CMazeBlock>::iterator iter = m_NotInvite.begin();

		//std::find(m_NotInvite.begin(), m_NotInvite.end(), _maze.GetBoard(Width, Height))
		for (iter = m_NotInvite.begin(); iter != m_NotInvite.end(); iter++)
		{
			if (iter->GetX() == _maze.GetBoard(Width, Height).GetX() && iter->GetY() == _maze.GetBoard(Width, Height).GetY())
			{
				m_NotInvite.erase(iter);
				return true;
			}
		}
		return false;
		
	}
}

bool MazeGen::MakeEmpty(const int Width, const int Height)
{
	if (m_NotInvite.size() == 0)
		return true;
	else
		return false;
}

bool MazeGen::MakeEmpty(const CMazeBlock & block)
{
	if (m_NotInvite.size() == 0)
		return true;
	else
		return false;
}

void MazeGen::SetStartPoint(const int Width, const int Height)
{
	CurrentPoint.SetX(Width);
	CurrentPoint.SetY(Height);
	CurrentPoint.SetStatus(eMazeBlockStatus::START);

	m_Invite.push(CurrentPoint);
	int StartPointNext = CurrentPoint.GetX();
	StartPointNext += 1;
	CurrentPoint.SetX(StartPointNext);
	CurrentPoint.SetStatus(eMazeBlockStatus::EMPTY);
	m_Invite.push(CurrentPoint);
	
}

void MazeGen::SetEndPoint(const int Width, const int Height)
{
	//EndPoint = _maze.GetBoard(Width, Height);
	EndPoint.SetX(Width);
	EndPoint.SetY(Height);
	EndPoint.SetStatus(eMazeBlockStatus::END);
}
