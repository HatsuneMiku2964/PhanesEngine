#pragma once

#include <variant>
#include <type_traits>

#include "Events.h"
#include "AppEvents.h"
#include "KeyEvents.h"
#include "MouseEvents.h"

namespace PN
{
    template<typename... Ts>
    struct FnOverload : Ts... { using Ts::operator()...; };

    using EventBox = std::variant
        <
        std::monostate,
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent,
        KeyPressedEvent, KeyReleasedEvent, KeyTypedEvent, WindowResizeEvent, WindowCloseEvent
        >;


    class EventDispatcher
    {
        template<typename F>
        struct event_traits;

        template<typename C, typename R, typename EventT>
        struct event_traits<R(C::*)(EventT&) const>
        {
            using EventType = std::remove_cvref_t<EventT>;
        };

        template<typename C, typename R, typename EventT>
        struct event_traits<R(C::*)(EventT&)>
        {
            using EventType = std::remove_cvref_t<EventT>;
        };

        template<typename F>
        using event_traits_t = event_traits<decltype(&std::decay_t<F>::operator())>::EventType;

    public:
        EventDispatcher(Event& e) : event(e), eventbox(PackEvent(e)) {}

        template<typename T>
        bool Dispatch(std::function<bool(T&)> func)
        {
            if (event.GetEventType() == T::GetStaticType()) {
                event.Handled = func(*(T*) &event);
                return true;
            }
            return false;
        }

        template<typename... Args>
        bool Dispatch(Args&&... args)
        {
            (dispatch_single(std::forward<Args>(args)), ...);
            return event.Handled;
        }

    private:
        template<typename F>
        void dispatch_single(F&& func)
        {
            if (event.Handled) return;

            using EventT = event_traits_t<F>;
            if (event.GetEventType() != EventT::GetStaticType()) return;

            event.Handled |= func(*(EventT*)&event);
            
        }

        pn_forceinline static EventBox PackEvent(Event& e)
        {
            switch (e.GetEventType()) {
            case EventTypes::MouseButtonPressed:    return static_cast<MouseButtonPressedEvent&>(e);
            case EventTypes::MouseButtonReleased:   return static_cast<MouseButtonReleasedEvent&>(e);
            case EventTypes::MouseMoved:            return static_cast<MouseMovedEvent&>(e);
            case EventTypes::MouseScrolled:         return static_cast<MouseScrolledEvent&>(e);
            case EventTypes::KeyPressed:            return static_cast<KeyPressedEvent&>(e);
            case EventTypes::KeyReleased:           return static_cast<KeyReleasedEvent&>(e);
            case EventTypes::KeyTyped:              return static_cast<KeyTypedEvent&>(e);
            case EventTypes::WindowResize:          return static_cast<WindowResizeEvent&>(e);
            case EventTypes::WindowClose:           return static_cast<WindowCloseEvent&>(e);
            case EventTypes::WindowFocus:           return std::monostate{}; // NO IMPL
            case EventTypes::WindowLostFocus:       return std::monostate{}; // NO IMPL
            case EventTypes::WindowMoved:           return std::monostate{}; // NO IMPL
            case EventTypes::AppTick:               return std::monostate{}; // NO IMPL
            case EventTypes::AppUpdate:             return std::monostate{}; // NO IMPL
            case EventTypes::AppRender:             return std::monostate{}; // NO IMPL
            case EventTypes::None:                  return std::monostate{};
            default:                                return std::monostate{};
            }
        };

    private:
        Event& event;
        EventBox eventbox;
    };

}