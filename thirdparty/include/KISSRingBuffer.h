#ifndef BUFFER_H
#define BUFFER_H
#include <vector>
#include <mutex>
template<typename T>
class KISSRingBuffer
{
private:
    std::vector<T> m_buffer;
    unsigned int m_head;
    unsigned int m_tail;
    unsigned int m_size;
    unsigned int m_capacity;
    std::mutex m_mutex;
public:
    KISSRingBuffer(unsigned int n)
    {
        resize(n);
    }
    
    ~KISSRingBuffer(){}
    
    void reset() {
        m_head = 0;
        m_tail = 0;
	m_size = 0;
    }
    
    void resize(unsigned int capacity)
    {
        m_capacity = capacity;
        m_buffer.resize(m_capacity);
	reset();
    }
    
    void put(T val)
    {
        if (full()) return;
	m_buffer[m_head] = val;
        m_mutex.lock();
        m_head = (m_head + 1) % m_capacity;
	m_size++;
        m_mutex.unlock();
    }
    
    void pop_front()
    {
        if (empty()) return;
        m_mutex.lock();
        m_tail = (m_tail + 1) % m_capacity;
	m_size--;
        m_mutex.unlock();
    }

    unsigned int read(T* vals, unsigned int n)
    {
        for (unsigned int i = 0; i<n; ++i) {
            if (empty()) return i;
	    vals[i] = get();
        }
        return n;
    }
    
    unsigned int write(T* vals, unsigned int n) {
        for (unsigned int i = 0; i<n; i++) {
            put(vals[i]);
            if (full()) return i;
        }
        return n;
    }
    
    std::vector<T> readAll()
    {
        std::vector<T> v(m_capacity);
        unsigned int n = read(v.data(), m_capacity);
        v.resize(n);        
        return v;
    }
    
    T get()
    {
        T val = m_buffer[m_tail];
        pop_front();
        return val;
    }
    
    unsigned int capacity() const
    {
        return m_capacity;
    }
    
    bool empty() const
    {
	return m_size==0;
    }
    
    bool full() const
    {
	return m_size==m_capacity;
    }
    
    unsigned int size() const
    {
	return m_size;
    }
    
};
#endif
