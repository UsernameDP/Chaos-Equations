#pragma once
#include "SimulatorSharedObjects.hpp"
#include "Computer.hpp"
#include "Renderer.hpp"

class Simulator {
public:
	std::shared_ptr<SimulatorSharedObjects> simulatorSharedObjects = nullptr;
	std::unique_ptr<Computer> computer = nullptr;
	std::unique_ptr<Renderer> renderer = nullptr;

	Simulator(std::shared_ptr<Extension::Cameras::PerspectiveCamera> camera, std::shared_ptr<Settings> settings) {
		this->simulatorSharedObjects = std::make_unique<SimulatorSharedObjects>();
		computer = std::make_unique<Computer>(settings, simulatorSharedObjects);
		renderer = std::make_unique<Renderer>(camera, settings, simulatorSharedObjects);
	}

	~Simulator() = default;

};
