#include "FileHandler.h"

void manifest::getManifestFormatVersion() {
    switch (manifestformatversion) {
    case manifest_format_version::FORMAT_VERSION_1:
        manifestversion = 1;
        break;
    case manifest_format_version::FORMAT_VERSION_2:
        manifestversion = 2;
        break;
    }
    IF_DEF_DEBUG
        logger->success("Manifest version: "); log(manifestversion);
    END_IF_DEBUG
}

void RP::filter(_STD string& toBeFiltered, _STD unique_ptr<FilterReturnType> &pointer) {
    _STD string getThisOut("\pack.mcmeta"); // Remove pack.mcmeta from path
    _STD string filtered;
    size_t sizeToErase = (toBeFiltered.size() - getThisOut.length());
    size_t mcMetaNotExists = toBeFiltered.find(getThisOut);

    if (mcMetaNotExists == _STD string::npos) {
        logger->error("Can't find pack.mcmeta!");
        pointer->mcMetaExists = false;
        return;
    }
    else if (mcMetaNotExists != _STD string::npos)
    {
        pointer->mcMetaExists = true;
        if (sizeToErase != _STD string::npos) {
            filtered = toBeFiltered.erase(sizeToErase, getThisOut.length());
            pointer->filteredString = filtered;
            pointer->filteredSuccess = true;
            logger->success("Filtered successfully."); 
            return;
        }
        else {
            logger->error("Error! Can't filtered string. Either it does not exist, or program broken.");
            pointer->filteredSuccess = false;
            return;
        }
    }
}

void MCMETA::getmcMetaFile() {
    OPENFILENAME mcMetaFile;
    ZeroMemory(&this->filename, sizeof(this->filename));
    ZeroMemory(&mcMetaFile, sizeof(mcMetaFile));
    mcMetaFile.lStructSize = sizeof(mcMetaFile);
    mcMetaFile.hwndOwner = NULL;
    mcMetaFile.lpstrFilter = "mcmeta files\0*.mcmeta\0Any File\0*.*\0";
    mcMetaFile.lpstrFile = this->filename;
    mcMetaFile.nMaxFile = MAX_PATH;
    mcMetaFile.lpstrTitle = "Please select the pack.mcmeta file.";
    mcMetaFile.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameA(&mcMetaFile))
    {
        std::cout << "Found mcmeta file at: " << this->filename << newline;
        this->f_getMcMeta = true;
    }
    else
    {
        return;
    }
}

bool RP::getManifest() {
    // Temp values
    manifest manifest;
    _STD string __versionTemp__;
    _STD string __formatVersionTemp__;

    std::cout << getProjectName() << "Enter your pack name: ";
    std::getline(std::cin, manifest.name);

    std::cout << getProjectName() << "Enter your pack description: ";
    std::getline(std::cin, manifest.description);

    std::cout << getProjectName() << "Enter your pack version: ";
    std::getline(std::cin, __versionTemp__);

    std::cout << getProjectName() << "Enter your pack format version (1 or 2): ";
    std::getline(std::cin, __formatVersionTemp__);

    RP_TRY
    int formatversion = std::stoi(__formatVersionTemp__);

    if (formatversion > 2 || formatversion == 0) {
        logger->error("Please select 1 or 2.");
        return false;
    }
    if (formatversion <= 2 || formatversion != 0) {
        switch (formatversion) {
        case 1:
            manifest.manifestformatversion = static_cast<manifest_format_version>(formatversion);
            logger->success("Set manifest format version to 1!");
            break;
        case 2:
            manifest.manifestformatversion = static_cast<manifest_format_version>(formatversion);
            logger->success("Set manifest format version to 2!");
            break;
        }

        manifest.getManifestFormatVersion();
        return true;
    }
    RP_TRY_END RP_CATCH_EXCEPTION logger->error(e.what()); return false; RP_CATCH_EXCEPTION_END
}

bool RP::scan(fs::path const& path) {
    for (auto& dir : fs::recursive_directory_iterator(path)) { //recursive_
        if (dir.path().stem() == ".git") // ignore git folders
            continue;

        if (dir.is_directory()) {
            scan(dir.path());
            std::cout << dir.path();
            listDirectories.push_back(dir.path().string());
            system("cls");
        }
    } return true;
}

void RP::fileCopy(_STD string &file, _STD string &source, _STD string &destination) {
    for (int i = 0; i < source.size(); i++)
    {
        if (source[i] == '\\')
            source[i] = '/';
    }
    for (int i = 0; i < destination.size(); i++)
    {
        if (destination[i] == '\\')
            destination[i] == '/';
    }
    if (source[source.size() - 1] != '/')
        source.push_back('/');
    source = source + file;
    if (destination[destination.size() - 1] != '/')
        destination.push_back('/');
    destination = destination + file;

    std::ifstream sourceFile(source.c_str(), std::ios::binary);
    if (sourceFile)
    {
        std::ifstream idestination(destination.c_str());
        if (idestination)
        {
            IF_DEF_DEBUG
            std::cout << file << " already exist, Do you want to replace? [Yes/No] : ";
            END_IF_DEBUG
            std::string choice;
            std::getline(std::cin, choice);
            if (choice == "Y" || choice == "yes" || choice == "Yes" || choice == "YES" || choice == "y")
            {
                idestination.close();
                std::ofstream destinationFile(destination.c_str(), std::ios::binary);
                std::string line;
                while (std::getline(sourceFile, line))
                {
                    destinationFile << line << std::endl;
                }
                destinationFile.flush();
                destinationFile.close();
                IF_DEF_DEBUG
                std::cout << std::endl << "File copied successfully" << std::endl;
                END_IF_DEBUG
            }
            else
            {
                IF_DEF_DEBUG
                std::cout << "Exiting...........";
                END_IF_DEBUG
                idestination.close();
            }
        }
        else
        {
            idestination.close();
            std::ofstream destinationFile(destination.c_str(), std::ios::binary);
            std::string line;
            while (getline(sourceFile, line))
            {
                destinationFile << line << newline;
            }
            destinationFile.flush();
            destinationFile.close();
            IF_DEF_DEBUG
            std::cout << std::endl << "File copied successfully" << newline;
            END_IF_DEBUG
        }
        sourceFile.close();
    }
    else
    {
        IF_DEF_DEBUG
        std::cout << std::endl << "[ERROR]:-" << newline;
        std::cout << "Not able to locate " << source << newline;
        END_IF_DEBUG
    }
}

