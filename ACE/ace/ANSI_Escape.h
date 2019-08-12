/**
 * @file ANSI_Escape.h
 *
 * @author Frederick Hornsey <hornseyf@objectcomputing.com>
 *
 * Provides Support for ANSI Escape Sequences, which provides coloring of
 * terminal output on most systems. ANSI Escape Codes are quite powerful
 * depending on terminal support, but here we are just providing the basic 16
 * colors and bold.
 */

#ifndef ACE_ANSI_ESCAPE_H
#define ACE_ANSI_ESCAPE_H

#include /**/ "ace/pre.h"

#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#  pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/OS_NS_stdio.h"

#define ACE_ANSI_START "\x1b" // ESCAPE
#define ACE_ANSI_CSI_START "["
#define ACE_ANSI_SGR_END "m"

#define ACE_ANSI_RESET_SGR "0"

#define ACE_ANSI_BOLD "1"
#define ACE_ANSI_END_BOLD "22"

#define ACE_ANSI_INVERSE "7"
#define ACE_ANSI_END_INVERSE "27"

#define ACE_ANSI_FG_BLACK "30"
#define ACE_ANSI_FG_RED "31"
#define ACE_ANSI_FG_GREEN "32"
#define ACE_ANSI_FG_YELLOW "33"
#define ACE_ANSI_FG_BLUE "34"
#define ACE_ANSI_FG_MAGENTA "35"
#define ACE_ANSI_FG_CYAN "36"
#define ACE_ANSI_FG_WHITE "37"
#define ACE_ANSI_FG_DEFAULT "39"

#define ACE_ANSI_BG_BLACK "40"
#define ACE_ANSI_BG_RED "41"
#define ACE_ANSI_BG_GREEN "42"
#define ACE_ANSI_BG_YELLOW "43"
#define ACE_ANSI_BG_BLUE "44"
#define ACE_ANSI_BG_MAGENTA "45"
#define ACE_ANSI_BG_CYAN "46"
#define ACE_ANSI_BG_WHITE "47"
#define ACE_ANSI_BG_DEFAULT "49"

#define ACE_ANSI_CODE(CODE) ACE_ANSI_START CODE
#define ACE_ANSI_CSI(CSI_CODE) ACE_ANSI_CODE(ACE_ANSI_CSI_START CSI_CODE)
#define ACE_ANSI_SGR(SGR_CODE) ACE_ANSI_CSI(SGR_CODE ACE_ANSI_SGR_END)

bool ACE_Export ace_file_supports_ansi_escape (FILE *file);

#include /**/ "ace/post.h"
#endif /* ACE_ANSI_ESCAPE_CODES_H */
