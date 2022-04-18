#include"phonebook_trees.h"
#include<stdio.h>
int main()
{
    phonebook_trees myBook;
    int choice;
    Initialise(&myBook);
    //UI
    printf("This is the Assignment2 submission of DSPD2 by roll no. BT20CSE075\n----------------Welcome-----------------------\n");
    printf("___________Menu_____________\n");
    printf("0.Exit\n1.Add a new contact\n2.Edit a contact's details\n3.Delete a contact\n4.Search a contact\n5.Display sorted\n6.Print contact list\n7.Display in range\n8.Display sorted by name\n");
    do
    {
        printf("Select an action between 0-8 from the menu: ");
        scanf("%d",&choice);
        fflush(stdin);
        switch (choice)
        {
            case 1:
                Insert(&myBook);
                break;
            case 2:
                Edit(&myBook);
                break;
            case 3:
                Delete(&myBook);
                break;
            case 4:
                Search(&myBook);
                break;
            case 5:
                Display_sorted(&myBook);
                break;
            case 6:
                Print_all(&myBook);
                break;
            case 7:
                Range_search(&myBook);
                break;
            case 8:
                Sort_by_name(&myBook);
                break;
            case 0:
                printf("You will exit this program now.......");
                break;
            default:
                printf("Enter number between 0 to 7");
                break;
        }
    }while(choice!=0);
}