// SPDX-License-Identifier: MPL-2.0
// Copyright © 2020 Skyline Team and Contributors (https://github.com/skyline-emu/)

#include <kernel/types/KProcess.h>
#include "IRequest.h"

namespace skyline::service::nifm {
    IRequest::IRequest(const DeviceState &state, ServiceManager &manager) : event0(std::make_shared<type::KEvent>(state)), event1(std::make_shared<type::KEvent>(state)), BaseService(state, manager, {
        {0x0, SFUNC(IRequest::GetRequestState)},
        {0x1, SFUNC(IRequest::GetResult)},
        {0x2, SFUNC(IRequest::GetSystemEventReadableHandles)},
        {0x4, SFUNC(IRequest::Submit)},
    }) {}

    Result IRequest::GetRequestState(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response) {
        constexpr u32 Unsubmitted = 1; //!< The request has not been submitted
        response.Push<u32>(Unsubmitted);
        return {};
    }

    Result IRequest::GetResult(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response) {
        return {};
    }

    Result IRequest::GetSystemEventReadableHandles(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response) {
        auto handle = state.process->InsertItem(event0);
        state.logger->Debug("Request Event 0 Handle: 0x{:X}", handle);
        response.copyHandles.push_back(handle);

        handle = state.process->InsertItem(event1);
        state.logger->Debug("Request Event 1 Handle: 0x{:X}", handle);
        response.copyHandles.push_back(handle);

        return {};
    }

    Result IRequest::Submit(type::KSession &session, ipc::IpcRequest &request, ipc::IpcResponse &response) {
        return {};
    }
}
