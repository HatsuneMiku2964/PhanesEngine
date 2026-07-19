#pragma once

#include <variant>
#include <utility>

#include "Phanes/Events/Events.h"
#include "Phanes/Events/AppEvents.h"
#include "Phanes/Events/KeyEvents.h"
#include "Phanes/Events/MouseEvents.h"

namespace Phanes
{
    /* INFO: a struct that inherits the lambdas filled in on construction, utility for std::visit
    *
    *  Sample use case (appeared in one version of ImGuiLayer.cpp):
    *      EventBox eventbox = PackEvent(e); // put the event with the true type inside the std::variant box
    *      std::visit(FnOverload{ ... } , eventbox); // put lambdas inside "..."
    *
    *      // this EventDispatchOverload will inherit all these lambdas,
    *      // depends on the type of the event, we will execute one of it
    */
    template<class... Ts>
    struct FnOverload : Ts... { using Ts::operator()...; };

    using EventBox = std::variant
    <
        std::monostate,
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent,
        KeyPressedEvent, KeyReleasedEvent, KeyTypedEvent, WindowResizeEvent, WindowCloseEvent
    >;

    EventBox PackEvent(Event& e);

    class EventDispatcher
    {
        template<typename T>
        using EventFunc = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& e) : event_(e) {}

        template<typename T>
        bool Dispatch(EventFunc<T> func)
        {
            PN_CORE_LOG_WARN("Legacy func used: EventDispatcher::Dispatch(EventFunc<T> func)");
            if (event_.GetEventType() == T::GetStaticType()) {
                event_.Handled = func(*(T*) &event_);
                return true;
            }
            return false;
        }

        template<typename... Args>
        bool Dispatch(Args&&... args)               // INFO: all args (lambdas) should return bool
        {
            EventBox eventbox_ = PackEvent(event_);

            FnOverload overload{
                std::forward<Args>(args)...,        // pack all callbacks using perfect forwarding
                [](const auto&) { return false; },  // handle arbitary EVENT type
                [this](std::monostate) {            // handle arbitary type
                    PN_CORE_LOG_WARN("Try dispatching unknown event: {0} event", event_.GetName());
                    return false;
                }
            };

            bool success = std::visit(overload, eventbox_);
            event_.Handled = success;
            return success;
        }

    private:
        Event& event_;
    };

}