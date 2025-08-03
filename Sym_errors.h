/*
    Author: Ryan Patrick
    Timestamp: 27-Jul-2025
    Purpose: Declarations of routines for error handling
 */

#pragma once

// CppTrace 3rd-party library includes
#include <cpptrace/formatting.hpp>

// Standard library includes
#include <exception>
#include <string>

namespace Sym
{
    // Important: This method is only meant to be called within a CPPTRACE_CATCH block!
    // It won't work otherwise.
    void PrintErrorToStdErrorStream(const std::exception& e, const std::string message);

    // Used to format the stack traces printed by cpptrace
    const cpptrace::formatter* GetGlobalCppTraceFormatter();
}
