/*
    Author: Ryan Patrick
    Timestamp: 27-Jul-2025
    Purpose: Declarations of routines for error handling
 */

#pragma once

// CppTrace 3rd-party library includes
#include <cpptrace/formatting.hpp>

// Normal includes
#include "Sym_data_types.hpp"

// Standard library includes
#include <exception>
#include <functional>
#include <string>

namespace Sym
{
    // The purpose of this class is to allow two seperate error messages to be stored: one for user-facing display
    // such as in error popup dialogs, and one for debugging purposes to be printed to the system log.
    class DebugException : public std::exception
    {
    public:
        DebugException(std::string userMsg, std::string debugMsg) : m_userMsg(userMsg), m_debugMsg(debugMsg)
        {

        }

        const char* what() const noexcept override {
            return m_userMsg.c_str();
        }

        const std::string& GetDebugMessage() const noexcept
        {
            return m_debugMsg;
        }

    private:
        std::string m_userMsg;
        std::string m_debugMsg;
    };
    
    // Important: This method is only meant to be called within a CPPTRACE_CATCH block!
    // It won't work otherwise.
    void PrintErrorToStdErrorStream(const std::exception& e, const std::string message);

    void PrintDebugErrorToStdErrorStream(const DebugException& e, const std::string message);

    // Used to format the stack traces printed by cpptrace
    const cpptrace::formatter* GetGlobalCppTraceFormatter();

    std::string GetDebugString(const Permutation& permutation);

    void ProtectedCall(const std::function<void()>& fn, const std::string& contextErrMsg);
}
