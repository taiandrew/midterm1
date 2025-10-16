#include <iostream>
using namespace std;

// Constants
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Class implementing a doubly linked list
class DoublyLinkedList {

// private data members: node struct (not instances) and head / tail ptrs
private:

    // struct for nodes
    struct Node {
        int data;       // Stores an integer
        Node* prev;     // Pointer to prev node
        Node* next;     // Pointer to next node

        // constructor for node; default next and prev are null
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // pointer to head node (first node)
    Node* tail; // pointer to tail node (last node)

// Public members: methods for operations on list
public:

    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    
    void insert_after(int value, int position) {
        // Insert node after position (0 index)
        // args:
        // - value: int to store in new node
        // - position: index after which to insert new node]

        // Validation: index must be at least 0
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // If list is empty, insert new node at head (and tail)
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        // Traverse to specified position
        Node* temp = head;      // Start at head
        for (int i = 0; i < position && temp; ++i)      // Loop up to i times, or until end
            temp = temp->next; // Move to next node

        // Bounds check: if temp->next was null above, position is past end
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;     // Clean up memry
            return;
        }

        // Insert new node after temp; note temp is pointer to node before desired position
        newNode->next = temp->next;      // New node points to temp's next
        newNode->prev = temp;            // New node points back to temp
        if (temp->next)                 
            temp->next->prev = newNode;   // If there is a node after temp (before insertion), it now points back to new node
        else
            tail = newNode;              // If not, new node is new tail
        temp->next = newNode;           // temp points to new node
    }

    void delete_val(int value) {
        // Delete first node with value
        // arg: value to delete

        // Empty list; don't do anything
        if (!head) return;

        // Traverse list to find value
        Node* temp = head;
        
        while (temp && temp->data != value) // Keep going until value or end
            temp = temp->next;

        if (!temp) return; // Value not found; don't do anything

        // Value found -- remove node and update adjacent pointers
        if (temp->prev)
            temp->prev->next = temp->next;  // If not head, previous node pionts to next node
        else
            head = temp->next;      // Else, update head

        if (temp->next)
            temp->next->prev = temp->prev;  // If not tail, next node points back to previous node
        else
            tail = temp->prev;    // Else, update tail

        delete temp; // Delete the node
    }

    void delete_pos(int pos) {
        // Delete node at position. NOTE: appears to be 1-indexed
        // arg: position of node to delete

        // Empty list; don't do anything
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        
        // Call pop_front if pos is 1
        if (pos == 1) {
            pop_front();
            return;
        }
        
        // Else, traverse to position
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){      // Loop up to pos-1 times
            if (!temp) { // Out of bounds (previous iteration temp->next was null)
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;      // Traverse
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;      // Out of bounds
            return;
        }
        
        // Temp happened to be tail; call pop_back()
        if (!temp->next) {
            pop_back();
            return;
        }
        
        // Else, node is strictly inside. Update adjacent pointers and delete.
        Node* tempPrev = temp->prev;  
        tempPrev->next = temp->next;    // Prev node points to node after temp
        temp->next->prev = tempPrev;    // Node after temp poitns back to prev node
        delete temp; // Delete the node
    }

    void push_back(int v) {
        // Add a node w/ value v to tail
        // Arg: value v to store

        // Initialize new node (with null pointers)
        Node* newNode = new Node(v);

        if (!tail) // List is empty; make new node head and tail
            head = tail = newNode;
        else {  // List is not empty...
            tail->next = newNode;   // former tail points to new node
            newNode->prev = tail;   // new node points back to former tail
            tail = newNode;  // Update tail pointer
        }
    }
    
    void push_front(int v) {
        // Add a node w/ value v to head
        // Arg: value v to store

        // Init new node w/ null ptrs
        Node* newNode = new Node(v);
        if (!head) // List is empty; make new node head and tail
            head = tail = newNode;
        else { // List is not empty...
            newNode->next = head; // new node points to the former head
            head->prev = newNode; // former head points back to new node
            head = newNode; // Update head pointer
        }
    }
    
    void pop_front() {
        // Remove node at head

        // Empty list; don't do anything
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        // update pointers and delete node
        Node * temp = head;

        if (head->next) { // List has >=2 nodes
            head = head->next; // Update head ptr to next node
            head->prev = nullptr; // New head's prev is null
        }
        else // List has 1 node; will be empty
            head = tail = nullptr;
        delete temp; // Delete the old head
    }

    void pop_back() {
        // Remove node at tail

        // Empty list; don't do anything
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }

        // update pointers and delete node
        Node * temp = tail;

        if (tail->prev) { // List has >=2 nodes
            tail = tail->prev; // Update tail ptr to prev node
            tail->next = nullptr; // New tail's next is null
        }
        else
            head = tail = nullptr; // List has 1 node; will be empty
        delete temp; // Delete node
    }


    // Destructor
    ~DoublyLinkedList() {
        while (head) {  // Traverse the list via while loop
            Node* temp = head; // Save ptr to this node to delete
            head = head->next; // Move head down to next
            delete temp; // Delete node
        }
    }

    // Print the whole list
    void print() {
        Node* current = head; // Start at head
        if (!current) { // Empty list
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   // Traverse list
            cout << current->data << " ";   // Print current node's value
            current = current->next; // Move to next node
        }
        cout << endl;
    }

    // Print whole list in reverse order
    void print_reverse() {
        Node* current = tail;   // Start at tail
        if (!current) {  // Empty list
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   // Traverse list backwards
            cout << current->data << " "; // Print value
            current = current->prev; // Move to previous node
        }
        cout << endl;
    }

    // ADDITION
    void every_other_element() {
        // Prints every other element, starting from head (even indexed)
        // Note: modification of print() fn

        // Start at head; check empty list
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        // Printing every other element
        int index = 0;          // Keep track of index
        while (current) {       // Traverse list
            if (index % 2 == 0)  // Even index
                cout << current->data << " ";
            current = current->next;
            index++;
        }
        cout << endl;

    }
};

// Main
int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    // Create a list for testing
    
    return 0;
}