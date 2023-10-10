#pragma once

#include "../pch.h"

#ifndef DRAWING_H
#define DRAWING_H

namespace drawing {

    class Drawing {
    private:
        LPCSTR window_name = "mustinkybot";
        ImVec2 window_size = { 350, 150 };
        ImGuiWindowFlags window_flags = 0;
        bool draw_window = true;
    public:
        void active();
        bool is_active() const;
        void draw();
        void show_success_message();
    };

}

#endif
