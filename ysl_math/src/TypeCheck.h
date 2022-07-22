#ifndef YSL_MATH_TYPE_CHECK_H
#define YSL_MATH_TYPE_CHECK_H

#include "types.h"

namespace ysl {
	///////////////////////
	// u8
	template<typename T>
	struct is_u8 { static constexpr bool value = false; };

	template<>
	struct is_u8<u8> { static constexpr bool value = true; };

	///////////////////////
	// u16
	template<typename T>
	struct is_u16 { static constexpr bool value = false; };

	template<>
	struct is_u16<u16> { static constexpr bool value = true; };

	///////////////////////
	// u32
	template<typename T>
	struct is_u32 { static constexpr bool value = false; };

	template<>
	struct is_u32<u32> { static constexpr bool value = true; };

	///////////////////////
	// u64
	template<typename T>
	struct is_u64 { static constexpr bool value = false; };

	template<>
	struct is_u64<u64> { static constexpr bool value = true; };

	///////////////////////
	// i8
	template<typename T>
	struct is_i8 { static constexpr bool value = false; };

	template<>
	struct is_i8<i8> { static constexpr bool value = true; };

	///////////////////////
	// i16
	template<typename T>
	struct is_i16 { static constexpr bool value = false; };

	template<>
	struct is_i16<i16> { static constexpr bool value = true; };

	///////////////////////
	// i32
	template<typename T>
	struct is_i32 { static constexpr bool value = false; };

	template<>
	struct is_i32<i32> { static constexpr bool value = true; };

	///////////////////////
	// i64
	template<typename T>
	struct is_i64 { static constexpr bool value = false; };

	template<>
	struct is_i64<i64> { static constexpr bool value = true; };

	///////////////////////
	// f32
	template<typename T>
	struct is_f32 { static constexpr bool value = false; };

	template<>
	struct is_f32<f32> { static constexpr bool value = true; };

	///////////////////////
	// f64
	template<typename T>
	struct is_f64 { static constexpr bool value = false; };

	template<>
	struct is_f64<f64> { static constexpr bool value = true; };

	///////////////////////
	// usize
	template<typename T>
	struct is_usize { static constexpr bool value = false; };

	template<>
	struct is_usize<usize> { static constexpr bool value = true; };

	///////////////////////
	// template compare
	template<typename T, typename G>
	struct is_typename_match { static constexpr bool value = false; };

	template<typename G>
	struct is_typename_match<u8, G> { static constexpr bool value = is_u8<G>::value; };

	template<typename G>
	struct is_typename_match<u16, G> { static constexpr bool value = is_u16<G>::value; };

	template<typename G>
	struct is_typename_match<u32, G> { static constexpr bool value = is_u32<G>::value; };

	template<typename G>
	struct is_typename_match<u64, G> { static constexpr bool value = is_u64<G>::value; };

	template<typename G>
	struct is_typename_match<i8, G> { static constexpr bool value = is_i8<G>::value; };

	template<typename G>
	struct is_typename_match<i16, G> { static constexpr bool value = is_i16<G>::value; };

	template<typename G>
	struct is_typename_match<i32, G> { static constexpr bool value = is_i32<G>::value; };

	template<typename G>
	struct is_typename_match<i64, G> { static constexpr bool value = is_i64<G>::value; };

	template<typename G>
	struct is_typename_match<f32, G> { static constexpr bool value = is_f32<G>::value; };

	template<typename G>
	struct is_typename_match<f64, G> { static constexpr bool value = is_f64<G>::value; };


}

#endif