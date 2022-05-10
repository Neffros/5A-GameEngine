#include "MultiDelegate.h"

namespace GameEngine {
    template<typename R, typename ...ARGS, R (*function)(ARGS...)>
    static inline R FunctionProxy(void *, ARGS... args) {
        return function(std::forward<ARGS>(args)...);
    }

    template<typename R, typename ...ARGS, class C, R(C::*method)(ARGS...)>
    static inline R MethodProxy(void *instance, ARGS... args) {
        return (static_cast<C *>(instance)->*method)(std::forward<ARGS>(args)...);
    }

    template<typename R, typename... ARGS>
    template<R (*function)(ARGS...)>
    void MultiDelegate<R(ARGS...)>::Bind() {
        _delegateObjects.emplace(DelegateObject(nullptr, &FunctionProxy<function>));
    }

    template<typename R, typename ...ARGS>
    template<class C, R(C::*method)(ARGS...)>
    void MultiDelegate<R(ARGS...)>::Bind(C *instance) {
        _delegateObjects.template emplace(DelegateObject(instance, &MethodProxy<C, method>));
    }

    template<typename R, typename... ARGS>
    template<R (*function)(ARGS...)>
    void MultiDelegate<R(ARGS...)>::Unbind() {
        ProxyFunction func = &FunctionProxy<function>;
        for(int i = _delegateObjects.size(); i >= 0; --i){
            if(_delegateObjects[i].Equals(nullptr, func)){
                _delegateObjects.erase(_delegateObjects.begin() + i);
                return;
            }
        }
    }

    template<typename R, typename... ARGS>
    template<class C, R (C::*method)(ARGS...)>
    void MultiDelegate<R(ARGS...)>::Unbind(C *instance) {
        ProxyFunction func = &MethodProxy<method>;
        for(int i = _delegateObjects.size(); i >= 0; --i){
            if(_delegateObjects[i].Equals(instance, func)){
                _delegateObjects.erase(_delegateObjects.begin() + i);
                return;
            }
        }
    }

    template<typename R, typename... ARGS>
    void MultiDelegate<R(ARGS...)>::Invoke(ARGS... args) const {
        for(int i = _delegateObjects.size(); i >= 0; --i) {
            _delegateObjects[i].Invoke(std::forward<ARGS>(args)...);
        }
    }
}