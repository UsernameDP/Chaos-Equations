#pragma once

namespace GLCore {
	class TimeStep {
	private:
		float m_DeltaTime = 0;
		float m_LastTime = 0;
		float m_Time = 0;
	public:
		TimeStep() = default;
		inline TimeStep(float time) :m_Time(time) {}

		inline operator float() const { return m_Time; }

		inline void setTime(float time) {
			this->m_LastTime = this->m_Time;
			this->m_Time = time;
			this->m_DeltaTime = m_Time - m_LastTime;
		}
		inline float getSeconds() const { return m_Time; }
		inline float getMilliseconds() const { return m_Time * 1000.0f; }

		inline float getDeltaSeconds() const { return m_DeltaTime; }
		inline float getDeltaMilliseconds() const { return m_DeltaTime * 1000.0f; }
	};
}