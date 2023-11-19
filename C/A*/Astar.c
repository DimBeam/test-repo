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
//áñ÷éêïðïßçóç ìåôþðïõ 
initialize(&frontier);
//áñ÷éêïðïßçóç ëßóôáò ðïõ èá ðåñéëáìâÜíåé ôéò êáôáóôÜóåéò ðïõ Ý÷ïõí åðåêôáèåß 
initialize(&closed_stack);

//äçìéïõñãßá ôõ÷áßáò êáôÜóôáóçò 
RandomGenerator();

//¸íáñîç ìÝôñçóçò ÷ñüíïõ
clock_t start,sofar; 
start=clock();


//ÅíÜñîç áíáæÞôçóçò ìå üñéï ôéò 2 þñåò
while (time<2)
	{
//Óå êÜèå åðáíÜëçøç åëÝã÷åôáé ï êüìâïò ðïõ âñßóêåôå óôçí êïñõöÞ ôçò óôïßâáò ôïõ ìåôþðïõ
//ÅÜí ç åêôßìçóç ôïõ ôñÝ÷ïíôïò êüìâïõ åßíáé ìéêñüôåñç áð ôçí åêôßìçóç ôçò ìéêñüôåñçò ëýóçò ðïõ Ý÷ïõìå âñåé , 
//ìïíï ôïôå êáíïõìå åðÝêôáóç , äéáöïñåôéêá pop	(ãñáììÞ 118)
		if (found_goal.rating>frontier.node[frontier.top].rating)
		{
		
		//ÐñïóèÝôïõìå óôç êëåéóôÞ ëßóôá ôïí êïìâï ðïõ ðñüêåéôáé íá åðåêôÞíïõìå êáé óôç óõíÝ÷åéá ôïí êÜíïõìå pop áð ôç ëßóôá ôïõ ìåôþðïõ
			push_to_closed(&closed_stack,frontier.node[frontier.top]);
			pop(&frontier,&frontier.node[frontier.top]);

			
			//Äßíïõìå ôéìÞ óôï i ôç èÝóç -óôçí closed ëßóôá- ôïõ êüìâïõ ðïõ åðåêôÞíïõìå 
			i=closed_stack.top;
			
			
			/*Ðåñíþíôáò ùò üñéóìá ôïí êüâìï ðïõ åðåêôÞíïõìå êáé ôçí êéíÞóç ðïõ èá êÜíïõìå (ð÷ U=ðÜíù) äçìéïõñãïýìå ôá ðáéäéÜ ôïõ
			ìå ôç âïÞèåéá ôçò create_child.
			ÅëÝã÷ïíôáò ðÜíôá áí åßíáé äõíáôç ìéá óõãêåêñéìÝíç êßíçóç áíÜëïãá ìå ôç èÝóç ôïõ êåíïõ 
			êáé ôçí ðñïçãïýìåãç êßíçóç (þóôå íá áðïöýãïõìå ôá ìðñïò-ðßóù). */
			
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
			
			
			//Ñïëüé 
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
		
		//Åáí ôï ìÝôùðï Ý÷åé áäåéÜóåé ôüôå ôõðþíïõìå ôï ìïíïðÜôé ôçò êáëýôåñçò ëýóçò
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

//ÓÕÍÁÑÔÇÓÅÉÓ

//ÓõíÜñôçóç äçìéïõñãßáò ôõ÷áßáò áñ÷éêÞò êáôÜóôáóçò
void RandomGenerator ()
{
	int Puzzle[4][4];
	int n=15,i,j,x,y,x1,y1,swap_block;
	double time;
	
	//initialize first state
	first_state.father_pointer = -1;
	first_state.move = 'S';
	first_state.depth = 0;
		
	//ÃÝìéóìá ðßíáêá Puzzle
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

	//ÁíáêÜôåìá ôõ÷áßùí êåëéþí ãéá 2 äåõôåñüëåðôá 
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

	//ÃÝìéóìá ôçò áñ÷éêÞò êáôÜóôáóçò (first_state.state) ìå ôéò ôéìÝò ôïõ ðßíáêá Puzzle êáé áðïèÞêåõóç èÝóçò êåíïý
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
	
	//Push ôïõ êüìâïõ áñ÷éêÞò êáôÜóôáóçò óôï ìÝôùðï êáé áðïèÞêåõóç ôçò áðïôßìçóçò ìå ôç âïÞèåéá ôçò óõíÜñôçóçò evaluation
	push(&frontier,first_state);
	first_state.rating=evaluation(first_state);
}




//ÓõíÜñôçóç äçìéïõñãßáò êüìâïõ
void create_child (struct stack_element node_father,char new_move)
{
	int i,j;
	//Ïñéóìüò êáôÜëëçëùí ôéìþí óôá ÷áñáêôçñéóôçêÜ ôïõ íÝïõ êüìâïõ
		new_node.father_pointer = closed_stack.top;
		new_node.move = new_move;
		new_node.depth =node_father.depth+1;
	
	//Áñ÷éêïðïßçóç ôïõ ðßíáêá êáôÜóôáóçò ùò ßäéï ìå áõôüí ôïõ ãïíéêïý êüìâïõ
		for (i=0 ;i<4;i++)
		{
			for (j=0 ;j<4;j++)
			{
				new_node.state[i][j]=node_father.state[i][j];
			}
		}
		
		
		//ÅöáñìïãÞ ôùí áëëáãþí óôïí ðßíáêá áíÜëïãá ìå ôï üñéóìá ôçò êßíçóçò ðïõ äüèçêå 
		if (new_move =='L')
		{
			//ÁðïèÞêåõóç íåáò èÝóçò êåíïý
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]-1;
			 //ÁíôáëëáãÞ ôéìþí óôá êåëßá ðïõ ìåôáêéíÞèçêáí
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1]=0;
		}
		else if (new_move =='R')
		{
			//ÁðïèÞêåõóç íåáò èÝóçò êåíïý
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]+1;
			 //ÁíôáëëáãÞ ôéìþò óôá êåëßá ðïõ ìåôáêéíÞèçêáí
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1]=0;
		}
		else if (new_move =='D')
		{
			//ÁðïèÞêåõóç íåáò èÝóçò êåíïý
			new_node.space_pos[0]=node_father.space_pos[0]+1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			//ÁíôáëëáãÞ ôéìþò óôá êåëßá ðïõ ìåôáêéíÞèçêáí
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]]=0;
		}
		else if (new_move =='U')
		{
			//save new space position
			new_node.space_pos[0]=node_father.space_pos[0]-1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			//ÁíôáëëáãÞ ôéìþò óôá êåëßá ðïõ ìåôáêéíÞèçêáí
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]]=0;
		}
		
		//ÁðïèÞêåõóç ôéìÞò áðïôßìçóçò
		new_node.rating=evaluation(new_node);
		//ÌåôñçôÞò êüìâùí 	
		node_counter++;
		// Åßóïäïò ôïõ äçìéïõñãçìÝíïõ êüìâïõ óôç óôïßâá
		push(&frontier,new_node);
		
}  


