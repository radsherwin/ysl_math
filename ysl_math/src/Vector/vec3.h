#ifndef YSL_MATH_VEC3_H
#define YSL_MATH_VEC3_H

#include "Trig.h"
#include "Util.h"
#include "TypeCheck.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <array>

namespace ysl {
	//class mat4;
	template<typename T> class vec2;
	template<typename T> class vec3;
	template<typename T> class vec4;

	template<typename T> vec3<T> operator*( T s, const vec3<T>& rhs );
	template<typename T> void transpose_matrix( std::array<vec3<T>, 4>& v );

	template< class T >
	struct TypeIsInt {
		static const bool value = false;
	};

	template<>
	struct TypeIsInt< int > {
		static const bool value = true;
	};

	template<typename T>
	class vec3 {
	public:
		vec3() : data{ 0, 0, 0 } {}
		vec3( const vec3& v ) : data( v.data ) {}
		vec3& operator=( const vec3& v ) {
			if ( this != &v )
			{
				data = v.data;
			}
			return *this;
		}

		~vec3() = default;

		inline explicit vec3( std::array<T, 2> a ) : data{ a[ 0 ], a[ 1 ], 0 } {}
		inline explicit vec3( std::array<T, 3> a ) : data( a ) {}
		inline explicit vec3( const vec4<T>& v ) : data( v.as_vec3().data ) {}

		inline explicit vec3( const __m128& m ) {
			auto _data = ysl::bit_cast< std::array<f32, 4> >( m );
			std::copy_n( _data.begin(), data.size(), data.begin() );
		}
		inline explicit vec3( T v ) : data{ v,v,v } {}
		inline explicit vec3( T x, T y ) : data{ x,y,0 } {}
		inline explicit vec3( T x, T y, T z ) : data{ x,y,z } {}

		inline explicit vec3( const std::array< T, 3 >& v ) : data{ v[ 0 ], v[ 1 ], v[ 2 ] } {};
		inline explicit vec3( const std::array< T, 4 >& v ) : data{ v[ 0 ], v[ 1 ], v[ 2 ] } {};

		template<typename G>
		inline explicit vec3( const std::array< G, 3 >& v ) requires ( !ysl::is_typename_match<T, G>::value )
			: data{ static_cast< T >( v[ 0 ] ), static_cast< T >( v[ 1 ] ), static_cast< T >( v[ 2 ] ) } {};
		template<typename G>
		inline explicit vec3( const std::array< G, 4 >& v ) requires ( !ysl::is_typename_match<T, G>::value )
			: data{ static_cast< T >( v[ 0 ] ), static_cast< T >( v[ 1 ] ), static_cast< T >( v[ 2 ] ) } {};

		template<typename G>
		inline explicit vec3( G v ) requires ( !ysl::is_typename_match<T, G>::value ) : data{ static_cast< T >( v ),static_cast< T >( v ),static_cast< T >( v ) } {}
		template<typename G>
		inline explicit vec3( G x, G y ) requires ( !ysl::is_typename_match<T, G>::value ) : data{ static_cast< T >( x ),static_cast< T >( y ),0 } {}
		template<typename G>
		inline explicit vec3( G x, G y, G z ) requires ( !ysl::is_typename_match<T, G>::value ) : data{ static_cast< T >( x ),static_cast< T >( y ),static_cast< T >( z ) } {}

		inline T operator[]( usize i ) const;

		inline T& operator[]( usize i );

		// vec operator overloads
		inline vec3 operator*( const vec3& v2 ) const;
		inline vec3& operator*=( const vec3& v2 );
		inline vec3 operator+( const vec3& v2 ) const;
		inline vec3& operator+=( const vec3& v2 );
		inline vec3 operator-( const vec3& v2 ) const;
		inline vec3& operator-=( const vec3& v2 );
		inline vec3 operator/( const vec3& v2 ) const;
		inline vec3& operator/=( const vec3& v2 );

		// scalar operator overloads
		inline vec3 operator*( T s ) const;
		inline vec3& operator*=( T s );
		inline vec3 operator/( T s ) const;
		inline vec3& operator/=( T s );

