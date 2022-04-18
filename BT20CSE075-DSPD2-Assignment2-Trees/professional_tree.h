#ifndef PROFESSIONAL_H
#define PROFESSIONAL_H
#define PROFESSIONAL_CONTACT 1
typedef struct tree_node_s2 
{
  	int height;
    char name[50];
    int phone_key;
    char email[50];
    char office_number[50];
    char office[50];
    int cont_type;
  	struct tree_node_s2 *left_child, *right_child, *parent;
} Professional_Node;
typedef struct avl_tree_s2 
{
  	int height, number_of_nodes;
  	struct tree_node_s2 *root;
} AvlTree_Professional; //basically a container
//constructors
AvlTree_Professional * make_Professional_tree_from_node(Professional_Node *node); //utility, not used
AvlTree_Professional * make_Professional_tree_empty();
Professional_Node * make_Professional_node();
//avl checks needed for insert delete
void Professional_check_in(AvlTree_Professional *tree, Professional_Node *node);
void Professional_check_out(AvlTree_Professional *tree, Professional_Node *node);
//utilities
int get_int_max_Professional(int a, int b);
int get_height_Professional(Professional_Node *node);
int balance_Professional(Professional_Node *node);
void clean_Professional(AvlTree_Professional* tree);
void cleaner_Professional(Professional_Node* root);
//display
void print_node_Professional(Professional_Node* node);
void inorder_Professional(Professional_Node* root);
void inorder_print_Professional(AvlTree_Professional* tree);
void inorder_professional_reverse(Professional_Node* root);
void inorder_print_professional_reverse(AvlTree_Professional* tree);
void print_range_prof(Professional_Node* root,int k1,int k2);
//rotations about given node needed for insert delete
void rotate_right_Professional(AvlTree_Professional *tree, Professional_Node *node);
void rotate_left_Professional(AvlTree_Professional *tree, Professional_Node *node);
//insert,delete,search,edit
int key_insert_newProfessional(AvlTree_Professional *tree);
int key_delete_Professional(int key, AvlTree_Professional *tree);
int search_by_key_Professional(int key, AvlTree_Professional *tree,Professional_Node** node);
int edit_by_key_Professional(int ket, AvlTree_Professional * tree);
//Q8-display sorted by name
Professional_Node* copy_node_2(Professional_Node* node);//create copy of data
int insert_professional_by_name(AvlTree_Professional* tree,Professional_Node* node);
void create_name_tree_Professional(AvlTree_Professional* tree,Professional_Node* root);
void check_in_professional_name(AvlTree_Professional *tree, Professional_Node *node);
void rotate_right_professional_name(AvlTree_Professional *tree, Professional_Node *node);
void rotate_left_professional_name(AvlTree_Professional *tree, Professional_Node *node);
#endif