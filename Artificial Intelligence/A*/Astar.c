#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "Astar.H"
unsigned long long int node_counter=1;

struct stack_element first_state;
struct stack_element new_node;
struct stack_element empty_node;
struct stack_element found_goal;

stack_type frontier;
stack_type closed_stack; 

int GoalState[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};


int main(){	
long i;
double time=0;


found_goal.rating=40000;
//������������ ������� 
initialize(&frontier);
//������������ ������ ��� �� ������������ ��� ����������� ��� ����� ��������� 
initialize(&closed_stack);

//���������� ������� ���������� 
RandomGenerator();

//������ �������� ������
clock_t start,sofar; 
start=clock();


//������ ���������� �� ���� ��� 2 ����
while (time<2)
	{
//�� ���� ��������� ��������� � ������ ��� �������� ���� ������ ��� ������� ��� �������
//��� � �������� ��� ��������� ������ ����� ��������� �� ��� �������� ��� ���������� ����� ��� ������ ���� , 
//���� ���� ������� �������� , ����������� pop	(������ 118)
		if (found_goal.rating>frontier.node[frontier.top].rating)
		{
		
		//����������� ��� ������� ����� ��� ����� ��� ��������� �� ����������� ��� ��� �������� ��� ������� pop �� �� ����� ��� �������
			push_to_closed(&closed_stack,frontier.node[frontier.top]);
			pop(&frontier,&frontier.node[frontier.top]);

			
			//������� ���� ��� i �� ���� -���� closed �����- ��� ������ ��� ����������� 
			i=closed_stack.top;
			
			
			/*��������� �� ������ ��� ����� ��� ����������� ��� ��� ������ ��� �� ������� (�� U=����) ������������ �� ������ ���
			�� �� ������� ��� create_child.
			���������� ����� �� ����� ������ ��� ������������ ������ ������� �� �� ���� ��� ����� 
			��� ��� ����������� ������ (���� �� ���������� �� �����-����). */
			
			//UP MOVE
			if (closed_stack.node[i].space_pos[0]!=0  && closed_stack.node[i].move!='D' )	
			{
				create_child (closed_stack.node[i],'U');			
			}
			
			//DOWN MOVE
			if (closed_stack.node[i].space_pos[0]!=3 && closed_stack.node[i].move!='U' )	
			{
				create_child (closed_stack.node[i],'D');
			}
			
			//LEFT MOVE
			if (closed_stack.node[i].space_pos[1]!=0 && closed_stack.node[i].move!='R' )	
			{
				create_child (closed_stack.node[i],'L');
			}
			
			//RIGHT MOVE
			if (closed_stack.node[i].space_pos[1]!=3 && closed_stack.node[i].move!='L' )	
			{
				create_child (closed_stack.node[i],'R');	
			}			
			
			
			//����� 
			sofar=clock()-start;	
			time= ((double)sofar)/(CLOCKS_PER_SEC*3600);
			
			
			//OverFlow Check
			if (frontier.top>max_stack_elements)
			{
				printf("FRONTIER STACK OVERFLOW! \n");
				break;
			}
			if (closed_stack.top>max_stack_elements-3)
			{
				printf("CLOSED STACK OVERFLOW! \n");
				break;
			}
			
		
		}
		else pop(&frontier,&frontier.node[frontier.top]);
		
		//��� �� ������ ���� �������� ���� ��������� �� �������� ��� ��������� �����
		if (is_empty(&frontier)<0) 
		{
			printPath(found_goal);
			break;
		}
	} 

printf("Total nodes created: %llu \n",node_counter);
printf("Time passed: %.0f minutes",time);

return 0;
}

//�����������

//��������� ����������� ������� ������� ����������
void RandomGenerator ()
{
	int Puzzle[4][4];
	int n=15,i,j,x,y,x1,y1,swap_block;
	double time;
	
	//initialize first state
	first_state.father_pointer = -1;
	first_state.move = 'S';
	first_state.depth = 0;
		
	//������� ������ Puzzle
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

	//��������� ������� ������ ��� 2 ������������ 
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

	//������� ��� ������� ���������� (first_state.state) �� ��� ����� ��� ������ Puzzle ��� ���������� ����� �����
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
	
	//Push ��� ������ ������� ���������� ��� ������ ��� ���������� ��� ���������� �� �� ������� ��� ���������� evaluation
	push(&frontier,first_state);
	first_state.rating=evaluation(first_state);
}




