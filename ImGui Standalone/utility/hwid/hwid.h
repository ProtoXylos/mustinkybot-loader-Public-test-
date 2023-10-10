#pragma once

#include "../../pch.h"

#ifndef HWID_H
#define HWID_H

namespace hwid {

    class CPUIDProvider {
    public:
        static std::string get_cpu_id();
    };

    class MACAddressProvider {
    public:
        static std::string get_mac_address();
    };

    class CombinedHWIDProvider {
    public:
        static std::string get_combined_hwid();
    };

}

#endif
