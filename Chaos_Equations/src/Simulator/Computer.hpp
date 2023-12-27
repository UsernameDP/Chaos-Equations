#pragma once

class Computer {
public:
	std::shared_ptr<Settings> settings;
	std::shared_ptr<SimulatorSharedObjects> simulatorSharedObjects = nullptr;

	Computer(std::shared_ptr<Settings> settings, std::shared_ptr<SimulatorSharedObjects> simulatorSharedObjects) {
		this->settings = settings;
		this->simulatorSharedObjects = simulatorSharedObjects;
	}

	std::unique_ptr<Extension::Shaders::ComputeShader> nextGen_shader = nullptr;

	void initGen() {
		static bool firstCall = true;

		/*InitGen*/
		Extension::Shaders::ComputeShader* initGen_shader = &Extension::AssetPool::getComputeShader("InitGen");
		simulatorSharedObjects->particles = std::make_shared<std::vector<Particle>>(settings->simulationSettings->numberOfParticles);

		if (firstCall)
			simulatorSharedObjects->particles_SSBO = std::make_unique<Extension::Primitives::SSBO>(GL_STATIC_DRAW, simulatorSharedObjects->particles.get());
		else
			simulatorSharedObjects->particles_SSBO->updateAndReallocateData(GL_STATIC_DRAW, simulatorSharedObjects->particles.get());

		initGen_shader->use();
		simulatorSharedObjects->particles_SSBO->bindAt(0);
		initGen_shader->uploadVec3f("spawnPoint",  settings->simulationSettings->spawnPoint);
		initGen_shader->uploadFloat("maxDisplacement", settings->simulationSettings->maxDisplacement);
		initGen_shader->dispatch(glm::vec3(simulatorSharedObjects->particles->size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		simulatorSharedObjects->particles_SSBO->unbind();
		initGen_shader->detach();

		/*Setup NextGen*/
		std::string nextGen_GLSLSrc = std::string(Extension::AssetPool::getGLSL_SRC("nextGen.comp"));
		size_t replacePos = nextGen_GLSLSrc.find("${nextGenFunction}");
		nextGen_GLSLSrc.replace(replacePos, 19, settings->simulationSettings->nextGenFunctionDefinition);

		nextGen_shader = std::make_unique<Extension::Shaders::ComputeShader>("NextGen");
		nextGen_shader->addPrimitiveShader(new Extension::Shaders::PrimitiveShader(GL_COMPUTE_SHADER,
			"nextGen.comp", nextGen_GLSLSrc));
		nextGen_shader->compile();

		if (firstCall)
			firstCall = false;
	}

	void nextGen(const TimeStep& ts) {
		nextGen_shader->use();
		nextGen_shader->uploadFloat("highestSpeed", settings->simulationSettings->higestSpeed);
		nextGen_shader->uploadVec3f("lowestSpeedColor", settings->simulationSettings->lowestSpeedColor);
		nextGen_shader->uploadVec3f("highestSpeedColor", settings->simulationSettings->highestSpeedColor);
		nextGen_shader->uploadFloat("dt", ts.getDeltaSeconds());
		simulatorSharedObjects->particles_SSBO->bindAt(0);
		
		nextGen_shader->dispatch(glm::vec3(simulatorSharedObjects->particles->size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		simulatorSharedObjects->particles_SSBO->unbind();
		nextGen_shader->detach();
	}



};