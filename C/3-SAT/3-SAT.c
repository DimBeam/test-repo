#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "3-SAT.h"

int literal[var*2];
int problem [cl][3];
int false_clauses[cl];
int f_cl;

int main() {
	int i;

	
	//For each problem  
	for (i=0;i<provlimata;i++)
	{
		printf("------- PROBLEM %d STARTS ------- \n",i+1);
		//Generate Random Problem 		
		rand_prob();
		printf("\n");
		
		//Gsat		
		printf("\n --Gsat-- : \n");
		Gsat();
		
		//WalkSat
		printf("\n --Walksat-- : \n");
		WalkSat();
		printf("\n");
	}
	
return 0; 
}


//Create random Problem
void rand_prob()
{
	
	int i,j,pick,r;
	char flag;
	int time=0;
	
	
	clock_t start,sofar; 
	start=clock();
	
	//Construct Random Clauses
	//For 1 second pick random Literals
	while (time < 1.0 )
	{
		// Problem with "cl" number of Clauses
		for (i=0;i<cl;i++)
		{
		//3-Sat, so by definition 3 literals each clause	
			for (j=0;j<=2;j++)
			{
				do 
				{
					flag ='c';
					pick = rand() % 20;
					problem [i][j]=pick;
				
					/*Each Literal has a symmetrical relation with its negative in a way their sum result in 19
					 E.g 
					Negative of p0 = p19 | Negative of p1 = p18 | etc     */
					
					//Avoid Same Literal and Negative Literals in same Clause
					if (j>0)
					{
						if (pick+problem[i][j-1]==num-1 || pick+problem[i][j-2]==num-1) flag='r';
						else if (problem[i][j-1]==pick || problem[i][j-2]==pick) flag ='r';
					}	
				} while (flag=='r');
			
				//Minimum pointer first in each clause  *Just for faster [Repeated clause check].*
				if (problem[i][j]<problem[i][0])
				{
					problem[i][j]=problem[i][0];
					problem[i][0]=pick;
				}
			}
		
			//Repeated Clause Check 
			for (r=0;r<i;r++)
			{
				if (problem[i][0]==problem[r][0])
				{
					//if same clause found , repeat	clause[i]
					if (problem[i][1]==problem[r][1] && problem[i][2]==problem[r][2])
					{
						i--;
						break;
					}
					else if (problem[i][1]==problem[r][2] && problem[i][2]==problem[r][1])
					{				
						i--;
						break;
					}	

				}
			}
			
		}
	sofar=clock()-start;
	time=((double)sofar)/CLOCKS_PER_SEC;
	}
	

}

//Assing random values to literals
void rand_value()
{
	
	int time=0,s,i;
	
	clock_t start,sofar; 
	start=clock();
	
	//For 1 second 
	while (time < 1.0 )
	{
		
		//For every Variable 
		for (i=0;i<var;i++)
		{
			s=rand();
		//	Apply randomly truth value(0 or 1) and the opposite to its negative
			if (s%2==0) 
			{
				literal[i]=0;
				literal[(num-1)-i]=1;
			}
			else 
			{
				literal [i]=1;
				literal[(num-1)-i]=0;	

			}
		}

	sofar=clock()-start;
	time= ((double)sofar)/CLOCKS_PER_SEC;		
	}	
	
}



int evaluation (char hold_f)
{
	int i,cost=0;
	
		//for every clause
		for (i=0;i<cl;i++)
		{
			//if all Literals are False then Clause is False  
			if ((literal[problem[i][0]]==0) && (literal[problem[i][1]]==0) && (literal[problem[i][2]]==0)) 
			{
				//store false clauses in array ,if necessary
				if (hold_f=='y') false_clauses[cost]=i;
				
				//increase cost
				cost++;	
			}
				
		}
	
	if (hold_f=='y' && cost!=0) select_f_cl(cost) ;
	
	return cost;
}


void flip (int q)
{
	//Change Value to given variable and its negative
	if (literal[q]==0)
		{
			literal[q]=1;
			literal[(num-1)-q]=0;
		}
		else 
		{
			literal[q]=0;
			literal[(num-1)-q]=1;
		}
	
}



