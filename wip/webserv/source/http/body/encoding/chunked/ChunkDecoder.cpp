/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkDecoder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:51:33 by alicetetu         #+#    #+#             */
/*   Updated: 2021/01/22 11:36:10 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <exception/Exception.hpp>
#include <http/body/encoding/chunked/ChunkDecoder.hpp>
#include <cstdlib>
#include <iostream>
#include <config/Configuration.hpp>

ChunkDecoder::ChunkDecoder(bool isAllocated) :
		m_isAllocated(isAllocated),
		m_state(S_NOT_STARTED),
		m_sizeNb(0),
		m_sizeStr(""),
		m_parsedChunk(""),
		m_totalSize(0)
{
}

ChunkDecoder::~ChunkDecoder()
{
}

#define SIZE_CONVERSION()											\
		char *endPtr;												\
		std::string hex_intro = "0x" + m_sizeStr;					\
		m_sizeNb = strtol(hex_intro.c_str(), &endPtr, 16);			\
		if (endPtr == hex_intro.c_str())							\
			throw Exception ("Hexadecimal conversion impossible"); 	\
		m_sizeStr = "";

bool
ChunkDecoder::consume(const std::string &in, std::string &out, size_t &consumed, bool max)
{
	std::string copy = in;
	
	if (in.empty())
		return (false);
	while (1)
	{
		switch (m_state)
		{
			case S_NOT_STARTED:
			case S_SIZE:
			{
				size_t found;
				found = copy.find("\r\n");
				
				if (found != std::string::npos)
				{
					if (found != 0)
						m_sizeStr = copy.substr(0, found);
					else
						m_sizeStr = copy.substr(0, 1);
					
					consumed += found + 2;
			
					if (m_sizeStr.empty())
					{
						m_state = S_SIZE;
						return (false);
					}
					
					SIZE_CONVERSION();
				
					m_sizeStr = "";
					copy.erase(0, found + 2);
				}
				else
				{
					return (false);
				}

				if (m_sizeNb == 0)
				{
					m_state = S_OVER;
					return (true);
				
				}
				else
				{
					m_state = S_CHUNK;	
				}
				break;
			}

			case S_CHUNK:
			{
				if (copy.size() <= (size_t)m_sizeNb)
				{
			
					out += copy;
					m_sizeNb -= copy.size();
					consumed += copy.size();
					copy.erase(0, std::string::npos);
				}
				else
				{
					m_parsedChunk = copy.substr(0, m_sizeNb);
					if (!max)
						out += m_parsedChunk;
					consumed += m_sizeNb;
					m_parsedChunk = "";
					
					copy.erase(0, m_sizeNb);
					m_sizeNb = 0;
				}
				
				if (m_sizeNb == 0)
				{
					m_state = S_CHUNK_END;
				}
				if (copy.empty())
					return (false);
				break;
			}

			case S_CHUNK_END:
			{
				size_t f;
				
				f = copy.find("\r\n");
				if (f != std::string::npos)
				{
					consumed += f + 2;
					copy.erase(0, f + 2);
					m_state = S_SIZE;
				}
				else if ((f = copy.find("\r")) != std::string::npos)
				{
					consumed += f + 1;
					copy.erase(0, f + 1);
					m_state = S_CHUNK_END2;
				}
				else
				{
					return (false);
				}
				if (copy.empty())
					return (false);

				break;
			}
			case S_CHUNK_END2:
			{
			
				size_t f;
			
				f = copy.find("\n");
				if (f != std::string::npos)
				{
					consumed += f + 1;
					copy.erase(0, f + 1);
					m_state = S_SIZE;
				}
				else if (copy.size() != 0)
				{
					m_state = S_CHUNK_END;
				}
				
				if (copy.empty())
					return (false);
					
				break;
			}	

			case S_OVER:
			{
				return (true);
			}
		}
	}

	
	
	

	return (false);
}

ChunkDecoder::State
ChunkDecoder::state()
{
	return (m_state);
}

void
ChunkDecoder::cleanup()
{
	if (m_isAllocated)
		delete this;
}
