#pragma once

#include "Phanes/Core/Events/Events.h"
#include "Phanes/Core/Events/AppEvents.h"
#include "Phanes/Core/Events/MouseEvents.h"

namespace PN {
    class OrthoCameraController
    {
    public:
        OrthoCameraController(float aspect_ratio = 16.f / 9.f);

        void OnUpdate(TimeStep ts);
        void OnEvent(Event& e);

        pn_forceinline OrthographicCamera& GetCamera() { return camera; }
        pn_forceinline const OrthographicCamera& GetCamera() const { return camera; }

        pn_forceinline float GetZoomLevel() { return zoom_lvl; }
        pn_forceinline void SetZoomLevel(float lvl) { zoom_lvl = lvl; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        float aspect_ratio;
        float zoom_lvl = 1.f;

        OrthographicCamera camera;

        float move_speed = 30.f;
        float rot_speed = 180.f;
    };
}
