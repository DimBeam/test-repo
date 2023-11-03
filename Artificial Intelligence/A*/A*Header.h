#define max_stack_elements 1000000


struct stack_element{
int state [4][4];
long father_pointer ;
char move ;
long depth ;
int space_pos [2];
long rating;
};

typedef struct {
	long top;
	struct stack_element node[max_stack_elements];
} stack_type;

void initialize(stack_type *stack);
int is_empty(stack_type *stack);
void push(stack_type *stack, struct stack_element item);
void pop(stack_type *stack,struct stack_element *item);

void RandomGenerator();
void create_child (struct stack_element node_father,char new_move);
int rep_state_check(struct stack_element new_node);
int isGoal(int newState[][4]);
void printPath (struct stack_element item);
void push_to_closed (stack_type *stack, struct stack_element item);
long evaluation (struct stack_element ev_node);
