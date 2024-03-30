// LinkedList.cpp
// Implementation for a linked list of Islands for the Treasure Hunter assignment.
// Author: Your Name

#include "LinkedList.h"
#include <iostream>

// Default constructor
LinkedList::LinkedList() : head(nullptr), currPos(nullptr) {}

// Destructor
LinkedList::~LinkedList() {
    makeEmpty();
}

// Copy constructor
LinkedList::LinkedList(const LinkedList& other) : head(nullptr), currPos(nullptr) {
    NodeType* temp = other.head;
    while (temp != nullptr) {
        insertIsland(temp->info);
        temp = temp->next;
    }
}

// Assignment operator
LinkedList& LinkedList::operator=(const LinkedList& rhs) {
    if (this != &rhs) {
        makeEmpty(); // Clear current list

        NodeType* temp = rhs.head;
        while (temp != nullptr) {
            insertIsland(temp->info);
            temp = temp->next;
        }
    }
    return *this;
}

// Insert an island at the head of the list
void LinkedList::insertIsland(Island is) {
    NodeType* newNode = new NodeType;
    newNode->info = is;
    newNode->next = head;
    head = newNode;
}

// Remove the first occurrence of an island from the list
void LinkedList::removeIsland(Island is) {
    NodeType *current = head, *prev = nullptr;
    while (current != nullptr) {
        if (current->info.isEqual(is)) {
            if (prev == nullptr) {
                // Removing the first element
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            break; // Island found and removed, exit the loop
        }
        prev = current;
        current = current->next;
    }
}

// Make the list empty, removing all elements
void LinkedList::makeEmpty() {
    NodeType* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
    currPos = nullptr; // Resetting the current position
}

// Reset the current position for iteration
void LinkedList::resetCurrPos() {
    currPos = nullptr;
}

// Get the next island and advance the current position
Island LinkedList::getNextIsland() {
    if (currPos == nullptr) {
        currPos = head;
    } else {
        currPos = currPos->next;
    }
    if (currPos != nullptr) {
        return currPos->info;
    } else {
        return Island(); // Return an empty island if we've reached the end
    }
}

// Check if the current position is at the end of the list
bool LinkedList::isCurrPosNull() const {
    return currPos == nullptr || currPos->next == nullptr;
}

// Get the length of the list
int LinkedList::getLength() const {
    int length = 0;
    NodeType* temp = head;
    while (temp != nullptr) {
        length++;
        temp = temp->next;
    }
    return length;
}

// Print the list to the specified output stream
void LinkedList::print(std::ostream& out) {
    NodeType* temp = head;
    while (temp != nullptr) {
        temp->info.print(out);
        out << std::endl; // Move to the next line after printing each island
        temp = temp->next;
    }
}
