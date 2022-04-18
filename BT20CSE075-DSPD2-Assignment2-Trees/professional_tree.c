#include "professional_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<string.h>
//constructors
AvlTree_Professional * make_Professional_tree_from_node(Professional_Node *node)
{
    assert(node != NULL);
  

    AvlTree_Professional *tree = (AvlTree_Professional *)malloc(sizeof(AvlTree_Professional));
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
AvlTree_Professional *make_Professional_tree_empty()
{
    AvlTree_Professional *new_tree = (AvlTree_Professional *)malloc(sizeof(AvlTree_Professional));
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
Professional_Node * make_Professional_node()
{
    Professional_Node *new_node = (Professional_Node *)malloc(sizeof(Professional_Node));
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
    printf("Enter the office number of contact: \n");
    fgets(new_node->office_number,50,stdin);
    printf("Enter the name of office of contact: \n");
    fgets(new_node->office,50,stdin);
    new_node->cont_type=PROFESSIONAL_CONTACT;
    new_node->left_child = new_node->right_child = new_node->parent = NULL;
    new_node->height = 0;
    return new_node;
}
//avl checks
void Professional_check_in(AvlTree_Professional *tree, Professional_Node *node)
{
    assert(tree != NULL);
    assert(node != NULL);

    int bal = balance_Professional(node); //get balance factor of this node

    if(node->parent == NULL) //at root
    {
        return;
    }

    //get balance of parent
    Professional_Node *parent = node->parent;
    int p_bal = balance_Professional(parent);

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
        Professional_check_in(tree, parent);
        }
        else if(p_bal < -1)
        {
            if(bal == -1)
            {
	            // Do a single right rotation.
	            rotate_right_Professional(tree, parent);
            }
            else if(bal == 1)
            {
	            // Do a double rotation
	            rotate_left_Professional(tree, parent->left_child);
	            rotate_right_Professional(tree, parent);
            }
            else
            {
	            //Unreachable under normal functioning
	            printf("Critical error occured in check_in procedure.\n");
	            exit(2);
            }
        }
        else
        {
            //Unreachable under normal functioning
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
            Professional_check_in(tree, parent);
        }
        else if(p_bal > 1)
        {
            if(bal == 1)
            {
	            // Do a single left rotation. 
	            rotate_left_Professional(tree, parent);
            }
            else if(bal == -1)
            {
	            // Do a double rotation
	            rotate_right_Professional(tree, parent->right_child);
	            rotate_left_Professional(tree, parent);
            }
            else
            {
	            //Unreachable under normal functioning
	            printf("Critical error occured in check_in procedure.\n");
	            exit(2);
            }
        }   
        else
        {
	        //Unreachable under normal functioning
            printf("Critical error occured in check_in procedure.\n");
            exit(2);
        }
    }
}
void Professional_check_out(AvlTree_Professional *tree, Professional_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Keep track of the parent of the node.
    Professional_Node *parent = node->parent;
  
    // Get the balance of the current node.
    int bal = balance_Professional(node);

    if(bal < -1)
    {
        // get balance of its left child.
        int l_bal = balance_Professional(node->left_child);

        if(l_bal == -1)
        {
            //Fix by single right rotation.
            rotate_right_Professional(tree, node);
        }
        else if(l_bal == 1)
        {
            //Fix with a left-right rotation.
            rotate_left_Professional(tree, node->left_child);
            rotate_right_Professional(tree, node);
        }
        else
        {
            rotate_right_Professional(tree, node);
        }
    }
    else if(bal > 1)
    {

        // Figure out the balance of its right child.
        int r_bal = balance_Professional(node->right_child);

        if(r_bal == 1)
        {
            // Double right heavy imbalance. Fix with a single left rotation.
            rotate_left_Professional(tree, node);
        }
        else if(r_bal == -1)
        {
            // Right-Left imbalance. Fix with a right-left rotation.
            rotate_right_Professional(tree, node->right_child);
            rotate_left_Professional(tree, node);
        }
        else
        {
            rotate_left_Professional(tree, node);
        }
    }

    // Continue upwards traversal.
    if(parent) 
    {
        Professional_check_out(tree, parent);
    }
}
//utilities
inline int get_int_max_Professional(int a, int b)
{
    return (a > b) ? a : b;
}
int get_height_Professional(Professional_Node *node)
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
    return get_int_max_Professional(l_height, r_height) + 1;
}
int balance_Professional(Professional_Node *node)
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
    node->height = get_int_max_Professional(l_height, r_height) + 1;

    // Return the balance (height difference).
    return r_height - l_height;
}
void print_node_Professional(Professional_Node* node)
{
    if(node!=NULL)
    {
        fputs(node->name,stdout);
        printf("%d\n",node->phone_key);
        fputs(node->email,stdout);
        fputs(node->office,stdout);
        fputs(node->office_number,stdout);
        fputs("__________________________________________\n",stdout);
    }
}
void inorder_Professional(Professional_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    inorder_Professional(root->left_child);
    print_node_Professional(root);
    inorder_Professional(root->right_child);
}
void inorder_print_Professional(AvlTree_Professional* tree)
{
    fputs("This prints phonebook in ascending order\n",stdout);
    inorder_Professional(tree->root);
}
void inorder_professional_reverse(Professional_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    inorder_professional_reverse(root->right_child);
    print_node_Professional(root);
    inorder_professional_reverse(root->left_child);
}
void inorder_print_professional_reverse(AvlTree_Professional* tree)
{
    fputs("This prints phonebook in descending order\n",stdout);
    inorder_professional_reverse(tree->root);   
}
//rotations
void rotate_right_Professional(AvlTree_Professional *tree, Professional_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Professional_Node *l_child = node->left_child;

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
        // Adapt the parent.
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
        node->height = get_height_Professional(node);
    }
    if(l_child)
    {
        if(l_child->left_child)
        {
            l_child->left_child->height = get_height_Professional(l_child->left_child);
        }
        l_child->height = get_height_Professional(l_child);
    }
}
void rotate_left_Professional(AvlTree_Professional *tree, Professional_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Professional_Node *r_child = node->right_child;

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
        // Adapt the parent.
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
        node->height = get_height_Professional(node);
    }
    if(r_child)
    {
        if(r_child->right_child)
        {
            r_child->right_child->height = get_height_Professional(r_child->right_child);
        }
        r_child->height = get_height_Professional(r_child);
    }
}
//insert,delete,search
int key_insert_newProfessional(AvlTree_Professional *tree)
{
    assert(tree != NULL); // Check arguments.

    // The new node.
    Professional_Node *new_node = make_Professional_node();
  
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
        Professional_Node *active = tree->root;
    
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
	                Professional_check_in(tree, new_node);
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
                    Professional_check_in(tree, new_node);
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

	//Unreachable under normal functioning
    printf("Critical error occured while inserting a new node.\n");
    exit(2);
}
int key_delete_Professional(int key, AvlTree_Professional *tree)
{
    // Check arguments.
    assert(tree != NULL);

    // Pointer to the node to be deleted.
    Professional_Node *del_node = NULL;

    // Search for the key to be deleted.
    if(!search_by_key_Professional(key, tree, &del_node))
    {
        // The key was not found, return unsuccessful deletion.
        return 0;
    }

    if(del_node)
    {
        // Pointer to the replacement node (for the deleted one).
        Professional_Node *repl = del_node->left_child;
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

        Professional_Node *rebalance = NULL;
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
            Professional_check_out(tree, rebalance);
        }
        else
        {
            if(repl){Professional_check_out(tree, repl);}
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

	//Unreachable under normal functioning
    printf("Critical error occured while deleting a node.\n");
    exit(2);
}   
int search_by_key_Professional(int key, AvlTree_Professional *tree, Professional_Node **node)
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

    //Unreachable under normal functioning
    printf("Critical error occured while searching for a node.\n");
    exit(2);
}
int edit_by_key_Professional(int key, AvlTree_Professional * tree)
{
    assert(tree!=NULL);
    Professional_Node* edit;
    if(!search_by_key_Professional(key,tree,&edit))
    {
        printf("Node not found\n");
        return 0;
    }
    else
    {
        printf("You can only edit the details of a contact, if you wish to modify the phone number, please use delete function\n");
        char temp[50];
        printf("Enter the new name of the contact: \n");
        fgets(temp,50,stdin);
        strcpy(edit->name,temp);
        printf("Enter the email of contact: \n");
        fgets(temp,50,stdin);
        strcpy(edit->email,temp);
        printf("Enter the office of contact: \n");
        fgets(temp,50,stdin);
        strcpy(edit->office,temp);
        printf("Enter the office number of contact: \n");
        fgets(temp,50,stdin);
        strcpy(edit->office_number,temp);
        return 1;
    }
}
void print_range_prof(Professional_Node* root,int k1,int k2)
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
        print_range_prof(root->left_child,k1,k2);
    }
    if(k1<=root->phone_key && k2>=root->phone_key)
    {
        print_node_Professional(root);
    }
    print_range_prof(root->right_child,k1,k2);
}
Professional_Node* copy_node_2(Professional_Node* node)//create copy of data
{
    Professional_Node *new_node = (Professional_Node *)malloc(sizeof(Professional_Node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed while generating a new node.\n");
        exit(1); 
    }
    strcpy(new_node->name,node->name);
    strcpy(new_node->email,node->email);
    strcpy(new_node->office,node->office);
    strcpy(new_node->office_number,new_node->office_number);
    new_node->phone_key=node->phone_key;
    new_node->cont_type=PROFESSIONAL_CONTACT;
    new_node->left_child = new_node->right_child = new_node->parent = NULL;
    new_node->height = 0;
    return new_node;
}
int insert_professional_by_name(AvlTree_Professional* tree,Professional_Node* node)
{
    assert(tree != NULL); // Check arguments.

    // The new node.
    Professional_Node *new_node = copy_node_2(node);
  
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
        Professional_Node *active = tree->root;
    
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
	                check_in_professional_name(tree, new_node);
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
                    check_in_professional_name(tree, new_node);
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
void check_in_professional_name(AvlTree_Professional *tree, Professional_Node *node)
{
    assert(tree != NULL);
    assert(node != NULL);

    int bal = balance_Professional(node); //get balance factor of this node

    if(node->parent == NULL) //if we're at root
    {
        return;
    }

    //get balance of parent
    Professional_Node *parent = node->parent;
    int p_bal = balance_Professional(parent);

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
        check_in_professional_name(tree, parent);
        }
        else if(p_bal < -1)
        {
            if(bal == -1)
            {
	            // Do a single right rotation.
	            rotate_right_professional_name(tree, parent);
            }
            else if(bal == 1)
            {
	            // Do a double rotation (left, right).
	            rotate_left_professional_name(tree, parent->left_child);
	            rotate_right_professional_name(tree, parent);
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
            check_in_professional_name(tree, parent);
        }
        else if(p_bal > 1)
        {
            if(bal == 1)
            {
	            // Do a single left rotation. 
	            rotate_left_professional_name(tree, parent);
            }
            else if(bal == -1)
            {
	            // Do a double rotation (right, left).
	            rotate_right_professional_name(tree, parent->right_child);
	            rotate_left_professional_name(tree, parent);
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
void rotate_right_professional_name(AvlTree_Professional *tree, Professional_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Professional_Node *l_child = node->left_child;

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
        node->height = get_height_Professional(node);
    }
    if(l_child)
    {
        if(l_child->left_child)
        {
            l_child->left_child->height = get_height_Professional(l_child->left_child);
        }
        l_child->height = get_height_Professional(l_child);
    }
}
void rotate_left_professional_name(AvlTree_Professional *tree, Professional_Node *node)
{
    // Check arguments.
    assert(tree != NULL);
    assert(node != NULL);

    // Pointer to the second node in rotation.
    Professional_Node *r_child = node->right_child;

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
        node->height = get_height_Professional(node);
    }
    if(r_child)
    {
        if(r_child->right_child)
        {
            r_child->right_child->height = get_height_Professional(r_child->right_child);
        }
        r_child->height = get_height_Professional(r_child);
    }
}
void create_name_tree_Professional(AvlTree_Professional* tree,Professional_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    insert_professional_by_name(tree,root);
    create_name_tree_Professional(tree,root->left_child);
    create_name_tree_Professional(tree,root->right_child);
}
void clean_Professional(AvlTree_Professional* tree)
{
    cleaner_Professional(tree->root);
    free(tree);
}
void cleaner_Professional(Professional_Node* root)
{
    if(root==NULL)
    {
        return;
    }
    cleaner_Professional(root->left_child);
    cleaner_Professional(root->right_child);
    free(root);
}