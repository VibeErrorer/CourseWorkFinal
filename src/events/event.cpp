#include "events/event.h"
#include <sstream>

std::string Event::GetDescription() const { return "Unknown event"; }

std::string PrintRequest::GetDescription() const {
    std::ostringstream stream;
    stream << "Print request: " << GetQuantity() << " letter(s)";
    return stream.str();
}

std::string DeliveryRequest::GetDescription() const {
    std::ostringstream stream;
    stream << "Delivery request: " << GetQuantity() << " letter(s)";
    return stream.str();
}

BusinessTrip::BusinessTrip(int mails, int days, std::string locationName, std::string requiredEmployeeType)
    : Event(TypeEvent::BusinessTrip, mails)
    , location{ std::move(locationName) }
    , requiredType{ std::move(requiredEmployeeType) }
    , tripDays{ days }
    , durationTrip{ std::chrono::hours(24 * days) }
{
}

std::string BusinessTrip::GetDescription() const {
    std::ostringstream stream;
    stream << "Business trip to " << location
        << " (" << tripDays << " day(s), "
        << GetQuantity() << " letter(s))";
    return stream.str();
}