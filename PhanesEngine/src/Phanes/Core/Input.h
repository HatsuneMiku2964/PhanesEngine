#pragma once
#include "Core.h"

namespace PN {
    // INFO: singleton
    class Input
    {
    public:
        pn_forceinline static float GetMouseX() { return instance_->GetMouseX_Impl(); }
        pn_forceinline static float GetMouseY() { return instance_->GetMouseY_Impl(); }
        pn_forceinline static std::pair<float, float> GetMousePos() { return instance_->GetMousePos_Impl(); }
        pn_forceinline static bool IsKeyPressed(int keycode) { return instance_->IsKeyPressed_Impl(keycode); }
        pn_forceinline static bool IsMouseButtonPressed(int button) { return instance_->IsMouseButtonPressed_Impl(button); }

    protected:
        virtual float GetMouseX_Impl() = 0;
        virtual float GetMouseY_Impl() = 0;
        virtual std::pair<float, float> GetMousePos_Impl() = 0;
        virtual bool IsKeyPressed_Impl(int keycode) = 0;
        virtual bool IsMouseButtonPressed_Impl(int button) = 0;

    private:
        static Input* instance_;
    };
}
