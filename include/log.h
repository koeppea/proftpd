/*
 * ProFTPD - FTP server daemon
 * Copyright (c) 1997, 1998 Public Flood Software
 * Copyright (c) 1999, 2000 MacGyver aka Habeeb J. Dihu <macgyver@tos.net>
 * Copyright (c) 2001, 2002, 2003 The ProFTPD Project team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 * As a special exemption, Public Flood Software/MacGyver aka Habeeb J. Dihu
 * and other respective copyright holders give permission to link this program
 * with OpenSSL, and distribute the resulting executable, without including
 * the source code for OpenSSL in the source distribution.
 */

/* Logging, either to syslog or stderr, as well as debug logging
 * and debug levels.
 *
 * $Id: log.h,v 1.17 2003-01-02 17:28:17 castaglia Exp $
 */

#ifndef PR_LOG_H
#define PR_LOG_H

#ifndef LOG_AUTHPRIV
#define LOG_AUTHPRIV LOG_AUTH
#endif

#if !defined(WTMP_FILE) && defined(_PATH_WTMP)
#define WTMP_FILE _PATH_WTMP
#endif

/* These are the debug levels, higher numbers print more debugging
 * info.  DEBUG0 (the default) prints nothing.
 */

#define DEBUG9		9
#define DEBUG8		8
#define DEBUG7		7
#define DEBUG6		6
#define DEBUG5		5
#define DEBUG4		4
#define	DEBUG3		3
#define DEBUG2		2
#define DEBUG1		1
#define DEBUG0		0

/* log_openfile() return values */
#define LOG_WRITEABLE_DIR	-2
#define LOG_SYMLINK		-3

/* Log file modes */
#define LOG_SYSTEM_MODE         0640
#define LOG_XFER_MODE           0644

char *fmt_time(time_t);
int log_wtmp(char *, const char *, const char *, p_in_addr_t *);
void log_setfacility(int);
int log_openfile(const char *, int *, mode_t);
int log_opensyslog(const char *);
void log_closesyslog(void);

/* Utilize gcc's __attribute__ pragma for signalling that it should perform
 * printf-style checking of this function's arguments.
 */
void log_pri(int, const char *, ...)
#ifdef __GNUC__
       __attribute__ ((format (printf, 2, 3)));
#else
       ;
#endif

void log_auth(int, const char *, ...);
void log_stderr(int);
int  log_setdebuglevel(int);

/* Utilize gcc's __attribute__ pragma for signalling that it should perform
 * printf-style checking of this function's arguments.
 */
void log_debug(int, const char *, ...)
#ifdef __GNUC__
       __attribute__ ((format (printf, 2, 3)));
#else
       ;
#endif

void log_discard(void);
void init_log(void);

int log_str2sysloglevel(const char *);

/* TransferLog routines */
int log_open_xfer(const char *);
void log_close_xfer(void);
int log_xfer(int, char *, off_t, char *, char, char, char, char *, char);

#endif /* PR_LOG_H */
