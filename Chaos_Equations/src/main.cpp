#include <iostream>
#include <GLCore/Core/Core.hpp>

#include "ChaosEquationsLayer.hpp"
class ChaosEquationsApplication : public GLCore::Application {

public:
    ChaosEquationsApplication(const GLCore::WindowProps& props) : GLCore::Application(props)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    virtual void init() override {
        Extension::AssetPool::setComputeShader(new Extension::Shaders::ComputeShader("InitGen", "initGen.comp"));

        pushLayer(new ChaosEquationsLayer());
    }
};

int main()
{
    GLCore::WindowProps props = GLCore::WindowProps("Chaos Equations");
    props.disableVsync();
    std::unique_ptr<GLCore::Application> app = std::make_unique<ChaosEquationsApplication>(props);
    app->init();
    app->run();
}