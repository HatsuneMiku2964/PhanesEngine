#include "pnpch.h"
#include "EventsDispatch.h";

namespace Phanes
{
    EventBox PackEvent(Event& e)
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
    }
}