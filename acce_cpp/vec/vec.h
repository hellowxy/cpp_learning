#ifndef VEC_H
#define VEC_H

#include<cstddef>
#include<memory>

template<typename T>
class Vec
{
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef T value_type;

        Vec()
        {
            create();
        }

        Vec(const Vec& v)
        {
            create(v.begin(), v.end());
        }

        explicit Vec(int count, const T& val = T())
        {
            create(count, val);
        }

        Vec& operator=(const Vec&);

        ~Vec()
        {
            uncreate();
        }

        size_type size()
        {
            return avail - data;
        }

        size_type size() const
        {
            return avail - data;
        }


        T& operator[](size_type i)
        {
            return data[i];
        }

        const T& operator[](size_type i) const
        {
            return data[i];
        }

        iterator begin()
        {
            return data;
        }

        const_iterator begin() const
        {
            return data;
        }

        iterator end()
        {
            return avail;
        }

        const_iterator end() const
        {
            return avail;
        }

        void push_back(const T& val)
        {
            if(avail == limit)
            {
                grow();
            }
            unchecked_append(val);
        }

        void clear()
        {
            uncreate();
        }
    private:
        iterator data;
        iterator avail;
        iterator limit;
        std::allocator<T> alloc;

        void create();
        void create(size_type n, const T& val);
        void create(const_iterator begin, const_iterator end);

        void uncreate();

        void grow();
        void unchecked_append(const T& val);
};

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    if(&rhs != this)
    {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template<typename T>
void Vec<T>::create()
{
    data = avail = limit = nullptr;
}

template<typename T>
void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, avail, val);
}

template<typename T>
void Vec<T>::create(const_iterator begin, const_iterator end)
{
    data = alloc.allocate(end - begin);
    limit = avail = std::uninitialized_copy(begin, end, data);
}

template<typename T>
void Vec<T>::uncreate()
{
    if(data)
    {
        iterator it = avail;
        while(it != data)
        {
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = nullptr;
}

template<typename T>
void Vec<T>::grow()
{
    size_type new_size = 1;
    if(size() > 0)
    {
        new_size = 2 * size();
    }
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template<typename T>
void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}
#endif