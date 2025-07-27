/*
    Author: Ryan Patrick
    Timestamp: 27-Jul-2025
    Purpose: Declarations of routines for presenting errors in the UI
 */

#pragma once

// Standard library includes
#include <string>

namespace SymUI
{
    // Displays] a Windows popup to the user indicating an error has occurred.
    void ShowErrorPopup(const std::exception& e, const const std::string message);
}