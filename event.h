#ifndef EVENT_H
#define EVENT_H

class Event
{

};
class Request : public Event
{
    int mails{};
public:
    explicit Request(int mails) : mails{mails}{};
};
class BusinessTrip : public Request
{
    double durationtime{};
public:
    BusinessTrip(int mails, double dt) :
        Request(mails), durationtime{dt}{}
};

#endif // EVENT_H
