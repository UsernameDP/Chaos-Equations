#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"

#include <stack>

using namespace GLCore;

class ChaosEquationsLayer : public Layer
{
private:
	struct Particle {
		glm::vec4 pos;
		glm::vec4 color;
		glm::vec4 history[99]; //Trail size is essentilly 100 since pos counts
	};

	std::vector<Particle> particles;

	//Simulation Settings:
	unsigned int numberOfParticles = 10000;
	glm::vec3 center = glm::vec3(0, 0, 0);
	float maxDisplacement = 0.1f; //displacement from center

	std::string nextGenFunctionDefinition =
		"vec4 nextGen(vec4 current) {\n"
		"    vec4 next = current;"
		"    return next;"
		"}\n";

	//ImGui Flags
	bool showImGui = true;
	bool lastSPACE = false;

	//Simulation Flags
	bool start = false; //start - initGen() then nextGen()
	bool stop = false; //stop - Temporarily stops running nextGen()

	//OpenGL Objects
		//Computing
	std::unique_ptr<Extension::Primitives::SSBO> particles_GPU = nullptr;
	std::unique_ptr<Extension::Shaders::ComputeShader> nextGen_shader = nullptr;


private:
	//Chaos Equations Methods
	void initGen() {
		static bool firstCall = true;
		if (!firstCall) {
			particles_GPU->unbind();
			particles_GPU->destroy();

			//TODO : Set new numberOfParticles, center, and maxDeltaDisplacement unless the variables can be binded to imgui gui
		}

		//Fill the particles vector
		Extension::Shaders::ComputeShader* initGen_shader = &Extension::AssetPool::getComputeShader("InitGen");
		particles = std::vector<Particle>(numberOfParticles);

		particles_GPU = std::make_unique<Extension::Primitives::SSBO>(GL_STATIC_DRAW, &particles);
		
		initGen_shader->use();
		particles_GPU->bindAt(0);
		initGen_shader->uploadVec3f("center", center);
		initGen_shader->uploadFloat("maxDisplacement", maxDisplacement);
		initGen_shader->dispatch(glm::vec3(particles.size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		particles_GPU->unbind();
		initGen_shader->detach();
		particles_GPU->readDataTo(&particles);

		//Set nextGen shader
		std::string nextGen_GLSLSrc = std::string(Extension::AssetPool::getGLSL_SRC("nextGen.comp"));
		size_t replacePos = nextGen_GLSLSrc.find("${nextGenFunction}");
		nextGen_GLSLSrc.replace(replacePos, 19, nextGenFunctionDefinition);

		nextGen_shader = std::make_unique<Extension::Shaders::ComputeShader>("NextGen");
		nextGen_shader->addPrimitiveShader(new Extension::Shaders::PrimitiveShader(GL_COMPUTE_SHADER,
			"nextGen.comp", nextGen_GLSLSrc));
		nextGen_shader->compile();

	}
	void nextGen(const GLCore::TimeStep& ts) {
		nextGen_shader->use();
		nextGen_shader->uploadFloat("dt", ts.getDeltaSeconds());
		particles_GPU->bindAt(0);
		nextGen_shader->dispatch(glm::vec3(particles.size(), 1, 1), GL_SHADER_STORAGE_BARRIER_BIT);

		particles_GPU->unbind();
		nextGen_shader->detach();

		//particles_GPU->readDataTo(&particles);
	}
	void render() {

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
		initGen();
	}
	virtual void onDetach() override
	{
	}
	virtual void onUpdate(const GLCore::TimeStep &ts) override
	{
		render();
		if (!stop) { //render nextGen after so we can see gen 0
			nextGen(ts);
		}
	}
	virtual void onImguiUpdate(const GLCore::TimeStep &ts) override
	{
		if (Application::get().getKeyPressed(GLFW_KEY_SPACE) && 
			Application::get().getKeyPressed(GLFW_KEY_SPACE) != lastSPACE && 
			!Application::get().isImGuiFocused()) {
			showImGui = !showImGui;
		}

		if (showImGui) {
			//Displaying FPS
			ImGui::SetNextWindowPos(ImVec2(
				Application::get().getWindow().getProps().getPosX(),
				Application::get().getWindow().getProps().getPosY()),
				ImGuiCond_Always);

			//FPS 
			if (ImGui::Begin("FPS", &showImGui, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize)) {
				ImGui::Text("FPS : %.2f", 1 / ts.getDeltaSeconds());
			}
			ImGui::End();

			ImGui::SetNextWindowPos(ImVec2(
				Application::get().getWindow().getProps().getPosX() + Application::get().getWindow().getProps().getWidth() - 350,
				Application::get().getWindow().getProps().getPosY()),
				ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(
				350,
				Application::get().getWindow().getProps().getHeight()),
				ImGuiCond_Always);

			if (ImGui::Begin("Settings", &showImGui, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {

			}
			ImGui::End();
		}

		lastSPACE = Application::get().getKeyPressed(GLFW_KEY_SPACE);
	}
};