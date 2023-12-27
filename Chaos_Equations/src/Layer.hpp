#pragma once
#include "GLCore/Core/Core.hpp"
#include "GLCore/Extension/Extension.hpp"
using namespace GLCore;

#include "Settings.hpp"
#include "GUI.hpp"
#include "Simulator/Simulator.hpp"

class ChaosEquationsLayer : public Layer
{
private:
	std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera = nullptr;
	std::shared_ptr<Settings> settings = nullptr;
	std::unique_ptr<GUI> gui = nullptr;
	std::unique_ptr<Simulator> simulator = nullptr;

private:
	//GLCore::Layer Methods
public:
	ChaosEquationsLayer() : Layer("ChaosEquations")
	{

	}
	virtual ~ChaosEquationsLayer()
	{
		
	}

	virtual void onAttach() override
	{
		settings = std::make_shared<Settings>();

		Extension::Cameras::PerspectiveCameraProps cameraProps(
			3.0f,
			90.0f,
			0.0f,
			settings->simulationSettings->spawnPoint,
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f,
			0.1f,
			1000.0f
		);
		cameraProps.enableRotateAboutTargetWithKeys();
		cameraProps.enableFOVWithScroll();
		cameraProps.enableMoveRadiusWithKeys();
		cameraProps.setCameraMovementSpeedFactor(10.0);
		camera = std::make_shared<Extension::Cameras::PerspectiveCamera>(cameraProps);

		gui = std::make_unique<GUI>(camera, settings);
		simulator = std::make_unique<Simulator>(camera, settings);
		simulator->computer->initGen();
		simulator->renderer->init();
	}
	virtual void onDetach() override
	{

	}
	virtual void onUpdate(const GLCore::TimeStep &ts) override
	{
		if (settings->simulationFlags->restart) {
			simulator->computer->initGen();
			simulator->renderer->restart();
			
			settings->simulationFlags->restart = false;
		}

		camera->onUpdate(ts, Extension::Cameras::PerspectiveCameraOptions::ROTATE_USING_CAMERA_TARGET);

		simulator->renderer->render(ts);
		if (!settings->simulationFlags->stop) {
			simulator->computer->nextGen(ts);
		}

	}
	virtual void onImguiUpdate(const GLCore::TimeStep &ts) override
	{
		gui->render(ts);
	}
};