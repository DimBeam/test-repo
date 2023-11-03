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
//αρχικοποίηση μετώπου 
initialize(&frontier);
//αρχικοποίηση λίστας που θα περιλαμβάνει τις καταστάσεις που έχουν επεκταθεί 
initialize(&closed_stack);

//δημιουργία τυχαίας κατάστασης 
RandomGenerator();

//Έναρξη μέτρησης χρόνου
clock_t start,sofar; 
start=clock();


//Ενάρξη αναζήτησης με όριο τις 2 ώρες
while (time<2)
	{
//Σε κάθε επανάληψη ελέγχεται ο κόμβος που βρίσκετε στην κορυφή της στοίβας του μετώπου
//Εάν η εκτίμηση του τρέχοντος κόμβου είναι μικρότερη απ την εκτίμηση της μικρότερης λύσης που έχουμε βρει , 
//μονο τοτε κανουμε επέκταση , διαφορετικα pop	(γραμμή 118)
		if (found_goal.rating>frontier.node[frontier.top].rating)
		{
		
		//Προσθέτουμε στη κλειστή λίστα τον κομβο που πρόκειται να επεκτήνουμε και στη συνέχεια τον κάνουμε pop απ τη λίστα του μετώπου
			push_to_closed(&closed_stack,frontier.node[frontier.top]);
			pop(&frontier,&frontier.node[frontier.top]);

			
			//Δίνουμε τιμή στο i τη θέση -στην closed λίστα- του κόμβου που επεκτήνουμε 
			i=closed_stack.top;
			
			
			/*Περνώντας ως όρισμα τον κόβμο που επεκτήνουμε και την κινήση που θα κάνουμε (πχ U=πάνω) δημιουργούμε τα παιδιά του
			με τη βοήθεια της create_child.
			Ελέγχοντας πάντα αν είναι δυνατη μια συγκεκριμένη κίνηση ανάλογα με τη θέση του κενου 
			και την προηγούμεγη κίνηση (ώστε να αποφύγουμε τα μπρος-πίσω). */
			
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
			
			
			//Ρολόι 
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
		
		//Εαν το μέτωπο έχει αδειάσει τότε τυπώνουμε το μονοπάτι της καλύτερης λύσης
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

//ΣΥΝΑΡΤΗΣΕΙΣ

//Συνάρτηση δημιουργίας τυχαίας αρχικής κατάστασης
void RandomGenerator ()
{
	int Puzzle[4][4];
	int n=15,i,j,x,y,x1,y1,swap_block;
	double time;
	
	//initialize first state
	first_state.father_pointer = -1;
	first_state.move = 'S';
	first_state.depth = 0;
		
	//Γέμισμα πίνακα Puzzle
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

	//Ανακάτεμα τυχαίων κελιών για 2 δευτερόλεπτα 
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

	//Γέμισμα της αρχικής κατάστασης (first_state.state) με τις τιμές του πίνακα Puzzle και αποθήκευση θέσης κενού
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
	
	//Push του κόμβου αρχικής κατάστασης στο μέτωπο και αποθήκευση της αποτίμησης με τη βοήθεια της συνάρτησης evaluation
	push(&frontier,first_state);
	first_state.rating=evaluation(first_state);
}




//Συνάρτηση δημιουργίας κόμβου
void create_child (struct stack_element node_father,char new_move)
{
	int i,j;
	//Ορισμός κατάλληλων τιμών στα χαρακτηριστηκά του νέου κόμβου
		new_node.father_pointer = closed_stack.top;
		new_node.move = new_move;
		new_node.depth =node_father.depth+1;
	
	//Αρχικοποίηση του πίνακα κατάστασης ως ίδιο με αυτόν του γονικού κόμβου
		for (i=0 ;i<4;i++)
		{
			for (j=0 ;j<4;j++)
			{
				new_node.state[i][j]=node_father.state[i][j];
			}
		}
		
		
		//Εφαρμογή των αλλαγών στον πίνακα ανάλογα με το όρισμα της κίνησης που δόθηκε 
		if (new_move =='L')
		{
			//Αποθήκευση νεας θέσης κενού
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]-1;
			 //Ανταλλαγή τιμών στα κελία που μετακινήθηκαν
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]-1]=0;
		}
		else if (new_move =='R')
		{
			//Αποθήκευση νεας θέσης κενού
			 new_node.space_pos[0]=node_father.space_pos[0];
			 new_node.space_pos[1]=node_father.space_pos[1]+1;
			 //Ανταλλαγή τιμώς στα κελία που μετακινήθηκαν
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1]=0;
		}
		else if (new_move =='D')
		{
			//Αποθήκευση νεας θέσης κενού
			new_node.space_pos[0]=node_father.space_pos[0]+1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			//Ανταλλαγή τιμώς στα κελία που μετακινήθηκαν
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]]=0;
		}
		else if (new_move =='U')
		{
			//save new space position
			new_node.space_pos[0]=node_father.space_pos[0]-1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			//Ανταλλαγή τιμώς στα κελία που μετακινήθηκαν
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]]=0;
		}
		
		//Αποθήκευση τιμής αποτίμησης
		new_node.rating=evaluation(new_node);
		//Μετρητής κόμβων 	
		node_counter++;
		// Είσοδος του δημιουργημένου κόμβου στη στοίβα
		push(&frontier,new_node);
		
}  


