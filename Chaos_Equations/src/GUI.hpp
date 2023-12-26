#pragma once
#include "GUI.hpp"

class GUI {

public:
	std::shared_ptr<Settings> settings;
	std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera;

	bool showImGui = true;
	bool currentESC = false;
	bool prevESC = false;

	GUI(std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera, std::shared_ptr<Settings> settings) {
		this->settings = settings;
		this->camera = camera;
	}

private:
	void renderFPS(const TimeStep& ts, const WindowProps& props ) {
		ImGui::SetNextWindowPos(ImVec2(
			props.getPosX(),
			props.getPosY()),
			ImGuiCond_Always);

		//FPS 
		if (ImGui::Begin("FPS", &showImGui, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("FPS : %.2f", 1 / ts.getDeltaSeconds());
		}
		ImGui::End();
	}
	void renderSimulationSettings(const WindowProps& props) {
		ImGui::SetNextWindowPos(ImVec2(
			props.getPosX() + props.getWidth() * (1 - 0.25),
			props.getPosY()),
			ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(
			props.getWidth() * 0.25,
			props.getHeight()),
			ImGuiCond_Always);
		if (ImGui::Begin("Chaos Equations", &showImGui, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse)) {
			if (settings->simulationFlags->stop) {
				if (ImGui::Button("Continue")) {
					settings->simulationFlags->stop = false;
				}
			}
			else {
				if (ImGui::Button("Stop")) {
					settings->simulationFlags->stop = true;
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Apply")) {
				settings->simulationFlags->restart = true;
			}

			ImGui::SeparatorText("Simulation Settings : ");

			if (ImGui::InputInt("Number of Particles", &settings->simulationSettings->numberOfParticles, 10, 100, ImGuiInputTextFlags_EnterReturnsTrue)) {
				settings->simulationFlags->restart = true;
			}
			if (ImGui::InputFloat3("Center / Spawn Point", settings->simulationSettings->spawnPoint.data.data , "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
				settings->simulationFlags->restart = true;
			}
			if (ImGui::InputFloat("Displacement from Center", &settings->simulationSettings->maxDisplacement, 0.01f, 0.1f, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
				settings->simulationFlags->restart = true;
			}

			ImGui::Text("Define NextGen function for Chaos Equations");
			ImGui::Text("Available variables & Constants : ");
			ImGui::BulletText("dt - FLOAT time difference between each render in seconds");
			ImGui::InputTextMultiline("##Define Next Generation", settings->simulationSettings->nextGenFunctionDefinition, settings->simulationSettings->nextGenFunctionDefinition_Size, ImVec2(ImGui::GetColumnWidth(), ImGui::GetContentRegionAvail().y - 50), ImGuiInputTextFlags_AllowTabInput);
		}
		ImGui::End();
	}
	void renderCameraInfo(const WindowProps& props) {

	}

public:
	void render(const TimeStep& ts) {
		WindowProps& props = Application::get().getWindow().getProps();
		currentESC = props.getKeyPressed(GLFW_KEY_ESCAPE);

		if (currentESC &&
			currentESC != prevESC &&
			!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
			showImGui = !showImGui;
		}

		if (showImGui) {
			renderFPS(ts, props);
			renderSimulationSettings(props);
			renderCameraInfo(props);
		}

		prevESC = currentESC;
	}

};