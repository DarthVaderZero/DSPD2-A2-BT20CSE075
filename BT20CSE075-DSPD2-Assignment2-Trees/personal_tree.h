#ifndef PERSONAL_H
#define PERSONAL_H
#define PERSONAL_CONTACT 0
typedef struct tree_node_s 
{
  	int height;
    char name[50];
    int phone_key;
    char email[50];
    int cont_type;
  	struct tree_node_s *left_child, *right_child, *parent;
} Personal_Node;
typedef struct avl_tree_s 
{
  	int height, number_of_nodes;
  	struct tree_node_s *root;
} AvlTree_Personal; //basically a container
//constructors
AvlTree_Personal * make_personal_tree_from_node(Personal_Node *node); //utility, not used
AvlTree_Personal * make_personal_tree_empty();
Personal_Node * make_personal_node();
//avl checks needed for insert delete
void personal_check_in(AvlTree_Personal *tree, Personal_Node *node);
void personal_check_out(AvlTree_Personal *tree, Personal_Node *node);
//utilities
int get_int_max_personal(int a, int b);
int get_height_personal(Personal_Node *node);
int balance_personal(Personal_Node *node);
void clean_personal(AvlTree_Personal* tree);
void cleaner_personal(Personal_Node* root);
//display
void print_node_personal(Personal_Node* node);
void inorder_personal(Personal_Node* root);
void inorder_print_personal(AvlTree_Personal* tree);
void inorder_personal_reverse(Personal_Node* root);
void inorder_print_personal_reverse(AvlTree_Personal* tree);
void print_range_personal(Personal_Node* root,int k1,int k2);
//rotations about given node needed for insert delete
void rotate_right_personal(AvlTree_Personal *tree, Personal_Node *node);
void rotate_left_personal(AvlTree_Personal *tree, Personal_Node *node);
//insert,delete,search,edit
int key_insert_newpersonal(AvlTree_Personal *tree);
int key_delete_personal(int key, AvlTree_Personal *tree);
int search_by_key_personal(int key, AvlTree_Personal *tree,Personal_Node** node);
int edit_by_key_personal(int ket, AvlTree_Personal * tree);
//Q8-display sorted by name
Personal_Node* copy_node(Personal_Node* node);//create copy of data
int insert_personal_by_name(AvlTree_Personal* tree,Personal_Node* node);
void create_name_tree_personal(AvlTree_Personal* tree,Personal_Node* root);
void check_in_personal_name(AvlTree_Personal *tree, Personal_Node *node);
void rotate_right_personal_name(AvlTree_Personal *tree, Personal_Node *node);
void rotate_left_personal_name(AvlTree_Personal *tree, Personal_Node *node);
#endif