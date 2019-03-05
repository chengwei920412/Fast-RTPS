// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <MockTransport.h>
#include <algorithm>
#include <cstring>

using namespace std;

namespace eprosima{
namespace fastrtps{
namespace rtps{

std::vector<MockTransport*> MockTransport::mockTransportInstances;

MockTransport::MockTransport(const MockTransportDescriptor& descriptor)
    : TransportInterface(descriptor.supportedKind)
    , mockMaximumChannels(descriptor.maximumChannels)
{
    mockTransportInstances.push_back(this);
}

MockTransport::MockTransport()
    : TransportInterface(DefaultKind)
    , mockMaximumChannels(DefaultMaxChannels)
{
    mockTransportInstances.push_back(this);
}

MockTransport::~MockTransport()
{
    // Remove this mock from the handle vector
    mockTransportInstances.erase(std::remove(mockTransportInstances.begin(),
                                       mockTransportInstances.end(),
                                       this),
                                mockTransportInstances.end());
}

bool MockTransport::init()
{
    return true;
}

bool MockTransport::IsInputChannelOpen(const Locator_t& locator) const
{
    return (find(mockOpenInputChannels.begin(), mockOpenInputChannels.end(), locator.port) != mockOpenInputChannels.end());
}

bool MockTransport::IsLocatorSupported(const Locator_t& locator) const
{
    return locator.kind == transport_kind_;
}

bool MockTransport::is_locator_allowed(const Locator_t& /*locator*/) const
{
    return true;
}

bool MockTransport::OpenOutputChannel(
        SendResourceList& sender_resource_list,
        const Locator_t& locator)
{
    mockOpenOutputChannels.push_back(locator.port);
    return true;
}

bool MockTransport::OpenInputChannel(
        const Locator_t& locator,
        TransportReceiverInterface*, uint32_t)
{
    mockOpenInputChannels.push_back(locator.port);
    return true;
}

bool MockTransport::DoInputLocatorsMatch(
        const Locator_t& left,
        const Locator_t& right) const
{
    return left.port == right.port;
}

bool MockTransport::DoOutputLocatorsMatch(
        const Locator_t&,
        const Locator_t&) const
{
    return true;
}

Locator_t MockTransport::RemoteToMainLocal(const Locator_t& remote) const
{
    Locator_t mainLocal(remote);
    //memset(mainLocal.address, 0x00, sizeof(mainLocal.address));
    mainLocal.set_Invalid_Address();
    return mainLocal;
}

bool MockTransport::CloseInputChannel(const Locator_t& locator)
{
   mockOpenInputChannels.erase(std::remove(mockOpenInputChannels.begin(),
                                      mockOpenInputChannels.end(),
                                      locator.port),
                                mockOpenInputChannels.end());
   return true;
}

LocatorList_t MockTransport::NormalizeLocator(const Locator_t& locator)
{
    LocatorList_t list;
    list.push_back(locator);
    return list;
}

LocatorList_t MockTransport::ShrinkLocatorLists(const std::vector<LocatorList_t>& locatorLists)
{
    LocatorList_t result;

    for(auto locatorList : locatorLists)
        result.push_back(locatorList);

    return result;
}

} // namespace rtps
} // namespace fastrtps
} // namespace eprosima
