#include "login.h"

namespace login {

    directory::Directory directory;
    drawing::Drawing draw_manager;
    hwid::CombinedHWIDProvider combined_hwid_provider;
    login::AuthenticationManager authentication_manager;
    cheat::CheatManager cheat_manager;

    AuthenticationManager::AuthenticationManager() {
        bool success = flux::set_application("cllzb1dgo000cpn01ca4yfp8u");
        hwid = combined_hwid_provider.get_combined_hwid();
    }

    bool AuthenticationManager::handle_authentication(const char* license_key) {
        try {
            hwid = combined_hwid_provider.get_combined_hwid();
            flux::authenticate(license_key, hwid.c_str());
            authentication_successful = true;
            std::cout << "Authentication successful." << std::endl;
        }
        catch (std::runtime_error& e) {
            std::cout << "Authentication failed: " << e.what() << std::endl;
        }
    }

    void AuthenticationManager::show_login_dialog() {
        ImGui::Begin("mustinkybot - Login");
        {
            ImGui::Text("Login");

            ImGui::InputText("License Key", user_license_key, sizeof(user_license_key));

            if (ImGui::Button("Authenticate")) {
                handle_authentication(user_license_key);
            }

            ImGui::SameLine();

            ImGui::Checkbox("Auto-Login", &autologin);
        }
        ImGui::End();
    }

    void AuthenticationManager::show_authentication_dialog() {

        if (!authentication_successful) {
            show_login_dialog();

            directory.read_auto_login_setting();

            if (autologin && !auto_login_attempted) {
                auto_login_attempted = true;
                directory.read_license_key();
            }
        }
        else {
            bool directories_created = directory.create_directories();
            draw_manager.show_success_message();
        }
    }
}
