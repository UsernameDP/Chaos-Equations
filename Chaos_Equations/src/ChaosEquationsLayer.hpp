#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"

#include <stack>

using namespace GLCore;

class ChaosEquationsLayer : public Layer
{
private:
	/*Axis*/
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

	/*Particle*/
	struct Particle {
		glm::vec4 pos;
		glm::vec4 color;
		glm::vec4 history[249]; //Trail size is essentilly 100 since pos counts
	};

	std::vector<Particle> particles;

	//Simulation Settings:
	int numberOfParticles = 100;
	glm::vec3 center = glm::vec3(0, 0, 0);
	float maxDisplacement = 0.2f; //displacement from center

	static const size_t nextGenFunctionDefinition_Size = 10000;
	char nextGenFunctionDefinition[nextGenFunctionDefinition_Size] =
		"vec4 nextGen(vec4 current) {\n"
		"    vec4 next = current;\n"
		"    return next;\n"
		"}\n";

	//ImGui Flags
	bool showImGui = true;
	bool currentSPACE = false;
	bool lastSPACE = false;

	//Simulation Flags
	bool stop = false; //stop - Temporarily stops running nextGen()

	//OpenGL Objects
		//Computing
	std::unique_ptr<Extension::Primitives::SSBO> particles_SSBO = nullptr;
	std::unique_ptr<Extension::Shaders::ComputeShader> nextGen_shader = nullptr;
		//Rendering
	std::unique_ptr<Extension::Primitives::VBO> particles_VBO = nullptr;
	std::unique_ptr<Extension::Primitives::VAO> particles_VAO = nullptr;
	Extension::Shaders::Shader* particles_shader = nullptr;
	
