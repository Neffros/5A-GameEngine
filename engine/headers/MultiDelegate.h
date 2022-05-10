#pragma once

#include <utility>
#include <vector>

namespace GameEngine {
    template<typename T>
    class MultiDelegate{};

    template<typename R, typename ...ARGS>
    class MultiDelegate<R (ARGS...)>{
        typedef R (*ProxyFunction) (void*, ARGS...);
        class DelegateObject{
        private:
            void* _instance;
            ProxyFunction _proxy;

        public:
            DelegateObject(void* instance, ProxyFunction proxy) : _instance(instance), _proxy(proxy) {}
            void Invoke(ARGS... args) const {
                _proxy(_instance, std::forward<ARGS>(args)...);
            }
            bool Equals(void* instanceCmp, ProxyFunction _proxyCmp){
                return _instance == instanceCmp && _proxy == _proxyCmp;
            }
        };

    private:
        std::vector<DelegateObject> _delegateObjects;

    public:
        MultiDelegate() : _delegateObjects(std::vector<DelegateObject>()) {}

        template<R (*function) (ARGS...)>
        void Bind();

        template<class C, R(C::*method) (ARGS...)>
        void Bind(C* instance);

        template<R (*function) (ARGS...)>
        void Unbind();

        template<class C, R(C::*method) (ARGS...)>
        void Unbind(C* instance);

        void Invoke(ARGS... args) const;
    };
}