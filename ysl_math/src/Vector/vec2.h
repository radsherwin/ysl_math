// #ifndef YSL_MATH_VEC2_H
// #define YSL_MATH_VEC2_H

//#include "Trig.h"
//#include "Util.h"
//#include "TypeCheck.h"
// #include <array>

// namespace ysl
// {
// class vec3;
// class vec4;

// class vec2
// {
// public:
//     vec2() : data{0.0f, 0.0f} {}
//     vec2(const vec2 &v) : data(v.data){}
//     vec2 &operator=(const vec2 &v)
//     {
//         if(this != &v)
//         {
//             data = v.data;
//         }

//         return *this;
//     }

//     ~vec2() = default;

//     explicit vec2(f32 x) : data{x, 0.0f} {}
//     explicit vec2(f32 x, f32 y) : data{x,y} {}

//     template<typename T>
//     inline vec2(T x) : data{static_cast<f32>(x), 0.0f} {}
//     template<typename T>
//     inline vec2(T x, T y) : data{static_cast<f32>(x), static_cast<f32>(y)} {}

//     inline f32 operator[](usize i) const { assert(i >= 0 && i < 3); return data[i]; }
//     inline f32 &operator[](usize i) { assert(i>=0 && i < 3); return data[i];}

//     inline f32 x() const {return data[0];}
//     inline f32 y() const {return data[1];}
//     inline f32 &x() {return data[0];}
//     inline f32 &y() {return data[1];}

//     inline void set(i32 i, f32 s) { assert(i>=0 && i < 3); data[i] = s;}
//     inline void set_x(f32 s) { data[0] = s; }
//     inline void set_y(f32 s) { data[1] = s; }

//     template<typename T>
//     inline void set(i32 i, T s) { assert(i>=0 && i < 3); data[i] = static_cast<f32>(s);}
//     template<typename T>
//     inline void set_x(T s) { data[0] = static_cast<f32>(s); }
//     template<typename T>
//     inline void set_y(T s) { data[1] = static_cast<f32>(s); }

//     // converter functions
//     vec4 to_vec4() const;
//     vec3 to_vec3() const;

// private:
//     std::array<f32, 2> data;
// }; // class vec2
// }// namespace ysl

// #endif  
