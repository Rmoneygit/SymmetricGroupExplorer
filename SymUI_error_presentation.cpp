/*
    Author: Ryan Patrick
    Timestamp: 27-Jul-2025
    Purpose: Definitions for routines for presenting errors in the UI
 */

// Windows includes
#include <Windows.h>

// Normal includes
#include "SymUI_error_presentation.hpp"

// Standard library includes
#include <string>

void SymUI::ShowErrorPopup(const std::exception& e, const std::string message)
{
    MessageBoxA(nullptr, (message + e.what()).c_str(), "Error", MB_OK | MB_ICONERROR);
}