/*
 * LinkedList.cpp
 * CPSC 223 Pset 5
 *
 * Implementation for Linked List of Islands
 * TO STUDENT: Don't forget to remove // TODO when you submit!
 *
 * Author: Braeden Cullen
 */

#include "LinkedList.h"
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    // define head, next and current position, using the NodeType structure
    head = new NodeType;
    head->info = Island();
    head->next = nullptr;
    head->next = nullptr;
    currPos = nullptr;
}

// Destructor
LinkedList::~LinkedList()
{
    // cleanup linked list, simply iterate through each node until next = nullptr
    NodeType *current = head;
    while (current != nullptr) 
    {
        NodeType *temp = current;
        current = current->next;
        delete temp;
    }
}

// Assignment operator overload.
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    // implement operator = 
    // check if the linked list is the same as the one being assigned
    if (this == &rhs)
    {
        return *this;
    }
    // cleanup the linked list
    NodeType *current = head;
    while (current != nullptr)
    {
        NodeType *temp = current;
        current = current->next;
        delete temp;
    }
    // create a new linked list
    head = new NodeType;
    head->info = Island();
    head->next = nullptr;
    head->next = nullptr;
    currPos = nullptr;
    // iterate through the linked list and assign the values
    NodeType *currentRhs = rhs.head;
    NodeType *currentThis = head;
    while (currentRhs != nullptr)
    {
        currentThis->info = currentRhs->info;
        currentRhs = currentRhs->next;
        if (currentRhs != nullptr)
        {
            currentThis->next = new NodeType;
            currentThis = currentThis->next;
            currentThis->info = Island();
            currentThis->next = nullptr;
        }
    }
    return *this;
}

// Copy constructor
LinkedList::LinkedList(const LinkedList &other)
{
    // TODO: Implement the copy constructor
    head = new NodeType;
    head->info = Island();
    head->next = nullptr;
    currPos = nullptr;
    NodeType *currentOther = other.head;
    NodeType *currentThis = head;
    while (currentOther != nullptr)
    {
        currentThis->info = currentOther->info;
        currentOther = currentOther->next;
        if (currentOther != nullptr)
        {
            currentThis->next = new NodeType;
            currentThis = currentThis->next;
            currentThis->info = Island();
            currentThis->next = nullptr;
        }
    }
}

int LinkedList::getLength() const
{
    int count = 0;
    NodeType *current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

bool LinkedList::isCurrPosNull() const
{
    return currPos == nullptr;
}

void LinkedList::insertIsland(Island is)
{
    // inserts island infront of this
    NodeType *newNode = new NodeType;
    newNode->info = is;
    newNode->next = head;
    head = newNode;
}

void LinkedList::removeIsland(Island is)
{
    //remove the first island in this that equals is
    NodeType *current = head;
    NodeType *prev = nullptr;
    while (current != nullptr)
    {
        if (current->info.isEqual(is))
        {
            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

Island LinkedList::getNextIsland()
{
    // Returns the island this.currPos and advances this.currPos to the next island in the list.
    // If this.currPos is NULL, then this function behaves as though this.currPos was the first island in the list. 
    // If there are no islands in the list, the behavior of this function is undefined.

    if (currPos == nullptr)
    {
        currPos = head;
    }
    else
    {
        currPos = currPos->next;
    }
    return currPos->info;
}

void LinkedList::resetCurrPos()
{
    currPos = nullptr;
}

void LinkedList::makeEmpty()
{
    //remove all islands from this, and deallocate all memory owned by those islands and all memory allocated by this to manage each island, reset this.currPos
    NodeType *current = head;
    while (current != nullptr)
    {
        NodeType *temp = current;
        current = current->next;
        delete temp;
    }
    // run default constructor to reset
    head = new NodeType;
    head->info = Island();
    head->next = nullptr;
    head->next = nullptr;
    currPos = nullptr;
}

void LinkedList::print(ostream &out)
{
    NodeType *current = head;
    while (current != nullptr)
    {
        current->info.print(out);
        current = current->next;
    }
}
