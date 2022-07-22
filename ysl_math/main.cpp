#include "src/Vector.h"
#include "src/Matrix.h"

int main() {
	ysl::fvec3 x{ 1, 2, 4 };
	ysl::fvec3 y{ 1, 2, 4 };

	ysl::fvec3 z = ysl::cross( x, y );

	ysl::mat4 b = ysl::mat4::rot_x( 3.5f );

	b.print();
	return 0;
}