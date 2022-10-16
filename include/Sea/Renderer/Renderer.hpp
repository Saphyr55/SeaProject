#pragma once

namespace Sea
{
    class Renderer
    {
    public:
        virtual void ClearColor()=0;

    public:
        Renderer()=default;
        ~Renderer()=default;
    };
    
} 
