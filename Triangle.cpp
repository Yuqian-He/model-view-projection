//
// Created by LEI XU on 4/11/19.
//

#include "Triangle.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>

//对class Triangle的初始化和函数的定义
Triangle::Triangle()
{
    v[0] << 0, 0, 0;
    v[1] << 0, 0, 0;
    v[2] << 0, 0, 0;

    color[0] << 0.0, 0.0, 0.0;
    color[1] << 0.0, 0.0, 0.0;
    color[2] << 0.0, 0.0, 0.0;

    tex_coords[0] << 0.0, 0.0;
    tex_coords[1] << 0.0, 0.0;
    tex_coords[2] << 0.0, 0.0;
}

//函数setVertex的作用是将三角形的三个顶点坐标储存到v[3]中，注意，这里在rasterrizer.cpp中可看到用法，v[3]中保存的是经过视口变换后的坐标
void Triangle::setVertex(int ind, Eigen::Vector3f ver) { v[ind] = ver; }

//函数setNormal的作用是将法线保存到normal[3]中，此次实验并未用到这个函数
void Triangle::setNormal(int ind, Vector3f n) { normal[ind] = n; }

//函数setColor的作用是将画线的颜色信息，也就是RGB值保存到color[3]中
void Triangle::setColor(int ind, float r, float g, float b)
{
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) {
        throw std::runtime_error("Invalid color values");
    }

    color[ind] = Vector3f((float)r / 255., (float)g / 255., (float)b / 255.);
    return;
}

//函数setTexCoord的作用是设置画线的纹理，就是把线段类型保存到tex_coords[3]中，次实验并未用到这个函数，默认画的是直线
void Triangle::setTexCoord(int ind, float s, float t)
{
    tex_coords[ind] = Vector2f(s, t);
}

//函数toVector4的作用是把三维向量v[3]转换成四维的，多的那个元素用1补充
std::array<Vector4f, 3> Triangle::toVector4() const
{
    std::array<Vector4f, 3> res;
    std::transform(std::begin(v), std::end(v), res.begin(), [](auto& vec) {
        return Vector4f(vec.x(), vec.y(), vec.z(), 1.f);
    });
    return res;
}