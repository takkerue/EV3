#ifndef _SW_MAIN_H_
#define _SW_MAIN_H_

typedef enum {
	StopMode = 0,
	RunningMode,
	NumOfMode
} StopWatchMode;

void SW_main(void);
unsigned int SW_currentTimeMs(void);
StopWatchMode SW_mode(void);

#endif
