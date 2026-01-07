#pragma once

/*
https://stackoverflow.com/questions/16868129/how-to-store-variadic-template-arguments
https://www.murrayc.com/permalink/2015/12/05/modern-c-variadic-template-parameters-and-tuples/
*/

#include <cstddef>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace lib {

	namespace detail
	{

		struct return_void {};

		template<size_t N>
		struct invoke_helper
		{
			template<typename F, typename T, typename... A>
			static inline auto invoke(F && f, T && t, A &&... a) -> decltype(invoke_helper<N - 1>::invoke(
					::std::forward<F>(f), ::std::forward<T>(t), ::std::get<N - 1>(::std::forward<T>(t)), ::std::forward<A>(a)...))
			{
				return invoke_helper<N - 1>::invoke( ::std::forward<F>(f), ::std::forward<T>(t),
					::std::get<N - 1>(::std::forward<T>(t)), ::std::forward<A>(a)... );
			}
		};

		template<>
		struct invoke_helper<0> {
			template<typename F, typename T, typename... A>
			static inline auto invoke(F && f, T &&, A &&... a) -> decltype(::std::forward<F>(f)(::std::forward<A>(a)...))
			{
				return ::std::forward<F>(f)(::std::forward<A>(a)...);
			}
		};

		template<typename F, typename T>
		inline auto invoke(F && f, T && t) -> decltype(invoke_helper<
			::std::tuple_size< typename ::std::decay<T>::type >::value >::invoke(::std::forward<F>(f), ::std::forward<T>(t)))
		{
			return invoke_helper< ::std::tuple_size< typename ::std::decay<T>::type	>::value>::invoke(::std::forward<F>(f), ::std::forward<T>(t));
		}


	} /* namespace detail */


	template< typename func_type, typename... args_types >
	struct task
	{
		enum status{ idle, run, done };
		using function_type = func_type;
		using arguments_type = std::tuple<args_types...>;
		using result_type = typename std::conditional<
			!std::is_void< typename function_type::result_type >::value,
				typename function_type::result_type,
				detail::return_void >::type;

		function_type m_function;
		arguments_type m_arguments;
		typename result_type m_result;

		task() = default;

		task(function_type&& func, arguments_type&& args)
			: m_function(std::move(func))
			, m_arguments(std::move(args))
		{
		}

		const arguments_type& get_arguments() const { return m_arguments; }
		const result_type& get_result() const { return m_result; }


		void invoke()
		{
			invoke<typename result_type>();
		}

	private:

		template <typename rtype, typename std::enable_if< !std::is_same< rtype, detail::return_void >::value, typename rtype>::type* = 0 >
		void invoke()
		{
			m_result = detail::invoke(m_function, m_arguments);
		}

		template < typename rtype, typename std::enable_if< std::is_same< rtype, detail::return_void >::value, void>::type* = 0>
		void invoke()
		{
			detail::invoke(m_function, m_arguments);
		}

	};


#if 1

	template< typename func_type, typename... arguments_types >
	task<func_type, arguments_types...>
		make_task(func_type&& function, const arguments_types&&... args)
	{
		return task<func_type, arguments_types...>(function, std::forvard<arguments_types>(args)...);
	}

#endif

} /*namespace lib */
