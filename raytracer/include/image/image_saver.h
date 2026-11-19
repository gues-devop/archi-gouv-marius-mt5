#pragma once

#include "image/image.h"

#include <filesystem>

class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    virtual void save(Image& image, const std::filesystem::path& outputPath) = 0;
};
