#include "errors/ErrorHandler.h"

void ErrorHandler::clearErrors() {
    while(glGetError() != GL_NO_ERROR);
}

bool ErrorHandler::checkForErrors() {
    while(GLenum err = glGetError()) {
        std::string type;

        switch(err) {
            case 0x0500: type = "GL_INVALID_ENUM";
            case 0x0501: type = "GL_INVALID_VALUE";
            case 0x0502: type = "GL_INVALID_OPERATION";
            case 0x0505: type = "GL_OUT_OF_MEMORY";
            case 0x0506: type = "GL_INVALID_FRAMEBUFFER_OPERATION";

            default: type = "Not in List!";
            return false;
        }

        std::cout << "[OpenGl Error] (" << err << "): " << type << "\n";
    }

    return true;
}