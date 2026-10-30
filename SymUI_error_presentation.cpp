/*
    Author: Ryan Patrick
    Timestamp: 27-Jul-2025
    Purpose: Definitions for routines for presenting errors in the UI
 */

// Windows includes
#include <Windows.h>

// Cpptrace 3rd-party library includes
#include <cpptrace/from_current.hpp>

// Normal includes
#include "SymUI_error_presentation.hpp"
#include "Sym_errors.hpp"

// Standard library includes
#include <functional>
#include <string>

void SymUI::ShowErrorPopup(const std::exception& e, const std::string message)
{
    MessageBoxA(nullptr, (message + e.what()).c_str(), "Error", MB_OK | MB_ICONERROR);
}

void SymUI::ProtectedCall(const std::function<void()>& callable, const std::string& contextErrMsg)
{
    cpptrace::try_catch(
        callable,
        [&](const Sym::DebugException& e) {
            Sym::PrintDebugErrorToStdErrorStream(e, contextErrMsg);
            ShowErrorPopup(e, contextErrMsg);
        },
        [&](const std::exception& e) {
            Sym::PrintErrorToStdErrorStream(e, contextErrMsg);
            ShowErrorPopup(e, contextErrMsg);
        }
    );
}