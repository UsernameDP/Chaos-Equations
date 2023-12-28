#pragma once

struct Particle {
	glm::vec4 pos;
	glm::vec4 color;
	glm::vec4 history[249]; //Trail size is essentilly 100 since pos counts
};
struct History {
	glm::vec4 pos;
};

struct SimulatorSharedObjects {

	std::shared_ptr<Primitives::SSBO> particles_SSBO = nullptr;
	std::shared_ptr<Primitives::SSBO> particlesHistory_SSBO = nullptr; //history_SSBO will be "trailSize" times larger than particles_SSBO	

	unsigned int setNumberOfParticles = 0;
	unsigned int setTrailSize = 0;

	SimulatorSharedObjects() = default;
	~SimulatorSharedObjects() = default;
};