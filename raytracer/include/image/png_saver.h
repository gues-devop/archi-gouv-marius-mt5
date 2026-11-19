#pragma once

#include "image/image_saver.h"

class PngSaver : public ImageSaver {
public:
    void save(Image& image, const std::filesystem::path& outputPath) override;
};
