#pragma once

#include "Events.h"
#include <sstream>

namespace Phanes {
	class PN_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width__(width), height__(height) {}

		inline unsigned int GetWidth() const { return width__; }
		inline unsigned int GetHeight() const { return height__; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << width__ << ", " << height__;
			return ss.str();
		}

		IMPL_EVENT_TYPE(WindowResize)
		IMPL_EVENT_CATEGORY(EventCategories::Application)
	private:
		unsigned int width__, height__;
	};

	class PN_API WindowCloseEvent : public Event
	{
	public:
		IMPL_EVENT_TYPE(WindowClose)
		IMPL_EVENT_CATEGORY(EventCategories::Application)

		std::string ToString() const override { return GetName(); }
	};

	class PN_API AppTickEvent : public Event
	{
	public:
		IMPL_EVENT_TYPE(AppTick)
		IMPL_EVENT_CATEGORY(EventCategories::Application)

		std::string ToString() const override { return GetName(); }
	};
}