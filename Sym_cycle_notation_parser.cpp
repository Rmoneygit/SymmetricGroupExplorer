/*
    Author: Ryan Patrick
    Timestamp: 01-Sep-2025
    Purpose: Definitions of routines for use by the cycle notation parser
 */

#include "Sym_cycle_notation_parser.hpp"

#include <iostream>

NumNode* AddNodeToTail(NumNode* head, int value)
{
    NumNode* temp = new NumNode(value, nullptr);

    if (head == nullptr)
    {
        head = temp;
    }
    else
    {
        NumNode* p = head;
        while (p->m_next != nullptr)
        {
            p = p->m_next;
        }
        p->m_next = temp;
    }

    return head;
}

void PrintNumNodeList(NumNode* head)
{
    NumNode* p = head;

    while (p != nullptr)
    {
        std::cout << p->m_number << " --> ";
        p = p->m_next;
    }
    std::cout << "\n";
}