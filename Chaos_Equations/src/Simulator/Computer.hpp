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
		
		std::shared_ptr<Settings::SimulationSettings> simSettings = settings->simulationSettings;

		/*InitGen*/
		Extension::Shaders::ComputeShader* initGen_shader = &AssetPool::getComputeShader("InitGen");

		simulatorSharedObjects->setNumberOfParticles = simSettings->numberOfParticles;
		simulatorSharedObjects->setTrailSize = simSettings->trailSize;

		if (firstCall) {
			simulatorSharedObjects->particles_SSBO = std::make_shared<Primitives::SSBO>(GL_STATIC_DRAW, simulatorSharedObjects->setNumberOfParticles * sizeof(Particle));
			simulatorSharedObjects->particlesHistory_SSBO = std::make_shared<Primitives::SSBO>(GL_STATIC_DRAW, simulatorSharedObjects->setNumberOfParticles * simulatorSharedObjects->setTrailSize * sizeof(History));
		}
		else {
			simulatorSharedObjects->particles_SSBO->reallocateData(GL_STATIC_DRAW, simulatorSharedObjects->setNumberOfParticles * sizeof(Particle));
			simulatorSharedObjects->particlesHistory_SSBO->reallocateData(GL_STATIC_DRAW, simulatorSharedObjects->setNumberOfParticles * simulatorSharedObjects->setTrailSize * sizeof(History));
		}

		initGen_shader->use();
		simulatorSharedObjects->particles_SSBO->bindAt(0);
		simulatorSharedObjects->particlesHistory_SSBO->bindAt(1);
		initGen_shader->uploadUnsignedInt("trailSize", simSettings->trailSize);
		initGen_shader->uploadVec3f("spawnPoint",  simSettings->spawnPoint);
		initGen_shader->uploadFloat("maxDisplacement", simSettings->maxDisplacement);
		initGen_shader->dispatch(glm::vec3(simulatorSharedObjects->setNumberOfParticles, 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		simulatorSharedObjects->particles_SSBO->unbind();
		initGen_shader->detach();

		/*Setup NextGen*/
		std::string nextGen_GLSLSrc = std::string(Extension::AssetPool::getGLSL_SRC("nextGen.comp"));
		size_t replacePos = nextGen_GLSLSrc.find("${nextGenFunction}");
		nextGen_GLSLSrc.replace(replacePos, 19, simSettings->nextGenFunctionDefinition);

		nextGen_shader = std::make_unique<Extension::Shaders::ComputeShader>("NextGen");
		nextGen_shader->addPrimitiveShader(new Extension::Shaders::PrimitiveShader(GL_COMPUTE_SHADER,
			"nextGen.comp", nextGen_GLSLSrc));
		nextGen_shader->compile();

		if (firstCall)
			firstCall = false;
	}

	void nextGen(const TimeStep& ts) {
		std::shared_ptr<Settings::SimulationSettings> simSettings = settings->simulationSettings;

		nextGen_shader->use();
		nextGen_shader->uploadUnsignedInt("trailSize", simSettings->trailSize);
		nextGen_shader->uploadFloat("highestSpeed", simSettings->higestSpeed);
		nextGen_shader->uploadVec3f("lowestSpeedColor", simSettings->lowestSpeedColor);
		nextGen_shader->uploadVec3f("highestSpeedColor", simSettings->highestSpeedColor);
		nextGen_shader->uploadFloat("dt", ts.getDeltaSeconds());
		simulatorSharedObjects->particles_SSBO->bindAt(0);
		simulatorSharedObjects->particlesHistory_SSBO->bindAt(1);
		
		nextGen_shader->dispatch(glm::vec3(simulatorSharedObjects->setNumberOfParticles, 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		simulatorSharedObjects->particles_SSBO->unbind();
		nextGen_shader->detach();
	}



};