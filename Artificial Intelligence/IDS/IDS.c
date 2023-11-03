#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "IDS.H"

struct stack_element first_state;
struct stack_element new_node;
struct stack_element empty_node;
unsigned long long int node_counter=1;
stack_type frontier;
int GoalState[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};


int main(){	
int d,i,term=0,j,x,y;
double time=0;
initialize(&frontier);
RandomGenerator();
clock_t start,sofar; 
start=clock();
for (d=0;d>=0;d++)
{
	
	printf("\n \t START WITH LIMIT DEPTH %d \n",d);
	
	while(is_empty(&frontier)==0)
	{
		i=frontier.top;
		if (frontier.node[i].depth<d && frontier.node[i].expanded=='N')
		{
			frontier.node[i].expanded='Y';
			
			
			
			//UP MOVE
			if (frontier.node[i].space_pos[0]!=0  && frontier.node[i].move!='D' )	
			{
				
				create_child (frontier.node[i],'U');				
			
				//CHECK IF GOAL STATE	
				if (isGoal(frontier.node[frontier.top].state)==1)
				{	
					printf("\t GOAL STATE FOUND! \n");
					printf("\t PRINTING PATH \n");
					printPath(frontier.node[frontier.top]);
					term=1;
					break;
				}
			}
			
			//DOWN MOVE
			if (frontier.node[i].space_pos[0]!=3 && frontier.node[i].move!='U' )	
			{
				create_child (frontier.node[i],'D');
				
				//CHECK IF GOAL STATE	
				if (isGoal(frontier.node[frontier.top].state)==1)
				{
					printf("\t GOAL STATE FOUND! \n");
					printf("\t PRINTING PATH \n");
					printPath(frontier.node[frontier.top]);
					term=1;
					break;
				}
			}
			
			//LEFT MOVE
			if (frontier.node[i].space_pos[1]!=0 && frontier.node[i].move!='R' )	
			{
				create_child (frontier.node[i],'L');
			
				//CHECK IF GOAL STATE | IF TRUE PRINT PATH & BREAK
				if (isGoal(frontier.node[frontier.top].state)==1)
				{
					printf("\t GOAL STATE FOUND! \n");
					printf("\t PRINTING PATH \n");
					printPath(frontier.node[frontier.top]);
					term=1;
					break;
				}
			}
			
			//RIGHT MOVE
			if (frontier.node[i].space_pos[1]!=3 && frontier.node[i].move!='L' )	
			{
				create_child (frontier.node[i],'R');		
				//CHECK IF GOAL STATE | IF TRUE PRINT PATH & BREAK	
				if (isGoal(frontier.node[frontier.top].state)==1)
				{
					printf("\t GOAL STATE FOUND! \n");
					printf("\t PRINTING PATH \n");
					printPath(frontier.node[frontier.top]);
					term=1;
					break;
				}
			}			
		
			
		}
		else 
		{
			pop(&frontier,&frontier.node[i]);
		}
		
		sofar=clock()-start;	
		time= ((double)sofar)/(CLOCKS_PER_SEC*3600);
		if (time>2)
		{
			term=1;
			break;
		}
	
	}
	if (term==1) break;
	printf(" \t Solution Not found with Depth Limit %d \n",d);
	push(&frontier,first_state);
}

printf("Total nodes created: %llu \n",node_counter);
printf("Time passed: %.0f minutes",time);
return 0;
}




