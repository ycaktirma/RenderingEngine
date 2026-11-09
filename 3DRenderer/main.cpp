#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"

"void main()\n"
"{FragColor = vec4(ourColor, 1.0);}\n";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
int main() {

	int major = 0, minor = 0, rev = 0;
	glfwGetVersion(&major, &minor, &rev);
	std::cout << glfwGetVersionString() << std::endl;
	std::cout << major << "/" << minor << "/" << rev << std::endl;

	int glfwSuccess = glfwInit();
	if (!glfwSuccess)
	{
		std::cout << "Failed to create glfw" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	float vertices[] = {
		 -0.7f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top
		 -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.9f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f// bottom left
	};

	float vertices2[] = {
		0,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top
		 0.2f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.2f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom left
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
	};

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int successVertexShader;
	char infoLogVertexShader[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertexShader);
	if (!successVertexShader) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertexShader);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertexShader << std::endl;
	}


	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	int successFragmentShader;
	char infoLogFragmentShader[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragmentShader);
	if (!successFragmentShader) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragmentShader);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragmentShader << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int successShaderProgram;
	char infoLogShaderProgram[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successShaderProgram);
	if (!successShaderProgram) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogShaderProgram);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLogShaderProgram<< std::endl;
	}
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//if (vertexColorLocation == -1) {
		//	std::cout << "Engine error: Uniform location can't be found." << std::endl;
		//}

		glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//std::cout << "GL error: " << glGetError() << std::endl;


		glfwSwapBuffers(window);
		glfwPollEvents();

		
	}
	glfwTerminate();
	return 0;
}