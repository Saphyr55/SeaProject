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
		void SetOnQuit(std::function<void()> onQuit);
		std::function<void()>& GetOnQuit();

	public:
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		~Application();

	private:
		void Init();

	private:
		std::function<void()> m_on_quit;
		bool m_is_running;
		std::vector<Ref<Handler<Application&>>> m_handlers;

	};
}