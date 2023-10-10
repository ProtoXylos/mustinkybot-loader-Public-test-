#pragma once

#include "../../pch.h"

#ifndef CHEAT_H
#define CHEAT_H

namespace cheat {

    class CheatManager {
    private:
        bool show_overlay_window;
        bool load_dll;
        ImVec2 window_size = { 470, 300 };
        std::string selected_game;
        std::string selected_game_update;

    public:
        void handle_game_selection(const std::string& game, const std::string& game_update);
        void my_window();
    };
}

#endif
