#ifndef TZFILE_H
#define TZFILE_H

/*
 * This file is in the public domain, so clarified as of
 * 1996-06-05 by Arthur David Olson.
 *
 * IDENTIFICATION
 *	  src/timezone/tzfile.h
 */

/*
 * This header is for use ONLY with the time conversion code.
 * There is no guarantee that it will remain unchanged,
 * or that it will remain at all.
 * Do NOT copy it to any system include directory.
 * Thank you!
 */

/*
 * Information about time zone files.
 */

#define TZDEFAULT	"localtime"
#define TZDEFRULES	"posixrules"

/*
 * Each file begins with. . .
 */

#define TZ_MAGIC	"TZif"

struct tzhead
{
	char		tzh_magic[4];	/* TZ_MAGIC */
	char		tzh_version[1]; /* '\0' or '2' or '3' as of 2013 */
	char		tzh_reserved[15];		/* reserved; must be zero */
	char		tzh_ttisgmtcnt[4];		/* coded number of trans. time flags */
	char		tzh_ttisstdcnt[4];		/* coded number of trans. time flags */
	char		tzh_leapcnt[4]; /* coded number of leap seconds */
	char		tzh_timecnt[4]; /* coded number of transition times */
	char		tzh_typecnt[4]; /* coded number of local time types */
	char		tzh_charcnt[4]; /* coded number of abbr. chars */
};

/*
 * . . .followed by. . .
 *
 *	tzh_timecnt (char [4])s		coded transition times a la time(2)
 *	tzh_timecnt (unsigned char)s	types of local time starting at above
 *	tzh_typecnt repetitions of
 *		one (char [4])		coded UT offset in seconds
 *		one (unsigned char) used to set tm_isdst
 *		one (unsigned char) that's an abbreviation list index
 *	tzh_charcnt (char)s		'\0'-terminated zone abbreviations
 *	tzh_leapcnt repetitions of
 *		one (char [4])		coded leap second transition times
 *		one (char [4])		total correction after above
 *	tzh_ttisstdcnt (char)s		indexed by type; if 1, transition
 *					time is standard time, if 0,
 *					transition time is wall clock time
 *					if absent, transition times are
 *					assumed to be wall clock time
 *	tzh_ttisgmtcnt (char)s		indexed by type; if 1, transition
 *					time is UT, if 0,
 *					transition time is local time
 *					if absent, transition times are
 *					assumed to be local time
 */

/*
 * If tzh_version is '2' or greater, the above is followed by a second instance
 * of tzhead and a second instance of the data in which each coded transition
 * time uses 8 rather than 4 chars,
 * then a POSIX-TZ-environment-variable-style string for use in handling
 * instants after the last transition time stored in the file
 * (with nothing between the newlines if there is no POSIX representation for
 * such instants).
 *
 * If tz_version is '3' or greater, the above is extended as follows.
 * First, the POSIX TZ string's hour offset may range from -167
 * through 167 as compared to the POSIX-required 0 through 24.
 * Second, its DST start time may be January 1 at 00:00 and its stop
 * time December 31 at 24:00 plus the difference between DST and
 * standard time, indicating DST all year.
 */

/*
 * In the current implementation, "tzset()" refuses to deal with files that
 * exceed any of the limits below.
 */

#define TZ_MAX_TIMES	2000

/* This must be at least 17 for Europe/Samara and Europe/Vilnius.  */
#define TZ_MAX_TYPES	256		/* Limited by what (unsigned char)'s can hold */

#define TZ_MAX_CHARS	50		/* Maximum number of abbreviation characters */
 /* (limited by what unsigned chars can hold) */

#define TZ_MAX_LEAPS	50		/* Maximum number of leap second corrections */

#endif   /* !defined TZFILE_H */
