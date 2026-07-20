#pragma once

#include <variant>
#include <utility>

#include "Phanes/Events/Events.h"
#include "Phanes/Events/AppEvents.h"
#include "Phanes/Events/KeyEvents.h"
#include "Phanes/Events/MouseEvents.h"

namespace Phanes
{
    template<class... Ts>
    struct FnOverload : Ts... { using Ts::operator()...; };

    using EventBox = std::variant
        <
        std::monostate,
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent, MouseScrolledEvent,
        KeyPressedEvent, KeyReleasedEvent, KeyTypedEvent, WindowResizeEvent, WindowCloseEvent
        >;


    class EventDispatcher
    {
        template<typename T>
        using EventFunc = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& e) : event_(e), eventbox_(PackEvent(e)) {}

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
            FnOverload overload{
                std::forward<Args>(args)...,        // pack all callbacks using perfect forwarding
                [](auto&) { return false; },        // handle arbitary EVENT type
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
        static EventBox PackEvent(Event& e)
        {
            switch (e.GetEventType()) {
                case EventTypes::MouseButtonPressed:    return dynamic_cast<MouseButtonPressedEvent&>(e);
                case EventTypes::MouseButtonReleased:   return dynamic_cast<MouseButtonReleasedEvent&>(e);
                case EventTypes::MouseMoved:            return dynamic_cast<MouseMovedEvent&>(e);
                case EventTypes::MouseScrolled:         return dynamic_cast<MouseScrolledEvent&>(e);
                case EventTypes::KeyPressed:            return dynamic_cast<KeyPressedEvent&>(e);
                case EventTypes::KeyReleased:           return dynamic_cast<KeyReleasedEvent&>(e);
                case EventTypes::KeyTyped:              return dynamic_cast<KeyTypedEvent&>(e);
                case EventTypes::WindowResize:          return dynamic_cast<WindowResizeEvent&>(e);
                case EventTypes::WindowClose:           return dynamic_cast<WindowCloseEvent&>(e);
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
        Event& event_;
        EventBox eventbox_;
    };

}