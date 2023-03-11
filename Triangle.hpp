//
// Created by LEI XU on 4/11/19.
//

#ifndef RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

#include <eigen3/Eigen/Eigen>

using namespace Eigen;

//作用：存储形成三角形的点的信息，包括位置和颜色
class Triangle
{
  public:
    Vector3f v[3]; /*the original coordinates of the triangle, v0, v1, v2 in
                      counter clockwise order 用来存储三角形的顶点*/
    /*Per vertex values*/
    Vector3f color[3];      // color at each vertex存储三角形的顶点颜色;
    Vector2f tex_coords[3]; // texture u,v 存储顶点材质坐标
    Vector3f normal[3];     // normal vector for each vertex 存储每个顶点的法向量

    // Texture *tex;
    Triangle();
    //分别返回三角形的顶点向量坐标
    Eigen::Vector3f a() const { return v[0]; }
    Eigen::Vector3f b() const { return v[1]; }
    Eigen::Vector3f c() const { return v[2]; }

    //函数setVertex的作用是将三角形的三个顶点坐标储存到v[3]中，注意，这里在rasterrizer.cpp中可看到用法，v[3]中保存的是经过视口变换后的坐标
    void setVertex(int ind, Vector3f ver); /*set i-th vertex coordinates */
    //函数setNormal的作用是将法线保存到normal[3]中，此次实验并未用到这个函数
    void setNormal(int ind, Vector3f n);   /*set i-th vertex normal vector*/
    //函数setColor的作用是将画线的颜色信息，也就是RGB值保存到color[3]中
    void setColor(int ind, float r, float g, float b); /*set i-th vertex color*/
    //函数setTexCoord的作用是设置画线的纹理，就是把线段类型保存到tex_coords[3]中，次实验并未用到这个函数，默认画的是直线
    void setTexCoord(int ind, float s, float t); /*set i-th vertex texture coordinate*/

    //函数toVector4的作用是把三维向量v[3]转换成四维的，多的那个元素用1补充
    std::array<Vector4f, 3> toVector4() const;
};

#endif // RASTERIZER_TRIANGLE_H