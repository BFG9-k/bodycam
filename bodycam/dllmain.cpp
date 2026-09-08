#include "includes.h"

bool __stdcall DllMain( HMODULE module, DWORD call_reason, void* reserved )
{
  switch ( call_reason )
  {
    case DLL_PROCESS_ATTACH:
    {
      std::thread( [ ] { core::c_cheat_bootstrap::run( ); } ).detach( );
      break;
    }
    case DLL_PROCESS_DETACH:
    break;
  }
  return true;
}