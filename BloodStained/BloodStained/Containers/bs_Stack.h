#ifndef _BS_STACK_H_
#define _BS_STACK_H_

#include "bs_Array.h"

namespace bs
{
	template <class T>
	class Stack
	{
	public:
		Stack()
		{

		}

		Stack(const Stack& s)
			:m_buffer(s.m_buffer)
		{

		}

		~Stack()
		{

		}

		const T& peek()
		{
			return m_buffer.last();
		}

		T pop()
		{
			T result = m_buffer.last();
			m_buffer.remove(m_buffer.pop());
			return result;
		}

		ptrsize count() { return m_buffer.count(); }
		bool isEmpty() { return m_buffer.count() == 0; }

		void push(const T& item) { m_buffer.add(item); }

	private:
		Array<T> m_buffer;
	};
}
#endif // _BS_STACK_H_