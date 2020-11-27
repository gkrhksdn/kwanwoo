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

//1은 벽
typedef struct pos
{
	int x, y;
}POS;

void mazeProcess()
{
	stack<POS> CurrentPosition; //현재 위치를 가지는 스택
	// 또 다른 스택이 필요한지 잘모르겠어요
	
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
			mapSize[j][i] = 1;	//전부 1로 초기화 벽으로 막기
		}
	}

	srand(time(NULL));

	while (true)
	{
		rotate = rand() % 4 + 2; // 2북 3동 4남 5서 랜덤으로 방향 설정했습니다.

		if (rotate == 2)
		{
			// 위로 올라가는 경우

			if (y == 0) // 맨윗부분인 경우 제외 // 범위에 벗어난 경우
				continue;

			// 전부다 막혀있을시 이동
			else if (mapSize[x + 1][y] == wall && mapSize[x][y + 1] == wall && mapSize[x - 1][y] == wall
				&& mapSize[x][y - 1] == wall) 
			{
				y--;
				CurrentPosition.push({ x, y });
			}
			//else if()// 이동할 경로가 없을시 뒤로 간다. 여기 들어갈 조건을 어떻게 해야할지 잘 모르겠어요
			//{
			//	
			//}
			//
		}

		//	if (rotate == 3)
		//	{
		//		// 동쪽으로 이동하는 경우
		//		if(x == SIZE_X)
		//			continue;

		//		else if (mapSize[x + 1][y] == 1 && mapSize[x-1][y] == 1 && mapSize[x][y+1] == 1 
		//			&& mapSize[x][y-1] == 1)
		//		{
		//			x++;
		//			CurrentPosition.push({ x,y });
		//		}
		//		else /*인접한 곳에 이동할 곳이 없다면, 이전 위치로 돌아감*/
		//		{
		//			x--;
		//			CurrentPosition.pop();
		//		}

		//		
		//	}

		//	if (rotate == 4)
		//	{
		//		// 남쪽 이동
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
		//		// 서쪽 이동
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
				cout << "■";
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