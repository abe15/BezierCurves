#include "window.h"

const char* window_title = "GLFW Starter Project";
Cube * cube;
//OBJObject * obj;
//OBJObject * bunny;

GLint shaderProgram;
GLint skyboxShaderProgram, sphereShaderProgram,lineShaderProgram;
bool left_button_down = false;
bool right_button_down = false;
bool control = false;
glm::vec3 directionLight(1, 1, 1);
float t = 3.14 / 4;
float t2 = 3.14 / 4;
float t3 = 3.14 / 2;

bool clicked = false;
bool c = false;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat cameraSpeed = 0.1f;

GLfloat lastX, lastY;
GLfloat fov = 45.0f;
// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "../shader.vert"
#define FRAGMENT_SHADER_PATH "../shader.frag"

#define SPHERE_VERTEX_SHADER_PATH "../sphereShader.vert"
#define SPHERE_FRAGMENT_SHADER_PATH "../sphereShader.frag"
#define SKYBOX_VERTEX_SHADER_PATH "../skybox.vert"
#define SKYBOX_FRAGMENT_SHADER_PATH "../skybox.frag"
#define LINE_VERTEX_SHADER_PATH "../lineShader.vert"
#define  LINE_FRAGMENT_SHADER_PATH "../lineShader.frag"
int selectObject = 0;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
bool firstMouse = true;
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
glm::vec3 lastPoint(0.0f, 0.0f, 0.0f);
glm::vec3 currentPoint(0.0f, 0.0f, 0.0f);
Sphere *s;
//BComp* bez = new BComp();

inline float Lerp(float t, float a, float b)
{
	return (a + t * (b - a));
};
/////


const static GLfloat cubeVertices[] = {
	// Positions          // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


const static GLfloat skyboxVertices[] = {
	// Positions          
	-100.0f,  100.0f, -100.0f,
	-100.0f, -100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,
	100.0f,  100.0f, -100.0f,
	-100.0f,  100.0f, -100.0f,

	-100.0f, -100.0f,  100.0f,
	-100.0f, -100.0f, -100.0f,
	-100.0f,  100.0f, -100.0f,
	-100.0f,  100.0f, -100.0f,
	-100.0f,  100.0f,  100.0f,
	-100.0f, -100.0f,  100.0f,

	100.0f, -100.0f, -100.0f,
	100.0f, -100.0f,  100.0f,
	100.0f,  100.0f,  100.0f,
	100.0f,  100.0f,  100.0f,
	100.0f,  100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,

	-100.0f, -100.0f,  100.0f,
	-100.0f,  100.0f,  100.0f,
	100.0f,  100.0f,  100.0f,
	100.0f,  100.0f,  100.0f,
	100.0f, -100.0f,  100.0f,
	-100.0f, -100.0f,  100.0f,

	-100.0f,  100.0f, -100.0f,
	100.0f,  100.0f, -100.0f,
	100.0f,  100.0f,  100.0f,
	100.0f,  100.0f,  100.0f,
	-100.0f,  100.0f,  100.0f,
	-100.0f,  100.0f, -100.0f,

	-100.0f, -100.0f, -100.0f,
	-100.0f, -100.0f,  100.0f,
	100.0f, -100.0f, -100.0f,
	100.0f, -100.0f, -100.0f,
	-100.0f, -100.0f,  100.0f,
	100.0f, -100.0f,  100.0f
};

bool isPaused = true;
bool beginn = true;

GLuint cubeVAO, cubeVBO;


GLuint skyboxVAO, skyboxVBO;

GLuint cubeTexture;


int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;
GLuint cubemapTexture;
//BCurve *gBCurve0;
BComp* ber;
void Window::initialize_objects()
{
	//cube = new Cube();
	glm::vec3 v(0, 0, 0);
	//	bunny = new OBJObject("..\\bunny.obj");
	//bear = new OBJObject("..\\bear.obj");
	//dragon = new OBJObject("..\\dragon.obj");
	//obj = &(*bunny);
	std::vector<const GLchar*> faces;
	faces.push_back("..\\skybox\\right.jpg");
	faces.push_back("..\\skybox\\left.jpg");
	faces.push_back("..\\skybox\\top.jpg");
	faces.push_back("..\\skybox\\bottom.jpg");
	faces.push_back("..\\skybox\\back.jpg");
	faces.push_back("..\\skybox\\front.jpg");
	cubemapTexture = loadCubemap(faces);
	//cube = new Cube();
	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	skyboxShaderProgram = LoadShaders(SKYBOX_VERTEX_SHADER_PATH, SKYBOX_FRAGMENT_SHADER_PATH);
	sphereShaderProgram = LoadShaders(SPHERE_VERTEX_SHADER_PATH, SPHERE_FRAGMENT_SHADER_PATH);
	lineShaderProgram = LoadShaders(LINE_VERTEX_SHADER_PATH, LINE_FRAGMENT_SHADER_PATH);
	s = new Sphere();
	s->setShaderid(sphereShaderProgram);
	// Setup skybox VAO

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
	cubeTexture = loadTexture("..\\container.jpeg");
	ber = new BComp();
	


}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	//delete(cube);
	//delete(obj);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(skyboxShaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);
	lastX = width / 2;
	lastY = height / 2;

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		V = camera.GetViewMatrix();
		//V = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		P = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 100.0f);

	}
}

