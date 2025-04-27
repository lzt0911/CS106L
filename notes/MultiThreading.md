# Multi Threading
## atomic
Atomic types are types that encapsulate(封装) a value whose access is guaranteed to not cause data racces and can be used to synchronize(同步) memory accesses among different threads.
## thread
## mutex
* mutex types: are lockable types used to protect access to a critical section of code: locking a mutex prevents other threads from locking it until it is unlocked: `mutex`, `recursive_mutex`, `timed_mutex`, `recursive_timed_mutex`.
* locks are objects that manage a mutex by associating its access to their own lifetime: `lock_guard`, `unique_lock`.
* functions to lock multiple mutexes simultaneously(同时)(`try_lock`, `lock`) and to directly prevent concurrent execution(并发执行) of a specific function(`call_once`).
## condition_variable
## future
```cpp

std::mutex mtx;

void greet(int id) {
    std::lock_guard<std::mutex> lg(mtx); 
    //std::this_thread::sleep_for(std::chrono::second(5)); 
    cout << "Hello there! My name is " << id << endl;
} 

int main() {
    cout << "Greetings from my threads..." << endl;
    std::thread thread1(greet, 1);
    std::thread thread2(greet, 2);

    thread1.join();
    thread2.join();
    
    cout << "All greetins done!" << endl;

    return 0;
}
```