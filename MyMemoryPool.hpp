/*
* MyMemoryPool.hpp
*
* Copyright (C) 2016 - yasin1151
*
* This Program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This Program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with VallauriSoft; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA  02110-1301  USA
*/

#ifndef _MY_MEMORY_POOL_
#define _MY_MEMORY_POOL_


//�ڴ��

#include <mutex>
#include <list>
#include <algorithm>

template <typename T>
class MyMemoryPool
{
public:
	/**@param init beginSize chunk
	*/
	MyMemoryPool(int beginSize = 10)
	{
		m_chunkSize = sizeof(T);
		addMem(beginSize);
	}

	/*@brief : to allocation a memory chunk 
	*/
	T* Alloc();

	/**@brief : to  recover the memory
	@param : need to recvoer ptr
	*/
	void  Delete(T* ptr);

private:

	void addMem(int size = 0);

private:
	std::mutex		  m_mutex;				//������
	std::list<T*> m_curUseMem;				//��ǰ�Ѿ�ʹ�õ��ڴ��,����Ҫ�ͷŵ��ڴ�
	std::list<T*> m_curHasMem;				//��ǰ����ʹ�õ��ڴ��
	std::size_t	  m_chunkSize;				//�ڴ��Ĵ�С
};

template <typename T>
void MyMemoryPool<T>::addMem(int size)
{
	size_t curSize = m_curUseMem.size();
	if (curSize <= 0 || size != 0)
	{
		curSize = size;
	}
	for (int i = 0; i < curSize * 2; i++)
	{
		m_curHasMem.push_back(new T);
	}
}

template <typename T>
T* MyMemoryPool<T>::Alloc()
{
	m_mutex.lock();
	if (m_curUseMem.empty())
	{
		addMem();
	}

	//�ӿ���ʹ�õ��ڴ����ȡ���������뵽�Ѿ�ʹ�õ��ڴ����
	T* retBuf = m_curHasMem.back();
	m_curHasMem.pop_back();
	m_curUseMem.push_back(retBuf);

	m_mutex.unlock();

	return retBuf;
}

template <typename T>
void  MyMemoryPool<T>::Delete(T* ptr)
{
	if (!ptr)
	{
		return;
	}

	m_mutex.lock();

	m_curUseMem.remove(ptr);
	m_curHasMem.push_back(ptr);
	ptr = nullptr;

	m_mutex.unlock();
}


#endif // !_MY_MEMORY_POOL_

