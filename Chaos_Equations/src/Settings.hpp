#pragma once

class Settings {
	
	struct SimulationSettings {
		int numberOfParticles = 2;
		glm::vec3 spawnPoint = glm::vec3(0, 0, 0);
		float maxDisplacement = 0.001f; //displacement from center
		static const size_t nextGenFunctionDefinition_Size = 10000;
		char nextGenFunctionDefinition[nextGenFunctionDefinition_Size] =
			"vec4 nextGen(vec4 current) {\n"
			"    vec4 next = current;\n"
			"    return next;\n"
			"}\n";

		SimulationSettings() = default;
	};

	struct SimulationFlags {
		bool stop = false;
		bool restart = false;
	};
	
public:
	std::shared_ptr<SimulationSettings> simulationSettings = nullptr;
	std::shared_ptr<SimulationFlags> simulationFlags = nullptr;

	Settings() {
		simulationSettings = std::make_shared<SimulationSettings>();
		simulationFlags = std::make_shared<SimulationFlags>();
	}
	~Settings() = default;
};