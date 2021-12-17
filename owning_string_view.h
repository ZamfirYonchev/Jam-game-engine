/*
 * owning_string_view.h
 *
 *  Created on: Dec 17, 2021
 *      Author: zamfi
 */

#ifndef OWNING_STRING_VIEW_H_
#define OWNING_STRING_VIEW_H_

#include <string>

class owning_string_view : public std::string_view
{
public:
    owning_string_view() = default;
    owning_string_view(std::string_view sv) : std::string_view{std::move(sv)}, m_string_buffer{} {}
    explicit owning_string_view(const char* str) : std::string_view{str}, m_string_buffer{} {}
    explicit owning_string_view(const std::string& str) : std::string_view{str}, m_string_buffer{} {}
    explicit owning_string_view(std::string&& str) : std::string_view{}, m_string_buffer{std::move(str)}
    {
    	rebind_base_string_view();
    }

    owning_string_view(const owning_string_view& rhs)
    {
        *this = rhs;
    }

    owning_string_view(owning_string_view&& rhs) noexcept
    {
        *this = std::move(rhs);
    }

    owning_string_view& operator=(const owning_string_view& rhs)
    {
        if(rhs.is_owning())
        {
            m_string_buffer = rhs.m_string_buffer;
            rebind_base_string_view();
        }
        else
        {
            base_string_view() = rhs.base_string_view();
        }

        return *this;
    }

    owning_string_view& operator=(owning_string_view&& rhs) noexcept
    {
        if(rhs.is_owning())
        {
            m_string_buffer = std::move(rhs.m_string_buffer);
            rebind_base_string_view();
        }
        else
        {
            base_string_view() = std::move(rhs.base_string_view());
        }

        return *this;
    }

    ~owning_string_view() = default;

private:
    std::string m_string_buffer;

    //helpers
    constexpr std::string_view& base_string_view() { return static_cast<std::string_view&>(*this); }
    constexpr const std::string_view& base_string_view() const { return static_cast<const std::string_view&>(*this); }
    bool is_owning() const { return base_string_view().data() == m_string_buffer.c_str(); }
    void rebind_base_string_view() { base_string_view() = m_string_buffer; }
};

#endif /* OWNING_STRING_VIEW_H_ */
