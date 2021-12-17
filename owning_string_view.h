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
	explicit owning_string_view(const char* str) : std::string_view{str}, m_string_buffer{} {}
	explicit owning_string_view(const std::string& str) : std::string_view{str}, m_string_buffer{} {}
	explicit owning_string_view(std::string&& str) : std::string_view{}, m_string_buffer{std::move(str)}
	{
		static_cast<std::string_view&>(*this) = m_string_buffer;
	}

private:
    std::string m_string_buffer;
};

#endif /* OWNING_STRING_VIEW_H_ */
