#ifndef YSL_MATH_MAT4_H
#define YSL_MATH_MAT4_H

#include <cassert>
#include <cstring>
#include <iostream>
#include "Vector.h"

namespace ysl {

	class mat4 {
	public:
		mat4()
			: data{ { {},{},{},{} } } {}
		mat4( const mat4& m )
			: data( m.data ) {}

		mat4& operator=( const mat4& m ) {
			if ( this != &m )
			{
				data = m.data;
			}

			return *this;
		}
		~mat4() = default;

		mat4( const fvec3& v1, const fvec3& v2, const fvec3& v3 ) {
			data[ 0 ] = v1.as_vec4();
			data[ 1 ] = v2.as_vec4();
			data[ 2 ] = v3.as_vec4();
			data[ 3 ] = ysl::identity_fvec4;
		}
		mat4( const fvec4& v1, const fvec4& v2, const fvec4& v3 ) {
			data[ 0 ] = v1;
			data[ 1 ] = v2;
			data[ 2 ] = v3;
			data[ 3 ] = ysl::identity_fvec4;
		}

		mat4( const fvec4& v1, const fvec4& v2, const fvec4& v3, const fvec4& v4 ) {
			data[ 0 ] = v1;
			data[ 1 ] = v2;
			data[ 2 ] = v3;
			data[ 3 ] = v4;
		}

		mat4( f32 f ) {
			for ( i32 i = 0; i < 4; ++i )
			{
				data[ i ].set( f );
			}
		}

		static mat4 identity() {
			mat4 m{};
			m.data[ 0 ].set_x( 1 );
			m.data[ 1 ].set_y( 1 );
			m.data[ 2 ].set_z( 1 );
			m.data[ 3 ].set_w( 1 );

			return m;
		}

		static mat4 translation() {
			mat4 m{};
			m.data[ 0 ].set_x( 1 );
			m.data[ 1 ].set_y( 1 );
			m.data[ 2 ].set_z( 1 );
			m.data[ 3 ].set_w( 1 );

			return m;
		}

		static mat4 translation( const fvec4& v ) {
			mat4 m{};
			m.data[ 0 ].set_x( 1 );
			m.data[ 1 ].set_y( 1 );
			m.data[ 2 ].set_z( 1 );
			m.data[ 3 ] = v;
			m.data[ 3 ].set_w( 1 );
			return m;
		}

		static mat4 translation( f32 x, f32 y, f32 z ) {
			mat4 m{};
			m.data[ 0 ].set_x( 1 );
			m.data[ 1 ].set_y( 1 );
			m.data[ 2 ].set_z( 1 );
			m.data[ 3 ] = fvec4{ x,y,z, 1 };
			return m;
		}

		static mat4 scale( f32 x, f32 y, f32 z ) {
			mat4 m{};
			m.data[ 0 ].set_x( x );
			m.data[ 1 ].set_y( y );
			m.data[ 2 ].set_z( z );
			m.data[ 3 ].set_w( 1 );

			return m;
		}

		static mat4 scale( f32 s ) {
			mat4 m{};
			m.data[ 0 ].set_x( s );
			m.data[ 1 ].set_y( s );
			m.data[ 2 ].set_z( s );
			m.data[ 3 ].set_w( 1 );

			return m;
		}

		static mat4 axis_angle( const fvec4& axis, f32 angle ) {
			// replace this with quaternions
			const f32 angle_a = 0.5f * angle;
			const f32 cos_a = ysl::cos( angle_a );
			const f32 sin_a = ysl::sin( angle_a );
			fvec4 q_vec = axis.get_norm();

			const f32 qx = q_vec.x();
			const f32 qy = q_vec.y();
			const f32 qz = q_vec.z();
			const f32 qw = cos_a;

			const f32 x2 = qx + qx;
			const f32 y2 = qy + qy;
			const f32 z2 = qz + qz;

			const f32 xx = qx * x2;
			const f32 xy = qx * y2;
			const f32 xz = qx * z2;

			const f32 yy = qy * y2;
			const f32 yz = qy * z2;
			const f32 zz = qz * z2;

			const f32 wx = qw * x2;
			const f32 wy = qw * y2;
			const f32 wz = qw * z2;

			return mat4{ fvec4{1.0f - ( yy + zz ), xy + wz, xz - wy, 0.0f},
						 fvec4{xy - wz, 1.0f - ( xx + zz ), yz + wx, 0.0f},
						 fvec4{xz + wy, yz - wx, 1.0f - ( xx + yy ), 0.0f},
						 fvec4{0,0,0,1.0f} };
		}

		static mat4 rot_x( f32 f ) {
			return mat4{ fvec4{1, 0, 0, 0},
						 fvec4{ 0, ysl::cos( f ), ysl::sin( f ), 0},
						 fvec4{ 0, -ysl::sin( f ), ysl::cos( f ), 0},
						 fvec4{0,0,0,1} };
		}

		static mat4 rot_y( f32 f ) {
			return mat4{ fvec4{ysl::cos( f ), 0, -ysl::sin( f ), 0},
						 fvec4{ 0, 1, 0, 0},
						 fvec4{ ysl::sin( f ), 0, ysl::cos( f ), 0},
						 fvec4{0,0,0,1} };
		}

		static mat4 rot_z( f32 f ) {
			return mat4{ fvec4{ysl::cos( f ), ysl::sin( f ), 0, 0},
						 fvec4{ -ysl::sin( f ), ysl::cos( f ), 0, 0},
						 fvec4{ 0, 0, 1, 0},
						 fvec4{0,0,0,1} };
		}

		// returns ROW at idx
		fvec4& operator[] ( const usize& idx ) {
			assert( idx >= 0 && idx < 4 );
			return data[ idx ];
		}