	std::unique_ptr<Extension::Cameras::PerspectiveCamera> camera = nullptr;

private:
	//Chaos Equations Methods
	void initGen() {
		static bool firstCall = true;

		/*InitGen*/
		Extension::Shaders::ComputeShader* initGen_shader = &Extension::AssetPool::getComputeShader("InitGen");
		particles = std::vector<Particle>(numberOfParticles);

		if (firstCall)
			particles_SSBO = std::make_unique<Extension::Primitives::SSBO>(GL_STATIC_DRAW, &particles);
		else
			particles_SSBO->updateAndReallocateData(GL_STATIC_DRAW, &particles);
		
		initGen_shader->use();
		particles_SSBO->bindAt(0);
		initGen_shader->uploadVec3f("center", center);
		initGen_shader->uploadFloat("maxDisplacement", maxDisplacement);
		initGen_shader->dispatch(glm::vec3(particles.size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		particles_SSBO->unbind();
		initGen_shader->detach();

		/*Setup NextGen*/
		std::string nextGen_GLSLSrc = std::string(Extension::AssetPool::getGLSL_SRC("nextGen.comp"));
		size_t replacePos = nextGen_GLSLSrc.find("${nextGenFunction}");
		nextGen_GLSLSrc.replace(replacePos, 19, nextGenFunctionDefinition);

		nextGen_shader = std::make_unique<Extension::Shaders::ComputeShader>("NextGen");
		nextGen_shader->addPrimitiveShader(new Extension::Shaders::PrimitiveShader(GL_COMPUTE_SHADER,
			"nextGen.comp", nextGen_GLSLSrc));
		nextGen_shader->compile();

		/*Camera*/
		Extension::Cameras::PerspectiveCameraProps cameraProps(
			100.0f,
			90.0f,
			0.0f,
			center,
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f,
			0.1f,
			100.0f
		);
		cameraProps.enableRotateAboutTargetWithKeys();
		cameraProps.enableFOVWithScroll();
		camera = std::make_unique<Extension::Cameras::PerspectiveCamera>(cameraProps);

		/*Particles*/
		std::vector<unsigned int> particlesIndexVector(numberOfParticles);
		for (unsigned int i = 0; i < particlesIndexVector.size(); i++)
			particlesIndexVector[i] = i;

		if (firstCall) {
			particles_VAO = std::make_unique<Extension::Primitives::VAO>();
			particles_VAO->bind();
			particles_VBO = std::make_unique<Extension::Primitives::VBO>(GL_STATIC_DRAW, &particlesIndexVector);
			particles_VAO->addVertexAttributeInt(0, 1, GL_UNSIGNED_INT, sizeof(unsigned int), (void*)0);
			particles_VAO->disableAttributes();
		}
		else {
			particles_VBO->updateAndReallocateData(GL_STATIC_DRAW, &particlesIndexVector);
		}

		if (firstCall)
			firstCall = false;
	}
	void nextGen(const GLCore::TimeStep& ts) {
		nextGen_shader->use();
		nextGen_shader->uploadFloat("dt", ts.getDeltaSeconds());
		particles_SSBO->bindAt(0);
		nextGen_shader->dispatch(glm::vec3(particles.size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		particles_SSBO->unbind();
		nextGen_shader->detach();
	}
	void render() {
		particles_shader->use();
		particles_shader->uploadMat4f("VP", camera->getViewProjection());
		particles_SSBO->bindAt(0);
		particles_VAO->bind();

		glDrawArrays(GL_POINTS, 0, particles.size());

		particles_shader->detach();
		particles_VAO->unbind();
	}

	//GLCore::Layer Methods
public:
	ChaosEquationsLayer() : Layer("ChaosEquationsLayer")
	{

	}
	virtual ~ChaosEquationsLayer()
	{
		
	}

	virtual void onAttach() override
	{
		/*Axis*/
		axis_shader = &Extension::AssetPool::getShader("Axis");
		axis_VAO = std::make_unique<Extension::Primitives::VAO>();
		axis_VBO = std::make_unique<Extension::Primitives::VBO>(GL_DYNAMIC_DRAW, &axisVertices);
		axis_VAO->addVertexAttributeFloat(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		axis_VAO->disableAttributes();

		/*Particle*/
		particles_shader = &Extension::AssetPool::getShader("Chaos");
		initGen();
	}
	virtual void onDetach() override
	{

	}
	virtual void onUpdate(const GLCore::TimeStep &ts) override
	{
		camera->onUpdate(ts, Extension::Cameras::PerspectiveCameraOptions::ROTATE_USING_CAMERA_TARGET);

		axis_shader->use();
		axis_shader->uploadMat4f("VP", camera->getViewProjection());
		axis_VAO->bind();

		glDrawArrays(GL_LINES, 0, 6);

		axis_VAO->unbind();
		axis_shader->detach();

		render();
		if (!stop) { //render nextGen after so we can see gen 0
			nextGen(ts);
		}
	}
	virtual void onImguiUpdate(const GLCore::TimeStep &ts) override
	{
		WindowProps props = Application::get().getWindow().getProps();
		currentSPACE = props.getKeyPressed(GLFW_KEY_SPACE);

		if (currentSPACE && 
			currentSPACE != lastSPACE &&
			!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
			showImGui = !showImGui;
		}

		if (showImGui) {
			//Displaying FPS
			ImGui::SetNextWindowPos(ImVec2(
				props.getPosX(),
				props.getPosY()),
				ImGuiCond_Always);

			//FPS 
			if (ImGui::Begin("FPS", &showImGui, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize)) {
				ImGui::Text("FPS : %.2f", 1 / ts.getDeltaSeconds());
			}
			ImGui::End();

			ImGui::SetNextWindowPos(ImVec2(
				props.getPosX() + props.getWidth() * (1- 0.25),
				props.getPosY()),
				ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(
				props.getWidth() * 0.25,
				props.getHeight()),
				ImGuiCond_Always);
			if (ImGui::Begin("Chaos Equations", &showImGui, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse)) {
				if (stop) {
					if (ImGui::Button("Continue")) {
						stop = false;
					}
				}
				else {
					if (ImGui::Button("Stop")) {
						stop = true;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Apply")) {
					initGen();
				}

				ImGui::SeparatorText("Simulation Settings : ");
			
				if (ImGui::InputInt("Number of Particles", &numberOfParticles, 10, 100, ImGuiInputTextFlags_EnterReturnsTrue)) {
					initGen(); //restart simulation
				}
				if (ImGui::InputFloat3("Center / Spawn Point", center.data.data, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
					initGen();
				}
				if (ImGui::InputFloat("Displacement from Center", &maxDisplacement, 0.01f, 0.1f, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
					initGen();
				}
				
				ImGui::Text("Define NextGen function for Chaos Equations");
				ImGui::Text("Available variables & Constants : ");
				ImGui::BulletText("dt - FLOAT time difference between each render in seconds");
				ImGui::InputTextMultiline("##Define Next Generation", nextGenFunctionDefinition, nextGenFunctionDefinition_Size, ImVec2(ImGui::GetColumnWidth(), ImGui::GetContentRegionAvail().y - 50), ImGuiInputTextFlags_AllowTabInput);
			}
			ImGui::End();
		}

		lastSPACE = currentSPACE;
	}
};