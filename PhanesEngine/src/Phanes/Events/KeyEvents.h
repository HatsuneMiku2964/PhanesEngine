#pragma once

#include "Events.h"

namespace Phanes {
	// base class for KeyPressedEvent, KeyReleasedEvent and KeyTypedEvent
	class KeyEvent : public Event
	{
	public:
		pn_forceinline int GetKeyCode() const { return KeyCode_; }

		IMPL_EVENT_CATEGORY(EventCategories::Input | EventCategories::Keyboard)

	protected:
		KeyEvent(int keycode) : KeyCode_(keycode) {}
		int KeyCode_;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, unsigned int repeatCount)
			: KeyEvent(keycode), RepeatCount_(repeatCount) {}

		pn_forceinline unsigned int GetRepeatCount() const { return RepeatCount_; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << KeyCode_ << " (" << RepeatCount_ << " repeats)";
			return ss.str();
		}
		IMPL_EVENT_TYPE(KeyPressed)

	private:
		unsigned int RepeatCount_;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << KeyCode_;
			return ss.str();
		}
		IMPL_EVENT_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << KeyCode_;
			return ss.str();
		}
		IMPL_EVENT_TYPE(KeyTyped)
	};
}