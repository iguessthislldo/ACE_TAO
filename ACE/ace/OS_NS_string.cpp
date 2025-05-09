#include "ace/ACE.h"
#include "ace/Global_Macros.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_stdlib.h"

#if !defined (ACE_HAS_INLINED_OSCALLS)
# include "ace/OS_NS_string.inl"
#endif /* ACE_HAS_INLINED_OSCALLS */

#if defined (ACE_HAS_ALLOC_HOOKS)
# include "ace/Malloc_Base.h"
#endif /* ACE_HAS_ALLOC_HOOKS */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

#if (defined (ACE_LACKS_STRDUP) && !defined (ACE_STRDUP_EQUIVALENT)) \
  || defined (ACE_HAS_STRDUP_EMULATION)
char *
ACE_OS::strdup_emulation (const char *s)
{
#if defined (ACE_HAS_ALLOC_HOOKS)
  char *t = (char *) ACE_Allocator::instance()->malloc (ACE_OS::strlen (s) + 1);
#else
  char *t = (char *) ACE_OS::malloc (ACE_OS::strlen (s) + 1);
#endif /* ACE_HAS_ALLOC_HOOKS */

  if (t == 0)
    return 0;

  return ACE_OS::strcpy (t, s);
}
#endif /* (ACE_LACKS_STRDUP && !ACE_STRDUP_EQUIVALENT) || ... */

#if defined (ACE_HAS_WCHAR)
#if (defined (ACE_LACKS_WCSDUP) && !defined (ACE_WCSDUP_EQUIVALENT)) \
  || defined (ACE_HAS_WCSDUP_EMULATION)
wchar_t *
ACE_OS::strdup_emulation (const wchar_t *s)
{
  wchar_t *buffer =
    (wchar_t *) ACE_OS::malloc ((ACE_OS::strlen (s) + 1)
                                * sizeof (wchar_t));
  if (buffer == 0)
    return 0;

  return ACE_OS::strcpy (buffer, s);
}
#endif /* (ACE_LACKS_WCSDUP && !ACE_WCSDUP_EQUIVALENT) || ... */
#endif /* ACE_HAS_WCHAR */

char *
ACE_OS::strecpy (char *s, const char *t)
{
  char *dscan = s;
  const char *sscan = t;

  while ((*dscan++ = *sscan++) != '\0')
    continue;

  return dscan;
}

#if defined (ACE_HAS_WCHAR)
wchar_t *
ACE_OS::strecpy (wchar_t *s, const wchar_t *t)
{
  wchar_t *dscan = s;
  const wchar_t *sscan = t;

  while ((*dscan++ = *sscan++) != ACE_TEXT_WIDE ('\0'))
    continue;

  return dscan;
}
#endif /* ACE_HAS_WCHAR */

char *
ACE_OS::strerror (int errnum)
{
  static char ret_errortext[128];

  if (ACE::is_sock_error (errnum))
    {
      const ACE_TCHAR *errortext = ACE::sock_error (errnum);
      ACE_OS::strsncpy (ret_errortext,
                        ACE_TEXT_ALWAYS_CHAR (errortext),
                        sizeof (ret_errortext));
      return ret_errortext;
    }
#if defined (ACE_LACKS_STRERROR)
  errno = EINVAL;
  return ACE_OS::strerror_emulation (errnum);
#else /* ACE_LACKS_STRERROR */
  // Adapt to the various ways that strerror() indicates a bad errnum.
  // Most modern systems set errno to EINVAL. Some older platforms return
  // a pointer to a NULL string. This code makes the behavior more consistent
  // across platforms. On a bad errnum, we make a string with the error number
  // and set errno to EINVAL.
  ACE_Errno_Guard g (errno);
  errno = 0;
  char *errmsg = 0;

# if defined (ACE_HAS_TR24731_2005_CRT)
  errmsg = ret_errortext;
  ACE_SECURECRTCALL (strerror_s (ret_errortext, sizeof(ret_errortext), errnum),
                     char *, 0, errmsg);
  if (errnum < 0 || errnum >= _sys_nerr)
    g = EINVAL;

  return errmsg;
# else
#  if defined (ACE_WIN32)
  if (errnum < 0 || errnum >= _sys_nerr)
    errno = EINVAL;
#  endif /* ACE_WIN32 */
  errmsg = ::strerror (errnum);

  if (errno == EINVAL || errmsg == 0 || errmsg[0] == 0)
    {
      ACE_OS::snprintf (ret_errortext, 128, "Unknown error %d", errnum);
      errmsg = ret_errortext;
      g = EINVAL;
    }
  return errmsg;
# endif /* ACE_HAS_TR24731_2005_CRT */
#endif /* ACE_LACKS_STRERROR */
}

#if defined (ACE_LACKS_STRERROR)
/**
 * Just returns "Unknown Error" all the time.
 */
char *
ACE_OS::strerror_emulation (int)
{
  return const_cast <char*> ("Unknown Error");
}
#endif /* ACE_LACKS_STRERROR */

char *
ACE_OS::strsignal (int signum)
{
  static char signal_text[128];
#if defined (ACE_HAS_STRSIGNAL)
  char *ret_val = 0;

# if defined (ACE_NEEDS_STRSIGNAL_RANGE_CHECK)
  if (signum < 0 || signum >= ACE_NSIG)
    ret_val = 0;
  else
# endif /* (ACE_NEEDS_STRSIGNAL_RANGE_CHECK */
  ret_val = ::strsignal (signum);

  if (ret_val <= reinterpret_cast<char *> (0))
    {
      ACE_OS::snprintf (signal_text, 128, "Unknown signal: %d", signum);
      ret_val = signal_text;
    }
  return ret_val;
#else
  if (signum < 0 || signum >= ACE_NSIG)
    {
      ACE_OS::snprintf (signal_text, 128, "Unknown signal: %d", signum);
      return signal_text;
    }
# if defined (ACE_SYS_SIGLIST)
  return ACE_SYS_SIGLIST[signum];
# else
  ACE_OS::snprintf (signal_text, 128, "Signal: %d", signum);
  return signal_text;
# endif /* ACE_SYS_SIGLIST */
#endif /* ACE_HAS_STRSIGNAL */
}

