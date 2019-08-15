#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <ctime>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
int processToggleModel(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//const std::vector<glm::vec3> ctrl4pts = {
//  glm::vec3(-10.0f, 0.0f, 0.0f),
//  glm::vec3(10.0f, -30.0f, 0.0f),
//  glm::vec3(30.0f, 10.0f, 0.0f),
//  glm::vec3(50.0f, 60.0f, 0.0f)
//};
//const std::vector<glm::vec3> ctrl6pts = {
//  glm::vec3(0.0f, 0.0f, 0.0f),
//  glm::vec3(10.0f, 20.0f, 0.0f),
//  glm::vec3(30.0f, 60.0f, 0.0f),
//  glm::vec3(70.0f, 100.0f, 40.0f),
//  glm::vec3(162.0f, 126.0f, 40.0f),
//  glm::vec3(166.0f, 190.0f, 40.0f)
//};

// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

template <class T = bool> T flip_a_coin(T a = true, T b = false)
{
  if (rand() % 2)
    return a;
  else
    return b;
}

Camera * camera = nullptr;
int main(int argc, char **argv)
{
    using namespace std;
    srand(static_cast<int>(time(0)));

    vector<Camera> mxcamera;
    mxcamera.push_back(Camera(glm::vec3(0.0f, 0.0f, 3.0f)));
    camera = &mxcamera.back();
    unsigned c_idx = 0;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // number of objects to render
    unsigned n = 2;
    n = (argc >= 2) ? stoi(argv[1]) : 0;
    while((n == 0) || (n > 10)) {
      cout << "#n of models (1~10) to draw: ";
      cin >> n;
    }

    // build and compile shaders
    // -------------------------
    Shader ourShader(FileSystem::getPath("resources/cg_ufpel.vs").c_str(), FileSystem::getPath("resources/cg_ufpel.fs").c_str());

    // load models
    // -----------
    Model ourModel(FileSystem::getPath("resources/objects/planet/planet.obj"), n);

    {
      cout << "How to use: " << endl;
      cout << "1~0 <- selects the current object (default: 1)" << endl;
      cout << "HJKLIO <- move the object to left, down, up, right, back, front(respectively)" << endl;
      cout << "ASWF <- move the camera to left, down, up, right (respectively)" << endl;
      cout << "XYZ <- rotate the object on the X, Y, Z (respectively)" << endl;
      cout << "NMBC <- to play an animation: linear, spline curve, rotate in a point, custom (respectively)" << endl;
      cout << "RT <- to scale up/down" << endl;
      cout << "F1 <- to add a new camera" << endl;
      cout << "F2 <- to toggle between cameras" << endl;
      cout << "F3 <- to makes the camera do linear tranlation" << endl;
      cout << "F4 <- to makes the camera do spline tranlation" << endl;
      cout << endl << endl;
    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        ourModel.selectObj(processToggleModel(window));

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // move
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
          ourModel.translate_plus(-1.0f * deltaTime * glm::vec3(1.0f, .0f, .0f));
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
          ourModel.translate_plus(deltaTime * glm::vec3(1.0f, .0f, .0f));
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
          ourModel.translate_plus(-1.0f * deltaTime * glm::vec3(.0f, 1.0f, .0f));
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
          ourModel.translate_plus(deltaTime * glm::vec3(.0f, 1.0f, .0f));
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
          ourModel.translate_plus(-1.0f * deltaTime * glm::vec3(.0f, .0f, 1.0f));
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
          ourModel.translate_plus(deltaTime * glm::vec3(.0f, .0f, 1.0f));

        // rotate
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
          ourModel.rotate_plus(glm::quat(0.0f, 1.0f, 0.0f, 0.0f) * (deltaTime * 10.0f));
        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
          ourModel.rotate_plus(glm::quat(0.0f, 0.0f, 1.0f, 0.0f) * (deltaTime * 10.0f));
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
          ourModel.rotate_plus(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) * (deltaTime * 10.0f));

        // linear
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
          ourModel.setValue(animation_t::linear, 1.0f);
        // spline || bezier
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
          ourModel.setValue(animation_t::spline, 1.0f);
        // rotate in a point
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
          ourModel.setValue(animation_t::rotate_pt, 1.0f);
        // custom animation
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
          ourModel.setValue(animation_t::animation1, 1.0f);

        // scale
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
          ourModel.scale_plus((1.0f * deltaTime) * glm::vec3(1.0f, 1.0f, 1.0f));
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
          ourModel.scale_plus((-1.0f * deltaTime) * glm::vec3(1.0f, 1.0f, 1.0f));

        if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
          mxcamera.push_back(Camera(glm::vec3(0.0f, 0.0f, 3.0f)));
          c_idx = mxcamera.size() -1;;
          camera = &mxcamera[c_idx];
        }
        if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
          ++c_idx;
          c_idx %= mxcamera.size();
          camera = &mxcamera[c_idx];
        }

        if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS || camera->mv == mov_t::ln)
          camera->playLinear(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS || camera->mv == mov_t::sp)
          camera->playSpline(deltaTime);

        if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
          ; // axis rotation
        if (glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS)
          ; // point rotation

        if (glfwGetKey(window, GLFW_KEY_F7) == GLFW_PRESS)
          camera->playWalk(deltaTime); // walk

        if (glfwGetKey(window, GLFW_KEY_F8) == GLFW_PRESS)
          ; // look at point
        if (glfwGetKey(window, GLFW_KEY_F9) == GLFW_PRESS)
          ; // look at object

        if (glfwGetKey(window, GLFW_KEY_F10) == GLFW_PRESS)
          camera->playAnimation(deltaTime); // custom animation

        // render objects
        ourModel.renderObjects(ourShader, deltaTime);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

unsigned factorial(unsigned n)
{
  return (n == 0 || n == 1) ? 1 : n * factorial(n-1);
}

float comb(unsigned n, unsigned k)
{
  return factorial(n) / (factorial(n-k) * factorial(k));
}

// calculates a 3 dimensional point for the bezier curve using control points and a t
// ----------------------------------------------------------------------------------
glm::vec3 bezier(const vector<glm::vec3> pts, const float t)
{
  glm::vec3 ret = glm::vec3(.0f, .0f, .0f);
  unsigned n = pts.size() -1;

  for (unsigned i = 0; i <= n; ++i) {
    ret.x += comb(n, i) * std::pow(1.0f - t, n - i) * std::pow(t, n) * pts[i].x;
    ret.y += comb(n, i) * std::pow(1.0f - t, n - i) * std::pow(t, n) * pts[i].y;
    ret.z += comb(n, i) * std::pow(1.0f - t, n - i) * std::pow(t, n) * pts[i].z;
  }

  return ret;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
}

// process model toggle input: keys between 1~0 change between models 1~10
// ---------------------------------------------------------------------------------------------------------
int processToggleModel(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
      return 0;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
      return 1;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
      return 2;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
      return 3;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
      return 4;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
      return 5;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
      return 6;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
      return 7;
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
      return 8;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
      return 9;
    return -1;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}
