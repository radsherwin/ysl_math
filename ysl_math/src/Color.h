#ifndef YSL_MATH_COLOR_H
#define YSL_MATH_COLOR_H

#include "Vector.h"

namespace ysl {
	namespace color {
		const fvec3 red			{ 1.0f, 0.0f, 0.0f };
		const fvec3 green		{ 0.0f, 1.0f, 0.0f };
		const fvec3 blue		{ 0.0f, 0.0f, 1.0f };
		const fvec3 purple		{ 0.6f, 0.2f, 0.9f };
		const fvec3 light_purple{ 0.9f, 0.8f, 1.0f };
		const fvec3 dark_orange	{ 0.8f, 0.4f, 0.0f };
		const fvec3 orange		{ 1.0f, 0.6f, 0.0f };
		const fvec3 pink		{ 1.0f, 0.6f, 0.7f };
		const fvec3 hot_pink	{ 1.0f, 0.5f, 1.0f };
		const fvec3 salmon		{ 1.0f, 0.6f, 0.5f };
		const fvec3 gold		{ 1.0f, 0.8f, 0.0f };
		const fvec3 yellow		{ 1.0f, 0.9f, 0.0f };
		const fvec3 white		{ 1.0f, 1.0f, 1.0f };
		const fvec3 black		{ 0.0f, 0.0f, 0.0f };
		const fvec3 gray		{ 0.6f, 0.6f, 0.6f };
		const fvec3 dark_gray	{ 0.2f, 0.2f, 0.2f };
	}

	namespace color_rgba {
		const fvec4 red			{ 1.0f, 0.0f, 0.0f, 1.0f };
		const fvec4 green		{ 0.0f, 1.0f, 0.0f, 1.0f };
		const fvec4 blue		{ 0.0f, 0.0f, 1.0f, 1.0f };
		const fvec4 purple		{ 0.6f, 0.2f, 0.9f, 1.0f };
		const fvec4 light_purple{ 0.9f, 0.8f, 1.0f, 1.0f };
		const fvec4 dark_orange	{ 0.8f, 0.4f, 0.0f, 1.0f };
		const fvec4 orange		{ 1.0f, 0.6f, 0.0f, 1.0f };
		const fvec4 pink		{ 1.0f, 0.6f, 0.7f, 1.0f };
		const fvec4 hot_pink	{ 1.0f, 0.5f, 1.0f, 1.0f };
		const fvec4 salmon		{ 1.0f, 0.6f, 0.5f, 1.0f };
		const fvec4 gold		{ 1.0f, 0.8f, 0.0f, 1.0f };
		const fvec4 yellow		{ 1.0f, 0.9f, 0.0f, 1.0f };
		const fvec4 white		{ 1.0f, 1.0f, 1.0f, 1.0f };
		const fvec4 black		{ 0.0f, 0.0f, 0.0f, 1.0f };
		const fvec4 gray		{ 0.6f, 0.6f, 0.6f, 1.0f };
		const fvec4 dark_gray	{ 0.2f, 0.2f, 0.2f, 1.0f };
	}
}

#endif