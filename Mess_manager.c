//Check if it works; if it doesn't, let me know.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 100
#define MAX_NAME_LENGTH 50

struct TMember {
    char name[MAX_NAME_LENGTH];
    float balance;
};

struct TMess {
    struct TMember members[MAX_MEMBERS];
    int member_count;
};

void initialize_mess(struct TMess *mess);
void add_member(struct TMess *mess, const char *name);
void remove_member(struct TMess *mess, const char *name);
void display_members(struct TMess *mess);
void add_expense(struct TMess *mess, float amount);
void show_balance(struct TMess *mess, const char *name);

int main() {
    struct TMess mess;
    initialize_mess(&mess);

    int choice;
    char name[MAX_NAME_LENGTH];
    float amount;

    printf("Welcome to the Mess Management System!\n");

    do {
        printf("\nMenu:\n1. Add member\n2. Remove member\n3. Display members\n4. Add expense\n5. Show balance\n0. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the new member: ");
                scanf("%s", name);
                add_member(&mess, name);
                break;

            case 2:
                printf("Enter the name of the member to remove: ");
                scanf("%s", name);
                remove_member(&mess, name);
                break;

            case 3:
                display_members(&mess);
                break;

            case 4:
                printf("Enter the expense amount: ");
                scanf("%f", &amount);
                add_expense(&mess, amount);
                break;

            case 5:
                printf("Enter the name of the member: ");
                scanf("%s", name);
                show_balance(&mess, name);
                break;

            case 0:
                printf("Exiting the Mess Management System. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

void initialize_mess(struct TMess *mess) {
    mess->member_count = 0;
}

void add_member(struct TMess *mess, const char *name) {
    if (mess->member_count >= MAX_MEMBERS) {
        printf("Maximum member capacity reached. Cannot add more members.\n");
        return;
    }

    for (int i = 0; i < mess->member_count; ++i) {
        if (strcmp(mess->members[i].name, name) == 0) {
            printf("Member already exists.\n");
            return;
        }
    }

    strcpy(mess->members[mess->member_count].name, name);
    mess->members[mess->member_count].balance = 0.0;
    mess->member_count++;

    printf("Member '%s' added successfully.\n", name);
}

void remove_member(struct TMess *mess, const char *name) {
    int found = 0;
    for (int i = 0; i < mess->member_count; ++i) {
        if (strcmp(mess->members[i].name, name) == 0) {
            found = 1;
            for (int j = i; j < mess->member_count - 1; ++j) {
                strcpy(mess->members[j].name, mess->members[j + 1].name);
                mess->members[j].balance = mess->members[j + 1].balance;
            }
            mess->member_count--;
            printf("Member '%s' removed successfully.\n", name);
            break;
        }
    }

    if (!found) {
        printf("Member '%s' not found.\n", name);
    }
}

void display_members(struct TMess *mess) {
    printf("Members and their balances:\n");
    for (int i = 0; i < mess->member_count; ++i) {
        printf("%s: %.2f\n", mess->members[i].name, mess->members[i].balance);
    }
}

void add_expense(struct TMess *mess, float amount) {
    if (mess->member_count == 0) {
        printf("Cannot add expense. No members in the mess.\n");
        return;
    }

    float share = amount / mess->member_count;
    for (int i = 0; i < mess->member_count; ++i) {
        mess->members[i].balance += share;
    }

    printf("Expense of %.2f added and distributed among all members.\n", amount);
}

void show_balance(struct TMess *mess, const char *name) {
    int found = 0;
    for (int i = 0; i < mess->member_count; ++i) {
        if (strcmp(mess->members[i].name, name) == 0) {
            found = 1;
            printf("Balance for member '%s': %.2f\n", name, mess->members[i].balance);
            break;
        }
    }

    if (!found) {
        printf("Member '%s' not found.\n", name);
    }
}
