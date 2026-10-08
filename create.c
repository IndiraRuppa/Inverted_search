#include "inverted_search.h"
void init_hash_table(hash *ht)
{
    for(int i=0;i<HASH_SIZE;i++)
    {
        ht[i].index=i;
        ht[i].link=NULL;
    }
}
//ind index of the word based on first character
int get_index(char ch)
{
    if (isupper(ch))
        return ch - 'A';
    if (islower(ch))
        return ch - 'a';
    if (isdigit(ch))
        return 26;
    return 27;
}

//create sub node
static subnode *create_subnode(char *filename)
{
    subnode *sub=malloc(sizeof(subnode));
    if(sub==NULL)
       return NULL;

    sub->word_count = 1;            // initial word count with 1 
    strcpy(sub->f_name, filename);  // store file name 
    sub->link = NULL;               // store NULL in sub node link 
    return sub;
}
//create main node
static mainnode *create_mainnode(char *word, subnode *sub)
{
    mainnode *main_node = malloc(sizeof(mainnode));
    if (main_node == NULL)
        return NULL;
 
    strcpy(main_node->word, word);  // store word 
    main_node->file_count = 1;      // initial file count with 1 
    main_node->sub_link = sub;      // link main node and sub node 
    main_node->link = NULL;
    return main_node;
}

//store one word of a file into the hash table
static int insert_word(hash *ht,char *word,char *filename)
{
    int index=get_index(word[0]);
    mainnode *temp=ht[index].link;
    mainnode *prev =NULL;
    subnode  *sub,*sub_prev,*new_sub;
    mainnode *new_main;

    while(temp!=NULL)
    {
        //word is present
        if(strcmp(temp->word,word)==0)
        {
          sub=temp->sub_link;   
          sub_prev=NULL;
        
        //compare the file name is present or not
           while(sub!=NULL)
           {
             if(strcmp(sub->f_name,filename)==0)
             {
                sub->word_count++;     //file name is present
                return SUCCESS;
             }
             sub_prev=sub;
             sub=sub->link;

           }
           //file name is not present : create sub node, insert at last
           new_sub=create_subnode(filename);
           if(new_sub==NULL)
           {
            return FAILURE;
           }
           if(sub_prev==NULL)
           {
            temp->sub_link=new_sub;
           }
           else
           {
            sub_prev->link=new_sub;
           }
           temp->file_count++;
           return SUCCESS;
        }
        prev=temp;
        temp=temp->link;
    }
//word is not present : create main node and sub node
    new_sub=create_subnode(filename);
     if(new_sub == NULL)
    {
    free(new_sub);
    return FAILURE;
    }
    new_main = create_mainnode(word, new_sub);
     if (new_main == NULL)
   {
    free(new_sub);
    return FAILURE;
   }

    //link main node with hash table
     if(prev==NULL)
    {
    ht[index].link=new_main;    //index was empty
    }
    else
    {
    prev->link=new_main;    //insert at last
   }
} 

//read all the words of one file and store them
int index_file(char *filename,hash *ht)
{
    char word[WORD_SIZE];
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("ERROR:%s cannot be opened\n",filename);
        return FAILURE;
    }
  while(fscanf(fp,"%49s",word)==1)
  {
     if (insert_word(ht, word, filename) == FAILURE)
        {
            printf("ERROR: memory not allocated\n");
            fclose(fp);
            return FAILURE;
        }
  }
    fclose(fp);
    printf("Database is created for %s\n", filename);
    return SUCCESS;
}

int create_database(filename *head, hash *ht)
{
    while (head != NULL)
    {
        index_file(head->filename, ht);
        head = head->link;
    }
    return SUCCESS;
}
 
void free_database(hash *ht)
{
    int i;
    mainnode *m, *m_next;
    subnode *s, *s_next;
 
    for (i = 0; i < HASH_SIZE; i++)
    {
        m = ht[i].link;
        while (m != NULL)
        {
            s = m->sub_link;
            while (s != NULL)
            {
                s_next = s->link;
                free(s);
                s = s_next;
            }
            m_next = m->link;
            free(m);
            m = m_next;
        }
        ht[i].link = NULL;
    }
}
 
void free_file_list(filename *head)
{
    filename *next;
    while (head != NULL)
    {
        next = head->link;
        free(head);
        head = next;
    }
}
 /* Updated: 2026-10-08 */
