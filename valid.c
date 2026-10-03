#include "inverted_search.h"

//file name should end with ".txt"
int txt_file(char *name)
{
    char *ext = strrchr(name, '.');

    //no dot in the name & only ".txt", no file name
    if (ext == NULL || ext == name)
    {
        return 0;
    }

    if (strcmp(ext, ".txt") != 0)
    {
        return 0;
    }
    return 1;
}

//check the file name is already present in the list or not
static int duplicate(filename *head, char *name)
{
    while (head != NULL)
    {
        if (strcmp(head->filename, name) == 0)
        {
            return 1;
        }
        head = head->link;
    }
    return 0;
}

//insert the file name at last of the list
static int insert_last(filename **head, char *name)
{
    filename *new = malloc(sizeof(filename));
    if (new == NULL)
    {
        return FAILURE;
    }
    strcpy(new->filename, name);
    new->link = NULL;

    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    filename *temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

int validate_file(char *name, filename **head)
{
    FILE *fp;

    //extension should be .txt only
    if (txt_file(name) == 0)
    {
        printf("ERROR: %s is not a .txt file\n", name);
        return FAILURE;
    }

    //file name should fit in the structure
    if (strlen(name) >= FNAME_SIZE)
    {
        printf("ERROR: %s file name is too long\n", name);
        return FAILURE;
    }

    //file should be present
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        printf("ERROR: %s file is not present\n", name);
        return FAILURE;
    }

    //at least one character should be present
    if (fgetc(fp) == EOF)
    {
        printf("ERROR: %s is an empty file\n", name);
        fclose(fp);
        return FAILURE;
    }
    fclose(fp);

    //duplicate file should not be present in the list
    if (duplicate(*head, name))
    {
        printf("ERROR: %s is a duplicate file\n", name);
        return FAILURE;
    }

    //valid file : insert into the list
    if (insert_last(head, name) == FAILURE)
    {
        printf("ERROR: memory not allocated\n");
        return FAILURE;
    }

    printf("%s is added to the file list\n", name);
    return SUCCESS;
}

int validate_args(int argc, char *argv[], filename **head)
{
    int i;

    if (argc < 2)
    {
        printf("Usage : %s file1.txt file2.txt ...\n", argv[0]);
        return FAILURE;
    }

    for (i = 1; i < argc; i++)
    {
        validate_file(argv[i], head);
    }

    if (*head == NULL)
    {
        printf("No valid files are present\n");
        return FAILURE;
    }
    return SUCCESS;
}