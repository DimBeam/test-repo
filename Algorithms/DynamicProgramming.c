//Dynamic Programming implementation for finding the Length of Longest Common Sequence between two Strings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int res[100][100],opt_a,opt_b,c_len,sum;
static char *c_p;
int fun (char *X ,char *Y,int m,int n);
int main(int argc, char *argv[]) 
{
	
	int mhkos,m,n,i,j;
	char X[100],Y[100];
	printf("Dwse 2 alfarithmitika \n");
	scanf("%s %s",X,Y);
	m=strlen(X);
	n=strlen(Y);
	for (i=0;i<m;i++)
	{
		for (j=0;j<n;j++)
		{
		res[i][j]=-1;
		} 
	}
	mhkos=fun(X,Y,m,n);
	printf("Mhkos megistis koinis akolouthias =%d \n",mhkos);
	printf("vhmata= %d",sum);
	return 0;
}


int fun (char *x ,char *y,int m,int n)
{
	
	if (res[m-1][n-1]!=-1) return res[m-1][n-1];
	sum=sum+1;
	if (m==0 || n==0)
	{
		return 0;		
	}
	else if (x[m-1]!=y[n-1])
	{
		return res[m-1][n-1]= max(fun(x,y,m-1,n),fun(x,y,m,n-1));
	}	
	else 
	{
		return res[m-1][n-1]=1+fun(x,y,m-1,n-1);
	}
}

int max (int q1,int q2)
{
	if (q1>q2) return q1;
	else return q2;
}





