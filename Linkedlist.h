#ifdef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <iostream>
#include <stdexcept>


//Do not use =this linked List!!!!!!


template <class T>
class LinkedList {
private:
    struct Node
    {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int length;

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~LinkedList() {
        while (head) {
            Node* nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }
    T& operator[](int index) {
        if (index >= length || index < 0) {
            throw std::invalid_argument("Index out of range.");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void append(T data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void insert(int index, T data) {
        if (index > length || index < 0) {
            throw std::invalid_argument("Index out of range.");
        }

        Node* newNode = new Node(data);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            if (length == 0) {
                tail = newNode;
            }
        } else {
            Node* prev = head;
            for (int i = 0; i < index - 1; i++) {
                prev = prev->next;
            }
            newNode->next = prev->next;
            prev->next = newNode;
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
        length++;
    }

    T pop() {
        if (!head) {
            throw std::out_of_range("List is empty.");
        }

        T data;
        if (head == tail) {
            data = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            data = tail->data;
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        length--;
        return data;
    }

    void remove(int index) {
        if (index >= length || index < 0) {
            throw std::invalid_argument("Index out of range.");
        }

        if (index == 0) {
            Node* toDelete = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete toDelete;
        } else {
            Node* prev = head;
            for (int i = 0; i < index - 1; i++) {
                prev = prev->next;
            }
            Node* toDelete = prev->next;
            prev->next = toDelete->next;
            if (prev->next == nullptr) {
                tail = prev;
            }
            delete toDelete;
        }
        length--;
    }
};

#endif