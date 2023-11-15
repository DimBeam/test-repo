//Deterministic approach to K-Means Clustering Algorithm 

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <time.h>

//for irish dataset
#define INST 150
#define ATR 4

float dataset[INST][ATR],global_cent[INST][ATR],global_deviation=INT_MAX,limits[2][ATR],k_best[INST][ATR];

void k_means(int k,int init);
void read_data();
void find_lim();


main()
{	

	int k,i,j;
	float prev=0,derivative;
	read_data();
	
	printf("Give Number of Clusters:");
	scanf("%d",&k);
	
	
	k_means(1, j);
	prev=global_deviation;
										//Global implementation of K-Means
							//use K_means to solve the problem from 1 to K clusters *sequantially                
	//*in the sense that the best solution to n-1 clusters would be the initial state for the n-1 centers when solving for N clusters
	for (i=2;i<=k;i++)
	{
	
		//the N-th center would be placed on each data point 
		for (j=0;j<INST;j++)
		{
			k_means(i, j);
		}
		derivative=prev-global_deviation;
		printf("Clusters %d  \t Cluster Error %f \t Derivative:%f \n\n",i,global_deviation,derivative);
		prev=global_deviation;
	}
	
	


	system("pause");
	return 0; 
}


void read_data()
{
	
    
    int i,j,k;
	//open file
    FILE *myFile;
	myFile=fopen("C:/Users/...","r"); //Your path 
	
	printf("Number of Instances: %d ",INST);
	printf("\nNumber of Attributes: %d \n",ATR);

	
    		
	//save data from file to array
    for (i = 0; i<INST; i++)
    {
    	for (j=0;j<ATR;j++)
    	{
        	fscanf(myFile,"%f,",&dataset[i][j]);
    //    	printf(" %.3f ", dataset[i][j]);
    	}
    	
//		printf("\t [%d]\n",i);
    }
    
    
    
    
}

void k_means(int k,int init)
{
	int i,j,c,loops=0,change=1;
	float euclidean,d_atr,sum_d,d,this_euclidean,min_euclidean,prev_cl,clustering[INST][2],sum_atr,cl_size,this_center[k][ATR];
	double cl_error=0;

	
	//copy previous centers
	for (i=0;i<k-1;i++)
	{
		for (j=0;j<ATR;j++)
		{
			this_center[i][j]=global_cent[i][j];
		}
	}
	
	// add new center to given intial point
	for (j=0;j<ATR;j++)
	{
		this_center[k-1][j]=dataset[init][j];
	}
	
	//k-means 
	while (change!=0)
	{
		change=0;
			
		// PHASE 1 || Compute distances and assing instances to nearest center 

		//for every instance 	 
		for (i=0;i<INST;i++)
		{
			//save for point jump check
			if (loops!=0)
			{
				prev_cl=clustering[i][0];
			}
			else change=1;
			
		    //for every center	
			for (c=0;c<k;c++) 
			{
			
				sum_d=0;
				d_atr=0;
				
				//every attribute of this instance
				for (j=0;j<ATR;j++)
				{
					//calculate the distance from center		
					d_atr=this_center[c][j]-dataset[i][j];
					d_atr=pow(d_atr,2);
					sum_d=sum_d+d_atr;
				}
				
				//squared euclidean distance between this instance and this center
				this_euclidean=sum_d;
				
				
				if (c==0) 
				{
					min_euclidean=this_euclidean;
					clustering[i][0]=c;
					clustering[i][1]=min_euclidean;
				}
				//if this center is the nearest so far 
				else if (min_euclidean>this_euclidean) 
				{
						//assing this point to this center
						min_euclidean=this_euclidean;
						clustering[i][0]=c;
						clustering[i][1]=min_euclidean;
				}
					
			}
			
			//if this point jumped to another cluster change the termination variable
			if (prev_cl!=clustering[i][0]) change=1;
		}
	
		//clustering error calculation
		cl_error=0;
		for(i=0;i<INST;i++)
		{
			cl_error=cl_error+clustering[i][1];
		}
		
		
		//PHASE 2 || OPTIMAL CENTER PLACEMENT
		
		//for every cluster
		for (c=0;c<k;c++)
		{
			
			
			//for every attribute 	
			for (i=0;i<ATR;i++)
			{
				sum_atr=0;
				cl_size=0;
				//scroll down the data set for this column
				for (j=0;j<INST;j++)
				{
					//check if this instance belong to this cluster , if so add to sum_atr
					if (clustering[j][0]==c)
					{
						sum_atr=sum_atr+dataset[j][i];
						cl_size=cl_size+1;
						
					}
				}
		
				//mean of this center for this attribute
				this_center[c][i]=(sum_atr/cl_size);
			}
				
		}
		loops=loops+1;
	}
	
	
	//save centers if this is the best solution so far
	if (cl_error<global_deviation || k==1)
	{
		global_deviation=cl_error;
		for (c=0;c<k;c++)
		{
			for (j=0;j<ATR;j++)
			{
				k_best[c][j]=this_center[c][j];
			}
		}
	}
	
	//update center with the best solution so k centers
	if (init==INST-1)
	{
		for (c=0;c<k;c++)
		{
			for (j=0;j<ATR;j++)
			{
				global_cent[c][j]=k_best[c][j];
			}
		}	
	}

}




//store the max and min for every attribute  **for random center generator
void find_lim()
{
	int i,j;
	
	for (j=0;j<ATR;j++)
    	{
    		
        	limits[0][j]=dataset[0][j];
        	limits[1][j]=dataset[0][j];
        	
			for (i=0;i<INST;i++)
        	{
        		if (dataset[i][j]<limits[0][j]) limits[0][j]=dataset[i][j];
        		else if (dataset[i][j]>limits[1][j]) limits[1][j]=dataset[i][j];
			}
			
//			printf("ATR%d \t max:%f --- min:%f \n",j,limits[1][j],limits[0][j]);
    	}
}



