//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h" 
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShaderRojo = "shaders/shader_rojo.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�
static const char* vShaderVerde = "shaders/shader_verde.vert";
static const char* vShaderAzul = "shaders/shader_azul.vert";
static const char* vShaderVerdeOsc = "shaders/shader_verdeosc.vert";
static const char* vShaderCafe = "shaders/shader_cafe.vert";


float angulo = 0.0f;
//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.25f, 0.0f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	// Letra M
	GLfloat vertices_m[] = {
		//X       Y          Z				 R       G       B
		//T1
		-0.7f,	0.05f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.6f,	0.05f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.7f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		//T2
		-0.6f,	0.05f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.7f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.6f,	0.75f,		0.0f,			0.480f,	0.446f,	0.697f,
		//T3
		-0.7f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.55f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.45f,	0.6f,		0.0f,			0.480f,	0.446f,	0.697f,
		//T4
		-0.55f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.45f,	0.6f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.45f,	0.73f,		0.0f,			0.480f,	0.446f,	0.697f,
		//T5
		-0.35f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.45f,	0.6f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.45f,	0.73f,		0.0f,			0.480f,	0.446f,	0.697f,
		//T6
		-0.45f,	0.6f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.35f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.2f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		//T7
		-0.2f,	0.05f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.3f,	0.75f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.2f,	0.85f,		0.0f,			0.480f,	0.446f,	0.697f,
		//T8
		-0.3f,	0.05f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.2f,	0.05f,		0.0f,			0.480f,	0.446f,	0.697f,
		-0.3f,	0.75f,		0.0f,			0.480f,	0.446f,	0.697f
	};
	MeshColor* letram = new MeshColor();
	letram->CreateMeshColor(vertices_m, 144);
	meshColorList.push_back(letram);

	// Letra V
	GLfloat vertices_v[] = {
		//X       Y          Z				 R       G       B
		//T1
		-0.2f,	-0.05f,		0.0f,			0.368f,	0.335f,	0.585f,
		-0.1f,	-0.05f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.0f,	-0.65f,		0.0f,			0.368f,	0.335f,	0.585f,
		//T2
		-0.2f,	-0.05f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.0f,	-0.65f,		0.0f,			0.368f,	0.335f,	0.585f,
		-0.05f,	-0.85f,		0.0f,			0.368f,	0.335f,	0.585f,
		//T3
		-0.05f,	-0.85f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.05f,	-0.85f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.0f,	-0.65f,		0.0f,			0.368f,	0.335f,	0.585f,
		//T4
		0.2f,	-0.05f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.0f,	-0.65f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.05f,	-0.85f,		0.0f,			0.368f,	0.335f,	0.585f,
		//T5
		0.2f,	-0.05f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.1f,	-0.05f,		0.0f,			0.368f,	0.335f,	0.585f,
		0.0f,	-0.65f,		0.0f,			0.368f,	0.335f,	0.585f
	};
	MeshColor* letrav = new MeshColor();
	letrav->CreateMeshColor(vertices_v, 90);
	meshColorList.push_back(letrav);

	//Letra G
	GLfloat vertices_g[] = {
		//X       Y          Z				 R       G       B
		//T1
		0.2f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.3f,	0.05f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.3f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T2
		0.2f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.3f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.3f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T3
		0.2f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.2f,	0.8f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.3f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T4
		0.2f,	0.8f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.3f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.25f,	0.85f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T5
		0.3f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.25f,	0.85f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T6
		0.25f,	0.85f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.55f,	0.85f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T7
		0.5f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.55f,	0.85f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.6f,	0.8f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T8
		0.5f,	0.75f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.6f,	0.8f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.65f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T9
		0.5f,	0.65f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.6f,	0.65f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.6f,	0.8f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T10
		0.3f,	0.05f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.3f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.05f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T11
		0.3f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.05f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T12
		0.5f,	0.4f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.6f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.05f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T13
		0.6f,	0.2f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.5f,	0.4f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.6f,	0.5f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T14
		0.5f,	0.4f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.6f,	0.5f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.4f,	0.5f,		0.0f,			0.492f,	0.357f,	0.509f,
		//T15
		0.5f,	0.4f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.4f,	0.5f,		0.0f,			0.492f,	0.357f,	0.509f,
		0.4f,	0.4f,		0.0f,			0.492f,	0.357f,	0.509f
	};

	MeshColor* letrag = new MeshColor();
	letrag->CreateMeshColor(vertices_g, 270);
	meshColorList.push_back(letrag);


}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para el color rojo
	shader1->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader para el color verde
	shader3->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader para el color azul
	shader4->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader para el color verde oscuro
	shader5->CreateFromFiles(vShaderVerdeOsc, fShader);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader(); //shader para el color caf�
	shader6->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(40.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.85f, 0.65f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		// Para las letras y figuras con color en el VAO
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		// Renderizar la letra M
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.2f, 0.6f, -4.0f)); // Ajustar la posici�n si es necesario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshColorList[0]->RenderMeshColor(); // �ndice 0 = Letra M

		// Renderiza la letra V
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.0f, 1.5f, -4.0f)); // Ajustar la posici�n si es necesario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshColorList[1]->RenderMeshColor(); // �ndice 1 = Letra V

		// Renderiza la letra G
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, 0.6f, -4.0f)); // Ajustar la posici�n si es necesario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshColorList[2]->RenderMeshColor(); // �ndice 2 = Letra G

		//Casa
		//Para el cubo rojo, se utiliza el primer set de shaders con �ndice 0 en ShaderList
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -3.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Puerta
		//Para el cubo verde, se utiliza el tercer set de shaders con �ndice 2 en ShaderList
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.633f, -2.6f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Ventana 1
		//Para el cubo verde, se utiliza el tercer set de shaders con �ndice 2 en ShaderList
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, -0.2f, -2.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		//Ventana 2
		//Para el cubo verde, se utiliza el tercer set de shaders con �ndice 2 en ShaderList
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, -0.2f, -2.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Techo
		//Para la piramide azul, se utiliza el cuarto set de shaders con �ndice 3 en ShaderList
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.14f, -1.0f));
		model = glm::scale(model, glm::vec3(0.45f, 0.25f, 0.45f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Pino 1
		//Para la piramide verde oscuro, se utiliza el quinto set de shaders con �ndice 4 en ShaderList
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.3f, -0.1f, -1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Pino 2
		//Para la piramide verde oscuro, se utiliza el quinto set de shaders con �ndice 4 en ShaderList
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.3f, -0.1f, -1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Tronco 1
		//Para el cubo caf�, se utiliza el sexto set de shaders con �ndice 5 en ShaderList
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.47f, -0.35f, -1.6f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Tronco 2
		//Para el cubo caf�, se utiliza el sexto set de shaders con �ndice 5 en ShaderList
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.47f, -0.35f, -1.6f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}
