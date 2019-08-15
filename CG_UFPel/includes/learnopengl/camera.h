#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

enum mov_t { nn, ln, sp, rt, rt_pt, wk, lk, lk_at, an };
typedef struct  ctrl_mov_ {
  glm::vec3 to;
  float time;
} ctrl_mov_t;
// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position; // the camera in relation to the world
    glm::vec3 Front; // a point in front of the camera
    glm::vec3 Up; // the up vector
    glm::vec3 Right; // right vector
    glm::vec3 WorldUp; // a point up
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    mov_t mv = mov_t::nn; // current movment
    ctrl_mov_t cmv; // control movment
    // TODO remove
    float yoff_max = 1.0f;
    float old_pitch = 0.0f;
    //

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
        this->cmv.time = 0.0f;
    }
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
        this->cmv.time = 0.0f;
    }

    void playSpline(float time)
    {
      if (this->mv == mov_t::nn) {
        this->cmv.time = 1.0f;
        this->mv = mov_t::sp;
      } else if (this->cmv.time < 0.0f) {
        this->cmv.time = 0.0f;
        this->mv = mov_t::nn;
      }

      this->cmv.time -= time;
      this->Position += glm::catmullRom(glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.2f, 0.3f, 0.0f),
          glm::vec3(0.4f, -0.4f, 0.0f),
          glm::vec3(1.0f, 0.8f, 0.0f),
          1.0f - this->cmv.time);
    }

    void playLinear(float time)
    {
      if (this->mv == mov_t::nn) {
        this->cmv.time = 1.0f;
        this->mv = mov_t::ln;
      } else if (this->cmv.time < 0.0f) {
        this->cmv.time = 0.0f;
        this->mv = mov_t::nn;
      }

      this->cmv.time -= time;
      this->Position += (glm::vec3(1.0f, 0.0f, 1.0f) * time);
    }

    void playWalk(float time)
    {
      if (this->mv == mov_t::nn) {
        this->cmv.time = 1.0f;
        this->mv = mov_t::wk;
      } else if (this->cmv.time < 0.0f) {
        this->cmv.time = 0.0f;
        this->mv = mov_t::nn;
      }

      this->cmv.time -= time;
      this->Position += (glm::vec3(0.0f, 0.0f, 1.0f) * time);
    }

    void playAnimation(float time)
    {
      if (this->mv == mov_t::nn) {
        this->cmv.time = 1.0f;
        this->mv = mov_t::an;
      } else if (this->cmv.time < 0.0f) {
        this->cmv.time = 0.0f;
        this->mv = mov_t::nn;
      }

      this->cmv.time -= time;
      this->Position += (glm::vec3(0.0f, 0.0f, 1.0f) * time);
      if (this->cmv.time > .75f) {
        this->Position += (glm::vec3(0.0f, 0.0f, 1.0f) * time);
      } else if (this->cmv.time > .5f) {
        this->Position += (glm::vec3(0.0f, 1.0f, 0.0f) * time);
      } else {
        this->Position += (glm::vec3(1.0f, 1.0f, 1.0f) * time);
      }
    }

    void play(float dt)
    {
      switch(this->mv){
        case mov_t::ln: this->playLinear(dt);
        case mov_t::sp: this->playSpline(dt);
        case mov_t::rt: ;
        case mov_t::rt_pt: ;
        case mov_t::wk: ;
        case mov_t::lk: ;
        case mov_t::lk_at: ;
        case mov_t::an: this->playAnimation(dt);
        default:
          return;
      }
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif
