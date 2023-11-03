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
//Αρχικοποίηση στοίβας μετώπου
initialize(&frontier);
//Δημιουργία τυχαίας αρχικής κατάστασης
RandomGenerator();
//Έναρξη χρονομέτρου
clock_t start,sofar; 
start=clock();
//Βρόγχος επαναληπτικής εκβάθυνσης | Κάνει break αν βρεθεί ο στόχος ή αν παρέλθει το χρονικό όριο (γραμμή 108)
for (d=0;d>=0;d++)
{
	
	printf("\n \t START WITH LIMIT DEPTH %d \n",d);
	
	//Οσό δεν έχει αδιάσει το μέτωπο τρέχει ο DFS
	while(is_empty(&frontier)==0)
	{
		//Δίνουμε στο i την τιμή του μετρητή top για ευκολία αναφοράς
		i=frontier.top;
		/*Εαν ο κόβμος που συντάμε στην κορυφή δέν έχει μεγαλύτερο βάθος απο το επιτρεπτό 
		και δεν έχει επεκταθεί ήδη , τότε το επεκτήνουμε. Διαφορετικά κάνουμε pop (γραμμή 99) */
		if (frontier.node[i].depth<d && frontier.node[i].expanded=='N')
		{
			//Αλλάξουμε το χαρακτηριστηκό expanded σε Y ώστε να κάνουμε pop οταν τον ξανασυναντίσουμε
			frontier.node[i].expanded='Y';
			
			/*Περνώντας ως όρισμα τον κόβμο που επεκτήνουμε και την κινήση που θα κάνουμε (πχ U=πάνω) δημιουργούμε τα παιδιά του
			με τη βοήθεια της create_child.
			Ελέγχοντας πάντα αν είναι δυνατη μια συγκεκριμένη κίνηση ανάλογα με τη θέση του κενου 
			και την προηγούμεγη κίνηση (ώστε να αποφύγουμε τα μπρος-πίσω). */
			
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
		
		//Χρονόμετρο & έλεγχος 
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



//ΣΥΝΑΡΤΗΣΕΙΣ

//Συνάρτηση δημιουργίας τυχαίας αρχικής κατάστασης
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
	//Push του κόμβου αρχικής κατάστασης στη στοίβα
	push(&frontier,first_state);
}

/* Συνάρτηση έλεγχου στόχου
False=0 , True=1 */
int isGoal(int newState[][4])
{
	int i,j;
	//Ελέγχος κάθε κελιού με τα αντίστοιχα της κατάστασης στόχου
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

//Συνάρτηση δημιουργίας κόμβου
void create_child (struct stack_element node_father,char new_move)
{
	int i,j;
	//Ορισμός κατάλληλων τιμών στα χαρακτηριστηκά του νέου κόμβου
		new_node.own_pointer=frontier.top+1;
		new_node.father_pointer = node_father.own_pointer;
		new_node.move = new_move;
		new_node.depth =node_father.depth+1;
		new_node.expanded = 'N';
	
	
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
			 //Ανταλλαγή τιμών στα κελία που μετακινήθηκαν
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1];
			 new_node.state[node_father.space_pos[0]][node_father.space_pos[1]+1]=0;
		}
		else if (new_move =='D')
		{
			//Αποθήκευση νεας θέσης κενού
			new_node.space_pos[0]=node_father.space_pos[0]+1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			 //Ανταλλαγή τιμών στα κελία που μετακινήθηκαν
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]+1][node_father.space_pos[1]]=0;
		}
		else if (new_move =='U')
		{
			//Αποθήκευση νεας θέσης κενού
			new_node.space_pos[0]=node_father.space_pos[0]-1;
			new_node.space_pos[1]=node_father.space_pos[1];	 
			 //Ανταλλαγή τιμών στα κελία που μετακινήθηκαν
			new_node.state[node_father.space_pos[0]][node_father.space_pos[1]]=new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]];
			new_node.state[node_father.space_pos[0]-1][node_father.space_pos[1]]=0;
		}
  		//Μετρητής κόμβων
		node_counter++;
		//Αν δεν βρεθεί ίδια κατάσταση  , τότε την προσθέτουμε στη στοίβα 
  		if (rep_state_check(new_node)==1) push(&frontier,new_node);		
}  


//Συνάρτηση ελέγχου επαναλαμβανόμενων καταστάσεων
int rep_state_check(struct stack_element this_node)
{
	int i,x,y;
	char flag='c';
	int cycle;
	int f=this_node.father_pointer;

//Ελέγχος όλων των προγόνων μέχρι τη ρίζα 	 
while (f!=-1)
{
	/*Ελεγχος για κυκλικές κινήσεις - Ελέγχονται μονο οι κόμβοι που έχουν διαφορά βάθους 12/ 30/ 56 /90 /132 καθώς 
	αυτές ειναι οι κινήσεις που μπορούν να δημιουργήσουν επαναλαμβανόμενη κατάσταση   2χ2|2χ3|3χ3|3χ4|4χ4 αντίστοιχα 
	*/
	cycle=this_node.depth-frontier.node[frontier.top].depth;
	if (cycle==(12 || 30 || 56 ||90|| 132))
	{
		flag='c';
	//Έλέχγος ένα προς ενα τα στοιχεία του πίνακα-state των προγόνων με τα αντίστοιχα της νεας κατάστασης	
	//Αν βρεθεί μη κοινό στοιχείο κάνουμε break και απ τις 2 επαναλήψεις ώστε να περάσουμε στον επόμενο έλεγχο  
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
	//Εαν έχουμε φτάσει στο τελευταίο στοιχείo του πίνακα χωρις να χει γίνει break σημαίνει οτι υπάρχει ίδια κατάσταση στη στοίβα 
			if (x==3 && y==3) 
			{
				printf("same state found! \n");
				return 0;
			}
			
		}
	}
	//Δίνουμε στο f τη θέση του πάτερα του κόμβου που ελέχθηκε , περνώντας έτσι στο παλαιότερο πρόγονο
	f=frontier.node[f].father_pointer;
}
return 1;
}


/* Λειτουργία: Δημιουργεί την κενή στοίβα
Είσοδος: Η στοίβα
Έξοδος: Μία κενή στοίβα */
void initialize(stack_type *stack) {
	stack->top = -1;
}

/* Λειτουργία: Ελέγχει αν η στοίβα είναι κενή
Είσοδος: Η στοίβα
Έξοδος: Επιστρέφει 1 αν η στοίβα είναι κενή και 0 διαφορετικά */
int is_empty(stack_type *stack) {
	if (stack->top !=-1) return 0;
	else return 1;
}

/* Λειτουργία: Εισάγει ένα στοιχείο στην στοίβα
Είσοδος: Η στοίβα και το στοιχείο προς εισαγωγή
Έξοδος: Η τροποποιημένη στοίβα */
void push(stack_type *stack, struct stack_element item) {
		stack->top++;
		stack->node[stack->top] = item;
}

/* Λειτουργία: Εξάγει ένα στοιχείο από τη στοίβα
Είσοδος: Η στοίβα και το κενό στοιχείο
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

if (item.father_pointer!=-1) printPath(frontier.node[item.father_pointer]);

}


