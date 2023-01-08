#pragma once
#include "../include.hpp"
#include "../entity.hpp"
#include "../math.hpp"
#include "../window.hpp"

//Not much difference between <Entity> and <GUIElement> other than a method to render without requiring camera.
//Also, even though position and scale are scored in Vector3s, only the X and Y are used.
namespace SHOGUN {

typedef enum {
    GUI_EL_ANCHOR_TL, GUI_EL_ANCHOR_CENTER 
} GUI_EL_ANCHOR;

typedef enum {
    GUI_EL_DOCK_TL, GUI_EL_DOCK_CENTER
} GUI_EL_DOCK;
class GUIElement : public Entity {
public:
    virtual void render() {}
    virtual bool collides(Vector2 pos) {return true;}
    Window* window;

    GUI_EL_ANCHOR anchor = GUI_EL_ANCHOR_TL;
    GUI_EL_DOCK dock = GUI_EL_DOCK_TL;


    Vector2 toGLPosition(Vector2 pos, Vector2 size) {
        if (dock == GUI_EL_DOCK_CENTER) { 
            return pos / window->size * Vector2(2, -2) + Vector2(-1, 1);  
        } else if (dock == GUI_EL_DOCK_TL) {
            return (pos + size / 2) / window->size * Vector2(2, -2) + Vector2(-1, 1);
        }
        return Vector2();
    }

    Vector2 toTLAnchor(Vector2 pos) {return Vector2();}
    Vector2 toCenterDock(Vector2 pos, Vector2 size) {
        //Convert cordinate system
        if (dock == GUI_EL_DOCK_CENTER) return pos;
        else if (dock == GUI_EL_DOCK_TL) {
            return pos + Vector2(size.x / 2, size.y / 2); 
        }
        return Vector2();
    }

};
}
