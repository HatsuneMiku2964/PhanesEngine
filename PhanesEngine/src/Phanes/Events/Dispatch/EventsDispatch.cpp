#include "pnpch.h"
#include "EventsDispatch.h";

namespace Phanes {
	EventBox PackEvent(Event& e)
	{
        switch (e.GetEventType()) {
            case EventTypes::MouseButtonPressed:   return static_cast<MouseButtonPressedEvent&>(e);
            case EventTypes::MouseButtonReleased:  return static_cast<MouseButtonReleasedEvent&>(e);
            case EventTypes::MouseMoved:           return static_cast<MouseMovedEvent&>(e);
            case EventTypes::MouseScrolled:        return static_cast<MouseScrolledEvent&>(e);
            case EventTypes::KeyPressed:           return static_cast<KeyPressedEvent&>(e);
            case EventTypes::KeyReleased:          return static_cast<KeyReleasedEvent&>(e);
            case EventTypes::KeyTyped:             return static_cast<KeyTypedEvent&>(e);
            case EventTypes::WindowResize:         return static_cast<WindowResizeEvent&>(e);
        default: return std::monostate{}; }
	}
}