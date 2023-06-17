#pragma once

#include <string>
#include <stdexcept>
#include <functional>

#include "Sea/Core/Common.hpp"
#include "Sea/Core/Handler.hpp"

namespace Sea
{	

	class Application final
	{
	public: 

	public:
		inline bool IsRunning() const { return m_is_running; }
		void Stop();
		void Launch();
		void Attach(Ref<Handler<Application&>> handler);

	public:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		~Application();

	private:
		void Init();

	private:
		bool m_is_running;
		std::vector<Ref<Handler<Application&>>> m_handlers;

	};
}