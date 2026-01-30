#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 20

// Structure to store passenger details using a Linked List [cite: 450, 634]
struct Passenger {
    int seatNo;
    char name[50];
    int age;
    struct Passenger *next;
};

struct Passenger *head = NULL;
int seats[MAX_SEATS]; // Array to track seat availability (0=Free, 1=Booked) [cite: 450, 641]

void bookTicket() {
    int i, seatNo = -1;
    char name[50];
    int age;

    // Search for the first available seat [cite: 591, 647]
    for (i = 0; i < MAX_SEATS; i++) {
        if (seats[i] == 0) {
            seatNo = i + 1;
            break;
        }
    }

    if (seatNo == -1) {
        printf("\nAll seats are booked! No seats available.\n"); [cite: 656]
        return;
    }

    printf("\nEnter Passenger Name: ");
    scanf(" %[^\n]", name); [cite: 658]
    printf("Enter Age: ");
    scanf("%d", &age); [cite: 660]

    // Mark seat as booked and allocate memory for passenger node [cite: 593, 661-662]
    seats[seatNo - 1] = 1;
    struct Passenger *newP = (struct Passenger *)malloc(sizeof(struct Passenger));
    newP->seatNo = seatNo;
    strcpy(newP->name, name);
    newP->age = age;
    newP->next = NULL;

    // Insert into linked list [cite: 598, 667-674]
    if (head == NULL) {
        head = newP;
    } else {
        struct Passenger *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newP;
    }

    printf("\nTicket booked successfully! Seat No: %d\n", seatNo); [cite: 676]
}

void cancelTicket() {
    if (head == NULL) {
        printf("\nNo bookings yet!\n"); [cite: 681]
        return;
    }

    int option;
    printf("\nCancel Ticket By:\n1. Seat Number\n2. Passenger Name\nEnter choice: "); [cite: 684]
    scanf("%d", &option);

    struct Passenger *temp = head, *prev = NULL;

    if (option == 1) {
        int seatNo;
        printf("\nEnter Seat Number to Cancel: "); [cite: 690]
        scanf("%d", &seatNo);

        if (seatNo < 1 || seatNo > MAX_SEATS || seats[seatNo - 1] == 0) {
            printf("\nInvalid Seat Number or Seat not booked.\n"); [cite: 694]
            return;
        }

        while (temp != NULL && temp->seatNo != seatNo) {
            prev = temp;
            temp = temp->next;
        }
    } else if (option == 2) {
        char name[50];
        printf("\nEnter Passenger Name: "); [cite: 703]
        scanf(" %[^\n]", name);

        while (temp != NULL && strcmp(temp->name, name) != 0) { [cite: 706]
            prev = temp;
            temp = temp->next;
        }
    } else {
        printf("\nInvalid option.\n"); [cite: 713]
        return;
    }

    if (temp == NULL) {
        printf("\nPassenger not found!\n"); [cite: 716]
        return;
    }

    // Update linked list and free memory [cite: 604-605, 719-727]
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    seats[temp->seatNo - 1] = 0;
    printf("\nTicket for Seat No %d (Passenger: %s) cancelled successfully!\n", 
           temp->seatNo, temp->name); [cite: 725]
    free(temp);
}

void viewPassengerList() {
    if (head == NULL) {
        printf("\nNo passengers booked yet!\n"); [cite: 733]
        return;
    }

    printf("\n=== Passenger List ===\n"); [cite: 735]
    struct Passenger *temp = head;
    while (temp != NULL) {
        printf("Seat No: %2d | Name: %-20s | Age: %d\n", 
               temp->seatNo, temp->name, temp->age); [cite: 738-739]
        temp = temp->next;
    }
}

void viewAvailableSeats() {
    printf("\n=== Available Seats ===\n"); [cite: 837]
    for (int i = 0; i < MAX_SEATS; i++) {
        printf("Seat %d [%s]\n", i + 1, seats[i] == 0 ? "Available" : "Booked"); [cite: 612-613, 838-857]
    }
}

int main() {
    int choice;
    for (int i = 0; i < MAX_SEATS; i++) seats[i] = 0; [cite: 580, 745]

    while (1) {
        printf("\n====== Railway/Bus Reservation System ======\n"); [cite: 748]
        printf("1. Book Ticket\n2. Cancel Ticket\n3. View Available Seats\n"); [cite: 749-751]
        printf("4. View Passenger List\n5. Exit\nEnter your choice: "); [cite: 752-754]
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break; [cite: 758]
            case 2: cancelTicket(); break; [cite: 759]
            case 3: viewAvailableSeats(); break; [cite: 760]
            case 4: viewPassengerList(); break; [cite: 761]
            case 5: printf("Goodbye!\n"); exit(0); [cite: 627, 762]
            default: printf("\nInvalid choice! Try again.\n"); [cite: 763]
        }
    }
    return 0;
}
