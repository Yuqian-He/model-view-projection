#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

//-----------------------------------translate camera position to original position -----------------------------------------------------
Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
	//initialize view
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity(); 

	//translate matrix, translate to original point
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

	//translate
    view = translate * view;

    return view;
}

//---------------------------------------------rotation based on z axis ----------------------------------------------------------------
Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
	//initial model matrix
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
	rotation_angle = rotation_angle / 180 * MY_PI;

	//rotation matrix
	Eigen::Matrix4f rotation;
	rotation << cos(rotation_angle), (-1)*sin(rotation_angle), 0, 0,
		sin(rotation_angle), cos(rotation_angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	model = model * rotation;

    return model;
}

//------------------------------------------persp->ortho matrix----------------------------------------------------
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // initial matrix
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f ortho = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f persp_ortho = Eigen::Matrix4f::Identity();

	//change to radian
	float halfEyeAngelRadian = eye_fov / 2 / 180.0 * MY_PI;

    float n = -1 * zNear;
    float f = -1 * zFar;
    float t = zNear * std::tan(halfEyeAngelRadian);// top / znear = tan(halfEyeAngelRadian)
    float r = t * aspect_ratio;// top / right = aspect_ration
    float l = (-1) * r;//
    float b = (-1) * t;//

	ortho << 2 / (r - l), 0, 0, 0,
        0, 2 / (t - b), 0, 0,
        0, 0, 2 / zNear - zFar, 0,
        0, 0, 0, 1;

	persp_ortho << n, 0, 0, 0,
        0, n, 0, 0,
        0, 0,n + f, -1 *  n * f,
        0, 0, 1, 0;

	projection = ortho * persp_ortho;

    return projection;
}

//rotation based on any axis
Eigen::Matrix4f get_rotation(Vector3f axis, float angle){


}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}