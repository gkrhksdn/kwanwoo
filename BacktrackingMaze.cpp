#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>
#include <stack>
using namespace std;

#define MAX_SIZE 100
#define MAZE_SIZE 10
#define SIZE_X 11
#define SIZE_Y 11

//1�� ��
typedef struct pos
{
	int x, y;
}POS;

void mazeProcess()
{
	stack<POS> CurrentPosition; //���� ��ġ�� ������ ����
	// �� �ٸ� ������ �ʿ����� �߸𸣰ھ��
	
	int wall = 1;
	int path = 0;
	
	POS start = { 0,0 };
	POS end = { SIZE_X, SIZE_Y }; 

	int x = 0;
	int y = 0;
	int rotate;

	int mapSize[SIZE_X][SIZE_Y];

	for (int i = 0; i < SIZE_Y; i++)
	{
		for (int j = 0; j < SIZE_X; j++)
		{
			mapSize[j][i] = 1;	//���� 1�� �ʱ�ȭ ������ ����
		}
	}

	srand(time(NULL));

	while (true)
	{
		rotate = rand() % 4 + 2; // 2�� 3�� 4�� 5�� �������� ���� �����߽��ϴ�.

		if (rotate == 2)
		{
			// ���� �ö󰡴� ���

			if (y == 0) // �����κ��� ��� ���� // ������ ��� ���
				continue;

			// ���δ� ���������� �̵�
			else if (mapSize[x + 1][y] == wall && mapSize[x][y + 1] == wall && mapSize[x - 1][y] == wall
				&& mapSize[x][y - 1] == wall) 
			{
				y--;
				CurrentPosition.push({ x, y });
			}
			//else if()// �̵��� ��ΰ� ������ �ڷ� ����. ���� �� ������ ��� �ؾ����� �� �𸣰ھ��
			//{
			//	
			//}
			//
		}

		//	if (rotate == 3)
		//	{
		//		// �������� �̵��ϴ� ���
		//		if(x == SIZE_X)
		//			continue;

		//		else if (mapSize[x + 1][y] == 1 && mapSize[x-1][y] == 1 && mapSize[x][y+1] == 1 
		//			&& mapSize[x][y-1] == 1)
		//		{
		//			x++;
		//			CurrentPosition.push({ x,y });
		//		}
		//		else /*������ ���� �̵��� ���� ���ٸ�, ���� ��ġ�� ���ư�*/
		//		{
		//			x--;
		//			CurrentPosition.pop();
		//		}

		//		
		//	}

		//	if (rotate == 4)
		//	{
		//		// ���� �̵�
		//		if(y == SIZE_Y)
		//			continue;

		//		else if (mapSize[x + 1][y] == 1 && mapSize[x - 1][y] == 1 && mapSize[x][y + 1] == 1
		//			&& mapSize[x][y - 1] == 1)
		//		{
		//			y++;
		//			CurrentPosition.push({ x,y });
		//		}
		//		else
		//		{
		//		
		//		}
		//		
		//	}

		//	if (rotate == 5)
		//	{
		//		// ���� �̵�
		//		if (x == 0)
		//			continue;
		//		
		//		else if (mapSize[x + 1][y] == 1 && mapSize[x - 1][y] == 1 && mapSize[x][y + 1] == 1
		//			&& mapSize[x][y - 1] == 1)
		//		{
		//			x--;
		//			CurrentPosition.push({ x,y });
		//		}
		//		
		//		else 
		//		{
		//			x++;
		//			CurrentPosition.pop();
		//		}
		//	}
		//}
	}

	for (int i = 0; i < SIZE_Y; i++)
	{
		for (int j = 0; j < SIZE_X; j++)
		{
			if (mapSize[j][i] == 0)
				printf("  ");
			if (mapSize[j][i] == 1)
				cout << "��";
		}
		cout << endl;
	}

	//system("pause");
	
}






int main()
{
	mazeProcess();
	return 0;
}