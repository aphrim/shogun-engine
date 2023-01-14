#include <iostream>
#include <cstring>
#include "window.hpp"

namespace SHOGUN {
static Window* activeWindow;

static void windowSizeChangeCallback(GLFWwindow*, int width, int height) {
    activeWindow->size = {(float) width, (float) height};
    for (WindowVector2EventListener listener : activeWindow->sizeChangeListeners) (*listener)(Vector2(width, height));
}

static void windowFocusedCallback(GLFWwindow*, int newFocus) {
    if (newFocus) {
        activeWindow->setIsFocused(true); 
    } else {
        activeWindow->setIsFocused(false);
    }
    for (WindowBoolEventListener listener : activeWindow->focusChangeListeners) (*listener)(newFocus == 1 ? true : false);
}

static void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        for (WindowIntEventListener listener : activeWindow->keyPressListeners) (*listener)(key);
    } else if (action == GLFW_RELEASE) {
        for (WindowIntEventListener listener : activeWindow->keyReleaseListeners) (*listener)(key);
    }
}

static void windowMouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED) != 1) return;
    for (WindowVector2EventListener listener : activeWindow->mouseMoveListeners)
        (*listener)(Vector2((xpos - activeWindow->mouse.x) / 8, (activeWindow->mouse.y - ypos) / 8));
    activeWindow->mouse = Vector2(xpos, ypos);
}

Window::Window(Vector2 size, const char* name, bool fullScreen) : 
    size(size), name(std::string(name))
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (fullScreen) {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        size.x = mode->width;
        size.y = mode->height;
        window = glfwCreateWindow(mode->width, mode->height, name, glfwGetPrimaryMonitor(), nullptr);
        this->size = size;
    } else {
        window = glfwCreateWindow(size.x, size.y, name, nullptr, nullptr);
    }

    if (window == nullptr) {
        glfwTerminate();
        std::cout << "Window is nullptr. Failed window creation (Window::Window) \n";
        throw "Failed to initalize window";
    }

    glfwMakeContextCurrent(window);
    //glViewport(0, 0, size.x, size.y);

    glfwSetFramebufferSizeCallback(window, windowSizeChangeCallback);
    glfwSetKeyCallback(window, windowKeyCallback);
    glfwSetWindowFocusCallback(window, windowFocusedCallback);
    glfwSetCursorPosCallback(window, windowMouseCallback);
    activeWindow = this;
    hoverCount = 0;
    cursorNormal = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    cursorHover = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::update() const {
    if (hoverCount > 0) {
        glfwSetCursor(window, cursorHover);
    } else {
        glfwSetCursor(window, cursorNormal);
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


bool Window::isKeyPressed(int key) const {
    return (glfwGetKey(window, key) == GLFW_PRESS); 
}

bool Window::isMouseButtonPressed(int key) const {
    return (glfwGetMouseButton(window, key) == GLFW_PRESS);
}

void Window::addListener(WindowVector2EventListener listener, WindowEventType type) {
    switch (type) {
    case WE_MOUSE_MOVE:
        activeWindow->mouseMoveListeners.push_back(listener);
        break;
    case WE_SIZE_CHANGE:
        activeWindow->sizeChangeListeners.push_back(listener);
        break;
    default:
        std::cout << "Wrong listener type \n";
        throw "Listener is not correct type for the WindowEventType, please check the docs";
    }
}

void Window::addListener(WindowIntEventListener listener, WindowEventType type) {
    switch (type) {
    case WE_MOUSE_SCROLL:
        activeWindow->scrollChangeListeners.push_back(listener);
        break;
    case WE_KEY_PRESS:
        activeWindow->keyPressListeners.push_back(listener);
        break;
    case WE_KEY_RELEASE:
        activeWindow->keyReleaseListeners.push_back(listener);
        break;
    default:
        std::cout << "Wrong listener type \n";
        throw "Listener is not correct type for the WindowEventType, please check the docs";
    }
}

void Window::addListener(WindowBoolEventListener listener, WindowEventType type) {
    switch (type) {
    case WE_FOCUS_CHANGE:
        activeWindow->focusChangeListeners.push_back(listener);
        break;
    default:
        std::cout << "Wrong listener type \n";
        throw "Listener is not correct type for the WindowEventType, please check the docs";
    }
}
    


const char* Window::getWindowName() const {
    return name.c_str();
}

void Window::setWindowName(const char* nameNew) {
    name = std::string(nameNew);
    glfwSetWindowTitle(window, name.c_str());
}

Vector2 Window::getWindowSize() const {
    return size;
}

void Window::setWindowSize(Vector2 size) {
    this->size = size;
    glfwSetWindowSize(window, size.x, size.y);
}

void Window::requestUserAttention() const {
    glfwRequestWindowAttention(window);
}

bool Window::isFocused() const {
    return focused;
}

void Window::focus() {
    glfwFocusWindow(window);
}

void Window::setIsFocused(bool focused) {
    this->focused = focused;
}

void Window::disableMouse() const {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Vector2 Window::getMousePosition() const {    
    return mouse;
}

Vector2 Window::getGUISpaceMousePosition() {
    return mouse / size;
}
}
