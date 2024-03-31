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
LinkedList::LinkedList() : head(nullptr), currPos(nullptr), previous_head_pointer(nullptr), previous_current_pointer(nullptr) {} 

// destructor
LinkedList::~LinkedList() 
{
    makeEmpty();
    if (previous_head_pointer != nullptr)
    {
        delete previous_head_pointer;
    }
    if (previous_current_pointer != nullptr) {
        delete previous_current_pointer;
    }
}

// copy constructor
LinkedList::LinkedList(const LinkedList& other) 
{
    if (other.head == nullptr) 
    {
        // if the other list is empty, ensure this list is initialized empty.
        head = nullptr;
        currPos = nullptr;
    } 
    else 
    {
        // start by copying the head node
        head = new NodeType;
        head->info = other.head->info;
        head->next = nullptr;

        // if other.currPos is at the head, set this.currPos to this head
        if (other.currPos == other.head) 
        {
            currPos = head;
        }

        NodeType* newCurrent = head; // current new node being added to 'this' list
        NodeType* otherCurrent = other.head->next; // current node in 'other' list being copied

        // copy the rest of the nodes
        while (otherCurrent != nullptr) 
        {
            newCurrent->next = new NodeType;
            newCurrent = newCurrent->next;
            newCurrent->info = otherCurrent->info;
            newCurrent->next = nullptr;

            // if otherCurrent is the currPos in 'other', update currPos in 'this'
            if (otherCurrent == other.currPos) 
            {
                currPos = newCurrent;
            }

            otherCurrent = otherCurrent->next;
        }
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
    NodeType* newNode = new NodeType();
    newNode->info = is; 
    newNode->next = this->head;
    
    this->head = newNode; 
}



void LinkedList::removeIsland(Island is)
{
    NodeType* current = head;
    NodeType* previous = nullptr;

    while (current != nullptr)
    {
        if (current->info.isEqual(is))
        {
            if (current == head)
            {
                this->head = current->next;
                //currPos = nullptr;
                previous_head_pointer = current;
            }
            else
            {
                // curr-next , currpos null.. currnext= currnextnext
                previous->next = current->next;
                if (currPos == current)
                {
                    //resetCurrPos();
                }
                previous_current_pointer = current;
                //delete current;
            }
            return;
        }
        // advance to the next node
        previous = current;
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
        delete previous_head_pointer;
        previous_head_pointer = nullptr;
        delete previous_current_pointer;
        previous_current_pointer = nullptr;
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
    int totalLength = getLength();
    int index = totalLength - 1;
    while (temp != nullptr) 
    {
        temp->info.print(out);
        if (index == 0) 
        {
            out << index << "\n";
        }
        else 
        {
            out << index << " ~~ ";
        }
        temp = temp->next;
        index--;
    }
}