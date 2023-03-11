//
// Created by goksu on 4/6/19.
//

#pragma once

#include "Triangle.hpp"
#include <algorithm>
#include <eigen3/Eigen/Eigen>
using namespace Eigen;
//此头文件用于创建rst命名空间，在这个命名空间里创建了所需的变量和类
namespace rst {
enum class Buffers
{
    Color = 1,
    Depth = 2
};

//内联函数重载|运算
inline Buffers operator|(Buffers a, Buffers b)
{
    return Buffers((int)a | (int)b);
}

//内联函数重载&运算
inline Buffers operator&(Buffers a, Buffers b)
{
    return Buffers((int)a & (int)b);
}
/*
关键字inline 必须与函数定义体放在一起才能使函数成为内联，仅将inline 放在函数声明前面不起任何作用。
内联函数直接将函数调用展开为函数体代码
函数调用是有代价的，会开辟栈空间，回收栈空间
内联函数没有这些代价，提高效率
*/

enum class Primitive
{
    //告诉后面的draw函数需要绘制的图形，目前只实现了三角形和直线
    Line,
    Triangle
};

/*
 * For the curious : The draw function takes two buffer id's as its arguments.
 * These two structs make sure that if you mix up with their orders, the
 * compiler won't compile it. Aka : Type safety
 * */

//做标记
struct pos_buf_id
{
    int pos_id = 0;
};

//做标记
struct ind_buf_id
{
    int ind_id = 0;
};

class rasterizer
{
  public:
    //构造函数 初始化frame_buf(像素数组)和depth_buf(深度数组)为w*h大小
    rasterizer(int w, int h);
    pos_buf_id load_positions(const std::vector<Eigen::Vector3f>& positions);
    ind_buf_id load_indices(const std::vector<Eigen::Vector3i>& indices);

    void set_model(const Eigen::Matrix4f& m);
    void set_view(const Eigen::Matrix4f& v);
    void set_projection(const Eigen::Matrix4f& p);

    void set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color);

    void clear(Buffers buff);

    void draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, Primitive type);

    //函数frame_buffer的作用是返回像素数组
    std::vector<Eigen::Vector3f>& frame_buffer() { return frame_buf; }

  private:
    void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);
    void rasterize_wireframe(const Triangle& t);

  private:
    Eigen::Matrix4f model;
    Eigen::Matrix4f view;
    Eigen::Matrix4f projection;

    std::map<int, std::vector<Eigen::Vector3f>> pos_buf;
    std::map<int, std::vector<Eigen::Vector3i>> ind_buf;

    std::vector<Eigen::Vector3f> frame_buf;
    std::vector<float> depth_buf;
    int get_index(int x, int y);

    int width, height;

    int next_id = 0;
    int get_next_id() { return next_id++; }
};
} // namespace rst