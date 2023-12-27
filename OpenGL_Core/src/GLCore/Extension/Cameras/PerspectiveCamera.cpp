#include "pch.hpp"
#include "PerspectiveCamera.hpp"
#include "GLCore/Core/Application.hpp"

namespace GLCore::Extension::Cameras {
	PerspectiveCamera::PerspectiveCamera(const PerspectiveCameraProps& props)
	{
		this->props = props;
	}

	void PerspectiveCamera::move(const glm::vec3& pos)
	{
		props.cameraPos = pos;
	}

	void PerspectiveCamera::moveDelta(const glm::vec3& deltaPos)
	{
		props.cameraPos += deltaPos;
	}

	void PerspectiveCamera::moveDeltaX(const float& deltaPosX)
	{
		props.cameraPos.x += deltaPosX;
	}

	void PerspectiveCamera::moveDeltaY(const float& deltaPosY)
	{
		props.cameraPos.y += deltaPosY;
	}

	void PerspectiveCamera::moveDeltaZ(const float& deltaPosZ)
	{
		props.cameraPos.z += deltaPosZ;
	}

	void PerspectiveCamera::rotateYaw(const float& angle)
	{
		props.yaw = angle;
		props.yaw = fmod(props.yaw, 360.0f);
	}

	void PerspectiveCamera::rotateDeltaYaw(const float& deltaAngle)
	{
		props.yaw += deltaAngle;
		props.yaw = fmod(props.yaw, 360.0f);
	}

	void PerspectiveCamera::rotatePitch(const float& angle)
	{
		props.pitch = angle;
		props.pitch = glm::clamp(props.pitch, -89.9f, 89.9f);
	}

	void PerspectiveCamera::rotateDeltaPitch(const float& deltaAngle)
	{
		props.pitch += deltaAngle;
		props.pitch = glm::clamp(props.pitch, -89.9f, 89.9f);
	}

	void PerspectiveCamera::rotateDeltaTargetYaw(const float& deltaAngle)
	{
		props.targetYaw += deltaAngle;
		props.targetYaw = fmod(props.targetYaw, 360.0f);
	}

	void PerspectiveCamera::rotateDeltaTargetPitch(const float& deltaAngle)
	{
		props.targetPitch += deltaAngle;
		props.targetPitch = glm::clamp(props.targetPitch, -89.9f, 89.9f);
	}

	void PerspectiveCamera::moveDeltaRadius(const float& deltaRadius) {
		props.radius += deltaRadius;
		if (props.radius < 0)
			props.radius = 0;
	}

	void PerspectiveCamera::zoomDeltaFov(const float& changeSinceInitialFOV)
	{
		props.FOV = props.initFOV + changeSinceInitialFOV;
		props.FOV = glm::clamp(props.FOV, 0.1f, 89.9f);
	}

	void PerspectiveCamera::onUpdate(const TimeStep& ts, const PerspectiveCameraOptions& rotate_option)
	{
		WindowProps& windowProps = Application::get().getWindow().getProps();

		if (props.FOVWithScroll ) {
			if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				float scrollY = windowProps.getScrollY();
				zoomDeltaFov(-scrollY);
			}
		}

		if (rotate_option == ROTATE_USING_PITCH_YAW) {
			if (props.rotateWithRightClick) {
				if (windowProps.getRightMouseDown()) {
					rotateDeltaYaw(windowProps.getMousePosDeltaX() * props.mouseSensitivity);
					rotateDeltaPitch(-windowProps.getMousePosDeltaY() * props.mouseSensitivity);
				}

			}

			if (props.rotateWithKeys) {
				float rotateSpeed = props.cameraRotateSpeedFactor * ts.getDeltaSeconds();
				if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
					if (windowProps.getKeyPressed(props.ROTATE_UP_KEY)) {
						rotateDeltaPitch(rotateSpeed);
					}
					if (windowProps.getKeyPressed(props.ROTATE_DOWN_KEY)) {
						rotateDeltaPitch(-rotateSpeed);
					}
					if (windowProps.getKeyPressed(props.ROTATE_LEFT_KEY)) {
						rotateDeltaYaw(-rotateSpeed);
					}
					if (windowProps.getKeyPressed(props.ROTATE_RIGHT_KEY)) {
						rotateDeltaYaw(rotateSpeed);
					}
				}
			}

