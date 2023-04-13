template <typename T> 
class basic_stopwatch : T {
    typedef typename T BaseTimer;
public:
	// create, optionally start timing an activity
    explicit basic_stopwatch(bool start);
    explicit basic_stopwatch(char const* activity = "Stopwatch", bool start = true);
    basic_stopwatch(std::ostream& log, char const* activity = "Stopwatch", bool start = true);
    // stop and destroy a stopwatch
    ~basic_stopwatch();
    // get last lap time (time of last stop)
    unsigned LapGet() const;
    // predicate: return true if the stopwatch is running
    bool IsStarted() const;
    // show accumulated time, keep running, set/return lap
    unsigned Show(char const* event = "show");
    // (re)start a stopwatch, set/return lap time
    unsigned Start(char const* event_namee = "start");
    // stop a running stopwatch, set/return lap time
    unsigned Stop(char const* event_name = "stop");
private:
    char const* m_activity; // "activity" string
    unsigned m_lap; // lap time (time of last stop)
    std::ostream& m_log; // stream on which to log events
};