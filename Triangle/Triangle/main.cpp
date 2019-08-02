//
//  main.cpp
//  Triangle
//
//  Created by mac on 2019/8/1.
//  Copyright © 2019 SSK. All rights reserved.
//

#include <stdio.h>

#include "GLShaderManager.h"

#include "GLTools.h"


#include <GLUT/GLUT.h>


//GLShaderManager *shaderManager;

//定义一个，着色管理器
GLShaderManager shaderManager;

//简单的批次容器，是GLTools的一个简单的容器类。
GLBatch triangleBatch;


// 绘制一个可以会动（方向键）的正方形
// 一边长的二分之一
GLfloat blockSize = 0.1f;

GLfloat vVerts[] = {
    -blockSize, -blockSize, 0.0f,
    blockSize, -blockSize, 0.0f,
    blockSize, blockSize, 0.0f,
    -blockSize, blockSize, 0.0f
};

// X & Y 每一步要移动的距离 (第二种方式)
GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;




// 窗口大小改变时调用，（init，update）是一个事件型函数，扩展：viewDidLoad是周期型函数
void changSize(int w, int h) {
    
    // x, y 代表窗口中左下角的坐标, 宽度，高度表示像素，通常x,y都为0（原点）
    glViewport(0, 0, w, h);
}

void renderScene() {
    
    
    // 1. 执行颜色缓冲区
    
    glClear(GL_COLOR_BUFFER_BIT/*颜色缓冲区*/ | GL_DEPTH_BUFFER_BIT/*深度缓冲区*/ | GL_STENCIL_BUFFER_BIT/*模板缓冲区*/);
    
    // 2. 指定渲染颜色
    GLfloat vGreen[] = {0.0f, 1.0f, 0.0f, 1.0f};
    
    
    // 第二种方式
    // 创建一个四行四列的矩阵
    // x, y, z, w(缩放因子 默认等于1.0)
    M3DMatrix44f mTransfromMatrix, mFinalTransfrom, mRotationMatix; //(存储结果)
    
    // 平移
    // 指针指向数组的时候可以不加取址符，普通变量需要
    // 因为数组名代表数组的首地址,是一个指针,所以不用加&符号。如果是引用数组内的元素,就必须得加&符
    m3dTranslationMatrix44(mTransfromMatrix, xPos, yPos, 0.0f);
    
    
    // |||
    // 带上旋转
    
    // 每次旋转5度
    static float ZRot = 0.0f;
   //ZRot += 0.5;
    
    // 1和0代表 yes or no
    m3dRotationMatrix44(mRotationMatix, m3dDegToRad(ZRot)/*f弧度*/, 0.0f, 0.0f, 1.0f);
    ZRot += 0.5;
    
    // 平移+旋转
    // 矩阵相乘
    m3dMatrixMultiply44(mFinalTransfrom, mTransfromMatrix, mRotationMatix);
    
    // 平面着色器
    // 一个矩阵，取代了第一种方法的顶点操作
    shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransfrom, vGreen);
    
    
//    // 使用固定管线 （单元着色器）
//    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
//
    // 开始绘制
    triangleBatch.Draw();


    glutSwapBuffers();
    
    
    // 垂直方向的一条直线，所有的点的X轴都相同，Y是变量 （变化的是高）
    // 水平方向的一条直线，所有的点的Y轴都相同，X是变量  (变化的是宽)
    
    
    
    // 3D数学  ==  线性代数
    
}


