#include "pnpch.h"
#include "OrthoCameraController.h"

#include "Phanes/Core/Input.h"
#include "Phanes/Core/Events/EventsDispatch.h"
#include "Phanes/Core/KeyCodes/KeyCodes.h"

namespace PN
{
    OrthoCameraController::OrthoCameraController(float aspect_ratio)
        :aspect_ratio(aspect_ratio), camera(-aspect_ratio * zoom_lvl, aspect_ratio* zoom_lvl, -zoom_lvl, zoom_lvl)
    {

    }

    void OrthoCameraController::OnUpdate(TimeStep ts)
    {
        float move_delta = move_speed * (float) ts;
        float rot_delta = rot_speed * (float) ts;

        if (Input::IsKeyPressed(PN_KEY_W)) camera.SetPos(camera.GetPos() + glm::vec3(0.f, move_delta, 0.f));
        if (Input::IsKeyPressed(PN_KEY_A)) camera.SetPos(camera.GetPos() + glm::vec3(-move_delta, 0.f, 0.f));
        if (Input::IsKeyPressed(PN_KEY_S)) camera.SetPos(camera.GetPos() + glm::vec3(0.f, -move_delta, 0.f));
        if (Input::IsKeyPressed(PN_KEY_D)) camera.SetPos(camera.GetPos() + glm::vec3(move_delta, 0.f, 0.f));

        if (Input::IsKeyPressed(PN_KEY_Q)) camera.SetRot(camera.GetRot() - rot_delta);
        if (Input::IsKeyPressed(PN_KEY_E)) camera.SetRot(camera.GetRot() + rot_delta);
    }

    void OrthoCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        e.Handled = dispatcher.Dispatch(
            BIND_EVENT_FN(OnMouseScrolled), BIND_EVENT_FN(OnWindowResize)
        );
    }

    bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        zoom_lvl -= e.GetYOffset() * 0.1f;
        zoom_lvl = std::max(zoom_lvl, 0.05f);
        camera.SetProjection(-aspect_ratio * zoom_lvl, aspect_ratio * zoom_lvl, -zoom_lvl, zoom_lvl);
        return false;
    }
    bool OrthoCameraController::OnWindowResize(WindowResizeEvent& e)
    {
        aspect_ratio = (float) e.GetWidth() / (float) e.GetHeight();
        camera.SetProjection(-aspect_ratio * zoom_lvl, aspect_ratio * zoom_lvl, -zoom_lvl, zoom_lvl);
        return false;
    }
}
