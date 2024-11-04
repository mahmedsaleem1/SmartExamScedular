#include "queue.h"
#include <iostream>

Queue::Queue(int capacity) {
    front = 0;
    rear = 0;
    size = 0;
    q.resize(capacity);
}

void Queue::enQueue(int data, const string& str) {
    if (!isFull()) {
        q[rear] = make_pair(data, str); // Store pair in queue
        rear++;
        size++;
    } else {
        cout << "Queue is Full" << endl;
    }
}

void Queue::deQueue() {
    if (!isEmpty()) {
        q[front] = make_pair(-1, ""); // Reset the pair
        front++;
        size--;
        if (front == rear) {
            front = 0;
            rear = 0;
        }
    } else {
        cout << "Queue is Empty" << endl;
    }
}

pair<int, string> Queue::Front() {
    if (!isEmpty()) {
        return q[front];
    } else {
        return make_pair(-1, ""); // Return a default pair if empty
    }
}

pair<int, string> Queue::Rear() {
    if (!isEmpty()) {
        return q[rear - 1];
    } else {
        return make_pair(-1, ""); // Return a default pair if empty
    }
}

bool Queue::isEmpty() {
    return (front == rear);
}

bool Queue::isFull() {
    return (rear == q.size());
}

int Queue::Size() {
    return size;
}
