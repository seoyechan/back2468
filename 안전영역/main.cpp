#include <stdio.h>
#include <queue>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int n, nRet;
int nfiled[101][101];
int nvisit[101][101];
int min_t, max_t;

int dirx[] = { 0, 0, 1, -1 };
int diry[] = { 1, -1, 0, 0 };

typedef struct pos{
	int x, y;
};

int simul()
{
	queue <pos> bfsq;
	pos cur = { 0, 0 };
	int nextx = 0;
	int nexty = 0;
	int safety_zone = 0;

	for (int t = min_t; t < max_t; t++)
	{
		for (int k = 0; k < n; k++)
			for (int z = 0; z < n; z++)
				nvisit[k][z] = 0;

		safety_zone = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (nfiled[i][j] > t && nvisit[i][j] == 0)
				{	
					bfsq.push({ j, i });
					nvisit[i][j] = 1;

					while (!bfsq.empty())
					{
						cur = bfsq.front();
						bfsq.pop();

						for (int k = 0; k < 4; k++)
						{
							nextx = cur.x + dirx[k];
							nexty = cur.y + diry[k];

							if (nextx >= 0 && nextx < n && nexty >= 0 && nexty < n && nvisit[nexty][nextx] == 0)
							{
								if (nfiled[nexty][nextx] > t)
								{
									nvisit[nexty][nextx] = 1;
									bfsq.push({ nextx, nexty });
								}
							}
						}
					}
					safety_zone++;
				
				}
			}
		}
		if (nRet < safety_zone)
			nRet = safety_zone;
	}
	return 0;
}



int main()
{
	scanf("%d", &n);

	min_t = 101;
	max_t = -1;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			scanf("%d", &nfiled[i][j]);
			nvisit[i][j] = 0;

			if (nfiled[i][j] < min_t)
				min_t = nfiled[i][j];
			if (nfiled[i][j] > max_t)
				max_t = nfiled[i][j];
		}
	}
	nRet = 0;
	simul();
	printf("%d\n", nRet);

	return 0;
}