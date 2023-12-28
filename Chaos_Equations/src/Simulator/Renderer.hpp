#pragma once

class Renderer {
	std::shared_ptr<Settings> settings = nullptr;
	std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera = nullptr;
	std::shared_ptr<SimulatorSharedObjects> simulatorSharedObjects = nullptr;

	Extension::Shaders::Shader* axis_shader;
	std::unique_ptr<Extension::Primitives::VAO> axis_VAO;
	std::unique_ptr<Extension::Primitives::VBO> axis_VBO;
	std::vector<float> axisVertices = {
		//X Axis (Red)
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		//Y Axis (Green)
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		//Z Axis (Blue)
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	std::unique_ptr<Extension::Primitives::VAO> particles_VAO = nullptr;
	Extension::Shaders::Shader* particles_shader = nullptr;

	std::unique_ptr<Extension::Primitives::EBO> particlesHistory_EBO = nullptr;
	std::unique_ptr<Extension::Primitives::VAO> particlesHistory_VAO = nullptr;
	Extension::Shaders::Shader* particlesHistory_shader = nullptr;
	unsigned int setIndicesSize = 0;

	std::unique_ptr<Extension::Primitives::VBO> cameraTarget_VBO = nullptr;
	std::unique_ptr<Extension::Primitives::VAO> cameraTarget_VAO = nullptr;
	Extension::Shaders::Shader* cameraTarget_shader = nullptr;
public:
	Renderer(std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera, std::shared_ptr<Settings> settings, std::shared_ptr<SimulatorSharedObjects> simulatorSharedObjects) {
		this->camera = camera;
		this->settings = settings;
		this->simulatorSharedObjects = simulatorSharedObjects;
	}
	~Renderer() = default;

	void init() {
		std::shared_ptr<Settings::SimulationSettings> simSettings = settings->simulationSettings;

		axis_shader = &Extension::AssetPool::getShader("Axis");
		axis_VAO = std::make_unique<Extension::Primitives::VAO>();
		axis_VBO = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &axisVertices);
		axis_VAO->addVertexAttributeFloat(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		axis_VAO->disableAttributes();

		cameraTarget_shader = &Extension::AssetPool::getShader("CameraTarget");
		cameraTarget_VAO = std::make_unique<Extension::Primitives::VAO>();
		cameraTarget_VBO = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, 3 * sizeof(float));
		cameraTarget_VAO->addVertexAttributeFloat(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		cameraTarget_VAO->disableAttributes();

		particles_shader = &Extension::AssetPool::getShader("Particle");
		particles_VAO = std::make_unique<Extension::Primitives::VAO>();

		particlesHistory_shader = &Extension::AssetPool::getShader("History");
		particlesHistory_VAO = std::make_unique<Extension::Primitives::VAO>();
		particlesHistory_VAO->bind();
		setIndicesSize = simSettings->numberOfParticles * simSettings->trailSize * 2; //*2 because we drawing with GL_LINES
		std::vector<unsigned int> indices(setIndicesSize); 
		for (unsigned int i = 0; i < simSettings->numberOfParticles * simSettings->trailSize; i++) {
			unsigned int indiceIndex = i * 2;
			indices[indiceIndex] = i;
			indices[indiceIndex + 1] = i + 1;
		}
		particlesHistory_EBO = std::make_unique<Extension::Primitives::EBO>(GL_STATIC_DRAW, &indices);
	}
	
	void restart() {
		std::shared_ptr<Settings::SimulationSettings> simSettings = settings->simulationSettings;

		setIndicesSize = simSettings->numberOfParticles * simSettings->trailSize * 2;
		std::vector<unsigned int> indices(setIndicesSize); 
		for (unsigned int i = 0; i < simSettings->numberOfParticles * simSettings->trailSize; i++) {
			unsigned int indiceIndex = i * 2;
			indices[indiceIndex] = i;
			indices[indiceIndex + 1] = i + 1;
		}
		particlesHistory_EBO->updateAndReallocateData(GL_STATIC_DRAW, &indices);
	}

	void render(const TimeStep& ts) {
		std::shared_ptr<Settings::SimulationSettings> simSettings = settings->simulationSettings;
		/*Render Trails*/
		particlesHistory_shader->use();
		particlesHistory_shader->uploadMat4f("VP", camera->getViewProjection());
		simulatorSharedObjects->particles_SSBO->bindAt(0);
		simulatorSharedObjects->particlesHistory_SSBO->bindAt(1);
		particlesHistory_VAO->bind();
		glDrawElements(GL_LINES, simSettings->numberOfParticles * simSettings->trailSize * 2, GL_UNSIGNED_INT, 0);

		/*Render Particle*/
		particles_shader->use();
		particles_shader->uploadMat4f("VP", camera->getViewProjection());
		simulatorSharedObjects->particles_SSBO->bindAt(0);
		particles_VAO->bind();
		glDrawArrays(GL_POINTS, 0, simulatorSharedObjects->setNumberOfParticles);
		particles_shader->detach();
		particles_VAO->unbind();
		simulatorSharedObjects->particles_SSBO->unbind();

		if (settings->simulationFlags->showImGui) {
			/*Axis*/
			axis_shader->use();
			axis_shader->uploadFloat("radius", camera->getProps().radius * 0.5);
			axis_shader->uploadMat4f("VP", camera->getViewProjection());
			axis_VAO->bind();

			glDrawArrays(GL_LINES, 0, 6);

			axis_VAO->unbind();
			axis_shader->detach();

			/*CameraTarget Point*/
			glm::vec3 cameraTarget = camera->getProps().cameraTarget;
			std::vector<float> cameraTargetVector = { cameraTarget.x, cameraTarget.y, cameraTarget.z };
			cameraTarget_VBO->updateData(&cameraTargetVector);
			cameraTarget_shader->use();
			cameraTarget_shader->uploadMat4f("VP", camera->getViewProjection());
			cameraTarget_VAO->bind();

			glDrawArrays(GL_POINTS, 0, 1);

			cameraTarget_shader->detach();
			cameraTarget_VAO->unbind();
		}

	}

};