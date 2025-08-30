#pragma once

#include <functional>
#include <tuple>
#include <ZLib/util.h>

namespace {
    std::stack<std::function<void()>> cleanupStack;

    void doCleanup(){
        while (cleanupStack.size()){
            cleanupStack.top()();
            cleanupStack.pop();
        }
    }

    RunNow<> cleanupRunner((void (*)())([](){atexit(doCleanup);}));
}

template<typename Func, typename... Params> void pushCleanup(Func func, std::tuple<Params...> &params){
    cleanupStack.push([func, params](){std::apply(func, params);});
}

template<typename Func, typename... Params> void pushCleanup(Func func, std::tuple<Params...> &&params){
    cleanupStack.push([func, params](){std::apply(func, params);});
}

template<typename Func> void pushCleanup(Func func){
    cleanupStack.push([func](){func();});
}