void Window::idle_callback(GLFWwindow* window)
{
	
}

int time1 = 0;
int count = 0;

void Window::display_callback(GLFWwindow* window)
{
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (beginn)
	{
		time1 = ber->getMax();
		beginn = false;
	}

	glfwPollEvents();
	
	Window::do_movement();
	
	glm::mat4 projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 m = glm::mat4(1.0f);

	glUseProgram(shaderProgram);
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	GLint j = glGetUniformLocation(shaderProgram, "code");
	GLint k = glGetUniformLocation(shaderProgram,"modelview");
	int code = 0;
	glPointSize(10.0);
	//glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i< ber->control_Points->size(); i++)
	{
		glUniform1f(j, code);
	//	glColor3f(code / 255.0, 0, 0);
		glVertex3f((*ber->control_Points)[i].x, (*ber->control_Points)[i].y, (*ber->control_Points)[i].z);
		code++;
	}
	glEnd();


	


	glUseProgram(lineShaderProgram);
	//glUniformMatrix4fv(glGetUniformLocation(lineShaderProgram, "model"), 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(lineShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(lineShaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniform3f(glGetUniformLocation(lineShaderProgram, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// draw line
//	std::vector<glm::vec3>  j = ber->drawingPoints;
	//int j = ber->drawingPoints->size();
	//glBindVertexArray(ber->VAO);		
	//glDrawElements(GL_TRIANGLES, j, GL_UNSIGNED_INT, NULL);
	glUniform4f(glGetUniformLocation(lineShaderProgram, "chooseColor"), 1, 0, 1, 1);
	ber->Draw();
	glUniform4f(glGetUniformLocation(lineShaderProgram, "chooseColor"), 0, 1, 1, 1);
	ber->Draw2();

	//glUseProgram(shaderProgram);
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &m[0][0]);
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);



	//ber->Draw3();
	glBindVertexArray(0);



	//draw sphere
	//glm::mat4 model = glm::mat4(1.0f);
	//glm::mat4 view = camera.GetViewMatrix();
	//glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	glUseProgram(sphereShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(sphereShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(sphereShaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniform3f(glGetUniformLocation(sphereShaderProgram, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

	// Cubes
	glm::vec3 v = ber->drawingPoints->at(time1);
	glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(v.x, v.y, v.z));
	s->draw(t);
	//glBindVertexArray(cubeVAO);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	if (count % 1 == 0 && !isPaused) {
	time1++;
	}
	if (time1 == ber->drawingPoints->size()) {
		time1 = 0;
	}
	//glUseProgram(lineShaderProgram);
	//glUniformMatrix4fv(glGetUniformLocation(lineShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	//glUniformMatrix4fv(glGetUniformLocation(lineShaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	//glUniform3f(glGetUniformLocation(lineShaderProgram, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);





	// Draw skybox first
	glDepthFunc(GL_LEQUAL); // Remember to turn depth writing off
	glUseProgram(skyboxShaderProgram);
//	glm::mat4 view = camera.GetViewMatrix();	// Remove any translation component of the view matrix
	//glm::mat4 projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 100.0f);

	//&Window::P[0][0]
	glUniformMatrix4fv(glGetUniformLocation(skyboxShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

	//glUniformMatrix4fv(projection, 1, GL_FALSE, &Window::P[0][0]);


	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxShaderProgram, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);	

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	//glDepthMask(GL_TRUE);
	
	count++;



	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		isPaused = !isPaused;

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		isPaused = true;
		time1 = ber->getMax();
			
	
	}
		

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
void Window::do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}


void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS)
		{
			left_button_down = true;
			double txpos, typos;
			glfwGetCursorPos(window, &txpos, &typos);

			lastPoint = Window::trackBallMapping(txpos, typos);
			if (checkClicked(txpos, typos))
			{
				clicked = true;

			}

			}
			else if (action == GLFW_RELEASE)
			{
				left_button_down = false;
				clicked = false;
			}

		}
	}


glm::vec3 Window::trackBallMapping(double x, double y)
{
	glm::vec3 v;
	float d;
	v.x = (2.0*x - Window::width) / Window::width;
	v.y = (2.0*y - Window::height) / Window::height;
	v.z = 0;
	d = glm::length(v);
	d = (d < 1.0) ? d : 1.0;
	v.z = sqrt(1.001 - d*d);
	glm::normalize(v);
	return v;


}

glm::vec3 Window::reverse(double x, double y) {

	glm::vec3 v((width*x + width) / width, height*(y + 1) / height, 0);
	return v;

}


void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);


}

void Window::scrollback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


bool Window::checkClicked(double x, double y)
{
	unsigned char res[4];
	GLint viewport[4];


	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
	int whichOne = (int)(res[0] * 255);


	return (res[0] == 0) ? (false) : (true);

}

GLuint Window::loadCubemap(std::vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image = 0;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
	}
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	//added from 
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Use clamp to edge to hide skybox edges:
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);



	SOIL_free_image_data(image);
	return textureID;
}

GLuint Window::loadTexture(GLchar* path)
{
	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}