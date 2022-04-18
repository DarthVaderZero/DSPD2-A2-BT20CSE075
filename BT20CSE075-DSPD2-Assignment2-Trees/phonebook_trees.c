#include"phonebook_trees.h"
#include<stdio.h>
void Initialise(phonebook_trees* book) //constructor
{
    book->tree_person = make_personal_tree_empty();
    book->tree_prof = make_Professional_tree_empty();
}
//make sure that all these functions can only be used after a phonebook has been instantiated
void Insert(phonebook_trees* book)
{
    printf("What type of contact do you want to insert?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    int status;
    scanf("%d",&choice);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            status=key_insert_newpersonal(book->tree_person);
            flag=1;
        }
        else if(choice==1)
        {
            status=key_insert_newProfessional(book->tree_prof);
            flag=1;
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    }
    if(status==1)
    {
        printf("insertion successful\n");
    }
}
void Edit(phonebook_trees* book)
{
    printf("What type of contact do you want to edit?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    int status,val;
    scanf("%d",&choice);
    printf("Enter the contact number whose details you want to edit: \n");
    scanf("%d",&val);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            status=edit_by_key_personal(val,book->tree_person);
            flag=1;
        }
        else if(choice==1)
        {
            status=edit_by_key_Professional(val,book->tree_prof);
            flag=1;
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    }
    if(status==1)
    {
        printf("editing successful\n");
    }
}
void Delete(phonebook_trees* book)
{
    printf("What type of contact do you want to delete?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    int status,val;
    scanf("%d",&choice);
    printf("Enter the contact number which you wish to delete: \n");
    scanf("%d",&val);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            status=key_delete_personal(val,book->tree_person);
            flag=1;
        }
        else if(choice==1)
        {
            status=key_delete_Professional(val,book->tree_prof);
            flag=1;
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    }
    if(status==1)
    {
        printf("deletion successful\n");
    }   
}
void Search(phonebook_trees* book)
{
    printf("What type of contact do you want to search?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    int status,val;
    scanf("%d",&choice);
    printf("Enter the contact number which you wish to search: \n");
    scanf("%d",&val);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            Personal_Node* temp;
            status=search_by_key_personal(val,book->tree_person,&temp);
            flag=1;
            if(status==1)
            {
                print_node_personal(temp);
            }
            else
            {
                printf("Node not found in personal tree\n");
            }
        }
        else if(choice==1)
        {
            Professional_Node* temp;
            status=search_by_key_Professional(val,book->tree_prof,&temp);
            flag=1;
            if(status==1)
            {
                print_node_Professional(temp);
            }
            else
            {
                printf("Node not found in professional tree\n");
            }
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    }   
}
void Display_sorted(phonebook_trees* book)
{
    printf("What contacts do you want to print?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    scanf("%d",&choice);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            int aord;
            printf("press 0 to print personal tree in ascending order, press 1 for descending: \n");
            scanf("%d",&aord);
            if(aord==0)
            {
                inorder_print_personal(book->tree_person);
                flag=1;
            }
            else if(aord==1)
            {
                inorder_print_personal_reverse(book->tree_person);
                flag=1;
            }
            else
            {
                printf("Enter 0 or 1 only\n");
                flag=0;
            }
        }
        else if(choice==1)
        {
            int aord;
            printf("press 0 to print professional tree in ascending order, press 1 for descending: \n");
            scanf("%d",&aord);
            if(aord==0)
            {
                inorder_print_Professional(book->tree_prof);
                flag=1;
            }
            else if(aord==1)
            {
                inorder_print_professional_reverse(book->tree_prof);
                flag=1;
            }
            else
            {
                printf("Enter 0 or 1 only\n");
                flag=0;
            }
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    }   
}
void Print_all(phonebook_trees* book)
{
    printf("What type of contact-list do you want to display?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    scanf("%d",&choice);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            inorder_print_personal(book->tree_person);
            flag=1;
        }
        else if(choice==1)
        {
            inorder_print_Professional(book->tree_prof);
            flag=1;
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    } 
}
void Range_search(phonebook_trees* book)
{
    printf("What type of contact-list do you want to display?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    scanf("%d",&choice);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            int k1,k2;
            printf("Enter the 2 phone numbers seperated by space: ");
            scanf("%d %d",&k1,&k2);
            print_range_personal(book->tree_person->root,k1,k2);
            flag=1;
        }
        else if(choice==1)
        {
            int k1,k2;
            printf("Enter the 2 phone numbers seperated by space: ");
            scanf("%d %d",&k1,&k2);
            print_range_prof(book->tree_prof->root,k1,k2);
            flag=1;
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    }   
}
void Sort_by_name(phonebook_trees* book)
{
    printf("What type of contact-list do you want to display?Press 0 for personal and 1 for professional: \n");
    int choice;
    int flag=0;
    scanf("%d",&choice);
    fflush(stdin);
    while(!flag)
    {
        if(choice==0)
        {
            AvlTree_Personal* temp = make_personal_tree_empty();
            create_name_tree_personal(temp,book->tree_person->root);
            inorder_print_personal(temp);
            clean_personal(temp);
            flag=1;
        }
        else if(choice==1)
        {
            AvlTree_Professional* temp = make_Professional_tree_empty();
            create_name_tree_Professional(temp,book->tree_prof->root);
            inorder_print_Professional(temp);
            clean_Professional(temp);
            flag=1;            
        }
        else
        {
            printf("Please choose 1 or 0\n");
            flag=0;
        }
    }  
}