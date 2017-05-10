#ifndef BS_FUNCTION_H
#define BS_FUNCTION_H

#include "../Utilities/bs_types.h"

namespace bs
{
	template <typename returnType, typename T0, typename T1 = nothing, typename T2 = nothing, typename T3 = nothing, typename T4 = nothing, typename T5 = nothing>
	struct Function
	{
	};

	//0 arguments
	template <typename returnType>
	struct Function<returnType, void, nothing, nothing, nothing, nothing, nothing>
	{
		
	private:
		typedef returnType(*functionPointer)();
		functionPointer m_pointer;

	public:
		Function()
		{

		}
		Function(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}
		returnType operator()()
		{
			return (*m_pointer)();
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//1 argument
	template <typename returnType, typename T0>
	struct Function<returnType, T0, nothing, nothing, nothing, nothing, nothing>
	{
	private:
		typedef returnType(*functionPointer)(T0 t0);
		functionPointer m_pointer;

	public:
		Function()
		{

		}
		Function(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		returnType operator()(T0 t0)
		{
			return (*m_pointer)(t0);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//2 arguments
	template <typename returnType, typename T0, typename T1>
	struct Function<returnType, T0, T1, nothing, nothing, nothing, nothing>
	{
	private:
		typedef returnType(*functionPointer)(T0 t0, T1 t1);
		functionPointer m_pointer;

	public:
		Function()
		{

		}
		Function(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		returnType operator()(T0 t0, T1 t1)
		{
			return (*m_pointer)(t0, t1);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//3 arguments
	template <typename returnType, typename T0, typename T1, typename T2>
	struct Function<returnType, T0, T1, T2, nothing, nothing, nothing>
	{
	private:
		typedef returnType(*functionPointer)(T0 t0, T1 t1, T2 t2);
		functionPointer m_pointer;

	public:
		Function()
		{

		}
		Function(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		returnType operator()(T0 t0, T1 t1, T2 t2)
		{
			return (*m_pointer)(t0, t1, t2);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//4 arguments
	template <typename returnType, typename T0, typename T1, typename T2, typename T3>
	struct Function<returnType, T0, T1, T2, T3, nothing, nothing>
	{
	private:
		typedef returnType(*functionPointer)(T0 t0, T1 t1, T2 t2, T3 t3);
		functionPointer m_pointer;

	public:
		Function()
		{

		}
		Function(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		returnType operator()(T0 t0, T1 t1, T2 t2, T3 t3)
		{
			return (*m_pointer)(t0, t1, t2, t3);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//5 arguments
	template <typename returnType, typename T0, typename T1, typename T2, typename T3, typename T4>
	struct Function<returnType, T0, T1, T2, T3, T4, nothing>
	{
	private:
		typedef returnType(*functionPointer)(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4);
		functionPointer m_pointer;

	public:
		Function()
		{

		}
		Function(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		returnType operator()(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4)
		{
			return (*m_pointer)(t0, t1, t2, t3, t4);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};
}

#endif