//Search for Solution with Gsat
void Gsat()
{
	int i,point_cost,j,q;
	int cost[var],min_cost,pick,prev_flip;
	char flag='r';
	
	//Start with random states for MaxTries
	for (i=0;i<maxTries;i++)
	{
		prev_flip=-1;
		//Assing Random Values And Evaluate the Cost of the Initial State
		rand_value();
		point_cost=evaluation('n');
		printf("\n \t ||TRY %d || \n",i+1);
	
		//Check if Initial State cost=0 
		if 	(point_cost==0) 
		{
			printf("Solution Found!");
			return ; 
		}
	
		//Limit Flips for Current state 
		for (j=0;j<maxFlips;j++)
		{	
			min_cost=50;
			
			//Evaluate neighbors cost
			for (q=0;q<var;q++)
			{
				//flip and evaluate
 				flip (q);
				cost[q]=evaluation('n');
				
				if (cost[q]==0) 
				{
					printf("SOLUTION FOUND !!!! COST=%d \n",cost[q]);
					return;
				}
			
			//Save Best Flip	
			//prevent backwards movement	
				 if  (min_cost>cost[q] && q!=prev_flip)
				{
					min_cost=cost[q];
				}
				
				//reverse 
				flip (q);	
			}
			
			//If all neighbors lead to descent , then break and start again with random values
			if (min_cost>point_cost)
			{
				break;
			}
			else
			{
				point_cost=min_cost;
			
				//Else chose randomly to flip one of the best choices 
				do
				{
					
					pick=rand() % var;
			
					if (cost[pick]==min_cost && pick!=prev_flip)
					{
						flip(pick);
						prev_flip=pick;
						break;
					}
				
				}while (flag=='r');
			
			
			}
		
		}
		
	}

	printf("Gsat FAILED TO FIND SOLUTION | Cost %d \n",cost[pick]);
}


void WalkSat()
{
	int i,j,q,current_cost,min_cost,ch,selection;
	int this_eva,best_lit,len,l_pick;
	int flip_cost[3],lit_spot[3];
	
	double range = 100-(100*(1-probability));
	
	
	//Start with random states for MaxTries
	for (i=0;i<maxTries;i++)
	{
		//Assing Random Values And Evaluate the Cost of the Initial State
		rand_value();
		
		//evaluate current cost
		current_cost=evaluation('n');
		
		printf("\n \t ||TRY %d || \n",i+1);
	
		//Check if Initial State cost=0 
		if 	(current_cost==0) 
		{
			printf("\t \t SOLUTION FOUND !!! || Cost %d \n",current_cost);
			return ; 
		}
		
		//for max flips
		for (j=0;j<maxFlips;j++)
		{
			//Evalutate current cost and choose random false clause
			evaluation('y');
			
			//intialize min_cost to maximum
			min_cost=cl;

			// for every literal in the choose clause 
			for (q=0;q<=2;q++)
			{
		
				//flip and evaluate
				flip(problem[f_cl][q]);
				this_eva=evaluation('n');
				flip_cost[q]=this_eva;

				if (this_eva==0) 
				{
					printf("\t \t SOLUTION FOUND !!! Cost %d \n",this_eva);
					return;
				}
		
				//Save best choice 
				if (min_cost>this_eva)
				{
					min_cost=this_eva;
					best_lit=problem[f_cl][q];
				}
				
				//reverse
				flip(problem[f_cl][q]);
				
			}
			
			//If choices that improve the current state exist, chose randomly one the them 
			if (min_cost<current_cost)
			{
				do
				{
					l_pick=rand() % 3;
					
				}while (flip_cost[l_pick]>=current_cost);
				
				//Apply Changes
				flip(problem[f_cl][l_pick]);
				current_cost=flip_cost[l_pick];
			}
			else 
			{
				//pick a number between 0-99
				selection = rand() % 100 ;	
				
				// probabilty (1-p) to select best choice  
				//1-p *60%  | selection =  between 40-99 gives best choice to flip
				if (selection>range)
				{
					flip(problem[f_cl][best_lit]);
					current_cost=min_cost;
				}
				else 
				{
					//p=40% | selection = [ 0 - 39 ] another random choice to flip
					do 
					{
						l_pick=rand() % 3;
						
					}while (problem[f_cl][l_pick]==problem[f_cl][best_lit]);
					
					//Apply Changes
					flip(problem[f_cl][l_pick]);
					current_cost=flip_cost[l_pick];
				}
				
			}
			
		}
	}	
	

	
printf("WalkSat FAILED TO FIND SOLUTION | Cost %d \n",current_cost);
	
	
}







void select_f_cl(int cost)
{
	int pick;
	//choose randomly , one of false clauses
	pick = rand() % cost;
	f_cl=false_clauses[pick];
}
