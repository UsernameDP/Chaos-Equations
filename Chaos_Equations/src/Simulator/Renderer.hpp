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

	std::unique_ptr<Extension::Primitives::VBO> particles_VBO = nullptr;
	std::unique_ptr<Extension::Primitives::VAO> particles_VAO = nullptr;
	Extension::Shaders::Shader* particles_shader = nullptr;
public:
	Renderer(std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera, std::shared_ptr<Settings> settings, std::shared_ptr<SimulatorSharedObjects> simulatorSharedObjects) {
		this->camera = camera;
		this->settings = settings;
		this->simulatorSharedObjects = simulatorSharedObjects;
	}
	~Renderer() = default;

	void init() {
		axis_shader = &Extension::AssetPool::getShader("Axis");
		axis_VAO = std::make_unique<Extension::Primitives::VAO>();
		axis_VBO = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &axisVertices);
		axis_VAO->addVertexAttributeFloat(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		axis_VAO->disableAttributes();


		particles_shader = &Extension::AssetPool::getShader("Chaos");

		std::vector<unsigned int> particlesIndexVector(settings->simulationSettings->numberOfParticles);
		for (unsigned int i = 0; i < particlesIndexVector.size(); i++)
			particlesIndexVector[i] = i;

		particles_VAO = std::make_unique<Extension::Primitives::VAO>();
		particles_VAO->bind();
		particles_VBO = std::make_unique<Extension::Primitives::VBO>(GL_STATIC_DRAW, &particlesIndexVector);
		particles_VAO->addVertexAttributeInt(0, 1, GL_UNSIGNED_INT, sizeof(unsigned int), (void*)0);
		particles_VAO->disableAttributes();
	}
	
	void restart() {
		std::vector<unsigned int> particlesIndexVector(settings->simulationSettings->numberOfParticles);
		for (unsigned int i = 0; i < particlesIndexVector.size(); i++)
			particlesIndexVector[i] = i;

		particles_VBO->updateAndReallocateData(GL_STATIC_DRAW, &particlesIndexVector);
	}

	void render(const TimeStep& ts) {
		axis_shader->use();
		axis_shader->uploadMat4f("VP", camera->getViewProjection());
		axis_VAO->bind();

		glDrawArrays(GL_LINES, 0, 6);

		axis_VAO->unbind();
		axis_shader->detach();

		particles_shader->use();
		particles_shader->uploadMat4f("VP", camera->getViewProjection());
		simulatorSharedObjects->particles_SSBO->bindAt(0);
		particles_VAO->bind();

		glDrawArrays(GL_POINTS, 0, simulatorSharedObjects->particles->size());

		particles_shader->detach();
		particles_VAO->unbind();
		simulatorSharedObjects->particles_SSBO->unbind();
	}

};