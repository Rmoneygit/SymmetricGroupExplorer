/*
    Author: Ryan Patrick
    Timestamp: Jun-26-2025
    Purpose: Type declarations for the UI code
 */

#pragma once

#include <string>

namespace SymUI
{
	enum InputMode { TABLE, CYCLE };

    class Token
    {
    public:
        Token(std::string value, std::string type) : m_value(value), m_type(type) {};

        const std::string GetValue() const
        {
            return m_value;
        };

        const std::string GetType() const
        {
            return m_type;
        };

        const std::string GetDebugString() const
        {
            return "Value: " + m_value + " Type: " + m_type + "\n";
        }

    private:
        std::string m_value;
        std::string m_type;
    };
}