/**
 * meta.h
 *
 * Class for a meta event.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_EVENT_META_h
#define MIDI_EVENT_META_h

#include <iostream>
#include <cppmidi/event.h>
#include <cppmidi/vlvalue.h>

/**
 * Setting up the basic namespace.
 */
namespace Midi {
    namespace Events {
        /* Enum to maintain all the possible Meta events, to prevent meta events with invalid
         * types to exist.
         */
        enum MetaType {
            SEQUENCE_NUMBER = 0x00,
            TEXT = 0x01,
            COPYRIGHT = 0x02,
            NAME_TRACK = 0x03,
            NAME_INSTRUMENT = 0x04,
            TEXT_LYRIC = 0x05,
            TEXT_MARKER = 0x06,
            CUE = 0x07,
            CHANNEL_PREFIX_ASSIGNMENT = 0x20,
            EOT = 0x2F,
            TEMPO = 0x51,
            SMPTE_OFFSET = 0x54,
            SIGNATURE_TIME = 0x58,
            SIGNATURE_KEY = 0x59,
            SPECIFIC = 0x7F
        };

        class Meta : public Event {
            public:
                /**
                 * Creates a metaevent with type t. Length should be plus one, because there
                 * is a fixed header for this event (0xFF).
                 * @param t The type of metaevent to create.
                 */
                Meta(MetaType t) : Event(), _type(t), _dataSize(0) { }

                /**
                 * Destructor.
                 */
                virtual ~Meta() {}

                /**
                 * Function which prints this event.
                 * @param output The output stream to print to.
                 * @return std::ostream& The original output stream.
                 */
                virtual std::ostream& print(std::ostream& output) const;

                /**
                 * Method to clone the event, should be implemented by derived classes.
                 * @returns Event* the cloned event pointer, which is dynamically allocated.
                 */
                virtual Event* clone() const {
                    return new Meta(*this);
                }

                /**
                 * Method which tries to pop a Meta object from the input stream.
                 * Returns NULL if it cannot be popped, otherwise it will return a dynamically allocated
                 * Event*. If NULL is returned, the guarantee is made that the stream is not modified.* @param input The input stream.
                 * @return Event* A dynamically allocated event.
                 */
                static Event* popEvent(std::istream &input);

                /**
                 * Method which adds the current data length plus the usual length of
                 * this event.
                 * @return uint32_t The total length in bytes of this sysex event.
                 */
                virtual uint32_t getLength() const { return Event::getLength() + 2 + _dataSize.getLength() + _data.size(); }
            private:
                /**
                 * Private Meta constructor.
                 */
                Meta() : Event(), _dataSize(0) { }

                /**
                 * The type of this meta event.
                 * @var uint8_t
                 */
                uint8_t _type;

                /**
                 * The VLValue with the length of the data.
                 * @var VLValue
                 */
                VLValue _dataSize;

                /**
                 * Variable to hold the data for the meta event.
                 * @var uint8_t
                 */
                std::vector<uint8_t> _data;
        };
    }
}

#endif
