// ## OS ## 
#include <Windows.h>
//#include <filesystem>
#include <iostream>
#include <sstream>     

// ## Threading ##
#include <thread>
#include <atomic>

// ## External Libs ##
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<ft2build.h>
#include FT_FREETYPE_H

// ## Engine ##
#include "physics_engine/core/Engine.h"
#include "physics_engine/core/ObjectManager.h"      
#include "physics_engine/error/ErrorHandler.h"

#include "physics_engine/objects/Drawable.h"
#include "physics_engine/objects/GlShape.h"
#include "physics_engine/objects/ObjectManager.h"
#include "physics_engine/objects/ShapeFactory.h"
#include "physics_engine/objects/Updateable.h"

#include "physics_engine/rendering/VertexBuffer.h"
#include "physics_engine/rendering/VertexBufferLayout.h"
#include "physics_engine/rendering/VertexArray.h"
#include "physics_engine/rendering/IndexBuffer.h"
#include "physics_engine/rendering/Shader.h"
#include "physics_engine/rendering/Renderer2D.h"
#include "physics_engine/rendering/TextRenderer.h"

#include "physics_engine/ui/UIElement.h"
#include "physics_engine/ui/Panel.h"
#include "physics_engine/ui/Button.h"

#include "physics_engine/objects/objs/Circle.h"
// ## Global Vars and Functions ##

// ## Main Function ## 
int main() {
    
    // --- Essentials --- //
    PhyEn::Engine engine("Standart");
    PhyEn::ErrorHandler errorhandler;

    PhyEn::ObjectManager objectManager;
    PhyEn::Shader shapeShader("../../assets/shaders/shape.vert", "../../assets/shaders/shape.frag");
    PhyEn::Renderer2D renderer2D(&shapeShader);

    float width  = 800.0f;
    float height = 600.0f;

    auto proj = glm::ortho(-width  * 0.5f, width  * 0.5f,
                           -height * 0.5f, height * 0.5f,
                           -1.0f, 1.0f);
    auto view = glm::mat4(1.0f);
    glm::mat4 viewProj = proj * view;


    // Beispielobjekt
    auto rect = objectManager.createDrawable<PhyEn::Panel>(
        glm::vec2{0.0f, 0.0f},
        glm::vec2{100.0f, 50.0f},
        glm::vec4{0.2f, 0.3f, 0.8f, 1.0f}
    );

    auto* circle = objectManager.createDrawable<PhyEn::Circle>(50.0f, glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 64);
    
    while (!engine.WindowShouldClose()) {
        try {
            static auto last = glfwGetTime();
            auto now = glfwGetTime();
            float dt = static_cast<float>(now - last);
            last = now;

                objectManager.updateAll(dt);
                renderer2D.begin(viewProj);
                objectManager.drawAll(renderer2D);
                renderer2D.end();

            engine.SwapBuffersAndPollEvents();
            errorhandler.checkForErrors();
        } catch (std::exception &e) {
            std::cerr << "Exeption in the Main-Loop: " << e.what() << std::endl;
        }
    }

    std::cout << "Engine killed!\n";
    engine.kill();
    return 0;
}



