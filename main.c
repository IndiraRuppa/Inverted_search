#include "inverted_search.h"

// it will read buffer input until '\n' or EOF
void clear_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main(int argc, char *argv[])
{
    hash hash_table[HASH_SIZE];
    filename *head = NULL;
    int choice = 0, created = 0, ret;

    // hash table is an array of 28 entries, each holds the address of its first main node
    init_hash_table(hash_table);

    if (validate_args(argc, argv, &head) == FAILURE)
    {
        return 1;
    }

    while (choice != 6)
    {
        printf("\n1. Create database\n");
        printf("2. Display database\n");
        printf("3. Search database\n");
        printf("4. Save database\n");
        printf("5. Update database\n");
        printf("6. Exit\n");
        printf("Enter your choice : ");

        ret = scanf("%d", &choice);
        if (ret == EOF)
            break;
        clear_buffer();
        if (ret != 1)
            choice = 0;

        if (choice >= 2 && choice <= 5 && created == 0)
        {
            printf("Database is not created, choose option 1 first\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                if (created == 1)
                    printf("Database is already created\n");
                else
                {
                    create_database(head, hash_table);
                    created = 1;
                }
                break;
            case 2:
                display_database(hash_table);
                break;
            case 3:
                search_database(hash_table);
                break;
            case 4:
                save_database(hash_table, head);
                break;
            case 5:
                update_database(hash_table, &head);
                break;
            case 6:
                break;
            default:
                printf("Invalid choice, enter 1 to 6\n");
        }
    }                               /* end of while loop */

    free_database(hash_table);
    free_file_list(head);
    return 0;
}