#include <Sea/Renderer/Window.hpp>

class MyWindow : public Sea::Window
{
private:
    
public:
    MyWindow(std::string title, int w, int h) : Sea::Window(title, w, h);
    ~MyWindow();
};

