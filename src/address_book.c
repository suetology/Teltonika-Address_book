#include "address_book.h"

#include <stdlib.h>
#include <string.h>
#include <signal.h>

struct Person *list = NULL;
unsigned program_opened;

void terminate_signal_handler(int signum)
{
        program_opened = 0;
}

int init_book() 
{
        program_opened = 1;

        signal(SIGINT, terminate_signal_handler);
        signal(SIGQUIT, terminate_signal_handler);

        int return_value = 0;
        char *home_dir = getenv("HOME");

        if (home_dir == NULL) {
                fprintf(stderr, "Unable to get the Home directory path\n");
                return_value = 1;
        } else {
                char *filename = "addresses.csv";
                char filepath[CAPACITY] = { 0 };

                strcat(filepath, home_dir);
                strcat(filepath, "/");
                strcat(filepath, filename);

                FILE *file = fopen(filepath, "r");
                if (file == NULL) {
                        fprintf(stderr, "Unable to open file: %s\n", filepath);
                        return_value = 2;
                } else {
	                load_list(file, &list);
                        fclose(file);
                } 
        }
        return return_value;
}

unsigned is_program_opened() 
{
        return program_opened;
}

void show_menu() 
{
        printf("Show all addresses.............1\n");
        printf("Find address by name...........2\n");
        printf("Find address by surname........3\n");
        printf("Find address by email..........4\n");
        printf("Find address by phone number...5\n");
        printf("Add a new address..............6\n");
        printf("Delete an address..............7\n");
        printf("Delete all addresses...........8\n");
        printf("Exit program...................9\n");
        printf("Choose an option by entering a number:\n");
}

unsigned get_menu_input()
{
        unsigned decision = 0;

        while (1) {
                scanf("%1u", &decision);
                while (getchar() != '\n');

                if (decision >= 1 && decision <= 9)
                        break;

                fprintf(stderr, "There is no such option, try again:\n");
        }
        return decision;
}

void choose_option(unsigned option)
{
        switch (option) {
        case 1:
                show_all_addresses();
                break;
        case 2:
                find_address_by_name();
                break;
        case 3:
                find_address_by_surname();
                break;
        case 4:
                find_address_by_email();
                break;
        case 5:
                find_address_by_phone();
                break;
        case 6:
                add_address();
                break;
        case 7:
                delete_address();
                break;
        case 8:
                delete_all_addresses();
                break;
        case 9:
                exit_program();
                break;
        default:
                break;
        }
}

void show_all_addresses() 
{
        if (list == NULL) {
                printf("The list is empty\n");
                return;
        }
        print_list(list);
}

void find_address_by_name()
{
        char name[CAPACITY];

        printf("Enter a seach name:\n");
        scanf("%29s", name);
        while (getchar() != '\n');

        struct Person *address = find_by_name(list, name);
        if (address == NULL)
                printf("There are no addresses with such name\n");
        else
                print_node(address);
}

void find_address_by_surname()
{
        char surname[CAPACITY];

        printf("Enter a seach surname:\n");
        scanf("%29s", surname);
        while (getchar() != '\n');

        struct Person *address = find_by_surname(list, surname);
        if (address == NULL)
                printf("There are no addresses with such surname\n");
        else
                print_node(address);
}

void find_address_by_email()
{
        char email[CAPACITY];

        printf("Enter a seach email:\n");
        scanf("%29s", email);
        while (getchar() != '\n');

        struct Person *address = find_by_email(list, email);
        if (address == NULL)
                printf("There are no addresses with such email\n");
        else
                print_node(address);
}

void find_address_by_phone()
{
        char phone[CAPACITY];

        printf("Enter a seach phone number:\n");
        scanf("%29s", phone);
        while (getchar() != '\n');

        struct Person *address = find_by_phone(list, phone);
        if (address == NULL)
                printf("There are no addresses with such phone number\n");
        else
                print_node(address);
}

void add_address()
{
        char decision = 0;
        printf("Enter \"p\" or \"P\" to add address to a specific position. Otherwise it will be added to the end of the book\n");
        scanf("%c", &decision);
        while (getchar() != '\n');

        if (decision != 'p' && decision != 'P') {
                struct Person *new_address = enter_address();
                if (new_address == NULL) {
                        fprintf(stderr, "Something went wrong...\n");
                        return;
                }
                add_to_list(&list, new_address);
                return;
        }
        int pos = 0;
        printf("Enter the index of a new address:\n");
        scanf("%d", &pos);
        while (getchar() != '\n');

        struct Person *new_address = enter_address();
        if (new_address == NULL) {
                fprintf(stderr, "Something went wrong...\n");
                return;
        }
        add_to_list_at(&list, new_address, pos);
}

struct Person *enter_address() 
{
        char name[CAPACITY];
	char surname[CAPACITY];
	char email[CAPACITY];
	char phone[CAPACITY];

        printf("Enter name: ");
        scanf("%29s", name);
        printf("Enter surname: ");
        scanf("%29s", surname);
        printf("Enter email: ");
        scanf("%29s", email);
        printf("Enter phone number: ");
        scanf("%29s", phone);
        while (getchar() != '\n');

        return create_node(name, surname, email, phone);
}

void delete_address()
{
        int pos = 0;
        printf("Enter the index of an address to delete:\n");
        scanf("%d", &pos);
        while (getchar() != '\n');

        delete_at(&list, pos);
}

void delete_all_addresses()
{
        delete_list(&list);
}

unsigned program_should_close()
{
        char decision = 0;
        printf("Enter \"c\" or \"C\" to continue work:\n");
        scanf("%c", &decision);
        while (getchar() != '\n');

        if (decision != 'c' && decision != 'C') {
                program_opened = 0;
        }       
}

void exit_program() 
{
        delete_all_addresses();
        exit(0);    
}