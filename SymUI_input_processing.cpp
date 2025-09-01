/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Implementations of routines for processing user input
 */

#include "Sym_data_types.hpp"
#include "SymUI_data_types.hpp"
#include "SymUI_input_processing.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <stdexcept>

void SymUI::ProcessPermutationInput(int i, Sym::Permutation& inputBuffer, Sym::Permutation& permutation)
{
    if (inputBuffer.size() != permutation.size())
    {
        throw std::invalid_argument("Expected inputBuffer and permutation to have the same size.");
    }

    // Only allow values between 1-n inclusive
    if (inputBuffer[i] > 0 && inputBuffer[i] <= inputBuffer.size())
    {
        // A permutation is a shuffling of symbols, so repetitions can't be allowed. 
        // So, swap the existing occurrence of this symbol with this one. Example:
        /*
        **********Stage 1**********
        inputBuffer
        1 2 3 4
        1 3 2 3

        permutation
        1 2 3 4
        1 4 2 3

        **********Stage 2**********
        inputBuffer
        1 2 3 4
        1 3 2 *4*

        permutation
        1 2 3 4
        1 4 2 *4*

        **********Stage 3**********
        inputBuffer
        1 2 3 4
        1 3 2 4

        permutation
        1 2 3 4
        1 *3* 2 4

        */
        bool foundValue = false;
        for (int j = 0; j < inputBuffer.size(); j++)
        {
            if (inputBuffer[j] == inputBuffer[i] && i != j)
            {
                inputBuffer[j] = permutation[i];
                permutation[j] = permutation[i];
                foundValue = true;
                break;
            }
        }

        assert(foundValue);

        permutation[i] = inputBuffer[i];
    }
    else
    {
        inputBuffer[i] = permutation[i];
    }
}

void SymUI::ShrinkPermutationByOne(Sym::Permutation& permutation)
{
    int n = static_cast<int>(permutation.size());
    for (int i = 0; i < n; i++)
    {
        if (permutation[i] == n)
        {
            permutation[i] = permutation[n - 1];
        }
    }

    permutation.resize(n - 1);
}

void SymUI::CopyPermutation(Sym::Permutation& destination, Sym::Permutation& source)
{
    for (int i = 0; i < destination.size(); i++)
    {
        destination[i] = source[i];
    }
}

Sym::Permutation SymUI::InitializePermutation(int size)
{
    Sym::Permutation permutation;

    for (int i = 0; i < size; i++)
    {
        permutation.push_back(i + 1);
    }

    return permutation;
}

// Purpose: Perform lexical analysis on the input string, which means to break up the string into tokens.
// In a formal grammar, a token is an indivisible unit of meaning. These tokens will subsequently be fed into a parser 
// which will check if this particular sequence of tokens conforms to the rules of the grammar. This lexer is meant
// to tokenize permutations written in cycle notation. It uses a state table which represents an FSA (Finite State Automaton)
static std::vector<SymUI::Token> cycleNotationLexer(const std::string cycleInput)
{
    // State table.
    /*
      The meaning of the rows in the table are as follows:
      1: Starting state
      2: In number
      3: End of number
      4: Found "(" or ")"
      5: Error state

      "d" stands for digit,
      "sp" stands for space,
      "*" stands for wildcard character
      (that is, any character not specifically listed.)

      If the token is the kind that can only be recognized by running off the end,
      it must also back up the character pointer. This is indicated in the "back-up"
      column. Accepting states that don't require backing off the character pointer
      are marked with "n"; those that do, with "y".

      An "A" in front of a row indicates an accepting state. Entering an accepting
      state means we have recognized an acceptable token of the language

            |       Input
      Curr. |
      State | d   sp  (   )  \n  \0   *    Backup
      --------------------------------------
        1   | 2   1   4   4   1   1   5
        2   | 2   3   3   3   3   3   5
    A   3   | 1   1   1   1   1   1   1     y
    A   4   | 1   1   1   1   1   1   1     n
    A   5   | 1   1   1   1   1   1   1

    */

    const int numStates = 5;
    const int numColumns = 7;
    const int stateTable[numStates][numColumns] =
    {
        {2, 1, 4, 4, 1, 1, 5},
        {2, 3, 3, 3, 3, 3, 5},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1}
    };

    // For determining state table column.
    const char* colstring = " ()\n";
    // For identifying digits.
    const char* digs = "0123456789";

    int startPtr;             // Token-start pointer
    int currCharPtr;             // Pointer to current character
    std::string tokenType;        // Number, seperator
    int col = -1;       // Column of the state table
    char currChar;            // Current character
    std::string lexeme;       // I.e., a character string
    int currState = 1;  // Current lexical state.
    int prevState = 1; // Previous lexical state.
    std::vector<SymUI::Token> tokenVec;

    startPtr = 0;
    currCharPtr = 0;

    size_t inputLength = cycleInput.length();
    size_t colstringLength = 3;

    // Scanning loop
    while (currCharPtr <= inputLength)
    {
        currChar = cycleInput[currCharPtr]; // Get next input character.

        // Find state table column.
        col = -1;
        for (int i = 0; i < colstringLength; i++)
        {
            if (colstring[i] == currChar)
            {
                col = i + 1; // Plus one since column 0 is for digits
                break;
            }
        }

        if (col == -1)
        {
            if (currChar == '\0')
            {
                col = 5;
            }            
            else if (strchr(digs, currChar))
            {
                col = 0;
            }
            else
            {
                col = numColumns - 1;
            }

        }

        prevState = currState;
        currState = stateTable[currState - 1][col];
        if (currCharPtr - startPtr == 0)
            lexeme = cycleInput[currCharPtr];
        else
            lexeme = cycleInput.substr(startPtr, currCharPtr - startPtr);

        switch (currState)
        {
        case 3:
            tokenType = "Number";
            prevState = currState;
            currState = 1;
            currCharPtr--; // Perform backup
            break;
        case 4:
            tokenType = "Parentheses";
            prevState = currState;
            currState = 1;
            break;
        case 5:
            tokenType = "Invalid";
            prevState = currState;
            currState = 1;
            break;
        }

        currCharPtr++;
        if (currState == 1)
        {
            startPtr = currCharPtr;
            if (prevState != 1)
            {
                tokenVec.push_back(SymUI::Token(lexeme, tokenType));
            }
        }

        if (tokenType == "Invalid")
        {
            break;
        }
    }

    return tokenVec;
}

Sym::Permutation SymUI::ProcessCycleNotationInput(const char* cycleInput)
{
    std::vector<SymUI::Token> tokens = cycleNotationLexer(cycleInput);

    std::cout << "ProcessCycleNotationInput begin\n";
    int i = 1;
    for (SymUI::Token token : tokens)
    {
        std::cout << "Token " << i++ << ": " << token.GetDebugString();
    }
    
    std::cout << "ProcessCycleNotationInput end\n";
    
    if (tokens.size() == 0)
    {
        throw std::exception("No tokens recognized in input.\n");
    }

    // Assumption is that the lexer immediately returns upon encountering an invalid token,
    // so it will be the last one in the list.
    SymUI::Token finalToken = tokens[tokens.size() - 1];
    if (finalToken.GetType() == "Invalid")
    {
        std::string errorMsg = "Invalid token encountered: " + finalToken.GetValue();
        throw std::exception(errorMsg.c_str());
    }


    return Sym::Permutation();
}