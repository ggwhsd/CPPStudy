#include <stdio.h>
#include <stdlib.h>

int maze[7][7] = {
{2,2,2,2,2,2,2},
{2,0,0,0,0,0,2},
{2,0,2,0,0,0,2},
{2,0,0,2,0,2,2},
{2,2,0,2,0,2,2},
{2,0,0,0,0,0,2},
{2,2,2,2,2,2,2}
};
int startI=1, startJ=1;
int endI=5, endJ=5;
int visit(int i, int j)
{
	int m,n;
	maze[i][j]=1;
	if(i==endI && j==endJ)
	{
		printf("display path \n");
		for(m=0;m<7;m++)
		{
			for(n=0;n<7;n++)
			{
				if(maze[m][n]==2)
					printf("X");
				else if(maze[m][n]==1)
					printf("O");
				else
					printf(" ");
			}
			printf("\n");
		}
	
	}
	if(maze[i][j+1]==0) visit(i,j+1);
	if(maze[i+1][j]==0) visit(i+1,j);
	if(maze[i][j-1]==0) visit(i,j-1);
	if(maze[i-1][j]==0) visit(i-1,j);

	maze[i][j]=0;
	

}



int main(void)
{
	int i,j;
	printf("maze is :\n");
	for(i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			if(maze[i][j]==2)
				printf("X");
			else
				printf(" ");
			if(j==6)
				printf("\n");
		}
	}
	visit(startI,startJ)
;
	return 0;
}
