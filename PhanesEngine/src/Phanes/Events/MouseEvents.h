#pragma once

#include "Events.h"

namespace Phanes {
	class PN_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: mouseX__(x), mouseY__(y) {}

		inline float GetX() const { return mouseX__; }
		inline float GetY() const { return mouseY__; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << mouseX__ << ", " << mouseY__;
			return ss.str();
		}

		IMPL_EVENT_TYPE(MouseMoved)
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse)
	private:
		float mouseX__, mouseY__;
	};

	class PN_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: XOffset__(x), YOffset__(y) {
		}

		inline float GetXOffset() const { return XOffset__; }
		inline float GetYOffset() const { return YOffset__; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << XOffset__ << ", " << YOffset__ ;
			return ss.str();
		}

		IMPL_EVENT_TYPE(MouseScrolled)
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse)
	private:
		float XOffset__, YOffset__;
	};

	// base class for MouseButtonPressedEvent and MouseButtonReleasedEvent
	class PN_API MouseButtonEvent : public Event
	{
	public:
		inline int GetButtonCode() const { return buttonCode_; }
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse)

	protected:
		MouseButtonEvent(int buttoncode) : buttonCode_(buttoncode) {}
		int buttonCode_;
	};
	
	class PN_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << buttonCode_;
			return ss.str();
		}
		IMPL_EVENT_TYPE(MouseButtonPressed)
	};

	class PN_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << buttonCode_;
			return ss.str();
		}
		IMPL_EVENT_TYPE(MouseButtonReleased)
	};
}