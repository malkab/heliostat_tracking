#include "TrackerTarget.h"

TrackerTarget::TrackerTarget()
{
    aimingType = global;
    aimingPoint = vec3d(0.f, 0.f, 100.f);
    angles = vec2d(0.f, 0.f);
}

TrackerTarget::~TrackerTarget()
{

}
