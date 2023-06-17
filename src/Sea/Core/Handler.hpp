#pragma once


namespace Sea
{
    template<typename T>
    class Handler
    {
    public:
        virtual void Handle(T type) { }

    public:
        Handler() = default;
        virtual ~Handler() = default;
    };

}
