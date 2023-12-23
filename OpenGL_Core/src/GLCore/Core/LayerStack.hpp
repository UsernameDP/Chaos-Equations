#pragma once
#include "Layer.hpp"

namespace GLCore {
	class LayerStack {
	private:
		std::vector<Layer*> layers;
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushLayerFront(Layer* layer);
		//void popLayer(const std::string& name); Remove is not needed most likely

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	};
}