char *
ACE_OS::strerror_r (int errnum, char *buf, size_t buflen)
{
#ifdef ACE_HAS_STRERROR_R
# ifdef ACE_HAS_STRERROR_R_XSI
  if (::strerror_r (errnum, buf, buflen) == 0)
    return buf;
  return const_cast <char*> ("Unknown Error");
# else
  return ::strerror_r (errnum, buf, buflen);
# endif
#else
  return ACE_OS::strncpy (buf, strerror (errnum), buflen);
#endif
}

const char *
ACE_OS::strnchr (const char *s, int c, size_t len)
{
  for (size_t i = 0; i < len; ++i)
    if (s[i] == c)
      return s + i;

  return 0;
}

const ACE_WCHAR_T *
ACE_OS::strnchr (const ACE_WCHAR_T *s, ACE_WCHAR_T c, size_t len)
{
  for (size_t i = 0; i < len; ++i)
    {
      if (s[i] == c)
        {
          return s + i;
        }
    }

  return 0;
}

const char *
ACE_OS::strnstr (const char *s1, const char *s2, size_t len2)
{
  // Substring length
  size_t const len1 = ACE_OS::strlen (s1);

  // Check if the substring is longer than the string being searched.
  if (len2 > len1)
    return 0;

  // Go upto <len>
  size_t const len = len1 - len2;

  for (size_t i = 0; i <= len; i++)
    {
      if (ACE_OS::memcmp (s1 + i, s2, len2) == 0)
        {
         // Found a match!  Return the index.
          return s1 + i;
        }
    }

  return 0;
}

const ACE_WCHAR_T *
ACE_OS::strnstr (const ACE_WCHAR_T *s1, const ACE_WCHAR_T *s2, size_t len2)
{
  // Substring length
  size_t const len1 = ACE_OS::strlen (s1);

  // Check if the substring is longer than the string being searched.
  if (len2 > len1)
    return 0;

  // Go upto <len>
  size_t const len = len1 - len2;

  for (size_t i = 0; i <= len; i++)
    {
      if (ACE_OS::memcmp (s1 + i, s2, len2 * sizeof (ACE_WCHAR_T)) == 0)
        {
          // Found a match!  Return the index.
          return s1 + i;
        }
    }

  return 0;
}

char *
ACE_OS::strsncpy (char *dst, const char *src, size_t maxlen)
{
  char *rdst = dst;
  const char *rsrc = src;
  size_t rmaxlen = maxlen;

  if (rmaxlen > 0)
    {
      if (rdst!=rsrc)
        {
          *rdst = '\0';
          if (rsrc != 0)
            {
              ACE_OS::strncat (rdst, rsrc, --rmaxlen);
            }
        }
      else
        {
          rdst += (rmaxlen - 1);
          *rdst = '\0';
        }
    }
  return dst;
}

ACE_WCHAR_T *
ACE_OS::strsncpy (ACE_WCHAR_T *dst, const ACE_WCHAR_T *src, size_t maxlen)
{
  ACE_WCHAR_T *rdst = dst;
  const ACE_WCHAR_T *rsrc = src;
  size_t rmaxlen = maxlen;

  if (rmaxlen > 0)
    {
      if (rdst!= rsrc)
        {
          *rdst = ACE_TEXT_WIDE ('\0');
          if (rsrc != 0)
            {
              ACE_OS::strncat (rdst, rsrc, --rmaxlen);
            }
        }
      else
        {
          rdst += (rmaxlen - 1);
          *rdst = ACE_TEXT_WIDE ('\0');
        }
    }
  return dst;
}

#if defined (ACE_LACKS_STRTOK_R)
char *
ACE_OS::strtok_r_emulation (char *s, const char *tokens, char **lasts)
{
  if (s == 0)
    s = *lasts;
  else
    *lasts = s;
  if (*s == 0)                  // We have reached the end
    return 0;
  size_t const l_org = ACE_OS::strlen (s);
  s = ::strtok (s, tokens);
  if (s == 0)
    return 0;
  size_t const l_sub = ACE_OS::strlen (s);
  if (s + l_sub < *lasts + l_org)
    *lasts = s + l_sub + 1;
  else
    *lasts = s + l_sub;
  return s ;
}
#endif /* ACE_LACKS_STRTOK_R */

# if defined (ACE_HAS_WCHAR) && defined (ACE_LACKS_WCSTOK)
wchar_t*
ACE_OS::strtok_r_emulation (ACE_WCHAR_T *s,
                            const ACE_WCHAR_T *tokens,
                            ACE_WCHAR_T **lasts)
{
  ACE_WCHAR_T* sbegin = s ? s : *lasts;
  sbegin += ACE_OS::strspn(sbegin, tokens);
  if (*sbegin == 0)
    {
      static ACE_WCHAR_T empty[1] = { 0 };
      *lasts = empty;
      return 0;
  }
  ACE_WCHAR_T*send = sbegin + ACE_OS::strcspn(sbegin, tokens);
  if (*send != 0)
      *send++ = 0;
  *lasts = send;
  return sbegin;
}
# endif  /* ACE_HAS_WCHAR && ACE_LACKS_WCSTOK */

ACE_END_VERSIONED_NAMESPACE_DECL
