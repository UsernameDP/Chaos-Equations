#pragma once
#include "GUI.hpp"
#include <iostream>
#include <sstream>

class GUI {

public:
	std::shared_ptr<Settings> settings;
	std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera;

	bool currentESC = false;
	bool prevESC = false;

	std::stringstream consoleOutputs;

	GUI(std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera, std::shared_ptr<Settings> settings) {
		this->settings = settings;
		this->camera = camera;

		std::streambuf* oldStdout = std::cout.rdbuf();
		std::cout.rdbuf(consoleOutputs.rdbuf());
	}

private:
	void renderFPS(const TimeStep& ts, const WindowProps& props ) {
		ImGui::SetNextWindowPos(ImVec2(
			props.getPosX(),
			props.getPosY()),
			ImGuiCond_Always);

		//FPS 
		if (ImGui::Begin("FPS", &settings->simulationFlags->showImGui, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize)) {
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
			props.getHeight() * 0.66),
			ImGuiCond_Always);
		if (ImGui::Begin("Chaos Equations", &settings->simulationFlags->showImGui, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse)) {
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
			
			if (ImGui::CollapsingHeader("Particles")) {
				if (ImGui::InputInt("Number of Particles", &settings->simulationSettings->numberOfParticles, 10, 100, ImGuiInputTextFlags_EnterReturnsTrue)) {
					settings->simulationFlags->restart = true;
				}
				if (ImGui::InputFloat3("Center / Spawn Point", settings->simulationSettings->spawnPoint.data.data, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
					settings->simulationFlags->restart = true;
				}
				if (ImGui::InputFloat("Displacement from Center", &settings->simulationSettings->maxDisplacement, 0.01f, 0.1f, "%.8f", ImGuiInputTextFlags_EnterReturnsTrue)) {
					settings->simulationFlags->restart = true;
				}
			}
			if (ImGui::CollapsingHeader("Colors")) {
				ImGui::InputFloat("Highest Speed", &settings->simulationSettings->higestSpeed, 0.5f, 1.0f);
				ImGui::ColorPicker3("Lowest Speed Color", settings->simulationSettings->lowestSpeedColor.data.data);
				ImGui::ColorPicker3("Highest Speed Color", settings->simulationSettings->highestSpeedColor.data.data);
			}
			if (ImGui::CollapsingHeader("Next Generation Function")) {
				ImGui::InputTextMultiline("##Define Next Generation", settings->simulationSettings->nextGenFunctionDefinition, settings->simulationSettings->nextGenFunctionDefinition_Size, ImVec2(ImGui::GetColumnWidth(), ImGui::GetContentRegionAvail().y - 10), ImGuiInputTextFlags_AllowTabInput);
			}
		}
		ImGui::End();
	}
	void renderCameraInfo(const WindowProps& props) {
		Extension::Cameras::PerspectiveCameraProps& cameraProps = camera->getProps();

		ImGui::SetNextWindowPos(ImVec2(
			props.getPosX() + props.getWidth() * (1 - 0.25),
			props.getPosY() + props.getHeight() * 0.66),
			ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(
			props.getWidth() * 0.25,
			props.getHeight() * 0.33),
			ImGuiCond_Always);

		if (ImGui::Begin("Camera Settings", &settings->simulationFlags->showImGui, ImGuiWindowFlags_NoCollapse)) {
			if (ImGui::CollapsingHeader("Camera Target Properties")) {
				ImGui::InputFloat3("Camera Target", cameraProps.cameraTarget.data.data);
				ImGui::InputFloat("Camera Target X", &cameraProps.cameraTarget.x, 1, 5, "%.3f");
				ImGui::InputFloat("Camera Target Y", &cameraProps.cameraTarget.y, 1, 5, "%.3f");
				ImGui::InputFloat("Camera Target Z", &cameraProps.cameraTarget.z, 1, 5, "%.3f");
				ImGui::InputFloat("Radius", &cameraProps.radius, 10, 50, "%.3f");
				ImGui::InputFloat("Yaw (Degrees)", &cameraProps.targetYaw);
				ImGui::InputFloat("Pitch (Degrees)", &cameraProps.targetPitch);
				ImGui::InputFloat("Movement Speed", &cameraProps.cameraMovementSpeedFactor);
				ImGui::InputFloat("Rotation Speed", &cameraProps.cameraRotateSpeedFactor);
			}
			if (ImGui::CollapsingHeader("Projection Matrix Properties")) {
				ImGui::InputFloat("Near Distance", &cameraProps.nearDist);
				ImGui::InputFloat("Far Distance", &cameraProps.farDist);
			}
		}
		ImGui::End();
	}

	void renderOpenGLDebugInfo(const WindowProps& props) {


	}

public:
	void render(const TimeStep& ts) {
		WindowProps& props = Application::get().getWindow().getProps();
		currentESC = props.getKeyPressed(GLFW_KEY_ESCAPE);

		if (currentESC &&
			currentESC != prevESC &&
			!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
			settings->simulationFlags->showImGui = !settings->simulationFlags->showImGui;
		}

		if (settings->simulationFlags->showImGui) {
			renderFPS(ts, props);
			renderSimulationSettings(props);
			renderCameraInfo(props);
			renderOpenGLDebugInfo(props);
		}

		prevESC = currentESC;
	}

};