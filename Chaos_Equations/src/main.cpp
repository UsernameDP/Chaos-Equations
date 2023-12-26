#include <iostream>
#include <GLCore/Core/Core.hpp>

#include "Layer.hpp"
class ChaosEquationsApplication : public GLCore::Application {

public:
    ChaosEquationsApplication(const GLCore::WindowProps& props) : GLCore::Application(props)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_PROGRAM_POINT_SIZE);
    }

    virtual void init() override {
        Extension::AssetPool::setComputeShader(new Extension::Shaders::ComputeShader("InitGen", "initGen.comp"));
        Extension::AssetPool::setShader(new Extension::Shaders::VertexPipelineShader("Axis", "axis.vert", "axis.frag"));
        Extension::AssetPool::setShader(new Extension::Shaders::VertexPipelineShader("Chaos", "chaos.vert", "chaos.geom", "chaos.frag"));

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