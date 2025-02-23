#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <cstdlib> // Para poder utilizar rand()
#include <ctime>   // Para srand(time(0))
#include <random> // Para generación de números aleatorios



//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO[3], VBO[3], shader;

//Variables para cambiar el color
float R, V, A; //Variables RGB
double tiempoA = 0.0; //Variable para almacenar el tiempo de cambio del color
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 1);

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.9f,0.7f,0.8f,1.0f);	 			\n\
}";


void inicializarColor() {
	R = static_cast<float>(dist(gen)); // Genera 0 o 1
	V = static_cast<float>(dist(gen));
	A = static_cast<float>(dist(gen));
}


void cambiarColor() {
	double tiempoS = glfwGetTime();
	if (tiempoS - tiempoA >= 2.0) { // Cambia cada 2 segundos
		float nuevoR, nuevoV, nuevoA;
		do {
			nuevoR = static_cast<float>(dist(gen));
			nuevoV = static_cast<float>(dist(gen));
			nuevoA = static_cast<float>(dist(gen));
		} while (nuevoR == R && nuevoV == V && nuevoA == A); // Gracias a esto, asegura que el color sea diferente

		R = nuevoR;
		V = nuevoV;
		A = nuevoA;

		tiempoA = tiempoS; // Guarda el tiempo actual como referencia para el próximo cambio de color
	}
}


//Funciones para crear las letras
void CrearLetras()
{
	//Vertices para M
	GLfloat vertices[] = {
		//T1
		-0.7f,0.05f,0.0f,
		-0.6f,0.05f,0.0f,
		-0.7f,0.85f,0.0f,

		// T2
		-0.6f,0.05f,0.0f,
		-0.7f,0.85f,0.0f,
		-0.6f,0.75f,0.0f,

		// T3
		-0.7f,0.85f,0.0f,
		-0.55f,0.85f,0.0f,
		-0.45f,0.6f,0.0f,

		// T4
		-0.55f,0.85f,0.0f,
		-0.45f,0.6f,0.0f,
		-0.45f,0.73f,0.0f,

		// T5
		-0.35f,0.85f,0.0f,
		-0.45f,0.6f,0.0f,
		-0.45f,0.73f,0.0f,

		// T6
		-0.45f,0.6f,0.0f,
		-0.35f,0.85f,0.0f,
		-0.2f,0.85f,0.0f,

		// T7
		-0.2f,0.05f,0.0f,
		-0.3f,0.75f,0.0f,
		-0.2f,0.85f,0.0f,

		// T8
		-0.3f,0.05f,0.0f,
		-0.2f,0.05f,0.0f,
		-0.3f,0.75f,0.0f

	};

	//vertices para la V
	GLfloat vertices_dos[] = {
		//T1
		-0.2f,-0.05f,0.0f,
		-0.1f,-0.05f,0.0f,
		0.0f,-0.65f,0.0f,

		//T2
		-0.2f,-0.05f,0.0f,
		0.0f,-0.65f,0.0f,
		-0.05f,-0.85f,0.0f,

		//T3
		-0.05f,-0.85f,0.0f,
		0.05f,-0.85f,0.0f,
		0.0f,-0.65f,0.0f,

		//T4
		0.2f,-0.05f,0.0f,
		0.0f,-0.65f,0.0f,
		0.05f,-0.85f,0.0f,

		//T5
		0.2f,-0.05f,0.0f,
		0.1f,-0.05f,0.0f,
		0.0f,-0.65f,0.0f
	};

	//Vertices para la G
	GLfloat vertices_tres[] = {
		//T1
		0.2f,0.2f,0.0f,
		0.3f,0.05f,0.0f,
		0.3f,0.2f,0.0f,

		//T2
		0.2f,0.2f,0.0f,
		0.3f,0.2f,0.0f,
		0.3f,0.75f,0.0f,

		//T3
		0.2f,0.2f,0.0f,
		0.2f,0.8f,0.0f,
		0.3f,0.75f,0.0f,

		//T4
		0.2f,0.8f,0.0f,
		0.3f,0.75f,0.0f,
		0.25f,0.85f,0.0f,

		//T5
		0.3f,0.75f,0.0f,
		0.25f,0.85f,0.0f,
		0.5f,0.75f,0.0f,

		//T6
		0.25f,0.85f,0.0f,
		0.5f,0.75f,0.0f,
		0.55f,0.85f,0.0f,

		//T7
		0.5f,0.75f,0.0f,
		0.55f,0.85f,0.0f,
		0.6f,0.8f,0.0f,

		//T8
		0.5f,0.75f,0.0f,
		0.6f,0.8f,0.0f,
		0.5f,0.65f,0.0f,

		//T9
		0.5f,0.65f,0.0f,
		0.6f,0.65f,0.0f,
		0.6f,0.8f,0.0f,

		//T10
		0.3f,0.05f,0.0f,
		0.3f,0.2f,0.0f,
		0.5f,0.05f,0.0f,

		//T11
		0.3f,0.2f,0.0f,
		0.5f,0.05f,0.0f,
		0.5f,0.2f,0.0f,

		//T12
		0.5f,0.4f,0.0f,
		0.6f,0.2f,0.0f,
		0.5f,0.05f,0.0f,

		//T13
		0.6f,0.2f,0.0f,
		0.5f,0.4f,0.0f,
		0.6f,0.5f,0.0f,

		//T14
		0.5f,0.4f,0.0f,
		0.6f,0.5f,0.0f,
		0.4f,0.5f,0.0f,

		//T15
		0.5f,0.4f,0.0f,
		0.4f,0.5f,0.0f,
		0.4f,0.4f,0.0f
	};

	glGenVertexArrays(3, VAO); //generar 1 VAO
	glGenBuffers(3, VBO);

	//configuración de la M
	glBindVertexArray(VAO[0]);//asignar VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);

	//configuración de la V
	glBindVertexArray(VAO[1]);//asignar VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_dos), vertices_dos, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);

	//configuración de la G
	glBindVertexArray(VAO[2]);//asignar VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tres), vertices_tres, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);

	//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader
{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader, 1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader = glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	//verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}
}
int main()
{
	//Llamar a la función para generar un fondo random
	inicializarColor();

	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

	//Crear tríangulo
	CrearLetras();
	CompileShaders();

	//Se debe de guardar el tiempo inicial
	tiempoA = glfwGetTime();

	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Cambia color cada cierto tiempo
		cambiarColor();

		//Recibir eventos del usuario
		glfwPollEvents();

		//Limpiar la ventana
		glClearColor(R, V, A, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		//Dibuja la M
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 24);

		//Dibuja la V
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 15);

		//Dibuja la G
		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 45);

		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}