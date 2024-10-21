#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <string.h>
#include <cglm/struct/vec2.h>
#include <util/defs.h>
#include <SDL_events.h>
#include <util/util.h>

typedef uint8_t keystate_t;
#define KEYSTATE_UNCLICKED 0ui8
#define KEYSTATE_CLICKED 1ui8
#define KEYSTATE_UP 3ui8
#define KEYSTATE_DOWN 4ui8
#define KEYSTATE_UNKNOWN 5ui8

typedef uint8_t mousebutton_t;
#define MOUSEBUTTON1 1ui8
#define MOUSEBUTTON2 2ui8
#define MOUSEBUTTON3 3ui8
#define MOUSEBUTTON4 4ui8
#define MOUSEBUTTON5 5ui8

void Input_PollStates();
keystate_t Input_GetKeyState(SDL_Scancode scancode);
keystate_t* Input_GetKeyStates(uint32_t* numkeys);
keystate_t Input_GetMouseButton(mousebutton_t mouseButton);
ivec2s Input_GetMouseDelta();
void Input_CheckMouseWheel(SDL_MouseWheelEvent mouseWheelEvent);
void Input_ResetMouseWheel();
vec2s Input_GetMouseWheelDelta();

#endif // ! INPUT_H
