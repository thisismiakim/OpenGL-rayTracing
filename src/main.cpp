#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

/* include header files */
#include "Trace.h"
#include "RGB.h"
#include "Shader.h"
//#include "Draw.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// Global Variables
// window setting global variables
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;

Point intersect, tmp1, tmp2, cam, point, center[4]; // 3차원 좌표
RGB color, shade, obj[4]; // RGB 색상
Vec3 dir, normal, vec; // 3차원 벡터
Phong ps[4]; // phong shading
Sphere spheres[4]; // 구체 3차원
Ray ray, shadow; // 광선

float r, g, b, x, y, z, a[4], d[4], s[4], p[4]; // r,g,b, x, y, z  쉐이딩에 필요한 parms

// Image processing matrix
unsigned char image[SCREEN_HEIGHT][SCREEN_WIDTH][3];

// shader
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
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


// 구체 초기화
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

// 파일 읽기 함수
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


//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
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

						glClear(GL_COLOR_BUFFER_BIT);


						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

					}
				}
			}

		}
	}

	// Display image

	//glDrawPixels(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, image);

	// draw pixel..
	// 텍스쳐를 만들고 이를 사각형 폴리곤에 매핑하여 그리는 방식 사용
	// unsigned char image[SCREEN_HEIGHT][SCREEN_WIDTH][3];
	// image의 포지션 데이터는 여기..

	// 텍스처를 위한 메모리를 할당합니다.
	// GLuint texture;
	// glGenTextures(1, &texture);
	// glBindTexture(GL_TEXTURE_2D, texture);

	// // fill pixel
	// GLuint pixels[SCREEN_WIDTH * SCREEN_HEIGHT * 3];
	// for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 3; i += 3)
	// {

	// }

	glFlush();
}

// shader input

/* main loop */
int main()
{
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



    /* Initialise GLAD.*/
    // GLAD library manages function pointers for OpenGL, handling OS-specific quirks
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[ERROR] Failed to initialize GLAD" << std::endl;
        return -1;
    }



    /* Shader Program build and compile */
	// build and compile our shader program
    // ------------------------------------
    // vertex shader
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
    // fragment shader
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

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    /* Render Loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process user input
        processInput(window);

        // Render the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 컬러값 지정해서 넣기
        glClear(GL_COLOR_BUFFER_BIT);

        // ----------------------------------------------------------------------------
        // Drawing Functions here ...

        //display();
		// draw our first triangle
        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 3);


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

							// draw one pixel?
							// glUseProgram(shaderProgram);
							// glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
							// glDrawArrays(GL_TRIANGLES, 0, 3);
						}
					}
				}

			}
		}

		// Display image
		//glClear(GL_COLOR_BUFFER_BIT);
		//glDrawPixels(XDIM, YDIM, GL_RGB, GL_UNSIGNED_BYTE, image);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);





		glFlush();
		
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


// ----------- key event ----------------------
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