//Äçìéïõñãåß ôçí êåíÞ óôïßâá
void initialize(stack_type *stack) {
	stack->top = -1;
}

/*ÅëÝã÷åé áí ç óôïßâá åßíáé êåíÞ
Åßóïäïò: Ç óôïßâá
¸îïäïò: ÅðéóôñÝöåé 1 áí ç óôïßâá åßíáé êåíÞ êáé 0 äéáöïñåôéêÜ */
int is_empty(stack_type *stack) {
	if (stack->top !=-1) return 0;
	else return 1;
}


/* ÅéóÜãåé Ýíá óôïé÷åßï óôçí óôïßâá óôçí êáôÜëëçëç èÝóç þóôå íá äéáôçñåßôáé ç ðñïôåñáéüôçôá ôùí óôïé÷ßùí ìå ôçí ìéêñüôåñç áðïôßìçóç 
Åßóïäïò: Ç óôïßâá êáé ôï óôïé÷åßï ðñïò åéóáãùãÞ
¸îïäïò: Ç ôñïðïðïéçìÝíç óôïßâá */
void push(stack_type *stack, struct stack_element item) {
		int i;
		//Ðñïôåñáéïðïßçóç óôïßâáò , óðñþ÷ïíïíôáò ôï íåï áíôéêåßìåíï ðßóù áð áõôÜ ðïõ Ý÷ïõí ìéêñüôåñç áðïôßìçóç êüóôïõò 
		for (i=stack->top;i>=0;i--)
		{
		//Óðñþíåé ìðñïóôÜ ôá ìéêñüôåñá ìÝ÷ñé íá âñåé ôç èÝóç ôïõ
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
		
		//Push Áñ÷éêÞò êáôÜóôáóçò
		if (stack->top==-1)
		{
			stack->top++;
			stack->node[stack->top]=item;
		}
		
		
}

/* Ëåéôïõñãßá: ÅîÜãåé Ýíá óôïé÷åßï áðü ôç óôïßâá
Åßóïäïò: Ç óôïßâá êáé ôï êåíü óôïé÷åßï empty_node
¸îïäïò: Ç ôñïðïðïéçìÝíç óôïßâá */
void pop(stack_type *stack, struct stack_element *item) {
	if (is_empty(stack)==0) {
		stack->node[stack->top]=empty_node;
		stack->top--;
	}
	else
		printf("----The stack is empty! Cannot delete any items!----");
}

/*Ëåéôïõñãßá: Åêôõðþíåé ôçí êáôÜóôáóç ôïõ êïìâïõ ðïõ äÝ÷åôáé ùò ïñéóìá. 
Óôç óõíÝ÷åéá êáëåß ôïí åáõôü ôçò ìå üñéóìá ôïí ãïíéêü êüìâï. Ç áíáäñïìÞ óôáìáôÜåé üôáí öôÜóïõìå óôç ñßæá. */
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


/*ÓõíÜñôçóç áðïôßìçóçò F(n)
Åßóïäïò:ÄÝ÷åôáé ùò üñéóìá ôïí íåïäçìéïõñãçìÝíï êüìâï
Ëåéôïõñãßá : ÁðïôéìÜ ôï êüóôïò ôçò äéáäñïìÞò áðï ôç ñßæá ùò ôç ëýóç âáóéæüìåíç 
óôï âÜèïò ôïõ êüìâïõ [g(n)] + ôçí ôéìÞ ôïõ heuristic [h(n)] 

**Ç ôéìÞ ôïõ heuristic åßíáé ôï Üèñïéóìá ôùí ïñéæüíôéùí êáé êÜèåôùí áðïóôÜóåùí 
üëùí ôùí áñéèìþí áðü ôéò óùóôÝò ôïõò èÝóåéò 
*/
long evaluation (struct stack_element ev_node)
{
	int i,j,flag,x,y,yp,pl,manhattan,heuristic=0;
	
	//Ãéá êÜèå êåëß ôïõ ðßíáêá ev_node.state, áíáæÞôçóç óôïí ðßíáêá ôçò êáôÜóôáóçò óôü÷ïõ 
	//ìÝ÷ñé íá âñïýìå ôï êåëß ðïõ Ý÷åé ôçí ßäéá ôéìÞ.Tüôå ðñïóèÝôïõìå ôçí ïñéæüíôéá êáé êÜèåôç áðüóôáóç ôùí 2 áõôþí êåëéþí.
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
					//ÊñáôÜìå ôçí áðüëõôç ôéìÞ
						yp=i-x;
						if (yp<0) yp=yp*(-1);
					
						
						pl=j-y;
						if (pl<0) pl=pl*(-1);
					//Ðñüóèåóç áðüóôáóçò ðëÜôïõò + ýøïõò	
						manhattan=yp+pl;
						
					//ÐñïóèÝôïõìå ôï áðïôÝëåóìá óôçí ôéìÞ ðïõ Ý÷åé ôï heuristic Þäç	
						heuristic=heuristic+manhattan;
					//êÜíïõìå break êáé ðåñíÜìå óôï åðüìåíï êåëß ôïõ ðßíáêá ev_node.state
						flag=1;
						break;
					}
			
				}
				if (flag==1) break;
			}
		}
	}

	//Goal State Check | Áðïèçêåýïõìå ôïí êüìâï ðïõ Ýöôáóå óôç ëýóç óôïí êüìâï found_goal
	if (heuristic==0)
	{
		found_goal=ev_node;
		found_goal.rating=found_goal.depth;
	}

	//F(n) = h(n) | g(n) = depth
	return heuristic+ev_node.depth;
}


//ÓõíÜñôçóç åéóáãùãÞò óôïé÷åßïõ óôç óôïßâá closed_stack
void push_to_closed (stack_type *stack, struct stack_element item) 
{
		stack->top++;
		stack->node[stack->top] = item;
}



