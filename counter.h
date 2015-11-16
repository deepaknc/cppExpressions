template <typename T>
struct Counter
{
    Counter() 
    {
        count++;
    }
    ~Counter()
    {
        count--;
    }
    Counter(const Counter&)
    {
        count++;
    }
    static int count;
};

template<typename T>
int Counter<T>::count = 0; // this now can go in header
