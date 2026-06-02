#pragma once

#include "Phanes/Core.h"

namespace Phanes {

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
	inline EventCategories operator|(EventCategories a, EventCategories b) {
		return static_cast<EventCategories>(static_cast<int>(a) | static_cast<int>(b));
	}
	inline EventCategories operator&(EventCategories a, EventCategories b) {
		return static_cast<EventCategories>(static_cast<int>(a) & static_cast<int>(b));
	}
	inline EventCategories& operator|=(EventCategories& a, EventCategories b) {
		a = a | b; 
		return a;
	}
	inline bool HasCategory(EventCategories flags, EventCategories category) {
		return (static_cast<int>(flags) & static_cast<int>(category)) != 0;
	}

// macros for u to impl Phanes::Event in your event class FASTER, u can use this macro to impl the GetEventType(), GetName() and GetCategoryFlags() function
#define IMPL_EVENT_TYPE(type)	static EventTypes GetStaticType() { return EventTypes::##type; }\
								virtual EventTypes GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define IMPL_EVENT_CATEGORY(category)	virtual int GetCategoryFlags() const override { return static_cast<int>(category); }
// ~macros

	class PN_API Event
	{
	public:
		// pure virtual functions, must be implemented by derived classes
		virtual EventTypes GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		// mainly for debug
		virtual std::string ToString() const { return GetName(); }
		//utility function to check if the event is in a category
		inline bool IsInCategory(EventCategories category) const { return GetCategoryFlags() & static_cast<int>(category); }

		bool Handled_ = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : event_(event) {}

		template<typename T>
		bool Dispatch(EventFunc<T> func) {
			if (event_.GetEventType() == T::GetStaticType()) {
				event_.Handled_ = func(*(T*)&event_);
				return true;
			}
			return false;
		}
	private:
		Event& event_;
	};

	inline std::ostream& operator<<(std::ostream& o, const Event& e) {
		return o << e.ToString();
	}
}