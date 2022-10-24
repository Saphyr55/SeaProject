#include "Sea/Core/Game.hpp"

namespace Sea
{
    void Game::Run() 
    { 
        m_isRunning = true; 
        if (m_window != nullptr)
            m_window->Run();
    }

    void Game::Stop() 
    { 
        m_isRunning = false; 
        m_window->Close();
    }

    bool Game::IsRunning() 
    { 
        return m_isRunning; 
    }

    Window& Game::GetWindow()
    {
        return *m_window;
    }

    const Renderer& Game::GetRenderer()
    {
        return GetWindow().GetRenderer();
    }
}