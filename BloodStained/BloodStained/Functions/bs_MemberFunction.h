#ifndef BS_MEMBERFUNCTION_H
#define BS_MEMBERFUNCTION_H


#include "../Utilities/bs_types.h"
#include "bs_BaseMemberFunction.h"
namespace bs
{
	template <typename Type, typename returnType, typename T0, typename T1 = nothing, typename T2 = nothing, typename T3 = nothing, typename T4 = nothing, typename T5 = nothing>
	struct MemberFunction : public BaseMemberFunction<returnType, T0, T1, T2, T3, T4, T5>
	{
	};

	//0 arguments
	template <typename Type, typename returnType>
	struct MemberFunction<Type, returnType, void, nothing, nothing, nothing, nothing, nothing> 
		:public BaseMemberFunction<returnType, void, nothing, nothing, nothing, nothing, nothing>
	{

	private:
		typedef returnType (Type::*functionPointer)();
		functionPointer m_pointer;
		Type*	m_caster;
	public:
		MemberFunction()
			:m_pointer(nullptr)
		{

		}

		~MemberFunction() override
		{

		}

		bool canExecute() override
		{
			return m_pointer != nullptr;
		}

		MemberFunction(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}
		returnType operator()()override
		{
			return (*m_caster.*m_pointer)();
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		void setCaster(Type* caster)
		{
			m_caster = caster;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}

		
	};

	//1 argument
	template <typename Type, typename returnType, typename T0>
	struct MemberFunction<Type, returnType, T0, nothing, nothing, nothing, nothing, nothing>
		:public BaseMemberFunction<returnType, T0, nothing, nothing, nothing, nothing, nothing>
	{
	private:
		typedef returnType (Type::*functionPointer)(T0);
		functionPointer m_pointer;
		Type*	m_caster;
	public:
		MemberFunction()
		{

		}
		MemberFunction(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		~MemberFunction() override
		{

		}

		bool canExecute() override
		{
			return m_pointer != nullptr;
		}

		returnType operator()(T0 t0)override
		{
			return (*m_caster.*m_pointer)(t0);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		void setCaster(Type* caster)
		{
			m_caster = caster;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//2 arguments
	template <typename Type, typename returnType, typename T0, typename T1>
	struct MemberFunction<Type, returnType, T0, T1, nothing, nothing, nothing, nothing>
		:public BaseMemberFunction<returnType, T0, T1, nothing, nothing, nothing, nothing>
	{
	private:
		typedef returnType(Type::*functionPointer)(T0 t0, T1 t1);
		functionPointer m_pointer;
		Type*	m_caster;
	public:
		MemberFunction()
		{

		}
		MemberFunction(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		~MemberFunction() override
		{

		}

		bool canExecute() override
		{
			return m_pointer != nullptr;
		}

		returnType operator()(T0 t0, T1 t1)override
		{
			return (*m_caster.*m_pointer)(t0, t1);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		void setCaster(Type* caster)
		{
			m_caster = caster;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}

	};

	//3 arguments
	template <typename Type, typename returnType, typename T0, typename T1, typename T2>
	struct MemberFunction<Type, returnType, T0, T1, T2, nothing, nothing, nothing>
		:public BaseMemberFunction<returnType, T0, T1, T2, nothing, nothing, nothing>
	{
	private:
		typedef returnType(Type::*functionPointer)(T0 t0, T1 t1, T2 t2);
		functionPointer m_pointer;
		Type*	m_caster;
	public:
		MemberFunction()
		{

		}
		MemberFunction(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		~MemberFunction() override
		{

		}

		bool canExecute() override
		{
			return m_pointer != nullptr;
		}

		returnType operator()(T0 t0, T1 t1, T2 t2)override
		{
			return (*m_caster.*m_pointer)(t0, t1, t2);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		void setCaster(Type* caster)
		{
			m_caster = caster;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//4 arguments
	template <typename Type, typename returnType, typename T0, typename T1, typename T2, typename T3>
	struct MemberFunction<Type, returnType, T0, T1, T2, T3, nothing, nothing>
		:public BaseMemberFunction<returnType, T0, T1, T2, T3, nothing, nothing>
	{
	private:
		typedef returnType(Type::*functionPointer)(T0 t0, T1 t1, T2 t2, T3 t3);
		functionPointer m_pointer;
		Type*	m_caster;
	public:
		MemberFunction()
		{

		}
		MemberFunction(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		~MemberFunction() override
		{

		}

		bool canExecute() override
		{
			return m_pointer != nullptr;
		}

		returnType operator()(T0 t0, T1 t1, T2 t2, T3 t3) override
		{
			return (*m_caster.*m_pointer)(t0, t1, t2, t3);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		void setCaster(Type* caster)
		{
			m_caster = caster;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

	//5 arguments
	template <typename Type, typename returnType, typename T0, typename T1, typename T2, typename T3, typename T4>
	struct MemberFunction<Type, returnType, T0, T1, T2, T3, T4, nothing>
		:public BaseMemberFunction<returnType, T0, T1, T2, T3, T4, nothing>
	{
	private:
		typedef returnType(Type::*functionPointer)(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4);
		functionPointer m_pointer;
		Type*	m_caster;
	public:
		MemberFunction()
		{

		}
		MemberFunction(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		~MemberFunction() override
		{

		}

		bool canExecute() override
		{
			return m_pointer != nullptr;
		}

		returnType operator()(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4) override
		{
			return (*m_caster.*m_pointer)(t0, t1, t2, t3, t4);
		}

		void operator=(const functionPointer& pointer)
		{
			this->m_pointer = pointer;
		}

		void setCaster(Type* caster)
		{
			m_caster = caster;
		}

		functionPointer getPointer()
		{
			return m_pointer;
		}
	};

}

#endif // !BS_MEMBERFUNCTION_H
