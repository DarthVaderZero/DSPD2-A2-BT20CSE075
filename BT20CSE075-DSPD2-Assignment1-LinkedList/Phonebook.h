#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> //needed for demo of q9
#define SIZE 50
typedef enum{PERSONAL,PROFESSONAL}type;
typedef enum{FAILURE,SUCCESS}status_code;
typedef struct node_type1
{
    char name[SIZE];
    char mobile_number[SIZE];
    char email[SIZE];
    struct node_type1* next;
    type contact_type;
    int call_time;
}personalcontact;

typedef struct node_type2
{
    char name[SIZE];
    char mobile_number[SIZE];
    char email[SIZE];
    char office_number[SIZE];
    char office[SIZE];
    struct node_type2* next;
    type contact_type;
    int call_time;
}professionalcontact;

typedef struct node_type3
{
    personalcontact* head_personal;
    professionalcontact* head_professional;
}Phonebook; //Phonebook will hold the head pointers of both datalists

//Question 1 functions
void set_personal_data(personalcontact* ptr);
void set_professional_data(professionalcontact* ptr);
personalcontact* create_node_pers();
professionalcontact* create_node_prof();
personalcontact* insert_in_personal_list(personalcontact* nptr,personalcontact* ptrptr);
professionalcontact* insert_in_professional_list(professionalcontact* nptr,professionalcontact* ptrptr);
status_code insert_contact(Phonebook* pptr,type create_type);//contact_type to decide to in personal or professional
//end question 1
//Q2 edit
void edit_personal_details(personalcontact* lptr,char name[SIZE],char mobile[SIZE]);
void edit_professional_details(professionalcontact* lptr,char name[SIZE],char mobile[SIZE]);
void edit_contact(Phonebook* pptr,type edit_type);
//end Q2
//Q3 delete
personalcontact* delete_personal(personalcontact* lptr,char delete_name[SIZE],char delete_mobile[SIZE]);
professionalcontact* delete_professional(professionalcontact* lptr,char delete_name[SIZE],char delete_mobile[SIZE]);
void delete_contact(Phonebook* pptr, type delete_type);
//end Q3
//Q4 search
personalcontact* search_person(personalcontact* lptr,char* search_value);
professionalcontact* search_professional(professionalcontact* lptr,char* search_value);
void search(Phonebook* pptr,type search_type);
//end Q4
//Q5 sort
void display_descending_personal(personalcontact* lptr);
void display_descending_professional(professionalcontact* lptr);
void display_ascending_personal(personalcontact* lptr);
void display_ascending_professional(professionalcontact* lptr);
void display_sorted(Phonebook* pptr,type sort_type);
//end
//Q6 print
void print_personal_node(personalcontact* ptr);
void print_professional_node(professionalcontact* ptr);
void print_phonebook(Phonebook* pptr, type print_type);
//End question 6
//Q7 union
personalcontact* merge_person_list(personalcontact* A,personalcontact* B);
professionalcontact* merge_professional_list(professionalcontact* A,professionalcontact* B);
void union_phonebooks(Phonebook* pptr1,Phonebook* pptr2);
//end Q7
//Q8 duplicates
void remove_dupe_personal(personalcontact* lptr);
void remove_dupe_professional(professionalcontact* lptr);
void remove_duplicates(Phonebook* pptr,type remove_type);
//end Q8 
//cleaner
void clean_personal_list(personalcontact* lptr);
void clean_professional_list(professionalcontact* lptr);
void clean_phonebook(Phonebook* ptr);