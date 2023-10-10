#include "directory.h"

namespace directory {

    directory::Directory directory;
    drawing::Drawing draw_manager;
    hwid::CombinedHWIDProvider combined_hwid_provider;
    login::AuthenticationManager authentication_manager;
    cheat::CheatManager cheat_manager;

    bool Directory::create_directories() {

        CreateDirectoryW(mustinkybot_path.c_str(), nullptr);
        CreateDirectoryW(user_path.c_str(), nullptr);
        CreateDirectoryW(logs_path.c_str(), nullptr);
        CreateDirectoryW(settings_path.c_str(), nullptr);

        std::wstring user_file_path = user_path + L"\\user.txt";
        std::ofstream user_file(user_file_path);
        if (user_file.is_open()) {
            user_file << authentication_manager.user_license_key;
            user_file.close();
        }
        else {
            return false;
        }

        if (authentication_manager.autologin) {
            std::wstring settings_file_path = settings_path + L"\\settings.txt";
            std::ofstream settings_file(settings_file_path);
            if (settings_file.is_open()) {
                settings_file << "AutoLogin = true";
                settings_file.close();
            }
            else {
                return false;
            }
        }

        return true;
    }

    bool Directory::read_auto_login_setting() {

        std::wstring settings_file_path = settings_path + L"\\settings.txt";
        std::ifstream settings_file(settings_file_path);
        if (settings_file.is_open()) {
            std::string line;
            while (std::getline(settings_file, line)) {
                if (line.find("AutoLogin = true") != std::string::npos) {
                    authentication_manager.autologin = true;
                    break;
                }
            }
            settings_file.close();
        }
        return authentication_manager.autologin;
    }

    bool Directory::read_license_key() {

        std::wstring user_file_path = user_path + L"\\user.txt";
        std::wifstream user_file(user_file_path);

        if (user_file.is_open()) {
            std::wstring w_license_key;
            std::getline(user_file, w_license_key);

            size_t converted_chars = 0;
            wcstombs_s(&converted_chars, authentication_manager.user_license_key, w_license_key.c_str(), sizeof(authentication_manager.user_license_key));

            if (!authentication_manager.handle_authentication(authentication_manager.user_license_key)) {
                std::wstring settings_file_path = settings_path + L"\\settings.txt";
                if (DeleteFileW(settings_file_path.c_str())) {
                    std::cout << "Deleted settings.txt due to authentication failure." << std::endl;
                }
                user_file.close();
                return false;
            }

            user_file.close();

            return true;
        }

        return false;
    }
}
