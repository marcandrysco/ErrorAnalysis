#ifndef POLL_H
#define POLL_H

#ifdef WINDOWS
#else

#include <poll.h>

/**
 * Poll structure.
 *   @fd: The file desciptor.
 *   @events, revents: The events.
 */
struct poll_t {
	int fd;
	short events, revents;
};

#endif

#endif
