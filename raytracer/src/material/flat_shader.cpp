#include "material/flat_shader.h"

#include "geometry/hit_info.h"
#include "light/light.h"

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(
    const HitInfo& hitInfo,
    const Vector& toLight
) const {
    (void)hitInfo;
    (void)toLight;
    return _colour;
}

Colour FlatShader::shade(
    const HitInfo& hitInfo,
    const Light& light
) const {
    (void)hitInfo;
    (void)light;
    return _colour;
}
