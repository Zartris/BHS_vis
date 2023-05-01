//
// Created by zartris on 5/1/23.
//

#pragma once

#include "REngine/Application.hpp"
#include "bhs_game/models/AirportLogistic.hpp"

namespace REngine {
    class BHSApplication : public Application {
    public:
        BHSApplication(const ApplicationSpecification &spec);

        std::unique_ptr<bhs_game::AirportLogistic> airportLogistic;


    };
}


