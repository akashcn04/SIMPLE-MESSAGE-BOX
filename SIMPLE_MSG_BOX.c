#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_LENGTH 100

// Structure to represent a message
typedef struct Message {
    char *sender;
    char *receiver;
    char *content;
    time_t timestamp;
    struct Message *next;
} Message;

// Function to create a new message
Message *createMessage(char *sender, char *receiver, char *content) {
    // Allocate memory for a new message
    Message *newMessage = (Message *)malloc(sizeof(Message));
    if (!newMessage) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    // Initialize message fields
    newMessage->sender = strdup(sender);
    newMessage->receiver = strdup(receiver);
    newMessage->content = strdup(content);
    newMessage->timestamp = time(NULL);
    newMessage->next = NULL;
    return newMessage;
}

// Function to send a message and add it to the message box
void sendMessage(Message **head, char *sender, char *receiver, char *content) 
{
    // Create a new message
    Message *newMessage = createMessage(sender, receiver, content);
    // If message box is empty, set the new message as the head
    if (*head == NULL) {
        *head = newMessage;
    } else {
        // Traverse to the end of the message box
        Message *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Add the new message at the end
        current->next = newMessage;
    }
}

// Function to receive messages for a specific receiver
void receiveMessages(Message *head, char *receiver) {
    Message *current = head;
    int count = 0;

    printf("Messages for %s:\n", receiver);
    while (current != NULL) 
    {
        if (strcmp(current->receiver, receiver) == 0) {
            // Display sender, content, and timestamp of the message
            printf("Sender: %s\n", current->sender);
            printf("Content: %s\n", current->content);
            printf("Timestamp: %s", ctime(&(current->timestamp)));
            printf("--------------------\n");
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("No messages found for %s\n", receiver);
    }
}

// Function to free memory allocated for messages
void freeMessages(Message *head) {
    Message *current = head;
    while (current != NULL) {
        Message *temp = current;
        current = current->next;
        // Free memory for sender, receiver, content, and the message itself
        free(temp->sender);
        free(temp->receiver);
        free(temp->content);
        free(temp);
    }
}

// Main function
int main() {
    Message *messageBox = NULL;
    char sender[MAX_INPUT_LENGTH];
    char receiver[MAX_INPUT_LENGTH];
    char content[MAX_INPUT_LENGTH];
     int choice;
    // Menu-driven messaging system
    do {
        printf("1. Send message\n 2. Receive messages\n 3. CLEAR_MESSEGES\n");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the buffer

        switch (choice) {
            case 1:
                printf("Enter sender: ");
                fgets(sender, sizeof(sender), stdin);
                sender[strcspn(sender, "\n")] = '\0'; // Remove newline character
                printf("Enter receiver: ");
                fgets(receiver, sizeof(receiver), stdin);
                receiver[strcspn(receiver, "\n")] = '\0'; // Remove newline character
                printf("Enter message content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0'; // Remove newline character
                sendMessage(&messageBox, sender, receiver, content);
                break;
            case 2:
                printf("Enter receiver: ");
                fgets(receiver, sizeof(receiver), stdin);
                receiver[strcspn(receiver, "\n")] = '\0'; // Remove newline character
                receiveMessages(messageBox, receiver);
                break;
            case 3:
                freeMessages(messageBox);
                messageBox=NULL;
                break;
        }
    }while(choice<=3);
    return 0;
}
