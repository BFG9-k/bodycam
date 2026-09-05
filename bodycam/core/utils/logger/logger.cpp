#include "logger.h"

void core::c_logger::alloc_console( const char* label )
{
  AllocConsole( );
  FILE* f{};
  freopen_s( &f, "CONOUT$", "w", stdout );
  SetConsoleTitleA( label );
}

void core::c_logger::print( const char* file, int line, WORD color, const char* fmt, ... )
{
  SYSTEMTIME time;
  GetLocalTime( &time );

  HANDLE console_handle = GetStdHandle( STD_OUTPUT_HANDLE );

  CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
  GetConsoleScreenBufferInfo( console_handle, &screen_buffer_info );

  WORD original_attributes = screen_buffer_info.wAttributes;

  printf( "[%02d:%02d:%02d] ", time.wHour, time.wMinute, time.wSecond );
  const char* file_name = strrchr( file, '\\' ) + 1;
  SetConsoleTextAttribute( console_handle, color );

  printf( "%s (line %d) >> ", file_name, line );
  SetConsoleTextAttribute( console_handle, original_attributes );

  va_list args;
  va_start( args, fmt );
  vprintf( fmt, args );
  va_end( args );

  printf( "\n" );
}