		template<typename G>
		inline vec3 operator*( G s ) const requires ( ysl::is_typename_match<T, G>::value == false ) {
			__m128 m = _mm_loadu_ps( &data[ 0 ] );

			m = _mm_mul_ps( m, _mm_set1_ps( static_cast< T >( s ) ) );

			return vec3<T>{m};
		}

		template<typename G>
		inline vec3& operator*=( G s ) requires ( ysl::is_typename_match<T, G>::value == false ) {
			vec3 x = *this;
			data = ( x * static_cast< T >( s ) ).data;
			return *this;
		}

		// misc operators
		inline vec3 operator-() const;

		// static functions
		vec3 random() {
			return vec3{ util::random_f32(), util::random_f32(), util::random_f32() };
		}

		vec3 random( f32 min, f32 max ) {
			return vec3{ util::random_f32( min, max ), util::random_f32( min, max ), util::random_f32( min, max ) };
		}

		// convertor functions
		vec4<T> as_vec4() const {
			return vec4<T>{data, 0.0f};
		}

		vec4<T> as_point4() const {
			return vec4<T>{data};
		}

		// vec2 vec3::as_vec2() const
		// {
		//     return vec2{data[0], data[1]};
		// }   
		//vec2 as_vec2() const;

		// getters
		[[nodiscard]] inline T x() const { return data[ 0 ]; }
		[[nodiscard]] inline T y() const { return data[ 1 ]; }
		[[nodiscard]] inline T z() const { return data[ 2 ]; }

		// setters
		[[nodiscard]] inline T& x() { return data[ 0 ]; }
		[[nodiscard]] inline T& y() { return data[ 1 ]; }
		[[nodiscard]] inline T& z() { return data[ 2 ]; }
		inline void set( i32 idx, T s ) { assert( idx >= 0 && idx < 3 ); data[ idx ] = s; }
		inline void set( T s ) { data = { {s,s,s} }; }
		inline void set_x( T s ) { data[ 0 ] = s; }
		inline void set_y( T s ) { data[ 1 ] = s; }
		inline void set_z( T s ) { data[ 2 ] = s; }

		inline void set( i32 idx, T s ) requires ( !ysl::is_f32<T>::value ) { assert( idx >= 0 && idx < 3 ); data[ idx ] = static_cast< T >( s ); }
		inline void set( T s ) requires ( !ysl::is_f32<T>::value ) { data = { {static_cast< T >( s ),static_cast< T >( s ),static_cast< T >( s )} }; }
		inline void set_x( T s ) requires ( !ysl::is_f32<T>::value ) { data[ 0 ] = static_cast< T >( s ); }
		inline void set_y( T s ) requires ( !ysl::is_f32<T>::value ) { data[ 1 ] = static_cast< T >( s ); }
		inline void set_z( T s ) requires ( !ysl::is_f32<T>::value ) { data[ 2 ] = static_cast< T >( s ); }

		// math functions
		vec3 get_inv() const {
			const __m128 m = _mm_loadu_ps( &data[ 0 ] );
			return vec3{ _mm_rcp_ps( m ) };
		}

		f32 mag() const {
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			m = _mm_mul_ps( m, m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			m = _mm_sqrt_ps( m );
			return _mm_cvtss_f32( m );
		}

		f32 mag_squared() const {
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			m = _mm_mul_ps( m, m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_f32( m );
		}

		void norm() {
			const f32 _mag = mag();
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			__m128 m2 = _mm_rcp_ps( _mm_set1_ps( _mag ) );
			m = _mm_mul_ps( m, m2 );

			auto ar = ysl::bit_cast< std::array<f32, 4> >( m );
			std::copy_n( ar.begin(), data.size(), data.begin() );
		}

		vec3 get_norm() const {
			const f32 _mag = mag();
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			__m128 m2 = _mm_rcp_ps( _mm_set1_ps( _mag ) );
			m = _mm_mul_ps( m, m2 );

			return vec3{ m };
		}

		T dot( const vec3& v2 ) const {
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );
			m = _mm_mul_ps( m, m2 );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_f32( m );
		}

		u32 dot( const vec3& v2 ) const requires ( ysl::is_u32<T>::value == true ) {
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );
			m = _mm_mul_ps( m, m2 );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_u32( m );
		}

