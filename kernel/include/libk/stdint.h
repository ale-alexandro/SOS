#ifndef LIBK_STDINT_H
#define LIBK_STDINT_H

typedef unsigned char   uint8_t;
typedef char            int8_t;
typedef unsigned short  uint16_t;
typedef short           int16_t;
typedef unsigned int    uint32_t;
typedef int	            int32_t;

typedef uint32_t        size_t;

/* Minimum of signed integral types.  */
# define INT8_MIN                 (-128)
# define INT16_MIN                (-32767-1)
# define INT32_MIN                (-2147483647-1)
# define INT64_MIN                (-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types.  */
# define INT8_MAX                 (127)
# define INT16_MAX                (32767)
# define INT32_MAX                (2147483647)
# define INT64_MAX                (__INT64_C(9223372036854775807))
/* Maximum of unsigned integral types.  */
# define UINT8_MAX                 (255)
# define UINT16_MAX                (65535)
# define UINT32_MAX                (4294967295U)
# define UINT64_MAX                (__UINT64_C(18446744073709551615))
#endif
