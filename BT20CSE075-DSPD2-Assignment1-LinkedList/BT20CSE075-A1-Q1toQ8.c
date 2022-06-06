#include"Phonebook.h"
int main()//In this function Q1-8 are demonstrated
{
    //creating 2 phonebooks so demo of union is possible
    Phonebook example1;
    Phonebook example2;
    //initialisation
    srand(time(0));
    int type_choice,choice,book_choice;
    type contact_type;
    example1.head_personal=NULL;
    example1.head_professional=NULL;
    example2.head_personal=NULL;
    example2.head_professional=NULL;
    //UI
    printf("This is the Assignment1 submission of DSPD2 by roll no. BT20CSE075\n----------------Welcome-----------------------\n");
    printf("___________Menu_____________\n");
    printf("0.Exit\n1.Add a new contact\n2.Edit a contact's details\n3.Delete a contact\n4.Search a contact\n5.Display sorted\n6.Print contact list\n7.Merge both phonebooks\n8.Remove Duplicates\n");
    do
    {
        printf("Select an action between 0-8 from the menu: ");
        scanf("%d",&choice);
        fflush(stdin);
        switch (choice)
        {
        case 1:
            printf("Do you want to enter data in Phonebook 1 or 2: ");
            scanf("%d",&book_choice);
            printf("Press 0 for personal and 1 for professional contact: ");
            scanf("%d",&type_choice);
            contact_type = type_choice;
            fflush(stdin);
            if(book_choice==1)
            {
                insert_contact(&example1,contact_type);
            }
            else if(book_choice==2)
            {
                insert_contact(&example2,contact_type);
            }
            break;
        case 2:
            printf("do you want to edit data in Phonebook 1 or 2: ");
            scanf("%d",&book_choice);
            printf("Press 0 for personal and 1 for professional contact: ");
            scanf("%d",&type_choice);
            contact_type = type_choice;
            fflush(stdin);
            if(book_choice==1)
            {
                edit_contact(&example1,contact_type);
            }
            else if(book_choice==2)
            {
                edit_contact(&example2,contact_type);
            }
            break;
        case 3:
            printf("do you want to delete from Phonebook 1 or 2: ");
            scanf("%d",&book_choice);
            printf("Press 0 for personal and 1 for professional contact: ");
            scanf("%d",&type_choice);
            contact_type = type_choice;
            fflush(stdin);
            if(book_choice==1)
            {
                delete_contact(&example1,contact_type);
            }
            else if(book_choice==2)
            {
                delete_contact(&example2,contact_type);
            }
            break;
        case 4:
            printf("do you want to search in Phonebook 1 or 2: ");
            scanf("%d",&book_choice);
            printf("Press 0 for personal and 1 for professional contact: ");
            scanf("%d",&type_choice);
            contact_type = type_choice;
            fflush(stdin);
            if(book_choice==1)
            {
                search(&example1,contact_type);
            }
            else if(book_choice==2)
            {
                insert_contact(&example2,contact_type);
            }
            break;
        case 5:
            printf("do you want to view sorted Phonebook 1 or 2: ");
            scanf("%d",&book_choice);
            printf("Press 0 for personal and 1 for professional contact: ");
            scanf("%d",&type_choice);
            contact_type = type_choice;
            fflush(stdin);
            if(book_choice==1)
            {
                display_sorted(&example1,contact_type);
            }
            else if(book_choice==2)
            {
                display_sorted(&example2,contact_type);
            }
            break;
        case 6:
            printf("do you want to display data from Phonebook 1 or 2: ");
            scanf("%d",&book_choice);
            printf("Press 0 for personal and 1 for professional contact: ");
            scanf("%d",&type_choice);
            contact_type = type_choice;
            fflush(stdin);
            if(book_choice==1)
            {
                print_phonebook(&example1,contact_type);
            }
            else if(book_choice==2)
            {
                print_phonebook(&example2,contact_type);
            }
            break;
        case 7: ;//has to be done so we can declare variable
            int confirmation;
            printf("this will merge the 2 lists but empty the second one, press 1 to proceed: ");
            scanf("%d",&confirmation);
            fflush(stdin);
            if(confirmation==1)
            {
                union_phonebooks(&example1,&example2);
            }
            break;
        case 8:
            printf("do you want to remove duplicates from Phonebook 1 or 2: ");
            scanf("%d",&book_choice);
            printf("Press 0 for personal and 1 for professional contact: ");
            scanf("%d",&type_choice);
            contact_type = type_choice;
            fflush(stdin);
            if(book_choice==1)
            {
                remove_duplicates(&example1,contact_type);
            }
            else if(book_choice==2)
            {
                remove_duplicates(&example2,contact_type);
            }
            break;        
        default:
            break;
        }
    } while (choice);
    //clean the heap manually at exit
    clean_phonebook(&example1);
    clean_phonebook(&example2);
}