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

#include "Attachment.h"

namespace spine
{

class Skin;

class AttachmentLoader
{
public:
    virtual ~AttachmentLoader() {}

    std::string error1;
    std::string error2;

    // Called to create each attachment. Returns 0 to not load an attachment. If 0 is returned and setError was
    // called, an error occurred.
    Attachment* createAttachment(const Skin& skin, Attachment::Type type, const std::string& name, const std::string& path);

    // Called after the attachment has been fully loaded, for custom configuration by the user
    // Use it to set the loader, if you want onDestroyingAttachment to be called for it
    virtual void configureAttachment(Attachment* attachment) {}

    // Called just before the attachment is destroyed. Use it to release allocations made in configureAttachment.
    virtual void onDestroyingAttachment(Attachment* attachment) {}

protected:
    virtual Attachment* createAttachmentImpl(const Skin& skin, Attachment::Type type, const std::string& name, const std::string& path) = 0;

    void setError(const std::string& e1, const std::string& e2);
    void setUnknownTypeError(Attachment::Type type);
};

}
