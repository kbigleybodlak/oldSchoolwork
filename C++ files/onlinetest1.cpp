#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

struct thread_data
{
 int m_id;
 thread_data(int id) : m_id(id) {}
};
DWORD WINAPI thread_func(LPVOID lpParameter)
{
 thread_data *td = (thread_data*)lpParameter;
 std::cout << "thread with id = " << td->m_id << endl;
 return 0;
}
int main()
{
 for (int i=0; i< 10; i++)
 {
  CreateThread(NULL, 0, thread_func, new thread_data(i) , 0, 0);
 }
}
