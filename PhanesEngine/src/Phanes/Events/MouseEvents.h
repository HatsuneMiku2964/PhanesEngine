#pragma once

#include "Events.h"

namespace Phanes {
	class PN_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: mouseX_(x), mouseY_(y) {}

		inline float GetX() const { return mouseX_; }
		inline float GetY() const { return mouseY_; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << mouseX_ << ", " << mouseY_;
			return ss.str();
		}

		IMPL_EVENT_TYPE(MouseMoved)
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse)
	private:
		float mouseX_, mouseY_;
	};

	class PN_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: xOffset_(x), yOffset_(y) {
		}

		inline float GetXOffset() const { return xOffset_; }
		inline float GetYOffset() const { return yOffset_; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << xOffset_ << ", " << yOffset_ ;
			return ss.str();
		}

		IMPL_EVENT_TYPE(MouseScrolled)
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse)
	private:
		float xOffset_, yOffset_;
	};

	// base class for MouseButtonPressedEvent and MouseButtonReleasedEvent
	class PN_API MouseButtonEvent : public Event
	{
	public:
		inline int GetButtonCode() const { return ButtonCode_; }
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse)

	protected:
		MouseButtonEvent(int buttoncode) : ButtonCode_(buttoncode) {}
		int ButtonCode_;
	};
	
	class PN_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << ButtonCode_;
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
			ss << GetName() << ": " << ButtonCode_;
			return ss.str();
		}
		IMPL_EVENT_TYPE(MouseButtonReleased)
	};
}