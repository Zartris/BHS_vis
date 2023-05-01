//
// Created by zartris on 5/1/23.
//

#include "REngine/BHSApplication.h"

REngine::BHSApplication::BHSApplication(const REngine::ApplicationSpecification &spec) : Application(spec) {
    airportLogistic = std::make_unique<bhs_game::AirportLogistic>();
    airportLogistic->populate_world_from_file();
    airportLogistic.start();
    airportLogistic.stop();
    airportLogistic.destroy();

}
