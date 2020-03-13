#include <stdio.h>

int n, w, h;
int ans = 1<<30;

void boom(int before[15][12], int target);
void boomxy(int before[15][12], int target, int i = 0);

void boomxy(int before[15][12], int target, int i) {
	int pos[4][2] = { { 0,1 },{ 1,0 },{ -1,0 },{ 0,-1 } };
	int v = before[i][target];
	before[i][target] = 0;
	if (v != 0) {

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < v; k++)
			{
				if ((target + pos[j][0] * k < 0 ||
					target + pos[j][0] * k >= w ||
					i + pos[j][1] * k < 0 || i + pos[j][1] * k >= h)
					)
					break;
				int v2 = before[i + pos[j][1] * k][target + pos[j][0] * k];
				//before[i + pos[j][1] * k][target + pos[j][0] * k] = 0;
				if (v2 > 0)
					boomxy(before, target + pos[j][0] * k, i + pos[j][1] * k);
			}
		}

		return;
	}
	
}

void boom(int before[15][12],int target) {
	int pos[4][2] = { { 0,1},{1,0},{-1,0},{0,-1} };
	for (int i = 0; i < h; i++)
	{
		if (0 != before[i][target]) {
			boomxy(before, target, i);
			break;
		}
			
	}
}

void clean(int before[15][12]) {
	for (int i = 0; i < w; i++)
	{
		int index = h-1;
		for (int j = h-1; j >= 0; j--)
		{
			if (before[j][i] != 0) {
				before[index][i] = before[j][i];
				index--;
			}	
		}
		for (int j = index; j >= 0; j--) {
			before[j][i] = 0;
		}
	}
}

void dfs(int cont,int pos, int before[15][12]) {
	
	if (cont == 0) {
		int result = 0;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (before[i][j] != 0)
					result++;
		if (ans > result)
			ans = result;
		return;
	}

	int map[15][12];
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			map[i][j] = before[i][j];
		}
	}

	boom(map,pos);
	clean(map);
	//w¸¸Å­
	// ÆøÅº ¶³¾î Æ®¸®±â.
	for (int i = 0; i < w; i++)
	{
		dfs(cont - 1,i, map);
	}
}

int main() {

	int tc = 0;
	scanf("%d", &tc);

	for (int t = 0; t < tc; t++)
	{

		printf("#%d ", t+1);

		scanf("%d %d %d", &n, &w, &h);

		ans = 1 << 30;
		/////// w    h
		int map[15][12];
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				scanf("%d",&map[i][j]);
			}
		}

		for (int i = 0; i < w; i++)
		{
			dfs(n, i, map);
		}
		printf("%d\n", ans);

	}

	return 0;
}