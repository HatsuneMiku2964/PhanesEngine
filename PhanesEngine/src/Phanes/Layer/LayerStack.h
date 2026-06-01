#pragma once

#include "Phanes/Core.h"
#include "Layer.h"

namespace Phanes {
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return Layers_.begin(); }
		std::vector<Layer*>::iterator end() { return Layers_.end(); }

	protected:
		std::vector<Layer*> Layers_;
		std::vector<Layer*>::iterator LayerInsert_;
	};
}