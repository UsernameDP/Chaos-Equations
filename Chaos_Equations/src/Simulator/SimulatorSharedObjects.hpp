#pragma once

struct Particle {
	glm::vec4 pos;
	glm::vec4 color;
	glm::vec4 history[249]; //Trail size is essentilly 100 since pos counts
};

struct SimulatorSharedObjects {

	std::shared_ptr<Extension::Primitives::SSBO> particles_SSBO = nullptr;
	std::shared_ptr<std::vector<Particle>> particles = nullptr;


	SimulatorSharedObjects() = default;
	~SimulatorSharedObjects() = default;
};