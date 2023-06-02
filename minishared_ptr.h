#pragma once
#include<iostream>
using namespace std;
class counter {
public:
    counter() :shared_count(0), weak_count(0) {}
    int shared_count;
    int weak_count;
};
template <typename T> class miniweak_ptr;

template <typename T>
class minishared_ptr
{
public:
    friend class miniweak_ptr<T>;
    // ���캯��
    explicit minishared_ptr(T* p = nullptr) : pointer(p) {
        count_ptr = new counter();
        if (p) {
            count_ptr->shared_count = 1;
        }
    }

    template <typename U>
    minishared_ptr(minishared_ptr<U>& p) : pointer(p.pointer), count_ptr(p.count_ptr) {
        count_ptr->shared_count++;
    }


    template <typename U>
    minishared_ptr(miniweak_ptr<U>& p) : pointer(p.pointer), count_ptr(p.count_ptr) {
        count_ptr->shared_count++;
    }

    // ��������
    ~minishared_ptr()
    {
        _release();
    }
    // ģ��-> * ����
    T* operator->() const
    {
        return pointer;
    }
    T& operator*() const
    {
        return *pointer;
    }
    // Σ�ղ��� ����ԭʼָ��
    T* get() const
    {
        return pointer;
    }
    // ������һ����������֮ǰ����Ķ��� ע����ܻ�����Լ����¿����Լ�������
    void reset(T* p = nullptr)
    {
        if (p != pointer)
        {
            _release();
            pointer = p;
            count_ptr = new counter();
            count_ptr->shared_count = 0;
        }
    }

    // ������ֵ��ֵ
    // ��д��ֵ����������������unique_ptr��ͬ�ĵط�,�����ټ���һ��U��Ϊ�����ӵ���
    // ���ڲ��������ͷ��Ҳ��������������
    template <typename U>
    minishared_ptr<T>& operator=(minishared_ptr<U>& rp)
    {
        if (this->pointer != rp.pointer)
        {
            _release();
            pointer = rp.pointer;
            count_ptr = rp.count_ptr;
            count_ptr->shared_count++;
        }
        return *this;
    }
    int use_count() {
        return count_ptr->shared_count;
    }
    bool unique() {
        return use_count() == 1;
    }


private:
    T* pointer;
    counter* count_ptr;
    void _release() {
        count_ptr->shared_count--;
        //cout << "minishared_ptr�������� s,w:" << count_ptr->shared_count << " " << count_ptr->weak_count << endl;
        if (count_ptr->shared_count < 1) {
            delete pointer;
            if (count_ptr->weak_count < 1) {
                delete count_ptr;
                count_ptr = nullptr;
            }
        }
    }
};


template <typename T>
class miniweak_ptr {
public:
    friend class minishared_ptr<T>;
    // ���캯��
    // explicit miniweak_ptr() : pointer(nullptr), count_ptr(nullptr) {}
    miniweak_ptr() {
        pointer = nullptr;
        count_ptr = new counter();
        count_ptr->shared_count = 0;
        count_ptr->weak_count = 0;
    }

    template <typename U>
    miniweak_ptr(miniweak_ptr<U>& p) : pointer(p.pointer), count_ptr(p.count_ptr) {
        count_ptr->weak_count++;
    }


    template <typename U>
    miniweak_ptr(minishared_ptr<U>& p) : pointer(p.pointer), count_ptr(p.count_ptr) {
        count_ptr->weak_count++;
    }

    // ��������
    ~miniweak_ptr()
    {
        _release();
    }
    // ģ��-> * ����
    T* operator->() const
    {
        return pointer;
    }
    T& operator*() const
    {
        return *pointer;
    }
    // Σ�ղ��� ����ԭʼָ��
    T* get() const
    {
        return pointer;
    }
    // ������һ����������֮ǰ����Ķ��� ע����ܻ�����Լ����¿����Լ�������
    void reset(T* p = nullptr)
    {
        if (p != pointer)
        {
            delete pointer;
            pointer = p;
        }
    }

    // ��д��ֵ����������������unique_ptr��ͬ�ĵط�,�����ټ���һ��U��Ϊ�����ӵ���
    // ���ڲ��������ͷ��Ҳ��������������
    template <typename U>
    miniweak_ptr<T>& operator=(miniweak_ptr<U>& rp)
    {
        if (this->pointer != rp.pointer)
        {
            _release();
            pointer = rp.pointer;
            count_ptr = rp.count_ptr;
            count_ptr->weak_count++;
        }
        return *this;
    }

    template <typename U>
    miniweak_ptr<T>& operator=(minishared_ptr<U>& rp)
    {
        if (this->pointer != rp.pointer)
        {
            _release();
            pointer = rp.pointer;
            count_ptr = rp.count_ptr;
            count_ptr->weak_count++;
        }
        return *this;
    }
    minishared_ptr<T> lock() {
        return minishared_ptr<T>(*this);
    }
    int use_count() {
        return count_ptr->shared_count;
    }
    bool unique() {
        return use_count() == 1;
    }
    bool expired() {
        return use_count() == 0;
    }


private:
    T* pointer;
    counter* count_ptr;
    void _release() {
        if (count_ptr!=nullptr) {
            
            cout << "miniweak_ptr�������� s,w:" << count_ptr->shared_count << " " << count_ptr->weak_count << endl;

            if (count_ptr->shared_count < 1 && count_ptr->weak_count < 1) {
                delete count_ptr;
                count_ptr = nullptr;
            }
            else {
                count_ptr->weak_count--;
            }
        }
    }
};