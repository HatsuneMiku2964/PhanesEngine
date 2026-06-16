#pragma once

#include "Phanes/Layer/Layer.h"

namespace Phanes {
	class PN_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer ( );
		~ImGuiLayer ( );

		void OnAttach ( );
		void OnDetach ( );
		void OnUpdate ( );
		void OnEvent ( Event& e );

	private:
		float time_ = 0.f;
	};
}