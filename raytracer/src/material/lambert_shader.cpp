#include "material/lambert_shader.h"

#include "geometry/hit_info.h"
#include "light/light.h"

#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(
    const HitInfo& hitInfo,
    const Vector& toLight
) const {
    const double brightness =
        std::max(0.0, hitInfo.normal.dot(toLight));

    return Colour(
        _colour.r() * brightness,
        _colour.g() * brightness,
        _colour.b() * brightness
    );
}

Colour LambertShader::shade(
    const HitInfo& hitInfo,
    const Light& light
) const {
    const Vector directionToLight = light.position() - hitInfo.point;
    const double distanceToLight = directionToLight.length();
    if (distanceToLight == 0) {
        return Colour(0, 0, 0);
    }

    const Vector toLight = directionToLight * (1.0 / distanceToLight);
    const Colour surfaceColour = shade(hitInfo, toLight);
    return Colour(
        surfaceColour.r() * light.colour().r(),
        surfaceColour.g() * light.colour().g(),
        surfaceColour.b() * light.colour().b()
    );
}
