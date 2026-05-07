#pragma once
#include <functional>
#include <vector>

template<typename... Args>
class Signal
{
private:
    std::vector<std::function<void(Args...)>> functions;
public:
    void connect(std::function<void(Args...)> slot)
    {
        functions.push_back(slot);
    }

    template<typename T, typename Ret>
    void connect(T* obj, Ret(T::* method)(Args...))
    {
        functions.push_back([obj, method](Args... args) {
            (obj->*method)(args...);
        });
    }

    template<typename T, typename Ret>
    void connect(const T* obj, Ret(T::* method)(Args...) const)
    {
        functions.push_back([obj, method](Args... args) {
            (obj->*method)(args...);
        });
    }

    void emit(Args... args)
    {
        for (auto& function : functions)
        {
            function(args...);
        }
    }
};