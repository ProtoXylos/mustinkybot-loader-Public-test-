#include "cheat.h"

namespace cheat {

    directory::Directory directory;
    drawing::Drawing draw_manager;
    hwid::CombinedHWIDProvider combined_hwid_provider;
    login::AuthenticationManager authentication_manager;
    cheat::CheatManager cheat_manager;

    void CheatManager::handle_game_selection(const std::string& game, const std::string& game_update) {
        if (ImGui::Selectable(game.c_str())) {
            selected_game = game;
            selected_game_update = game_update;

            show_overlay_window = !show_overlay_window;
        }
    }

    void CheatManager::my_window() {
        try {
            std::string dll = flux::variables::get<std::string>("DLL");
            std::vector<std::string> games;

            size_t pos = 0;
            while ((pos = dll.find(":")) != std::string::npos) {
                games.push_back(dll.substr(0, pos));
                dll.erase(0, pos + 1);
            }
            games.push_back(dll);

            ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);

            ImGui::Begin("Authentication Info");

            ImVec2 auth_info_window_pos = ImGui::GetWindowPos();
            ImVec2 auth_info_window_size = ImGui::GetWindowSize();

            ImGui::Columns(1, "AuthenticationColumns");

            for (const std::string& game : games) {
                std::string game_string = flux::variables::get<std::string>(game);
                std::string game_string_update = flux::variables::get<std::string>(game + "-Update");

                if (load_dll) {
                    std::vector<char> data;
                    try {
                        flux::variables::download(game + "-File", data);
                        std::cout << "File downloaded successfully." << std::endl;
                    }
                    catch (std::runtime_error& e) {
                        std::cout << "Error downloading file: " << e.what() << std::endl;
                    }
                }

                handle_game_selection(game_string, game_string_update);
            }

            ImGui::NextColumn();

            ImGui::End();

            if (show_overlay_window) {
                ImGui::SetNextWindowPos(auth_info_window_pos);
                ImGui::SetNextWindowSize(auth_info_window_size);

                ImGui::Begin("Overlay Window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

                ImGui::Text("Selected Game: %s", selected_game.c_str());
                ImGui::Text("Selected Game Update: %s", selected_game_update.c_str());

                if (ImGui::Button("Back")) {
                    show_overlay_window = !show_overlay_window;
                }

                ImGui::SameLine();

                if (ImGui::Button("Load")) {
                    load_dll = !load_dll;
                }

                ImGui::End();
            }
        }
        catch (std::runtime_error& e) {
            std::cout << "Error getting field or variable: " << e.what() << std::endl;
        }
    }
}
