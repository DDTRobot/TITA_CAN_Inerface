
#ifndef CANFD_PROTOCOL__VISIBILITY_CONTROL_HPP_
#define CANFD_PROTOCOL__VISIBILITY_CONTROL_HPP_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define SOCKETCAN_EXPORT __attribute__((dllexport))
#define SOCKETCAN_IMPORT __attribute__((dllimport))
#else
#define SOCKETCAN_EXPORT __declspec(dllexport)
#define SOCKETCAN_IMPORT __declspec(dllimport)
#endif
#ifdef SOCKETCAN_BUILDING_LIBRARY
#define SOCKETCAN_PUBLIC SOCKETCAN_EXPORT
#else
#define SOCKETCAN_PUBLIC SOCKETCAN_IMPORT
#endif
#define SOCKETCAN_PUBLIC_TYPE SOCKETCAN_PUBLIC
#define SOCKETCAN_LOCAL
#else
#define SOCKETCAN_EXPORT __attribute__((visibility("default")))
#define SOCKETCAN_IMPORT
#if __GNUC__ >= 4
#define SOCKETCAN_PUBLIC __attribute__((visibility("default")))
#define SOCKETCAN_LOCAL __attribute__((visibility("hidden")))
#else
#define SOCKETCAN_PUBLIC
#define SOCKETCAN_LOCAL
#endif
#define SOCKETCAN_PUBLIC_TYPE
#endif

#endif  // CANFD_PROTOCOL__VISIBILITY_CONTROL_HPP_
