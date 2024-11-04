#pragma once
#include <vector>
#include <string>
#include <utility> // For std::pair

using namespace std;

class Queue {
private:
    vector<pair<int, string>> q; // Change to pair<int, string>
    int front;
    int rear;
    int size;
public:
    Queue(int capacity); // Constructor
    void enQueue(int data, const string& str); // Update method signature
    void deQueue();
    pair<int, string> Front(); // Update return type
    pair<int, string> Rear(); // Update return type
    bool isEmpty();
    bool isFull();
    int Size();
};




