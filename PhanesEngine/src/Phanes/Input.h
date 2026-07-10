#pragma once

namespace Phanes {
    // TIP: singleton
    class PN_API Input
    {
    public:
        inline static float GetMouseX() { return instance_->GetMouseX_Impl(); }
        inline static float GetMouseY() { return instance_->GetMouseY_Impl(); }
        inline static std::pair<float, float> GetMousePos() { return instance_->GetMousePos_Impl(); }
        inline static bool IsKeyPressed(int keycode) { return instance_->IsKeyPressed_Impl(keycode); }
        inline static bool IsMouseButtonPressed(int button) { return instance_->IsMouseButtonPressed_Impl(button); }

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
