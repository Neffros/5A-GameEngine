#pragma once

#include <utility>
#include <vector>

namespace GameEngine
{
    template<typename T>
    class MultiDelegate{};

    template<typename R, typename ...ARGS>
    class MultiDelegate<R (ARGS...)>
    {
    private:
        typedef R (*ProxyFunction) (void*, ARGS...);

        class DelegateObject
        {
        private:
            void* _instance;
            ProxyFunction _proxy;

        public:
            DelegateObject(void* instance, ProxyFunction proxy) : _instance(instance), _proxy(proxy) {}
            
            void invoke(ARGS... args) const
            {
                this->_proxy(_instance, std::forward<ARGS>(args)...);
            }

            bool equals(void* instanceCmp, ProxyFunction proxyCmp) const
            {
                return this->_instance == instanceCmp && this->_proxy == proxyCmp;
            }
        };
    private:
        template<R(*function)(ARGS...)>
        static inline R createFunctionProxy(void*, ARGS... args)
        {
            return function(std::forward<ARGS>(args)...);
        }

        template<class C, R(C::* method)(ARGS...)>
        static inline R createMethodProxy(void* instance, ARGS... args)
        {
            return (static_cast<C*>(instance)->*method)(std::forward<ARGS>(args)...);
        }

    private:
        std::vector<DelegateObject> _delegateObjects;

    public:
        MultiDelegate() { }

        template<R(*function)(ARGS...)>
        void bind()
        {
            this->_delegateObjects.push_back(DelegateObject(nullptr, &createFunctionProxy<function>));
        }

        template<class C, R(C::* method)(ARGS...)>
        void bind(C* instance)
        {
            this->_delegateObjects.push_back(DelegateObject(instance, &createMethodProxy<C, method>));
        }

        template<R(*function)(ARGS...)>
        void unbind()
        {
            ProxyFunction func = &createFunctionProxy<function>;
            for (int i = _delegateObjects.size() - 1; i >= 0; --i) {
                if (_delegateObjects[i].equals(nullptr, func)) {
                    _delegateObjects.erase(_delegateObjects.begin() + i);
                    return;
                }
            }
        }

        template<class C, R(C::* method)(ARGS...)>
        void unbind(C* instance)
        {
            ProxyFunction func = &createMethodProxy<method>;
            for (int i = _delegateObjects.size() - 1; i >= 0; --i) {
                if (_delegateObjects[i].equals(instance, func)) {
                    _delegateObjects.erase(_delegateObjects.begin() + i);
                    return;
                }
            }
        }

        void invoke(ARGS... args) const
        {
            for (const auto& del : this->_delegateObjects)
                del.invoke(std::forward<ARGS>(args)...);
        }
    };
}