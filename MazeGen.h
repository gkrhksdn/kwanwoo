#pragma once
#include "header.h"
#include "Maze.h"
class MazeGen
{
private:
	std::stack<CMazeBlock> m_Invite;// ������� // ó�� �����ϴ� ��ġ���� �̰��� �־ �湮�ϴ� ���� �̰��� ������
	std::deque<CMazeBlock> m_NotInvite;// ������� // // ó���� ���� ���� ������ ����

	bool InsertInvite(const CMazeBlock& block);
	bool DeleteInvite(const CMazeBlock& block);
	bool InsertNotInvite(const CMazeBlock& block);
	bool MakeEmpty(const CMazeBlock& block);
	
public:
	MazeGen() {};
	MazeGen(CMaze& _maze);
	void Gen(CMaze& _maze);
	void Print(const CMaze& maze);

	bool InsertInvite(const int Width, const int Height);
	bool DeleteInvite(const int Width, const int Height);
	bool InsertNotInvite(const int Width, const int Height);
	bool DeleteNotInvite(const int Width, const int Height, CMaze& _maze);
	bool MakeEmpty(const int Width, const int Height);

	void SetStartPoint(const int Width, const int Height);
	void SetEndPoint(const int Width, const int Height, CMaze& _maze);

	CMazeBlock CurrentPoint;
	CMazeBlock EndPoint;
};


