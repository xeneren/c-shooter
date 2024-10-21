#include "input.h"

keystate_t keyboardStates[SDL_NUM_SCANCODES] = { 0 };

keystate_t mouse1State = 0;
keystate_t mouse2State = 0;
keystate_t mouse3State = 0;
keystate_t mouse4State = 0;
keystate_t mouse5State = 0;

ivec2s mouseDelta;
vec2s mouseWheelDelta;

keystate_t checkState(keystate_t currentState, BOOL clicked) {
    if (currentState == KEYSTATE_UNCLICKED && clicked) {
        currentState = KEYSTATE_DOWN;
    }
    else if (currentState == KEYSTATE_DOWN) {
        if (clicked) {
            currentState = KEYSTATE_CLICKED;
        }
        else {
            currentState = KEYSTATE_UP;
        }
    }
    else if (currentState == KEYSTATE_CLICKED && !clicked) {
        currentState = KEYSTATE_UP;
    }
    else if (currentState == KEYSTATE_UP) {
        if (clicked) {
            currentState = KEYSTATE_DOWN;
        }
        else {
            currentState = KEYSTATE_UNCLICKED;
        }
    }
    return currentState;
}

void Input_PollStates() {
    int i = 1 << 0;
    uint32_t mouseButtons = SDL_GetRelativeMouseState(&mouseDelta.x, &mouseDelta.y);
    mouse1State = checkState(mouse1State, mouseButtons & SDL_BUTTON_LMASK);
    mouse2State = checkState(mouse2State, mouseButtons & SDL_BUTTON_RMASK);
    mouse3State = checkState(mouse3State, mouseButtons & SDL_BUTTON_MMASK);
    mouse4State = checkState(mouse4State, mouseButtons & SDL_BUTTON_X1MASK);
    mouse5State = checkState(mouse5State, mouseButtons & SDL_BUTTON_X2MASK);

    uint8_t* sdlKeyStates = SDL_GetKeyboardState(NULL);

    for (uint32_t i = 0; i < SDL_NUM_SCANCODES; i++) {
        keyboardStates[i] = checkState(keyboardStates[i], sdlKeyStates[i]);
    }
}

keystate_t Input_GetKeyState(SDL_Scancode scancode) {
    return keyboardStates[scancode];
}

keystate_t* Input_GetKeyStates(uint32_t* numkeys) {
    if (numkeys) {
        *numkeys = SDL_NUM_SCANCODES;
    }

    return keyboardStates;
}

keystate_t Input_GetMouseButton(mousebutton_t mouseButton) {
    switch (mouseButton) {
    case MOUSEBUTTON1:
        return mouse1State;
    case MOUSEBUTTON2:
        return mouse2State;
    case MOUSEBUTTON3:
        return mouse3State;
    case MOUSEBUTTON4:
        return mouse4State;
    case MOUSEBUTTON5:
        return mouse5State;
    default:
        return KEYSTATE_UNKNOWN;
    }
}

ivec2s Input_GetMouseDelta() {
    return mouseDelta;
}

void Input_CheckMouseWheel(SDL_MouseWheelEvent mouseWheelEvent) {
    mouseWheelDelta.x = mouseWheelEvent.x;
    mouseWheelDelta.y = mouseWheelEvent.y;
}

vec2s Input_GetMouseWheelDelta() {
    return mouseWheelDelta;
}

void Input_ResetMouseWheel() {
    mouseWheelDelta.x = 0;
    mouseWheelDelta.y = 0;
}