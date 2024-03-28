#pragma once
/*
 * NodeType.h
 * CPSC 223 Pset 5
 *
 *
 * Small struct that is part of a Linked List class.
 * Modified this function to include head member
 */

#include "Island.h" 
using namespace std;

struct NodeType
{
    Island info; 
    NodeType *next;
};
