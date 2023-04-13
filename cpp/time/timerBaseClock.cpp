class TimerBaseClock {
public:
    // clears the timer
    TimerBaseClock() { 
    	m_start = -1; 
    }
    // clears the timer
    void Clear() { 
    	m_start = -1; 
    }
    // returns true if the timer is running
    bool IsStarted() const { 
    	return (m_start != -1); 
    }
    // start the timer
    void Start() { 
    	m_start = clock(); 
    }
    // get the number of milliseconds since the timer was started
    unsigned long GetMs() {
        clock_t now;
        if (IsStarted()) {
            now = clock();
            clock_t dt = (now - m_start);
            return (unsigned long)(dt * 1000 / CLOCKS_PER_SEC);
        }
        return 0;
    }
private:
    clock_t m_start;
};