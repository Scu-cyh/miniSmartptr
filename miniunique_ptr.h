#include <iostream>
using namespace std;

template <typename T>
class miniunique_ptr {
public:
	// ���캯��
	explicit miniunique_ptr(T* p = nullptr) :pointer(p) {}

	// ������ֵ����
	template <typename U>
	miniunique_ptr(miniunique_ptr<U>&) = delete;		// ����һ����ĳ�Ա����ʱ��ʹ��=delete���Σ����������������Ϊdeleted����������������ٱ����ã����򱨴�
	// ������ֵ����

	template <typename U>
	miniunique_ptr(miniunique_ptr<U>&& p) : pointer(p.release()) {}

	// ��������
	~miniunique_ptr() {
		delete pointer;
	}

	// ģ��-> *����
	T* operator->() const {
		return pointer;
	}

	T& operator*() const {
		return *pointer;
	}

	// Σ�ղ���������ԭʼָ��
	T* get() const {
		return pointer;
	}

	// ��������ָ�������û�����ٶ���
	T* release() {
		T* old_ptr = pointer;
		pointer = nullptr;
		return old_ptr;
	}
	// ������һ����������֮ǰ����Ķ��� ע����ܻ�����Լ����¿����Լ�������
	void reset(T* p = nullptr) {
		if (p != pointer) {
			cout << "�����ԭʼ�ڴ�Ĺ���" << endl;
			delete pointer;
			pointer = p;
		}
	}
	// ��ֹ��ֵ��ֵ
	template <typename U>
	miniunique_ptr<T>& operator=(miniunique_ptr<U>& lp) = delete;
	// ������ֵ��ֵ
	template <typename U>
	miniunique_ptr<T>& operator=(miniunique_ptr<U>&& rp) {
		if (this->pointer != rp.pointer) {
			reset(rp.release());
		}
		return *this;
	}

private:
	T* pointer;
};