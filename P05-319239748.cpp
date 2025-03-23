/*
Práctica 5: Optimización y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Model Carroceria_Carro_M; 
Model Ventanas_Carro_M; 
Model Interior_Carro_M;  
Model Motor_Carro_M; 
Model Asientos_Carro_M; 
Model Aleron_Carro_M;  
Model Cofre_Carro_M; 
Model VidriosFarosDelanteros_Carro_M;
Model VidriosFarosTraseros_Carro_M;  
Model Suspension_Carro_M; 
Model Llanta1_Carro_M;
Model Rin1_Carro_M;
Model Llanta2_Carro_M;
Model Rin2_Carro_M;
Model Llanta3_Carro_M;
Model Rin3_Carro_M;
Model Llanta4_Carro_M;
Model Rin4_Carro_M;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	Carroceria_Carro_M = Model();
	Carroceria_Carro_M.LoadModel("Models/Carroceria_Carro.obj");

	Ventanas_Carro_M = Model();
	Ventanas_Carro_M.LoadModel("Models/Ventanas_Carro.obj");

	Interior_Carro_M = Model();
	Interior_Carro_M.LoadModel("Models/Interior_Carro.obj");

	Motor_Carro_M = Model();
	Motor_Carro_M.LoadModel("Models/Motor_Carro.obj");

	Asientos_Carro_M = Model();
	Asientos_Carro_M.LoadModel("Models/Asientos_Carro.obj");

	Aleron_Carro_M = Model();
	Aleron_Carro_M.LoadModel("Models/Aleron_Carro.obj");

	Cofre_Carro_M = Model();
	Cofre_Carro_M.LoadModel("Models/Cofre_Carro.obj");

	VidriosFarosDelanteros_Carro_M = Model();
	VidriosFarosDelanteros_Carro_M.LoadModel("Models/VidriosFarosDelanteros_Carro.obj");

	VidriosFarosTraseros_Carro_M = Model();
	VidriosFarosTraseros_Carro_M.LoadModel("Models/VidriosFarosTraseros_Carro.obj");

	Suspension_Carro_M = Model();
	Suspension_Carro_M.LoadModel("Models/Suspension_Carro.obj");

	Llanta1_Carro_M = Model();
	Llanta1_Carro_M.LoadModel("Models/Llanta1_Carro.obj");

	Rin1_Carro_M = Model();
	Rin1_Carro_M.LoadModel("Models/Rin1_Carro.obj");

	Llanta2_Carro_M = Model();
	Llanta2_Carro_M.LoadModel("Models/Llanta2_Carro.obj");

	Rin2_Carro_M = Model();
	Rin2_Carro_M.LoadModel("Models/Rin2_Carro.obj");

	Llanta3_Carro_M = Model();
	Llanta3_Carro_M.LoadModel("Models/Llanta3_Carro.obj");

	Rin3_Carro_M = Model();
	Rin3_Carro_M.LoadModel("Models/Rin3_Carro.obj");

	Llanta4_Carro_M = Model();
	Llanta4_Carro_M.LoadModel("Models/Llanta4_Carro.obj");

	Rin4_Carro_M = Model();
	Rin4_Carro_M.LoadModel("Models/Rin4_Carro.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();

		//------------*INICIA DIBUJO DE NUESTROS DEMÁS OBJETOS-------------------*
		//Cuerpo del carro (Carroceria)
		color = glm::vec3(0.5f, 0.45f, 0.5f); //modelo de goddard de color negro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.5f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getarticulacion6()));
		glm::mat4 modelCarro = model;
		model = modelCarro;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carroceria_Carro_M.RenderModel();

		model = modelCarro;
		//Ventanas del carro (Ventanas)
		color = glm::vec3(0.0f, 0.139f, 0.139f);
		model = glm::translate(model, glm::vec3(0.0f, 22.5f, 3.18f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ventanas_Carro_M.RenderModel();
		
		model = modelCarro;
		//Interior del carro (Interior)
		color = glm::vec3(0.85f, 0.85f, 0.85f);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 5.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Interior_Carro_M.RenderModel();

		model = modelCarro;
		//Motor del carro (Motor)
		color = glm::vec3(0.3f, 0.3f, 0.3f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Motor_Carro_M.RenderModel();

		model = modelCarro;
		//Asientos del carro (Asientos)
		color = glm::vec3(0.5f, 0.5f, 0.5f);
		model = glm::translate(model, glm::vec3(0.0f, 6.0f, -2.5f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Asientos_Carro_M.RenderModel();

		model = modelCarro;
		//Aleron del carro (Aleron)
		color = glm::vec3(0.25f, 0.25f, 0.25f);
		model = glm::translate(model, glm::vec3(0.0f, 22.0f, -56.5f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aleron_Carro_M.RenderModel();

		model = modelCarro;
		//Cofre del carro (Cofre)
		color = glm::vec3(0.4f, 0.35f, 0.4f);
		model = glm::translate(model, glm::vec3(1.0f, 22.07f, 29.485f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cofre_Carro_M.RenderModel();

		model = modelCarro;
		//Vidrios delanteros del carro (Faros Delanteros)
		color = glm::vec3(0.65f, 0.42f, 0.42f);
		model = glm::translate(model, glm::vec3(0.0f, 16.0f, 60.8f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VidriosFarosDelanteros_Carro_M.RenderModel();

		model = modelCarro;
		//Vidrios traseros del carro (Faros Traseros)
		color = glm::vec3(0.65f, 0.42f, 0.42f);
		model = glm::translate(model, glm::vec3(0.0f, 19.5f, -61.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VidriosFarosTraseros_Carro_M.RenderModel();

		model = modelCarro;
		//Suspension del carro (Suspension)
		color = glm::vec3(0.25f, 0.25f, 0.25f);
		model = glm::translate(model, glm::vec3(0.0f, 9.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Suspension_Carro_M.RenderModel();

		model = modelCarro;
		//Llanta del carro (Llanta 1)
		color = glm::vec3(0.45f, 0.45f, 0.45f);
		model = glm::translate(model, glm::vec3(28.8f, 8.05f, 41.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta1_Carro_M.RenderModel();

		model = modelaux;
		//Rin de la llanta (Rin 1)
		color = glm::vec3(0.45f, 0.35f, 0.45f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin1_Carro_M.RenderModel();

		model = modelCarro;
		//Llanta del carro (Llanta 2)
		color = glm::vec3(0.45f, 0.45f, 0.45f);
		model = glm::translate(model, glm::vec3(-28.0f, 8.05f, 41.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta2_Carro_M.RenderModel();

		model = modelaux;
		//Rin de la llanta (Rin 2)
		color = glm::vec3(0.45f, 0.35f, 0.45f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin2_Carro_M.RenderModel();

		model = modelCarro;
		//Llanta del carro (Llanta 3)
		color = glm::vec3(0.45f, 0.45f, 0.45f);
		model = glm::translate(model, glm::vec3(28.8f, 8.6f, -43.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta3_Carro_M.RenderModel();

		model = modelaux;
		//Rin de la llanta (Rin 3)
		color = glm::vec3(0.45f, 0.35f, 0.45f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin3_Carro_M.RenderModel();

		model = modelCarro;
		//Llanta del carro (Llanta 4)
		color = glm::vec3(0.45f, 0.45f, 0.45f);
		model = glm::translate(model, glm::vec3(-28.0f, 8.8f, -43.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta4_Carro_M.RenderModel();

		model = modelaux;
		//Rin de la llanta (Rin 4)
		color = glm::vec3(0.45f, 0.35f, 0.45f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rin4_Carro_M.RenderModel();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
