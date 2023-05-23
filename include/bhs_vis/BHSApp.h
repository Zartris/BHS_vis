#pragma once

#include <iostream>
#include "REngine/Application.hpp"
#include "REngine/BHSApplication.h"
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
    float time_remaining = 0.0f;

    virtual void OnAttach() override {
        std::cout << "Attach" << std::endl;
    }

    virtual void OnDetach() override {
        std::cout << "Detach" << std::endl;
    }

    virtual void OnUpdate(float ts) override {
        // Update game logic
        std::cout << "Update: " << ts << "s" << std::endl;
        REngine::BHSApplication *app = &REngine::BHSApplication::Get();
        float physics_dt = app->airportLogistic->get_physic_step_time();
        time_remaining += ts;
        while (time_remaining > physics_dt) {
            app->airportLogistic->step(ts);
            time_remaining -= physics_dt;
        }
    }

    virtual void OnUIRender() override {

        ImGui::Begin("Viewport");
        // Draw the viewport here
        // draw triangle






        ImGui::End();
        std::cout << "UIRender" << std::endl;
    }
};

REngine::Application *REngine::CreateApplication(int argc, char **argv) {
    REngine::ApplicationSpecification spec;
    spec.Name = "REngine window name";

    REngine::BHSApplication *app = new REngine::BHSApplication(spec);
    app->PushLayer<DemoLayer>();
    app->PushLayer<BHSGameLayer>();
    return app;
}