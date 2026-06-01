#pragma once

#include "Events.h"

namespace Phanes {
	class PN_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width_(width), height_(height) {}

		inline unsigned int GetWidth() const { return width_; }
		inline unsigned int GetHeight() const { return height_; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << GetName() << ": " << width_ << ", " << height_;
			return ss.str();
		}

		IMPL_EVENT_TYPE(WindowResize)
		IMPL_EVENT_CATEGORY(EventCategories::Application)
	private:
		unsigned int width_, height_;
	};

	class PN_API WindowCloseEvent : public Event
	{
	public:
		IMPL_EVENT_TYPE(WindowClose)
		IMPL_EVENT_CATEGORY(EventCategories::Application)
	};

	class PN_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		IMPL_EVENT_TYPE(AppTick)
		IMPL_EVENT_CATEGORY(EventCategories::Application)
	};

	class PN_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		IMPL_EVENT_TYPE(AppUpdate)
		IMPL_EVENT_CATEGORY(EventCategories::Application)
	};

	class PN_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		IMPL_EVENT_TYPE(AppRender)
		IMPL_EVENT_CATEGORY(EventCategories::Application)
	};
}