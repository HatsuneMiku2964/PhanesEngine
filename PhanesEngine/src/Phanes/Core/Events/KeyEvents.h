#pragma once

#include "Events.h"

namespace PN
{
    // base class for KeyPressedEvent, KeyReleasedEvent and KeyTypedEvent
    class KeyEvent : public Event
    {
    public:
        pn_forceinline int GetKeyCode() const { return KeyCode_; }

        IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Keyboard);

    protected:
        KeyEvent(int keycode) : KeyCode_(keycode) {}
        int KeyCode_;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, uint32_t repeatCount)
            : KeyEvent(keycode), repeat_cnt(repeatCount)
        {
        }

        pn_forceinline uint32_t GetRepeatCount() const { return repeat_cnt; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << KeyCode_ << " (" << repeat_cnt << " repeats)";
            return ss.str();
        }
        IMPL_EVENT_TYPE(KeyPressed);

    private:
        uint32_t repeat_cnt;
    };
    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << KeyCode_;
            return ss.str();
        }
        IMPL_EVENT_TYPE(KeyReleased);
    };
    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << KeyCode_;
            return ss.str();
        }
        IMPL_EVENT_TYPE(KeyTyped);
    };
}