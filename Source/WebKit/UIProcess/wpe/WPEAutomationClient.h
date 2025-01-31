/*
 * Copyright (C) 2018 Metrological
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(REMOTE_INSPECTOR)
#include "APIAutomationClient.h"
#include "WebProcessPool.h"
#include <JavaScriptCore/RemoteInspector.h>

namespace WebKit {

class WPEAutomationClient final : Inspector::RemoteInspector::Client {
public:
    explicit WPEAutomationClient(WebProcessPool& processPool, API::AutomationClient& client)
        : m_processPool(processPool)
        , m_client(client)
    {
        Inspector::RemoteInspector::singleton().setClient(this);
    }

    ~WPEAutomationClient()
    {
        Inspector::RemoteInspector::singleton().setClient(nullptr);
    }

private:
    bool remoteAutomationAllowed() const override
    {
        return m_client.allowsRemoteAutomation(&m_processPool);
    }

    void requestAutomationSession(const String& sessionIdentifier, const SessionCapabilities&) override
    {
        m_client.didRequestAutomationSession(&m_processPool, sessionIdentifier);
    }

    String browserName() const override
    {
        return m_client.browserName(&m_processPool);
    }

    String browserVersion() const override
    {
        return m_client.browserVersion(&m_processPool);
    }


    WebProcessPool& m_processPool;
    API::AutomationClient& m_client;
};

} // namespace WebKit

#endif // ENABLE(REMOTE_INSPECTOR)
