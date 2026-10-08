#include "inverted_search.h"

void display_database(hash *ht)
{
    int found = 0;
    mainnode *temp;
    subnode *sub_temp;

    printf("\n");
    for (int i = 0; i < HASH_SIZE; i++)
    {
        if (ht[i].link != NULL)
        {
            temp = ht[i].link;
            while (temp != NULL)
            {
                found = 1;
                printf("[%d] [%s] %d file(s) : file : ", i, temp->word, temp->file_count);

                sub_temp = temp->sub_link;
                while (sub_temp != NULL)
                {
                    printf("%s : %d time(s)", sub_temp->f_name, sub_temp->word_count);
                    if (sub_temp->link != NULL)
                    {
                        printf(" : ");
                    }
                    sub_temp = sub_temp->link;
                }
                printf("\n");
                temp = temp->link;
            }
        }
    }

    if (found == 0)
    {
        printf("Database is empty\n");
    }
    printf("\n");
}/* Updated: 2026-10-08 */
