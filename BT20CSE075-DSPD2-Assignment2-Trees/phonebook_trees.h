#include"personal_tree.h"
#include"professional_tree.h"

typedef struct phonebook
{
    AvlTree_Personal* tree_person;
    AvlTree_Professional* tree_prof;
}phonebook_trees;
void Initialise(phonebook_trees* book);
void Insert(phonebook_trees* book);
void Edit(phonebook_trees* book);
void Delete(phonebook_trees* book);
void Search(phonebook_trees* book);
void Display_sorted(phonebook_trees* book);
void Print_all(phonebook_trees* book);
void Range_search(phonebook_trees* book);
void Sort_by_name(phonebook_trees* book);