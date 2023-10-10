#include "Drawing.h"

namespace drawing {

    directory::Directory directory;
    drawing::Drawing draw_manager;
    hwid::CombinedHWIDProvider combined_hwid_provider;
    login::AuthenticationManager authentication_manager;
    cheat::CheatManager cheat_manager;

    void Drawing::active() {
        draw_window = true;
    }

    bool Drawing::is_active() const {
        return draw_window;
    }

    void Drawing::draw() {
        if (is_active()) {
            ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
            authentication_manager.show_authentication_dialog();
        }
    }

    void Drawing::show_success_message() {
        cheat_manager.my_window();
    }
}
