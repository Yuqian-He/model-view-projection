# Overview
The goal for this peoject is implementing Model-View-Projection (MVP) matrix transformation technique to convert a 3D triangle with a user-defined position into its corresponding screen position, thereby enabling its display on the screen. 

# development environment

- build system generator: [CMake](https://cmake.org/)
- build system: [Ninja](https://ninja-build.org/)
- compiler: [GCC 12.2.0 aarch64-apple-darwin22](https://linux.die.net/man/1/gcc)
- Integrated Development Environment (IDE): [Visual Studio Code](https://code.visualstudio.com/) 
- C++ libraries:
  - C++ Standard Library
  - [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page)
  - [openCV2](https://opencv.org/)
- package manager: [vcpkg](https://github.com/Microsoft/vcpkg)
- version control system (VCS): [Git](https://git-scm.com/)

# Method 
## model/view transformation
Model transformation is transforming a 3D object in the local space to world space. There also include rotation because we should setup camera up at Y axis and look at -Z axis. We should impelement model/view transformation in both camera and object, in the code I just use translate matrix to translate them into original position (get_view_matrix). 

## projection transformation
There are two different projection : **perspective projection** & **othrographic projection**
![](assets/othro%26pres%20projection.png)
### othrographic projection
This projection is scaling object into canonical cube:
![](assets/othro%20projection.png)
I do it frist move the center to original point, and then scale it in 1 $/times$ 1 $/times$ 1 cube, here is the matrix:

$$
 M_{ortho} = 
  \begin{bmatrix}
  \frac{2}{r-1}&0&0&0\\
  0&\frac{2}{t-b}&0&0\\
  0&0&\frac{2}{n-f}&0\\
  0&0&0&1\\
  \end{bmatrix} 
  \begin{bmatrix}
  1&0&0&-\frac{r+1}{2}\\
  0&1&0&-\frac{t+b}{2}\\
  0&0&1&-\frac{n+f}{2}\\
  0&0&0&1\\
  \end{bmatrix} 
$$

### perspective projection
I do it first with perspective->othrographic matrix, there is the [calculation process](https://sites.cs.ucsb.edu/~lingqi/teaching/resources/GAMES101_Lecture_04.pdf)
After calculating perspective->othrographic matrix, multiply it with othrographic matrix.

$$
M_{persp} = M_{ortho}M_{persp->ortho}
$$

$$
M_{persp->ortho} = 
   \begin{bmatrix}
   n&0&0&0\\
   0&n&0&0\\
   0&0&n+f&-nf\\
   0&0&1&0\\
   \end{bmatrix}
$$

$$
 M_{ortho} = 
  \begin{bmatrix}
  \frac{2}{r-1}&0&0&0\\
  0&\frac{2}{t-b}&0&0\\
  0&0&\frac{2}{n-f}&0\\
  0&0&0&1\\
  \end{bmatrix} 
  \begin{bmatrix}
  1&0&0&-\frac{r+1}{2}\\
  0&1&0&-\frac{t+b}{2}\\
  0&0&1&-\frac{n+f}{2}\\
  0&0&0&1\\
  \end{bmatrix} 
$$

### rotate in any axis
![](assets/rotate%20in%20any%20axis.png)

# Result

