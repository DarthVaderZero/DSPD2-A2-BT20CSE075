#include "personal_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<string.h>
//constructors
AvlTree_Personal * make_personal_tree_from_node(Personal_Node *node)
{
    assert(node != NULL);
  

    AvlTree_Personal *tree = (AvlTree_Personal *)malloc(sizeof(AvlTree_Personal));
    if(tree == NULL)
    {
        printf("Memory allocation failed while creating a new tree from a node.\n");
        exit(1);
    }

    tree->root = node; 
    tree->height = 0;
    tree->number_of_nodes = 1;
    return tree;
}
AvlTree_Personal *make_personal_tree_empty()
{
    AvlTree_Personal *new_tree = (AvlTree_Personal *)malloc(sizeof(AvlTree_Personal));
    if(new_tree == NULL)
    {
        printf("Memory allocation failed while creating an empty tree.\n");
        exit(1);
    }
    new_tree->root = NULL;
    new_tree->height = -1;
    new_tree->number_of_nodes = 0;
    return new_tree;
}
Personal_Node * make_personal_node()
{
    Personal_Node *new_node = (Personal_Node *)malloc(sizeof(Personal_Node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed while generating a new node.\n");
        exit(1); 
    }
    printf("Enter the name of the contact: \n");
    fgets(new_node->name,50,stdin);
    printf("Enter the phone number of the contact: \n");
    scanf("%d",&(new_node->phone_key));
    fflush(stdin);
    printf("Enter the email of contact: \n");
    fgets(new_node->email,50,stdin);
    new_node->cont_type=PERSONAL_CONTACT;
    new_node->left_child = new_node->right_child = new_node->parent = NULL;
    new_node->height = 0;
    return new_node;
}
//avl checks
void personal_check_in(AvlTree_Personal *tree, Personal_Node *node)
{
    assert(tree != NULL);
    assert(node != NULL);

    int bal = balance_personal(node); //get balance factor of this node

    if(node->parent == NULL) //if we're at root
    {
        return;
    }

    //get balance of parent
    Personal_Node *parent = node->parent;
    int p_bal = balance_personal(parent);

    // Check balance for correctness, rotating if necessary.
    if(node->phone_key < parent->phone_key)
    {
        if(p_bal == 0)
        {
            // Exit
            return;
        }
        else if(p_bal == -1)
        {
        // Continue check at the parent.
        personal_check_in(tree, parent);
        }
        else if(p_bal < -1)
        {
            if(bal == -1)
            {
	            // Do a single right rotation.
	            rotate_right_personal(tree, parent);
            }
            else if(bal == 1)
            {
	            // Do a double rotation (left, right).
	            rotate_left_personal(tree, parent->left_child);
	            rotate_right_personal(tree, parent);
            }
            else
            {
	            //Unreachable code under normal circumstances
	            printf("Critical error occured in check_in procedure.\n");
	            exit(2);
            }
        }
        else
        {
            // Unreachable code under normal circumstances
            printf("Critical error occured in check_in procedure.\n");
            exit(2);
        }
    }
    else
    {
        if(p_bal <= 0)
        {
            // Exit 
            return;
        }
        else if(p_bal == 1)
        {
            // Continue check_in at the parent. 
            personal_check_in(tree, parent);
        }
        else if(p_bal > 1)
        {
            if(bal == 1)
            {
	            // Do a single left rotation. 
	            rotate_left_personal(tree, parent);
            }
            else if(bal == -1)
            {
	            // Do a double rotation (right, left).
	            rotate_right_personal(tree, parent->right_child);
	            rotate_left_personal(tree, parent);
            }
            else
            {
	            // Unreachable code under normal circumstances
	            printf("Critical error occured in check_in procedure.\n");
	            exit(2);
            }
        }   
        else
        {
            // Unreachable code under normal circumstances
            printf("Critical error occured in check_in procedure.\n");
            exit(2);
        }
    }
}
void personal_check_out(AvlTree_Personal *tree, Personal_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Keep track of the parent of the node.
    Personal_Node *parent = node->parent;
  
    // Get the balance of the current node.
    int bal = balance_personal(node);

    if(bal < -1)
    {

        //get balance of its left child.
        int l_bal = balance_personal(node->left_child);

        if(l_bal == -1)
        {
            // Fix by single right rotation.
            rotate_right_personal(tree, node);
        }
        else if(l_bal == 1)
        {
            // Fix with a left-right rotation.
            rotate_left_personal(tree, node->left_child);
            rotate_right_personal(tree, node);
        }
        else
        {
            rotate_right_personal(tree, node);
        }
    }
    else if(bal > 1)
    {
        // get balance of its right child.
        int r_bal = balance_personal(node->right_child);

        if(r_bal == 1)
        {
            //  Fix with a single left rotation.
            rotate_left_personal(tree, node);
        }
        else if(r_bal == -1)
        {
            //  Fix with a right-left rotation.
            rotate_right_personal(tree, node->right_child);
            rotate_left_personal(tree, node);
        }
        else
        {
            rotate_left_personal(tree, node);
        }
    }

    // Continue upwards traversal.
    if(parent) 
    {
        personal_check_out(tree, parent);
    }
}
//utilities
inline int get_int_max_personal(int a, int b)
{
    return (a > b) ? a : b;
}
int get_height_personal(Personal_Node *node)
{
    // Check arguments.
    assert(node != NULL);

    int l_height = -1;
    int r_height = -1;
    // Update children's height if they exists.
    if(node->left_child)
    {
        l_height = node->left_child->height;
    }
    if(node->right_child) 
    {
        r_height = node->right_child->height;
    }
  
    // Calculate and return the correct height.
    return get_int_max_personal(l_height, r_height) + 1;
}
int balance_personal(Personal_Node *node)
{
    // Check arguments.
    assert(node != NULL);

    // The base heights for no children.
    int l_height = -1;
    int r_height = -1;
    // Update children's height if they exists.
    if(node->left_child) 
    {
        l_height = node->left_child->height;
    }
    if(node->right_child) 
    {
        r_height = node->right_child->height;
    }

    // Update the current node's height.
    node->height = get_int_max_personal(l_height, r_height) + 1;

    // Return the balance (height difference).
    return r_height - l_height;
}
//display
void print_node_personal(Personal_Node* node)
{
    if(node!=NULL)
    {
        fputs(node->name,stdout);
        printf("%d\n",node->phone_key);
        fputs(node->email,stdout);
        fputs("__________________________________________\n",stdout);
    }
}
void inorder_personal(Personal_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    inorder_personal(root->left_child);
    print_node_personal(root);
    inorder_personal(root->right_child);
}
void inorder_print_personal(AvlTree_Personal* tree)
{
    fputs("This prints phonebook in ascending order\n",stdout);
    inorder_personal(tree->root);
}
void inorder_personal_reverse(Personal_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    inorder_personal_reverse(root->right_child);
    print_node_personal(root);
    inorder_personal_reverse(root->left_child);
}
void inorder_print_personal_reverse(AvlTree_Personal* tree)
{
    fputs("This prints phonebook in descending order\n",stdout);
    inorder_personal_reverse(tree->root); 
}
//rotations
void rotate_right_personal(AvlTree_Personal *tree, Personal_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Personal_Node *l_child = node->left_child;

    // Do rotation.
    if(node->parent == NULL)
    {
        // Operating on root.
        tree->root = l_child;
        l_child->parent = NULL;
    }
    else
    {
        // Give the parent its new child.
        if(node->phone_key < node->parent->phone_key)
        {
        // We are at left child.
        node->parent->left_child = l_child;
        }
        else
        {
        // We are at right child.
        node->parent->right_child = l_child;
        }
        l_child->parent = node->parent;
    }
    // Rearrange the children nodes.
    node->left_child = l_child->right_child;
    // If a child is there, adapt its parent.
    if(l_child->right_child)
    {
        l_child->right_child->parent = node;
    }
    l_child->right_child = node;
    node->parent = l_child;

    // Update the heights.
    if(node)
    {
        node->height = get_height_personal(node);
    }
    if(l_child)
    {
        if(l_child->left_child)
        {
            l_child->left_child->height = get_height_personal(l_child->left_child);
        }
        l_child->height = get_height_personal(l_child);
    }
}
void rotate_left_personal(AvlTree_Personal *tree, Personal_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Personal_Node *r_child = node->right_child;

    // Do rotation.
    if(node->parent == NULL)
    {
        // Operating on root.
        tree->root = r_child;
        r_child->parent = NULL;
    }
    else
    {
        // Give the parent its new child.
        if(node->phone_key < node->parent->phone_key)
        {
            // We are at left child.
            node->parent->left_child = r_child;
        }
        else
        {
            // We are at right child.
            node->parent->right_child = r_child;
        }
        r_child->parent = node->parent;
    }
    // Rearrange the children nodes.
    node->right_child = r_child->left_child;
    // If a child is there, adapt its parent.
    if(r_child->left_child) 
    {
        r_child->left_child->parent = node;
    }
    r_child->left_child = node;
    node->parent = r_child;

    // Update the heights.
    if(node)
    {
        node->height = get_height_personal(node);
    }
    if(r_child)
    {
        if(r_child->right_child)
        {
            r_child->right_child->height = get_height_personal(r_child->right_child);
        }
        r_child->height = get_height_personal(r_child);
    }
}
//insert,delete,search
int key_insert_newpersonal(AvlTree_Personal *tree)
{
    assert(tree != NULL); // Check arguments.

    // The new node.
    Personal_Node *new_node = make_personal_node();
  
    if(tree->root == NULL)
    {
        // Tree is empty, make the new node the root.
        tree->root = new_node;
        new_node->parent = NULL;
        // Adapt the height of the tree.
        tree->height = 0;
        // Increment number of nodes in tree.
        tree->number_of_nodes++;
        return 1;
    }
    else
    {
        // Traverse the tree.
        Personal_Node *active = tree->root;
    
        while(1)
        {
            if(new_node->phone_key < active->phone_key)
            {
	            // New node is expected to left of active.
	            if(active->left_child == NULL)
                {
	                // Insert to the left of active.
	                active->left_child = new_node;
	                new_node->parent = active;
	                // Increase number of nodes in tree.
	                tree->number_of_nodes++;
	                // Check balance and rebalance.
	                personal_check_in(tree, new_node);
	                // Update the height of the tree.
	                tree->height = tree->root->height;
	                return 1;
	            }

	        // Continue traversal.
	        active = active->left_child;
            }
            else if(new_node->phone_key > active->phone_key)
            {
	            // New node is expected to right of active.
	            if(active->right_child == NULL)
                {
	                // Insert to the right of active.
	                active->right_child = new_node;
                    new_node->parent = active;
                    // Increase number of nodes in tree.
                    tree->number_of_nodes++;
                    // Check balance and rebalance.
                    personal_check_in(tree, new_node);
                    // Update the height of the tree.
                    tree->height = tree->root->height;
                    return 1;
                }

                // Continue traversal.
                active = active->right_child; 
            }
            else
            {
                // Key already exists in tree. Insertion failure.
                return 0;
            }
        }
    }

    //Unreachable code under normal functioning
    printf("Critical error occured while inserting a new node.\n");
    exit(2);
}
int key_delete_personal(int key, AvlTree_Personal *tree)
{
    // Check arguments.
    assert(tree != NULL);

    // Pointer to the node to be deleted.
    Personal_Node *del_node = NULL;

    // Search for the key to be deleted.
    if(!search_by_key_personal(key, tree, &del_node))
    {
        // The key was not found, return unsuccessful deletion.
        return 0;
    }

    if(del_node)
    {
        // Pointer to the replacement node (for the deleted one).
        Personal_Node *repl = del_node->left_child;
        if(repl == NULL)
        {
            repl = del_node->right_child;
        }
        else
        {
        // Iterate until predecessor is found.
            while(repl->right_child)
            {
	            repl = repl->right_child;
            }
        }

        Personal_Node *rebalance = NULL;
        if(repl)
        {
            if(repl->parent != del_node) 
            {
                rebalance = repl->parent;
            }
            if(repl != del_node->right_child)
            {
	            repl->right_child = del_node->right_child;
	            if(del_node->right_child) 
                {
                    del_node->right_child->parent = repl;
                }
            }
            if(repl->parent != del_node)
            {
                repl->parent->right_child = repl->left_child;
                if(repl->left_child) 
                {
                    repl->left_child->parent = repl->parent;
                }
                repl->left_child = del_node->left_child;
                del_node->left_child->parent = repl;
            }
        }
        else
        {
            if(!rebalance && del_node->parent) 
            {
                rebalance = del_node->parent;
            }
        }
        // Point the parent of the deletion node to the replacement node.
        if(del_node->parent)
        {
            if(del_node->phone_key < del_node->parent->phone_key)
            {
	            // Deletion node is a left child of its parent.
	            del_node->parent->left_child = repl;
            }
            else
            {
                // Deletion node is a right child of its parent.
                del_node->parent->right_child = repl;
            }
            if(repl){repl->parent = del_node->parent;}
        }
        else
        {
            // Handeling the deletion of the root.
            tree->root = repl;
            if(repl) {repl->parent = NULL;}
        }

        // Call the rebalance procedure from the rebalance node on (if one exists).
        if(rebalance)
        {
            personal_check_out(tree, rebalance);
        }
        else
        {
            if(repl){personal_check_out(tree, repl);}
        }

        // Update the tree height.
        if(tree->root)
        {
            tree->height = tree->root->height;
        }
        else
        {
            tree->height = -1;
        }
        // Update the number of nodes in the tree.
        tree->number_of_nodes--;

        // Free the memory location and return.
        free(del_node);
        del_node = NULL;
        return 1;
    }

    //Unreachable code in normal circumstances
    printf("Critical error occured while deleting a node.\n");
    exit(2);
}   
int search_by_key_personal(int key, AvlTree_Personal *tree, Personal_Node **node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);
  
    // Check if the tree is empty.
    if(tree->root == NULL)
    {
        // Return a NULL-pointer on the node, and falsy.
        *node = NULL;
        return 0;
    }

    // Start traversing the tree.
    *node = tree->root;
    while(1)
    {
        if(key < (*node)->phone_key)
        {
            // Continue search to the left of the node.
            if((*node)->left_child == NULL)
            {
	            // Node not in tree, return.
	            return 0;
            }
            // Continue traversal.
            *node = (*node)->left_child;
        }
        else if(key > (*node)->phone_key)
        {
            // Continue search to the right of the node.
            if((*node)->right_child == NULL)
            {
	            // Node is not in tree, return.
	            return 0;
            }
            // Continue traversal.
            *node = (*node)->right_child;
        }
        else
        {
            // Found the node, return.
            return 1;
        }
    }

    //Unreachable code normally
    printf("Critical error occured while searching for a node.\n");
    exit(2);
}
int edit_by_key_personal(int key, AvlTree_Personal * tree)
{
    assert(tree!=NULL);
    Personal_Node* edit;
    if(!search_by_key_personal(key,tree,&edit))
    {
        printf("Node not found\n");
        return 0;
    }
    else
    {
        printf("You can only edit the name and email of a contact, if you wish to modify the phone number, please use delete function\n");
        char temp[50];
        printf("Enter the new name of the contact: \n");
        fgets(temp,50,stdin);
        strcpy(edit->name,temp);
        printf("Enter the email of contact: \n");
        fgets(temp,50,stdin);
        strcpy(edit->email,temp);
        return 1;
    }
}
void print_range_personal(Personal_Node* root,int k1,int k2)
{
    if(k1>k2) //ensures keys are in right order
    {
        int temp=k1;
        k1=k2;
        k2=temp;
    }
    if(root==NULL)
    {
        return;
    }
    if(k1<root->phone_key)
    {
        print_range_personal(root->left_child,k1,k2);
    }
    if(k1<=root->phone_key && k2>=root->phone_key)
    {
        print_node_personal(root);
    }
    print_range_personal(root->right_child,k1,k2);
}
Personal_Node* copy_node(Personal_Node* node)//create copy of data
{
    Personal_Node *new_node = (Personal_Node *)malloc(sizeof(Personal_Node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed while generating a new node.\n");
        exit(1); 
    }
    strcpy(new_node->name,node->name);
    strcpy(new_node->email,node->email);
    new_node->phone_key=node->phone_key;
    new_node->cont_type=PERSONAL_CONTACT;
    new_node->left_child = new_node->right_child = new_node->parent = NULL;
    new_node->height = 0;
    return new_node;
}
int insert_personal_by_name(AvlTree_Personal* tree,Personal_Node* node)
{
    assert(tree != NULL); // Check arguments.

    // The new node.
    Personal_Node *new_node = copy_node(node);
  
    if(tree->root == NULL)
    {
        // Tree is empty, make the new node the root.
        tree->root = new_node;
        new_node->parent = NULL;
        // Adapt the height of the tree.
        tree->height = 0;
        // Increment number of nodes in tree.
        tree->number_of_nodes++;
        return 1;
    }
    else
    {
        // Traverse the tree.
        Personal_Node *active = tree->root;
    
        while(1)
        {
            if(strcmpi(new_node->name,active->name)<0 || (strcmpi(new_node->name,active->name)==0 && new_node->phone_key<active->phone_key))
            {
	            // New node is expected to left of active.
	            if(active->left_child == NULL)
                {
	                // Insert to the left of active.
	                active->left_child = new_node;
	                new_node->parent = active;
	                // Increase number of nodes in tree.
	                tree->number_of_nodes++;
	                // Check balance and rebalance.
	                check_in_personal_name(tree, new_node);
	                // Update the height of the tree.
	                tree->height = tree->root->height;
	                return 1;
	            }

	        // Continue traversal.
	        active = active->left_child;
            }
            else if(strcmpi(new_node->name,active->name)>0 || (strcmpi(new_node->name,active->name)==0 && new_node->phone_key>active->phone_key))
            {
	            // New node is expected to right of active.
	            if(active->right_child == NULL)
                {
	                // Insert to the right of active.
	                active->right_child = new_node;
                    new_node->parent = active;
                    // Increase number of nodes in tree.
                    tree->number_of_nodes++;
                    // Check balance and rebalance.
                    check_in_personal_name(tree, new_node);
                    // Update the height of the tree.
                    tree->height = tree->root->height;
                    return 1;
                }

                // Continue traversal.
                active = active->right_child; 
            }
            else
            {
                // Key already exists in tree. Insertion failure.
                return 0;
            }
        }
    }

    //Unreachable code under normal functioning
    printf("Critical error occured while inserting a new node.\n");
    exit(2);   
}
void check_in_personal_name(AvlTree_Personal *tree, Personal_Node *node)
{
    assert(tree != NULL);
    assert(node != NULL);

    int bal = balance_personal(node); //get balance factor of this node

    if(node->parent == NULL) //if we're at root
    {
        return;
    }

    //get balance of parent
    Personal_Node *parent = node->parent;
    int p_bal = balance_personal(parent);

    // Check balance for correctness, rotating if necessary.
    if(strcmpi(node->name,parent->name)<0 || (strcmpi(node->name,parent->name)==0 && node->phone_key<parent->phone_key))
    {
        if(p_bal == 0)
        {
            // Exit
            return;
        }
        else if(p_bal == -1)
        {
        // Continue check at the parent.
        check_in_personal_name(tree, parent);
        }
        else if(p_bal < -1)
        {
            if(bal == -1)
            {
	            // Do a single right rotation.
	            rotate_right_personal_name(tree, parent);
            }
            else if(bal == 1)
            {
	            // Do a double rotation (left, right).
	            rotate_left_personal_name(tree, parent->left_child);
	            rotate_right_personal_name(tree, parent);
            }
            else
            {
	            //Unreachable code under normal circumstances
	            printf("Critical error occured in check_in procedure.\n");
	            exit(2);
            }
        }
        else
        {
            // Unreachable code under normal circumstances
            printf("Critical error occured in check_in procedure.\n");
            exit(2);
        }
    }
    else if(strcmpi(node->name,parent->name)>0 || (strcmpi(node->name,parent->name)==0 && node->phone_key>parent->phone_key))
    {
        if(p_bal <= 0)
        {
            // Exit 
            return;
        }
        else if(p_bal == 1)
        {
            // Continue check_in at the parent. 
            check_in_personal_name(tree, parent);
        }
        else if(p_bal > 1)
        {
            if(bal == 1)
            {
	            // Do a single left rotation. 
	            rotate_left_personal_name(tree, parent);
            }
            else if(bal == -1)
            {
	            // Do a double rotation (right, left).
	            rotate_right_personal_name(tree, parent->right_child);
	            rotate_left_personal_name(tree, parent);
            }
            else
            {
	            // Unreachable code under normal circumstances
	            printf("Critical error occured in check_in procedure.\n");
	            exit(2);
            }
        }   
        else
        {
            // Unreachable code under normal circumstances
            printf("Critical error occured in check_in procedure.\n");
            exit(2);
        }
    }
}

void rotate_right_personal_name(AvlTree_Personal *tree, Personal_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Personal_Node *l_child = node->left_child;

    // Do rotation.
    if(node->parent == NULL)
    {
        // Operating on root.
        tree->root = l_child;
        l_child->parent = NULL;
    }
    else
    {
        // Give the parent its new child.
        if(strcmpi(node->name,node->parent->name)<0 || (strcmpi(node->name,node->parent->name)==0 && node->phone_key<node->parent->phone_key))
        {
        // We are at left child.
        node->parent->left_child = l_child;
        }
        else if(strcmpi(node->name,node->parent->name)>0 || (strcmpi(node->name,node->parent->name)==0 && node->phone_key>node->parent->phone_key))
        {
        // We are at right child.
        node->parent->right_child = l_child;
        }
        l_child->parent = node->parent;
    }
    // Rearrange the children nodes.
    node->left_child = l_child->right_child;
    // If a child is there, adapt its parent.
    if(l_child->right_child)
    {
        l_child->right_child->parent = node;
    }
    l_child->right_child = node;
    node->parent = l_child;

    // Update the heights.
    if(node)
    {
        node->height = get_height_personal(node);
    }
    if(l_child)
    {
        if(l_child->left_child)
        {
            l_child->left_child->height = get_height_personal(l_child->left_child);
        }
        l_child->height = get_height_personal(l_child);
    }
}
void rotate_left_personal_name(AvlTree_Personal *tree, Personal_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Personal_Node *r_child = node->right_child;

    // Do rotation.
    if(node->parent == NULL)
    {
        // Operating on root.
        tree->root = r_child;
        r_child->parent = NULL;
    }
    else
    {
        // Give the parent its new child.
        if(strcmpi(node->name,node->parent->name)<0 || (strcmpi(node->name,node->parent->name)==0 && node->phone_key<node->parent->phone_key))
        {
            // We are at left child.
            node->parent->left_child = r_child;
        }
        else if(strcmpi(node->name,node->parent->name)>0 || (strcmpi(node->name,node->parent->name)==0 && node->phone_key>node->parent->phone_key))
        {
            // We are at right child.
            node->parent->right_child = r_child;
        }
        r_child->parent = node->parent;
    }
    // Rearrange the children nodes.
    node->right_child = r_child->left_child;
    // If a child is there, adapt its parent.
    if(r_child->left_child) 
    {
        r_child->left_child->parent = node;
    }
    r_child->left_child = node;
    node->parent = r_child;

    // Update the heights.
    if(node)
    {
        node->height = get_height_personal(node);
    }
    if(r_child)
    {
        if(r_child->right_child)
        {
            r_child->right_child->height = get_height_personal(r_child->right_child);
        }
        r_child->height = get_height_personal(r_child);
    }
}
void create_name_tree_personal(AvlTree_Personal* tree,Personal_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    insert_personal_by_name(tree,root);
    create_name_tree_personal(tree,root->left_child);
    create_name_tree_personal(tree,root->right_child);
}
void clean_personal(AvlTree_Personal* tree)
{
    cleaner_personal(tree->root);
    free(tree);
}
void cleaner_personal(Personal_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    cleaner_personal(root->left_child);
    cleaner_personal(root->right_child);
    free(root);
}