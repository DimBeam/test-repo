//Solving knapsack problem with different methods (Brute - Force , Top-down , bottom-up , Greedy)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 


#define nn 3 /* number of items */
#define WW 50 /* total weight */

/* declare a global array for the dynamic programming approaches */
int k[1000 + 1][WW + 1];

/* brute-force implementation for the knapsack problem */
int knapsack_bruteforce(int W, int w[], int v[], int n) {
	/* if total weight is zero, then no items can be
	   included so 0, or no item is available then 
	   also return 0 */
	if (W <= 0 || n <= 0)
		return 0;
	/* if the weight of the nth item is greater than 
	   the total weight available, then we do not include
	   the nth item and we recurse over the n - 1 subproblems */
	if (w[n - 1] > W)
		return knapsack_bruteforce(W, w, v, n - 1);
	else /* else we will consider two cases and take the maximum
		values of these cases: (i) do not include the nth item, 
		(ii) include the nth item */
		return max(knapsack_bruteforce(W, w, v, n - 1), v[n - 1] + knapsack_bruteforce(W - w[n - 1], w, v, n - 1));
}

/* top-down implementation for the knapsack problem */
int knapsack_topdown(int W, int w[], int v[], int n) {
	/* if total weight is zero, then no items can be
	included so 0, or no item is available then
	also return 0 */
	if (W <= 0 || n <= 0)
		return 0;
	/* check if we have already solved this subproblem */
	if (k[n][W] != -1)
		return k[n][W];
	/* if the weight of the nth item is greater than
	the total weight available, then we do not include
	the nth item and we recurse over the n - 1 subproblems */
	if (w[n - 1] > W)
		return k[n][W] = knapsack_topdown(W, w, v, n - 1); // total weight in this iteration is less
												 // than the weight of the ith item so excluding it
	else /* else we will consider two cases and take the maximum
		values of these cases: (i) do not include the nth item, 
		(ii) include the nth item */
		return k[n][W] = max(knapsack_topdown(W, w, v, n - 1), v[n - 1] + knapsack_topdown(W - w[n - 1], w, v, n - 1));
}

/* bottom-up implementation for the knapsack problem */
int knapsack_bottomup(int W, int w[], int v[], int n) {
	int i, j; // ith item and jth weight
	/* as k is a 2-D matrix so just iterate like that for each item */
	for (i = 0; i <= n; i++) {
		/* and for each item take each weight */
		for (j = 0; j <= W; j++) {
			/* base case */
			if (i == 0 || j == 0)
				k[i][j] = 0;
			/* total weight in this iteration is less than the weight of the ith item */
			else if (j < w[i - 1])
				k[i][j] = k[i - 1][j]; /* not including the ith item */
			else
				k[i][j] = max(k[i - 1][j], v[i - 1] + k[i - 1][j - w[i - 1]]); /* maximum over not including or including with maximum over i - 1 items */
		}
	}
	return k[n][W];
}

int max ( int q1, int q2)
{
	if (q1>q2) return q1;
	else return q2;
}

int Greedy1_maxValue(int W, int w[], int v[], int n)
{
	int max,i,j,exch,s_value=0,s_weight=0;
	for (i=0;i<n-1;i++)
	{ 
		max=v[i];
		for (j=i+1;j<n;j++)
		{		
			if (max<v[j])
			{
			max = v[j];
			exch = w[j];
			
			v[j]=v[i];
			w[j]=w[i];

			v[i]=max;
			w[i]=exch;
			
			}
		}
	}
	/*for (i=0;i<n;i++)
	{
		printf(" V[%d] = %d \t W[%d]= %d \n",i,v[i],i,w[i]);
		
	}
	*/
	for (i=0;i<n;i++)
	{
		if (s_weight+w[i]<=W)
		{
			s_value+=v[i];
			s_weight+=w[i];
		}
	}
	return s_value;
}

int Greedy2_minWeight(int W, int w[], int v[], int n)
{
		int min,i,j,exch,s_value=0,s_weight=0;
	
	for (i=0;i<n-1;i++)
	{ 
		min=w[i];
		for (j=i+1;j<n;j++)
		{		
			if (min>w[j])
			{
			min = w[j];
			exch = v[j];
			
			v[j]=v[i];
			w[j]=w[i];

			w[i]=min;
			v[i]=exch;
			
			}
		}
	}
	/*for (i=0;i<n;i++)
	{
		printf(" V[%d] = %d \t W[%d]= %d \n",i,v[i],i,w[i]);
		
	}
	*/
	for (i=0;i<n;i++)
	{
		if (s_weight+w[i]<=W)
		{
			s_value+=v[i];
			s_weight+=w[i];
		}else return s_value;
	}
	return s_value;
}

