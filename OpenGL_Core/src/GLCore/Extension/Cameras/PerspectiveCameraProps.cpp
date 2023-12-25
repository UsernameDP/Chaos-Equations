#include "pch.hpp"
#include "PerspectiveCameraProps.hpp"

namespace GLCore::Extension::Cameras {
	PerspectiveCameraProps::PerspectiveCameraProps(const glm::vec3& cameraPos, const float& yaw, const float& pitch, const glm::vec3& cameraUp, const float& initFOV, const float& nearDist, const float& farDist)
	{
		this->cameraPos = cameraPos;
		this->yaw = yaw;
		this->pitch = pitch;
		this->cameraUp = cameraUp;
		this->initFOV = initFOV;
		this->nearDist = nearDist;
		this->farDist = farDist;

		this->FOV = this->initFOV;
	}

	PerspectiveCameraProps::PerspectiveCameraProps(const float& radius, const float& targetYaw, const float& targetPitch, const glm::vec3& cameraTarget, const glm::vec3& cameraUp, const float& initFOV, const float& nearDist, const float& farDist)
	{
		this->radius = radius;
		this->targetYaw = targetYaw;
		this->targetPitch = targetPitch;
		this->cameraTarget = cameraTarget;
		this->cameraUp = cameraUp;
		this->nearDist = nearDist;
		this->farDist = farDist;
		this->initFOV = initFOV;

		this->FOV = this->initFOV;
	}

}