#pragma once

#include "Phanes/Input.h"
namespace Phanes
{
    class WindowsInput : public Input
    {
    public:

    protected:
        virtual float GetMouseX_Impl() override;
        virtual float GetMouseY_Impl() override;
        virtual std::pair<float, float> GetMousePos_Impl() override;
        virtual bool IsKeyPressed_Impl(int keycode) override;
        virtual bool IsMouseButtonPressed_Impl(int button) override;

    private:

    };
}