// 坐标系 -1 到 1
void specialKeys(int key, int x, int y) {
    
    
    // 第二种方式
    
    GLfloat stepSize = 0.025f;
    
    if (key == GLUT_KEY_UP) {
        printf("向上键\n");

        // 往上移
        yPos += stepSize;

    } else if (key == GLUT_KEY_LEFT) {
        printf("GLUT_KEY_LEFT\n");

        xPos -= stepSize;

    } else if (key == GLUT_KEY_DOWN) {
         printf("GLUT_KEY_DOWN\n");

        yPos -= stepSize;
    } else if (key == GLUT_KEY_RIGHT) {
        printf("GLUT_KEY_RIGHT\n");

        xPos += stepSize;
    }
    
    // 边界检测（碰撞）
    
    
    // 距离判断 （第一种方法用的坐标）
    
    // 四边留0.1的距离 其实并不精确？？ (此处有疑问，用的是距离，而不是坐标，最大的值是 0.9？)【关键在于矩阵函数的工作原理，待解决】
    
    // left
    if (xPos < -1.0f + blockSize) {
        xPos = -1.0f + blockSize;
        printf("left : %f \n", xPos);
    }
    
    // right
    if (xPos > 1.0f - blockSize) {
        xPos = 1.0f - blockSize;
    }
    
    // down
    if (yPos < -1.0f + blockSize) {
        yPos = -1.0f + blockSize;
    }
    
    // top
    if (yPos > 1.0f - blockSize) {
        yPos = 1.0f - blockSize;
    }
    
    // 重新绘制，不提交顶点，因为第二种方式不直接计算顶点，而使用矩阵  ---> call renderScene
    glutPostRedisplay();
    
//    // 第一种方法
//    GLfloat stepSize = 0.025f;
//
//    // D点
//    GLfloat blockX = vVerts[0];
//    GLfloat blockY = vVerts[10];
//
//
//
//    if (key == GLUT_KEY_UP) {
//        printf("向上键\n");
//
//        // 往上移
//        blockY += stepSize;
//
//    } else if (key == GLUT_KEY_LEFT) {
//        printf("GLUT_KEY_LEFT\n");
//
//        blockX -= stepSize;
//
//    } else if (key == GLUT_KEY_DOWN) {
//         printf("GLUT_KEY_DOWN\n");
//
//        blockY -= stepSize;
//    } else if (key == GLUT_KEY_RIGHT) {
//        printf("GLUT_KEY_RIGHT\n");
//
//        blockX += stepSize;
//    }
//
//    printf("%d \n", ((-1) - 1));
//    printf("%f \n", blockY);
//    printf("%f \n", blockY - blockSize * 2);
//
//
//    printf("------------\n");
//    printf("blockX + blockSize * 2  : ---> %f\n", blockX + blockSize * 2);
//    printf("------------\n");
//
//
//    // 边界检测
//
//    // 到了最左边
//    if (blockX < -1.0f) {
//        blockX = -1.0f;
//    }
//
//    // 右边的最大值减去水平方向的最大边长
//    if (blockX > 1.0f - blockSize * 2) {
//        blockX = 1.0f - blockSize * 2;
//    }
//
//
//    // 到了top
//    if (blockY > 1.0f) {
//        blockY = 1.0f;
//    }
//
//    // 最底部
//    if (blockY < -1.0f + blockSize * 2) {
//        blockY = -1.0f + blockSize * 2;
//        printf("最底部：%f", blockY);
//    }
//
//    /*
//
//     如果模型是一个飞机，顶点几百个......
//     // 转换矩阵
//     // 改变视界坐标系// 世界坐标系
//
//     让一个图片移动的方式：
//     1.移动图形
//     2.移动坐标系
//
//     // 游戏动的是场景，而不是人物
//
//     */
//
//
//
//    // 更新其它三个点
//
//    //A点
//    vVerts[0] = blockX;
//    vVerts[1] = blockY - blockSize * 2;
//
//    // B点
//    vVerts[3] = blockX + blockSize * 2;
//    vVerts[4] = blockY - blockSize * 2;
//
//    // C点
//    vVerts[6] = blockX + blockSize * 2;
//    vVerts[7] = blockY;
//
//    // D点
//    vVerts[9] = blockX;
//    vVerts[10] = blockY;
//
//
//    printf("所有Point 的X :\n");
//
//
//    for (int i = 0; i < 12; i += 3) {
//        printf("%f \n", vVerts[i]);
//    }
//
//
//    triangleBatch.CopyVertexData3f(vVerts);
//
//    // 提交绘制
//    // call renderScene
//    glutPostRedisplay();
    
    

    
    
    
}

//为程序作一次性的设置
void setupRC() {
    
    /*
     
     1.清屏（原因类似变量初始化）
     
     */
    // 设置背影颜色
    
    // 数据载入颜色缓冲区，但并没有执行
    glClearColor(0.98f, 0.40f, 0.7f, 1.0f);
    
    // 初始化着色器管理器
    shaderManager.InitializeStockShaders();
    
    
    // 设置顶点：x,y,z
    // 一维数组
    // z轴都为零时可以省略
//    GLfloat vVerts[] = {
//        -0.5f,0.0f,0.0f,
//        0.5f,0.0f,0.0f,
//        0.0f,0.5f,0.0f
//    };
    
    //将三角形改为四方形
//    GLfloat vVerts[] = {
//        -0.25f,0.0f,0.0f,
//        0.25f,0.0f,0.0f,
//        0.5f/*0.5*/,0.5f,0.0f,
//        -0.5f/*0.5*/,0.5f,0.0f
//
//    };
    
    // primitive: 用不同的模式来绘图
    // 参数：模式，顶点数
    //triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.Begin(GL_QUADS, 4); // //GL_TRIANGLE_FAN
    
    
    
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}


int main(int argc,char* argv[]) {
    
    printf("%s",argv[0]);
    
    // 设置工作目录
    gltSetWorkingDirectory(argv[0]);
    
    // 初始化glut
    glutInit(&argc, argv);
    
    // 设置 Display Mode
    glutInitDisplayMode(GLUT_RGBA);
    
    // 窗口大小
    glutInitWindowSize(800, 600);
    
    // 创建窗口
    glutCreateWindow("Triangle");
    
    
    
    
    // 注册函数
    
    // 重塑函数
    glutReshapeFunc(changSize);
    
    // 显示函数
    glutDisplayFunc(renderScene);
    
    // 特殊j键位
    glutSpecialFunc(specialKeys);
    
    /*
     初始化一个GLEW库,确保OpenGL API对程序完全可用。
     在试图做任何渲染之前，要检查确定驱动程序的初始化过程中没有任何问题
     */
    

    GLenum status = glewInit();
    if (GLEW_OK != status) {
        
        printf("GLEW Error:%s\n",glewGetErrorString(status));
        return 1;
        
    }
    
    // 设置渲染环境
    setupRC();
    
    // run loop , 注：其后的代码不能被执行
    glutMainLoop();
    
    return 0;
    
}
