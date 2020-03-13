#include "stdio.h"


struct MyStruct
{
	int number;
	int flag;
};

int converter(char o)
{
	if (o >= 'A' && o <= 'Z')
		return o - 'A' + 10 ;
	if (o >= '0' && o <= '9')
		return o - '0';
}

int  main()
{
	int t = 0;
	scanf("%d", &t);

	for (int tc = 0; tc < t; tc++)
	{

		printf("#%d ", tc + 1);
		int n, k; //(8 ≤ N ≤ 28) 
		scanf("%d %d", &n, &k);

		char numberstring[29];
		scanf("%s", numberstring);
		
		MyStruct convertlist[29 * 4 + 1] = { 0 };
		int length = 0;
		for (int i = 0; i < n; i++)
		{ // N번째에서 시작!
			for (int j = 0; j < n; j+= (n / 4))
			{
				int outputnubmer = 0;
				int state = 1;
				for (int l = 0; l < n/4; l++)
				{
					outputnubmer *= 16;
					outputnubmer +=
						converter(numberstring[(i + j + l) % n]);
				}
				convertlist[length].number = outputnubmer;
				length++;
				bool find = false;
				for (int l = 0; l < length-1; l++)
				{
					if (convertlist[l].number == convertlist[length-1].number) {
						find = true;
						length--; break;
					}
				}
				if (find == false)
				{
					for (int l = 0; l < length; l++)
					{
						if (convertlist[l].number < convertlist[length-1].number)
							convertlist[length-1].flag++;
						if (convertlist[l].number > convertlist[length-1].number)
							convertlist[l].flag++;
					}
				}
			}
		}

		for (int i = 0; i < length; i++)
		{
			if (convertlist[i].flag == length-k)
			{
				printf("%d\n", convertlist[i].number);
				break;
			}
		}

	}

	return 0;
}