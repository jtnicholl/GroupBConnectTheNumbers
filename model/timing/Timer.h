#ifndef TIMER_H
#define TIMER_H

#include <mutex>

namespace model {
namespace timing {

/**
 * This timer class is intended to be ran on its own thread.
 * When run, it increments its counter once per second.
 *
 * @author Luke Whaley
 */
class Timer {
public:
    /**
     * Constructs a new non-running Timer object with
     * a counter of 0.
     *
     * @post !isCounting() && getSecondCount() == 0
     */
    Timer();

    /**
     * Constructs a new non-running Timer with the
     * specified counter value.
     *
     * @pre counter >= 0
     * @post !isCounting() && getSecondCount() == counter
     */
    Timer(int counter);

    /**
     * Deallocates this Timer object and all of its
     * resources.
     */
    virtual ~Timer();

    /**
     * Starts running this timer. This is the method that should
     * be given to an instance of std::thread. The count will continue
     * as long as isCounting() returns true.
     *
     * @post isCounting()
     */
    void run();

    /**
     * Resets this Timer object's counter.
     *
     * @post getSecondCount() == 0
     */
    void reset();

    /**
     * Stops this timer object from running. This method should be called
     * before std::thread::join().
     *
     * @post !isRunning()
     */
    void stop();

    /**
     * Gets this timer's current count in seconds.
     *
     * @return this timer's second count.
     */
    int getSecondCount();

    /**
     * Determines whether or not this Timer object is currently
     * counting.
     *
     * @return true if this Timer is counting; false otherwise.
     */
    bool isCounting();

    /**
     * Adds the callback that is called when this Timer's count
     * is incremented.
     *
     * @param callback the function pointer to call when the count is incremented.
     * @param data the data to pass to the given function pointer.
     */
    void addSecondsIncreasedListener(void (*callback)(void*), void* data);

private:
    volatile int counter;
    volatile bool counting;

    std::mutex counterLock;
    std::mutex countingConditionLock;

    void (*callback)(void*);
    void* callbackData;

    void notifyListener();
};

}
}

#endif // TIMER_H
