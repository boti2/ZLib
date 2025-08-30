#pragma once

#include <functional>

template <typename... Params> class RunNow {
    public:
        RunNow(std::function<void(Params...)> f, Params... params){
            f(params...);
        }
};
