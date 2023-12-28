#pragma once

class Settings {
	
	struct SimulationSettings {
		int numberOfParticles = 100;
		glm::vec3 spawnPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		float maxDisplacement = 0.1f; //displacement from center

		float higestSpeed = 10.0f;
		glm::vec3 lowestSpeedColor = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 highestSpeedColor = glm::vec3(1.0f, 0.0f, 0.0f);

		static const size_t nextGenFunctionDefinition_Size = 10000;
		char nextGenFunctionDefinition[nextGenFunctionDefinition_Size] =
			"vec4 nextGen(vec4 current) {\n"
			"    vec3 next;\n"
			"    float scale = 1.0;\n"
			"    float x = current.x;\n"
			"    float y = current.y;\n"
			"    float z = current.z;\n"
			"    return vec4(next, 1.0);\n"
			"}\n";

		SimulationSettings() = default;
	};

	struct SimulationFlags {
		bool stop = false;
		bool restart = false;
		bool showImGui = true;
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