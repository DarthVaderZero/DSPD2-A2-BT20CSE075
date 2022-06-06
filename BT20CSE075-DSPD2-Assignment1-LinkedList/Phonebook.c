#include"Phonebook.h"
//Question 1 functions
void set_personal_data(personalcontact* ptr) //setter functions
{
    printf("Enter the Name of contact: \n");
    fgets(ptr->name,SIZE,stdin);
    printf("Enter the mobile number of contact: \n");
    fgets(ptr->mobile_number,SIZE,stdin);
    printf("Enter the email of contact: \n");
    fgets(ptr->email,SIZE,stdin);
    ptr->contact_type=PERSONAL;
    ptr->call_time = rand()%21; //sets call time to random value between 0-20 minutes,for demonstration of Q9
}
void set_professional_data(professionalcontact* ptr)
{
    printf("Enter the Name of contact: \n");
    fgets(ptr->name,SIZE,stdin);
    printf("Enter the mobile number of contact: \n");
    fgets(ptr->mobile_number,SIZE,stdin);
    printf("Enter the email of contact: \n");
    fgets(ptr->email,SIZE,stdin);
    printf("Enter the office number of contact: \n");
    fgets(ptr->office_number,SIZE,stdin);
    printf("Enter the office of contact: \n");
    fgets(ptr->office,SIZE,stdin);
    ptr->contact_type=PROFESSONAL;
    ptr->call_time=rand()%21; //sets call time to random value between 0-20 minutes,for demonstration of Q9
}
personalcontact* create_node_pers() //constructors for nodes
{
    personalcontact* nptr;
    nptr = (personalcontact*)malloc(sizeof(personalcontact));
    if(nptr!=NULL)
    {
        set_personal_data(nptr);
    }
    return nptr;
}
professionalcontact* create_node_prof()
{
    professionalcontact* nptr;
    nptr = (professionalcontact*)malloc(sizeof(professionalcontact));
    if(nptr!=NULL)
    {
        set_professional_data(nptr);
    }
    return nptr;
}
personalcontact* insert_in_personal_list(personalcontact* nptr,personalcontact* ptrptr)
{
    personalcontact *head = ptrptr;
    personalcontact *current = head;
    personalcontact *previous = NULL;
    nptr->next = NULL;
    int is_done = 0;
    int is_new_head = 0;
    if(head==NULL)
    {
        head=nptr;
    }
    else
    {
        while(!is_done && current!=NULL)//linear traversel+sorted insertion
        {
            if(strcasecmp(nptr->name,current->name)>0)
            {
                previous = current;
                current=current->next;
            }
            else if(strcasecmp(nptr->name,current->name)<0)
            {
                if(previous!=NULL)//we have traversed into the list
                {
                    previous->next=nptr;
                }
                else
                {
                    is_new_head=1;
                }
                nptr->next=current;
                is_done=1;
            }
            else if(strcasecmp(nptr->name,current->name)==0)
            {
                if (strcmp(nptr->mobile_number, current->mobile_number) > 0)
                {
                    if (current->next == NULL)
                    {
                        current->next = nptr;
                        is_done = 1;
                    }
                    else
                    {
                        nptr->next = current->next;
                        current->next = nptr;
                        is_done = 1;
                    }
                }
                else
                {
                    if (previous!= NULL)
                    {
                        previous->next = nptr;
                    }
                    else
                    {
                        is_new_head = 1;
                    }
                    nptr->next = current;
                    is_done = 1;
                }
            }
        }
        if(current==NULL)
        {
            previous->next=nptr;
        }
        if(is_new_head)
        {
            head=nptr;
        }
    }
    ptrptr = head;
    printf("Data inserted in personal list\n");
    return ptrptr;
}
professionalcontact* insert_in_professional_list(professionalcontact* nptr,professionalcontact* ptrptr)//same code but different pointer type
{
    professionalcontact *head = ptrptr;
    professionalcontact *current = head;
    professionalcontact *previous = NULL;
    nptr->next = NULL;
    int is_done = 0;
    int is_new_head = 0;
    if(head==NULL)
    {
        head=nptr;
    }
    else
    {
        while(!is_done && current!=NULL)//linear traversel+sorted insertion
        {
            if(strcasecmp(nptr->name,current->name)>0)
            {
                previous = current;
                current=current->next;
            }
            else if(strcasecmp(nptr->name,current->name)<0)
            {
                if(previous!=NULL)//we have traversed into the list
                {
                    previous->next=nptr;
                }
                else
                {
                    is_new_head=1;
                }
                nptr->next=current;
                is_done=1;
            }
            else if(strcasecmp(nptr->name,current->name)==0)
            {
                if (strcmp(nptr->mobile_number, current->mobile_number) > 0)
                {
                    if (current->next == NULL)
                    {
                        current->next = nptr;
                        is_done = 1;
                    }
                    else
                    {
                        nptr->next = current->next;
                        current->next = nptr;
                        is_done = 1;
                    }
                }
                else
                {
                    if (previous!= NULL)
                    {
                        previous->next = nptr;
                    }
                    else
                    {
                        is_new_head = 1;
                    }
                    nptr->next = current;
                    is_done = 1;
                }
            }
        }
        if(current==NULL)
        {
            previous->next=nptr;
        }
        if(is_new_head)
        {
            head=nptr;
        }
    }

    ptrptr = head;
    printf("Data inserted in professional list\n");
    return ptrptr;
}
status_code insert_contact(Phonebook* pptr,type create_type)
{   
    status_code SC = SUCCESS;
    if(create_type==PERSONAL)
    {
        personalcontact* nptr = create_node_pers();
        if(nptr==NULL)
        {
            SC=FAILURE;
        }
        else
        {
            pptr->head_personal=insert_in_personal_list(nptr,pptr->head_personal);
        }
        return SC;
    }
    if(create_type==PROFESSONAL)
    {
        professionalcontact* nptr = create_node_prof();
        if(nptr==NULL)
        {
            SC=FAILURE;
        }
        else
        {
            pptr->head_professional=insert_in_professional_list(nptr,pptr->head_professional);
        }
        return SC;
    }
}
//end Question 1
//search functions
personalcontact* search_person(personalcontact* lptr,char search_value[SIZE])
{
    personalcontact* retval;
    int flag=0;
    if(lptr==NULL)
    {
        printf("Empty personal list\n");
        retval = NULL;
    }
    personalcontact* temp = lptr;
    while (temp!=NULL&&!flag);
    {
        if(strcasecmp(temp->mobile_number,search_value)==0) //we search by phone number as it is the unique value for each contact 
        {
            printf("Match Found\n");
            retval=temp;
            flag=1;
        }
        temp=temp->next;
    }
    if(!flag)
    {
        printf("No matching key\n");
        retval = NULL;
    }
    return retval;
}
professionalcontact* search_professional(professionalcontact* lptr,char search_value[SIZE])
{
    professionalcontact* retval;
    int flag=0;
    if(lptr==NULL)
    {
        printf("Empty personal list\n");
        retval = NULL;
    }
    professionalcontact* temp = lptr;
    while (temp!=NULL)
    {
        if(strcasecmp(temp->mobile_number,search_value)==0) //we search by phone number as it is the unique value for each contact 
        {
            printf("Match Found\n");
            retval=temp;
            flag=1;
        }
        temp=temp->next;
    }
    if(!flag)
    {
        printf("No matching key\n");
        retval = NULL;
    }
    return retval;
}
void search(Phonebook* pptr,type search_type)
{
    char search_key[SIZE];
    printf("Enter the mobile number to be searched: ");
    fgets(search_key,SIZE,stdin);
    if(search_type == PERSONAL)
    {
        personalcontact* search_result = search_person(pptr->head_personal,search_key);
        if(search_result!=NULL)
        {
            print_personal_node(search_result);
        }
    }
    if(search_type == PROFESSONAL)
    {
        professionalcontact* search_result = search_professional(pptr->head_professional,search_key);
        if(search_result!=NULL)
        {
            print_professional_node(search_result);
        }
    }
}
//end search functions
//Delete functions
personalcontact* delete_personal(personalcontact* lptr,char delete_name[SIZE],char delete_mobile[SIZE])
{
    personalcontact* nptr = lptr;
    personalcontact* previous=NULL,* current=nptr;
    int is_done=0;
    while(!is_done && current!=NULL)
    {
        if(strcasecmp(delete_name,current->name)==0 && strcasecmp(delete_mobile,current->mobile_number)==0)
        {
            if(previous==NULL)
            {
                nptr = current->next;
                free(current);
            }
            else if(current->next==NULL)
            {
                previous->next = NULL;
                free(current);
            }
            else
            {
                previous->next=current->next;
                free(current);
            }
            is_done=1;
            printf("Contact found and successfully deleted\n");
        }
        previous=current;
        current=current->next;
    }
    if(!is_done)
    {
        printf("Contact with details not found to be deleted\n");
    }
    return nptr;
}
professionalcontact* delete_professional(professionalcontact* lptr,char delete_name[SIZE],char delete_mobile[SIZE])
{
    professionalcontact* nptr = lptr;
    professionalcontact* previous=NULL,* current=nptr;
    int is_done=0;
    while(!is_done && current!=NULL)
    {
        if(strcasecmp(delete_name,current->name)==0 && strcasecmp(delete_mobile,current->mobile_number)==0)
        {
            if(previous==NULL)
            {
                nptr = current->next;
                free(current);
            }
            else if(current->next==NULL)
            {
                previous->next = NULL;
                free(current);
            }
            else
            {
                previous->next=current->next;
                free(current);
            }
            is_done=1;
            printf("Contact found and successfully deleted\n");
        }
        previous=current;
        current=current->next;
    }
    if(!is_done)
    {
        printf("Contact with details not found to be deleted\n");
    }
    return nptr;
}
void delete_contact(Phonebook* pptr, type delete_type)
{
    char delete_name[SIZE],delete_mobile[SIZE];
    printf("Enter the Name of contact to delete: ");
    fgets(delete_name,SIZE,stdin);
    printf("Enter the Phone number of the contact to delete: ");
    fgets(delete_mobile,SIZE,stdin);
    if (delete_type==PERSONAL)
    {
        pptr->head_personal=delete_personal(pptr->head_personal,delete_name,delete_mobile);
    }
    if(delete_type==PROFESSONAL)
    {
        pptr->head_professional=delete_professional(pptr->head_professional,delete_name,delete_mobile);
    }
    
}
//end delete
//Edit function
void edit_personal_details(personalcontact* lptr,char name[SIZE],char mobile[SIZE]) //allows modification of fields that are not sorting keys
{
    personalcontact* nptr = lptr;
    int is_done=0;
    while(!is_done && nptr!=NULL)
    {
        if(strcasecmp(nptr->name,name)==0 && strcasecmp(nptr->mobile_number,mobile)==0)
        {
            printf("You can modify the email.Please enter the new email: ");
            fgets(nptr->email,SIZE,stdin);
            is_done=1;
        }
        nptr = nptr->next;
    }
    if(!is_done)
    {
        printf("Contact to edit not found\n");
    }
}
void edit_professional_details(professionalcontact* lptr,char name[SIZE],char mobile[SIZE]) //allows modification of fields that are not sorting keys
{
    professionalcontact* nptr = lptr;
    int is_done=0;
    while(!is_done&&nptr==NULL)
    {
        if(strcasecmp(nptr->name,name)==0 && strcasecmp(nptr->mobile_number,mobile)==0)
        {
            printf("You can modify the email.Please enter the new email: ");
            fgets(nptr->email,SIZE,stdin);
            printf("You can modify the office number.Please enter the new office number: ");
            fgets(nptr->office_number,SIZE,stdin);
            printf("You can modify the office name.Please enter the new office name: ");
            fgets(nptr->office,SIZE,stdin);
            is_done=1;
        }
        nptr = nptr->next;
    }
    if(!is_done)
    {
        printf("Contact to edit not found\n");
    }
}
void edit_contact(Phonebook* pptr,type edit_type)
{
    printf("!!!!!NOTE:You cannot edit the phone number and name of any contact as they are sorting keys, only other details!!!!!\n");
    printf("If you wish to modify the keys,please use delete and create to add a updated contact\n");
    char edit_name[SIZE],edit_mobile[SIZE];
    printf("Enter the Name of contact to edit: ");
    fgets(edit_name,SIZE,stdin);
    printf("Enter the Phone number of the contact to edit: ");
    fgets(edit_mobile,SIZE,stdin);
    if(edit_type==PERSONAL)
    {
        edit_personal_details(pptr->head_personal,edit_name,edit_mobile);
    }
    if(edit_type==PROFESSONAL)
    {
        edit_professional_details(pptr->head_professional,edit_name,edit_mobile);
    }
}
//Sort function-since list created in phonebook is always stored sorted, no seperate sorting is needed,instead ascending and desscending can be displayed as needed
void display_descending_personal(personalcontact* lptr)
{
    if(lptr==NULL)
    {
        return;
    }
    display_descending_personal(lptr->next);
    print_personal_node(lptr);
}
void display_descending_professional(professionalcontact* lptr)
{
    if(lptr==NULL)
    {
        return;
    }
    display_descending_professional(lptr->next);
    print_professional_node(lptr);
}
void display_ascending_personal(personalcontact* lptr)
{
    if(lptr==NULL)
    {
        return;
    }    
    print_personal_node(lptr);
    display_ascending_personal(lptr->next);
}
void display_ascending_professional(professionalcontact* lptr)
{
    if(lptr==NULL)
    {
        return;
    }
    print_professional_node(lptr);
    display_ascending_professional(lptr->next);
}
void display_sorted(Phonebook* pptr,type sort_type)
{   
    int disp_style;
    printf("enter 0 to display in ascending order namewise, 1 to display in descending order namewise: ");
    scanf("%d",&disp_style);
    if(sort_type==PERSONAL)
    {
        switch (disp_style)
        {
        case 0:
            display_ascending_personal(pptr->head_personal);
            break;
        case 1:
            display_descending_personal(pptr->head_personal);
        }
    }
    else if(sort_type==PROFESSONAL)
    {
        switch (disp_style)
        {
        case 0:
            display_ascending_professional(pptr->head_professional);
            break;
        case 1:
            display_descending_professional(pptr->head_professional);
        }
    }
}
//end sorted 
//Question 6
void print_personal_node(personalcontact* ptr)
{
    if(ptr!=NULL)
    {
        fputs(ptr->name,stdout);
        fputs(ptr->mobile_number,stdout);
        fputs(ptr->email,stdout);
        printf("call time: %d\n",ptr->call_time);
        fputs("__________________________________________\n",stdout);
    }
    else
    {
        printf("NULL node\n");
    }
}
void print_professional_node(professionalcontact* ptr)
{
    if(ptr!=NULL)
    {
        fputs(ptr->name,stdout);
        fputs(ptr->mobile_number,stdout);
        fputs(ptr->email,stdout);
        fputs(ptr->office,stdout);
        fputs(ptr->office_number,stdout);
        printf("call time: %d\n",ptr->call_time);
        fputs("__________________________________________\n",stdout);
    }
    else
    {
        printf("NULL node\n");
    }
}
void print_phonebook(Phonebook* pptr, type print_type)
{
    if(print_type==PERSONAL)
    {
        personalcontact* temp = pptr->head_personal;
        while(temp!=NULL)
        {
            print_personal_node(temp);
            temp=temp->next;
        }
    }
    if(print_type==PROFESSONAL)
    {
        professionalcontact* temp = pptr->head_professional;
        while(temp!=NULL)
        {
            print_professional_node(temp);
            temp=temp->next;
        }
    }
}
//end Q6
//Q7 union
personalcontact* merge_person_list(personalcontact* A,personalcontact* B)
{
    if(A==NULL)
    {
        return B;
    }
    else if(B==NULL)
    {
        return A;
    }

    personalcontact* mergedptr = NULL;
    if(strcasecmp(A->name,B->name)<0) //name in A before name in B
    {
        mergedptr=A;
        A=A->next;
    }
    else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A < B
    {
        mergedptr=A;
        A=A->next;
    }
    else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A > B
    {
        mergedptr=B;
        B=B->next;
    }
    else
    {
        mergedptr=B;
        B=B->next;
    }
    personalcontact* mergedend=mergedptr;
    while(A!=NULL && B!=NULL)
    {
        personalcontact* temp=NULL;
        if(strcasecmp(A->name,B->name)<0) //name in A before name in B
        {
            temp=A;
            A=A->next;
        }
        else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A < B
        {
            temp=A;
            A=A->next;
        }
        else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A > B
        {
            temp=B;
            B=B->next;
        }
        else
        {
            temp=B;
            B=B->next;
        }
        mergedend->next=temp;
        mergedend=temp;
    }
    if(A != NULL)
    {
        mergedend->next=A;
    }
    else if(B!=NULL)
    {
        mergedend->next=B;
    }
    printf("Personal lists merged\n");
    return mergedptr;
}
professionalcontact* merge_professional_list(professionalcontact* A,professionalcontact* B)
{
    if(A==NULL)
    {
        return B;
    }
    else if(B==NULL)
    {
        return A;
    }

    professionalcontact* mergedptr = NULL;
    if(strcasecmp(A->name,B->name)<0) //name in A before name in B
    {
        mergedptr=A;
        A=A->next;
    }
    else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A < B
    {
        mergedptr=A;
        A=A->next;
    }
    else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A > B
    {
        mergedptr=B;
        B=B->next;
    }
    else
    {
        mergedptr=B;
        B=B->next;
    }
    professionalcontact* mergedend=mergedptr;
    while(A!=NULL && B!=NULL)
    {
        professionalcontact* temp=NULL;
        if(strcasecmp(A->name,B->name)<0) //name in A before name in B
        {
            temp=A;
            A=A->next;
        }
        else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A < B
        {
            temp=A;
            A=A->next;
        }
        else if(strcasecmp(A->name,B->name)==0 && strcasecmp(A->mobile_number,B->mobile_number)<=0)//name in A same as B, but number in A > B
        {
            temp=B;
            B=B->next;
        }
        else
        {
            temp=B;
            B=B->next;
        }
        mergedend->next=temp;
        mergedend=temp;
    }
    if(A != NULL)
    {
        mergedend->next=A;
    }
    else if(B!=NULL)
    {
        mergedend->next=B;
    }
    printf("Professional lists merged\n");
    return mergedptr;
}
void union_phonebooks(Phonebook* pptr1,Phonebook* pptr2)
{
    printf("!!!THIS FUNCTION WILL MERGE THE PHONEBOOKS INTO THE FIRST ONE,THE SECOND PHONEBOOK WILL BECOME EMPTY!!!\n");
    pptr1->head_personal=merge_person_list(pptr1->head_personal,pptr2->head_personal);
    pptr1->head_professional=merge_professional_list(pptr1->head_professional,pptr2->head_professional);
    pptr2->head_personal=NULL;
    pptr2->head_professional=NULL;//makes sure no dangling pointers remain
}
//end Q7
//Q8 remove duplicates
void remove_dupe_personal(personalcontact* lptr)
{
    personalcontact* current = lptr;
    personalcontact* next_connect = NULL;
    if(current==NULL)
    {
        return;
    }
    while(current->next!=NULL)
    {
        if(strcasecmp(current->name,current->next->name)==0 && strcasecmp(current->mobile_number,current->next->mobile_number)==0)
        {
            next_connect=current->next->next;
            free(current->next);
            current->next=next_connect;
        }
        else
        {
            current=current->next;
        }
    }
}
void remove_dupe_professional(professionalcontact* lptr)
{
    professionalcontact* current = lptr;
    professionalcontact* next_connect = NULL;
    if(current==NULL)
    {
        return;
    }
    while(current->next!=NULL)
    {
        if(strcasecmp(current->name,current->next->name)==0 && strcasecmp(current->mobile_number,current->next->mobile_number)==0)
        {
            next_connect=current->next->next;
            free(current->next);
            current->next=next_connect;
        }
        else
        {
            current=current->next;
        }
    }
}
void remove_duplicates(Phonebook* pptr,type remove_type)
{
    if(remove_type==PERSONAL)
    {
        remove_dupe_personal(pptr->head_personal);
    }
    else if(remove_type==PROFESSONAL)
    {
        remove_dupe_professional(pptr->head_professional);
    }
}
//end Q8
//cleaner
void clean_personal_list(personalcontact* lptr)
{
    if(lptr==NULL)
    {
        return;
    }
    clean_personal_list(lptr->next);
    free(lptr);
}
void clean_professional_list(professionalcontact* lptr)
{
    if(lptr==NULL)
    {
        return;
    }
    clean_professional_list(lptr->next);
    free(lptr);
}
void clean_phonebook(Phonebook* ptr)
{
    clean_personal_list(ptr->head_personal);
    clean_professional_list(ptr->head_professional);
    ptr->head_personal=NULL;
    ptr->head_professional=NULL;
}