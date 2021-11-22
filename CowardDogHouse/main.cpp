/*
###############################################
    ALUMNO: CRUZ GALVAN ALBERTO ISRAEL
    GRUPO: 12
    PROYECTO FINAL 
    FECHA DE ENTREGA: 21-11-21
###############################################
*/
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
//Permite cargar modelos
#include "SOIL2/SOIL2.h"
//Permite cargar texturas
#include "stb_image.h"
// Properties
const GLuint WIDTH = 1080, HEIGHT = 800;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function protacionotypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//************************V A R I A B L E S
//rotacion, rotacion 2 y rotacion 3 es para cajones
float rotacion = 0.0f, rotacion2 = 0.0f, rotacionAspas = 0.0f;

//para murcielagos
float bat1 = 0.0f, linnear_bat_izq=0.0f, linnear_bat_der=0.0f;
bool cambio_sentido_bat = false;
//-------------------------------------

bool bandera_de_reinicio = false;
bool cambio_sentido = false;
bool activacion = false;
//Para monitor
int j = 0;
int n = 0;
//************************V A R I A B L E S


int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Coward dog house by ALBERTO CRUZ 313291388", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    Shader lampshader("Shaders/lamp.vs", "Shaders/lamp.frag");




    // -------------------------------------------------------------------------------L O A D                  M O D E LS
    Model casa((char*)"Models/Casa/casa.obj");
    Model pokeabajo((char*)"Models/Pokeball/poke_abajo.obj");
    Model Cajon1((char*)"Models/Cajon1/Cajon1.obj");
    Model Cajon2((char*)"Models/Cajon2/Cajon2.obj");
    Model Cajon3((char*)"Models/Cajon3/Cajon3.obj");
    Model Aspas((char*)"Models/Aspas/Aspas.obj");
    //Murcielago
    Model Murcielago1((char*)"Models/Murcielago1/Murcielago1.obj");
    Model Murcielago2((char*)"Models/Murcielago2/Murcielago2.obj");
    Model Murcielago3((char*)"Models/Murcielago3/Murcielago3.obj");
    Model Murcielago4((char*)"Models/Murcielago4/Murcielago4.obj");
    Model Murcielago5((char*)"Models/Murcielago5/Murcielago5.obj");
    Model Murcielago6((char*)"Models/Murcielago6/Murcielago6.obj");
    Model Murcielago7((char*)"Models/Murcielago7/Murcielago7.obj");
    Model Murcielago8((char*)"Models/Murcielago8/Murcielago8.obj");
    Model Murcielago9((char*)"Models/Murcielago9/Murcielago9.obj");
    Model Murcielago10((char*)"Models/Murcielago10/Murcielago10.obj");
    Model Murcielago11((char*)"Models/Murcielago11/Murcielago11.obj");
    //Fantasma
    Model Fantasma1((char*)"Models/Fantasma1/Fantasma1.obj");
    Model Fantasma2((char*)"Models/Fantasma2/Fantasma2.obj");
    Model Fantasma3((char*)"Models/Fantasma3/Fantasma3.obj");
    Model Fantasma4((char*)"Models/Fantasma4/Fantasma4.obj");
    Model Fantasma5((char*)"Models/Fantasma5/Fantasma5.obj");
    Model Fantasma6((char*)"Models/Fantasma6/Fantasma6.obj");
    Model Fantasma7((char*)"Models/Fantasma7/Fantasma7.obj");
    Model Fantasma8((char*)"Models/Fantasma8/Fantasma8.obj");
    Model Fantasma9((char*)"Models/Fantasma9/Fantasma9.obj");
    
    
    Model cubito((char*)"Models/Cubito/Cubito.obj");
    //Monitor imagen
    Model MonitorApagado((char*)"Models/MonitorApagado/MonitorApagado.obj");
    Model MonitorEnemigo1((char*)"Models/MonitorEnemigo1/MonitorEnemigo1.obj");
    Model MonitorEnemigo2((char*)"Models/MonitorEnemigo2/MonitorEnemigo2.obj");
    Model MonitorEnemigo3((char*)"Models/MonitorEnemigo3/MonitorEnemigo3.obj");
    Model MonitorEnemigo4((char*)"Models/MonitorEnemigo4/MonitorEnemigo4.obj");

    
    //Arreglo para imagen en monitor
    Model MonitorEnemigosDeCoraje[5] = { MonitorApagado,MonitorEnemigo1,MonitorEnemigo2,MonitorEnemigo3,MonitorEnemigo4 };
   
    //Arreglo para aparicion de fantasmas
    Model AparicionFantasmas[10] = { cubito,Fantasma1,
                                    Fantasma2,Fantasma3,Fantasma4,
                                    Fantasma5,Fantasma6,Fantasma7,
                                    Fantasma8,Fantasma9 };

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    GLfloat vertices[] =
    {
        // positions          // colors           // texture coords
                                              //u  |  v                                            
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 

    };

    GLuint indices[] =
    {  // Note that we start from 0!
        0,1,3,
        1,2,3

    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load textures - para cargar texturas

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image; //    Aquí se alojan los bytes de las texturas al momento de trabajar con esllas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  //  //Para imagenes con .png, usar GL_RGBA
  //image = stbi_load("images/goku.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
  //  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  //  glGenerateMipmap(GL_TEXTURE_2D);
  //  //Si se logra generar la imagen, la mando a memoria
  //  if (image)
  //  {
  //      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  //      glGenerateMipmap(GL_TEXTURE_2D);
  //  }
  //  //mando mensaje de error y librero memoria  
  //  else
  //  {
  //      std::cout << "Failed to load texture" << std::endl;
  //  }
  //  stbi_image_free(image);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.0f, 0.0, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
        
        
        
        //Añadimos rotacionación de casa a futuro
        model = glm::translate(model, glm::vec3(-25.0f, 58.0f,-11.0f ));
        model = glm::rotate(model, glm::radians(rotacionAspas), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        
        //Mando a llamar a mi s nuevos modelos parte 1
        
        Aspas.Draw(shader);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(0);
        casa.Draw(shader);
        

        glBindVertexArray(0);
        


        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        AparicionFantasmas[n].Draw(shader);
        glBindVertexArray(0);
        
        
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        MonitorEnemigosDeCoraje[j].Draw(shader);
        glBindVertexArray(0);

        


        /****CAJON 1*************************************************************************************************************************/
//             
        model = glm::translate(model, glm::vec3(0.0f, 0.0f,rotacion));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cajon1.Draw(shader);
        glBindVertexArray(0);
        /****FIN CAJON 1*************************************************************************************************************************/
        /****CAJON 2*************************************************************************************************************************/
        
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, rotacion2));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cajon2.Draw(shader);
        glBindVertexArray(0);
        /****FIN 2*************************************************************************************************************************/
        /****CAJON 3*************************************************************************************************************************/
        
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, rotacion));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cajon3.Draw(shader);
        glBindVertexArray(0);
        /****FIN 3*************************************************************************************************************************/
        

         //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //PARA M U R C I E L A G O S
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Murcielago 1
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1+(3.1416*2)), linnear_bat_izq));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago1.Draw(shader);
        glBindVertexArray(0);
        
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         //Murcielago 2
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_izq));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago2.Draw(shader);
        glBindVertexArray(0);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Murcielago 3
       //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_izq));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago3.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
       //Murcielago 4
      //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_der));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago4.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
       //Murcielago 5
      //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_der));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago5.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Murcielago 6
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_der));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago6.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //! //Murcielago 7
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_der));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago7.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!  //! //Murcielago 8
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_der));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago8.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!  //! //Murcielago 9
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_izq));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago9.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!  //! //Murcielago 10
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_izq));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago10.Draw(shader);
        glBindVertexArray(0);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!  //! //Murcielago 11
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, sin(bat1 + (3.1416 * 2)), linnear_bat_izq));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Murcielago11.Draw(shader);
        glBindVertexArray(0);

      
        
        
        
        
        //---------------------------------------------------------------------------------------------------------
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!  //! Monitor apagado
        //Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
       /* model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Monitor0.Draw(shader);
        glBindVertexArray(0);*/
        
        
        
        /****ASPAS*************************************************************************************************************************/

        ////Seteamos en el origen=Hacemos que el comportamiento de los cajones sea regular
        //model = glm::mat4(1);
        //model = glm::rotacionate(model, glm::radians(rotacionAspas), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //Aspas.Draw(shader);
        
        /****FIN ASPAS*************************************************************************************************************************/
     /*   glBindVertexArray(0);*/



        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        lampshader.Use();
        //glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime*5);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime * 5);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime * 5);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime * 5);
    }
    //Por si se desea agregar alguna animacion a futuro
    if (bandera_de_reinicio)
    {

        printf("bandera_de_reinicio: %d\n", bandera_de_reinicio);
        
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Para M O N I T O R
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (j < 4) {
            j += 1;
        }
        else {
            j = 1;
        }
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Para F A N T A S M A S
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (n<9) {
            n += 1;
        }
        else {
            n = 0;
        }
        printf("================================================================>Valor de n: %d", n);
        printf("================================================================>Valor de j: %d", j);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Para M U R C I E L A G O S
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (cambio_sentido_bat==false) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!linnear_bat_izq: %f\n", linnear_bat_izq);
            //Movimiento senoidal
            bat1 += 0.2f;
            linnear_bat_izq -= 1.0f;
            linnear_bat_der += 1.0f;

            if (linnear_bat_izq <= -209.0f) {
                cambio_sentido_bat=true;

            }
        }

        if (cambio_sentido_bat == true) {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!linnear_bat_izq: %f\n", linnear_bat_izq);
            linnear_bat_izq += 1.0f;
            linnear_bat_der -= 1.0f;
            //Movimiento senoidal
            bat1 += 0.2f;

            if (linnear_bat_izq >= 0.0f) {
                cambio_sentido_bat = false;

            }
        }

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Para M U R C I E L A G O S
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Para cajones y aspas del molino
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (cambio_sentido == false) {
            printf("cambio de sentido: %d\n", cambio_sentido);
            rotacion2 -= 0.017f;
            rotacionAspas -= 2.0f;//Aspas

            //------------------------------------
            //Para que se alternen los cajones
            if (rotacion == 0.0f) {
                rotacion = rotacion;
            }
            else {
                rotacion += 0.017f;

            }
            //------------------------------------


            printf("***************************cajon rotacion2: %d\n", rotacion2);

            if (rotacion2 <= -4.29f) {
                cambio_sentido = true;
                
            }
        }

        

        if (cambio_sentido == true) {
            printf("cambio de sentido: %d\n", cambio_sentido);
            rotacion2 += 0.017f;
            rotacion -= 0.017f;
            


            printf("***************************cajon rotacion2: %f\n", rotacion2);
            rotacionAspas -= 2.0f;//Aspas

            if (rotacion2 >= 0.0f ) {
                cambio_sentido = false;
                

            }

        }
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //Para cajones y aspas del molino
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      
    }


    
    

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    //Activamos-desactivamos modo miedo -- apagamos /encendemos animaciones
    if (keys[GLFW_KEY_O]) {
        activacion = !activacion;
        n = 0;
        printf("\n!!!!!Valor de activacion: %d\n", activacion);
        if (activacion) {
            bandera_de_reinicio = true;
        
        }
        else {
            bandera_de_reinicio = false;
        }


    }
    


}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

