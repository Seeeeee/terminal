// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "../../terminal/adapter/termDispatch.hpp"
#include "ITerminalApi.hpp"

class TerminalDispatch : public Microsoft::Console::VirtualTerminal::TermDispatch
{
public:
    TerminalDispatch(::Microsoft::Terminal::Core::ITerminalApi& terminalApi);
    virtual ~TerminalDispatch(){};
    virtual void Execute(const wchar_t wchControl) override;
    virtual void Print(const wchar_t wchPrintable) override;
    virtual void PrintString(const std::wstring_view string) override;

    bool SetGraphicsRendition(const std::basic_string_view<::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions> options) override;

    virtual bool CursorPosition(const size_t line,
                                const size_t column) override; // CUP

    bool CursorForward(const size_t distance) override;
    bool CursorBackward(const size_t distance) override;
    bool CursorUp(const size_t distance) override;

    bool EraseCharacters(const size_t numChars) override;
    bool SetWindowTitle(std::wstring_view title) override;

    bool SetColorTableEntry(const size_t tableIndex, const DWORD color) override;
    bool SetCursorStyle(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::CursorStyle cursorStyle) override;

    bool SetDefaultForeground(const DWORD color) override;
    bool SetDefaultBackground(const DWORD color) override;
    bool EraseInLine(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::EraseType eraseType) override; // ED
    bool DeleteCharacter(const size_t count) override;
    bool InsertCharacter(const size_t count) override;
    bool EraseInDisplay(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::EraseType eraseType) override;

private:
    ::Microsoft::Terminal::Core::ITerminalApi& _terminalApi;

    static bool s_IsRgbColorOption(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions opt) noexcept;
    static bool s_IsBoldColorOption(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions opt) noexcept;
    static bool s_IsDefaultColorOption(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions opt) noexcept;

    bool _SetRgbColorsHelper(const std::basic_string_view<::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions> options,
                             size_t& optionsConsumed);
    bool _SetBoldColorHelper(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions option);
    bool _SetDefaultColorHelper(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions option);
    void _SetGraphicsOptionHelper(const ::Microsoft::Console::VirtualTerminal::DispatchTypes::GraphicsOptions opt);
};
