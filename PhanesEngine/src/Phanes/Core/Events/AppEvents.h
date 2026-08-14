#pragma once

#include "Events.h"

namespace PN
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height)
            : width(width), height(height)
        {
        }

        pn_forceinline uint32_t GetWidth() const { return width; }
        pn_forceinline uint32_t GetHeight() const { return height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << width << ", " << height;
            return ss.str();
        }

        IMPL_EVENT_TYPE(WindowResize);
        IMPL_EVENT_CATEGORY(EventCategories::Application);
    private:
        uint32_t width, height;
    };
    class WindowCloseEvent : public Event
    {
    public:
        IMPL_EVENT_TYPE(WindowClose);
        IMPL_EVENT_CATEGORY(EventCategories::Application);
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        IMPL_EVENT_TYPE(AppTick);
        IMPL_EVENT_CATEGORY(EventCategories::Application);
    };
    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        IMPL_EVENT_TYPE(AppUpdate);
        IMPL_EVENT_CATEGORY(EventCategories::Application);
    };
    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        IMPL_EVENT_TYPE(AppRender);
        IMPL_EVENT_CATEGORY(EventCategories::Application);
    };
}