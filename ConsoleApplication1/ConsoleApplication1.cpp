#include <iostream>

using namespace std;



template<typename T>
class myShared_ptr
{
    T* _array;
    size_t* _count;

    void release()
    {
        if (_count)
        {
            (*_count)--;

            if ((*_count) == 0)
            {
                delete _array;
                delete _count;
            }
        }
    }

public:

    myShared_ptr()
    {
        _array = nullptr;
        _count = nullptr;
    }
    explicit myShared_ptr(T* ptr)
    {
        _array = ptr;
        _count = new size_t(1);
    }
    myShared_ptr(const myShared_ptr<T>& sharedptr)
    {
        this->_array = sharedptr._array;

        if (sharedptr._count != nullptr)
            this->_count = new size_t(*(sharedptr._count) + 1);
    }
    myShared_ptr(myShared_ptr<T>&& sharedptr)
    {
        this->_array = sharedptr._array;
        this->_count = sharedptr._count;

        sharedptr._array = nullptr;
        sharedptr._count = nullptr;
    }

    myShared_ptr& operator=(const myShared_ptr<T>& sharedptr)
    {
        if (this != &sharedptr)
        {
            release();

            this->_array = sharedptr._array;
            this->_count = sharedptr._count;

            if (_count) (*_count)++;
        }
        return *this;
    }

    T* get() const { return _array; }
    size_t use_count() const
    {
        if (_count != nullptr)
            return *_count;
        else return NULL;
    }

    T& operator*() const
    {
        return *_array;
    }

    operator bool()
    {
        return(_array != nullptr);
    }

    T* operator->() const { return _array; }

    void reset(T* sharedptr = nullptr)
    {
        release();

        if (sharedptr != nullptr)
        {
            _array = sharedptr;
            _count = new size_t(1);
        }
        else
        {
            _array = nullptr;
            _count = nullptr;
        }
    }

    template<typename T>
    friend ostream& operator<<(ostream& out, const myShared_ptr<T>& myPtr);

    ~myShared_ptr() { release(); }
};


template<typename T>
ostream& operator<<(ostream& print, const myShared_ptr<T>& myPtr)
{
    print << myPtr.get();
    return print;
}



void main()
{

}