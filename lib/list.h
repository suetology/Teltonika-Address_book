#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#define CAPACITY 30
#define DELIMETER ","

struct Person {
	char name[CAPACITY];
	char surname[CAPACITY];
	char email[CAPACITY];
	char phone[CAPACITY];

	struct Person *next;
};

struct Person *create_node(char *name, char *surname, char *email, char *phone);
struct Person *load_node(char *address_line);
void load_list(FILE *file, struct Person **list);
void print_node(struct Person *node);
void print_list(struct Person *list);
void add_to_list(struct Person **list, struct Person *new_address);
void add_to_list_at(struct Person **list, struct Person *new_address, int pos);
void delete_at(struct Person **list, int pos);
void delete_list(struct Person **list);
struct Person *find_at(struct Person *list, int pos);
struct Person *find_by_name(struct Person *list, char *name);
struct Person *find_by_surname(struct Person *list, char *surname);
struct Person *find_by_email(struct Person *list, char *email);
struct Person *find_by_phone(struct Person *list, char *phone);

#endif