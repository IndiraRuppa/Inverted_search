#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define WORD_SIZE 50            //max word length incl. '\0' (fscanf uses %49s)
#define FNAME_SIZE 50           //max file name length incl. '\0'  
#define HASH_SIZE 28            //0-25 = a-z / A-Z, 26 = digits, 27 = others

#define  SUCCESS 1
#define  FAILURE 0
typedef int Status;

//List of validated file names
typedef struct file
{
    char filename[FNAME_SIZE];
    struct file *link;
}filename;

//Sub node: one per (word, file) pair
typedef struct sub
{
    int  word_count;
    char f_name[FNAME_SIZE];
    struct sub *link;
}subnode;

//Main node: one per unique wor
typedef struct mainnode
{
    int file_count;            //in how many files the word is present
    char word[WORD_SIZE];
    struct mainnode *link;     //next main node in the same hash index
    struct sub*sub_link;       //list of sub nodes  
}mainnode;

//Hash table entry
typedef struct
{
    int index;
    mainnode *link;
}hash;

// main.c
void clear_buffer(void);
//validate.c
int  txt_file( char *name);
int validate_file( char *name, filename **head);
int validate_args(int argc, char *argv[], filename **head);

//create_database
void   init_hash_table(hash *ht);
int    get_index(char ch);
int index_file( char *filename, hash *ht);
int create_database(filename *head, hash *ht);
void   free_database(hash *ht);
void   free_file_list(filename *head);


//other operations
void display_database(hash *ht);
void search_database(hash *ht);
void save_database(hash  *ht, filename *head);
void update_database(hash *ht, filename **head);


#endif/* Updated: 2026-10-08 */
