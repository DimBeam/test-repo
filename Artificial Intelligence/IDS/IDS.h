	#define max_stack_elements 1000000


struct stack_element{
int state [4][4];
int own_pointer;
int father_pointer ;
char move ;
int depth ;
char expanded;
int space_pos [2];
};

typedef struct {
	int top;
	struct stack_element node[max_stack_elements];
} stack_type;

/* Äçìéïõñãåß ôçí êåíÞ óôïßâá */
void initialize(stack_type *stack);
/* ÅëÝã÷åé áí ç óôïßâá åßíáé Üäåéá */
int is_empty(stack_type *stack);
/* ÅéóÜãåé Ýíá óôïé÷åßï óôçí óôïßâá */
void push(stack_type *stack, struct stack_element item);
/* ÄéáãñÜöåé Ýíá óôïé÷åßï áðü ôçí óôïßâá */
void pop(stack_type *stack,struct stack_element *item);
/* ÅðéóôñÝöåé ôï êïñõöáßá óôïé÷åßï ôçò óôïßâáò ÷ùñßò íá ôï óâÞóåé */

/*Äçìéïõñãåß ìéá ôõ÷áßá áñ÷éêÞ êáôÜóôáóç*/
void RandomGenerator();
/*Äçìéïõñãåß íÝï êüìâï*/
void create_child (struct stack_element node_father,char new_move);
/*ÅëÝã÷åé åáí ç íåá êáôÜóôáóç õðÜñ÷åé Þäç óôçí óôïßâá*/
int rep_state_check(struct stack_element new_node);
/*ÅëÝã÷åé åáí ç äïèÞóá êáôÜóôáóç åßíáé ç êáôÜóôáóç óôü÷ïõ*/
int isGoal(int newState[][4]);
/*Åêôõðþíåé ôï ìïíïðÜôé áð ôï óôï÷ï ùò ôç ñßæá */
void printPath (struct stack_element item);

