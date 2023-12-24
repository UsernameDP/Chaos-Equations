#include <iostream>
#include <GLCore/Core/Core.hpp>

#include "ChaosEquationsLayer.hpp"
class ExampleApplication : public GLCore::Application {

public:
    ExampleApplication() : GLCore::Application("OpenGL_Example")
    {

    }

    virtual void init() override {
        Extension::AssetPool::setComputeShader(new Extension::Shaders::ComputeShader("InitGen", "initGen.comp"));

        pushLayer(new ChaosEquationsLayer());
    }
};

int main()
{
    Window::disableVsync();
    std::unique_ptr<GLCore::Application> app = std::make_unique<ExampleApplication>();
    app->init();
    app->run();
}