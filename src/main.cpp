// =============================================================================
// main.cpp — точка входа: компания, сотрудники, задачи дня, симуляция
// =============================================================================

#include <chrono>
#include <memory>

#include "core/company.h"
#include "employees/auto_memory_doll.h"
#include "employees/mail_man.h"
#include "events/event.h"

int main()
{
    using std::chrono::minutes;
    using std::chrono::milliseconds;

    Company company{ "C.H. Company", "Claudia", "Hodgins" };

    company.GetBoss().Hire(std::make_unique<AutoMemoryDoll>("Violet", "Evergarden", minutes(2), milliseconds(0)));
    company.GetBoss().Hire(std::make_unique<AutoMemoryDoll>("Cattleya", "Baudelaire", minutes(3), milliseconds(0)));
    company.GetBoss().Hire(std::make_unique<AutoMemoryDoll>("Erica", "Brown", minutes(4), milliseconds(0)));
    company.GetBoss().Hire(std::make_unique<AutoMemoryDoll>("Iris", "Cannary", minutes(4), milliseconds(0)));
    company.GetBoss().Hire(std::make_unique<MailMan>("Benedict", "Blue", minutes(2), milliseconds(0)));
    company.GetBoss().Hire(std::make_unique<MailMan>("Roland", "", minutes(3), milliseconds(0)));

    company.SortByRole();

    auto& boss = company.GetBoss();

    boss.AddTask(std::make_unique<PrintRequest>(10));
    boss.AddTask(std::make_unique<PrintRequest>(25));
    boss.AddTask(std::make_unique<DeliveryRequest>(40));
    boss.AddTask(std::make_unique<DeliveryRequest>(30));
    boss.AddTask(std::make_unique<PrintRequest>(15));
    boss.AddTask(std::make_unique<BusinessTrip>(2, 1, "Leiden", "AutoMemoryDoll"));
    boss.AddTask(std::make_unique<DeliveryRequest>(10));
    boss.AddTask(std::make_unique<BusinessTrip>(3, 3, "Drossel", "AutoMemoryDoll"));
    boss.AddTask(std::make_unique<PrintRequest>(13));
    boss.AddTask(std::make_unique<PrintRequest>(110));
    boss.AddTask(std::make_unique<DeliveryRequest>(20));

    Statistic statistic;

    company.Simulate(1);

    boss.AddTask(std::make_unique<PrintRequest>(50));
    boss.AddTask(std::make_unique<PrintRequest>(10));
    boss.AddTask(std::make_unique<DeliveryRequest>(10));
    boss.AddTask(std::make_unique<DeliveryRequest>(30));
    boss.AddTask(std::make_unique<PrintRequest>(40));
    boss.AddTask(std::make_unique<DeliveryRequest>(40));
    boss.AddTask(std::make_unique<PrintRequest>(10));
    boss.AddTask(std::make_unique<PrintRequest>(5));
    boss.AddTask(std::make_unique<DeliveryRequest>(5));

    company.Simulate(2);

    boss.AddTask(std::make_unique<PrintRequest>(50));
    boss.AddTask(std::make_unique<PrintRequest>(10));
    boss.AddTask(std::make_unique<DeliveryRequest>(10));
    boss.AddTask(std::make_unique<DeliveryRequest>(30));
    boss.AddTask(std::make_unique<PrintRequest>(40));
    boss.AddTask(std::make_unique<DeliveryRequest>(40));
    boss.AddTask(std::make_unique<PrintRequest>(10));
    boss.AddTask(std::make_unique<PrintRequest>(5));
    boss.AddTask(std::make_unique<DeliveryRequest>(5));

    company.Simulate(3);

    boss.AddTask(std::make_unique<PrintRequest>(10));
    boss.AddTask(std::make_unique<PrintRequest>(60));
    boss.AddTask(std::make_unique<DeliveryRequest>(150));
    boss.AddTask(std::make_unique<DeliveryRequest>(110));
    boss.AddTask(std::make_unique<PrintRequest>(70));
    boss.AddTask(std::make_unique<DeliveryRequest>(10));
    boss.AddTask(std::make_unique<PrintRequest>(5));
    boss.AddTask(std::make_unique<PrintRequest>(3));
    boss.AddTask(std::make_unique<DeliveryRequest>(5));

    company.Simulate(4);

    boss.AddTask(std::make_unique<PrintRequest>(5));
    boss.AddTask(std::make_unique<PrintRequest>(4));
    boss.AddTask(std::make_unique<DeliveryRequest>(50));
    boss.AddTask(std::make_unique<DeliveryRequest>(10));
    boss.AddTask(std::make_unique<PrintRequest>(62));
    boss.AddTask(std::make_unique<DeliveryRequest>(5));
    boss.AddTask(std::make_unique<PrintRequest>(25));
    boss.AddTask(std::make_unique<PrintRequest>(2));
    boss.AddTask(std::make_unique<DeliveryRequest>(1));

    company.Simulate(5);

    boss.AddTask(std::make_unique<PrintRequest>(3));
    boss.AddTask(std::make_unique<PrintRequest>(7));
    boss.AddTask(std::make_unique<DeliveryRequest>(15));
    boss.AddTask(std::make_unique<DeliveryRequest>(12));
    boss.AddTask(std::make_unique<PrintRequest>(45));
    boss.AddTask(std::make_unique<DeliveryRequest>(43));
    boss.AddTask(std::make_unique<PrintRequest>(33));
    boss.AddTask(std::make_unique<PrintRequest>(2));
    boss.AddTask(std::make_unique<DeliveryRequest>(1));

    company.Simulate(6);

    boss.AddTask(std::make_unique<BusinessTrip>(25, 7, "Flugel", "AutoMemoryDoll"));
    boss.AddTask(std::make_unique<PrintRequest>(19));
    boss.AddTask(std::make_unique<PrintRequest>(47));
    boss.AddTask(std::make_unique<DeliveryRequest>(22));
    boss.AddTask(std::make_unique<DeliveryRequest>(37));
    boss.AddTask(std::make_unique<PrintRequest>(90));
    boss.AddTask(std::make_unique<DeliveryRequest>(131));
    boss.AddTask(std::make_unique<PrintRequest>(170));
    boss.AddTask(std::make_unique<PrintRequest>(59));
    boss.AddTask(std::make_unique<DeliveryRequest>(70));

    company.Simulate(7);

    return 0;
}