			glm::vec3 direction;
			direction.x = cos(glm::radians(props.yaw)) * cos(glm::radians(props.pitch));
			direction.y = sin(glm::radians(props.pitch));
			direction.z = sin(glm::radians(props.yaw)) * cos(glm::radians(props.pitch));
			props.cameraFront = glm::normalize(direction);
			

			if (props.movementWithKeys) {
				float cameraSpeed = props.cameraMovementSpeedFactor * ts.getDeltaSeconds();
				if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
					if (windowProps.getKeyPressed(props.MOVE_FORWARD_KEY)) {
						moveDelta(props.cameraFront * cameraSpeed);
					}
					if (windowProps.getKeyPressed(props.MOVE_BACKWARD_KEY)) {
						moveDelta(-props.cameraFront * cameraSpeed);
					}
					if (windowProps.getKeyPressed(props.MOVE_LEFT_KEY)) {
						moveDelta(-glm::normalize(glm::cross(props.cameraFront, props.cameraUp)) * cameraSpeed);
					}
					if (windowProps.getKeyPressed(props.MOVE_RIGHT_KEY)) {
						moveDelta(glm::normalize(glm::cross(props.cameraFront, props.cameraUp)) * cameraSpeed);
					}
				}
			}

			props.view = glm::lookAt(props.cameraPos, props.cameraPos + props.cameraFront, props.cameraUp);
		}
		else {
			if (props.rotateAboutTargetWithKeys) {
				float cameraSpeed = props.cameraRotateSpeedFactor * ts.getDeltaSeconds();
				if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
					if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_UP_KEY)) {
						rotateDeltaTargetPitch(cameraSpeed);
					}
					if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_DOWN_KEY)) {
						rotateDeltaTargetPitch(-cameraSpeed);
					}
					if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_LEFT_KEY)) {
						rotateDeltaTargetYaw(cameraSpeed);
					}
					if (windowProps.getKeyPressed(props.ROTATE_ABOUT_CAMERA_TARGET_RIGHT_KEY)) {
						rotateDeltaTargetYaw(-cameraSpeed);
					}
				}
			}

			if (props.moveRadiusWithKeys) {
				float changeRadiusSpeed = props.cameraMovementSpeedFactor * ts.getDeltaSeconds();
				if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
					if (windowProps.getKeyPressed(props.MOVE_RADIUS_INCREASE_KEY)) {
						moveDeltaRadius(changeRadiusSpeed);
					}
					if (windowProps.getKeyPressed(props.MOVE_RADIUS_DECREASE_KEY)) {
						moveDeltaRadius(-changeRadiusSpeed);
					}
				}
			}

			glm::vec3 deltaDistFromTarget;
			deltaDistFromTarget.x = props.radius * cos(glm::radians(props.targetYaw)) * cos(glm::radians(props.targetPitch));
			deltaDistFromTarget.y = props.radius * sin(glm::radians(props.targetPitch));
			deltaDistFromTarget.z = props.radius * sin(glm::radians(props.targetYaw)) * cos(glm::radians(props.targetPitch));
			props.cameraPos = deltaDistFromTarget + props.cameraTarget;

			props.view = glm::lookAt(props.cameraPos, props.cameraTarget, props.cameraUp);
		}
		props.projection = glm::perspective(glm::radians(props.FOV), (float)windowProps.getWidth() / (float)windowProps.getHeight(), props.nearDist, props.farDist);

		props.VP = props.projection * props.view;
	}

}