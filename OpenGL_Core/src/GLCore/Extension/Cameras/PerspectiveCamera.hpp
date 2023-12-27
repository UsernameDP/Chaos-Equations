#pragma once
#include "PerspectiveCameraProps.hpp"

namespace GLCore::Extension::Cameras {

	class PerspectiveCamera {
	private:
		PerspectiveCameraProps props;
	public:
		PerspectiveCamera( const PerspectiveCameraProps& props);

		void move(const glm::vec3& pos);
		void moveDelta(const glm::vec3& deltaPos);
		void moveDeltaX(const float& deltaPosX);
		void moveDeltaY(const float& deltaPosY);
		void moveDeltaZ(const float& deltaPosZ);
		
		void rotateYaw(const float& angle);
		void rotateDeltaYaw(const float& deltaAngle);
		void rotatePitch(const float& angle);
		void rotateDeltaPitch(const float& deltaAngle);

		void rotateDeltaTargetYaw(const float& deltaAngle);
		void rotateDeltaTargetPitch(const float& deltaAngle);
		void moveDeltaRadius(const float& deltaRadius);

		void zoomDeltaFov(const float& changeSinceInitialFOV);

		void onUpdate(const TimeStep& ts, const PerspectiveCameraOptions& rotate_option);

		inline PerspectiveCameraProps& getProps() { return props;  }
		inline glm::mat4& getViewProjection() { return props.VP; }
	};

}