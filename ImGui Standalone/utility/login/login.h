#pragma once

#include "../../pch.h"

#ifndef LOGIN_H
#define LOGIN_H

namespace login {

    class AuthenticationManager {
    private:

    public:

        bool authentication_successful = false;
        bool autologin;
        bool auto_login_attempted = false;
        std::string hwid;
        char user_license_key[64] = "";

        AuthenticationManager();

        bool handle_authentication(const char* license_key);

        void show_login_dialog();
        void show_authentication_dialog();
    };
}

#endif
