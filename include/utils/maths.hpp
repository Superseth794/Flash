//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_MATHS_HPP
#define FLASH_MATHS_HPP

#include <cmath>
#include <chrono>
#include <ostream>

#ifndef M_E
#   define M_E 2.71828182845904523536028747135266250 //> e
#endif

#ifndef M_LOG2E
#   define M_LOG2E 1.44269504088896340735992468100189214 //> log2(e)
#endif

#ifndef M_LOG10E
#   define M_LOG10E 0.434294481903251827651128918916605082 //> log10(e)
#endif

#ifndef M_LN2
#   define M_LN2 0.693147180559945309417232121458176568 //> ln(2)
#endif

#ifndef M_LN10
#   define M_LN10 2.30258509299404568401799145468436421 //> ln(10)
#endif

#ifndef M_PI
#   define M_PI 3.14159265358979323846264338327950288 //> pi
#endif

#ifndef M_PI_2
#   define M_PI_2 1.57079632679489661923132169163975144 //> pi/2
#endif

#ifndef M_PI_4
#   define M_PI_4 0.785398163397448309615660845819875721 //> pi/4
#endif

#ifndef M_1_PI
#   define M_1_PI 0.318309886183790671537767526745028724 //> 1/pi
#endif

#ifndef M_2_PI
#   define M_2_PI 0.636619772367581343075535053490057448 //> 2/pi
#endif

#ifndef M_PI2
#   define M_PI2 9.869604401089358618834490999876151135 //> pi^2
#endif

#ifndef M_PI3
#   define M_PI3 31.006276680299820175476315067101395202 //> pi^3
#endif

#ifndef M_SQRTPI
#   define M_SQRTPI 1.7724538509055160272981674833411451827 //> sqrt(pi)
#endif

#ifndef M_1_SQRTPI
#   define M_1_SQRTPI 0.5641895835477562869480794515607725858 //> 1/sqrt(pi)
#endif

#ifndef M_2_SQRTPI
#   define M_2_SQRTPI 1.12837916709551257389615890312154517 //> 2/sqrt(pi)
#endif

#ifndef M_SQRT2
#   define M_SQRT2 1.41421356237309504880168872420969808 //> sqrt(2)
#endif

#ifndef M_1_SQRT2
#   define M_1_SQRT2 0.707106781186547524400844362104849039 //> 1/sqrt(2)
#endif

#ifndef M_SQRT3
#   define M_SQRT3 1.732050807568877293527446341505872366 //> sqrt(3)
#endif

#ifndef M_1_SQRT3
#   define M_1_SQRT3 0.577350269189625764509148780501957455 //> 1/sqrt(3)
#endif

#define M_EPSILON 1e-3

namespace flash {

struct Time {
    long long microseconds;
    long long milliseconds;
    long long seconds;
    long long minutes;
};

template <typename T, typename ...Arg>
bool near(T x, Arg ...args) {
    static_assert((std::is_convertible_v<T, Arg> && ...));
    return ((std::abs(x - static_cast<T>(args)) < M_EPSILON) && ...);
}

template <typename R, typename P>
Time getTime(std::chrono::duration<R, P> duration) {
    using D = std::chrono::duration<R, P>;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= D(minutes);

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= D(seconds);

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= D(milliseconds);

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);

    return Time {
        microseconds.count(),
        milliseconds.count(),
        seconds.count(),
        minutes.count()
    };
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& os, flash::Time const& time) {
    os << time.minutes << "min " << time.seconds << "s " << time.milliseconds << "ms "<< time.microseconds << "µs ";
    return os;
}

}

#endif //FLASH_MATHS_HPP
