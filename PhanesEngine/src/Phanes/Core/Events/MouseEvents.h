#pragma once

#include "Events.h"

namespace PN
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : x(x), y(y)
        {
        }

        pn_forceinline float GetX() const { return x; }
        pn_forceinline float GetY() const { return y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << x << ", " << y;
            return ss.str();
        }

        IMPL_EVENT_TYPE(MouseMoved);
        IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse);
    private:
        float x, y;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float x, float y)
            : x_offset(x), y_offset(y)
        {
        }

        pn_forceinline float GetXOffset() const { return x_offset; }
        pn_forceinline float GetYOffset() const { return y_offset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << x_offset << ", " << y_offset;
            return ss.str();
        }

        IMPL_EVENT_TYPE(MouseScrolled);
        IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse);
    private:
        float x_offset, y_offset;
    };

    // base class for MouseButtonPressedEvent and MouseButtonReleasedEvent
    class MouseButtonEvent : public Event
    {
    public:
        pn_forceinline int GetButtonCode() const { return ButtonCode_; }
        IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse);

    protected:
        MouseButtonEvent(int buttoncode) : ButtonCode_(buttoncode) {}
        int ButtonCode_;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << ButtonCode_;
            return ss.str();
        }
        IMPL_EVENT_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << ButtonCode_;
            return ss.str();
        }
        IMPL_EVENT_TYPE(MouseButtonReleased);
    };
}