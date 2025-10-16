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

    // Insert node after position (0 index)
    void insert_after(int value, int position) {

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
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}