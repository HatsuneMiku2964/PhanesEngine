#pragma once

#include "Phanes/Core/Input.h"
namespace PN
{
    class WindowsInput : public Input
    {
    protected:
        float GetMouseX_Impl() override;
        float GetMouseY_Impl() override;
        std::pair<float, float> GetMousePos_Impl() override;
        bool IsKeyPressed_Impl(int keycode) override;
        bool IsMouseButtonPressed_Impl(int button) override;
    };
}