		i32 dot( const vec3& v2 ) const requires ( ysl::is_i32<T>::value == true ) {
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );
			m = _mm_mul_ps( m, m2 );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_i32( m );
		}

		i64 dot( const vec3& v2 ) const requires ( ysl::is_i64<T>::value == true ) {
			__m128 m = _mm_loadu_ps( &data[ 0 ] );
			const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );
			m = _mm_mul_ps( m, m2 );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return reinterpret_cast< i64 >( _mm_cvtss_i64( m ) );
		}

		vec3 cross( const vec3& v2 ) const {
			const __m128 m = _mm_loadu_ps( &data[ 0 ] );
			const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );
			__m128 tmp0 = _mm_shuffle_ps( m, m, _MM_SHUFFLE( 3, 0, 2, 1 ) );
			const __m128 tmp1 = _mm_shuffle_ps( m2, m2, _MM_SHUFFLE( 3, 1, 0, 2 ) );
			__m128 tmp2 = _mm_mul_ps( tmp0, m2 );
			const __m128 tmp3 = _mm_mul_ps( tmp0, tmp1 );
			tmp2 = _mm_shuffle_ps( tmp2, tmp2, _MM_SHUFFLE( 3, 0, 2, 1 ) );
			tmp0 = _mm_sub_ps( tmp3, tmp2 );

			return vec3{ tmp0 };
		}

		// helper functions
		bool near_zero( f32 e ) const {
			for ( usize i = 0; i < 3; ++i )
			{
				if ( abs( data[ i ] ) > e ) return false;
			}

			return true;
		}

		void rcp() {
			data[ 0 ] = 1 / data[ 0 ];
			data[ 1 ] = 1 / data[ 1 ];
			data[ 2 ] = 1 / data[ 2 ];
		}

		vec3 get_rcp() const {
			return vec3{ 1 / data[ 0 ], 1 / data[ 1 ], 1 / data[ 2 ] };
		}

		vec3 flip_sign() const {
			return vec3{ -data[ 0 ], -data[ 1 ], -data[ 2 ] };
		}

		void print() const {
			printf( "vec3: (%.02f, %.02f, %.02f)\n", data[ 0 ], data[ 1 ], data[ 2 ] );
		}

		// friend
		inline friend vec3 operator*( T s, const vec3& rhs );


	private:
		std::array<T, 3> data;
	}; // class vec 3


	//------------------------------------------------------------------------------------------------------
	//                                  inline
	//------------------------------------------------------------------------------------------------------

	template<typename T>
	inline T vec3<T>::operator[]( usize i ) const {
		assert( i >= 0 && i < 3 );
		return data[ i ];
	}

	template<typename T>
	inline T& vec3<T>::operator[]( usize i ) {
		assert( i >= 0 && i < 3 );
		return data[ i ];
	}

	// vec operator overloads
	template<typename T>
	inline  vec3<T> vec3<T>::operator*( const vec3<T>& v2 ) const {
		const __m128 m = _mm_loadu_ps( &data[ 0 ] );
		const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );

		return vec3<T>{_mm_mul_ps( m, m2 )};
	}

	template<typename T>
	inline vec3<T>& vec3<T>::operator*=( const vec3<T>& v2 ) {
		vec3<T> x = *this;
		data = ( x * v2 ).data;
		return *this;
	}

	template<typename T>
	inline vec3<T> vec3<T>::operator+( const vec3<T>& v2 ) const {
		const __m128 m = _mm_loadu_ps( &data[ 0 ] );
		const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );

		return vec3<T>{_mm_add_ps( m, m2 )};
	}

	template<typename T>
	inline vec3<T>& vec3<T>::operator+=( const vec3<T>& v2 ) {
		vec3<T> x = *this;
		data = ( x + v2 ).data;
		return *this;
	}

	template<typename T>
	inline vec3<T> vec3<T>::operator-( const vec3<T>& v2 ) const {
		const __m128 m = _mm_loadu_ps( &data[ 0 ] );
		const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );

		return vec3<T>{_mm_sub_ps( m, m2 )};
	}

	template<typename T>
	inline vec3<T>& vec3<T>::operator-=( const vec3<T>& v2 ) {
		vec3<T> x = *this;
		data = ( x - v2 ).data;
		return *this;
	}

	template<typename T>
	inline vec3<T> vec3<T>::operator/( const vec3<T>& v2 ) const {
		const __m128 m = _mm_loadu_ps( &data[ 0 ] );
		const __m128 m2 = _mm_loadu_ps( &v2.data[ 0 ] );
		return vec3<T>{_mm_div_ps( m, m2 )};
	}

	template<typename T>
	inline vec3<T>& vec3<T>::operator/=( const vec3<T>& v2 ) {
		vec3<T> x = *this;
		data = ( x / v2 ).data;
		return *this;
	}

	// scalar operator overlaods

	template<typename T>
	inline vec3<T> vec3<T>::operator*( T s ) const {
		__m128 m = _mm_loadu_ps( &data[ 0 ] );

		m = _mm_mul_ps( m, _mm_set1_ps( s ) );

		return vec3<T>{m};
	}

	template<typename T>
	inline vec3<T> operator*( T s, const vec3<T>& rhs ) // friend
	{
		__m128 m = _mm_loadu_ps( &rhs.data[ 0 ] );
		m = _mm_mul_ps( m, _mm_set1_ps( s ) );

		return vec3<T>{m};
	}

	template<typename T>
	inline vec3<T>& vec3<T>::operator*=( T s ) {
		vec3<T> x = *this;
		data = ( x * s ).data;
		return *this;
	}

	template<typename T>
	inline vec3<T> vec3<T>::operator/( T s ) const {
		const __m128 m = _mm_loadu_ps( &data[ 0 ] );
		const __m128 m2 = _mm_rcp_ps( _mm_set1_ps( s ) );

		return vec3{ _mm_mul_ps( m, m2 ) };
	}

	template<typename T>
	inline vec3<T>& vec3<T>::operator/=( T s ) {
		vec3 x = *this;
		data = ( x / s ).data;
		return *this;
	}

	// misc operators
	template<typename T>
	inline vec3<T> vec3<T>::operator-() const {
		__m128 m = _mm_loadu_ps( &data[ 0 ] );
		m = _mm_xor_ps( m, _mm_set1_ps( -0.f ) );
		return vec3{ m };
	}

	//template<typename T>
	//inline f32 dot(const vec3<T> &v1, const vec3<T> &v2)
	//{
	//    __m128 m = _mm_loadu_ps(&v1.data[0]);
	//    const __m128 m2 = _mm_loadu_ps(&v2.data[0]);
	//    m = _mm_mul_ps(m, m2);
	//    m = _mm_hadd_ps(m, m);
	//    m = _mm_hadd_ps(m, m);
	//    return _mm_cvtss_f32(m);
	//}
	//
	//template<typename T>
	//inline vec3<T> cross(const vec3<T> &v1, const vec3<T> &v2)
	//{
	//    const __m128 m = _mm_loadu_ps(&v1.data[0]);
	//    const __m128 m2 = _mm_loadu_ps(&v2.data[0]);
	//    __m128 tmp0 = _mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 0, 2, 1));
	//    const __m128 tmp1 = _mm_shuffle_ps(m2, m2, _MM_SHUFFLE(3, 1, 0, 2));
	//    __m128 tmp2 = _mm_mul_ps(tmp0, m2);
	//    const __m128 tmp3 = _mm_mul_ps(tmp0, tmp1);
	//    tmp2 = _mm_shuffle_ps(tmp2, tmp2, _MM_SHUFFLE(3, 0, 2, 1));
	//    tmp0 = _mm_sub_ps(tmp3, tmp2);
	//
	//    return vec3<T>{tmp0};
	//}

} // namespace ysl

#endif