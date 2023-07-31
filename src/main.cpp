#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

/* Include header files */
#include "Trace.h"
#include "RGB.h"
#include "Shader.h"
//#include "Draw.h"

// ---------------------------------------------------------------------------

/* Function Prototypes */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void setSpheres();
void read();


// ---------------------------------------------------------------------------


/* Global Variables */
// window setting global variables
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;

// for drawing
Point intersect, tmp1, tmp2, cam, point, center[4]; // 3차원 좌표
RGB color, shade, obj[4]; // RGB 색상
Vec3 dir, normal, vec; // 3차원 벡터
Phong ps[4]; // phong shading
Sphere spheres[4]; // 구체 3차원
Ray ray, shadow; // 광선

float r, g, b, x, y, z, a[4], d[4], s[4], p[4]; // r,g,b, x, y, z  쉐이딩에 필요한 parms

// Image processing matrix
unsigned char image[SCREEN_HEIGHT][SCREEN_WIDTH][3];


/* Basic Shader source data*/
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
    "}\n\0";


// ----------------------------------------------------------------------------


/* main loop */
int main()
{
	// -----------------------------------------------------------------------

	/* GLFW Setting */
    // Initialise GLFW 
    glfwInit();

    // Setting Up OpenGL context version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MacOS option
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// -----------------------------------------------------------------------

    /* Create a window using GLFW */ 
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, 
                                          SCREEN_HEIGHT, 
                                          "RayTracing", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "[ERROR] Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }


    // Set the current context to the window
    glfwMakeContextCurrent(window);
    // Set callback function for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// -----------------------------------------------------------------------

    /* Initialise GLAD*/
    // GLAD library manages function pointers for OpenGL, handling OS-specific quirks
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[ERROR] Failed to initialize GLAD" << std::endl;
        return -1;
    }


	// -----------------------------------------------------------------------

    /* Shader Program build and compile */
	// build and compile our shader program

	// ------------------------------------
	// Copyright!!-------
    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	// ------------------------------------
    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

