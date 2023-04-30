#include "bhs_vis/BHSApp.h"
#include "bhs_game/models/AirportLogistic.hpp"

bool g_ApplicationRunning = true;

int main(int argc, char **argv) {
    // Initialize app

    while (g_ApplicationRunning) {
        REngine::Application *app = REngine::CreateApplication(argc, argv);
        app->Run();
        delete app;
    }

    return 0;
}