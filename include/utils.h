#ifndef UTILS_H
#define UTILS_H

#define STR2(a) STR(a)
#define STR(x) #x

#define __unused __attribute__((unused))
#define __funused __attribute__((maybe_unused))
#define __deprecated(msg) __attribute__((deprecated(msg)))
#define __packed __attribute__((packed))
#define __aligned(x) __attribute__((aligned(x)))
#define __noreturn __attribute__((noreturn))
#define __unreachable __builtin_unreachable();

#endif
