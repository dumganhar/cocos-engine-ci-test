/****************************************************************************
 Copyright (c) 2019-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#import "gfx-base/GFXQueue.h"

namespace cc {
namespace gfx {
struct CCMTLGPUQueueObject;
class CCMTLQueue final : public Queue {
    friend class CCMTLDevice;

public:
    explicit CCMTLQueue();
    ~CCMTLQueue();
    CCMTLQueue(const CCMTLQueue &) = delete;
    CCMTLQueue(CCMTLQueue &&) = delete;
    CCMTLQueue &operator=(const CCMTLQueue &) = delete;
    CCMTLQueue &operator=(CCMTLQueue &&) = delete;

    void submit(CommandBuffer *const *cmdBuffs, uint32_t count) override;

    inline CCMTLGPUQueueObject *gpuQueueObj() { return _gpuQueueObj; }

protected:
    void doInit(const QueueInfo &info) override;
    void doDestroy() override;

    CCMTLGPUQueueObject *_gpuQueueObj = nullptr;
};

} // namespace gfx
} // namespace cc
