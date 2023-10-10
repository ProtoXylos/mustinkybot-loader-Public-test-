#pragma once

#include "../../pch.h"

#ifndef DIRECTORY_H
#define DIRECTORY_H

namespace directory {

    class Directory {
    private:
        std::wstring mustinkybot_path = L"C:\\mustinkybot";
        std::wstring user_path = mustinkybot_path + L"\\user";
        std::wstring logs_path = mustinkybot_path + L"\\logs";
        std::wstring settings_path = mustinkybot_path + L"\\settings";
    public:
        bool create_directories();
        bool read_auto_login_setting();
        bool read_license_key();
    };
}

#endif
