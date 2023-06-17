#pragma once

#include <functional>

namespace Sea
{

    template<typename E, typename T = void>
    class Result
    {
    public:
        enum class Type 
        {
           SUCCESS, 
           FAILURE
        };

    public:
        Result<E, T>& OnFailure(std::function<void(E)> on);
		Result<E, T>& OnSuccess(std::function<void(T)> on);
		void Success(T* type);
	    void Failure(E error);

    public:
        Result() = default;
        ~Result() = default;

    private:
        T* m_value = nullptr;
        E m_error;
        Type m_type_inner;
    };

	template<typename E, typename T>
    Result<E, T>& Result<E, T>::OnSuccess(std::function<void(T)> on)
    {   
        if (m_type_inner == Type::SUCCESS)
        {
            on();
        }
		return *this;
    }

    template<typename E, typename T>    
    Result<E, T>& Result<E, T>::OnFailure(std::function<void(E)> on)
    {
		if (m_type_inner == Type::FAILURE) on(m_error);
        return *this;
    }

    template<typename E, typename T>
    void Result<E, T>::Success(T* type)
    {
		m_type_inner = Type::SUCCESS;
        m_value = type;
    }

	template<typename E, typename T>
    void Result<E, T>::Failure(E error)
    {
		m_type_inner = Type::FAILURE;
		m_error = error;
    }

}
