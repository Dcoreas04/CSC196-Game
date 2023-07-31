#pragma once
#include <chrono>

namespace kiko
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() : 
			m_startTime{ clock::now() }
		{}

		void Tick();
		void Reset() { m_startTime = clock::now(); }

		clock_rep GetElapsedNanoseconds();
		clock_rep GetElapsedMicroseconds();
		clock_rep GetElapsedMilliseconds();
		float GetElapsedSeconds();

		float GetTime() const { return m_time; }
		float GetDeltaTime() const { return m_deltaTime; }
		float getUnscaledDeltaTime() const { return m_deltaTime; }

		float getTimeScale() const{ return m_timeScale; }
		float setTimeScale(float timeScale) { return m_timeScale = timeScale; }

	private:
		clock::time_point m_startTime;
		clock::time_point m_frameTime;

		float m_time = 0;
		float m_deltaTime = 0;
		float m_timeScale = 1;
	};

	extern Time g_time;
}