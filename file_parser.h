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

    std::ifstream& read()
    {
    	if(m_file.is_open())
    		return m_file;
    	else
    		throw std::ifstream::failure("File not opened");
    }

private:
    std::ifstream m_file;
};

#endif /* FILE_PARSER_H_ */
