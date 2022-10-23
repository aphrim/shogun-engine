#pragma once
#include <vector>
#include <string>
#include "include.hpp"
#include "vector.hpp"

namespace SHOGUN {

typedef enum {
    WE_MOUSE_MOVE, WE_MOUSE_SCROLL,
    WE_SIZE_CHANGE, WE_FOCUS_CHANGE,
    WE_KEY_PRESS, WE_KEY_RELEASE,
} WindowEventType;

typedef void (*WindowVector2EventListener)(Vector2);
typedef void (*WindowIntEventListener)(int);
typedef void (*WindowBoolEventListener)(bool);

class Window {
public:

    Window(Vector2 size, const char* name, bool fullScreen);
    ~Window();

    bool shouldClose() const;
    void update() const;

    bool isKeyPressed(int key) const;
    bool isMouseButtonPressed(int key) const;

    void addListener(WindowVector2EventListener listener, WindowEventType type);
    void addListener(WindowIntEventListener     listener, WindowEventType type);
    void addListener(WindowBoolEventListener    listener, WindowEventType type);

    const char* getWindowName() const;
    void setWindowName(const char* nameNew);

    Vector2 getWindowSize() const;
    void setWindowSize(Vector2 size);

    void requestUserAttention() const;
    
    bool isFocused() const;
    void focus();
    void setIsFocused(bool focused);


    void disableMouse() const;
    Vector2 getMousePosition() const;

    std::vector<WindowVector2EventListener> sizeChangeListeners   = std::vector<WindowVector2EventListener>();
    std::vector<WindowVector2EventListener> mouseMoveListeners    = std::vector<WindowVector2EventListener>();
    std::vector<WindowBoolEventListener>    focusChangeListeners  = std::vector<WindowBoolEventListener>();
    std::vector<WindowIntEventListener>     scrollChangeListeners = std::vector<WindowIntEventListener>();
    std::vector<WindowIntEventListener>     keyPressListeners     = std::vector<WindowIntEventListener>();
    std::vector<WindowIntEventListener>     keyReleaseListeners   = std::vector<WindowIntEventListener>();
    Vector2 mouse;
    Vector2 size;
private:
    GLFWwindow* window;
    std::string name;
    bool focused;

};
}