//��������� ����������� ������
void create_child (struct stack_element node_father,char new_move)
{
	int i,j;
	//������� ���������� ����� ��� �������������� ��� ���� ������
		new_node.father_pointer = closed_stack.top;
		new_node.move = new_move;
		new_node.depth =node_father.depth+1;
	
	//������������ ��� ������ ���������� �� ���� �� ����� ��� ������� ������
		for (i=0 ;i<4;i++)
		{
			for (j=0 ;j<4;j++)
			{
				new_node.state[i][j]=node_father.state[i][j];
			}
		}
		
		
		//�������� ��� ������� ���� ������ ������� �� �� ������ ��� ������� ��� ������ 
		if (new_move =='L')
		{
			//���������� ���� ����� �����
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]-1;
			 //��������� ����� ��� ����� ��� �������������
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1]=0;
		}
		else if (new_move =='R')
		{
			//���������� ���� ����� �����
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]+1;
			 //��������� ����� ��� ����� ��� �������������
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1]=0;
		}
		else if (new_move =='D')
		{
			//���������� ���� ����� �����
			new_node.space_pos[0]=node_father.space_pos[0]+1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			//��������� ����� ��� ����� ��� �������������
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]]=0;
		}
		else if (new_move =='U')
		{
			//save new space position
			new_node.space_pos[0]=node_father.space_pos[0]-1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			//��������� ����� ��� ����� ��� �������������
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]]=0;
		}
		
		//���������� ����� ����������
		new_node.rating=evaluation(new_node);
		//�������� ������ 	
		node_counter++;
		// ������� ��� �������������� ������ ��� ������
		push(&frontier,new_node);
		
}  


//���������� ��� ���� ������
void initialize(stack_type *stack) {
	stack->top = -1;
}

/*������� �� � ������ ����� ����
�������: � ������
������: ���������� 1 �� � ������ ����� ���� ��� 0 ����������� */
int is_empty(stack_type *stack) {
	if (stack->top !=-1) return 0;
	else return 1;
}


/* ������� ��� �������� ���� ������ ���� ��������� ���� ���� �� ����������� � ������������� ��� �������� �� ��� ��������� ��������� 
�������: � ������ ��� �� �������� ���� ��������
������: � ������������� ������ */
void push(stack_type *stack, struct stack_element item) {
		int i;
		//��������������� ������� , ������������ �� ��� ����������� ���� �� ���� ��� ����� ��������� ��������� ������� 
		for (i=stack->top;i>=0;i--)
		{
		//������� ������� �� ��������� ����� �� ���� �� ���� ���
			if (item.rating>=stack->node[i].rating)
			{
				stack->node[i+1]=stack->node[i];
			}
			else 
			{
				stack->node[i+1]=item;
				stack->top++;
				break;
			}
		}
		
		//Push ������� ����������
		if (stack->top==-1)
		{
			stack->top++;
			stack->node[stack->top]=item;
		}
		
		
}

/* ����������: ������ ��� �������� ��� �� ������
�������: � ������ ��� �� ���� �������� empty_node
������: � ������������� ������ */
void pop(stack_type *stack, struct stack_element *item) {
	if (is_empty(stack)==0) {
		stack->node[stack->top]=empty_node;
		stack->top--;
	}
	else
		printf("----The stack is empty! Cannot delete any items!----");
}

/*����������: ��������� ��� ��������� ��� ������ ��� ������� �� ������. 
��� �������� ����� ��� ����� ��� �� ������ ��� ������ �����. � �������� ��������� ���� �������� ��� ����. */
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

if (item.father_pointer!=-1) printPath(closed_stack.node[item.father_pointer]);

}


/*��������� ���������� F(n)
�������:������� �� ������ ��� ���������������� �����
���������� : ������� �� ������ ��� ��������� ��� �� ���� �� �� ���� ���������� 
��� ����� ��� ������ [g(n)] + ��� ���� ��� heuristic [h(n)] 

**� ���� ��� heuristic ����� �� �������� ��� ���������� ��� ������� ���������� 
���� ��� ������� ��� ��� ������ ���� ������ 
*/
long evaluation (struct stack_element ev_node)
{
	int i,j,flag,x,y,yp,pl,manhattan,heuristic=0;
	
	//��� ���� ���� ��� ������ ev_node.state, ��������� ���� ������ ��� ���������� ������ 
	//����� �� ������ �� ���� ��� ���� ��� ���� ����.T��� ����������� ��� ��������� ��� ������ �������� ��� 2 ����� ������.
	for (i=0;i<=3;i++)
	{
		
		for (j=0;j<=3;j++)
		{
			flag=0;
			
			for (x=0;x<=3;x++)
			{
				for (y=0;y<=3;y++)
				{
					if (ev_node.state[i][j]==GoalState[x][y])
					{
					//������� ��� ������� ����
						yp=i-x;
						if (yp<0) yp=yp*(-1);
					
						
						pl=j-y;
						if (pl<0) pl=pl*(-1);
					//�������� ��������� ������� + �����	
						manhattan=yp+pl;
						
					//����������� �� ���������� ���� ���� ��� ���� �� heuristic ���	
						heuristic=heuristic+manhattan;
					//������� break ��� ������� ��� ������� ���� ��� ������ ev_node.state
						flag=1;
						break;
					}
			
				}
				if (flag==1) break;
			}
		}
	}

	//Goal State Check | ������������ ��� ����� ��� ������ ��� ���� ���� ����� found_goal
	if (heuristic==0)
	{
		found_goal=ev_node;
		found_goal.rating=found_goal.depth;
	}

	//F(n) = h(n) | g(n) = depth
	return heuristic+ev_node.depth;
}


//��������� ��������� ��������� ��� ������ closed_stack
void push_to_closed (stack_type *stack, struct stack_element item) 
{
		stack->top++;
		stack->node[stack->top] = item;
}



