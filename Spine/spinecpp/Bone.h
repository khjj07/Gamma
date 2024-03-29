////////////////////////////////////////////////////////////////////////////////
// Spine Runtimes Software License
// Version 2.4
//
// Copyright (c) 2013-2016, Esoteric Software
// Copyright (c) 2016, Chobolabs
// All rights reserved.
//
// You are granted a perpetual, non-exclusive, non-sublicensable and
// non-transferable license to use, install, execute and perform the Spine
// Runtimes Software (the "Software") and derivative works solely for personal
// or internal use. Without the written permission of Esoteric Software (see
// Section 2 of the Spine Software License Agreement), you may not (a) modify,
// translate, adapt or otherwise create derivative works, improvements of
// the Software or develop new applications using the Software or (b) remove,
// delete, alter or obscure any trademarks or any copyright, trademark, patent
// or other intellectual property or proprietary rights notices on or in the
// Software, including any copy thereof. Redistributions in binary or source
// form must include this license and terms.
//
// THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE AND CHOBOLABS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE OR CHOBOLABS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "spinecpp/BoneData.h"
#include <vector>

namespace spine
{

class Skeleton;

struct Bone
{
public:
    static void setYDown(bool yDown);
    static bool isYDown();

    Bone(const BoneData& data, const Skeleton& skeleton, Bone* parent);

    const std::string& getName() const { return data.name; }

    void setToSetupPose();
    void updateWorldTransform();
    void updateWorldTransformWith(Vector translation, float rotation, Vector scale, Vector shear);

    float getWorldRotationX() const;
    float getWorldRotationY() const;
    float getWorldScaleX() const;
    float getWorldScaleY() const;

    float worldToLocalRotationX() const;
    float worldToLocalRotationY() const;

    void rotateWorld(float degrees);
    void updateLocalTransform();

    void worldToLocal(Vector world, Vector& outLocal);
    void localToWorld(Vector local, Vector& outWorld);

    bool isRoot() const { return !parent; }

    // links
    const BoneData& data;
    const Skeleton& skeleton;
    Bone* const parent;
    std::vector<Bone*> children;

    // Logical data

    // user data
    Vector translation;
    float rotation;
    Vector scale;
    Vector shear;

    float appliedRotation;

    // Physical data

    // world tranform 2x2 matrix
    float a, b;
    float c, d;

    Vector worldPos;
    Vector worldSign;

    // Internal data
    int/*bool*/ sorted;

private:
    static bool m_isYDown;
};

}
