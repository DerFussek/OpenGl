#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) ErrorHandler::clearErrors();\
                    x;\
                    ASSERT(ErrorHandler::checkForErrors())

class ErrorHandler {
    public:
        static void clearErrors();
        static bool checkForErrors();
};