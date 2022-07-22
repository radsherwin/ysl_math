#ifndef YSL_MATH_VEC4_H
#define YSL_MATH_VEC4_H

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

	template<typename T> vec4<T> operator*( T s, const vec4<T>& rhs );
	template<typename T> void transpose_matrix( std::array<vec4<T>, 4>& v );
	template<typename T> void transpose_matrix( vec4< T >& v0, vec4< T >& v1, vec4< T >& v2, vec4< T >& v3 );

	template<typename T>
	class vec4 {
	public:
		vec4() : _m( _mm_set_ps( 1.0f, 0.0f, 0.0f, 0.0f ) ) {}
		vec4( const vec4& v ) : _m( v._m ) {}
		vec4& operator=( const vec4& v ) {
			if ( this != &v )
			{
				_m = v._m;
			}

			return *this;
		}

		~vec4() = default;

		inline explicit vec4( std::array<T, 2> a ) : _m( _mm_loadu_ps( &a[ 0 ] ) ) { reinterpret_cast< T* >( &_m )[ 3 ] = 1; }
		inline explicit vec4( std::array<T, 3> a ) : _m( _mm_loadu_ps( &a[ 0 ] ) ) { reinterpret_cast< T* >( &_m )[ 3 ] = 1; }
		inline explicit vec4( std::array<T, 3> a, T s ) : _m( _mm_loadu_ps( &a[ 0 ] ) ) { reinterpret_cast< T* >( &_m )[ 3 ] = s; }
		inline explicit vec4( std::array<T, 4> a ) : _m( _mm_load_ps( &a[ 0 ] ) ) {}
		inline explicit vec4( const __m128& m ) : _m( m ) {}
		inline explicit vec4( f32 v ) : _m( _mm_set1_ps( v ) ) {}
		inline explicit vec4( f32 x, f32 y ) : _m( _mm_set_ps( 1, 0, y, x ) ) {}
		inline explicit vec4( f32 x, f32 y, f32 z ) : _m( _mm_set_ps( 1, z, y, x ) ) {}
		inline explicit vec4( f32 x, f32 y, f32 z, f32 w ) : _m( _mm_set_ps( w, z, y, x ) ) {}

		template<typename G>
		inline explicit vec4( G v ) requires ( !ysl::is_f32< G >::value ) : _m( _mm_set1_ps( static_cast< f32 >( v ) ) ) {}
		template<typename G>
		inline explicit vec4( G x, G y ) requires ( !ysl::is_f32< G >::value ) : _m( _mm_set_ps( 1, 0, static_cast< f32 >( y ), static_cast< f32 >( x ) ) ) {}
		template<typename G>
		inline explicit vec4( G x, G y, G z ) requires ( !ysl::is_f32< G >::value ) : _m( _mm_set_ps( 1, static_cast< f32 >( z ), static_cast< f32 >( y ), static_cast< f32 >( x ) ) ) {}
		template<typename G>
		inline explicit vec4( G x, G y, G z, G w ) requires ( !ysl::is_f32< G >::value ) : _m( _mm_set_ps( static_cast< f32 >( w ), static_cast< f32 >( z ), static_cast< f32 >( y ), static_cast< f32 >( x ) ) ) {}

		inline T operator[]( usize i ) const;

		inline T& operator[]( usize i );
		//vec4<T> operator*(const mat4 &rhs);

		inline vec4 operator*( const vec4& v2 ) const;
		inline vec4& operator*=( const vec4& v2 );
		inline vec4 operator+( const vec4& v2 ) const;
		inline vec4& operator+=( const vec4& v2 );
		inline vec4 operator-( const vec4& v2 ) const;
		inline vec4& operator-=( const vec4& v2 );
		inline vec4 operator/( const vec4& v2 ) const;
		inline vec4& operator/=( const vec4& v2 );

		// scalar operator overlaods
		inline vec4 operator*( T s ) const;
		inline vec4& operator*=( T s );
		inline vec4 operator/( T s ) const;
		inline vec4& operator/=( T s );

		template<typename G>
		inline vec4 operator*( T s ) const requires ( ysl::is_typename_match<T, G>::value == false ) {
			return vec4<T>{_mm_mul_ps( _m, _mm_set1_ps( static_cast< T >( s ) ) )};
		}

		template<typename G>
		inline vec4& operator*=( T s ) requires ( ysl::is_typename_match<T, G>::value == false ) {
			_m = _mm_mul_ps( _m, _mm_set1_ps( static_cast< T >( s ) ) );

			return *this;
		}

		// misc operators
		inline vec4 operator-() const;


		// static functions
		// static functions
		vec4<T> random() {
			return vec4<T>{util::random_f32(), util::random_f32(), util::random_f32(), util::random_f32()};
		}

		vec4<T> random_point4() {
			return vec4<T>{util::random_f32(), util::random_f32(), util::random_f32()};
		}

		vec4<T> random( f32 min, f32 max ) {
			return vec4<T>{util::random_f32( min, max ), util::random_f32( min, max ), util::random_f32( min, max ), util::random_f32( min, max )};
		}

		vec4<T> random_point4( f32 min, f32 max ) {
			return vec4<T>{util::random_f32( min, max ), util::random_f32( min, max ), util::random_f32( min, max )};
		}

		// converter functions
		vec3<T> as_vec3() const {
			return vec3<T>{data};
		}
		//vec2 as_vec2() const;
		vec4<T>& to_point4() {
			reinterpret_cast< T* >( &_m )[ 0 ] = 1;

			return *this;
		}

		// getters
		[[nodiscard]] inline T x() const { return _mm_cvtss_f32( _mm_shuffle_ps( _m, _m, _MM_SHUFFLE( 0, 0, 0, 0 ) ) ); }
		[[nodiscard]] inline T y() const { return _mm_cvtss_f32( _mm_shuffle_ps( _m, _m, _MM_SHUFFLE( 1, 1, 1, 1 ) ) ); }
		[[nodiscard]] inline T z() const { return _mm_cvtss_f32( _mm_shuffle_ps( _m, _m, _MM_SHUFFLE( 2, 2, 2, 2 ) ) ); }
		[[nodiscard]] inline T w() const { return _mm_cvtss_f32( _mm_shuffle_ps( _m, _m, _MM_SHUFFLE( 3, 3, 3, 3 ) ) ); }

		// setters
		[[nodiscard]] inline T& x() { return reinterpret_cast< T* >( &_m )[ 0 ]; }
		[[nodiscard]] inline T& y() { return reinterpret_cast< T* >( &_m )[ 1 ]; }
		[[nodiscard]] inline T& z() { return reinterpret_cast< T* >( &_m )[ 2 ]; }
		inline void set( T s ) { _m = _mm_set1_ps( s ); }
		inline void set_x( T s ) { _m = _mm_move_ss( _m, _mm_set_ss( s ) ); }
		inline void set_y( T s ) { _m = _mm_insert_ps( _m, _mm_set_ss( s ), 0x10 ); }
		inline void set_z( T s ) { _m = _mm_insert_ps( _m, _mm_set_ss( s ), 0x20 ); }
		inline void set_w( T s ) { _m = _mm_insert_ps( _m, _mm_set_ss( s ), 0x30 ); }

		inline void set( T s ) requires ( !ysl::is_f32<T>::value ) { _m = _mm_set1_ps( static_cast< f32 >( s ) ); }
		inline void set_x( T s ) requires ( !ysl::is_f32<T>::value ) { _m = _mm_move_ss( _m, _mm_set_ss( static_cast< f32 >( s ) ) ); }
		inline void set_y( T s ) requires ( !ysl::is_f32<T>::value ) { _m = _mm_insert_ps( _m, _mm_set_ss( static_cast< f32 >( s ) ), 0x10 ); }
		inline void set_z( T s ) requires ( !ysl::is_f32<T>::value ) { _m = _mm_insert_ps( _m, _mm_set_ss( static_cast< f32 >( s ) ), 0x20 ); }
		inline void set_w( T s ) requires ( !ysl::is_f32<T>::value ) { _m = _mm_insert_ps( _m, _mm_set_ss( static_cast< f32 >( s ) ), 0x30 ); }

		template<typename G>
		inline void set( G idx, T s ) requires ( ysl::is_usize<G>::value || ysl::is_i32<G>::value ) {
			switch ( idx )
			{
				case 0:
					_m = _mm_move_ss( _m, _mm_set_ss( s ) );
					break;
				case 1:
					_m = _mm_insert_ps( _m, _mm_set_ss( s ), 0x10 );
					break;
				case 2:
					_m = _mm_insert_ps( _m, _mm_set_ss( s ), 0x20 );
					break;
				case 3:
					_m = _mm_insert_ps( _m, _mm_set_ss( s ), 0x30 );
					break;
				default:
					assert( false );
			}
		}

		// math functions
		f32 mag() const {
			__m128 m = _mm_mul_ps( _m, _m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			m = _mm_sqrt_ps( m );
			return _mm_cvtss_f32( m );
		}

		f32 mag_squared() const {
			__m128 m = _mm_mul_ps( _m, _m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_f32( m );
		}

		void norm() {
			const f32 _mag = mag();
			_m = _mm_div_ps( _m, _mm_set1_ps( _mag ) );
		}

		vec4<T> get_norm() const {
			const f32 _mag = mag();
			const __m128 m = _mm_div_ps( _m, _mm_set1_ps( _mag ) );
			return vec4<T>{m};
		}

		T dot( const vec4<T>& v2 ) const {
			__m128 m = _mm_mul_ps( _m, v2._m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_f32( m );
		}

		u32 dot( const vec4<T>& v2 ) const requires( ysl::is_u32<T>::value == true ) {
			__m128 m = _mm_mul_ps( _m, v2._m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_u32( m );
		}

		i32 dot( const vec4<T>& v2 ) const requires( ysl::is_i32<T>::value == true ) {
			__m128 m = _mm_mul_ps( _m, v2._m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return _mm_cvtss_i32( m );
		}

		i64 dot( const vec4<T>& v2 ) const requires( ysl::is_i64<T>::value == true ) {
			__m128 m = _mm_mul_ps( _m, v2._m );
			m = _mm_hadd_ps( m, m );
			m = _mm_hadd_ps( m, m );
			return reinterpret_cast< i64 >( _mm_cvtss_i64( m ) );
		}

		vec4<T> cross( const vec4<T>& v2 ) const {
			__m128 tmp0 = _mm_shuffle_ps( _m, _m, _MM_SHUFFLE( 3, 0, 2, 1 ) );
			const __m128 tmp1 = _mm_shuffle_ps( v2._m, v2._m, _MM_SHUFFLE( 3, 1, 0, 2 ) );
			__m128 tmp2 = _mm_mul_ps( tmp0, v2._m );
			const __m128 tmp3 = _mm_mul_ps( tmp0, tmp1 );
			tmp2 = _mm_shuffle_ps( tmp2, tmp2, _MM_SHUFFLE( 3, 0, 2, 1 ) );
			tmp0 = _mm_sub_ps( tmp3, tmp2 );

			return vec4<T>{tmp0};
		}

		// helper functions
		bool near_zero( f32 e ) const {
			for ( size_t i = 0; i < 4; ++i )
			{
				if ( ysl::abs( ysl::bit_cast< std::array<T, 4> >( _m )[ i ] ) > e ) return false;
			}

			return true;
		}

		void rcp() {
			_m = _mm_rcp_ps( _m );
		}

		vec4<T> get_rcp() const {
			const __m128 m = _mm_rcp_ps( _m );
			//m = _mm_insert_ps(m, _mm_set_ss(_mm_cvtss_f32(_mm_shuffle_ps(_m, _m, _MM_SHUFFLE(3, 3, 3, 3)))), 0x30);
			return vec4<T>{m};
		}

		vec4<T> flip_sign() const {
			const __m128 m = _mm_mul_ps( _m, _mm_set1_ps( -1.0f ) );
			return vec4<T>{m};
		}

		void print() const {
			auto _data = ysl::bit_cast< std::array<T, 4> >( _m );
			printf( "vec4: (%.02f, %.02f, %.02f, %.02f)\n", _data[ 0 ], _data[ 1 ], _data[ 2 ], _data[ 3 ] );
		}

		//private:
			// friend
		friend vec4<T> operator*( T s, const vec4<T>& rhs );

		template<typename T> friend void transpose_matrix( std::array<vec4<T>, 4>& v );
		template<typename T> friend void transpose_matrix( vec4< T >& v0, vec4< T >& v1, vec4< T >& v2, vec4< T >& v3 );
	private:
		union {
			__m128 _m;
			struct {
				std::array<T, 4> data;
				//simd_float data;
			};

		};

	}; // class vec 4

	//------------------------------------------------------------------------------------------------------
	//                                  inline
	//------------------------------------------------------------------------------------------------------
	// vec operator overloads
	template<typename T>
	inline T vec4<T>::operator[]( usize i ) const {
		assert( i >= 0 && i < 4 );
		return data[ i ];
	}

	template<typename T>
	inline T& vec4<T>::operator[]( usize i ) {
		assert( i >= 0 && i < 4 );
		return data[ i ];
	}

	// matrix operator overloads
	// template<typename T>
	// vec4<T> vec4<T>::operator*(const mat4 &rhs)
// {
//     vec4<T> res{};
// 	for (i32 i = 0; i < 4; ++i)
// 	{
// 		//res.set(i, dot(lhs, rhs.col(i)));
//         res[i] = dot(rhs.col(i));
// 	}

	template<typename T>
	inline  vec4<T> vec4<T>::operator*( const vec4<T>& v2 ) const {
		return vec4{ _mm_mul_ps( _m, v2._m ) };
	}

	template<typename T>
	inline vec4<T>& vec4<T>::operator*=( const vec4<T>& v2 ) {
		_m = _mm_mul_ps( _m, v2._m );
		return *this;
	}

	template<typename T>
	inline vec4<T> vec4<T>::operator+( const vec4<T>& v2 ) const {
		return vec4<T>{_mm_add_ps( _m, v2._m )};
	}

	template<typename T>
	inline vec4<T>& vec4<T>::operator+=( const vec4<T>& v2 ) {
		_m = _mm_add_ps( _m, v2._m );
		return *this;
	}

	template<typename T>
	inline vec4<T> vec4<T>::operator-( const vec4<T>& v2 ) const {
		return vec4<T>{_mm_sub_ps( _m, v2._m )};
	}

	template<typename T>
	inline vec4<T>& vec4<T>::operator-=( const vec4<T>& v2 ) {
		_m = _mm_sub_ps( _m, v2._m );
		return *this;
	}

	template<typename T>
	inline vec4<T> vec4<T>::operator/( const vec4<T>& v2 ) const {
		return vec4<T>{_mm_div_ps( _m, v2._m )};
	}

	template<typename T>
	inline vec4<T>& vec4<T>::operator/=( const vec4<T>& v2 ) {
		_m = _mm_div_ps( _m, v2._m );
		return *this;
	}

	// scalar operator overloads
	template<typename T>
	inline vec4<T> vec4<T>::operator*( T s ) const {
		return vec4<T>{_mm_mul_ps( _m, _mm_set1_ps( s ) )};
	}

	template<typename T>
	inline vec4<T>& vec4<T>::operator*=( T s ) {
		_m = _mm_mul_ps( _m, _mm_set1_ps( s ) );

		return *this;
	}

	template<typename T>
	inline vec4<T> vec4<T>::operator/( T s ) const {
		return vec4<T>{_mm_div_ps( _m, _mm_set1_ps( s ) )};
	}

	template<typename T>
	inline vec4<T>& vec4<T>::operator/=( T s ) {
		_m = _mm_div_ps( _m, _mm_set1_ps( s ) );
		return *this;
	}

	// misc operators
	template<typename T>
	inline vec4<T> vec4<T>::operator-() const {
		const __m128 m = _mm_xor_ps( _m, _mm_set1_ps( -0.f ) );
		return vec4<T>{m};
	}

	////////////
	// friends
	template<typename T>
	inline vec4<T> operator*( T s, const vec4<T>& rhs ) {
		return rhs * s;
	}

	template<typename T>
	inline void transpose_matrix( std::array<vec4<T>, 4>& v ) {
		const __m128 r1 = _mm_shuffle_ps( v[ 0 ]._m, v[ 1 ]._m, _MM_SHUFFLE( 1, 0, 1, 0 ) );
		const __m128 r2 = _mm_shuffle_ps( v[ 0 ]._m, v[ 1 ]._m, _MM_SHUFFLE( 3, 2, 3, 2 ) );
		const __m128 r3 = _mm_shuffle_ps( v[ 2 ]._m, v[ 3 ]._m, _MM_SHUFFLE( 1, 0, 1, 0 ) );
		const __m128 r4 = _mm_shuffle_ps( v[ 2 ]._m, v[ 3 ]._m, _MM_SHUFFLE( 3, 2, 3, 2 ) );
		v[ 0 ]._m = _mm_shuffle_ps( r1, r3, _MM_SHUFFLE( 2, 0, 2, 0 ) );
		v[ 1 ]._m = _mm_shuffle_ps( r1, r3, _MM_SHUFFLE( 3, 1, 3, 1 ) );
		v[ 2 ]._m = _mm_shuffle_ps( r2, r4, _MM_SHUFFLE( 2, 0, 2, 0 ) );
		v[ 3 ]._m = _mm_shuffle_ps( r2, r4, _MM_SHUFFLE( 3, 1, 3, 1 ) );
	}

	template<typename T>
	inline void transpose_matrix( vec4< T >& v0, vec4< T >& v1, vec4< T >& v2, vec4< T >& v3 ) {
		const __m128 r1 = _mm_shuffle_ps( v0._m, v1._m, _MM_SHUFFLE( 1, 0, 1, 0 ) );
		const __m128 r2 = _mm_shuffle_ps( v0._m, v1._m, _MM_SHUFFLE( 3, 2, 3, 2 ) );
		const __m128 r3 = _mm_shuffle_ps( v2._m, v3._m, _MM_SHUFFLE( 1, 0, 1, 0 ) );
		const __m128 r4 = _mm_shuffle_ps( v2._m, v3._m, _MM_SHUFFLE( 3, 2, 3, 2 ) );
		v0._m = _mm_shuffle_ps( r1, r3, _MM_SHUFFLE( 2, 0, 2, 0 ) );
		v1._m = _mm_shuffle_ps( r1, r3, _MM_SHUFFLE( 3, 1, 3, 1 ) );
		v2._m = _mm_shuffle_ps( r2, r4, _MM_SHUFFLE( 2, 0, 2, 0 ) );
		v3._m = _mm_shuffle_ps( r2, r4, _MM_SHUFFLE( 3, 1, 3, 1 ) );
	}

} // namespace ysl

#endif