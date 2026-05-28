#pragma once

#include "Events.h"
#include <sstream>

namespace Phanes {
	// base class for KeyPressedEvent, KeyReleasedEvent and KeyTypedEvent
	class PN_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keyCode_; }
		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Keyboard)

	protected:
		KeyEvent(int keycode) : keyCode_(keycode) {}
		int keyCode_;
	};

	class PN_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, unsigned int repeatCount)
			: KeyEvent(keycode), repeatCount_(repeatCount) {}
		inline unsigned int GetRepeatCount() const { return repeatCount_; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << keyCode_ << " (" << repeatCount_ << " repeats)";
			return ss.str();
		}
		IMPL_EVENT_TYPE(KeyPressed)

	private:
		unsigned int repeatCount_;
	};

	class PN_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << keyCode_;
			return ss.str();
		}
		IMPL_EVENT_TYPE(KeyReleased)
	};
}