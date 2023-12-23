#pragma once
#include "TimeStep.hpp"

namespace GLCore {
	class Layer {
	protected:
		std::string name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;
	
		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(const TimeStep& ts) {}
		virtual void onImguiUpdate(const TimeStep& ts) {}

		inline const std::string& getName() const { return name; }
	};
}