//Δημιουργεί την κενή στοίβα
void initialize(stack_type *stack) {
	stack->top = -1;
}

/*Ελέγχει αν η στοίβα είναι κενή
Είσοδος: Η στοίβα
Έξοδος: Επιστρέφει 1 αν η στοίβα είναι κενή και 0 διαφορετικά */
int is_empty(stack_type *stack) {
	if (stack->top !=-1) return 0;
	else return 1;
}


/* Εισάγει ένα στοιχείο στην στοίβα στην κατάλληλη θέση ώστε να διατηρείται η προτεραιότητα των στοιχίων με την μικρότερη αποτίμηση 
Είσοδος: Η στοίβα και το στοιχείο προς εισαγωγή
Έξοδος: Η τροποποιημένη στοίβα */
void push(stack_type *stack, struct stack_element item) {
		int i;
		//Προτεραιοποίηση στοίβας , σπρώχονοντας το νεο αντικείμενο πίσω απ αυτά που έχουν μικρότερη αποτίμηση κόστους 
		for (i=stack->top;i>=0;i--)
		{
		//Σπρώνει μπροστά τα μικρότερα μέχρι να βρει τη θέση του
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
		
		//Push Αρχικής κατάστασης
		if (stack->top==-1)
		{
			stack->top++;
			stack->node[stack->top]=item;
		}
		
		
}

/* Λειτουργία: Εξάγει ένα στοιχείο από τη στοίβα
Είσοδος: Η στοίβα και το κενό στοιχείο empty_node
Έξοδος: Η τροποποιημένη στοίβα */
void pop(stack_type *stack, struct stack_element *item) {
	if (is_empty(stack)==0) {
		stack->node[stack->top]=empty_node;
		stack->top--;
	}
	else
		printf("----The stack is empty! Cannot delete any items!----");
}

/*Λειτουργία: Εκτυπώνει την κατάσταση του κομβου που δέχεται ως ορισμα. 
Στη συνέχεια καλεί τον εαυτό της με όρισμα τον γονικό κόμβο. Η αναδρομή σταματάει όταν φτάσουμε στη ρίζα. */
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


/*Συνάρτηση αποτίμησης F(n)
Είσοδος:Δέχεται ως όρισμα τον νεοδημιουργημένο κόμβο
Λειτουργία : Αποτιμά το κόστος της διαδρομής απο τη ρίζα ως τη λύση βασιζόμενη 
στο βάθος του κόμβου [g(n)] + την τιμή του heuristic [h(n)] 

**Η τιμή του heuristic είναι το άθροισμα των οριζόντιων και κάθετων αποστάσεων 
όλων των αριθμών από τις σωστές τους θέσεις 
*/
long evaluation (struct stack_element ev_node)
{
	int i,j,flag,x,y,yp,pl,manhattan,heuristic=0;
	
	//Για κάθε κελί του πίνακα ev_node.state, αναζήτηση στον πίνακα της κατάστασης στόχου 
	//μέχρι να βρούμε το κελί που έχει την ίδια τιμή.Tότε προσθέτουμε την οριζόντια και κάθετη απόσταση των 2 αυτών κελιών.
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
					//Κρατάμε την απόλυτη τιμή
						yp=i-x;
						if (yp<0) yp=yp*(-1);
					
						
						pl=j-y;
						if (pl<0) pl=pl*(-1);
					//Πρόσθεση απόστασης πλάτους + ύψους	
						manhattan=yp+pl;
						
					//Προσθέτουμε το αποτέλεσμα στην τιμή που έχει το heuristic ήδη	
						heuristic=heuristic+manhattan;
					//κάνουμε break και περνάμε στο επόμενο κελί του πίνακα ev_node.state
						flag=1;
						break;
					}
			
				}
				if (flag==1) break;
			}
		}
	}

	//Goal State Check | Αποθηκεύουμε τον κόμβο που έφτασε στη λύση στον κόμβο found_goal
	if (heuristic==0)
	{
		found_goal=ev_node;
		found_goal.rating=found_goal.depth;
	}

	//F(n) = h(n) | g(n) = depth
	return heuristic+ev_node.depth;
}


//Συνάρτηση εισαγωγής στοιχείου στη στοίβα closed_stack
void push_to_closed (stack_type *stack, struct stack_element item) 
{
		stack->top++;
		stack->node[stack->top] = item;
}



