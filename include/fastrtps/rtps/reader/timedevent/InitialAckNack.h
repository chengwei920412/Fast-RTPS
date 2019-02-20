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

/**
 * @file InitialAckNack.h
 *
 */

#ifndef INITIALACKNACK_H_
#define INITIALACKNACK_H_

#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC

#include <fastrtps/rtps/resources/TimedEvent.h>
#include <fastrtps/rtps/messages/RTPSMessageGroup.h>

namespace eprosima {
namespace fastrtps {
namespace rtps {

class WriterProxy;
class RTPSParticipantImpl;

/**
 * InitialAckNack class, controls the initial send operation of AckNack.
 * @ingroup WRITER_MODULE
 */
class InitialAckNack : public TimedEvent
{
    public:

        /**
         * Constructs a InitialAckNack event object
         * @param participant   Pointer to the participant creating this event.
         * @param writer_proxy  Pointer to the writer this event should be associated to.
         */
        InitialAckNack(
                RTPSParticipantImpl* participant,
                WriterProxy* writer_proxy);

        virtual ~InitialAckNack();

        /**
         * Method invoked when the event occurs
         *
         * @param code Code representing the status of the event
         * @param msg Message associated to the event
         */
        void event(
                EventCode code,
                const char* msg= nullptr);

        //!
        RTPSMessageGroup_t message_buffer_;
        //!
        WriterProxy* writer_proxy_;
};

} /* namespace rtps */
} /* namespace fastrtps */
} /* namespace eprosima */

#endif
#endif /* INITIALACKNACK_H_ */
