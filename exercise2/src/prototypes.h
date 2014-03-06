void setupTimer(void);
void disableTimer(void);
void startTimer(void);
void stopTimer(void);

void setupDAC(void);
void disableDAC(void);

void setupNVIC(void);
void setupGPIO(void);
void GPIO_interrupt_clear(void);
void GPIO_LED(void);
int map_input(void);

void setupSleep(int arg);
void wfi(void);
