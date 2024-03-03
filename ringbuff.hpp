#include <iostream>
template<typename T>
class RingBuffer{
public:
    RingBuffer()
    : _buf(nullptr)
    , _size(0)
    {}

    explicit RingBuffer(size_t sz)
    : RingBuffer() // First call the default constructor
    {
        if (!sz) {
            throw std::invalid_argument("Size cannot be zero.");
        };
        _size = sz;
        _buf = new T[sz];
        _pHead = _buf;
        _pTail = _buf;
        _empty = true;
    }

    ~RingBuffer()
    {
        delete [] _buf;
    }

    RingBuffer(const RingBuffer& other)
            : _size(other._size),
              _buf(new T[other._size]),  // Allocate new memory for the copied buffer
              _pHead(_buf),
              _pTail(_buf),
              _empty(other._empty)
    {
        // Copy elements from the other buffer
        _pHead = _buf + (other._pHead-other._buf);
        _pTail = _buf + (other._pTail - other._buf);
        std::copy(other._buf, other._buf + other._size, _buf);
    }

    RingBuffer& operator = (const RingBuffer& rhv){
        if (this == &rhv)
            return *this;

        RingBuffer temp(rhv);
        swap(temp, *this);

        return *this;
    }

    static void swap(RingBuffer& lhv, RingBuffer& rhv) noexcept
    {
        std::swap(lhv._buf, rhv._buf);
        std::swap(lhv._size, rhv._size);
        std::swap(lhv._empty, rhv._empty);
        std::swap(lhv._pHead, rhv._pHead);
        std::swap(lhv._pTail, rhv._pTail);
    }




    size_t getSize() { return _size; }

    int getCount() {
        if (_pTail>_pHead)
            return _pTail - _pHead;
        if (_pTail<_pHead){
            return _size - (_pHead - _pTail);
        }
        if (_pTail==_pHead & !_empty)
            return _size;
        if (_pTail==_pHead & _empty)
            return 0;
    }

    int getFree() {
        return _size - this->getCount();
    }

    bool isEmpty() const {
        return _empty;
    }

    bool isFull() {
        if (this->getFree()==0)
            return true;
        else
            return false;
    }

    void push(const T& value){
        if (this->isFull())
        {
            throw std::out_of_range("Ring buffer is already full");
        }
        else
        {
            *_pTail = value;
            _empty = false;
            if (_pTail== _buf + _size-1)
                _pTail = _buf;
            else
                _pTail+=1;
        }
    }

    T& front(){
        return *_pHead;
    }

    const T& front() const{
        return *_pHead;
    };


    T& back(){
        if (_pTail == _buf)
            return  *(_buf+_size-1);
        return *(_pTail-1);
    };

    T& back() const {
        if (_pTail == _buf)
            return  *(_buf+_size-1);
        return *(_pTail-1);
    };
    T& pop(){
        if (_empty)
        {
            throw std::out_of_range("Ring buffer is empty");
        }
        else{
            if (_pHead+1==_buf+_size-1)
                _pHead=_buf;
            else{
                _pHead+=1;
                return *(_pHead-1);
            }
            if (this->getCount()==0)
                _empty = true;
        }
    }

private:
    T* _buf;
    size_t _size;
    bool _empty;
    T* _pTail;
    T* _pHead;
};

