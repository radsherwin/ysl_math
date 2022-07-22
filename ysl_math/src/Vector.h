#ifndef YSL_MATH_VECT_H
#define YSL_MATH_VECT_H

#include "Vector/vec2.h"
#include "Vector/vec3.h"
#include "Vector/vec4.h"

namespace ysl {
	/////////////////////
	//	typedefs
	////////////////////
	using fvec4 = vec4<f32>;
	using ivec4 = vec4<i32>;
	using dvec4 = vec4<f64>;
	using FVector = vec4<f32>;
	using FVector4 = vec4<f32>;
	using IVector4 = vec4<i32>;
	using DVector4 = vec4<f64>;
	using FVec4 = vec4<f32>;
	using IVec4 = vec4<i32>;
	using DVec4 = vec4<f64>;

	using fvec3 = vec3<f32>;
	using ivec3 = vec3<i32>;
	using dvec3 = vec3<f64>;
	using FVector3 = vec3<f32>;
	using IVector3 = vec3<i32>;
	using DVector3 = vec3<f64>;
	using FVec3 = vec3<f32>;
	using IVec3 = vec3<i32>;
	using DVec3 = vec3<f64>;

	/////////////////////
	//	constants
	////////////////////
	const vec4<f32> identity_fvec4 = vec4<f32>{ 0.0f,0.0f,0.0f,1.0f };
	const vec4<f32> zero_fvec4 = vec4<f32>{0.0f,0.0f,0.0f,0.0f };
	const vec4<i32> identity_ivec4 = vec4<i32>{0,0,0,1};
	const vec4<i32> zero_ivec4 = vec4<i32>{0,0,0,0};

	const vec3<f32> zero_fvec3 = vec3<f32>{ 0.0f,0.0f,0.0f };
	const vec3<i32> zero_ivec3 = vec3<i32>{ 0,0,0 };

	/////////////////////
	//	cross
	////////////////////
	template<typename T>
	vec2< T > cross( const vec2< T >& v1, const vec2< T >& v2 ) {
		return v1.cross( v2 );
	}

	template<typename T>
	vec3< T > cross( const vec3< T >& v1, const vec3< T >& v2 ) {
		return v1.cross( v2 );
	}

	template<typename T>
	vec4< T > cross( const vec4< T >& v1, const vec4< T >& v2 ) {
		return v1.cross( v2 );
	}

	/////////////////////
	//	dot
	////////////////////

	template<typename T>
	T dot( const vec2< T >& v1, const vec2< T >& v2 ) {
		return v1.dot( v2 );
	}

	template<typename T>
	T dot( const vec3< T >& v1, const vec3< T >& v2 ) {
		return v1.dot( v2 );
	}

	template<typename T>
	T dot( const vec4< T >& v1, const vec4< T >& v2 ) {
		return v1.dot( v2 );
	}

}

#endif