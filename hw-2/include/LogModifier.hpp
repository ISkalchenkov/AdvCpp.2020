#ifndef LOG_MODIFIER_HPP
#define LOG_MODIFIER_HPP

#include <string>
#include <sstream>

#include "BaseLogger.hpp"

namespace log {

enum class Modification {
    OFF,
    ON
};

class LogModifier {
public:
    static LogModifier& get_instance() noexcept;
    void set_color_mod(Modification mod) noexcept;

    void set_weight_mod(Modification mod) noexcept;

    void set_time_mod(Modification mod) noexcept;
    void set_all_mod(Modification mod) noexcept;
    std::string formate(const std::string msg, Level lvl) noexcept;

private:
    Modification color_;

    Modification weight_;
    Modification time_;

    LogModifier() noexcept;
    ~LogModifier() = default;

    void time_fmt(std::ostringstream& fmt_message);
    void weight_fmt(std::ostringstream& fmt_message);
    void color_fmt(std::ostringstream& fmt_message, Level lvl);
    void level_fmt(std::ostringstream& fmt_message, Level lvl);
};

} // namespace log

#endif // LOG_MODIFIER_HPP