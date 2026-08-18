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

    template<typename Class, typename EventT>
    auto BindEventFn(bool(Class::* fn)(EventT&), Class* instance)
    {
        return [instance, fn](EventT& e) -> bool {
            return (instance->*fn)(e);
        };
    }


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
        EventDispatcher(Event& e) : event(e) {}

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

            event.Handled |= func(*(EventT*) &event);

        }

    private:
        Event& event;
    };

}