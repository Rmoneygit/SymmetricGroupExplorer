/*
    Author: Ryan Patrick
    Timestamp: 01-Sep-2025
    Purpose: Definitions of routines for use by the cycle notation parser
 */

#include "Sym_cycle_notation_parser.hpp"
#include "Sym_symmetric_group.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

using namespace Sym;

NumNode* Sym::AddNodeToTail(NumNode* head, int value)
{
    if (value <= 0)
    {
        std::ostringstream oss;
        oss << "Encountered the nonpositive number \'" << value << "\' in a cycle.";
        throw std::exception(oss.str().c_str());
    }

    if (value > s_numSymbols)
    {
        std::ostringstream oss;
        oss << "Encountered the number \'" << value << "\', which is greater than the maximum possible value \'" << s_numSymbols << "\'.";
        throw std::exception(oss.str().c_str());
    }
    
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

void Sym::PrintNumNodeList(NumNode* head)
{
    NumNode* p = head;

    while (p != nullptr)
    {
        std::cout << p->m_number << " --> ";
        p = p->m_next;
    }
    std::cout << "\n";
}

Permutation* Sym::CreatePermutation(NumNode* head)
{
    Permutation* perm = new Permutation(s_numSymbols);

    // Initializing the permutation to identity is useful since it enforces this rule:
    // In a cycle, any number not explicitly written is mapped to itself.
    SetToIdentity(*perm);
    
    std::unordered_set<int> encounteredNumbers;

    NumNode* p = head;
    while (p != nullptr)
    {
        auto iter = encounteredNumbers.find(p->m_number);
        if (iter != encounteredNumbers.end())
        {
            std::ostringstream oss;
            oss << "Encountered the number \'" << p->m_number << "\' more than once in the same cycle.";
            throw std::exception(oss.str().c_str());
        }

        encounteredNumbers.insert(p->m_number);

        NumNode* next = p->m_next;

        // Last element in the cycle is a special case. It should be mapped to the first element of the cycle.
        if (next == nullptr)
        {
            (*perm)[p->m_number - 1] = head->m_number;
            break;
        }
        
        // If a ---> b, then b is placed at index a - 1. 
        (*perm)[p->m_number - 1] = next->m_number;

        p = p->m_next;
    }

    return perm;
}