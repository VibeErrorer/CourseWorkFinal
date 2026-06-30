#ifndef EVENT_H
#define EVENT_H

#include <chrono>
#include <memory>   
#include <string>

#include "events/event_types.h"

class Event
{
    TypeEvent type;
    int quantity{};

public:
    Event() = default;
    Event(TypeEvent type, int mails) : type{ type }, quantity{ mails } {}
    virtual ~Event() = default;

    TypeEvent GetType() const { return type; }
    int GetQuantity() const { return quantity; }
    void SetQuantity(int q) { quantity = q; }  

    virtual std::chrono::seconds GetDuration() const { return std::chrono::seconds(0); }
    virtual std::string GetDescription() const;

    // создаёт копию события с другим количеством
    virtual std::unique_ptr<Event> CreateWithQuantity(int newQuantity) const = 0;
};

class PrintRequest : public Event
{
public:
    explicit PrintRequest(int mails) : Event(TypeEvent::PrintRequest, mails) {}
    std::string GetDescription() const override;

    std::unique_ptr<Event> CreateWithQuantity(int newQuantity) const override {
        return std::make_unique<PrintRequest>(newQuantity);
    }
};

class DeliveryRequest : public Event
{
public:
    explicit DeliveryRequest(int mails) : Event(TypeEvent::DeliveryRequest, mails) {}
    std::string GetDescription() const override;

    std::unique_ptr<Event> CreateWithQuantity(int newQuantity) const override {
        return std::make_unique<DeliveryRequest>(newQuantity);
    }
};

class BusinessTrip : public Event
{
    std::string location;
    std::string requiredType;
    int tripDays;
    std::chrono::seconds durationTrip;

public:
    BusinessTrip(int mails, int days, std::string locationName, std::string requiredEmployeeType);

    int GetTripDays() const { return tripDays; }
    const std::string& GetLocation() const { return location; }
    const std::string& GetRequiredType() const { return requiredType; }

    std::chrono::seconds GetDuration() const override { return durationTrip; }
    std::string GetDescription() const override;

    std::unique_ptr<Event> CreateWithQuantity(int newQuantity) const override {
        return std::make_unique<BusinessTrip>(newQuantity, tripDays, location, requiredType);
    }
};

#endif // EVENT_H