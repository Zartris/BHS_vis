//
// Created by zartris on 5/1/23.
//

#include "REngine/BHSApplication.h"

static REngine::BHSApplication *s_bhs_Instance = nullptr;

namespace REngine {
    BHSApplication::BHSApplication(const REngine::ApplicationSpecification &spec) : Application(spec) {
        s_bhs_Instance = this;

        airportLogistic = std::make_unique<bhs_game::AirportLogistic>();
        airportLogistic->populate_world();
        airportLogistic->set_physic_step_time(0.01f);
    }

    BHSApplication &BHSApplication::Get() {
        return *s_bhs_Instance;
    }


}

