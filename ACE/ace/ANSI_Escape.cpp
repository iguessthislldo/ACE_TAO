#include "ace/ANSI_Escape.h"

#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_unistd.h"

bool
ace_file_supports_ansi_escape (FILE *file)
{
#ifdef ACE_HAS_ANSI_ESCAPE
  ACE_HANDLE file_handle = ACE_OS::fileno(file);
  if (file_handle == ACE_INVALID_HANDLE)
    {
      return false;
    }
  if (!ACE_OS::isatty(file_handle))
    {
      return false;
    }
  if (ACE_OS::getenv("NO_COLOR")) // https://no-color.org/
    {
      return false;
    }
  // TODO: https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#example-of-enabling-virtual-terminal-processing
  return true;
#else
  return false;
#endif
}