int Greedy3_VfW (int W, int w[], int v[], int n)
{
	int i,j,exch,s_weight=0,s_value=0,exch2;
	double arr_VfW[n],max;
	
	for (i=0;i<n;i++)
	{
	arr_VfW[i]=(double)v[i]/(double)w[i];
	}
	
	for (i=0;i<n-1;i++)
	{
	
		max=arr_VfW[i];
		for(j=i+1;j<=n-1;j++)
		{
			if (max<arr_VfW[j])
			{
			 	max=arr_VfW[j];
			 	arr_VfW[j]=arr_VfW[i];
			 	arr_VfW[i]=max;
			 	
			 	exch=w[j];
			 	w[j]=w[i];
			 	w[i]=exch;
			 	
			 	exch2=v[j];
			 	v[j]=v[i];
			 	v[i]=exch2;
			}
		}
	}
	/*	for (i=0;i<n;i++)
	{
		printf(" V[%d] = %d \t W[%d]= %d \t arr_VfW[%d]= %lf \n",i,v[i],i,w[i],i,arr_VfW[i]);
		
	}
	*/
	for (i=0;i<n;i++)
	{
		if (s_weight+w[i]<=W)
		{
			s_value+=v[i];
			s_weight+=w[i];
		}
	}
	return s_value;
} 

int main() {
	//int v[] = { 60, 100, 120 };
	//int w[] = { 10, 20, 30 };
	int w[1000],v[1000];
	int g1,g2,g3,i,j,d;
	long Ticks_S,Ticks_F,Ticks_P;
	long Ticks_S1,Ticks_S2,Ticks_S3,Ticks_S4,Ticks_S5;
	long Ticks_F1,Ticks_F2,Ticks_F3,Ticks_F4,Ticks_F5;
	long Ticks_P1,Ticks_P2,Ticks_P3,Ticks_P4,Ticks_P5;
	double Time;
	memset(w, 0, sizeof(w[0]) * (d + 1 ) );
	memset(v, 0, sizeof(v[0]) * (d + 1) );

	for (d=5;d<=1000;d=d+5)
	{
		Time=0.0;
		Ticks_P=0.0;
		Ticks_P1=0.0;
		Ticks_P2=0.0;
		Ticks_P3=0.0;
		Ticks_P4=0.0;
		Ticks_P5=0.0;
		for (i=0;i<5;i++)
		{
		    for (j=0;j<d;j++)
		    {   
				v[j]=rand()% (100 - 0 + 1)+1 ;
				w[j]=rand() % (100 - 0 + 1)+1; 
			//	printf("V[%d]= %d \t W[%d]= %d\n",j,v[j],j,w[j]);
			}
			Ticks_S = clock();
			printf("Using brute-force approach: %d \n", knapsack_bruteforce(WW, w, v, d));
			Ticks_F = clock();
			Ticks_P += Ticks_F - Ticks_S ;
			
			
			memset(k, -1, sizeof(k[0][0]) * (d + 1) * (WW + 1));
			Ticks_S1 = clock();
			printf("Using top-down approach: %d\n", knapsack_topdown(WW, w, v, d));
			Ticks_F1 = clock();
			Ticks_P1 += Ticks_F1 - Ticks_S1 ;
	
			
			memset(k, 0, sizeof(k[0][0]) * (d + 1) * (WW + 1));
			Ticks_S2 = clock();
			printf("Using bottom-up approach: %d\n", knapsack_bottomup(WW, w, v, d));
			Ticks_F2 = clock();
			Ticks_P2 =Ticks_P2 +( Ticks_F2 - Ticks_S2 );
						
			Ticks_S3 = clock();
			g1=Greedy1_maxValue(WW,w,v,d);
			Ticks_F3 = clock();
			printf("Using Greedy Algorithm sorted by maximum Value: %d \n",g1);
			Ticks_P3 += Ticks_F3 - Ticks_S3 ;	
			
			Ticks_S4 = clock();
			g2=Greedy2_minWeight(WW,w,v,d);
			Ticks_F4 = clock();
			printf("Using Greedy Algorithm sorted by minimum Weight: %d \n",g2);
			Ticks_P4 += Ticks_F4 - Ticks_S4 ;
						
			Ticks_S5 = clock();
			g3=Greedy3_VfW(WW,w,v,d);
			Ticks_F5 = clock();
			printf("Using Greedy Algorithm sorted by maximum [Value per Weight]: %d \n \n",g3);
			Ticks_P5 += Ticks_F5 - Ticks_S5 ;
			
			if (i==4)
			{
			 	Time = (double)(Ticks_P/CLOCKS_PER_SEC)/5.0;
				printf("\t *Average Execution Time of Brute Force With Array Length %d : %lfsec \n",d,Time);
				
				Time = (double)(Ticks_P1/CLOCKS_PER_SEC)/5.0;
			    printf("\t *Average Execution Time of Top Down Approach With Array Length %d : %lfsec \n",d,Time);
			    
				Time = (double)(Ticks_P2/CLOCKS_PER_SEC)/5.0;
			    printf("\t *Average Execution Time of Bottom Up Aprroach With Array Length %d : %lfsec \n",d,Time);
			    
				Time = (double)(Ticks_P3/CLOCKS_PER_SEC)/5.0;
			    printf("\t *Average Execution Time of Greedy sorted by maximum Value With Array Length %d : %lfsec \n",d,Time);
			    
				Time = (double)(Ticks_P4/CLOCKS_PER_SEC)/5.0;
			    printf("\t *Average Execution Time of Greedy sorted by manimum Weight With Array Length %d : %lfsec \n",d,Time);
			    
			    Time = (double)(Ticks_P5/CLOCKS_PER_SEC)/5.0;
			    printf("\t *Average Execution Time of Greedy sorted by maximum Value per Weight With Array Length %d : %lfsec \n\n\n",d,Time);
			    

			}			
		}
	}
		
		system("PAUSE");
		return 0;
	
	
}
