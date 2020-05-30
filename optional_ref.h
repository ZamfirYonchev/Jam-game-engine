/*
 * optional_ref.h
 *
 *  Created on: Jan 18, 2020
 *      Author: zamfi
 */

#ifndef OPTIONAL_REF_H_
#define OPTIONAL_REF_H_

#include <utility>

#if __cplusplus >= 201703L
#include <optional>
template<typename T, typename Func>
auto operator+(std::optional<T> opt, Func f) -> std::optional<decltype(f(*opt))>
{
    if(opt)
        return std::optional(f(*opt));
    else
        return std::nullopt;
}

template<typename T, typename Func>
std::optional<T> operator-(std::optional<T> opt, Func f)
{
    if(!opt) f();

    return opt;
}
#endif

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

#if __cplusplus >= 201703L
    template<typename Func>
    auto operator+(Func f) -> std::optional<decltype(f(**this))>
    {
        if(m_valid)
        	return std::optional(f(m_value));
        else
          return std::nullopt;
    }
#else
    template<typename Func>
    optional_ref& operator+(Func f)
    {
        if(m_valid) f(m_value);

        return *this;
    }
#endif

    template<typename Func>
    optional_ref& operator-(Func f)
    {
        if(!m_valid) f();

        return *this;
    }

    operator bool() const
    {
        return m_valid;
    }

    private:
    bool m_valid;
    T&  m_value;

    static T nullValue;
};

template<typename T>
T optional_ref<T>::nullValue {};

#endif /* OPTIONAL_REF_H_ */
