#pragma once

#include <iostream>
#include "REngine/Application.hpp"
#include "bhs_game/models/AirportLogistic.hpp"

class DemoLayer : public REngine::Layer {
public:
    virtual void OnUIRender() override {
        ImGui::ShowDemoWindow();
    }
};

class HelloLayer : public REngine::Layer {
public:
    virtual void OnUIRender() override {
        ImGui::Begin("Hello");
        ImGui::Button("Button");
        ImGui::End();
    }
};

class BHSGameLayer : public REngine::Layer {
public:

    virtual void OnAttach() {
        std::cout << "Attach" << std::endl;

    }

    virtual void OnDetach() {
        std::cout << "Detach" << std::endl;
    }

    virtual void OnUpdate(float ts) override {
        // Update game logic
        std::cout << "Update: " << ts << std::endl;

    }

    virtual void OnUIRender() override {

        ImGui::Begin("Viewport");
        ImGui::Button("Button");
        ImGui::End();
        std::cout << "UIRender" << std::endl;
    }
};

REngine::Application *REngine::CreateApplication(int argc, char **argv) {
    REngine::ApplicationSpecification spec;
    spec.Name = "REngine window name";

    REngine::Application *app = new REngine::Application(spec);
    app->PushLayer<DemoLayer>();
    app->PushLayer<BHSGameLayer>();
    return app;
}