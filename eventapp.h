//**********************************************************************
// $Id$
//
/// @file eventapp.h
//**********************************************************************

#ifndef EVENTAPP_H_
#define EVENTAPP_H_

#include <fcntl.h>
#include <stdio.h>
#include <event.h>
//======================================================================
// CEventApp class
//
/// CEventApp application class
//======================================================================

class CEventApp
{
public:
	/// constructor
	CEventApp();

	/// destructor
	virtual ~CEventApp();

	/// main function
	/// @param argc: same as process main function
	/// @param argv: same as process main function
	/// @retval 0: ok
	///	@retval <> 0: error
	/// handle initialization
	/// next, sit in a loop processing events
	int main(int argc, char *argv[]);

protected:
	/// static timeout callback function for event library
	/// @param fd: file descriptor for this event (unused)
	/// @param event: type of event (unused)
	/// @param arg: callback argument
	static void static_process_timeout(int fd, short event, void *arg);

	/// timeout callback function
	/// @retval 0: ok
	/// @retval <> 0: error
	int process_timeout(void);

protected:
	static struct timeval const m_timeout_interval;		///< timeout interval
	static struct timeval const m_null_interval;		///< null interval
	struct event m_timeout_event;						///< timeout event

private:
	static char const m_class_name[];					///< class name

};

#endif // EVENTAPP_H_
