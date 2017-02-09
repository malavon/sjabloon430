#ifndef MYLIBRARY_COMPAT_HPP_
#define MYLIBRARY_COMPAT_HPP_

/**
 * Make sure there's a decltype operator, since it makes using the templates a lot easier. Won't do anything on C++11.
 */
#ifndef decltype
#define decltype(__x) __typeof__(__x)
#endif

#endif /* MYLIBRARY_COMPAT_HPP_ */
