#include "minishared_ptr.h"
#include "miniunique_ptr.h"
#include <string>
#include <iostream>
#include <memory>
using namespace std;
class student
{
public:
    student(string n, int a) : name(n), age(a) { cout << "����student name" << name << " age:" << age << endl; }
    ~student()
    {
        cout << "����student name" << name << " age:" << age << endl;
    }
    string getName() const
    {
        return name;
    }
    void older(int n)
    {
        age += n;
    }

private:
    string name;
    int age;
};

struct TA;
struct TB;

struct TA {
    miniweak_ptr<TB> bptr;
    ~TA() {
        cout << "class TA is disstruct..." << endl;
    }
};

struct TB {
    minishared_ptr<TA> aptr;
    ~TB() {
        cout << "class TB is disstruct..." << endl;
    }
};

int main()
{
    /*minishared_ptr���Գ���*/
    cout << "-----minishared_ptr���Գ���-----" << endl;
    minishared_ptr<student> ptr1(new student("С��", 18));
    minishared_ptr<student> ptr2(ptr1);
    cout << "ptr1_count: " << ptr1.use_count() << endl;
    minishared_ptr<student> ptr3(ptr2);
    cout << "ptr1_count: " << ptr1.use_count() << endl;
    minishared_ptr<student> ptr4=ptr2;
    cout << "ptr1_count: " << ptr1.use_count() << endl;
    minishared_ptr<student> ptr5;
    cout << "ptr5_count: " << ptr5.use_count() << endl;
    ptr5 = ptr2;
    cout << "ptr1_count: " << ptr1.use_count() << endl;

    cout << "------------��������------------" << endl;
    ptr1.reset();
    cout << "ptr1_count: " << ptr1.use_count() << endl;
    cout << "ptr2_count: " << ptr2.use_count() << endl;
    ptr2.reset();
    ptr3.reset();
    
    cout << "ptr5��Ψһ������ָ����?";
    if(ptr5.unique())
        cout << "\t��" << endl;
    else
        cout << "\t��" << endl;

    ptr4.reset();
    cout << "ptr5��Ψһ������ָ����?";
    if (ptr5.unique())
        cout << "\t��" << endl;
    else
        cout << "\t��" << endl;
    cout << "--------------------------------" << endl;

    /*miniunique_ptr���Գ���*/
    //cout << "-----minishared_ptr���Գ���-----" << endl;
    //minishared_ptr<student> ptr1(new student("С��", 17));
    //miniweak_ptr<student> p1(ptr1);
    //miniweak_ptr<student> p2(p1);
    //miniweak_ptr<student> p3;
    //p3 = ptr1;
    //miniweak_ptr<student> p4;
    //p4 = p2;

    //miniweak_ptr<student> p5;
    //miniweak_ptr<student> p6(p5);

    //cout << "use_count: " << endl;
    //cout << "wp1: " << p1.use_count() << endl;
    //cout << "wp2: " << p2.use_count() << endl;
    //cout << "wp3: " << p3.use_count() << endl;
    //cout << "wp4: " << p4.use_count() << endl;
    //cout << "wp5: " << p5.use_count() << endl;
    //cout << "wp6: " << p6.use_count() << endl;

    //cout << "------------��������------------" << endl;
    //minishared_ptr<int> shared(new int (10));
    //miniweak_ptr<int> weak(shared);
    //cout << "1. weak " << (weak.expired() ? "is" : "is not") << " expired" << endl;
    //shared.reset();
    //cout << "2. weak " << (weak.expired() ? "is" : "is not") << " expired" << endl;

    //minishared_ptr<int> sp1(new int(520));
    //miniweak_ptr<int> wp;
    //wp = sp1;
    //minishared_ptr<int> sp2 = wp.lock();

    //cout << "use_count: " << wp.use_count() << endl;
    //cout << "*sp1: " << *sp1 << endl;
    //cout << "*sp2: " << *sp2 << endl;

    //cout << "----------ѭ�����ò���----------" << endl;
    //minishared_ptr<TA> ap(new TA);
    //minishared_ptr<TB> bp(new TB);

    //ap->bptr = bp;
    //bp->aptr = ap;

    //cout << "TA object use_count: " << ap.use_count() << endl;
    //cout << "TB object use_count: " << bp.use_count() << endl;
    //cout << "--------------------------------" << endl;
    
    /*miniunique_ptr���Գ���*/
    //cout << "-----miniunique_ptr���Գ���-----" << endl;
    //miniunique_ptr<student> ptr1;
    //miniunique_ptr<student> ptr2(new student("С��", 18));
    //miniunique_ptr<int> ptr3(new int(10));
    //// miniunique_ptr<student> ptr4(ptr2);      // ����
    //cout << "------------��������------------" << endl;
    //ptr2.reset();
    //cout << "ptr3: " << *ptr3.get() << endl;
    //cout << "--------------------------------" << endl;
    
    return 0;
}