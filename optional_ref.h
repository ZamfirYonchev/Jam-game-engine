/*
 * optional_ref.h
 *
 *  Created on: Jan 18, 2020
 *      Author: zamfi
 */

#ifndef OPTIONAL_REF_H_
#define OPTIONAL_REF_H_

#include <utility>

template<typename T>
class optional_ref
{
    public:
    optional_ref() : m_valid(false), m_value(nullValue) {}
    optional_ref(T& ref) : m_valid(true), m_value(ref) {}
    optional_ref(T&& ref) : m_valid(true), m_value(ref) {}
    optional_ref(const optional_ref& rhs) : m_valid(rhs.m_valid), m_value(rhs.m_value) {}
    optional_ref(optional_ref&& rhs) : m_valid(std::move(rhs.m_valid)), m_value(rhs.m_value) {}
    ~optional_ref() = default;

    optional_ref& operator=(const optional_ref& rhs) = delete; //undefined for now so don't use
    /*    {
        if(m_valid && rhs.m_valid)
            m_value = rhs.m_value;

        return *this;
    }*/

    optional_ref& operator=(optional_ref&& rhs) = delete; //undefined for now so don't use
    /*{
    	if(m_valid && rhs.m_valid)
    		m_value = rhs.m_value;

    	return *this;
    }*/

    T& operator*() { return m_value; }
    const T& operator*() const { return m_value; }

    T* operator->() { return &m_value; }
    const T* operator->() const { return &m_value; }

    template<typename Func>
    auto operator&&(Func f) -> optional_ref<decltype(f(**this))>
    {
        if(m_valid)
          return optional_ref(f(m_value));
        else
          return optional_ref<decltype(f(**this))>();
    }

    template<typename Func>
    void operator||(Func f)
    {
        if(!m_valid) f();
    }

    operator bool() const
    {
        return m_valid;
    }

    //void operator&&(void (*f)(const T&))
    //{
    //    if(m_valid) f(m_value);
    //}

    private:
    bool m_valid;
    T&  m_value;

    static T nullValue;
};

template<typename T>
T optional_ref<T>::nullValue {};

#endif /* OPTIONAL_REF_H_ */
