/*
- Window.hpp
-
- Author: 100086865
-
- Header files for Window.cpp, contains the definitions for
- the callback functions.
*/

#pragma once

/*
- Callback function that processes keyboard input
- @param: Current window
- @param: Actioned key
- @param: Key scan code
- @param: Action (pressed, released)
- @param: Keyboard modifier (Shift, ALT, CTRL, Super)
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

/*
- Callback function that resizes the window
- @param: Current window
- @param: New window width
- @param: New window height
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);