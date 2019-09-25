
#include "eventapp.h"

int main(int argc, char *argv[])
{
	CEventApp app;
	int ret;

	ret = app.main(argc, argv);

	return ret;
}

char const CEventApp::m_class_name[] = "CEventApp";


struct timeval const CEventApp::m_timeout_interval = {
	1,								// int    tv_sec;	// seconds
	0								// int    tv_usec;	// microseconds
};

struct timeval const CEventApp::m_null_interval = {
	0,								// int    tv_sec;	// seconds
	0								// int    tv_usec;	// microseconds
};


//----------------------------------------------------------------------
// CEventApp::CEventApp()
//
// constructor
//----------------------------------------------------------------------

CEventApp::CEventApp()
{

}

//----------------------------------------------------------------------
// CEventApp::~CEventApp()
//
// destructor
//----------------------------------------------------------------------

CEventApp::~CEventApp()
{

}

//----------------------------------------------------------------------
// CEventApp::main()
//
// main function
// @param argc: same as process main function
// @param argv: same as process main function
// @retval 0: ok
// @retval <> 0: error
// handle initialization
// next, sit in a loop processing events
//----------------------------------------------------------------------

int CEventApp::main(int argc, char *argv[])
{
	int ret;
	
	// initialize event library
	event_init();

	event_set(&m_timeout_event, -1, 0, &static_process_timeout, this);

	// schedule timeout event for first timeout
	ret = event_add(&m_timeout_event, &m_timeout_interval);
	if (ret < 0) {
		// error
		fprintf(stderr, "%s::%s(): event_add() returned %d\n", m_class_name, __FUNCTION__, ret);
		return ret;
	}

	// run event loop as long as no handler calls 
	// event_loopexit() to signal an error
	event_loop(0);

	return ret;
}

//----------------------------------------------------------------------
// CEventApp::static_process_timeout()
//
// static timeout callback function for event library
// @param fd: file descriptor for this event (unused)
// @param event: type of event (unused)
// @param arg: callback argument
//----------------------------------------------------------------------

void CEventApp::static_process_timeout(int, short, void *arg)
{
	CEventApp *papp;
	int ret;

	// cast third argument to class instance pointer
	papp = static_cast<CEventApp *>(arg);

	// invoke (non-static) class
	ret = papp->process_timeout();
	if (ret < 0) {
		// exit event loop (and terminate app)
		event_loopexit(&m_null_interval);
	}
}

//----------------------------------------------------------------------
// CEventApp::process_timeout()
//
// timeout callback function
// @retval 0: ok
// @retval <> 0: error
//----------------------------------------------------------------------

int CEventApp::process_timeout(void)
{
	int ret;

	printf("%s::%s(): hello from CEventApp\n", m_class_name, __FUNCTION__);

	// reschedule timeout event for next timeout
	ret = event_add(&m_timeout_event, &m_timeout_interval);
	if (ret < 0) {
		// error
		fprintf(stderr, "%s::%s(): event_add() returned %d\n", m_class_name, __FUNCTION__, ret);
	}

	return ret;
}

__attribute__((constructor))
void ecosystem_app_handler(void)
{
	printf("%s(): Application started\n", __FUNCTION__);
}
