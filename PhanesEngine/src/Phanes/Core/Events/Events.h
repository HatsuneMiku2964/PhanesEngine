#pragma once

namespace PN
{
    enum class EventTypes
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };
    enum class EventCategories : int
    {
        None = 0,
        Application = BIT_PUSH(0),
        Input = BIT_PUSH(1),
        Keyboard = BIT_PUSH(2),
        Mouse = BIT_PUSH(3),
    };

    // bitwise operators for EventCategories, so we can combine them using bitwise operations
    pn_forceinline EventCategories operator|(EventCategories a, EventCategories b)
    {
        return static_cast<EventCategories>(static_cast<int>(a) | static_cast<int>(b));
    }
    pn_forceinline EventCategories operator&(EventCategories a, EventCategories b)
    {
        return static_cast<EventCategories>(static_cast<int>(a) & static_cast<int>(b));
    }
    pn_forceinline EventCategories& operator|=(EventCategories& a, EventCategories b)
    {
        a |= b; return a;
    }
    pn_forceinline bool HasCategory(EventCategories flags, EventCategories category)
    {
        return (static_cast<int>(flags) & static_cast<int>(category)) != 0;
    }

    // impl functions of interface PN::Event
    #define IMPL_EVENT_TYPE(type)           pn_forceinline static EventTypes GetStaticType() { return EventTypes::##type; }\
                                            pn_forceinline EventTypes GetEventType() const override { return GetStaticType(); }\
                                            pn_forceinline const char* GetName() const override { return #type; }

    #define IMPL_EVENT_CATEGORY(category)   pn_forceinline int GetCategoryFlags() const override { return static_cast<int>(category); }
    // ~macros

    class Event
    {
    public:
        virtual ~Event() = default;
        virtual EventTypes GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        // mainly for debug
        pn_forceinline virtual std::string ToString() const { return GetName(); }

        //utility function to check if the event is in a category
        pn_forceinline bool IsInCategory(EventCategories category) const { return GetCategoryFlags() & static_cast<int>(category); }

        bool Handled = false;
    };

    pn_forceinline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}