		fvec4 operator[] ( const usize& idx ) const {
			assert( idx >= 0 && idx < 4 );
			return data[ idx ];
		}

		mat4 operator*( const mat4& rhs ) const {
			mat4 m_tmp;

			for ( usize i = 0; i < 4; ++i )
			{
				for ( usize j = 0; j < 4; ++j )
				{
					m_tmp[ i ].set( j, ysl::dot( data[ i ], rhs.col( j ) ) );
				}
			}

			return m_tmp;
		}

		fvec4 col( const usize& idx ) const {
			assert( idx >= 0 && idx < 4 );
			fvec4 res;
			for ( i32 i = 0; i < 4; ++i )
			{
				res.set( i, data[ i ][ idx ] );
			}

			return res;
		}

		void transpose() {
			ysl::transpose_matrix( data[ 0 ], data[ 1 ], data[ 2 ], data[ 3 ] );
		}

		mat4 get_transpose() const {
			return mat4{ col( 0 ), col( 1 ), col( 2 ), col( 3 ) };
		}

		fvec4 get_translation4() const {
			// return translation vector of size 4
			return fvec4{ data[ 3 ] };
		}

		fvec3 get_translation3() const {
			return fvec3{ data[ 3 ][ 0 ], data[ 3 ][ 1 ], data[ 3 ][ 2 ] };
		}

		mat4 get_translation_m() const {
			return mat4::translation( data[ 3 ] );
		}

		mat4 get_inv_translation_m() const {
			return mat4::translation( data[ 3 ].flip_sign() );
		}

		mat4 get_rotation_m() const {
			// row 0 = side vector
			// row 1 = up vector
			// row 2 = forward vector
			// row 3 = translation vector
			// normalize because we don't want scale
			return mat4( data[ 0 ].get_norm(), data[ 1 ].get_norm(), data[ 2 ].get_norm() );
		}

		fvec3 get_scale() const {
			// returns vec3(sideScale, upScale, forwardScale)
			return fvec3( data[ 0 ].mag(), data[ 1 ].mag(), data[ 2 ].mag() );
		}

		mat4 get_scale_m() const {
			return mat4::scale( data[ 0 ].mag(), data[ 1 ].mag(), data[ 2 ].mag() );
		}

		mat4 get_inv_scale_m() const {
			return mat4::scale( 1 / data[ 0 ].mag(), 1 / data[ 0 ].mag(), 1 / data[ 0 ].mag() );
		}

		void set_identity() {
			data[ 0 ].set_x( 1.0f );
			data[ 1 ].set_y( 1.0f );
			data[ 2 ].set_z( 1.0f );
			data[ 3 ].set_w( 1.0f );
		}

		void set_translation( const fvec4& v ) {
			data[ 3 ] = v;
		}

		void set_translation( f32 x, f32 y, f32 z ) {
			data[ 3 ] = fvec4{ x,y,z,1.0f };
		}

		void set_translation( const fvec3& v ) {
			data[ 3 ] = v.as_point4();
		}

		void set_scale( f32 f ) {
			data[ 0 ].set_x( f );
			data[ 1 ].set_y( f );
			data[ 2 ].set_z( f );
			data[ 3 ].set_w( 1.0f );
		}

		void set_scale( f32 x, f32 y, f32 z ) {
			data[ 0 ].set_x( x );
			data[ 1 ].set_y( y );
			data[ 2 ].set_z( z );
			data[ 3 ].set_w( 1.0f );
		}

		void set_scale_x( f32 f ) {
			data[ 0 ] *= ysl::fvec4{ f,1,1,1 };
		}

		void set_scale_y( f32 f ) {
			data[ 1 ] *= ysl::fvec4{ 1,f,1,1 };
		}

		void set_scale_z( f32 f ) {
			data[ 2 ] *= ysl::fvec4{ 1,1,f,1 };
		}

		void inv() {
			// normal = SRT
			// inverser = iTiRiS
			const mat4 r = get_rotation_m().get_transpose();
			const mat4 s = get_inv_scale_m();
			const mat4 t = get_inv_translation_m();

			*this = t * r * s;

		}

		mat4 get_inv() const {
			const mat4 r = get_rotation_m().get_transpose();
			const mat4 s = get_inv_scale_m();
			const mat4 t = get_inv_translation_m();

			mat4 m{};
			m = t * r * s;

			return m;
		}

		void print() const {
			for ( usize i = 0; i < 4; ++i )
			{
				data[ i ].print();
			}
		}

		friend fvec4 operator*( const fvec4& lhs, const mat4& rhs );
		//friend vec<4> operator*=(const vec<4> &lhs, const mat4 &rhs);

	private:
		std::array<fvec4, 4> data;
	};

	inline fvec4 operator *( const fvec4& lhs, const mat4& rhs ) {
		fvec4 res;
		for ( i32 i = 0; i < 4; ++i )
		{
			res.set( i, dot( lhs, rhs.col( i ) ) );
		}

		return res;
	}

	inline fvec3 operator *( const fvec3& lhs, const mat4& rhs ) {
		fvec4 res;
		fvec4 lhs2 = lhs.as_point4();
		for ( i32 i = 0; i < 4; ++i )
		{
			res.set( i, dot( lhs2, rhs.col( i ) ) );
		}
		res.set_w( 0 );
		return res.as_vec3();
	}

	inline fvec3 operator *=( fvec3& lhs, const mat4& rhs ) {
		fvec4 res;
		fvec4 lhs2 = lhs.as_point4();
		for ( i32 i = 0; i < 4; ++i )
		{
			res.set( i, dot( lhs2, rhs.col( i ) ) );
		}
		res.set_w( 0 );
		lhs = res.as_vec3();
		return lhs;
	}

} // namespace

#endif //YSL_MATH__MAT_H_