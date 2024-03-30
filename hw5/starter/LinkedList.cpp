/**
 * Name: Braeden Cullen
 * Assignment: Treasure Hunter
 * Class: CPSC223 Spring 2024
 * Date: March 30th
 * Implementation for a linked list of Islands for the Treasure Hunter assignment.
 * 
 */

#include "LinkedList.h"
#include <iostream>

// constructor, using colon syntax to initialize
LinkedList::LinkedList() : head(nullptr), currPos(nullptr) {} 

// destructor
LinkedList::~LinkedList() 
{
    makeEmpty();
}

// copy constructor, using colon syntax to initialize
LinkedList::LinkedList(const LinkedList& other) : head(nullptr), currPos(nullptr) 
{
    NodeType* temp = other.head;
    while (temp != nullptr) 
    {
        insertIsland(temp->info);
        temp = temp->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& rhs) 
{
    if (this != &rhs) 
    {
        makeEmpty(); // clear current list

        NodeType* temp = rhs.head;
        while (temp != nullptr) 
        {
            insertIsland(temp->info); // perform deep copy
            temp = temp->next;
        }
    }
    return *this;
}

void LinkedList::insertIsland(Island is) 
{
    NodeType* newNode = new NodeType;
    newNode->info = is;
    newNode->next = head;
    head = newNode;
}

void LinkedList::removeIsland(Island is) 
{
    NodeType *current = head, *prev = nullptr;
    while (current != nullptr) 
    {
        if (current->info.isEqual(is)) // check if island found 
        {
            if (prev == nullptr) 
            {
                head = current->next; // remove first element
            } 
            else 
            {
                prev->next = current->next;
            }
            delete current;
            break; // found island, exit loop
        }
        prev = current;
        current = current->next;
    }
}

void LinkedList::makeEmpty() 
{
    NodeType* temp;
    while (head != nullptr) 
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    currPos = nullptr; // resetting the current position
}

void LinkedList::resetCurrPos() 
{
    currPos = nullptr;
}

Island LinkedList::getNextIsland() 
{
    if (currPos == nullptr) 
    {
        currPos = head;
    } 
    else 
    {
        currPos = currPos->next;
    }
    if (currPos != nullptr) 
    {
        return currPos->info;
    } 
    else 
    {
        return Island(); // return empty island if we reach the end
    }
}

bool LinkedList::isCurrPosNull() const 
{
    return currPos == nullptr || currPos->next == nullptr;
}

int LinkedList::getLength() const 
{
    int length = 0;
    NodeType* temp = head;
    while (temp != nullptr)
    {
        length++;
        temp = temp->next;
    }
    return length;
}

void LinkedList::print(std::ostream& out) 
{
    NodeType* temp = head;
    while (temp != nullptr) 
    {
        temp->info.print(out);
        out << std::endl; // move to next line
        temp = temp->next;
    }
}
