#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Stack {
private:
    vector<int> arr; // Vector to store stack elements

public:
    Stack();               // Constructor
    ~Stack();              // Destructor

    void push(int x);      // Add an element to the stack
    int pop();             // Remove and return the top element
    int peek() const;      // Get the top element without removing it
    int size() const;      // Get current stack size
    bool isEmpty() const;  // Check if the stack is empty
    void printStack() const; // Print all stack elements
};