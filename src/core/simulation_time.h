// =============================================================================
// simulation_time.h — масштаб времени: 1 симулированный час = 1 реальная секунда
// =============================================================================

#ifndef SIMULATION_TIME_H
#define SIMULATION_TIME_H

#include <chrono>

namespace SimTime {

constexpr int kSimHoursPerRealSecond = 1;
constexpr int kWorkDayHours = 8;
constexpr int kSimSecondsPerSimHour = 3600;

inline std::chrono::seconds WorkDayRealDuration()
{
    return std::chrono::seconds(kWorkDayHours / kSimHoursPerRealSecond);
}

// Перевод симулированной длительности в реальное время ожидания.
template <typename Rep, typename Period>
std::chrono::milliseconds ToReal(std::chrono::duration<Rep, Period> simulatedDuration)
{
    using namespace std::chrono;
    const auto simulatedSeconds = duration_cast<seconds>(simulatedDuration);
    const auto realMilliseconds =
        (simulatedSeconds.count() * milliseconds(1000).count()) / kSimSecondsPerSimHour;
    return milliseconds(realMilliseconds);
}

} // namespace SimTime

#endif // SIMULATION_TIME_H
