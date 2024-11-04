#include "Stack.h"

// Constructor
Stack::Stack() {}

// Destructor
Stack::~Stack() {}

// Method to add an element x to the stack
void Stack::push(int x) {
    arr.push_back(x); // Add the element to the end of the vector
}

// Method to remove and return the top element
int Stack::pop() {
    if (isEmpty()) {
        throw out_of_range("Stack Underflow: No elements to pop");
    }
    int topElement = arr.back(); // Get the top element
    arr.pop_back();              // Remove the top element
    return topElement;
}

// Method to get the top element without removing it
int Stack::peek() const {
    if (isEmpty()) {
        throw out_of_range("Stack is empty: No elements to peek");
    }
    return arr.back(); // Return the top element
}

// Method to get the current stack size
int Stack::size() const {
    return arr.size(); // Return the size of the vector
}

// Method to check if the stack is empty
bool Stack::isEmpty() const {
    return arr.empty(); // Return true if the vector is empty
}

// Method to print all elements in the stack
void Stack::printStack() const {
    if (isEmpty()) {
        cout << "Stack is empty." << endl;
        return;
    }

    cout << "Stack elements (top to bottom): ";
    for (int i = arr.size() - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

