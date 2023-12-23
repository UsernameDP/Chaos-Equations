#include "pch.hpp"
#include "LayerStack.hpp"

namespace GLCore {
	LayerStack::LayerStack() {}
	LayerStack::~LayerStack() {
		for (Layer* layer : layers) {
			layer->onDetach();
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		layers.push_back(layer);
		layer->onAttach();
	}

	void LayerStack::pushLayerFront(Layer* layer) {
		layers.emplace_back(layer);
		layer->onAttach();
	}
}