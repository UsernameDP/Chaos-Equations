#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLCore/Core/TimeStep.hpp"
#include <GLFW/glfw3.h>

namespace GLCore::Extension::Cameras {
	enum PerspectiveCameraOptions {
		ROTATE_USING_PITCH_YAW,
		ROTATE_USING_CAMERA_TARGET
	};

	struct PerspectiveCameraProps {
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraTarget;
		glm::vec3 cameraUp;

		//ROTATE_USING PITCH YAW
		float pitch = 0.0f; //pitch of 0 and yaw of 0 points to positive x axis direction
		float yaw = 0.0f; //

		//ROTATE_USING_CAMERA_TARGET
		float radius; //distance from the cameraTarget
		float targetYaw; //horizontal angle relative to cameraTarget
		float targetPitch; //vertical angle relative to cameraTarget

		float initFOV = 45.0f;
		float FOV = initFOV;
		float nearDist;
		float farDist;

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		glm::mat4 VP; // view * projection


		float mouseSensitivity = 0.2f;
		float scrollSensitivity = 1.0f;
		float cameraMovementSpeedFactor = 2.5f;
		float cameraRotateSpeedFactor = 50.0f;

		bool movementWithKeys = false;
		bool rotateAboutTargetWithKeys = false;
		bool FOVWithScroll = false;
		bool rotateWithRightClick = false;
		bool rotateWithKeys = false;

		uint16_t MOVE_FORWARD_KEY = GLFW_KEY_W;
		uint16_t MOVE_BACKWARD_KEY = GLFW_KEY_S;
		uint16_t MOVE_LEFT_KEY = GLFW_KEY_A;
		uint16_t MOVE_RIGHT_KEY = GLFW_KEY_D;

		uint16_t ROTATE_UP_KEY = GLFW_KEY_UP;
		uint16_t ROTATE_DOWN_KEY = GLFW_KEY_DOWN;
		uint16_t ROTATE_LEFT_KEY = GLFW_KEY_LEFT;
		uint16_t ROTATE_RIGHT_KEY = GLFW_KEY_RIGHT;


		uint16_t ROTATE_ABOUT_CAMERA_TARGET_UP_KEY = GLFW_KEY_W;
		uint16_t ROTATE_ABOUT_CAMERA_TARGET_DOWN_KEY = GLFW_KEY_S;
		uint16_t ROTATE_ABOUT_CAMERA_TARGET_LEFT_KEY = GLFW_KEY_A;
		uint16_t ROTATE_ABOUT_CAMERA_TARGET_RIGHT_KEY = GLFW_KEY_D;

		PerspectiveCameraProps() = default;
		PerspectiveCameraProps(const glm::vec3& cameraPos, const float& yaw, const float& pitch, const glm::vec3& cameraUp, const float& initFOV, const float& nearDist, const float& farDist);
		PerspectiveCameraProps(const float& radius, const float& targetYaw, const float& targetPitch, const glm::vec3& cameraTarget, const glm::vec3& cameraUp, const float& initFOV, const float& nearDist, const float& farDist);

		inline void setMouseSensitivity(const float& mouseSensitivity) { this->mouseSensitivity = mouseSensitivity; }
		inline void setScrollSensitivity(const float& scrollSensitivity) { this->scrollSensitivity = scrollSensitivity; }
		inline void setCameraMovementSpeedFactor(const float& cameraMovementSpeedFactor) { this->cameraMovementSpeedFactor = cameraMovementSpeedFactor; }
		inline void setCameraRotateSpeedFactor(const float& cameraRotateSpeedFactor) { this->cameraRotateSpeedFactor = cameraRotateSpeedFactor; }

		inline void enableMovementWithKeys() { this->movementWithKeys = true; }
		inline void enableRotateAboutTargetWithKeys() { this->rotateAboutTargetWithKeys = true; }
		inline void enableRotateWithRightClick() { this->rotateWithRightClick = true; }
		inline void enableFOVWithScroll() { this->FOVWithScroll = true; }
		inline void enableRotateWithKeys() { this->rotateWithKeys = true; }

		inline void setRotateAboutCameraTargetKeys(uint16_t ROTATE_ABOUT_CAMERA_TARGET_UP_KEY, uint16_t ROTATE_ABOUT_CAMERA_TARGET_DOWN_KEY, uint16_t ROTATE_ABOUT_CAMERA_TARGET_LEFT_KEY, uint16_t ROTATE_ABOUT_CAMERA_TARGET_RIGHT_KEY) {
			this->ROTATE_ABOUT_CAMERA_TARGET_UP_KEY = ROTATE_ABOUT_CAMERA_TARGET_UP_KEY;
			this->ROTATE_ABOUT_CAMERA_TARGET_DOWN_KEY = ROTATE_ABOUT_CAMERA_TARGET_DOWN_KEY;
			this->ROTATE_ABOUT_CAMERA_TARGET_LEFT_KEY = ROTATE_ABOUT_CAMERA_TARGET_LEFT_KEY;
			this->ROTATE_ABOUT_CAMERA_TARGET_RIGHT_KEY = ROTATE_ABOUT_CAMERA_TARGET_RIGHT_KEY;
		}
		inline void setMovementKeys(uint16_t MOVE_FORWARD_KEY, uint16_t MOVE_BACKWARD_KEY, uint16_t MOVE_LEFT_KEY, uint16_t MOVE_RIGHT_KEY) {
			this->MOVE_FORWARD_KEY = MOVE_FORWARD_KEY;
			this->MOVE_BACKWARD_KEY = MOVE_BACKWARD_KEY;
			this->MOVE_LEFT_KEY = MOVE_LEFT_KEY;
			this->MOVE_RIGHT_KEY = MOVE_RIGHT_KEY;
		}
		inline void setRotationKeys(uint16_t ROTATE_UP_KEY, uint16_t ROTATE_DOWN_KEY, uint16_t ROTATE_LEFT_KEY, uint16_t ROTATE_RIGHT_KEY) {
			this->ROTATE_UP_KEY = ROTATE_UP_KEY;
			this->ROTATE_DOWN_KEY = ROTATE_DOWN_KEY;
			this->ROTATE_LEFT_KEY = ROTATE_LEFT_KEY;
			this->ROTATE_RIGHT_KEY = ROTATE_RIGHT_KEY;
		}

		/*ROTATE_USING_CAMERA_TARGET*/
		inline void setRadius(const float& radius) { this->radius = radius; }
		inline void setCameraTarget(const glm::vec3& cameraTarget) { this->cameraTarget = cameraTarget; }
	};
}