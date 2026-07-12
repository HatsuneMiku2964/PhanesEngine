#pragma once

#include <variant>

#include "Phanes/Events/Events.h"
#include "Phanes/Events/AppEvents.h"
#include "Phanes/Events/KeyEvents.h"
#include "Phanes/Events/MouseEvents.h"

namespace Phanes {

    /* TIP: a struct that inherits the lambdas filled in on construction, 
    *       utility for std::visit
    * 
    *  Sample use case (appears in one version of ImGuiLayer.cpp): 
    *      EventBox eventbox = PackEvent(e); // TIP: put the event with the true type inside the std::variant box
    *      std::visit(EventDispatchOverload{
    *          [&e](std::monostate) { PN_CORE_LOG_WARN("Invalid event type dispatched: {0} event", e.GetName()); return false; }, // default case, if no type matches
    *          [this](MouseButtonPressedEvent& ev) { return OnMouseButtonPressedEvent(ev); },
    *          [this](KeyPressedEvent& ev) { return OnKeyPressedEvent(ev); },
    *          [this](WindowResizeEvent& ev) { return OnWindowResizeEvent(ev); } 
    *          ... // other lambdas
    *      } , eventbox);
    *      // this EventDispatchOverload will inherit all these lambdas, 
    *      // depends on the type of the event, we will execute one of it
    */
    template<class... Ts>
    struct EventDispatchOverload : Ts... { using Ts::operator()...; };

    using EventBox = std::variant<
        std::monostate,
        MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseMovedEvent,
        MouseScrolledEvent, KeyPressedEvent, KeyReleasedEvent, KeyTypedEvent,
        WindowResizeEvent
    >;
    EventBox PackEvent(Event& e);


    class EventDispatcher
    {
        template<typename T>
        using EventFunc = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& e) : event_(e) {}
        
        template<typename T>
        bool Dispatch(EventFunc<T> func) {
            if (event_.GetEventType() == T::GetStaticType()) {
                event_.Handled = func(*(T*)&event_);
                return true;
            }
            return false;
        }
    private:
        Event& event_;
    };

}