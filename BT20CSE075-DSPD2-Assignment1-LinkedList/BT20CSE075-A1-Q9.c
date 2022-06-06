#include"Phonebook.h"
typedef struct Node_Q9
{
    Phonebook book;
    int total_call_time;
    struct Node_Q9* next;
    char name_owner[SIZE];
}Owner;
int get_total_call_time(Phonebook* pptr) //returns total time owner spent on calls, assigned during initialisation itself when phonebook is created
{
    int sum=0;
    personalcontact* nptr = pptr->head_personal;
    while(nptr!=NULL)
    {
        sum+=nptr->call_time; //traverse whole personal list and accumulate the call time
        nptr=nptr->next;
    }
    professionalcontact* lptr = pptr->head_professional;
    while(lptr!=NULL)
    {
        sum+=lptr->call_time;
        lptr=lptr->next;
    }
    return sum;
}
Owner* create_owner() //similar to constructor
{
    Owner* nptr;
    nptr = (Owner*)malloc(sizeof(Owner));
    if(nptr!=NULL)
    {
        printf("Enter the name of the Owner: ");
        fgets(nptr->name_owner,SIZE,stdin);
        //For demonstration purposes, I have assumed there to be only 2 personal and professional contacts in each owner's phonebook
        nptr->book.head_personal=NULL;
        nptr->book.head_professional=NULL;
        printf("Now enter Personal contacts: \n");
        insert_contact(&(nptr->book),PERSONAL);
        insert_contact(&(nptr->book),PERSONAL);
        printf("Now enter Professional contacts: \n");
        insert_contact(&(nptr->book),PROFESSONAL);
        insert_contact(&(nptr->book),PROFESSONAL);
        nptr->total_call_time=get_total_call_time(&(nptr->book));
        nptr->next=NULL;
        printf("Contacts for the owner added\n");
    }
    return nptr;
}
void insert_in_list(Owner** lptr,Owner* nptr) //returns the head of the linked list of Owners after insertion
{
    if(nptr==NULL)
    {
        return;
    }
    Owner* current;
    if(*lptr==NULL||(*lptr)->total_call_time<=nptr->total_call_time)
    {
        nptr->next=*lptr;
        *lptr=nptr;
    }
    else
    {
        current=*lptr;
        while(current->next!=NULL&&current->next->total_call_time>nptr->total_call_time)
        {
            current=current->next;
        }
        nptr->next=current->next;
        current->next=nptr;
    }
    printf("Owner Inserted\n");
}
void print_owner_list(Owner* lptr)
{
    Owner* temp = lptr;
    while(temp!=NULL)
    {
        fputs(temp->name_owner,stdout);
        printf("total call time: %d\n",temp->total_call_time);
        printf("_______________\n");
        temp=temp->next;
    }
}
int main()
{
    //initialisation
    srand(time(0));
    Owner* head=NULL;
    Owner* new_owner;
    //for demonstration purposes, here 5 owners are inserted in list, though this can be setup in loop for as many insertions as needed
    printf("Submission and Demonstration of Q9 of Assignment1 of DSPD2 by BT20CSE075.\n");
    printf("Below you will be prompted to create 5 owners and their phonebooks, after that the owners linked list is sorted by total call time in decreasing order.\n");
    new_owner = create_owner();
    insert_in_list(&head,new_owner);
    new_owner = create_owner();
    insert_in_list(&head,new_owner);
    new_owner = create_owner();
    insert_in_list(&head,new_owner);
    new_owner = create_owner();
    insert_in_list(&head,new_owner);
    new_owner = create_owner();
    insert_in_list(&head,new_owner);
    //printing the list to show that the owner list is in decreasing order
    print_owner_list(head);
}