void RandomGenerator ()
{
	int Puzzle[4][4];
	int n=15,i,j,x,y,x1,y1,swap_block;
	double time;
	//initialize first state
	first_state.own_pointer=0; 
	first_state.father_pointer = -1;
	first_state.move = 'S';
	first_state.depth = 0;
	first_state.expanded= 'N';
		
		
	for (i=0;i<=3;i++)
	{		
		for (j=0;j<=3;j++)
			{
				Puzzle[i][j]=n;
				n=n-1;
			}	
	}
	
	time=0;
	clock_t start,sofar; 
	start=clock();

	while (time < 2.0 )
	{
		x= rand() % 4  ;
		y= rand() % 4  ;
		x1= rand() % 4  ;
		y1= rand() % 4  ;
		swap_block=Puzzle[x][y];
		Puzzle[x][y]=Puzzle[x1][y1];
		Puzzle[x1][y1]=swap_block;
		
		sofar=clock()-start;	
		time= ((double)sofar)/CLOCKS_PER_SEC;		
	}
	for (i=0;i<=3;i++)
	{
		for (j=0;j<=3;j++)
		{
			first_state.state[i][j]=Puzzle[i][j];
			if (Puzzle[i][j]==0)
			{
				first_state.space_pos[0]=i;
				first_state.space_pos[1]=j;
			}
		}
	}
	push(&frontier,first_state);
}

False=0 , True=1 */
int isGoal(int newState[][4])
{
	int i,j;
	for (i=0;i<=3;i++)
	{
		for (j=0;j<=3;j++)
		{
		   if (GoalState[i][j]!=newState[i][j])
		   {
		   		return 0;
		   }
		}
	}
return 1;
}

void create_child (struct stack_element node_father,char new_move)
{
	int i,j;
		new_node.own_pointer=frontier.top+1;
		new_node.father_pointer = node_father.own_pointer;
		new_node.move = new_move;
		new_node.depth =node_father.depth+1;
		new_node.expanded = 'N';
	
	
		for (i=0 ;i<4;i++)
		{
			for (j=0 ;j<4;j++)
			{
				new_node.state[i][j]=node_father.state[i][j];
			}
		}
		
		if (new_move =='L')
		{
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]-1;
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1]=0;
		}
		else if (new_move =='R')
		{
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]+1;
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1]=0;
		}
		else if (new_move =='D')
		{
			new_node.space_pos[0]=node_father.space_pos[0]+1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]]=0;
		}
		else if (new_move =='U')
		{
			new_node.space_pos[0]=node_father.space_pos[0]-1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]]=0;
		}
		node_counter++;
  		if (rep_state_check(new_node)==1) push(&frontier,new_node);		
}  


int rep_state_check(struct stack_element this_node)
{
	int i,x,y;
	char flag='c';
	int cycle;
	int f=this_node.father_pointer;

while (f!=-1)
{
	
	cycle=this_node.depth-frontier.node[frontier.top].depth;
	if (cycle==(12 || 30 || 56 ||90|| 132))
	{
		flag='c';  
		for (x=0;x<=3;x++)
		{
			for (y=0;y<=3;y++)
			{
				
				if (frontier.node[f].state[x][y]!=this_node.state[x][y])
				{
					flag='b';
					break ;
				}
			}
			if (flag=='b') break;
			if (x==3 && y==3) 
			{
				printf("same state found! \n");
				return 0;
			}
			
		}
	}
	f=frontier.node[f].father_pointer;
}
return 1;
}



void initialize(stack_type *stack) {
	stack->top = -1;
}


int is_empty(stack_type *stack) {
	if (stack->top !=-1) return 0;
	else return 1;
}


void push(stack_type *stack, struct stack_element item) {
		stack->top++;
		stack->node[stack->top] = item;
}


void pop(stack_type *stack, struct stack_element *item) {
	if (is_empty(stack)==0) {
		stack->node[stack->top]=empty_node;
		stack->top--;
	}
	else
		printf("----The stack is empty! Cannot delete any items!----");
}

void printPath (struct stack_element item){
	int i,j;
	printf("/t ------------ \n");
	printf("/t || \n");
	for (i=0;i<=3;i++)
	{
		for (j=0;j<=3;j++)
		{
			printf ("/t %d \n",item.state[i][j]);
		}
		printf("\n");
	}

if (item.father_pointer!=-1) printPath(frontier.node[item.father_pointer]);

}


