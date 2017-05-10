#ifndef BS_BASEMEMBERFUNCTION
#define BS_BASEMEMBERFUNCTION


namespace bs
{
	template <typename returnType, typename T0, typename T1 = nothing, typename T2 = nothing, typename T3 = nothing, typename T4 = nothing, typename T5 = nothing>
	struct BaseMemberFunction
	{
	};

	//0 arguments
	template <typename returnType>
	struct BaseMemberFunction<returnType, void, nothing, nothing, nothing, nothing, nothing>
	{
	public:
		BaseMemberFunction()
		{

		}

		virtual ~BaseMemberFunction()
		{

		}

		virtual returnType operator()()
		{
			
		}


		virtual bool canExecute()
		{
			return true;
		}
	};

	//1 argument
	template <typename returnType, typename T0>
	struct BaseMemberFunction<returnType, T0, nothing, nothing, nothing, nothing, nothing>
	{
	public:
		BaseMemberFunction()
		{

		}

		virtual ~BaseMemberFunction()
		{

		}

		virtual returnType operator()(T0 t0)
		{

		}

		virtual bool canExecute()
		{
			return true;
		}
	};

	//2 arguments
	template <typename returnType, typename T0, typename T1>
	struct BaseMemberFunction<returnType, T0, T1, nothing, nothing, nothing, nothing>
	{
	public:
		BaseMemberFunction()
		{

		}

		virtual ~BaseMemberFunction()
		{

		}

		virtual returnType operator()(T0 t0, T1 t1)
		{

		}


		virtual bool canExecute()
		{
			return true;
		}
	};

	//3 arguments
	template <typename returnType, typename T0, typename T1, typename T2>
	struct BaseMemberFunction<returnType, T0, T1, T2, nothing, nothing, nothing>
	{
	public:
		BaseMemberFunction()
		{

		}

		virtual ~BaseMemberFunction()
		{

		}

		virtual returnType operator()(T0 t0, T1 T1, T2 T2)
		{

		}

		virtual bool canExecute()
		{
			return true;
		}
	};

	//4 arguments
	template <typename returnType, typename T0, typename T1, typename T2, typename T3>
	struct BaseMemberFunction<returnType, T0, T1, T2, T3, nothing, nothing>
	{
	public:
		BaseMemberFunction()
		{

		}

		virtual ~BaseMemberFunction()
		{

		}

		virtual returnType operator()(T0 t0, T1 t1, T2 t2, T3 t3)
		{

		}

		virtual bool canExecute()
		{
			return true;
		}
	};

	//5 arguments
	template <typename returnType, typename T0, typename T1, typename T2, typename T3, typename T4>
	struct BaseMemberFunction<returnType, T0, T1, T2, T3, T4, nothing>
	{
	public:
		BaseMemberFunction()
		{

		}

		virtual ~BaseMemberFunction()
		{

		}

		virtual returnType operator()(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4)
		{

		}


		virtual bool canExecute()
		{
			return true;
		}
	};
}

#endif // !BS_BASEMEMBERFUNCTÝON
