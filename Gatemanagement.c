#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char purpose[100];
    char time[20];
} Visitor;

Visitor visitors[MAX];
int count = 0;

void addVisitor() {
    if(count >= MAX) {
        printf("\nRecord full! Cannot add more visitors.\n");
        return;
    }

    printf("\nEnter Visitor Name: ");
    scanf(" %[^\n]", visitors[count].name);

    printf("Enter Purpose of Visit: ");
    scanf(" %[^\n]", visitors[count].purpose);

    printf("Enter Entry Time (HH:MM): ");
    scanf(" %[^\n]", visitors[count].time);

    count++;
    printf("\nVisitor record added successfully!\n");
}

void viewVisitors() {
    if(count == 0) {
        printf("\nNo visitor records found.\n");
        return;
    }

    printf("\n----- Visitor Records -----\n");
    for(int i = 0; i < count; i++) {
        printf("Visitor %d\n", i + 1);
        printf("Name: %s\n", visitors[i].name);
        printf("Purpose: %s\n", visitors[i].purpose);
        printf("Time: %s\n\n", visitors[i].time);
    }
}

void searchVisitor() {
    char searchName[50];
    int found = 0;

    printf("\nEnter name to search: ");
    scanf(" %[^\n]", searchName);

    for(int i = 0; i < count; i++) {
        if(strcmp(visitors[i].name, searchName) == 0) {
            printf("\nVisitor Found:\n");
            printf("Name: %s\n", visitors[i].name);
            printf("Purpose: %s\n", visitors[i].purpose);
            printf("Time: %s\n", visitors[i].time);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("\nVisitor not found.\n");
    }
}

int main() {
    int choice;

    while(1) {
        printf("\n----- GATE MANAGEMENT SYSTEM -----\n");
        printf("1. Add Visitor\n");
        printf("2. View All Visitors\n");
        printf("3. Search Visitor\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addVisitor(); break;
            case 2: viewVisitors(); break;
            case 3: searchVisitor(); break;
            case 4: 
                printf("\nExiting system...\n");
                exit(0);
            default: 
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
