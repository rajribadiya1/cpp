#include <iostream>
using namespace std;

// Node structure (each node is stored in heap memory using new)
struct Node {
    int data;
    Node* next;
};

// CREATE: insert at end
void insertAtEnd(Node* &head, int value) {
    Node* newNode = new Node;      // dynamic allocation
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;            // first node
        return;
    }

    Node* temp = head;             // traverse to last node
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;          // link last->next to new node
}

// READ: display all nodes
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty\n";
        return;
    }
    cout << "Linked List: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// UPDATE: change first node with given oldValue to newValue
bool updateNode(Node* head, int oldValue, int newValue) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == oldValue) {
            temp->data = newValue;
            return true;
        }
        temp = temp->next;
    }
    return false;  // not found
}

// DELETE: delete first node with given value
bool deleteNode(Node* &head, int value) {
    if (head == nullptr) return false;

    // if head itself to be deleted
    if (head->data == value) {
        Node* toDelete = head;
        head = head->next;       // move head
        delete toDelete;         // free memory
        return true;
    }

    Node* prev = head;
    Node* curr = head->next;

    while (curr != nullptr && curr->data != value) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false; // not found

    prev->next = curr->next;   // unlink node
    delete curr;               // free memory
    return true;
}

// Free the whole list at end
void freeList(Node* &head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;   // empty list
    int choice, value, oldValue, newValue;

    do {
        cout << "\n--- Singly Linked List (CRUD) ---\n";
        cout << "1. Insert (Create)\n";
        cout << "2. Display (Read)\n";
        cout << "3. Update\n";
        cout << "4. Delete\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insertAtEnd(head, value);
                break;

            case 2:
                displayList(head);
                break;

            case 3:
                cout << "Enter value to update: ";
                cin >> oldValue;
                cout << "Enter new value: ";
                cin >> newValue;
                if (updateNode(head, oldValue, newValue))
                    cout << "Node updated successfully.\n";
                else
                    cout << "Value not found in list.\n";
                break;

            case 4:
                cout << "Enter value to delete: ";
                cin >> value;
                if (deleteNode(head, value))
                    cout << "Node deleted successfully.\n";
                else
                    cout << "Value not found in list.\n";
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    // free all remaining nodes before program ends
    freeList(head);
    return 0;
}
