#pragma once
#include "Common.h"
#include "Logger.h"
inline _STD vector<_STD string> listDirectories;

enum class manifest_format_version {
    FORMAT_VERSION_1 = 1,
    FORMAT_VERSION_2
};

struct manifest {
    _STD string name, description, UUID1, UUID2;
    int version, min_engine_version, manifestversion;
    bool platform_locked{};
    manifest_format_version manifestformatversion;

    void getManifestFormatVersion();
};

struct FilterReturnType {
    _STD string filteredString;
    bool mcMetaExists{};
    bool filteredSuccess{};
}; 	

struct MCMETA {
    char filename[RP_MAX_PATH];
    bool f_getMcMeta = false;
    void getmcMetaFile();
}; 

namespace RP {
    bool getManifest();
    void filter(_STD string& toBeFiltered, _STD unique_ptr<FilterReturnType> &pointer);
    bool scan(fs::path const& path);
    void fileCopy(_STD string &file, _STD string &source, _STD string &destination);
}

#define _RP RP::










