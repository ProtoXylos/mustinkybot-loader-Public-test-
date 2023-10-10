#include "hwid.h"

namespace hwid {

    directory::Directory directory;
    drawing::Drawing draw_manager;
    hwid::CombinedHWIDProvider combined_hwid_provider;
    login::AuthenticationManager authentication_manager;
    cheat::CheatManager cheat_manager;

    std::string CPUIDProvider::get_cpu_id() {
        std::string cpu_id;

        if (CoInitializeEx(0, COINIT_MULTITHREADED) == S_OK) {
            if (CoInitializeSecurity(
                nullptr,
                -1,
                nullptr,
                nullptr,
                RPC_C_AUTHN_LEVEL_DEFAULT,
                RPC_C_IMP_LEVEL_IMPERSONATE,
                nullptr,
                EOAC_NONE,
                nullptr) == S_OK) {

                IWbemLocator* p_loc = nullptr;
                IWbemServices* p_svc = nullptr;

                if (CoCreateInstance(
                    CLSID_WbemLocator,
                    0,
                    CLSCTX_INPROC_SERVER,
                    IID_IWbemLocator,
                    reinterpret_cast<LPVOID*>(&p_loc)) == S_OK) {

                    if (p_loc->ConnectServer(
                        BSTR(L"ROOT\\CIMV2"),
                        nullptr,
                        nullptr,
                        nullptr,
                        0,
                        nullptr,
                        nullptr,
                        &p_svc) == S_OK) {

                        if (CoSetProxyBlanket(
                            p_svc,
                            RPC_C_AUTHN_WINNT,
                            RPC_C_AUTHZ_NONE,
                            nullptr,
                            RPC_C_AUTHN_LEVEL_CALL,
                            RPC_C_IMP_LEVEL_IMPERSONATE,
                            nullptr,
                            EOAC_NONE) == S_OK) {

                            IEnumWbemClassObject* p_enumerator = nullptr;

                            if (p_svc->ExecQuery(
                                BSTR(L"WQL"),
                                BSTR(L"SELECT * FROM Win32_Processor"),
                                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                                nullptr,
                                &p_enumerator) == S_OK) {

                                IWbemClassObject* p_cls_obj = nullptr;
                                ULONG u_return = 0;

                                while (p_enumerator) {
                                    HRESULT hr = p_enumerator->Next(WBEM_INFINITE, 1, &p_cls_obj, &u_return);
                                    if (u_return == 0) {
                                        break;
                                    }

                                    VARIANT vt_prop;
                                    hr = p_cls_obj->Get(L"ProcessorId", 0, &vt_prop, 0, 0);
                                    if (hr == S_OK) {
                                        cpu_id = _bstr_t(vt_prop.bstrVal);
                                        VariantClear(&vt_prop);
                                    }

                                    p_cls_obj->Release();
                                }

                                p_enumerator->Release();
                            }
                        }
                    }
                }

                if (p_svc) {
                    p_svc->Release();
                }
                if (p_loc) {
                    p_loc->Release();
                }

                CoUninitialize();
            }
        }

        return cpu_id;
    }

    std::string MACAddressProvider::get_mac_address() {
        std::string mac_address;

        if (CoInitializeEx(0, COINIT_MULTITHREADED) == S_OK) {
            if (CoInitializeSecurity(
                nullptr,
                -1,
                nullptr,
                nullptr,
                RPC_C_AUTHN_LEVEL_DEFAULT,
                RPC_C_IMP_LEVEL_IMPERSONATE,
                nullptr,
                EOAC_NONE,
                nullptr) == S_OK) {

                IWbemLocator* p_loc = nullptr;
                IWbemServices* p_svc = nullptr;

                if (CoCreateInstance(
                    CLSID_WbemLocator,
                    0,
                    CLSCTX_INPROC_SERVER,
                    IID_IWbemLocator,
                    reinterpret_cast<LPVOID*>(&p_loc)) == S_OK) {

                    if (p_loc->ConnectServer(
                        BSTR(L"ROOT\\CIMV2"),
                        nullptr,
                        nullptr,
                        nullptr,
                        0,
                        nullptr,
                        nullptr,
                        &p_svc) == S_OK) {

                        if (CoSetProxyBlanket(
                            p_svc,
                            RPC_C_AUTHN_WINNT,
                            RPC_C_AUTHZ_NONE,
                            nullptr,
                            RPC_C_AUTHN_LEVEL_CALL,
                            RPC_C_IMP_LEVEL_IMPERSONATE,
                            nullptr,
                            EOAC_NONE) == S_OK) {

                            IEnumWbemClassObject* p_enumerator = nullptr;

                            if (p_svc->ExecQuery(
                                BSTR(L"WQL"),
                                BSTR(L"SELECT * FROM Win32_NetworkAdapterConfiguration WHERE IPEnabled = true"),
                                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                                nullptr,
                                &p_enumerator) == S_OK) {

                                IWbemClassObject* p_cls_obj = nullptr;
                                ULONG u_return = 0;

                                while (p_enumerator) {
                                    HRESULT hr = p_enumerator->Next(WBEM_INFINITE, 1, &p_cls_obj, &u_return);
                                    if (u_return == 0) {
                                        break;
                                    }

                                    VARIANT vt_prop;
                                    hr = p_cls_obj->Get(L"MACAddress", 0, &vt_prop, 0, 0);
                                    if (hr == S_OK) {
                                        mac_address = _bstr_t(vt_prop.bstrVal);
                                        VariantClear(&vt_prop);
                                        break;
                                    }

                                    p_cls_obj->Release();
                                }

                                p_enumerator->Release();
                            }
                        }
                    }
                }

                if (p_svc) {
                    p_svc->Release();
                }
                if (p_loc) {
                    p_loc->Release();
                }

                CoUninitialize();
            }
        }

        return mac_address;
    }

    std::string CombinedHWIDProvider::get_combined_hwid() {
        std::string cpu_id = CPUIDProvider::get_cpu_id();
        std::string mac_address = MACAddressProvider::get_mac_address();

        std::string combined_hwid = cpu_id.substr(0, 4) + mac_address.substr(0, 7);

        return combined_hwid;
    }
}
