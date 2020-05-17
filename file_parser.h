/*
 * file_parser.h
 *
 *  Created on: Nov 10, 2019
 *      Author: zamfi
 */

#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <string>
#include <fstream>
#include <iostream>
#include "optional_ref.h"

class FileParser
{
public:
    FileParser(std::string filename)
    {
        open(filename);
    }

    FileParser() : FileParser("") {}

    ~FileParser()
    {
    	close();
    }

    FileParser(const FileParser& ) = delete;
    FileParser(FileParser&& rhs)
    {
    	m_file = std::move(rhs.m_file);
    }

    FileParser& operator=(const FileParser& ) = delete;
    FileParser& operator=(FileParser&& rhs)
    {
    	close();
    	m_file = std::move(rhs.m_file);
    	return *this;
    }

    void open(const std::string& filename)
    {
        if(filename.length() > 0)
        {
        	if(m_file.is_open())
        		close();

            m_file.open(filename);
            if(m_file.is_open() == false)
            {
                std::cerr << "File " << filename << " cannot be opened!" << std::endl;
            }
        }
    }

    void close()
    {
    	m_file.close();
    }

    optional_ref<std::ifstream> read()
    {
    	if(m_file.is_open())
    		return optional_ref<std::ifstream>(m_file);
    	else
    		return optional_ref<std::ifstream>();
    }

private:
    std::ifstream m_file;
};

#endif /* FILE_PARSER_H_ */
