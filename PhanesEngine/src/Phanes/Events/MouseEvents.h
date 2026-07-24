#pragma once

#include "Events.h"

namespace Phanes {
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: mouseX_(x), mouseY_(y) {}

		pn_forceinline float GetX() const { return mouseX_; }
		pn_forceinline float GetY() const { return mouseY_; }

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

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: xOffset_(x), yOffset_(y) {
		}

		pn_forceinline float GetXOffset() const { return xOffset_; }
		pn_forceinline float GetYOffset() const { return yOffset_; }

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
	class MouseButtonEvent : public Event
	{
	public:
		pn_forceinline int GetButtonCode() const { return ButtonCode_; }
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Mouse)

	protected:
		MouseButtonEvent(int buttoncode) : ButtonCode_(buttoncode) {}
		int ButtonCode_;
	};
	
	class MouseButtonPressedEvent : public MouseButtonEvent
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

	class MouseButtonReleasedEvent : public MouseButtonEvent
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