/// how to use phong shader !!!


	// ------------------------------------
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	// ------------------------------------

	// 위의 코드에서는 먼저 사각형의 4개의 꼭짓점을 정의하고, 
	//이를 이용해 2개의 삼각형을 그리기 위한 인덱스를 지정합니다.
	// 그 후에 VAO(Vertex Array Object), VBO(Vertex Buffer Object), EBO(Element Buffer Object)를 생성하고 초기화하며, 
	// 이를 통해 OpenGL에게 정점 데이터가 어떻게 구성되었는지 알려줍니다.
	// 마지막으로, 렌더링시 glDrawElements 함수를 사용하여 두 개의 삼각형을 그립니다. 이 함수는 EBO의 인덱스를 사용하여 정점을 그립니다.
    
	
	// 삼각형 버텍스 그리던 예시 함수
	// // Set up vertex data (and buffer(s)) and configure vertex attributes
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f, // left  
    //      0.5f, -0.5f, 0.0f, // right 
    //      0.0f,  0.5f, 0.0f  // top   
    // }; 

	// 사각형의 정점 데이터 (x, y)
    float vertices[] = {
        // positions       // texture coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
    };

	// 이 정점들로 구성된 두 개의 삼각형을 정의하는 인덱스
	unsigned int indices[] = {  
		0, 1, 3,  // 첫 번째 삼각형
		1, 2, 3   // 두 번째 삼각형
	}; 


	// VBO: Vertex Buffer Object
	// VAO: Vertex Array Object
	// EBO: Element Buffer Object
	// 버퍼와 배열 생성
    unsigned int VBO, VAO, EBO; 
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 먼저 Vertex Array Object를 바인딩하고, 그다음 버텍스 버퍼를 바인딩 및 설정하고, 그다음 버텍스 속성을 구성합니다.
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // 버텍스 배열 바인딩
	glBindVertexArray(VAO);

	// 정점 버퍼 바인딩 및 정점 데이터 복사
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 인덱스 버퍼 바인딩 및 인덱스 데이터 복사
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 버텍스 속성 포인터 설정
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



	// Create a Texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	



	// ------ 
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0); 


	// draw our first triangle
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	// draw spheres
	read(); // 파일에서 데이터 읽기

	setSpheres(); // 구체 설정

	for (int i = 0; i < SCREEN_HEIGHT; i++) // 이미지에 대한 각 픽셀을 순회하면서
	{
		for (int z = 0; z < SCREEN_WIDTH; z++)
		{
			bool intersected = false;
			for (int f = 0; f < 4; f++) // 레이트레이싱
			{
				point.set(z - SCREEN_WIDTH / 2, i - SCREEN_HEIGHT / 2, 0);
				ray.set(cam, point);

				if (spheres[f].sphereIntersect(ray, intersect, normal))
				{
					tmp1 = spheres[f].center;

					if (cam.dist(tmp1) > cam.dist(intersect) || intersected == false)
					{
						shadow.set(intersect, dir);
						ps[f].SetObject(obj[f], a[f], d[f], s[f], p[f]);

						for (int y = 0; y < 4; y++)
						{
							if (spheres[y].sphereIntersect(shadow, tmp2, vec) && y != f)
							{
								ps[f].SetObject(obj[f], a[f], 0, 0, p[f]);
							}
						}

						ps[f].GetShade(intersect, normal, shade);

						image[i][z][0] = shade.R;
						image[i][z][1] = shade.G;
						image[i][z][2] = shade.B;

						tmp1.set(intersect.px, intersect.py, intersect.pz);
						intersected = true;

						/* Basic Shader source data*/

						// 컬러를 넣어야할ㄷㅅ
						//fragmentShaderSource.Fragcolor =vec4(shade.R, shade.G, shade.B, 1.0f);


					}
				}
			}

		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	//delete[] image;

    /* Render Loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process user input
        processInput(window);

        // Render the screen
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Screen Color White
        glClear(GL_COLOR_BUFFER_BIT);

        // ----------------------------------------------------------------------------
        // Drawing Functions here ...

		// draw our first triangle
        // glUseProgram(shaderProgram);
		// glBindVertexArray(VAO);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glUseProgram(shaderProgram);
		// //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		// //glDrawArrays(GL_TRIANGLES, 0, 3);

		// // 이후 렌더링 시
		// glBindVertexArray(VAO);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// 삼각형 그리기 메소드를 통한.. 픽셀 드로잉


		glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // -------------------------------------------------------------------------------
        // Swap the buffers and poll I/O events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    // Clean up Shaders
	// optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
















// ---------------------------------
/* Key events */
// 사용자 입력 처리: GLFW가 해당 프레임에서 관련 키가 눌림/해제됐는지 쿼리하고 그에 따라 반응
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: 창의 크기가 변경될 때 (OS 또는 사용자 리사이즈에 의해) 이 콜백 함수 실행
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



// ----------------------------------------
/* set Spheres function */

void setSpheres()
{
	center[0].set(-100, -100, 200);
	center[1].set(50, -50, 100);
	center[2].set(-100, 100, 200); 
	center[3].set(50, 150, 0); 

	spheres[0].set(center[0], 90); 
	spheres[1].set(center[1], 100); 
	spheres[2].set(center[2], 100); 
	spheres[3].set(center[3], 70);
}



// ----------------------------------------

/* File read function */

void read()
{
	ifstream din;
	din.open("input.txt");

	string input;
	int num = 0;

	while (din >> input)
	{
		if (input == "Camera")
		{
			din >> x >> y >> z;
			cam.set(x, y, -8000);
			for (int i = 0; i < 4; i++)
			{
				ps[i].SetCamera(cam);
			}
		}
		else if (input == "Light")
		{
			din >> r >> g >> b >> x >> y >> z;
			color.set(r, b, g);
			dir.set(x, y, z);
			for (int i = 0; i < 4; i++)
			{
				ps[i].SetLight(color, dir);
			}
		}
		else if (input == "Object")
		{
			din >> r >> g >> b >> a[num] >> d[num] >> s[num] >> p[num];
			obj[num].set(r, g, b);
			num++;
		}

	}
}