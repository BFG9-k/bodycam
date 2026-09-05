#pragma once
#include "../../../includes.h"

namespace core
{
	class c_logger
	{
	public:
		void alloc_console( const char* label );
		void print( const char* file, int line, WORD color, const char* fmt, ... );
	};
	inline const std::unique_ptr < c_logger > logger = std::make_unique< c_logger >( );
}

#define L_SUCCESS(fmt, ...) core::logger->print(__FILE__, __LINE__, FOREGROUND_INTENSITY | FOREGROUND_GREEN, fmt, __VA_ARGS__)
#define L_ERROR(fmt, ...) core::logger->print(__FILE__, __LINE__, FOREGROUND_INTENSITY | FOREGROUND_RED, fmt, __VA_ARGS__)
#define L_WARNING(fmt, ...) core::logger->print(__FILE__, __LINE__, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN, fmt, __VA_ARGS__)
#define L_INFO(fmt, ...) core::logger->print(__FILE__, __LINE__, FOREGROUND_INTENSITY | FOREGROUND_BLUE, fmt, __VA_ARGS__)