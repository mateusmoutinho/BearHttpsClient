/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef INNER_H__
#define INNER_H__

#include <string.h>
#include <limits.h>

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CONFIG_H__
#define CONFIG_H__

/*
 * This file contains compile-time flags that can override the
 * autodetection performed in relevant files. Each flag is a macro; it
 * deactivates the feature if defined to 0, activates it if defined to a
 * non-zero integer (normally 1). If the macro is not defined, then
 * autodetection applies.
 */

/*
 * When BR_64 is enabled, 64-bit integer types are assumed to be
 * efficient (i.e. the architecture has 64-bit registers and can
 * do 64-bit operations as fast as 32-bit operations).
 *
#define BR_64   1
 */

/*
 * When BR_LOMUL is enabled, then multiplications of 32-bit values whose
 * result are truncated to the low 32 bits are assumed to be
 * substantially more efficient than 32-bit multiplications that yield
 * 64-bit results. This is typically the case on low-end ARM Cortex M
 * systems (M0, M0+, M1, and arguably M3 and M4 as well).
 *
#define BR_LOMUL   1
 */

/*
 * When BR_SLOW_MUL is enabled, multiplications are assumed to be
 * substantially slow with regards to other integer operations, thus
 * making it worth to make more operations for a given task if it allows
 * using less multiplications.
 *
#define BR_SLOW_MUL   1
 */

/*
 * When BR_SLOW_MUL15 is enabled, short multplications (on 15-bit words)
 * are assumed to be substantially slow with regards to other integer
 * operations, thus making it worth to make more integer operations if
 * it allows using less multiplications.
 *
#define BR_SLOW_MUL15   1
 */

/*
 * When BR_CT_MUL31 is enabled, multiplications of 31-bit values (used
 * in the "i31" big integer implementation) use an alternate implementation
 * which is slower and larger than the normal multiplication, but should
 * ensure constant-time multiplications even on architectures where the
 * multiplication opcode takes a variable number of cycles to complete.
 *
#define BR_CT_MUL31   1
 */

/*
 * When BR_CT_MUL15 is enabled, multiplications of 15-bit values (held
 * in 32-bit words) use an alternate implementation which is slower and
 * larger than the normal multiplication, but should ensure
 * constant-time multiplications on most/all architectures where the
 * basic multiplication is not constant-time.
#define BR_CT_MUL15   1
 */

/*
 * When BR_NO_ARITH_SHIFT is enabled, arithmetic right shifts (with sign
 * extension) are performed with a sequence of operations which is bigger
 * and slower than a simple right shift on a signed value. This avoids
 * relying on an implementation-defined behaviour. However, most if not
 * all C compilers use sign extension for right shifts on signed values,
 * so this alternate macro is disabled by default.
#define BR_NO_ARITH_SHIFT   1
 */

/*
 * When BR_RDRAND is enabled, the SSL engine will use the RDRAND opcode
 * to automatically obtain quality randomness for seeding its internal
 * PRNG. Since that opcode is present only in recent x86 CPU, its
 * support is dynamically tested; if the current CPU does not support
 * it, then another random source will be used, such as /dev/urandom or
 * CryptGenRandom().
 *
#define BR_RDRAND   1
 */

/*
 * When BR_USE_GETENTROPY is enabled, the SSL engine will use the
 * getentropy() function to obtain quality randomness for seeding its
 * internal PRNG. On Linux and FreeBSD, getentropy() is implemented by
 * the standard library with the system call getrandom(); on OpenBSD,
 * getentropy() is the system call, and there is no getrandom() wrapper,
 * hence the use of the getentropy() function for maximum portability.
 *
 * If the getentropy() call fails, and BR_USE_URANDOM is not explicitly
 * disabled, then /dev/urandom will be used as a fallback mechanism. On
 * FreeBSD and OpenBSD, this does not change much, since /dev/urandom
 * will block if not enough entropy has been obtained since last boot.
 * On Linux, /dev/urandom might not block, which can be troublesome in
 * early boot stages, which is why getentropy() is preferred.
 *
#define BR_USE_GETENTROPY   1
 */

/*
 * When BR_USE_URANDOM is enabled, the SSL engine will use /dev/urandom
 * to automatically obtain quality randomness for seeding its internal
 * PRNG.
 *
#define BR_USE_URANDOM   1
 */

/*
 * When BR_USE_WIN32_RAND is enabled, the SSL engine will use the Win32
 * (CryptoAPI) functions (CryptAcquireContext(), CryptGenRandom()...) to
 * automatically obtain quality randomness for seeding its internal PRNG.
 *
 * Note: if both BR_USE_URANDOM and BR_USE_WIN32_RAND are defined, the
 * former takes precedence.
 *
#define BR_USE_WIN32_RAND   1
 */

/*
 * When BR_USE_UNIX_TIME is enabled, the X.509 validation engine obtains
 * the current time from the OS by calling time(), and assuming that the
 * returned value (a 'time_t') is an integer that counts time in seconds
 * since the Unix Epoch (Jan 1st, 1970, 00:00 UTC).
 *
#define BR_USE_UNIX_TIME   1
 */

/*
 * When BR_USE_WIN32_TIME is enabled, the X.509 validation engine obtains
 * the current time from the OS by calling the Win32 function
 * GetSystemTimeAsFileTime().
 *
 * Note: if both BR_USE_UNIX_TIME and BR_USE_WIN32_TIME are defined, the
 * former takes precedence.
 *
#define BR_USE_WIN32_TIME   1
 */

/*
 * When BR_ARMEL_CORTEXM_GCC is enabled, some operations are replaced with
 * inline assembly which is shorter and/or faster. This should be used
 * only when all of the following are true:
 *   - target architecture is ARM in Thumb mode
 *   - target endianness is little-endian
 *   - compiler is GCC (or GCC-compatible for inline assembly syntax)
 *
 * This is meant for the low-end cores (Cortex M0, M0+, M1, M3).
 * Note: if BR_LOMUL is not explicitly enabled or disabled, then
 * enabling BR_ARMEL_CORTEXM_GCC also enables BR_LOMUL.
 *
#define BR_ARMEL_CORTEXM_GCC   1
 */

/*
 * When BR_AES_X86NI is enabled, the AES implementation using the x86 "NI"
 * instructions (dedicated AES opcodes) will be compiled. If this is not
 * enabled explicitly, then that AES implementation will be compiled only
 * if a compatible compiler is detected. If set explicitly to 0, the
 * implementation will not be compiled at all.
 *
#define BR_AES_X86NI   1
 */

/*
 * When BR_SSE2 is enabled, SSE2 intrinsics will be used for some
 * algorithm implementations that use them (e.g. chacha20_sse2). If this
 * is not enabled explicitly, then support for SSE2 intrinsics will be
 * automatically detected. If set explicitly to 0, then SSE2 code will
 * not be compiled at all.
 *
#define BR_SSE2   1
 */

/*
 * When BR_POWER8 is enabled, the AES implementation using the POWER ISA
 * 2.07 opcodes (available on POWER8 processors and later) is compiled.
 * If this is not enabled explicitly, then that implementation will be
 * compiled only if a compatible compiler is detected, _and_ the target
 * architecture is POWER8 or later.
 *
#define BR_POWER8   1
 */

/*
 * When BR_INT128 is enabled, then code using the 'unsigned __int64'
 * and 'unsigned __int128' types will be used to leverage 64x64->128
 * unsigned multiplications. This should work with GCC and compatible
 * compilers on 64-bit architectures.
 *
#define BR_INT128   1
 */

/*
 * When BR_UMUL128 is enabled, then code using the '_umul128()' and
 * '_addcarry_u64()' intrinsics will be used to implement 64x64->128
 * unsigned multiplications. This should work on Visual C on x64 systems.
 *
#define BR_UMUL128   1
 */

/*
 * When BR_LE_UNALIGNED is enabled, then the current architecture is
 * assumed to use little-endian encoding for integers, and to tolerate
 * unaligned accesses with no or minimal time penalty.
 *
#define BR_LE_UNALIGNED   1
 */

/*
 * When BR_BE_UNALIGNED is enabled, then the current architecture is
 * assumed to use big-endian encoding for integers, and to tolerate
 * unaligned accesses with no or minimal time penalty.
 *
#define BR_BE_UNALIGNED   1
 */

#endif

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_H__
#define BR_BEARSSL_H__

#include <stddef.h>
#include <stdint.h>

/** \mainpage BearSSL API
 *
 * # API Layout
 *
 * The functions and structures defined by the BearSSL API are located
 * in various header files:
 *
 * | Header file     | Elements                                          |
 * | :-------------- | :------------------------------------------------ |
 * | bearssl_hash.h  | Hash functions                                    |
 * | bearssl_hmac.h  | HMAC                                              |
 * | bearssl_kdf.h   | Key Derivation Functions                          |
 * | bearssl_rand.h  | Pseudorandom byte generators                      |
 * | bearssl_prf.h   | PRF implementations (for SSL/TLS)                 |
 * | bearssl_block.h | Symmetric encryption                              |
 * | bearssl_aead.h  | AEAD algorithms (combined encryption + MAC)       |
 * | bearssl_rsa.h   | RSA encryption and signatures                     |
 * | bearssl_ec.h    | Elliptic curves support (including ECDSA)         |
 * | bearssl_ssl.h   | SSL/TLS engine interface                          |
 * | bearssl_x509.h  | X.509 certificate decoding and validation         |
 * | bearssl_pem.h   | Base64/PEM decoding support functions             |
 *
 * Applications using BearSSL are supposed to simply include `bearssl.h`
 * as follows:
 *
 *     #include <bearssl.h>
 *
 * The `bearssl.h` file itself includes all the other header files. It is
 * possible to include specific header files, but it has no practical
 * advantage for the application. The API is separated into separate
 * header files only for documentation convenience.
 *
 *
 * # Conventions
 *
 * ## MUST and SHALL
 *
 * In all descriptions, the usual "MUST", "SHALL", "MAY",... terminology
 * is used. Failure to meet requirements expressed with a "MUST" or
 * "SHALL" implies undefined behaviour, which means that segmentation
 * faults, buffer overflows, and other similar adverse events, may occur.
 *
 * In general, BearSSL is not very forgiving of programming errors, and
 * does not include much failsafes or error reporting when the problem
 * does not arise from external transient conditions, and can be fixed
 * only in the application code. This is done so in order to make the
 * total code footprint lighter.
 *
 *
 * ## `NULL` values
 *
 * Function parameters with a pointer type shall not be `NULL` unless
 * explicitly authorised by the documentation. As an exception, when
 * the pointer aims at a sequence of bytes and is accompanied with
 * a length parameter, and the length is zero (meaning that there is
 * no byte at all to retrieve), then the pointer may be `NULL` even if
 * not explicitly allowed.
 *
 *
 * ## Memory Allocation
 *
 * BearSSL does not perform dynamic memory allocation. This implies that
 * for any functionality that requires a non-transient state, the caller
 * is responsible for allocating the relevant context structure. Such
 * allocation can be done in any appropriate area, including static data
 * segments, the heap, and the stack, provided that proper alignment is
 * respected. The header files define these context structures
 * (including size and contents), so the C compiler should handle
 * alignment automatically.
 *
 * Since there is no dynamic resource allocation, there is also nothing to
 * release. When the calling code is done with a BearSSL feature, it
 * may simple release the context structures it allocated itself, with
 * no "close function" to call. If the context structures were allocated
 * on the stack (as local variables), then even that release operation is
 * implicit.
 *
 *
 * ## Structure Contents
 *
 * Except when explicitly indicated, structure contents are opaque: they
 * are included in the header files so that calling code may know the
 * structure sizes and alignment requirements, but callers SHALL NOT
 * access individual fields directly. For fields that are supposed to
 * be read from or written to, the API defines accessor functions (the
 * simplest of these accessor functions are defined as `static inline`
 * functions, and the C compiler will optimise them away).
 *
 *
 * # API Usage
 *
 * BearSSL usage for running a SSL/TLS client or server is described
 * on the [BearSSL Web site](https://www.bearssl.org/api1.html). The
 * BearSSL source archive also comes with sample code.
 */

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_HASH_H__
#define BR_BEARSSL_HASH_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_hash.h
 *
 * # Hash Functions
 *
 * This file documents the API for hash functions.
 *
 *
 * ## Procedural API
 *
 * For each implemented hash function, of name "`xxx`", the following
 * elements are defined:
 *
 *   - `br_xxx_vtable`
 *
 *     An externally defined instance of `br_hash_class`.
 *
 *   - `br_xxx_SIZE`
 *
 *     A macro that evaluates to the output size (in bytes) of the
 *     hash function.
 *
 *   - `br_xxx_ID`
 *
 *     A macro that evaluates to a symbolic identifier for the hash
 *     function. Such identifiers are used with HMAC and signature
 *     algorithm implementations.
 *
 *     NOTE: for the "standard" hash functions defined in [the TLS
 *     standard](https://tools.ietf.org/html/rfc5246#section-7.4.1.4.1),
 *     the symbolic identifiers match the constants used in TLS, i.e.
 *     1 to 6 for MD5, SHA-1, SHA-224, SHA-256, SHA-384 and SHA-512,
 *     respectively.
 *
 *   - `br_xxx_context`
 *
 *     Context for an ongoing computation. It is allocated by the
 *     caller, and a pointer to it is passed to all functions. A
 *     context contains no interior pointer, so it can be moved around
 *     and cloned (with a simple `memcpy()` or equivalent) in order to
 *     capture the function state at some point. Computations that use
 *     distinct context structures are independent of each other. The
 *     first field of `br_xxx_context` is always a pointer to the
 *     `br_xxx_vtable` structure; `br_xxx_init()` sets that pointer.
 *
 *   - `br_xxx_init(br_xxx_context *ctx)`
 *
 *     Initialise the provided context. Previous contents of the structure
 *     are ignored. This calls resets the context to the start of a new
 *     hash computation; it also sets the first field of the context
 *     structure (called `vtable`) to a pointer to the statically
 *     allocated constant `br_xxx_vtable` structure.
 *
 *   - `br_xxx_update(br_xxx_context *ctx, const void *data, size_t len)`
 *
 *     Add some more bytes to the hash computation represented by the
 *     provided context.
 *
 *   - `br_xxx_out(const br_xxx_context *ctx, void *out)`
 *
 *     Complete the hash computation and write the result in the provided
 *     buffer. The output buffer MUST be large enough to accommodate the
 *     result. The context is NOT modified by this operation, so this
 *     function can be used to get a "partial hash" while still keeping
 *     the possibility of adding more bytes to the input.
 *
 *   - `br_xxx_state(const br_xxx_context *ctx, void *out)`
 *
 *     Get a copy of the "current state" for the computation so far. For
 *     MD functions (MD5, SHA-1, SHA-2 family), this is the running state
 *     resulting from the processing of the last complete input block.
 *     Returned value is the current input length (in bytes).
 *
 *   - `br_xxx_set_state(br_xxx_context *ctx, const void *stb, uint64_t count)`
 *
 *     Set the internal state to the provided values. The 'stb' and
 *     'count' values shall match that which was obtained from
 *     `br_xxx_state()`. This restores the hash state only if the state
 *     values were at an appropriate block boundary. This does NOT set
 *     the `vtable` pointer in the context.
 *
 * Context structures can be discarded without any explicit deallocation.
 * Hash function implementations are purely software and don't reserve
 * any resources outside of the context structure itself.
 *
 *
 * ## Object-Oriented API
 *
 * For each hash function that follows the procedural API described
 * above, an object-oriented API is also provided. In that API, function
 * pointers from the vtable (`br_xxx_vtable`) are used. The vtable
 * incarnates object-oriented programming. An introduction on the OOP
 * concept used here can be read on the BearSSL Web site:<br />
 * &nbsp;&nbsp;&nbsp;[https://www.bearssl.org/oop.html](https://www.bearssl.org/oop.html)
 *
 * The vtable offers functions called `init()`, `update()`, `out()`,
 * `set()` and `set_state()`, which are in fact the functions from
 * the procedural API. That vtable also contains two informative fields:
 *
 *   - `context_size`
 *
 *     The size of the context structure (`br_xxx_context`), in bytes.
 *     This can be used by generic implementations to perform dynamic
 *     context allocation.
 *
 *   - `desc`
 *
 *     A "descriptor" field that encodes some information on the hash
 *     function: symbolic identifier, output size, state size,
 *     internal block size, details on the padding.
 *
 * Users of this object-oriented API (in particular generic HMAC
 * implementations) may make the following assumptions:
 *
 *   - Hash output size is no more than 64 bytes.
 *   - Hash internal state size is no more than 64 bytes.
 *   - Internal block size is a power of two, no less than 16 and no more
 *     than 256.
 *
 *
 * ## Implemented Hash Functions
 *
 * Implemented hash functions are:
 *
 * | Function  | Name    | Output length | State length |
 * | :-------- | :------ | :-----------: | :----------: |
 * | MD5       | md5     |     16        |     16       |
 * | SHA-1     | sha1    |     20        |     20       |
 * | SHA-224   | sha224  |     28        |     32       |
 * | SHA-256   | sha256  |     32        |     32       |
 * | SHA-384   | sha384  |     48        |     64       |
 * | SHA-512   | sha512  |     64        |     64       |
 * | MD5+SHA-1 | md5sha1 |     36        |     36       |
 *
 * (MD5+SHA-1 is the concatenation of MD5 and SHA-1 computed over the
 * same input; in the implementation, the internal data buffer is
 * shared, thus making it more memory-efficient than separate MD5 and
 * SHA-1. It can be useful in implementing SSL 3.0, TLS 1.0 and TLS
 * 1.1.)
 *
 *
 * ## Multi-Hasher
 *
 * An aggregate hasher is provided, that can compute several standard
 * hash functions in parallel. It uses `br_multihash_context` and a
 * procedural API. It is configured with the implementations (the vtables)
 * that it should use; it will then compute all these hash functions in
 * parallel, on the same input. It is meant to be used in cases when the
 * hash of an object will be used, but the exact hash function is not
 * known yet (typically, streamed processing on X.509 certificates).
 *
 * Only the standard hash functions (MD5, SHA-1, SHA-224, SHA-256, SHA-384
 * and SHA-512) are supported by the multi-hasher.
 *
 *
 * ## GHASH
 *
 * GHASH is not a generic hash function; it is a _universal_ hash function,
 * which, as the name does not say, means that it CANNOT be used in most
 * places where a hash function is needed. GHASH is used within the GCM
 * encryption mode, to provide the checked integrity functionality.
 *
 * A GHASH implementation is basically a function that uses the type defined
 * in this file under the name `br_ghash`:
 *
 *     typedef void (*br_ghash)(void *y, const void *h, const void *data, size_t len);
 *
 * The `y` pointer refers to a 16-byte value which is used as input, and
 * receives the output of the GHASH invocation. `h` is a 16-byte secret
 * value (that serves as key). `data` and `len` define the input data.
 *
 * Three GHASH implementations are provided, all constant-time, based on
 * the use of integer multiplications with appropriate masking to cancel
 * carry propagation.
 */

/**
 * \brief Class type for hash function implementations.
 *
 * A `br_hash_class` instance references the methods implementing a hash
 * function. Constant instances of this structure are defined for each
 * implemented hash function. Such instances are also called "vtables".
 *
 * Vtables are used to support object-oriented programming, as
 * described on [the BearSSL Web site](https://www.bearssl.org/oop.html).
 */
typedef struct br_hash_class_ br_hash_class;
struct br_hash_class_ {
	/**
	 * \brief Size (in bytes) of the context structure appropriate for
	 * computing this hash function.
	 */
	size_t context_size;

	/**
	 * \brief Descriptor word that contains information about the hash
	 * function.
	 *
	 * For each word `xxx` described below, use `BR_HASHDESC_xxx_OFF`
	 * and `BR_HASHDESC_xxx_MASK` to access the specific value, as
	 * follows:
	 *
	 *     (hf->desc >> BR_HASHDESC_xxx_OFF) & BR_HASHDESC_xxx_MASK
	 *
	 * The defined elements are:
	 *
	 *  - `ID`: the symbolic identifier for the function, as defined
	 *    in [TLS](https://tools.ietf.org/html/rfc5246#section-7.4.1.4.1)
	 *    (MD5 = 1, SHA-1 = 2,...).
	 *
	 *  - `OUT`: hash output size, in bytes.
	 *
	 *  - `STATE`: internal running state size, in bytes.
	 *
	 *  - `LBLEN`: base-2 logarithm for the internal block size, as
	 *    defined for HMAC processing (this is 6 for MD5, SHA-1, SHA-224
	 *    and SHA-256, since these functions use 64-byte blocks; for
	 *    SHA-384 and SHA-512, this is 7, corresponding to their
	 *    128-byte blocks).
	 *
	 * The descriptor may contain a few other flags.
	 */
	uint32_t desc;

	/**
	 * \brief Initialisation method.
	 *
	 * This method takes as parameter a pointer to a context area,
	 * that it initialises. The first field of the context is set
	 * to this vtable; other elements are initialised for a new hash
	 * computation.
	 *
	 * \param ctx   pointer to (the first field of) the context.
	 */
	void (*init)(const br_hash_class **ctx);

	/**
	 * \brief Data injection method.
	 *
	 * The `len` bytes starting at address `data` are injected into
	 * the running hash computation incarnated by the specified
	 * context. The context is updated accordingly. It is allowed
	 * to have `len == 0`, in which case `data` is ignored (and could
	 * be `NULL`), and nothing happens.
	 * on the input data.
	 *
	 * \param ctx    pointer to (the first field of) the context.
	 * \param data   pointer to the first data byte to inject.
	 * \param len    number of bytes to inject.
	 */
	void (*update)(const br_hash_class **ctx, const void *data, size_t len);

	/**
	 * \brief Produce hash output.
	 *
	 * The hash output corresponding to all data bytes injected in the
	 * context since the last `init()` call is computed, and written
	 * in the buffer pointed to by `dst`. The hash output size depends
	 * on the implemented hash function (e.g. 16 bytes for MD5).
	 * The context is _not_ modified by this call, so further bytes
	 * may be afterwards injected to continue the current computation.
	 *
	 * \param ctx   pointer to (the first field of) the context.
	 * \param dst   destination buffer for the hash output.
	 */
	void (*out)(const br_hash_class *const *ctx, void *dst);

	/**
	 * \brief Get running state.
	 *
	 * This method saves the current running state into the `dst`
	 * buffer. What constitutes the "running state" depends on the
	 * hash function; for Merkle-Damgård hash functions (like
	 * MD5 or SHA-1), this is the output obtained after processing
	 * each block. The number of bytes injected so far is returned.
	 * The context is not modified by this call.
	 *
	 * \param ctx   pointer to (the first field of) the context.
	 * \param dst   destination buffer for the state.
	 * \return  the injected total byte length.
	 */
	uint64_t (*state)(const br_hash_class *const *ctx, void *dst);

	/**
	 * \brief Set running state.
	 *
	 * This methods replaces the running state for the function.
	 *
	 * \param ctx     pointer to (the first field of) the context.
	 * \param stb     source buffer for the state.
	 * \param count   injected total byte length.
	 */
	void (*set_state)(const br_hash_class **ctx,
		const void *stb, uint64_t count);
};

#ifndef BR_DOXYGEN_IGNORE
#define BR_HASHDESC_ID(id)           ((uint32_t)(id) << BR_HASHDESC_ID_OFF)
#define BR_HASHDESC_ID_OFF           0
#define BR_HASHDESC_ID_MASK          0xFF

#define BR_HASHDESC_OUT(size)        ((uint32_t)(size) << BR_HASHDESC_OUT_OFF)
#define BR_HASHDESC_OUT_OFF          8
#define BR_HASHDESC_OUT_MASK         0x7F

#define BR_HASHDESC_STATE(size)      ((uint32_t)(size) << BR_HASHDESC_STATE_OFF)
#define BR_HASHDESC_STATE_OFF        15
#define BR_HASHDESC_STATE_MASK       0xFF

#define BR_HASHDESC_LBLEN(ls)        ((uint32_t)(ls) << BR_HASHDESC_LBLEN_OFF)
#define BR_HASHDESC_LBLEN_OFF        23
#define BR_HASHDESC_LBLEN_MASK       0x0F

#define BR_HASHDESC_MD_PADDING       ((uint32_t)1 << 28)
#define BR_HASHDESC_MD_PADDING_128   ((uint32_t)1 << 29)
#define BR_HASHDESC_MD_PADDING_BE    ((uint32_t)1 << 30)
#endif

/*
 * Specific hash functions.
 *
 * Rules for contexts:
 * -- No interior pointer.
 * -- No pointer to external dynamically allocated resources.
 * -- First field is called 'vtable' and is a pointer to a
 *    const-qualified br_hash_class instance (pointer is set by init()).
 * -- SHA-224 and SHA-256 contexts are identical.
 * -- SHA-384 and SHA-512 contexts are identical.
 *
 * Thus, contexts can be moved and cloned to capture the hash function
 * current state; and there is no need for any explicit "release" function.
 */

/**
 * \brief Symbolic identifier for MD5.
 */
#define br_md5_ID     1

/**
 * \brief MD5 output size (in bytes).
 */
#define br_md5_SIZE   16

/**
 * \brief Constant vtable for MD5.
 */
extern const br_hash_class br_md5_vtable;

/**
 * \brief MD5 context.
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/**
	 * \brief Pointer to vtable for this context.
	 */
	const br_hash_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	unsigned char buf[64];
	uint64_t count;
	uint32_t val[4];
#endif
} br_md5_context;

/**
 * \brief MD5 context initialisation.
 *
 * This function initialises or resets a context for a new MD5
 * computation. It also sets the vtable pointer.
 *
 * \param ctx   pointer to the context structure.
 */
void br_md5_init(br_md5_context *ctx);

/**
 * \brief Inject some data bytes in a running MD5 computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_md5_update(br_md5_context *ctx, const void *data, size_t len);

/**
 * \brief Compute MD5 output.
 *
 * The MD5 output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `out`. The context
 * itself is not modified, so extra bytes may be injected afterwards
 * to continue that computation.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the hash output.
 */
void br_md5_out(const br_md5_context *ctx, void *out);

/**
 * \brief Save MD5 running state.
 *
 * The running state for MD5 (output of the last internal block
 * processing) is written in the buffer pointed to by `out`. The
 * number of bytes injected since the last initialisation or reset
 * call is returned. The context is not modified.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the running state.
 * \return  the injected total byte length.
 */
uint64_t br_md5_state(const br_md5_context *ctx, void *out);

/**
 * \brief Restore MD5 running state.
 *
 * The running state for MD5 is set to the provided values.
 *
 * \param ctx     pointer to the context structure.
 * \param stb     source buffer for the running state.
 * \param count   the injected total byte length.
 */
void br_md5_set_state(br_md5_context *ctx, const void *stb, uint64_t count);

/**
 * \brief Symbolic identifier for SHA-1.
 */
#define br_sha1_ID     2

/**
 * \brief SHA-1 output size (in bytes).
 */
#define br_sha1_SIZE   20

/**
 * \brief Constant vtable for SHA-1.
 */
extern const br_hash_class br_sha1_vtable;

/**
 * \brief SHA-1 context.
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/**
	 * \brief Pointer to vtable for this context.
	 */
	const br_hash_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	unsigned char buf[64];
	uint64_t count;
	uint32_t val[5];
#endif
} br_sha1_context;

/**
 * \brief SHA-1 context initialisation.
 *
 * This function initialises or resets a context for a new SHA-1
 * computation. It also sets the vtable pointer.
 *
 * \param ctx   pointer to the context structure.
 */
void br_sha1_init(br_sha1_context *ctx);

/**
 * \brief Inject some data bytes in a running SHA-1 computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_sha1_update(br_sha1_context *ctx, const void *data, size_t len);

/**
 * \brief Compute SHA-1 output.
 *
 * The SHA-1 output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `out`. The context
 * itself is not modified, so extra bytes may be injected afterwards
 * to continue that computation.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the hash output.
 */
void br_sha1_out(const br_sha1_context *ctx, void *out);

/**
 * \brief Save SHA-1 running state.
 *
 * The running state for SHA-1 (output of the last internal block
 * processing) is written in the buffer pointed to by `out`. The
 * number of bytes injected since the last initialisation or reset
 * call is returned. The context is not modified.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the running state.
 * \return  the injected total byte length.
 */
uint64_t br_sha1_state(const br_sha1_context *ctx, void *out);

/**
 * \brief Restore SHA-1 running state.
 *
 * The running state for SHA-1 is set to the provided values.
 *
 * \param ctx     pointer to the context structure.
 * \param stb     source buffer for the running state.
 * \param count   the injected total byte length.
 */
void br_sha1_set_state(br_sha1_context *ctx, const void *stb, uint64_t count);

/**
 * \brief Symbolic identifier for SHA-224.
 */
#define br_sha224_ID     3

/**
 * \brief SHA-224 output size (in bytes).
 */
#define br_sha224_SIZE   28

/**
 * \brief Constant vtable for SHA-224.
 */
extern const br_hash_class br_sha224_vtable;

/**
 * \brief SHA-224 context.
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/**
	 * \brief Pointer to vtable for this context.
	 */
	const br_hash_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	unsigned char buf[64];
	uint64_t count;
	uint32_t val[8];
#endif
} br_sha224_context;

/**
 * \brief SHA-224 context initialisation.
 *
 * This function initialises or resets a context for a new SHA-224
 * computation. It also sets the vtable pointer.
 *
 * \param ctx   pointer to the context structure.
 */
void br_sha224_init(br_sha224_context *ctx);

/**
 * \brief Inject some data bytes in a running SHA-224 computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_sha224_update(br_sha224_context *ctx, const void *data, size_t len);

/**
 * \brief Compute SHA-224 output.
 *
 * The SHA-224 output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `out`. The context
 * itself is not modified, so extra bytes may be injected afterwards
 * to continue that computation.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the hash output.
 */
void br_sha224_out(const br_sha224_context *ctx, void *out);

/**
 * \brief Save SHA-224 running state.
 *
 * The running state for SHA-224 (output of the last internal block
 * processing) is written in the buffer pointed to by `out`. The
 * number of bytes injected since the last initialisation or reset
 * call is returned. The context is not modified.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the running state.
 * \return  the injected total byte length.
 */
uint64_t br_sha224_state(const br_sha224_context *ctx, void *out);

/**
 * \brief Restore SHA-224 running state.
 *
 * The running state for SHA-224 is set to the provided values.
 *
 * \param ctx     pointer to the context structure.
 * \param stb     source buffer for the running state.
 * \param count   the injected total byte length.
 */
void br_sha224_set_state(br_sha224_context *ctx,
	const void *stb, uint64_t count);

/**
 * \brief Symbolic identifier for SHA-256.
 */
#define br_sha256_ID     4

/**
 * \brief SHA-256 output size (in bytes).
 */
#define br_sha256_SIZE   32

/**
 * \brief Constant vtable for SHA-256.
 */
extern const br_hash_class br_sha256_vtable;

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief SHA-256 context.
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/**
	 * \brief Pointer to vtable for this context.
	 */
	const br_hash_class *vtable;
} br_sha256_context;
#else
typedef br_sha224_context br_sha256_context;
#endif

/**
 * \brief SHA-256 context initialisation.
 *
 * This function initialises or resets a context for a new SHA-256
 * computation. It also sets the vtable pointer.
 *
 * \param ctx   pointer to the context structure.
 */
void br_sha256_init(br_sha256_context *ctx);

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief Inject some data bytes in a running SHA-256 computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_sha256_update(br_sha256_context *ctx, const void *data, size_t len);
#else
#define br_sha256_update      br_sha224_update
#endif

/**
 * \brief Compute SHA-256 output.
 *
 * The SHA-256 output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `out`. The context
 * itself is not modified, so extra bytes may be injected afterwards
 * to continue that computation.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the hash output.
 */
void br_sha256_out(const br_sha256_context *ctx, void *out);

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief Save SHA-256 running state.
 *
 * The running state for SHA-256 (output of the last internal block
 * processing) is written in the buffer pointed to by `out`. The
 * number of bytes injected since the last initialisation or reset
 * call is returned. The context is not modified.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the running state.
 * \return  the injected total byte length.
 */
uint64_t br_sha256_state(const br_sha256_context *ctx, void *out);
#else
#define br_sha256_state       br_sha224_state
#endif

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief Restore SHA-256 running state.
 *
 * The running state for SHA-256 is set to the provided values.
 *
 * \param ctx     pointer to the context structure.
 * \param stb     source buffer for the running state.
 * \param count   the injected total byte length.
 */
void br_sha256_set_state(br_sha256_context *ctx,
	const void *stb, uint64_t count);
#else
#define br_sha256_set_state   br_sha224_set_state
#endif

/**
 * \brief Symbolic identifier for SHA-384.
 */
#define br_sha384_ID     5

/**
 * \brief SHA-384 output size (in bytes).
 */
#define br_sha384_SIZE   48

/**
 * \brief Constant vtable for SHA-384.
 */
extern const br_hash_class br_sha384_vtable;

/**
 * \brief SHA-384 context.
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/**
	 * \brief Pointer to vtable for this context.
	 */
	const br_hash_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	unsigned char buf[128];
	uint64_t count;
	uint64_t val[8];
#endif
} br_sha384_context;

/**
 * \brief SHA-384 context initialisation.
 *
 * This function initialises or resets a context for a new SHA-384
 * computation. It also sets the vtable pointer.
 *
 * \param ctx   pointer to the context structure.
 */
void br_sha384_init(br_sha384_context *ctx);

/**
 * \brief Inject some data bytes in a running SHA-384 computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_sha384_update(br_sha384_context *ctx, const void *data, size_t len);

/**
 * \brief Compute SHA-384 output.
 *
 * The SHA-384 output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `out`. The context
 * itself is not modified, so extra bytes may be injected afterwards
 * to continue that computation.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the hash output.
 */
void br_sha384_out(const br_sha384_context *ctx, void *out);

/**
 * \brief Save SHA-384 running state.
 *
 * The running state for SHA-384 (output of the last internal block
 * processing) is written in the buffer pointed to by `out`. The
 * number of bytes injected since the last initialisation or reset
 * call is returned. The context is not modified.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the running state.
 * \return  the injected total byte length.
 */
uint64_t br_sha384_state(const br_sha384_context *ctx, void *out);

/**
 * \brief Restore SHA-384 running state.
 *
 * The running state for SHA-384 is set to the provided values.
 *
 * \param ctx     pointer to the context structure.
 * \param stb     source buffer for the running state.
 * \param count   the injected total byte length.
 */
void br_sha384_set_state(br_sha384_context *ctx,
	const void *stb, uint64_t count);

/**
 * \brief Symbolic identifier for SHA-512.
 */
#define br_sha512_ID     6

/**
 * \brief SHA-512 output size (in bytes).
 */
#define br_sha512_SIZE   64

/**
 * \brief Constant vtable for SHA-512.
 */
extern const br_hash_class br_sha512_vtable;

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief SHA-512 context.
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/**
	 * \brief Pointer to vtable for this context.
	 */
	const br_hash_class *vtable;
} br_sha512_context;
#else
typedef br_sha384_context br_sha512_context;
#endif

/**
 * \brief SHA-512 context initialisation.
 *
 * This function initialises or resets a context for a new SHA-512
 * computation. It also sets the vtable pointer.
 *
 * \param ctx   pointer to the context structure.
 */
void br_sha512_init(br_sha512_context *ctx);

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief Inject some data bytes in a running SHA-512 computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_sha512_update(br_sha512_context *ctx, const void *data, size_t len);
#else
#define br_sha512_update   br_sha384_update
#endif

/**
 * \brief Compute SHA-512 output.
 *
 * The SHA-512 output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `out`. The context
 * itself is not modified, so extra bytes may be injected afterwards
 * to continue that computation.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the hash output.
 */
void br_sha512_out(const br_sha512_context *ctx, void *out);

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief Save SHA-512 running state.
 *
 * The running state for SHA-512 (output of the last internal block
 * processing) is written in the buffer pointed to by `out`. The
 * number of bytes injected since the last initialisation or reset
 * call is returned. The context is not modified.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the running state.
 * \return  the injected total byte length.
 */
uint64_t br_sha512_state(const br_sha512_context *ctx, void *out);
#else
#define br_sha512_state   br_sha384_state
#endif

#ifdef BR_DOXYGEN_IGNORE
/**
 * \brief Restore SHA-512 running state.
 *
 * The running state for SHA-512 is set to the provided values.
 *
 * \param ctx     pointer to the context structure.
 * \param stb     source buffer for the running state.
 * \param count   the injected total byte length.
 */
void br_sha512_set_state(br_sha512_context *ctx,
	const void *stb, uint64_t count);
#else
#define br_sha512_set_state   br_sha384_set_state
#endif

/*
 * "md5sha1" is a special hash function that computes both MD5 and SHA-1
 * on the same input, and produces a 36-byte output (MD5 and SHA-1
 * concatenation, in that order). State size is also 36 bytes.
 */

/**
 * \brief Symbolic identifier for MD5+SHA-1.
 *
 * MD5+SHA-1 is the concatenation of MD5 and SHA-1, computed over the
 * same input. It is not one of the functions identified in TLS, so
 * we give it a symbolic identifier of value 0.
 */
#define br_md5sha1_ID     0

/**
 * \brief MD5+SHA-1 output size (in bytes).
 */
#define br_md5sha1_SIZE   36

/**
 * \brief Constant vtable for MD5+SHA-1.
 */
extern const br_hash_class br_md5sha1_vtable;

/**
 * \brief MD5+SHA-1 context.
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/**
	 * \brief Pointer to vtable for this context.
	 */
	const br_hash_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	unsigned char buf[64];
	uint64_t count;
	uint32_t val_md5[4];
	uint32_t val_sha1[5];
#endif
} br_md5sha1_context;

/**
 * \brief MD5+SHA-1 context initialisation.
 *
 * This function initialises or resets a context for a new SHA-512
 * computation. It also sets the vtable pointer.
 *
 * \param ctx   pointer to the context structure.
 */
void br_md5sha1_init(br_md5sha1_context *ctx);

/**
 * \brief Inject some data bytes in a running MD5+SHA-1 computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_md5sha1_update(br_md5sha1_context *ctx, const void *data, size_t len);

/**
 * \brief Compute MD5+SHA-1 output.
 *
 * The MD5+SHA-1 output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `out`. The context
 * itself is not modified, so extra bytes may be injected afterwards
 * to continue that computation.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the hash output.
 */
void br_md5sha1_out(const br_md5sha1_context *ctx, void *out);

/**
 * \brief Save MD5+SHA-1 running state.
 *
 * The running state for MD5+SHA-1 (output of the last internal block
 * processing) is written in the buffer pointed to by `out`. The
 * number of bytes injected since the last initialisation or reset
 * call is returned. The context is not modified.
 *
 * \param ctx   pointer to the context structure.
 * \param out   destination buffer for the running state.
 * \return  the injected total byte length.
 */
uint64_t br_md5sha1_state(const br_md5sha1_context *ctx, void *out);

/**
 * \brief Restore MD5+SHA-1 running state.
 *
 * The running state for MD5+SHA-1 is set to the provided values.
 *
 * \param ctx     pointer to the context structure.
 * \param stb     source buffer for the running state.
 * \param count   the injected total byte length.
 */
void br_md5sha1_set_state(br_md5sha1_context *ctx,
	const void *stb, uint64_t count);

/**
 * \brief Aggregate context for configurable hash function support.
 *
 * The `br_hash_compat_context` type is a type which is large enough to
 * serve as context for all standard hash functions defined above.
 */
typedef union {
	const br_hash_class *vtable;
	br_md5_context md5;
	br_sha1_context sha1;
	br_sha224_context sha224;
	br_sha256_context sha256;
	br_sha384_context sha384;
	br_sha512_context sha512;
	br_md5sha1_context md5sha1;
} br_hash_compat_context;

/*
 * The multi-hasher is a construct that handles hashing of the same input
 * data with several hash functions, with a single shared input buffer.
 * It can handle MD5, SHA-1, SHA-224, SHA-256, SHA-384 and SHA-512
 * simultaneously, though which functions are activated depends on
 * the set implementation pointers.
 */

/**
 * \brief Multi-hasher context structure.
 *
 * The multi-hasher runs up to six hash functions in the standard TLS list
 * (MD5, SHA-1, SHA-224, SHA-256, SHA-384 and SHA-512) in parallel, over
 * the same input.
 *
 * The multi-hasher does _not_ follow the OOP structure with a vtable.
 * Instead, it is configured with the vtables of the hash functions it
 * should run. Structure fields are not supposed to be accessed directly.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	unsigned char buf[128];
	uint64_t count;
	uint32_t val_32[25];
	uint64_t val_64[16];
	const br_hash_class *impl[6];
#endif
} br_multihash_context;

/**
 * \brief Clear a multi-hasher context.
 *
 * This should always be called once on a given context, _before_ setting
 * the implementation pointers.
 *
 * \param ctx   the multi-hasher context.
 */
void br_multihash_zero(br_multihash_context *ctx);

/**
 * \brief Set a hash function implementation.
 *
 * Implementations shall be set _after_ clearing the context (with
 * `br_multihash_zero()`) but _before_ initialising the computation
 * (with `br_multihash_init()`). The hash function implementation
 * MUST be one of the standard hash functions (MD5, SHA-1, SHA-224,
 * SHA-256, SHA-384 or SHA-512); it may also be `NULL` to remove
 * an implementation from the multi-hasher.
 *
 * \param ctx    the multi-hasher context.
 * \param id     the hash function symbolic identifier.
 * \param impl   the hash function vtable, or `NULL`.
 */
static inline void
br_multihash_setimpl(br_multihash_context *ctx,
	int id, const br_hash_class *impl)
{
	/*
	 * This code relies on hash functions ID being values 1 to 6,
	 * in the MD5 to SHA-512 order.
	 */
	ctx->impl[id - 1] = impl;
}

/**
 * \brief Get a hash function implementation.
 *
 * This function returns the currently configured vtable for a given
 * hash function (by symbolic ID). If no such function was configured in
 * the provided multi-hasher context, then this function returns `NULL`.
 *
 * \param ctx    the multi-hasher context.
 * \param id     the hash function symbolic identifier.
 * \return  the hash function vtable, or `NULL`.
 */
static inline const br_hash_class *
br_multihash_getimpl(const br_multihash_context *ctx, int id)
{
	return ctx->impl[id - 1];
}

/**
 * \brief Reset a multi-hasher context.
 *
 * This function prepares the context for a new hashing computation,
 * for all implementations configured at that point.
 *
 * \param ctx    the multi-hasher context.
 */
void br_multihash_init(br_multihash_context *ctx);

/**
 * \brief Inject some data bytes in a running multi-hashing computation.
 *
 * The provided context is updated with some data bytes. If the number
 * of bytes (`len`) is zero, then the data pointer (`data`) is ignored
 * and may be `NULL`, and this function does nothing.
 *
 * \param ctx    pointer to the context structure.
 * \param data   pointer to the injected data.
 * \param len    injected data length (in bytes).
 */
void br_multihash_update(br_multihash_context *ctx,
	const void *data, size_t len);

/**
 * \brief Compute a hash output from a multi-hasher.
 *
 * The hash output for the concatenation of all bytes injected in the
 * provided context since the last initialisation or reset call, is
 * computed and written in the buffer pointed to by `dst`. The hash
 * function to use is identified by `id` and must be one of the standard
 * hash functions. If that hash function was indeed configured in the
 * multi-hasher context, the corresponding hash value is written in
 * `dst` and its length (in bytes) is returned. If the hash function
 * was _not_ configured, then nothing is written in `dst` and 0 is
 * returned.
 *
 * The context itself is not modified, so extra bytes may be injected
 * afterwards to continue the hash computations.
 *
 * \param ctx   pointer to the context structure.
 * \param id    the hash function symbolic identifier.
 * \param dst   destination buffer for the hash output.
 * \return  the hash output length (in bytes), or 0.
 */
size_t br_multihash_out(const br_multihash_context *ctx, int id, void *dst);

/**
 * \brief Type for a GHASH implementation.
 *
 * GHASH is a sort of keyed hash meant to be used to implement GCM in
 * combination with a block cipher (with 16-byte blocks).
 *
 * The `y` array has length 16 bytes and is used for input and output; in
 * a complete GHASH run, it starts with an all-zero value. `h` is a 16-byte
 * value that serves as key (it is derived from the encryption key in GCM,
 * using the block cipher). The data length (`len`) is expressed in bytes.
 * The `y` array is updated.
 *
 * If the data length is not a multiple of 16, then the data is implicitly
 * padded with zeros up to the next multiple of 16. Thus, when using GHASH
 * in GCM, this method may be called twice, for the associated data and
 * for the ciphertext, respectively; the zero-padding implements exactly
 * the GCM rules.
 *
 * \param y      the array to update.
 * \param h      the GHASH key.
 * \param data   the input data (may be `NULL` if `len` is zero).
 * \param len    the input data length (in bytes).
 */
typedef void (*br_ghash)(void *y, const void *h, const void *data, size_t len);

/**
 * \brief GHASH implementation using multiplications (mixed 32-bit).
 *
 * This implementation uses multiplications of 32-bit values, with a
 * 64-bit result. It is constant-time (if multiplications are
 * constant-time).
 *
 * \param y      the array to update.
 * \param h      the GHASH key.
 * \param data   the input data (may be `NULL` if `len` is zero).
 * \param len    the input data length (in bytes).
 */
void br_ghash_ctmul(void *y, const void *h, const void *data, size_t len);

/**
 * \brief GHASH implementation using multiplications (strict 32-bit).
 *
 * This implementation uses multiplications of 32-bit values, with a
 * 32-bit result. It is usually somewhat slower than `br_ghash_ctmul()`,
 * but it is expected to be faster on architectures for which the
 * 32-bit multiplication opcode does not yield the upper 32 bits of the
 * product. It is constant-time (if multiplications are constant-time).
 *
 * \param y      the array to update.
 * \param h      the GHASH key.
 * \param data   the input data (may be `NULL` if `len` is zero).
 * \param len    the input data length (in bytes).
 */
void br_ghash_ctmul32(void *y, const void *h, const void *data, size_t len);

/**
 * \brief GHASH implementation using multiplications (64-bit).
 *
 * This implementation uses multiplications of 64-bit values, with a
 * 64-bit result. It is constant-time (if multiplications are
 * constant-time). It is substantially faster than `br_ghash_ctmul()`
 * and `br_ghash_ctmul32()` on most 64-bit architectures.
 *
 * \param y      the array to update.
 * \param h      the GHASH key.
 * \param data   the input data (may be `NULL` if `len` is zero).
 * \param len    the input data length (in bytes).
 */
void br_ghash_ctmul64(void *y, const void *h, const void *data, size_t len);

/**
 * \brief GHASH implementation using the `pclmulqdq` opcode (part of the
 * AES-NI instructions).
 *
 * This implementation is available only on x86 platforms where the
 * compiler supports the relevant intrinsic functions. Even if the
 * compiler supports these functions, the local CPU might not support
 * the `pclmulqdq` opcode, meaning that a call will fail with an
 * illegal instruction exception. To safely obtain a pointer to this
 * function when supported (or 0 otherwise), use `br_ghash_pclmul_get()`.
 *
 * \param y      the array to update.
 * \param h      the GHASH key.
 * \param data   the input data (may be `NULL` if `len` is zero).
 * \param len    the input data length (in bytes).
 */
void br_ghash_pclmul(void *y, const void *h, const void *data, size_t len);

/**
 * \brief Obtain the `pclmul` GHASH implementation, if available.
 *
 * If the `pclmul` implementation was compiled in the library (depending
 * on the compiler abilities) _and_ the local CPU appears to support the
 * opcode, then this function will return a pointer to the
 * `br_ghash_pclmul()` function. Otherwise, it will return `0`.
 *
 * \return  the `pclmul` GHASH implementation, or `0`.
 */
br_ghash br_ghash_pclmul_get(void);

/**
 * \brief GHASH implementation using the POWER8 opcodes.
 *
 * This implementation is available only on POWER8 platforms (and later).
 * To safely obtain a pointer to this function when supported (or 0
 * otherwise), use `br_ghash_pwr8_get()`.
 *
 * \param y      the array to update.
 * \param h      the GHASH key.
 * \param data   the input data (may be `NULL` if `len` is zero).
 * \param len    the input data length (in bytes).
 */
void br_ghash_pwr8(void *y, const void *h, const void *data, size_t len);

/**
 * \brief Obtain the `pwr8` GHASH implementation, if available.
 *
 * If the `pwr8` implementation was compiled in the library (depending
 * on the compiler abilities) _and_ the local CPU appears to support the
 * opcode, then this function will return a pointer to the
 * `br_ghash_pwr8()` function. Otherwise, it will return `0`.
 *
 * \return  the `pwr8` GHASH implementation, or `0`.
 */
br_ghash br_ghash_pwr8_get(void);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_HMAC_H__
#define BR_BEARSSL_HMAC_H__

#include <stddef.h>
#include <stdint.h>



#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_hmac.h
 *
 * # HMAC
 *
 * HMAC is initialized with a key and an underlying hash function; it
 * then fills a "key context". That context contains the processed
 * key.
 *
 * With the key context, a HMAC context can be initialized to process
 * the input bytes and obtain the MAC output. The key context is not
 * modified during that process, and can be reused.
 *
 * IMPORTANT: HMAC shall be used only with functions that have the
 * following properties:
 *
 *   - hash output size does not exceed 64 bytes;
 *   - hash internal state size does not exceed 64 bytes;
 *   - internal block length is a power of 2 between 16 and 256 bytes.
 */

/**
 * \brief HMAC key context.
 *
 * The HMAC key context is initialised with a hash function implementation
 * and a secret key. Contents are opaque (callers should not access them
 * directly). The caller is responsible for allocating the context where
 * appropriate. Context initialisation and usage incurs no dynamic
 * allocation, so there is no release function.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	const br_hash_class *dig_vtable;
	unsigned char ksi[64], kso[64];
#endif
} br_hmac_key_context;

/**
 * \brief HMAC key context initialisation.
 *
 * Initialise the key context with the provided key, using the hash function
 * identified by `digest_vtable`. This supports arbitrary key lengths.
 *
 * \param kc              HMAC key context to initialise.
 * \param digest_vtable   pointer to the hash function implementation vtable.
 * \param key             pointer to the HMAC secret key.
 * \param key_len         HMAC secret key length (in bytes).
 */
void br_hmac_key_init(br_hmac_key_context *kc,
	const br_hash_class *digest_vtable, const void *key, size_t key_len);

/*
 * \brief Get the underlying hash function.
 *
 * This function returns a pointer to the implementation vtable of the
 * hash function used for this HMAC key context.
 *
 * \param kc   HMAC key context.
 * \return  the hash function implementation.
 */
static inline const br_hash_class *br_hmac_key_get_digest(
	const br_hmac_key_context *kc)
{
	return kc->dig_vtable;
}

/**
 * \brief HMAC computation context.
 *
 * The HMAC computation context maintains the state for a single HMAC
 * computation. It is modified as input bytes are injected. The context
 * is caller-allocated and has no release function since it does not
 * dynamically allocate external resources. Its contents are opaque.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	br_hash_compat_context dig;
	unsigned char kso[64];
	size_t out_len;
#endif
} br_hmac_context;

/**
 * \brief HMAC computation initialisation.
 *
 * Initialise a HMAC context with a key context. The key context is
 * unmodified. Relevant data from the key context is immediately copied;
 * the key context can thus be independently reused, modified or released
 * without impacting this HMAC computation.
 *
 * An explicit output length can be specified; the actual output length
 * will be the minimum of that value and the natural HMAC output length.
 * If `out_len` is 0, then the natural HMAC output length is selected. The
 * "natural output length" is the output length of the underlying hash
 * function.
 *
 * \param ctx       HMAC context to initialise.
 * \param kc        HMAC key context (already initialised with the key).
 * \param out_len   HMAC output length (0 to select "natural length").
 */
void br_hmac_init(br_hmac_context *ctx,
	const br_hmac_key_context *kc, size_t out_len);

/**
 * \brief Get the HMAC output size.
 *
 * The HMAC output size is the number of bytes that will actually be
 * produced with `br_hmac_out()` with the provided context. This function
 * MUST NOT be called on a non-initialised HMAC computation context.
 * The returned value is the minimum of the HMAC natural length (output
 * size of the underlying hash function) and the `out_len` parameter which
 * was used with the last `br_hmac_init()` call on that context (if the
 * initialisation `out_len` parameter was 0, then this function will
 * return the HMAC natural length).
 *
 * \param ctx   the (already initialised) HMAC computation context.
 * \return  the HMAC actual output size.
 */
static inline size_t
br_hmac_size(br_hmac_context *ctx)
{
	return ctx->out_len;
}

/*
 * \brief Get the underlying hash function.
 *
 * This function returns a pointer to the implementation vtable of the
 * hash function used for this HMAC context.
 *
 * \param hc   HMAC context.
 * \return  the hash function implementation.
 */
static inline const br_hash_class *br_hmac_get_digest(
	const br_hmac_context *hc)
{
	return hc->dig.vtable;
}

/**
 * \brief Inject some bytes in HMAC.
 *
 * The provided `len` bytes are injected as extra input in the HMAC
 * computation incarnated by the `ctx` HMAC context. It is acceptable
 * that `len` is zero, in which case `data` is ignored (and may be
 * `NULL`) and this function does nothing.
 */
void br_hmac_update(br_hmac_context *ctx, const void *data, size_t len);

/**
 * \brief Compute the HMAC output.
 *
 * The destination buffer MUST be large enough to accommodate the result;
 * its length is at most the "natural length" of HMAC (i.e. the output
 * length of the underlying hash function). The context is NOT modified;
 * further bytes may be processed. Thus, "partial HMAC" values can be
 * efficiently obtained.
 *
 * Returned value is the output length (in bytes).
 *
 * \param ctx   HMAC computation context.
 * \param out   destination buffer for the HMAC output.
 * \return  the produced value length (in bytes).
 */
size_t br_hmac_out(const br_hmac_context *ctx, void *out);

/**
 * \brief Constant-time HMAC computation.
 *
 * This function compute the HMAC output in constant time. Some extra
 * input bytes are processed, then the output is computed. The extra
 * input consists in the `len` bytes pointed to by `data`. The `len`
 * parameter must lie between `min_len` and `max_len` (inclusive);
 * `max_len` bytes are actually read from `data`. Computing time (and
 * memory access pattern) will not depend upon the data byte contents or
 * the value of `len`.
 *
 * The output is written in the `out` buffer, that MUST be large enough
 * to receive it.
 *
 * The difference `max_len - min_len` MUST be less than 2<sup>30</sup>
 * (i.e. about one gigabyte).
 *
 * This function computes the output properly only if the underlying
 * hash function uses MD padding (i.e. MD5, SHA-1, SHA-224, SHA-256,
 * SHA-384 or SHA-512).
 *
 * The provided context is NOT modified.
 *
 * \param ctx       the (already initialised) HMAC computation context.
 * \param data      the extra input bytes.
 * \param len       the extra input length (in bytes).
 * \param min_len   minimum extra input length (in bytes).
 * \param max_len   maximum extra input length (in bytes).
 * \param out       destination buffer for the HMAC output.
 * \return  the produced value length (in bytes).
 */
size_t br_hmac_outCT(const br_hmac_context *ctx,
	const void *data, size_t len, size_t min_len, size_t max_len,
	void *out);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Copyright (c) 2018 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_KDF_H__
#define BR_BEARSSL_KDF_H__

#include <stddef.h>
#include <stdint.h>




#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_kdf.h
 *
 * # Key Derivation Functions
 *
 * KDF are functions that takes a variable length input, and provide a
 * variable length output, meant to be used to derive subkeys from a
 * master key.
 *
 * ## HKDF
 *
 * HKDF is a KDF defined by [RFC 5869](https://tools.ietf.org/html/rfc5869).
 * It is based on HMAC, itself using an underlying hash function. Any
 * hash function can be used, as long as it is compatible with the rules
 * for the HMAC implementation (i.e. output size is 64 bytes or less, hash
 * internal state size is 64 bytes or less, and the internal block length is
 * a power of 2 between 16 and 256 bytes). HKDF has two phases:
 *
 *  - HKDF-Extract: the input data in ingested, along with a "salt" value.
 *
 *  - HKDF-Expand: the output is produced, from the result of processing
 *    the input and salt, and using an extra non-secret parameter called
 *    "info".
 *
 * The "salt" and "info" strings are non-secret and can be empty. Their role
 * is normally to bind the input and output, respectively, to conventional
 * identifiers that qualifu them within the used protocol or application.
 *
 * The implementation defined in this file uses the following functions:
 *
 *  - `br_hkdf_init()`: initialize an HKDF context, with a hash function,
 *    and the salt. This starts the HKDF-Extract process.
 *
 *  - `br_hkdf_inject()`: inject more input bytes. This function may be
 *    called repeatedly if the input data is provided by chunks.
 *
 *  - `br_hkdf_flip()`: end the HKDF-Extract process, and start the
 *    HKDF-Expand process.
 *
 *  - `br_hkdf_produce()`: get the next bytes of output. This function
 *    may be called several times to obtain the full output by chunks.
 *    For correct HKDF processing, the same "info" string must be
 *    provided for each call.
 *
 * Note that the HKDF total output size (the number of bytes that
 * HKDF-Expand is willing to produce) is limited: if the hash output size
 * is _n_ bytes, then the maximum output size is _255*n_.
 *
 * ## SHAKE
 *
 * SHAKE is defined in
 * [FIPS 202](https://csrc.nist.gov/publications/detail/fips/202/final)
 * under two versions: SHAKE128 and SHAKE256, offering an alleged
 * "security level" of 128 and 256 bits, respectively (SHAKE128 is
 * about 20 to 25% faster than SHAKE256). SHAKE internally relies on
 * the Keccak family of sponge functions, not on any externally provided
 * hash function. Contrary to HKDF, SHAKE does not have a concept of
 * either a "salt" or an "info" string. The API consists in four
 * functions:
 *
 *  - `br_shake_init()`: initialize a SHAKE context for a given
 *    security level.
 *
 *  - `br_shake_inject()`: inject more input bytes. This function may be
 *    called repeatedly if the input data is provided by chunks.
 *
 *  - `br_shake_flip()`: end the data injection process, and start the
 *    data production process.
 *
 *  - `br_shake_produce()`: get the next bytes of output. This function
 *    may be called several times to obtain the full output by chunks.
 */

/**
 * \brief HKDF context.
 *
 * The HKDF context is initialized with a hash function implementation
 * and a salt value. Contents are opaque (callers should not access them
 * directly). The caller is responsible for allocating the context where
 * appropriate. Context initialisation and usage incurs no dynamic
 * allocation, so there is no release function.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	union {
		br_hmac_context hmac_ctx;
		br_hmac_key_context prk_ctx;
	} u;
	unsigned char buf[64];
	size_t ptr;
	size_t dig_len;
	unsigned chunk_num;
#endif
} br_hkdf_context;

/**
 * \brief HKDF context initialization.
 *
 * The underlying hash function and salt value are provided. Arbitrary
 * salt lengths can be used.
 *
 * HKDF makes a difference between a salt of length zero, and an
 * absent salt (the latter being equivalent to a salt consisting of
 * bytes of value zero, of the same length as the hash function output).
 * If `salt_len` is zero, then this function assumes that the salt is
 * present but of length zero. To specify an _absent_ salt, use
 * `BR_HKDF_NO_SALT` as `salt` parameter (`salt_len` is then ignored).
 *
 * \param hc              HKDF context to initialise.
 * \param digest_vtable   pointer to the hash function implementation vtable.
 * \param salt            HKDF-Extract salt.
 * \param salt_len        HKDF-Extract salt length (in bytes).
 */
void br_hkdf_init(br_hkdf_context *hc, const br_hash_class *digest_vtable,
	const void *salt, size_t salt_len);

/**
 * \brief The special "absent salt" value for HKDF.
 */
#define BR_HKDF_NO_SALT   (&br_hkdf_no_salt)

#ifndef BR_DOXYGEN_IGNORE
extern const unsigned char br_hkdf_no_salt;
#endif

/**
 * \brief HKDF input injection (HKDF-Extract).
 *
 * This function injects some more input bytes ("key material") into
 * HKDF. This function may be called several times, after `br_hkdf_init()`
 * but before `br_hkdf_flip()`.
 *
 * \param hc        HKDF context.
 * \param ikm       extra input bytes.
 * \param ikm_len   number of extra input bytes.
 */
void br_hkdf_inject(br_hkdf_context *hc, const void *ikm, size_t ikm_len);

/**
 * \brief HKDF switch to the HKDF-Expand phase.
 *
 * This call terminates the HKDF-Extract process (input injection), and
 * starts the HKDF-Expand process (output production).
 *
 * \param hc   HKDF context.
 */
void br_hkdf_flip(br_hkdf_context *hc);

/**
 * \brief HKDF output production (HKDF-Expand).
 *
 * Produce more output bytes from the current state. This function may be
 * called several times, but only after `br_hkdf_flip()`.
 *
 * Returned value is the number of actually produced bytes. The total
 * output length is limited to 255 times the output length of the
 * underlying hash function.
 *
 * \param hc         HKDF context.
 * \param info       application specific information string.
 * \param info_len   application specific information string length (in bytes).
 * \param out        destination buffer for the HKDF output.
 * \param out_len    the length of the requested output (in bytes).
 * \return  the produced output length (in bytes).
 */
size_t br_hkdf_produce(br_hkdf_context *hc,
	const void *info, size_t info_len, void *out, size_t out_len);

/**
 * \brief SHAKE context.
 *
 * The HKDF context is initialized with a "security level". The internal
 * notion is called "capacity"; the capacity is twice the security level
 * (for instance, SHAKE128 has capacity 256).
 *
 * The caller is responsible for allocating the context where
 * appropriate. Context initialisation and usage incurs no dynamic
 * allocation, so there is no release function.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	unsigned char dbuf[200];
	size_t dptr;
	size_t rate;
	uint64_t A[25];
#endif
} br_shake_context;

/**
 * \brief SHAKE context initialization.
 *
 * The context is initialized for the provided "security level".
 * Internally, this sets the "capacity" to twice the security level;
 * thus, for SHAKE128, the `security_level` parameter should be 128,
 * which corresponds to a 256-bit capacity.
 *
 * Allowed security levels are all multiples of 32, from 32 to 768,
 * inclusive. Larger security levels imply lower performance; levels
 * beyond 256 bits don't make much sense. Standard levels are 128
 * and 256 bits (for SHAKE128 and SHAKE256, respectively).
 *
 * \param sc               SHAKE context to initialise.
 * \param security_level   security level (in bits).
 */
void br_shake_init(br_shake_context *sc, int security_level);

/**
 * \brief SHAKE input injection.
 *
 * This function injects some more input bytes ("key material") into
 * SHAKE. This function may be called several times, after `br_shake_init()`
 * but before `br_shake_flip()`.
 *
 * \param sc     SHAKE context.
 * \param data   extra input bytes.
 * \param len    number of extra input bytes.
 */
void br_shake_inject(br_shake_context *sc, const void *data, size_t len);

/**
 * \brief SHAKE switch to production phase.
 *
 * This call terminates the input injection process, and starts the
 * output production process.
 *
 * \param sc   SHAKE context.
 */
void br_shake_flip(br_shake_context *hc);

/**
 * \brief SHAKE output production.
 *
 * Produce more output bytes from the current state. This function may be
 * called several times, but only after `br_shake_flip()`.
 *
 * There is no practical limit to the number of bytes that may be produced.
 *
 * \param sc    SHAKE context.
 * \param out   destination buffer for the SHAKE output.
 * \param len   the length of the requested output (in bytes).
 */
void br_shake_produce(br_shake_context *sc, void *out, size_t len);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_RAND_H__
#define BR_BEARSSL_RAND_H__

#include <stddef.h>
#include <stdint.h>

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_BLOCK_H__
#define BR_BEARSSL_BLOCK_H__

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_block.h
 *
 * # Block Ciphers and Symmetric Ciphers
 *
 * This file documents the API for block ciphers and other symmetric
 * ciphers.
 *
 *
 * ## Procedural API
 *
 * For a block cipher implementation, up to three separate sets of
 * functions are provided, for CBC encryption, CBC decryption, and CTR
 * encryption/decryption. Each set has its own context structure,
 * initialised with the encryption key.
 *
 * For CBC encryption and decryption, the data to encrypt or decrypt is
 * referenced as a sequence of blocks. The implementations assume that
 * there is no partial block; no padding is applied or removed. The
 * caller is responsible for handling any kind of padding.
 *
 * Function for CTR encryption are defined only for block ciphers with
 * blocks of 16 bytes or more (i.e. AES, but not DES/3DES).
 *
 * Each implemented block cipher is identified by an "internal name"
 * from which are derived the names of structures and functions that
 * implement the cipher. For the block cipher of internal name "`xxx`",
 * the following are defined:
 *
 *   - `br_xxx_BLOCK_SIZE`
 *
 *     A macro that evaluates to the block size (in bytes) of the
 *     cipher. For all implemented block ciphers, this value is a
 *     power of two.
 *
 *   - `br_xxx_cbcenc_keys`
 *
 *     Context structure that contains the subkeys resulting from the key
 *     expansion. These subkeys are appropriate for CBC encryption. The
 *     structure first field is called `vtable` and points to the
 *     appropriate OOP structure.
 *
 *   - `br_xxx_cbcenc_init(br_xxx_cbcenc_keys *ctx, const void *key, size_t len)`
 *
 *     Perform key expansion: subkeys for CBC encryption are computed and
 *     written in the provided context structure. The key length MUST be
 *     adequate for the implemented block cipher. This function also sets
 *     the `vtable` field.
 *
 *   - `br_xxx_cbcenc_run(const br_xxx_cbcenc_keys *ctx, void *iv, void *data, size_t len)`
 *
 *     Perform CBC encryption of `len` bytes, in place. The encrypted data
 *     replaces the cleartext. `len` MUST be a multiple of the block length
 *     (if it is not, the function may loop forever or overflow a buffer).
 *     The IV is provided with the `iv` pointer; it is also updated with
 *     a copy of the last encrypted block.
 *
 *   - `br_xxx_cbcdec_keys`
 *
 *     Context structure that contains the subkeys resulting from the key
 *     expansion. These subkeys are appropriate for CBC decryption. The
 *     structure first field is called `vtable` and points to the
 *     appropriate OOP structure.
 *
 *   - `br_xxx_cbcdec_init(br_xxx_cbcenc_keys *ctx, const void *key, size_t len)`
 *
 *     Perform key expansion: subkeys for CBC decryption are computed and
 *     written in the provided context structure. The key length MUST be
 *     adequate for the implemented block cipher. This function also sets
 *     the `vtable` field.
 *
 *   - `br_xxx_cbcdec_run(const br_xxx_cbcdec_keys *ctx, void *iv, void *data, size_t num_blocks)`
 *
 *     Perform CBC decryption of `len` bytes, in place. The decrypted data
 *     replaces the ciphertext. `len` MUST be a multiple of the block length
 *     (if it is not, the function may loop forever or overflow a buffer).
 *     The IV is provided with the `iv` pointer; it is also updated with
 *     a copy of the last _encrypted_ block.
 *
 *   - `br_xxx_ctr_keys`
 *
 *     Context structure that contains the subkeys resulting from the key
 *     expansion. These subkeys are appropriate for CTR encryption and
 *     decryption. The structure first field is called `vtable` and
 *     points to the appropriate OOP structure.
 *
 *   - `br_xxx_ctr_init(br_xxx_ctr_keys *ctx, const void *key, size_t len)`
 *
 *     Perform key expansion: subkeys for CTR encryption and decryption
 *     are computed and written in the provided context structure. The
 *     key length MUST be adequate for the implemented block cipher. This
 *     function also sets the `vtable` field.
 *
 *   - `br_xxx_ctr_run(const br_xxx_ctr_keys *ctx, const void *iv, uint32_t cc, void *data, size_t len)` (returns `uint32_t`)
 *
 *     Perform CTR encryption/decryption of some data. Processing is done
 *     "in place" (the output data replaces the input data). This function
 *     implements the "standard incrementing function" from NIST SP800-38A,
 *     annex B: the IV length shall be 4 bytes less than the block size
 *     (i.e. 12 bytes for AES) and the counter is the 32-bit value starting
 *     with `cc`. The data length (`len`) is not necessarily a multiple of
 *     the block size. The new counter value is returned, which supports
 *     chunked processing, provided that each chunk length (except possibly
 *     the last one) is a multiple of the block size.
 *
 *   - `br_xxx_ctrcbc_keys`
 *
 *     Context structure that contains the subkeys resulting from the
 *     key expansion. These subkeys are appropriate for doing combined
 *     CTR encryption/decryption and CBC-MAC, as used in the CCM and EAX
 *     authenticated encryption modes. The structure first field is
 *     called `vtable` and points to the appropriate OOP structure.
 *
 *   - `br_xxx_ctrcbc_init(br_xxx_ctr_keys *ctx, const void *key, size_t len)`
 *
 *     Perform key expansion: subkeys for combined CTR
 *     encryption/decryption and CBC-MAC are computed and written in the
 *     provided context structure. The key length MUST be adequate for
 *     the implemented block cipher. This function also sets the
 *     `vtable` field.
 *
 *   - `br_xxx_ctrcbc_encrypt(const br_xxx_ctrcbc_keys *ctx, void *ctr, void *cbcmac, void *data, size_t len)`
 *
 *     Perform CTR encryption of some data, and CBC-MAC. Processing is
 *     done "in place" (the output data replaces the input data). This
 *     function applies CTR encryption on the data, using a full
 *     block-size counter (i.e. for 128-bit blocks, the counter is
 *     incremented as a 128-bit value). The 'ctr' array contains the
 *     initial value for the counter (used in the first block) and it is
 *     updated with the new value after data processing. The 'cbcmac'
 *     value shall point to a block-sized value which is used as IV for
 *     CBC-MAC, computed over the encrypted data (output of CTR
 *     encryption); the resulting CBC-MAC is written over 'cbcmac' on
 *     output.
 *
 *     The data length MUST be a multiple of the block size.
 *
 *   - `br_xxx_ctrcbc_decrypt(const br_xxx_ctrcbc_keys *ctx, void *ctr, void *cbcmac, void *data, size_t len)`
 *
 *     Perform CTR decryption of some data, and CBC-MAC. Processing is
 *     done "in place" (the output data replaces the input data). This
 *     function applies CTR decryption on the data, using a full
 *     block-size counter (i.e. for 128-bit blocks, the counter is
 *     incremented as a 128-bit value). The 'ctr' array contains the
 *     initial value for the counter (used in the first block) and it is
 *     updated with the new value after data processing. The 'cbcmac'
 *     value shall point to a block-sized value which is used as IV for
 *     CBC-MAC, computed over the encrypted data (input of CTR
 *     encryption); the resulting CBC-MAC is written over 'cbcmac' on
 *     output.
 *
 *     The data length MUST be a multiple of the block size.
 *
 *   - `br_xxx_ctrcbc_ctr(const br_xxx_ctrcbc_keys *ctx, void *ctr, void *data, size_t len)`
 *
 *     Perform CTR encryption or decryption of the provided data. The
 *     data is processed "in place" (the output data replaces the input
 *     data). A full block-sized counter is applied (i.e. for 128-bit
 *     blocks, the counter is incremented as a 128-bit value). The 'ctr'
 *     array contains the initial value for the counter (used in the
 *     first block), and it is updated with the new value after data
 *     processing.
 *
 *     The data length MUST be a multiple of the block size.
 *
 *   - `br_xxx_ctrcbc_mac(const br_xxx_ctrcbc_keys *ctx, void *cbcmac, const void *data, size_t len)`
 *
 *     Compute CBC-MAC over the provided data. The IV for CBC-MAC is
 *     provided as 'cbcmac'; the output is written over the same array.
 *     The data itself is untouched. The data length MUST be a multiple
 *     of the block size.
 *
 *
 * It shall be noted that the key expansion functions return `void`. If
 * the provided key length is not allowed, then there will be no error
 * reporting; implementations need not validate the key length, thus an
 * invalid key length may result in undefined behaviour (e.g. buffer
 * overflow).
 *
 * Subkey structures contain no interior pointer, and no external
 * resources are allocated upon key expansion. They can thus be
 * discarded without any explicit deallocation.
 *
 *
 * ## Object-Oriented API
 *
 * Each context structure begins with a field (called `vtable`) that
 * points to an instance of a structure that references the relevant
 * functions through pointers. Each such structure contains the
 * following:
 *
 *   - `context_size`
 *
 *     The size (in bytes) of the context structure for subkeys.
 *
 *   - `block_size`
 *
 *     The cipher block size (in bytes).
 *
 *   - `log_block_size`
 *
 *     The base-2 logarithm of cipher block size (e.g. 4 for blocks
 *     of 16 bytes).
 *
 *   - `init`
 *
 *     Pointer to the key expansion function.
 *
 *   - `run`
 *
 *     Pointer to the encryption/decryption function.
 *
 * For combined CTR/CBC-MAC encryption, the `vtable` has a slightly
 * different structure:
 *
 *   - `context_size`
 *
 *     The size (in bytes) of the context structure for subkeys.
 *
 *   - `block_size`
 *
 *     The cipher block size (in bytes).
 *
 *   - `log_block_size`
 *
 *     The base-2 logarithm of cipher block size (e.g. 4 for blocks
 *     of 16 bytes).
 *
 *   - `init`
 *
 *     Pointer to the key expansion function.
 *
 *   - `encrypt`
 *
 *     Pointer to the CTR encryption + CBC-MAC function.
 *
 *   - `decrypt`
 *
 *     Pointer to the CTR decryption + CBC-MAC function.
 *
 *   - `ctr`
 *
 *     Pointer to the CTR encryption/decryption function.
 *
 *   - `mac`
 *
 *     Pointer to the CBC-MAC function.
 *
 * For block cipher "`xxx`", static, constant instances of these
 * structures are defined, under the names:
 *
 *   - `br_xxx_cbcenc_vtable`
 *   - `br_xxx_cbcdec_vtable`
 *   - `br_xxx_ctr_vtable`
 *   - `br_xxx_ctrcbc_vtable`
 *
 *
 * ## Implemented Block Ciphers
 * 
 * Provided implementations are:
 *
 * | Name      | Function | Block Size (bytes) | Key lengths (bytes) |
 * | :-------- | :------- | :----------------: | :-----------------: |
 * | aes_big   | AES      |        16          | 16, 24 and 32       |
 * | aes_small | AES      |        16          | 16, 24 and 32       |
 * | aes_ct    | AES      |        16          | 16, 24 and 32       |
 * | aes_ct64  | AES      |        16          | 16, 24 and 32       |
 * | aes_x86ni | AES      |        16          | 16, 24 and 32       |
 * | aes_pwr8  | AES      |        16          | 16, 24 and 32       |
 * | des_ct    | DES/3DES |         8          | 8, 16 and 24        |
 * | des_tab   | DES/3DES |         8          | 8, 16 and 24        |
 *
 * **Note:** DES/3DES nominally uses keys of 64, 128 and 192 bits (i.e. 8,
 * 16 and 24 bytes), but some of the bits are ignored by the algorithm, so
 * the _effective_ key lengths, from a security point of view, are 56,
 * 112 and 168 bits, respectively.
 *
 * `aes_big` is a "classical" AES implementation, using tables. It
 * is fast but not constant-time, since it makes data-dependent array
 * accesses.
 *
 * `aes_small` is an AES implementation optimized for code size. It
 * is substantially slower than `aes_big`; it is not constant-time
 * either.
 *
 * `aes_ct` is a constant-time implementation of AES; its code is about
 * as big as that of `aes_big`, while its performance is comparable to
 * that of `aes_small`. However, it is constant-time. This
 * implementation should thus be considered to be the "default" AES in
 * BearSSL, to be used unless the operational context guarantees that a
 * non-constant-time implementation is safe, or an architecture-specific
 * constant-time implementation can be used (e.g. using dedicated
 * hardware opcodes).
 *
 * `aes_ct64` is another constant-time implementation of AES. It is
 * similar to `aes_ct` but uses 64-bit values. On 32-bit machines,
 * `aes_ct64` is not faster than `aes_ct`, often a bit slower, and has
 * a larger footprint; however, on 64-bit architectures, `aes_ct64`
 * is typically twice faster than `aes_ct` for modes that allow parallel
 * operations (i.e. CTR, and CBC decryption, but not CBC encryption).
 *
 * `aes_x86ni` exists only on x86 architectures (32-bit and 64-bit). It
 * uses the AES-NI opcodes when available.
 *
 * `aes_pwr8` exists only on PowerPC / POWER architectures (32-bit and
 * 64-bit, both little-endian and big-endian). It uses the AES opcodes
 * present in POWER8 and later.
 *
 * `des_tab` is a classic, table-based implementation of DES/3DES. It
 * is not constant-time.
 *
 * `des_ct` is an constant-time implementation of DES/3DES. It is
 * substantially slower than `des_tab`.
 *
 * ## ChaCha20 and Poly1305
 *
 * ChaCha20 is a stream cipher. Poly1305 is a MAC algorithm. They
 * are described in [RFC 7539](https://tools.ietf.org/html/rfc7539).
 *
 * Two function pointer types are defined:
 *
 *   - `br_chacha20_run` describes a function that implements ChaCha20
 *     only.
 *
 *   - `br_poly1305_run` describes an implementation of Poly1305,
 *     in the AEAD combination with ChaCha20 specified in RFC 7539
 *     (the ChaCha20 implementation is provided as a function pointer).
 *
 * `chacha20_ct` is a straightforward implementation of ChaCha20 in
 * plain C; it is constant-time, small, and reasonably fast.
 *
 * `chacha20_sse2` leverages SSE2 opcodes (on x86 architectures that
 * support these opcodes). It is faster than `chacha20_ct`.
 *
 * `poly1305_ctmul` is an implementation of the ChaCha20+Poly1305 AEAD
 * construction, where the Poly1305 part is performed with mixed 32-bit
 * multiplications (operands are 32-bit, result is 64-bit).
 *
 * `poly1305_ctmul32` implements ChaCha20+Poly1305 using pure 32-bit
 * multiplications (32-bit operands, 32-bit result). It is slower than
 * `poly1305_ctmul`, except on some specific architectures such as
 * the ARM Cortex M0+.
 *
 * `poly1305_ctmulq` implements ChaCha20+Poly1305 with mixed 64-bit
 * multiplications (operands are 64-bit, result is 128-bit) on 64-bit
 * platforms that support such operations.
 *
 * `poly1305_i15` implements ChaCha20+Poly1305 with the generic "i15"
 * big integer implementation. It is meant mostly for testing purposes,
 * although it can help with saving a few hundred bytes of code footprint
 * on systems where code size is scarce.
 */

/**
 * \brief Class type for CBC encryption implementations.
 *
 * A `br_block_cbcenc_class` instance points to the functions implementing
 * a specific block cipher, when used in CBC mode for encrypting data.
 */
typedef struct br_block_cbcenc_class_ br_block_cbcenc_class;
struct br_block_cbcenc_class_ {
	/**
	 * \brief Size (in bytes) of the context structure appropriate
	 * for containing subkeys.
	 */
	size_t context_size;

	/**
	 * \brief Size of individual blocks (in bytes).
	 */
	unsigned block_size;

	/**
	 * \brief Base-2 logarithm of the size of individual blocks,
	 * expressed in bytes.
	 */
	unsigned log_block_size;

	/**
	 * \brief Initialisation function.
	 *
	 * This function sets the `vtable` field in the context structure.
	 * The key length MUST be one of the key lengths supported by
	 * the implementation.
	 *
	 * \param ctx       context structure to initialise.
	 * \param key       secret key.
	 * \param key_len   key length (in bytes).
	 */
	void (*init)(const br_block_cbcenc_class **ctx,
		const void *key, size_t key_len);

	/**
	 * \brief Run the CBC encryption.
	 *
	 * The `iv` parameter points to the IV for this run; it is
	 * updated with a copy of the last encrypted block. The data
	 * is encrypted "in place"; its length (`len`) MUST be a
	 * multiple of the block size.
	 *
	 * \param ctx    context structure (already initialised).
	 * \param iv     IV for CBC encryption (updated).
	 * \param data   data to encrypt.
	 * \param len    data length (in bytes, multiple of block size).
	 */
	void (*run)(const br_block_cbcenc_class *const *ctx,
		void *iv, void *data, size_t len);
};

/**
 * \brief Class type for CBC decryption implementations.
 *
 * A `br_block_cbcdec_class` instance points to the functions implementing
 * a specific block cipher, when used in CBC mode for decrypting data.
 */
typedef struct br_block_cbcdec_class_ br_block_cbcdec_class;
struct br_block_cbcdec_class_ {
	/**
	 * \brief Size (in bytes) of the context structure appropriate
	 * for containing subkeys.
	 */
	size_t context_size;

	/**
	 * \brief Size of individual blocks (in bytes).
	 */
	unsigned block_size;

	/**
	 * \brief Base-2 logarithm of the size of individual blocks,
	 * expressed in bytes.
	 */
	unsigned log_block_size;

	/**
	 * \brief Initialisation function.
	 *
	 * This function sets the `vtable` field in the context structure.
	 * The key length MUST be one of the key lengths supported by
	 * the implementation.
	 *
	 * \param ctx       context structure to initialise.
	 * \param key       secret key.
	 * \param key_len   key length (in bytes).
	 */
	void (*init)(const br_block_cbcdec_class **ctx,
		const void *key, size_t key_len);

	/**
	 * \brief Run the CBC decryption.
	 *
	 * The `iv` parameter points to the IV for this run; it is
	 * updated with a copy of the last encrypted block. The data
	 * is decrypted "in place"; its length (`len`) MUST be a
	 * multiple of the block size.
	 *
	 * \param ctx    context structure (already initialised).
	 * \param iv     IV for CBC decryption (updated).
	 * \param data   data to decrypt.
	 * \param len    data length (in bytes, multiple of block size).
	 */
	void (*run)(const br_block_cbcdec_class *const *ctx,
		void *iv, void *data, size_t len);
};

/**
 * \brief Class type for CTR encryption/decryption implementations.
 *
 * A `br_block_ctr_class` instance points to the functions implementing
 * a specific block cipher, when used in CTR mode for encrypting or
 * decrypting data.
 */
typedef struct br_block_ctr_class_ br_block_ctr_class;
struct br_block_ctr_class_ {
	/**
	 * \brief Size (in bytes) of the context structure appropriate
	 * for containing subkeys.
	 */
	size_t context_size;

	/**
	 * \brief Size of individual blocks (in bytes).
	 */
	unsigned block_size;

	/**
	 * \brief Base-2 logarithm of the size of individual blocks,
	 * expressed in bytes.
	 */
	unsigned log_block_size;

	/**
	 * \brief Initialisation function.
	 *
	 * This function sets the `vtable` field in the context structure.
	 * The key length MUST be one of the key lengths supported by
	 * the implementation.
	 *
	 * \param ctx       context structure to initialise.
	 * \param key       secret key.
	 * \param key_len   key length (in bytes).
	 */
	void (*init)(const br_block_ctr_class **ctx,
		const void *key, size_t key_len);

	/**
	 * \brief Run the CTR encryption or decryption.
	 *
	 * The `iv` parameter points to the IV for this run; its
	 * length is exactly 4 bytes less than the block size (e.g.
	 * 12 bytes for AES/CTR). The IV is combined with a 32-bit
	 * block counter to produce the block value which is processed
	 * with the block cipher.
	 *
	 * The data to encrypt or decrypt is updated "in place". Its
	 * length (`len` bytes) is not required to be a multiple of
	 * the block size; if the final block is partial, then the
	 * corresponding key stream bits are dropped.
	 *
	 * The resulting counter value is returned.
	 *
	 * \param ctx    context structure (already initialised).
	 * \param iv     IV for CTR encryption/decryption.
	 * \param cc     initial value for the block counter.
	 * \param data   data to encrypt or decrypt.
	 * \param len    data length (in bytes).
	 * \return  the new block counter value.
	 */
	uint32_t (*run)(const br_block_ctr_class *const *ctx,
		const void *iv, uint32_t cc, void *data, size_t len);
};

/**
 * \brief Class type for combined CTR and CBC-MAC implementations.
 *
 * A `br_block_ctrcbc_class` instance points to the functions implementing
 * a specific block cipher, when used in CTR mode for encrypting or
 * decrypting data, along with CBC-MAC.
 */
typedef struct br_block_ctrcbc_class_ br_block_ctrcbc_class;
struct br_block_ctrcbc_class_ {
	/**
	 * \brief Size (in bytes) of the context structure appropriate
	 * for containing subkeys.
	 */
	size_t context_size;

	/**
	 * \brief Size of individual blocks (in bytes).
	 */
	unsigned block_size;

	/**
	 * \brief Base-2 logarithm of the size of individual blocks,
	 * expressed in bytes.
	 */
	unsigned log_block_size;

	/**
	 * \brief Initialisation function.
	 *
	 * This function sets the `vtable` field in the context structure.
	 * The key length MUST be one of the key lengths supported by
	 * the implementation.
	 *
	 * \param ctx       context structure to initialise.
	 * \param key       secret key.
	 * \param key_len   key length (in bytes).
	 */
	void (*init)(const br_block_ctrcbc_class **ctx,
		const void *key, size_t key_len);

	/**
	 * \brief Run the CTR encryption + CBC-MAC.
	 *
	 * The `ctr` parameter points to the counter; its length shall
	 * be equal to the block size. It is updated by this function
	 * as encryption proceeds.
	 *
	 * The `cbcmac` parameter points to the IV for CBC-MAC. The MAC
	 * is computed over the encrypted data (output of CTR
	 * encryption). Its length shall be equal to the block size. The
	 * computed CBC-MAC value is written over the `cbcmac` array.
	 *
	 * The data to encrypt is updated "in place". Its length (`len`
	 * bytes) MUST be a multiple of the block size.
	 *
	 * \param ctx      context structure (already initialised).
	 * \param ctr      counter for CTR encryption (initial and final).
	 * \param cbcmac   IV and output buffer for CBC-MAC.
	 * \param data     data to encrypt.
	 * \param len      data length (in bytes).
	 */
	void (*encrypt)(const br_block_ctrcbc_class *const *ctx,
		void *ctr, void *cbcmac, void *data, size_t len);

	/**
	 * \brief Run the CTR decryption + CBC-MAC.
	 *
	 * The `ctr` parameter points to the counter; its length shall
	 * be equal to the block size. It is updated by this function
	 * as decryption proceeds.
	 *
	 * The `cbcmac` parameter points to the IV for CBC-MAC. The MAC
	 * is computed over the encrypted data (i.e. before CTR
	 * decryption). Its length shall be equal to the block size. The
	 * computed CBC-MAC value is written over the `cbcmac` array.
	 *
	 * The data to decrypt is updated "in place". Its length (`len`
	 * bytes) MUST be a multiple of the block size.
	 *
	 * \param ctx      context structure (already initialised).
	 * \param ctr      counter for CTR encryption (initial and final).
	 * \param cbcmac   IV and output buffer for CBC-MAC.
	 * \param data     data to decrypt.
	 * \param len      data length (in bytes).
	 */
	void (*decrypt)(const br_block_ctrcbc_class *const *ctx,
		void *ctr, void *cbcmac, void *data, size_t len);

	/**
	 * \brief Run the CTR encryption/decryption only.
	 *
	 * The `ctr` parameter points to the counter; its length shall
	 * be equal to the block size. It is updated by this function
	 * as decryption proceeds.
	 *
	 * The data to decrypt is updated "in place". Its length (`len`
	 * bytes) MUST be a multiple of the block size.
	 *
	 * \param ctx      context structure (already initialised).
	 * \param ctr      counter for CTR encryption (initial and final).
	 * \param data     data to decrypt.
	 * \param len      data length (in bytes).
	 */
	void (*ctr)(const br_block_ctrcbc_class *const *ctx,
		void *ctr, void *data, size_t len);

	/**
	 * \brief Run the CBC-MAC only.
	 *
	 * The `cbcmac` parameter points to the IV for CBC-MAC. The MAC
	 * is computed over the encrypted data (i.e. before CTR
	 * decryption). Its length shall be equal to the block size. The
	 * computed CBC-MAC value is written over the `cbcmac` array.
	 *
	 * The data is unmodified. Its length (`len` bytes) MUST be a
	 * multiple of the block size.
	 *
	 * \param ctx      context structure (already initialised).
	 * \param cbcmac   IV and output buffer for CBC-MAC.
	 * \param data     data to decrypt.
	 * \param len      data length (in bytes).
	 */
	void (*mac)(const br_block_ctrcbc_class *const *ctx,
		void *cbcmac, const void *data, size_t len);
};

/*
 * Traditional, table-based AES implementation. It is fast, but uses
 * internal tables (in particular a 1 kB table for encryption, another
 * 1 kB table for decryption, and a 256-byte table for key schedule),
 * and it is not constant-time. In contexts where cache-timing attacks
 * apply, this implementation may leak the secret key.
 */

/** \brief AES block size (16 bytes). */
#define br_aes_big_BLOCK_SIZE   16

/**
 * \brief Context for AES subkeys (`aes_big` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_big_cbcenc_keys;

/**
 * \brief Context for AES subkeys (`aes_big` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_big_cbcdec_keys;

/**
 * \brief Context for AES subkeys (`aes_big` implementation, CTR encryption
 * and decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctr_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_big_ctr_keys;

/**
 * \brief Context for AES subkeys (`aes_big` implementation, CTR encryption
 * and decryption + CBC-MAC).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctrcbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_big_ctrcbc_keys;

/**
 * \brief Class instance for AES CBC encryption (`aes_big` implementation).
 */
extern const br_block_cbcenc_class br_aes_big_cbcenc_vtable;

/**
 * \brief Class instance for AES CBC decryption (`aes_big` implementation).
 */
extern const br_block_cbcdec_class br_aes_big_cbcdec_vtable;

/**
 * \brief Class instance for AES CTR encryption and decryption
 * (`aes_big` implementation).
 */
extern const br_block_ctr_class br_aes_big_ctr_vtable;

/**
 * \brief Class instance for AES CTR encryption/decryption + CBC-MAC
 * (`aes_big` implementation).
 */
extern const br_block_ctrcbc_class br_aes_big_ctrcbc_vtable;

/**
 * \brief Context initialisation (key schedule) for AES CBC encryption
 * (`aes_big` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_big_cbcenc_init(br_aes_big_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CBC decryption
 * (`aes_big` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_big_cbcdec_init(br_aes_big_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR encryption
 * and decryption (`aes_big` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_big_ctr_init(br_aes_big_ctr_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR + CBC-MAC
 * (`aes_big` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_big_ctrcbc_init(br_aes_big_ctrcbc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with AES (`aes_big` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_big_cbcenc_run(const br_aes_big_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with AES (`aes_big` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_big_cbcdec_run(const br_aes_big_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CTR encryption and decryption with AES (`aes_big` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (constant, 12 bytes).
 * \param cc     initial block counter value.
 * \param data   data to encrypt or decrypt (updated).
 * \param len    data length (in bytes).
 * \return  new block counter value.
 */
uint32_t br_aes_big_ctr_run(const br_aes_big_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief CTR encryption + CBC-MAC with AES (`aes_big` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to encrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_big_ctrcbc_encrypt(const br_aes_big_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR decryption + CBC-MAC with AES (`aes_big` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to decrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_big_ctrcbc_decrypt(const br_aes_big_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR encryption/decryption with AES (`aes_big` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param data     data to MAC (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_big_ctrcbc_ctr(const br_aes_big_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len);

/**
 * \brief CBC-MAC with AES (`aes_big` implementation).
 *
 * \param ctx      context (already initialised).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to MAC (unmodified).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_big_ctrcbc_mac(const br_aes_big_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len);

/*
 * AES implementation optimized for size. It is slower than the
 * traditional table-based AES implementation, but requires much less
 * code. It still uses data-dependent table accesses (albeit within a
 * much smaller 256-byte table), which makes it conceptually vulnerable
 * to cache-timing attacks.
 */

/** \brief AES block size (16 bytes). */
#define br_aes_small_BLOCK_SIZE   16

/**
 * \brief Context for AES subkeys (`aes_small` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_small_cbcenc_keys;

/**
 * \brief Context for AES subkeys (`aes_small` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_small_cbcdec_keys;

/**
 * \brief Context for AES subkeys (`aes_small` implementation, CTR encryption
 * and decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctr_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_small_ctr_keys;

/**
 * \brief Context for AES subkeys (`aes_small` implementation, CTR encryption
 * and decryption + CBC-MAC).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctrcbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_small_ctrcbc_keys;

/**
 * \brief Class instance for AES CBC encryption (`aes_small` implementation).
 */
extern const br_block_cbcenc_class br_aes_small_cbcenc_vtable;

/**
 * \brief Class instance for AES CBC decryption (`aes_small` implementation).
 */
extern const br_block_cbcdec_class br_aes_small_cbcdec_vtable;

/**
 * \brief Class instance for AES CTR encryption and decryption
 * (`aes_small` implementation).
 */
extern const br_block_ctr_class br_aes_small_ctr_vtable;

/**
 * \brief Class instance for AES CTR encryption/decryption + CBC-MAC
 * (`aes_small` implementation).
 */
extern const br_block_ctrcbc_class br_aes_small_ctrcbc_vtable;

/**
 * \brief Context initialisation (key schedule) for AES CBC encryption
 * (`aes_small` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_small_cbcenc_init(br_aes_small_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CBC decryption
 * (`aes_small` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_small_cbcdec_init(br_aes_small_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR encryption
 * and decryption (`aes_small` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_small_ctr_init(br_aes_small_ctr_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR + CBC-MAC
 * (`aes_small` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_small_ctrcbc_init(br_aes_small_ctrcbc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with AES (`aes_small` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_small_cbcenc_run(const br_aes_small_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with AES (`aes_small` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_small_cbcdec_run(const br_aes_small_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CTR encryption and decryption with AES (`aes_small` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (constant, 12 bytes).
 * \param cc     initial block counter value.
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes).
 * \return  new block counter value.
 */
uint32_t br_aes_small_ctr_run(const br_aes_small_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief CTR encryption + CBC-MAC with AES (`aes_small` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to encrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_small_ctrcbc_encrypt(const br_aes_small_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR decryption + CBC-MAC with AES (`aes_small` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to decrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_small_ctrcbc_decrypt(const br_aes_small_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR encryption/decryption with AES (`aes_small` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param data     data to MAC (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_small_ctrcbc_ctr(const br_aes_small_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len);

/**
 * \brief CBC-MAC with AES (`aes_small` implementation).
 *
 * \param ctx      context (already initialised).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to MAC (unmodified).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_small_ctrcbc_mac(const br_aes_small_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len);

/*
 * Constant-time AES implementation. Its size is similar to that of
 * 'aes_big', and its performance is similar to that of 'aes_small' (faster
 * decryption, slower encryption). However, it is constant-time, i.e.
 * immune to cache-timing and similar attacks.
 */

/** \brief AES block size (16 bytes). */
#define br_aes_ct_BLOCK_SIZE   16

/**
 * \brief Context for AES subkeys (`aes_ct` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_ct_cbcenc_keys;

/**
 * \brief Context for AES subkeys (`aes_ct` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_ct_cbcdec_keys;

/**
 * \brief Context for AES subkeys (`aes_ct` implementation, CTR encryption
 * and decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctr_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_ct_ctr_keys;

/**
 * \brief Context for AES subkeys (`aes_ct` implementation, CTR encryption
 * and decryption + CBC-MAC).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctrcbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[60];
	unsigned num_rounds;
#endif
} br_aes_ct_ctrcbc_keys;

/**
 * \brief Class instance for AES CBC encryption (`aes_ct` implementation).
 */
extern const br_block_cbcenc_class br_aes_ct_cbcenc_vtable;

/**
 * \brief Class instance for AES CBC decryption (`aes_ct` implementation).
 */
extern const br_block_cbcdec_class br_aes_ct_cbcdec_vtable;

/**
 * \brief Class instance for AES CTR encryption and decryption
 * (`aes_ct` implementation).
 */
extern const br_block_ctr_class br_aes_ct_ctr_vtable;

/**
 * \brief Class instance for AES CTR encryption/decryption + CBC-MAC
 * (`aes_ct` implementation).
 */
extern const br_block_ctrcbc_class br_aes_ct_ctrcbc_vtable;

/**
 * \brief Context initialisation (key schedule) for AES CBC encryption
 * (`aes_ct` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct_cbcenc_init(br_aes_ct_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CBC decryption
 * (`aes_ct` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct_cbcdec_init(br_aes_ct_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR encryption
 * and decryption (`aes_ct` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct_ctr_init(br_aes_ct_ctr_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR + CBC-MAC
 * (`aes_ct` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct_ctrcbc_init(br_aes_ct_ctrcbc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with AES (`aes_ct` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_ct_cbcenc_run(const br_aes_ct_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with AES (`aes_ct` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_ct_cbcdec_run(const br_aes_ct_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CTR encryption and decryption with AES (`aes_ct` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (constant, 12 bytes).
 * \param cc     initial block counter value.
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes).
 * \return  new block counter value.
 */
uint32_t br_aes_ct_ctr_run(const br_aes_ct_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief CTR encryption + CBC-MAC with AES (`aes_ct` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to encrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct_ctrcbc_encrypt(const br_aes_ct_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR decryption + CBC-MAC with AES (`aes_ct` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to decrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct_ctrcbc_decrypt(const br_aes_ct_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR encryption/decryption with AES (`aes_ct` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param data     data to MAC (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct_ctrcbc_ctr(const br_aes_ct_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len);

/**
 * \brief CBC-MAC with AES (`aes_ct` implementation).
 *
 * \param ctx      context (already initialised).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to MAC (unmodified).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct_ctrcbc_mac(const br_aes_ct_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len);

/*
 * 64-bit constant-time AES implementation. It is similar to 'aes_ct'
 * but uses 64-bit registers, making it about twice faster than 'aes_ct'
 * on 64-bit platforms, while remaining constant-time and with a similar
 * code size. (The doubling in performance is only for CBC decryption
 * and CTR mode; CBC encryption is non-parallel and cannot benefit from
 * the larger registers.)
 */

/** \brief AES block size (16 bytes). */
#define br_aes_ct64_BLOCK_SIZE   16

/**
 * \brief Context for AES subkeys (`aes_ct64` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t skey[30];
	unsigned num_rounds;
#endif
} br_aes_ct64_cbcenc_keys;

/**
 * \brief Context for AES subkeys (`aes_ct64` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t skey[30];
	unsigned num_rounds;
#endif
} br_aes_ct64_cbcdec_keys;

/**
 * \brief Context for AES subkeys (`aes_ct64` implementation, CTR encryption
 * and decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctr_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t skey[30];
	unsigned num_rounds;
#endif
} br_aes_ct64_ctr_keys;

/**
 * \brief Context for AES subkeys (`aes_ct64` implementation, CTR encryption
 * and decryption + CBC-MAC).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctrcbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t skey[30];
	unsigned num_rounds;
#endif
} br_aes_ct64_ctrcbc_keys;

/**
 * \brief Class instance for AES CBC encryption (`aes_ct64` implementation).
 */
extern const br_block_cbcenc_class br_aes_ct64_cbcenc_vtable;

/**
 * \brief Class instance for AES CBC decryption (`aes_ct64` implementation).
 */
extern const br_block_cbcdec_class br_aes_ct64_cbcdec_vtable;

/**
 * \brief Class instance for AES CTR encryption and decryption
 * (`aes_ct64` implementation).
 */
extern const br_block_ctr_class br_aes_ct64_ctr_vtable;

/**
 * \brief Class instance for AES CTR encryption/decryption + CBC-MAC
 * (`aes_ct64` implementation).
 */
extern const br_block_ctrcbc_class br_aes_ct64_ctrcbc_vtable;

/**
 * \brief Context initialisation (key schedule) for AES CBC encryption
 * (`aes_ct64` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct64_cbcenc_init(br_aes_ct64_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CBC decryption
 * (`aes_ct64` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct64_cbcdec_init(br_aes_ct64_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR encryption
 * and decryption (`aes_ct64` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct64_ctr_init(br_aes_ct64_ctr_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR + CBC-MAC
 * (`aes_ct64` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_ct64_ctrcbc_init(br_aes_ct64_ctrcbc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with AES (`aes_ct64` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_ct64_cbcenc_run(const br_aes_ct64_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with AES (`aes_ct64` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_ct64_cbcdec_run(const br_aes_ct64_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CTR encryption and decryption with AES (`aes_ct64` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (constant, 12 bytes).
 * \param cc     initial block counter value.
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes).
 * \return  new block counter value.
 */
uint32_t br_aes_ct64_ctr_run(const br_aes_ct64_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief CTR encryption + CBC-MAC with AES (`aes_ct64` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to encrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct64_ctrcbc_encrypt(const br_aes_ct64_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR decryption + CBC-MAC with AES (`aes_ct64` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to decrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct64_ctrcbc_decrypt(const br_aes_ct64_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR encryption/decryption with AES (`aes_ct64` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param data     data to MAC (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct64_ctrcbc_ctr(const br_aes_ct64_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len);

/**
 * \brief CBC-MAC with AES (`aes_ct64` implementation).
 *
 * \param ctx      context (already initialised).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to MAC (unmodified).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_ct64_ctrcbc_mac(const br_aes_ct64_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len);

/*
 * AES implementation using AES-NI opcodes (x86 platform).
 */

/** \brief AES block size (16 bytes). */
#define br_aes_x86ni_BLOCK_SIZE   16

/**
 * \brief Context for AES subkeys (`aes_x86ni` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_x86ni_cbcenc_keys;

/**
 * \brief Context for AES subkeys (`aes_x86ni` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_x86ni_cbcdec_keys;

/**
 * \brief Context for AES subkeys (`aes_x86ni` implementation, CTR encryption
 * and decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctr_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_x86ni_ctr_keys;

/**
 * \brief Context for AES subkeys (`aes_x86ni` implementation, CTR encryption
 * and decryption + CBC-MAC).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctrcbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_x86ni_ctrcbc_keys;

/**
 * \brief Class instance for AES CBC encryption (`aes_x86ni` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_x86ni_cbcenc_get_vtable()`.
 */
extern const br_block_cbcenc_class br_aes_x86ni_cbcenc_vtable;

/**
 * \brief Class instance for AES CBC decryption (`aes_x86ni` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_x86ni_cbcdec_get_vtable()`.
 */
extern const br_block_cbcdec_class br_aes_x86ni_cbcdec_vtable;

/**
 * \brief Class instance for AES CTR encryption and decryption
 * (`aes_x86ni` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_x86ni_ctr_get_vtable()`.
 */
extern const br_block_ctr_class br_aes_x86ni_ctr_vtable;

/**
 * \brief Class instance for AES CTR encryption/decryption + CBC-MAC
 * (`aes_x86ni` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_x86ni_ctrcbc_get_vtable()`.
 */
extern const br_block_ctrcbc_class br_aes_x86ni_ctrcbc_vtable;

/**
 * \brief Context initialisation (key schedule) for AES CBC encryption
 * (`aes_x86ni` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_x86ni_cbcenc_init(br_aes_x86ni_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CBC decryption
 * (`aes_x86ni` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_x86ni_cbcdec_init(br_aes_x86ni_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR encryption
 * and decryption (`aes_x86ni` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_x86ni_ctr_init(br_aes_x86ni_ctr_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR + CBC-MAC
 * (`aes_x86ni` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_x86ni_ctrcbc_init(br_aes_x86ni_ctrcbc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with AES (`aes_x86ni` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_x86ni_cbcenc_run(const br_aes_x86ni_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with AES (`aes_x86ni` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_x86ni_cbcdec_run(const br_aes_x86ni_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CTR encryption and decryption with AES (`aes_x86ni` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (constant, 12 bytes).
 * \param cc     initial block counter value.
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes).
 * \return  new block counter value.
 */
uint32_t br_aes_x86ni_ctr_run(const br_aes_x86ni_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief CTR encryption + CBC-MAC with AES (`aes_x86ni` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to encrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_x86ni_ctrcbc_encrypt(const br_aes_x86ni_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR decryption + CBC-MAC with AES (`aes_x86ni` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to decrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_x86ni_ctrcbc_decrypt(const br_aes_x86ni_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR encryption/decryption with AES (`aes_x86ni` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param data     data to MAC (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_x86ni_ctrcbc_ctr(const br_aes_x86ni_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len);

/**
 * \brief CBC-MAC with AES (`aes_x86ni` implementation).
 *
 * \param ctx      context (already initialised).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to MAC (unmodified).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_x86ni_ctrcbc_mac(const br_aes_x86ni_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len);

/**
 * \brief Obtain the `aes_x86ni` AES-CBC (encryption) implementation, if
 * available.
 *
 * This function returns a pointer to `br_aes_x86ni_cbcenc_vtable`, if
 * that implementation was compiled in the library _and_ the x86 AES
 * opcodes are available on the currently running CPU. If either of
 * these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_x86ni` AES-CBC (encryption) implementation, or `NULL`.
 */
const br_block_cbcenc_class *br_aes_x86ni_cbcenc_get_vtable(void);

/**
 * \brief Obtain the `aes_x86ni` AES-CBC (decryption) implementation, if
 * available.
 *
 * This function returns a pointer to `br_aes_x86ni_cbcdec_vtable`, if
 * that implementation was compiled in the library _and_ the x86 AES
 * opcodes are available on the currently running CPU. If either of
 * these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_x86ni` AES-CBC (decryption) implementation, or `NULL`.
 */
const br_block_cbcdec_class *br_aes_x86ni_cbcdec_get_vtable(void);

/**
 * \brief Obtain the `aes_x86ni` AES-CTR implementation, if available.
 *
 * This function returns a pointer to `br_aes_x86ni_ctr_vtable`, if
 * that implementation was compiled in the library _and_ the x86 AES
 * opcodes are available on the currently running CPU. If either of
 * these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_x86ni` AES-CTR implementation, or `NULL`.
 */
const br_block_ctr_class *br_aes_x86ni_ctr_get_vtable(void);

/**
 * \brief Obtain the `aes_x86ni` AES-CTR + CBC-MAC implementation, if
 * available.
 *
 * This function returns a pointer to `br_aes_x86ni_ctrcbc_vtable`, if
 * that implementation was compiled in the library _and_ the x86 AES
 * opcodes are available on the currently running CPU. If either of
 * these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_x86ni` AES-CTR implementation, or `NULL`.
 */
const br_block_ctrcbc_class *br_aes_x86ni_ctrcbc_get_vtable(void);

/*
 * AES implementation using POWER8 opcodes.
 */

/** \brief AES block size (16 bytes). */
#define br_aes_pwr8_BLOCK_SIZE   16

/**
 * \brief Context for AES subkeys (`aes_pwr8` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_pwr8_cbcenc_keys;

/**
 * \brief Context for AES subkeys (`aes_pwr8` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_pwr8_cbcdec_keys;

/**
 * \brief Context for AES subkeys (`aes_pwr8` implementation, CTR encryption
 * and decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctr_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_pwr8_ctr_keys;

/**
 * \brief Context for AES subkeys (`aes_pwr8` implementation, CTR encryption
 * and decryption + CBC-MAC).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_ctrcbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	union {
		unsigned char skni[16 * 15];
	} skey;
	unsigned num_rounds;
#endif
} br_aes_pwr8_ctrcbc_keys;

/**
 * \brief Class instance for AES CBC encryption (`aes_pwr8` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_pwr8_cbcenc_get_vtable()`.
 */
extern const br_block_cbcenc_class br_aes_pwr8_cbcenc_vtable;

/**
 * \brief Class instance for AES CBC decryption (`aes_pwr8` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_pwr8_cbcdec_get_vtable()`.
 */
extern const br_block_cbcdec_class br_aes_pwr8_cbcdec_vtable;

/**
 * \brief Class instance for AES CTR encryption and decryption
 * (`aes_pwr8` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_pwr8_ctr_get_vtable()`.
 */
extern const br_block_ctr_class br_aes_pwr8_ctr_vtable;

/**
 * \brief Class instance for AES CTR encryption/decryption + CBC-MAC
 * (`aes_pwr8` implementation).
 *
 * Since this implementation might be omitted from the library, or the
 * AES opcode unavailable on the current CPU, a pointer to this class
 * instance should be obtained through `br_aes_pwr8_ctrcbc_get_vtable()`.
 */
extern const br_block_ctrcbc_class br_aes_pwr8_ctrcbc_vtable;

/**
 * \brief Context initialisation (key schedule) for AES CBC encryption
 * (`aes_pwr8` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_pwr8_cbcenc_init(br_aes_pwr8_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CBC decryption
 * (`aes_pwr8` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_pwr8_cbcdec_init(br_aes_pwr8_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR encryption
 * and decryption (`aes_pwr8` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_pwr8_ctr_init(br_aes_pwr8_ctr_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for AES CTR + CBC-MAC
 * (`aes_pwr8` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_aes_pwr8_ctrcbc_init(br_aes_pwr8_ctrcbc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with AES (`aes_pwr8` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_pwr8_cbcenc_run(const br_aes_pwr8_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with AES (`aes_pwr8` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 16).
 */
void br_aes_pwr8_cbcdec_run(const br_aes_pwr8_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CTR encryption and decryption with AES (`aes_pwr8` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (constant, 12 bytes).
 * \param cc     initial block counter value.
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes).
 * \return  new block counter value.
 */
uint32_t br_aes_pwr8_ctr_run(const br_aes_pwr8_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief CTR encryption + CBC-MAC with AES (`aes_pwr8` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to encrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_pwr8_ctrcbc_encrypt(const br_aes_pwr8_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR decryption + CBC-MAC with AES (`aes_pwr8` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to decrypt (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_pwr8_ctrcbc_decrypt(const br_aes_pwr8_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len);

/**
 * \brief CTR encryption/decryption with AES (`aes_pwr8` implementation).
 *
 * \param ctx      context (already initialised).
 * \param ctr      counter for CTR (16 bytes, updated).
 * \param data     data to MAC (updated).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_pwr8_ctrcbc_ctr(const br_aes_pwr8_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len);

/**
 * \brief CBC-MAC with AES (`aes_pwr8` implementation).
 *
 * \param ctx      context (already initialised).
 * \param cbcmac   IV for CBC-MAC (updated).
 * \param data     data to MAC (unmodified).
 * \param len      data length (in bytes, MUST be a multiple of 16).
 */
void br_aes_pwr8_ctrcbc_mac(const br_aes_pwr8_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len);

/**
 * \brief Obtain the `aes_pwr8` AES-CBC (encryption) implementation, if
 * available.
 *
 * This function returns a pointer to `br_aes_pwr8_cbcenc_vtable`, if
 * that implementation was compiled in the library _and_ the POWER8
 * crypto opcodes are available on the currently running CPU. If either
 * of these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_pwr8` AES-CBC (encryption) implementation, or `NULL`.
 */
const br_block_cbcenc_class *br_aes_pwr8_cbcenc_get_vtable(void);

/**
 * \brief Obtain the `aes_pwr8` AES-CBC (decryption) implementation, if
 * available.
 *
 * This function returns a pointer to `br_aes_pwr8_cbcdec_vtable`, if
 * that implementation was compiled in the library _and_ the POWER8
 * crypto opcodes are available on the currently running CPU. If either
 * of these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_pwr8` AES-CBC (decryption) implementation, or `NULL`.
 */
const br_block_cbcdec_class *br_aes_pwr8_cbcdec_get_vtable(void);

/**
 * \brief Obtain the `aes_pwr8` AES-CTR implementation, if available.
 *
 * This function returns a pointer to `br_aes_pwr8_ctr_vtable`, if that
 * implementation was compiled in the library _and_ the POWER8 crypto
 * opcodes are available on the currently running CPU. If either of
 * these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_pwr8` AES-CTR implementation, or `NULL`.
 */
const br_block_ctr_class *br_aes_pwr8_ctr_get_vtable(void);

/**
 * \brief Obtain the `aes_pwr8` AES-CTR + CBC-MAC implementation, if
 * available.
 *
 * This function returns a pointer to `br_aes_pwr8_ctrcbc_vtable`, if
 * that implementation was compiled in the library _and_ the POWER8 AES
 * opcodes are available on the currently running CPU. If either of
 * these conditions is not met, then this function returns `NULL`.
 *
 * \return  the `aes_pwr8` AES-CTR implementation, or `NULL`.
 */
const br_block_ctrcbc_class *br_aes_pwr8_ctrcbc_get_vtable(void);

/**
 * \brief Aggregate structure large enough to be used as context for
 * subkeys (CBC encryption) for all AES implementations.
 */
typedef union {
	const br_block_cbcenc_class *vtable;
	br_aes_big_cbcenc_keys c_big;
	br_aes_small_cbcenc_keys c_small;
	br_aes_ct_cbcenc_keys c_ct;
	br_aes_ct64_cbcenc_keys c_ct64;
	br_aes_x86ni_cbcenc_keys c_x86ni;
	br_aes_pwr8_cbcenc_keys c_pwr8;
} br_aes_gen_cbcenc_keys;

/**
 * \brief Aggregate structure large enough to be used as context for
 * subkeys (CBC decryption) for all AES implementations.
 */
typedef union {
	const br_block_cbcdec_class *vtable;
	br_aes_big_cbcdec_keys c_big;
	br_aes_small_cbcdec_keys c_small;
	br_aes_ct_cbcdec_keys c_ct;
	br_aes_ct64_cbcdec_keys c_ct64;
	br_aes_x86ni_cbcdec_keys c_x86ni;
	br_aes_pwr8_cbcdec_keys c_pwr8;
} br_aes_gen_cbcdec_keys;

/**
 * \brief Aggregate structure large enough to be used as context for
 * subkeys (CTR encryption and decryption) for all AES implementations.
 */
typedef union {
	const br_block_ctr_class *vtable;
	br_aes_big_ctr_keys c_big;
	br_aes_small_ctr_keys c_small;
	br_aes_ct_ctr_keys c_ct;
	br_aes_ct64_ctr_keys c_ct64;
	br_aes_x86ni_ctr_keys c_x86ni;
	br_aes_pwr8_ctr_keys c_pwr8;
} br_aes_gen_ctr_keys;

/**
 * \brief Aggregate structure large enough to be used as context for
 * subkeys (CTR encryption/decryption + CBC-MAC) for all AES implementations.
 */
typedef union {
	const br_block_ctrcbc_class *vtable;
	br_aes_big_ctrcbc_keys c_big;
	br_aes_small_ctrcbc_keys c_small;
	br_aes_ct_ctrcbc_keys c_ct;
	br_aes_ct64_ctrcbc_keys c_ct64;
	br_aes_x86ni_ctrcbc_keys c_x86ni;
	br_aes_pwr8_ctrcbc_keys c_pwr8;
} br_aes_gen_ctrcbc_keys;

/*
 * Traditional, table-based implementation for DES/3DES. Since tables are
 * used, cache-timing attacks are conceptually possible.
 */

/** \brief DES/3DES block size (8 bytes). */
#define br_des_tab_BLOCK_SIZE   8

/**
 * \brief Context for DES subkeys (`des_tab` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[96];
	unsigned num_rounds;
#endif
} br_des_tab_cbcenc_keys;

/**
 * \brief Context for DES subkeys (`des_tab` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[96];
	unsigned num_rounds;
#endif
} br_des_tab_cbcdec_keys;

/**
 * \brief Class instance for DES CBC encryption (`des_tab` implementation).
 */
extern const br_block_cbcenc_class br_des_tab_cbcenc_vtable;

/**
 * \brief Class instance for DES CBC decryption (`des_tab` implementation).
 */
extern const br_block_cbcdec_class br_des_tab_cbcdec_vtable;

/**
 * \brief Context initialisation (key schedule) for DES CBC encryption
 * (`des_tab` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_des_tab_cbcenc_init(br_des_tab_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for DES CBC decryption
 * (`des_tab` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_des_tab_cbcdec_init(br_des_tab_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with DES (`des_tab` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 8).
 */
void br_des_tab_cbcenc_run(const br_des_tab_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with DES (`des_tab` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 8).
 */
void br_des_tab_cbcdec_run(const br_des_tab_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/*
 * Constant-time implementation for DES/3DES. It is substantially slower
 * (by a factor of about 4x), but also immune to cache-timing attacks.
 */

/** \brief DES/3DES block size (8 bytes). */
#define br_des_ct_BLOCK_SIZE   8

/**
 * \brief Context for DES subkeys (`des_ct` implementation, CBC encryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcenc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[96];
	unsigned num_rounds;
#endif
} br_des_ct_cbcenc_keys;

/**
 * \brief Context for DES subkeys (`des_ct` implementation, CBC decryption).
 *
 * First field is a pointer to the vtable; it is set by the initialisation
 * function. Other fields are not supposed to be accessed by user code.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_block_cbcdec_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint32_t skey[96];
	unsigned num_rounds;
#endif
} br_des_ct_cbcdec_keys;

/**
 * \brief Class instance for DES CBC encryption (`des_ct` implementation).
 */
extern const br_block_cbcenc_class br_des_ct_cbcenc_vtable;

/**
 * \brief Class instance for DES CBC decryption (`des_ct` implementation).
 */
extern const br_block_cbcdec_class br_des_ct_cbcdec_vtable;

/**
 * \brief Context initialisation (key schedule) for DES CBC encryption
 * (`des_ct` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_des_ct_cbcenc_init(br_des_ct_cbcenc_keys *ctx,
	const void *key, size_t len);

/**
 * \brief Context initialisation (key schedule) for DES CBC decryption
 * (`des_ct` implementation).
 *
 * \param ctx   context to initialise.
 * \param key   secret key.
 * \param len   secret key length (in bytes).
 */
void br_des_ct_cbcdec_init(br_des_ct_cbcdec_keys *ctx,
	const void *key, size_t len);

/**
 * \brief CBC encryption with DES (`des_ct` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to encrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 8).
 */
void br_des_ct_cbcenc_run(const br_des_ct_cbcenc_keys *ctx, void *iv,
	void *data, size_t len);

/**
 * \brief CBC decryption with DES (`des_ct` implementation).
 *
 * \param ctx    context (already initialised).
 * \param iv     IV (updated).
 * \param data   data to decrypt (updated).
 * \param len    data length (in bytes, MUST be multiple of 8).
 */
void br_des_ct_cbcdec_run(const br_des_ct_cbcdec_keys *ctx, void *iv,
	void *data, size_t len);

/*
 * These structures are large enough to accommodate subkeys for all
 * DES/3DES implementations.
 */

/**
 * \brief Aggregate structure large enough to be used as context for
 * subkeys (CBC encryption) for all DES implementations.
 */
typedef union {
	const br_block_cbcenc_class *vtable;
	br_des_tab_cbcenc_keys tab;
	br_des_ct_cbcenc_keys ct;
} br_des_gen_cbcenc_keys;

/**
 * \brief Aggregate structure large enough to be used as context for
 * subkeys (CBC decryption) for all DES implementations.
 */
typedef union {
	const br_block_cbcdec_class *vtable;
	br_des_tab_cbcdec_keys c_tab;
	br_des_ct_cbcdec_keys c_ct;
} br_des_gen_cbcdec_keys;

/**
 * \brief Type for a ChaCha20 implementation.
 *
 * An implementation follows the description in RFC 7539:
 *
 *   - Key is 256 bits (`key` points to exactly 32 bytes).
 *
 *   - IV is 96 bits (`iv` points to exactly 12 bytes).
 *
 *   - Block counter is over 32 bits and starts at value `cc`; the
 *     resulting value is returned.
 *
 * Data (pointed to by `data`, of length `len`) is encrypted/decrypted
 * in place. If `len` is not a multiple of 64, then the excess bytes from
 * the last block processing are dropped (therefore, "chunked" processing
 * works only as long as each non-final chunk has a length multiple of 64).
 *
 * \param key    secret key (32 bytes).
 * \param iv     IV (12 bytes).
 * \param cc     initial counter value.
 * \param data   data to encrypt or decrypt.
 * \param len    data length (in bytes).
 */
typedef uint32_t (*br_chacha20_run)(const void *key,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief ChaCha20 implementation (straightforward C code, constant-time).
 *
 * \see br_chacha20_run
 *
 * \param key    secret key (32 bytes).
 * \param iv     IV (12 bytes).
 * \param cc     initial counter value.
 * \param data   data to encrypt or decrypt.
 * \param len    data length (in bytes).
 */
uint32_t br_chacha20_ct_run(const void *key,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief ChaCha20 implementation (SSE2 code, constant-time).
 *
 * This implementation is available only on x86 platforms, depending on
 * compiler support. Moreover, in 32-bit mode, it might not actually run,
 * if the underlying hardware does not implement the SSE2 opcode (in
 * 64-bit mode, SSE2 is part of the ABI, so if the code could be compiled
 * at all, then it can run). Use `br_chacha20_sse2_get()` to safely obtain
 * a pointer to that function.
 *
 * \see br_chacha20_run
 *
 * \param key    secret key (32 bytes).
 * \param iv     IV (12 bytes).
 * \param cc     initial counter value.
 * \param data   data to encrypt or decrypt.
 * \param len    data length (in bytes).
 */
uint32_t br_chacha20_sse2_run(const void *key,
	const void *iv, uint32_t cc, void *data, size_t len);

/**
 * \brief Obtain the `sse2` ChaCha20 implementation, if available.
 *
 * This function returns a pointer to `br_chacha20_sse2_run`, if
 * that implementation was compiled in the library _and_ the SSE2
 * opcodes are available on the currently running CPU. If either of
 * these conditions is not met, then this function returns `0`.
 *
 * \return  the `sse2` ChaCha20 implementation, or `0`.
 */
br_chacha20_run br_chacha20_sse2_get(void);

/**
 * \brief Type for a ChaCha20+Poly1305 AEAD implementation.
 *
 * The provided data is encrypted or decrypted with ChaCha20. The
 * authentication tag is computed on the concatenation of the
 * additional data and the ciphertext, with the padding and lengths
 * as described in RFC 7539 (section 2.8).
 *
 * After decryption, the caller is responsible for checking that the
 * computed tag matches the expected value.
 *
 * \param key       secret key (32 bytes).
 * \param iv        nonce (12 bytes).
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 * \param aad       additional authenticated data.
 * \param aad_len   length of additional authenticated data (in bytes).
 * \param tag       output buffer for the authentication tag.
 * \param ichacha   implementation of ChaCha20.
 * \param encrypt   non-zero for encryption, zero for decryption.
 */
typedef void (*br_poly1305_run)(const void *key, const void *iv,
	void *data, size_t len, const void *aad, size_t aad_len,
	void *tag, br_chacha20_run ichacha, int encrypt);

/**
 * \brief ChaCha20+Poly1305 AEAD implementation (mixed 32-bit multiplications).
 *
 * \see br_poly1305_run
 *
 * \param key       secret key (32 bytes).
 * \param iv        nonce (12 bytes).
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 * \param aad       additional authenticated data.
 * \param aad_len   length of additional authenticated data (in bytes).
 * \param tag       output buffer for the authentication tag.
 * \param ichacha   implementation of ChaCha20.
 * \param encrypt   non-zero for encryption, zero for decryption.
 */
void br_poly1305_ctmul_run(const void *key, const void *iv,
	void *data, size_t len, const void *aad, size_t aad_len,
	void *tag, br_chacha20_run ichacha, int encrypt);

/**
 * \brief ChaCha20+Poly1305 AEAD implementation (pure 32-bit multiplications).
 *
 * \see br_poly1305_run
 *
 * \param key       secret key (32 bytes).
 * \param iv        nonce (12 bytes).
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 * \param aad       additional authenticated data.
 * \param aad_len   length of additional authenticated data (in bytes).
 * \param tag       output buffer for the authentication tag.
 * \param ichacha   implementation of ChaCha20.
 * \param encrypt   non-zero for encryption, zero for decryption.
 */
void br_poly1305_ctmul32_run(const void *key, const void *iv,
	void *data, size_t len, const void *aad, size_t aad_len,
	void *tag, br_chacha20_run ichacha, int encrypt);

/**
 * \brief ChaCha20+Poly1305 AEAD implementation (i15).
 *
 * This implementation relies on the generic big integer code "i15"
 * (which uses pure 32-bit multiplications). As such, it may save a
 * little code footprint in a context where "i15" is already included
 * (e.g. for elliptic curves or for RSA); however, it is also
 * substantially slower than the ctmul and ctmul32 implementations.
 *
 * \see br_poly1305_run
 *
 * \param key       secret key (32 bytes).
 * \param iv        nonce (12 bytes).
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 * \param aad       additional authenticated data.
 * \param aad_len   length of additional authenticated data (in bytes).
 * \param tag       output buffer for the authentication tag.
 * \param ichacha   implementation of ChaCha20.
 * \param encrypt   non-zero for encryption, zero for decryption.
 */
void br_poly1305_i15_run(const void *key, const void *iv,
	void *data, size_t len, const void *aad, size_t aad_len,
	void *tag, br_chacha20_run ichacha, int encrypt);

/**
 * \brief ChaCha20+Poly1305 AEAD implementation (ctmulq).
 *
 * This implementation uses 64-bit multiplications (result over 128 bits).
 * It is available only on platforms that offer such a primitive (in
 * practice, 64-bit architectures). Use `br_poly1305_ctmulq_get()` to
 * dynamically obtain a pointer to that function, or 0 if not supported.
 *
 * \see br_poly1305_run
 *
 * \param key       secret key (32 bytes).
 * \param iv        nonce (12 bytes).
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 * \param aad       additional authenticated data.
 * \param aad_len   length of additional authenticated data (in bytes).
 * \param tag       output buffer for the authentication tag.
 * \param ichacha   implementation of ChaCha20.
 * \param encrypt   non-zero for encryption, zero for decryption.
 */
void br_poly1305_ctmulq_run(const void *key, const void *iv,
	void *data, size_t len, const void *aad, size_t aad_len,
	void *tag, br_chacha20_run ichacha, int encrypt);

/**
 * \brief Get the ChaCha20+Poly1305 "ctmulq" implementation, if available.
 *
 * This function returns a pointer to the `br_poly1305_ctmulq_run()`
 * function if supported on the current platform; otherwise, it returns 0.
 *
 * \return  the ctmulq ChaCha20+Poly1305 implementation, or 0.
 */
br_poly1305_run br_poly1305_ctmulq_get(void);

#ifdef __cplusplus
}
#endif

#endif



#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_rand.h
 *
 * # Pseudo-Random Generators
 *
 * A PRNG is a state-based engine that outputs pseudo-random bytes on
 * demand. It is initialized with an initial seed, and additional seed
 * bytes can be added afterwards. Bytes produced depend on the seeds and
 * also on the exact sequence of calls (including sizes requested for
 * each call).
 *
 *
 * ## Procedural and OOP API
 *
 * For the PRNG of name "`xxx`", two API are provided. The _procedural_
 * API defined a context structure `br_xxx_context` and three functions:
 *
 *   - `br_xxx_init()`
 *
 *     Initialise the context with an initial seed.
 *
 *   - `br_xxx_generate()`
 *
 *     Produce some pseudo-random bytes.
 *
 *   - `br_xxx_update()`
 *
 *     Inject some additional seed.
 *
 * The initialisation function sets the first context field (`vtable`)
 * to a pointer to the vtable that supports the OOP API. The OOP API
 * provides access to the same functions through function pointers,
 * named `init()`, `generate()` and `update()`.
 *
 * Note that the context initialisation method may accept additional
 * parameters, provided as a 'const void *' pointer at API level. These
 * additional parameters depend on the implemented PRNG.
 *
 *
 * ## HMAC_DRBG
 *
 * HMAC_DRBG is defined in [NIST SP 800-90A Revision
 * 1](http://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90Ar1.pdf).
 * It uses HMAC repeatedly, over some configurable underlying hash
 * function. In BearSSL, it is implemented under the "`hmac_drbg`" name.
 * The "extra parameters" pointer for context initialisation should be
 * set to a pointer to the vtable for the underlying hash function (e.g.
 * pointer to `br_sha256_vtable` to use HMAC_DRBG with SHA-256).
 *
 * According to the NIST standard, each request shall produce up to
 * 2<sup>19</sup> bits (i.e. 64 kB of data); moreover, the context shall
 * be reseeded at least once every 2<sup>48</sup> requests. This
 * implementation does not maintain the reseed counter (the threshold is
 * too high to be reached in practice) and does not object to producing
 * more than 64 kB in a single request; thus, the code cannot fail,
 * which corresponds to the fact that the API has no room for error
 * codes. However, this implies that requesting more than 64 kB in one
 * `generate()` request, or making more than 2<sup>48</sup> requests
 * without reseeding, is formally out of NIST specification. There is
 * no currently known security penalty for exceeding the NIST limits,
 * and, in any case, HMAC_DRBG usage in implementing SSL/TLS always
 * stays much below these thresholds.
 *
 *
 * ## AESCTR_DRBG
 *
 * AESCTR_DRBG is a custom PRNG based on AES-128 in CTR mode. This is
 * meant to be used only in situations where you are desperate for
 * speed, and have an hardware-optimized AES/CTR implementation. Whether
 * this will yield perceptible improvements depends on what you use the
 * pseudorandom bytes for, and how many you want; for instance, RSA key
 * pair generation uses a substantial amount of randomness, and using
 * AESCTR_DRBG instead of HMAC_DRBG yields a 15 to 20% increase in key
 * generation speed on a recent x86 CPU (Intel Core i7-6567U at 3.30 GHz).
 *
 * Internally, it uses CTR mode with successive counter values, starting
 * at zero (counter value expressed over 128 bits, big-endian convention).
 * The counter is not allowed to reach 32768; thus, every 32768*16 bytes
 * at most, the `update()` function is run (on an empty seed, if none is
 * provided). The `update()` function computes the new AES-128 key by
 * applying a custom hash function to the concatenation of a state-dependent
 * word (encryption of an all-one block with the current key) and the new
 * seed. The custom hash function uses Hirose's construction over AES-256;
 * see the comments in `aesctr_drbg.c` for details.
 *
 * This DRBG does not follow an existing standard, and thus should be
 * considered as inadequate for production use until it has been properly
 * analysed.
 */

/**
 * \brief Class type for PRNG implementations.
 *
 * A `br_prng_class` instance references the methods implementing a PRNG.
 * Constant instances of this structure are defined for each implemented
 * PRNG. Such instances are also called "vtables".
 */
typedef struct br_prng_class_ br_prng_class;
struct br_prng_class_ {
	/**
	 * \brief Size (in bytes) of the context structure appropriate for
	 * running this PRNG.
	 */
	size_t context_size;

	/**
	 * \brief Initialisation method.
	 *
	 * The context to initialise is provided as a pointer to its
	 * first field (the vtable pointer); this function sets that
	 * first field to a pointer to the vtable.
	 *
	 * The extra parameters depend on the implementation; each
	 * implementation defines what kind of extra parameters it
	 * expects (if any).
	 *
	 * Requirements on the initial seed depend on the implemented
	 * PRNG.
	 *
	 * \param ctx        PRNG context to initialise.
	 * \param params     extra parameters for the PRNG.
	 * \param seed       initial seed.
	 * \param seed_len   initial seed length (in bytes).
	 */
	void (*init)(const br_prng_class **ctx, const void *params,
		const void *seed, size_t seed_len);

	/**
	 * \brief Random bytes generation.
	 *
	 * This method produces `len` pseudorandom bytes, in the `out`
	 * buffer. The context is updated accordingly.
	 *
	 * \param ctx   PRNG context.
	 * \param out   output buffer.
	 * \param len   number of pseudorandom bytes to produce.
	 */
	void (*generate)(const br_prng_class **ctx, void *out, size_t len);

	/**
	 * \brief Inject additional seed bytes.
	 *
	 * The provided seed bytes are added into the PRNG internal
	 * entropy pool.
	 *
	 * \param ctx        PRNG context.
	 * \param seed       additional seed.
	 * \param seed_len   additional seed length (in bytes).
	 */
	void (*update)(const br_prng_class **ctx,
		const void *seed, size_t seed_len);
};

/**
 * \brief Context for HMAC_DRBG.
 *
 * The context contents are opaque, except the first field, which
 * supports OOP.
 */
typedef struct {
	/**
	 * \brief Pointer to the vtable.
	 *
	 * This field is set with the initialisation method/function.
	 */
	const br_prng_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	unsigned char K[64];
	unsigned char V[64];
	const br_hash_class *digest_class;
#endif
} br_hmac_drbg_context;

/**
 * \brief Statically allocated, constant vtable for HMAC_DRBG.
 */
extern const br_prng_class br_hmac_drbg_vtable;

/**
 * \brief HMAC_DRBG initialisation.
 *
 * The context to initialise is provided as a pointer to its first field
 * (the vtable pointer); this function sets that first field to a
 * pointer to the vtable.
 *
 * The `seed` value is what is called, in NIST terminology, the
 * concatenation of the "seed", "nonce" and "personalization string", in
 * that order.
 *
 * The `digest_class` parameter defines the underlying hash function.
 * Formally, the NIST standard specifies that the hash function shall
 * be only SHA-1 or one of the SHA-2 functions. This implementation also
 * works with any other implemented hash function (such as MD5), but
 * this is non-standard and therefore not recommended.
 *
 * \param ctx            HMAC_DRBG context to initialise.
 * \param digest_class   vtable for the underlying hash function.
 * \param seed           initial seed.
 * \param seed_len       initial seed length (in bytes).
 */
void br_hmac_drbg_init(br_hmac_drbg_context *ctx,
	const br_hash_class *digest_class, const void *seed, size_t seed_len);

/**
 * \brief Random bytes generation with HMAC_DRBG.
 *
 * This method produces `len` pseudorandom bytes, in the `out`
 * buffer. The context is updated accordingly. Formally, requesting
 * more than 65536 bytes in one request falls out of specification
 * limits (but it won't fail).
 *
 * \param ctx   HMAC_DRBG context.
 * \param out   output buffer.
 * \param len   number of pseudorandom bytes to produce.
 */
void br_hmac_drbg_generate(br_hmac_drbg_context *ctx, void *out, size_t len);

/**
 * \brief Inject additional seed bytes in HMAC_DRBG.
 *
 * The provided seed bytes are added into the HMAC_DRBG internal
 * entropy pool. The process does not _replace_ existing entropy,
 * thus pushing non-random bytes (i.e. bytes which are known to the
 * attackers) does not degrade the overall quality of generated bytes.
 *
 * \param ctx        HMAC_DRBG context.
 * \param seed       additional seed.
 * \param seed_len   additional seed length (in bytes).
 */
void br_hmac_drbg_update(br_hmac_drbg_context *ctx,
	const void *seed, size_t seed_len);

/**
 * \brief Get the hash function implementation used by a given instance of
 * HMAC_DRBG.
 *
 * This calls MUST NOT be performed on a context which was not
 * previously initialised.
 *
 * \param ctx   HMAC_DRBG context.
 * \return  the hash function vtable.
 */
static inline const br_hash_class *
br_hmac_drbg_get_hash(const br_hmac_drbg_context *ctx)
{
	return ctx->digest_class;
}

/**
 * \brief Type for a provider of entropy seeds.
 *
 * A "seeder" is a function that is able to obtain random values from
 * some source and inject them as entropy seed in a PRNG. A seeder
 * shall guarantee that the total entropy of the injected seed is large
 * enough to seed a PRNG for purposes of cryptographic key generation
 * (i.e. at least 128 bits).
 *
 * A seeder may report a failure to obtain adequate entropy. Seeders
 * shall endeavour to fix themselves transient errors by trying again;
 * thus, callers may consider reported errors as permanent.
 *
 * \param ctx   PRNG context to seed.
 * \return  1 on success, 0 on error.
 */
typedef int (*br_prng_seeder)(const br_prng_class **ctx);

/**
 * \brief Get a seeder backed by the operating system or hardware.
 *
 * Get a seeder that feeds on RNG facilities provided by the current
 * operating system or hardware. If no such facility is known, then 0
 * is returned.
 *
 * If `name` is not `NULL`, then `*name` is set to a symbolic string
 * that identifies the seeder implementation. If no seeder is returned
 * and `name` is not `NULL`, then `*name` is set to a pointer to the
 * constant string `"none"`.
 *
 * \param name   receiver for seeder name, or `NULL`.
 * \return  the system seeder, if available, or 0.
 */
br_prng_seeder br_prng_seeder_system(const char **name);

/**
 * \brief Context for AESCTR_DRBG.
 *
 * The context contents are opaque, except the first field, which
 * supports OOP.
 */
typedef struct {
	/**
	 * \brief Pointer to the vtable.
	 *
	 * This field is set with the initialisation method/function.
	 */
	const br_prng_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	br_aes_gen_ctr_keys sk;
	uint32_t cc;
#endif
} br_aesctr_drbg_context;

/**
 * \brief Statically allocated, constant vtable for AESCTR_DRBG.
 */
extern const br_prng_class br_aesctr_drbg_vtable;

/**
 * \brief AESCTR_DRBG initialisation.
 *
 * The context to initialise is provided as a pointer to its first field
 * (the vtable pointer); this function sets that first field to a
 * pointer to the vtable.
 *
 * The internal AES key is first set to the all-zero key; then, the
 * `br_aesctr_drbg_update()` function is called with the provided `seed`.
 * The call is performed even if the seed length (`seed_len`) is zero.
 *
 * The `aesctr` parameter defines the underlying AES/CTR implementation.
 *
 * \param ctx        AESCTR_DRBG context to initialise.
 * \param aesctr     vtable for the AES/CTR implementation.
 * \param seed       initial seed (can be `NULL` if `seed_len` is zero).
 * \param seed_len   initial seed length (in bytes).
 */
void br_aesctr_drbg_init(br_aesctr_drbg_context *ctx,
	const br_block_ctr_class *aesctr, const void *seed, size_t seed_len);

/**
 * \brief Random bytes generation with AESCTR_DRBG.
 *
 * This method produces `len` pseudorandom bytes, in the `out`
 * buffer. The context is updated accordingly.
 *
 * \param ctx   AESCTR_DRBG context.
 * \param out   output buffer.
 * \param len   number of pseudorandom bytes to produce.
 */
void br_aesctr_drbg_generate(br_aesctr_drbg_context *ctx,
	void *out, size_t len);

/**
 * \brief Inject additional seed bytes in AESCTR_DRBG.
 *
 * The provided seed bytes are added into the AESCTR_DRBG internal
 * entropy pool. The process does not _replace_ existing entropy,
 * thus pushing non-random bytes (i.e. bytes which are known to the
 * attackers) does not degrade the overall quality of generated bytes.
 *
 * \param ctx        AESCTR_DRBG context.
 * \param seed       additional seed.
 * \param seed_len   additional seed length (in bytes).
 */
void br_aesctr_drbg_update(br_aesctr_drbg_context *ctx,
	const void *seed, size_t seed_len);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_PRF_H__
#define BR_BEARSSL_PRF_H__

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_prf.h
 *
 * # The TLS PRF
 *
 * The "PRF" is the pseudorandom function used internally during the
 * SSL/TLS handshake, notably to expand negotiated shared secrets into
 * the symmetric encryption keys that will be used to process the
 * application data.
 *
 * TLS 1.0 and 1.1 define a PRF that is based on both MD5 and SHA-1. This
 * is implemented by the `br_tls10_prf()` function.
 *
 * TLS 1.2 redefines the PRF, using an explicit hash function. The
 * `br_tls12_sha256_prf()` and `br_tls12_sha384_prf()` functions apply that
 * PRF with, respectively, SHA-256 and SHA-384. Most standard cipher suites
 * rely on the SHA-256 based PRF, but some use SHA-384.
 *
 * The PRF always uses as input three parameters: a "secret" (some
 * bytes), a "label" (ASCII string), and a "seed" (again some bytes). An
 * arbitrary output length can be produced. The "seed" is provided as an
 * arbitrary number of binary chunks, that gets internally concatenated.
 */

/**
 * \brief Type for a seed chunk.
 *
 * Each chunk may have an arbitrary length, and may be empty (no byte at
 * all). If the chunk length is zero, then the pointer to the chunk data
 * may be `NULL`.
 */
typedef struct {
	/**
	 * \brief Pointer to the chunk data.
	 */
	const void *data;

	/**
	 * \brief Chunk length (in bytes).
	 */
	size_t len;
} br_tls_prf_seed_chunk;

/**
 * \brief PRF implementation for TLS 1.0 and 1.1.
 *
 * This PRF is the one specified by TLS 1.0 and 1.1. It internally uses
 * MD5 and SHA-1.
 *
 * \param dst          destination buffer.
 * \param len          output length (in bytes).
 * \param secret       secret value (key) for this computation.
 * \param secret_len   length of "secret" (in bytes).
 * \param label        PRF label (zero-terminated ASCII string).
 * \param seed_num     number of seed chunks.
 * \param seed         seed chnks for this computation (usually non-secret).
 */
void br_tls10_prf(void *dst, size_t len,
	const void *secret, size_t secret_len, const char *label,
	size_t seed_num, const br_tls_prf_seed_chunk *seed);

/**
 * \brief PRF implementation for TLS 1.2, with SHA-256.
 *
 * This PRF is the one specified by TLS 1.2, when the underlying hash
 * function is SHA-256.
 *
 * \param dst          destination buffer.
 * \param len          output length (in bytes).
 * \param secret       secret value (key) for this computation.
 * \param secret_len   length of "secret" (in bytes).
 * \param label        PRF label (zero-terminated ASCII string).
 * \param seed_num     number of seed chunks.
 * \param seed         seed chnks for this computation (usually non-secret).
 */
void br_tls12_sha256_prf(void *dst, size_t len,
	const void *secret, size_t secret_len, const char *label,
	size_t seed_num, const br_tls_prf_seed_chunk *seed);

/**
 * \brief PRF implementation for TLS 1.2, with SHA-384.
 *
 * This PRF is the one specified by TLS 1.2, when the underlying hash
 * function is SHA-384.
 *
 * \param dst          destination buffer.
 * \param len          output length (in bytes).
 * \param secret       secret value (key) for this computation.
 * \param secret_len   length of "secret" (in bytes).
 * \param label        PRF label (zero-terminated ASCII string).
 * \param seed_num     number of seed chunks.
 * \param seed         seed chnks for this computation (usually non-secret).
 */
void br_tls12_sha384_prf(void *dst, size_t len,
	const void *secret, size_t secret_len, const char *label,
	size_t seed_num, const br_tls_prf_seed_chunk *seed);

/** 
 * brief A convenient type name for a PRF implementation.
 *
 * \param dst          destination buffer.
 * \param len          output length (in bytes).
 * \param secret       secret value (key) for this computation.
 * \param secret_len   length of "secret" (in bytes).
 * \param label        PRF label (zero-terminated ASCII string).
 * \param seed_num     number of seed chunks.
 * \param seed         seed chnks for this computation (usually non-secret).
 */
typedef void (*br_tls_prf_impl)(void *dst, size_t len,
	const void *secret, size_t secret_len, const char *label,
	size_t seed_num, const br_tls_prf_seed_chunk *seed);

#ifdef __cplusplus
}
#endif

#endif


/*
 * Copyright (c) 2017 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_AEAD_H__
#define BR_BEARSSL_AEAD_H__

#include <stddef.h>
#include <stdint.h>




#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_aead.h
 *
 * # Authenticated Encryption with Additional Data
 *
 * This file documents the API for AEAD encryption.
 *
 *
 * ## Procedural API
 *
 * An AEAD algorithm processes messages and provides confidentiality
 * (encryption) and checked integrity (MAC). It uses the following
 * parameters:
 *
 *   - A symmetric key. Exact size depends on the AEAD algorithm.
 *
 *   - A nonce (IV). Size depends on the AEAD algorithm; for most
 *     algorithms, it is crucial for security that any given nonce
 *     value is never used twice for the same key and distinct
 *     messages.
 *
 *   - Data to encrypt and protect.
 *
 *   - Additional authenticated data, which is covered by the MAC but
 *     otherwise left untouched (i.e. not encrypted).
 *
 * The AEAD algorithm encrypts the data, and produces an authentication
 * tag. It is assumed that the encrypted data, the tag, the additional
 * authenticated data and the nonce are sent to the receiver; the
 * additional data and the nonce may be implicit (e.g. using elements of
 * the underlying transport protocol, such as record sequence numbers).
 * The receiver will recompute the tag value and compare it with the one
 * received; if they match, then the data is correct, and can be
 * decrypted and used; otherwise, at least one of the elements was
 * altered in transit, normally leading to wholesale rejection of the
 * complete message.
 *
 * For each AEAD algorithm, identified by a symbolic name (hereafter
 * denoted as "`xxx`"), the following functions are defined:
 *
 *   - `br_xxx_init()`
 *
 *     Initialise the AEAD algorithm, on a provided context structure.
 *     Exact parameters depend on the algorithm, and may include
 *     pointers to extra implementations and context structures. The
 *     secret key is provided at this point, either directly or
 *     indirectly.
 *
 *   - `br_xxx_reset()`
 *
 *     Start a new AEAD computation. The nonce value is provided as
 *     parameter to this function.
 *
 *   - `br_xxx_aad_inject()`
 *
 *     Inject some additional authenticated data. Additional data may
 *     be provided in several chunks of arbitrary length.
 *
 *   - `br_xxx_flip()`
 *
 *     This function MUST be called after injecting all additional
 *     authenticated data, and before beginning to encrypt the plaintext
 *     (or decrypt the ciphertext).
 *
 *   - `br_xxx_run()`
 *
 *     Process some plaintext (to encrypt) or ciphertext (to decrypt).
 *     Encryption/decryption is done in place. Data may be provided in
 *     several chunks of arbitrary length.
 *
 *   - `br_xxx_get_tag()`
 *
 *     Compute the authentication tag. All message data (encrypted or
 *     decrypted) must have been injected at that point. Also, this
 *     call may modify internal context elements, so it may be called
 *     only once for a given AEAD computation.
 *
 *   - `br_xxx_check_tag()`
 *
 *     An alternative to `br_xxx_get_tag()`, meant to be used by the
 *     receiver: the authentication tag is internally recomputed, and
 *     compared with the one provided as parameter.
 *
 * This API makes the following assumptions on the AEAD algorithm:
 *
 *   - Encryption does not expand the size of the ciphertext; there is
 *     no padding. This is true of most modern AEAD modes such as GCM.
 *
 *   - The additional authenticated data must be processed first,
 *     before the encrypted/decrypted data.
 *
 *   - Nonce, plaintext and additional authenticated data all consist
 *     in an integral number of bytes. There is no provision to use
 *     elements whose length in bits is not a multiple of 8.
 *
 * Each AEAD algorithm has its own requirements and limits on the sizes
 * of additional data and plaintext. This API does not provide any
 * way to report invalid usage; it is up to the caller to ensure that
 * the provided key, nonce, and data elements all fit the algorithm's
 * requirements.
 *
 *
 * ## Object-Oriented API
 *
 * Each context structure begins with a field (called `vtable`) that
 * points to an instance of a structure that references the relevant
 * functions through pointers. Each such structure contains the
 * following:
 *
 *   - `reset`
 *
 *     Pointer to the reset function, that allows starting a new
 *     computation.
 *
 *   - `aad_inject`
 *
 *     Pointer to the additional authenticated data injection function.
 *
 *   - `flip`
 *
 *     Pointer to the function that transitions from additional data
 *     to main message data processing.
 *
 *   - `get_tag`
 *
 *     Pointer to the function that computes and returns the tag.
 *
 *   - `check_tag`
 *
 *     Pointer to the function that computes and verifies the tag against
 *     a received value.
 *
 * Note that there is no OOP method for context initialisation: the
 * various AEAD algorithms have different requirements that would not
 * map well to a single initialisation API.
 *
 * The OOP API is not provided for CCM, due to its specific requirements
 * (length of plaintext must be known in advance).
 */

/**
 * \brief Class type of an AEAD algorithm.
 */
typedef struct br_aead_class_ br_aead_class;
struct br_aead_class_ {

	/**
	 * \brief Size (in bytes) of authentication tags created by
	 * this AEAD algorithm.
	 */
	size_t tag_size;

	/**
	 * \brief Reset an AEAD context.
	 *
	 * This function resets an already initialised AEAD context for
	 * a new computation run. Implementations and keys are
	 * conserved. This function can be called at any time; it
	 * cancels any ongoing AEAD computation that uses the provided
	 * context structure.

	 * The provided IV is a _nonce_. Each AEAD algorithm has its
	 * own requirements on IV size and contents; for most of them,
	 * it is crucial to security that each nonce value is used
	 * only once for a given secret key.
	 *
	 * \param cc    AEAD context structure.
	 * \param iv    AEAD nonce to use.
	 * \param len   AEAD nonce length (in bytes).
	 */
	void (*reset)(const br_aead_class **cc, const void *iv, size_t len);

	/**
	 * \brief Inject additional authenticated data.
	 *
	 * The provided data is injected into a running AEAD
	 * computation. Additional data must be injected _before_ the
	 * call to `flip()`. Additional data can be injected in several
	 * chunks of arbitrary length.
	 *
	 * \param cc     AEAD context structure.
	 * \param data   pointer to additional authenticated data.
	 * \param len    length of additional authenticated data (in bytes).
	 */
	void (*aad_inject)(const br_aead_class **cc,
		const void *data, size_t len);

	/**
	 * \brief Finish injection of additional authenticated data.
	 *
	 * This function MUST be called before beginning the actual
	 * encryption or decryption (with `run()`), even if no
	 * additional authenticated data was injected. No additional
	 * authenticated data may be injected after this function call.
	 *
	 * \param cc   AEAD context structure.
	 */
	void (*flip)(const br_aead_class **cc);

	/**
	 * \brief Encrypt or decrypt some data.
	 *
	 * Data encryption or decryption can be done after `flip()` has
	 * been called on the context. If `encrypt` is non-zero, then
	 * the provided data shall be plaintext, and it is encrypted in
	 * place. Otherwise, the data shall be ciphertext, and it is
	 * decrypted in place.
	 *
	 * Data may be provided in several chunks of arbitrary length.
	 *
	 * \param cc        AEAD context structure.
	 * \param encrypt   non-zero for encryption, zero for decryption.
	 * \param data      data to encrypt or decrypt.
	 * \param len       data length (in bytes).
	 */
	void (*run)(const br_aead_class **cc, int encrypt,
		void *data, size_t len);

	/**
	 * \brief Compute authentication tag.
	 *
	 * Compute the AEAD authentication tag. The tag length depends
	 * on the AEAD algorithm; it is written in the provided `tag`
	 * buffer. This call terminates the AEAD run: no data may be
	 * processed with that AEAD context afterwards, until `reset()`
	 * is called to initiate a new AEAD run.
	 *
	 * The tag value must normally be sent along with the encrypted
	 * data. When decrypting, the tag value must be recomputed and
	 * compared with the received tag: if the two tag values differ,
	 * then either the tag or the encrypted data was altered in
	 * transit. As an alternative to this function, the
	 * `check_tag()` function may be used to compute and check the
	 * tag value.
	 *
	 * Tag length depends on the AEAD algorithm.
	 *
	 * \param cc    AEAD context structure.
	 * \param tag   destination buffer for the tag.
	 */
	void (*get_tag)(const br_aead_class **cc, void *tag);

	/**
	 * \brief Compute and check authentication tag.
	 *
	 * This function is an alternative to `get_tag()`, and is
	 * normally used on the receiving end (i.e. when decrypting
	 * messages). The tag value is recomputed and compared with the
	 * provided tag value. If they match, 1 is returned; on
	 * mismatch, 0 is returned. A returned value of 0 means that the
	 * data or the tag was altered in transit, normally leading to
	 * wholesale rejection of the complete message.
	 *
	 * Tag length depends on the AEAD algorithm.
	 *
	 * \param cc    AEAD context structure.
	 * \param tag   tag value to compare with.
	 * \return  1 on success (exact match of tag value), 0 otherwise.
	 */
	uint32_t (*check_tag)(const br_aead_class **cc, const void *tag);

	/**
	 * \brief Compute authentication tag (with truncation).
	 *
	 * This function is similar to `get_tag()`, except that the tag
	 * length is provided. Some AEAD algorithms allow several tag
	 * lengths, usually by truncating the normal tag. Shorter tags
	 * mechanically increase success probability of forgeries.
	 * The range of allowed tag lengths depends on the algorithm.
	 *
	 * \param cc    AEAD context structure.
	 * \param tag   destination buffer for the tag.
	 * \param len   tag length (in bytes).
	 */
	void (*get_tag_trunc)(const br_aead_class **cc, void *tag, size_t len);

	/**
	 * \brief Compute and check authentication tag (with truncation).
	 *
	 * This function is similar to `check_tag()` except that it
	 * works over an explicit tag length. See `get_tag()` for a
	 * discussion of explicit tag lengths; the range of allowed tag
	 * lengths depends on the algorithm.
	 *
	 * \param cc    AEAD context structure.
	 * \param tag   tag value to compare with.
	 * \param len   tag length (in bytes).
	 * \return  1 on success (exact match of tag value), 0 otherwise.
	 */
	uint32_t (*check_tag_trunc)(const br_aead_class **cc,
		const void *tag, size_t len);
};

/**
 * \brief Context structure for GCM.
 *
 * GCM is an AEAD mode that combines a block cipher in CTR mode with a
 * MAC based on GHASH, to provide authenticated encryption:
 *
 *   - Any block cipher with 16-byte blocks can be used with GCM.
 *
 *   - The nonce can have any length, from 0 up to 2^64-1 bits; however,
 *     96-bit nonces (12 bytes) are recommended (nonces with a length
 *     distinct from 12 bytes are internally hashed, which risks reusing
 *     nonce value with a small but not always negligible probability).
 *
 *   - Additional authenticated data may have length up to 2^64-1 bits.
 *
 *   - Message length may range up to 2^39-256 bits at most.
 *
 *   - The authentication tag has length 16 bytes.
 *
 * The GCM initialisation function receives as parameter an
 * _initialised_ block cipher implementation context, with the secret
 * key already set. A pointer to that context will be kept within the
 * GCM context structure. It is up to the caller to allocate and
 * initialise that block cipher context.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_aead_class *vtable;

#ifndef BR_DOXYGEN_IGNORE
	const br_block_ctr_class **bctx;
	br_ghash gh;
	unsigned char h[16];
	unsigned char j0_1[12];
	unsigned char buf[16];
	unsigned char y[16];
	uint32_t j0_2, jc;
	uint64_t count_aad, count_ctr;
#endif
} br_gcm_context;

/**
 * \brief Initialize a GCM context.
 *
 * A block cipher implementation, with its initialised context structure,
 * is provided. The block cipher MUST use 16-byte blocks in CTR mode,
 * and its secret key MUST have been already set in the provided context.
 * A GHASH implementation must also be provided. The parameters are linked
 * in the GCM context.
 *
 * After this function has been called, the `br_gcm_reset()` function must
 * be called, to provide the IV for GCM computation.
 *
 * \param ctx    GCM context structure.
 * \param bctx   block cipher context (already initialised with secret key).
 * \param gh     GHASH implementation.
 */
void br_gcm_init(br_gcm_context *ctx,
	const br_block_ctr_class **bctx, br_ghash gh);

/**
 * \brief Reset a GCM context.
 *
 * This function resets an already initialised GCM context for a new
 * computation run. Implementations and keys are conserved. This function
 * can be called at any time; it cancels any ongoing GCM computation that
 * uses the provided context structure.
 *
 * The provided IV is a _nonce_. It is critical to GCM security that IV
 * values are not repeated for the same encryption key. IV can have
 * arbitrary length (up to 2^64-1 bits), but the "normal" length is
 * 96 bits (12 bytes).
 *
 * \param ctx   GCM context structure.
 * \param iv    GCM nonce to use.
 * \param len   GCM nonce length (in bytes).
 */
void br_gcm_reset(br_gcm_context *ctx, const void *iv, size_t len);

/**
 * \brief Inject additional authenticated data into GCM.
 *
 * The provided data is injected into a running GCM computation. Additional
 * data must be injected _before_ the call to `br_gcm_flip()`.
 * Additional data can be injected in several chunks of arbitrary length;
 * the maximum total size of additional authenticated data is 2^64-1
 * bits.
 *
 * \param ctx    GCM context structure.
 * \param data   pointer to additional authenticated data.
 * \param len    length of additional authenticated data (in bytes).
 */
void br_gcm_aad_inject(br_gcm_context *ctx, const void *data, size_t len);

/**
 * \brief Finish injection of additional authenticated data into GCM.
 *
 * This function MUST be called before beginning the actual encryption
 * or decryption (with `br_gcm_run()`), even if no additional authenticated
 * data was injected. No additional authenticated data may be injected
 * after this function call.
 *
 * \param ctx   GCM context structure.
 */
void br_gcm_flip(br_gcm_context *ctx);

/**
 * \brief Encrypt or decrypt some data with GCM.
 *
 * Data encryption or decryption can be done after `br_gcm_flip()`
 * has been called on the context. If `encrypt` is non-zero, then the
 * provided data shall be plaintext, and it is encrypted in place.
 * Otherwise, the data shall be ciphertext, and it is decrypted in place.
 *
 * Data may be provided in several chunks of arbitrary length. The maximum
 * total length for data is 2^39-256 bits, i.e. about 65 gigabytes.
 *
 * \param ctx       GCM context structure.
 * \param encrypt   non-zero for encryption, zero for decryption.
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 */
void br_gcm_run(br_gcm_context *ctx, int encrypt, void *data, size_t len);

/**
 * \brief Compute GCM authentication tag.
 *
 * Compute the GCM authentication tag. The tag is a 16-byte value which
 * is written in the provided `tag` buffer. This call terminates the
 * GCM run: no data may be processed with that GCM context afterwards,
 * until `br_gcm_reset()` is called to initiate a new GCM run.
 *
 * The tag value must normally be sent along with the encrypted data.
 * When decrypting, the tag value must be recomputed and compared with
 * the received tag: if the two tag values differ, then either the tag
 * or the encrypted data was altered in transit. As an alternative to
 * this function, the `br_gcm_check_tag()` function can be used to
 * compute and check the tag value.
 *
 * \param ctx   GCM context structure.
 * \param tag   destination buffer for the tag (16 bytes).
 */
void br_gcm_get_tag(br_gcm_context *ctx, void *tag);

/**
 * \brief Compute and check GCM authentication tag.
 *
 * This function is an alternative to `br_gcm_get_tag()`, normally used
 * on the receiving end (i.e. when decrypting value). The tag value is
 * recomputed and compared with the provided tag value. If they match, 1
 * is returned; on mismatch, 0 is returned. A returned value of 0 means
 * that the data or the tag was altered in transit, normally leading to
 * wholesale rejection of the complete message.
 *
 * \param ctx   GCM context structure.
 * \param tag   tag value to compare with (16 bytes).
 * \return  1 on success (exact match of tag value), 0 otherwise.
 */
uint32_t br_gcm_check_tag(br_gcm_context *ctx, const void *tag);

/**
 * \brief Compute GCM authentication tag (with truncation).
 *
 * This function is similar to `br_gcm_get_tag()`, except that it allows
 * the tag to be truncated to a smaller length. The intended tag length
 * is provided as `len` (in bytes); it MUST be no more than 16, but
 * it may be smaller. Note that decreasing tag length mechanically makes
 * forgeries easier; NIST SP 800-38D specifies that the tag length shall
 * lie between 12 and 16 bytes (inclusive), but may be truncated down to
 * 4 or 8 bytes, for specific applications that can tolerate it. It must
 * also be noted that successful forgeries leak information on the
 * authentication key, making subsequent forgeries easier. Therefore,
 * tag truncation, and in particular truncation to sizes lower than 12
 * bytes, shall be envisioned only with great care.
 *
 * The tag is written in the provided `tag` buffer. This call terminates
 * the GCM run: no data may be processed with that GCM context
 * afterwards, until `br_gcm_reset()` is called to initiate a new GCM
 * run.
 *
 * The tag value must normally be sent along with the encrypted data.
 * When decrypting, the tag value must be recomputed and compared with
 * the received tag: if the two tag values differ, then either the tag
 * or the encrypted data was altered in transit. As an alternative to
 * this function, the `br_gcm_check_tag_trunc()` function can be used to
 * compute and check the tag value.
 *
 * \param ctx   GCM context structure.
 * \param tag   destination buffer for the tag.
 * \param len   tag length (16 bytes or less).
 */
void br_gcm_get_tag_trunc(br_gcm_context *ctx, void *tag, size_t len);

/**
 * \brief Compute and check GCM authentication tag (with truncation).
 *
 * This function is an alternative to `br_gcm_get_tag_trunc()`, normally used
 * on the receiving end (i.e. when decrypting value). The tag value is
 * recomputed and compared with the provided tag value. If they match, 1
 * is returned; on mismatch, 0 is returned. A returned value of 0 means
 * that the data or the tag was altered in transit, normally leading to
 * wholesale rejection of the complete message.
 *
 * Tag length MUST be 16 bytes or less. The normal GCM tag length is 16
 * bytes. See `br_check_tag_trunc()` for some discussion on the potential
 * perils of truncating authentication tags.
 *
 * \param ctx   GCM context structure.
 * \param tag   tag value to compare with.
 * \param len   tag length (in bytes).
 * \return  1 on success (exact match of tag value), 0 otherwise.
 */
uint32_t br_gcm_check_tag_trunc(br_gcm_context *ctx,
	const void *tag, size_t len);

/**
 * \brief Class instance for GCM.
 */
extern const br_aead_class br_gcm_vtable;

/**
 * \brief Context structure for EAX.
 *
 * EAX is an AEAD mode that combines a block cipher in CTR mode with
 * CBC-MAC using the same block cipher and the same key, to provide
 * authenticated encryption:
 *
 *   - Any block cipher with 16-byte blocks can be used with EAX
 *     (technically, other block sizes are defined as well, but this
 *     is not implemented by these functions; shorter blocks also
 *     imply numerous security issues).
 *
 *   - The nonce can have any length, as long as nonce values are
 *     not reused (thus, if nonces are randomly selected, the nonce
 *     size should be such that reuse probability is negligible).
 *
 *   - Additional authenticated data length is unlimited.
 *
 *   - Message length is unlimited.
 *
 *   - The authentication tag has length 16 bytes.
 *
 * The EAX initialisation function receives as parameter an
 * _initialised_ block cipher implementation context, with the secret
 * key already set. A pointer to that context will be kept within the
 * EAX context structure. It is up to the caller to allocate and
 * initialise that block cipher context.
 */
typedef struct {
	/** \brief Pointer to vtable for this context. */
	const br_aead_class *vtable;

#ifndef BR_DOXYGEN_IGNORE
	const br_block_ctrcbc_class **bctx;
	unsigned char L2[16];
	unsigned char L4[16];
	unsigned char nonce[16];
	unsigned char head[16];
	unsigned char ctr[16];
	unsigned char cbcmac[16];
	unsigned char buf[16];
	size_t ptr;
#endif
} br_eax_context;

/**
 * \brief EAX captured state.
 *
 * Some internal values computed by EAX may be captured at various
 * points, and reused for another EAX run with the same secret key,
 * for lower per-message overhead. Captured values do not depend on
 * the nonce.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	unsigned char st[3][16];
#endif
} br_eax_state;

/**
 * \brief Initialize an EAX context.
 *
 * A block cipher implementation, with its initialised context
 * structure, is provided. The block cipher MUST use 16-byte blocks in
 * CTR + CBC-MAC mode, and its secret key MUST have been already set in
 * the provided context. The parameters are linked in the EAX context.
 *
 * After this function has been called, the `br_eax_reset()` function must
 * be called, to provide the nonce for EAX computation.
 *
 * \param ctx    EAX context structure.
 * \param bctx   block cipher context (already initialised with secret key).
 */
void br_eax_init(br_eax_context *ctx, const br_block_ctrcbc_class **bctx);

/**
 * \brief Capture pre-AAD state.
 *
 * This function precomputes key-dependent data, and stores it in the
 * provided `st` structure. This structure should then be used with
 * `br_eax_reset_pre_aad()`, or updated with `br_eax_get_aad_mac()`
 * and then used with `br_eax_reset_post_aad()`.
 *
 * The EAX context structure is unmodified by this call.
 *
 * \param ctx   EAX context structure.
 * \param st    recipient for captured state.
 */
void br_eax_capture(const br_eax_context *ctx, br_eax_state *st);

/**
 * \brief Reset an EAX context.
 *
 * This function resets an already initialised EAX context for a new
 * computation run. Implementations and keys are conserved. This function
 * can be called at any time; it cancels any ongoing EAX computation that
 * uses the provided context structure.
 *
 * It is critical to EAX security that nonce values are not repeated for
 * the same encryption key. Nonces can have arbitrary length. If nonces
 * are randomly generated, then a nonce length of at least 128 bits (16
 * bytes) is recommended, to make nonce reuse probability sufficiently
 * low.
 *
 * \param ctx     EAX context structure.
 * \param nonce   EAX nonce to use.
 * \param len     EAX nonce length (in bytes).
 */
void br_eax_reset(br_eax_context *ctx, const void *nonce, size_t len);

/**
 * \brief Reset an EAX context with a pre-AAD captured state.
 *
 * This function is an alternative to `br_eax_reset()`, that reuses a
 * previously captured state structure for lower per-message overhead.
 * The state should have been populated with `br_eax_capture_state()`
 * but not updated with `br_eax_get_aad_mac()`.
 *
 * After this function is called, additional authenticated data MUST
 * be injected. At least one byte of additional authenticated data
 * MUST be provided with `br_eax_aad_inject()`; computation result will
 * be incorrect if `br_eax_flip()` is called right away.
 *
 * After injection of the AAD and call to `br_eax_flip()`, at least
 * one message byte must be provided. Empty messages are not supported
 * with this reset mode.
 *
 * \param ctx     EAX context structure.
 * \param st      pre-AAD captured state.
 * \param nonce   EAX nonce to use.
 * \param len     EAX nonce length (in bytes).
 */
void br_eax_reset_pre_aad(br_eax_context *ctx, const br_eax_state *st,
	const void *nonce, size_t len);

/**
 * \brief Reset an EAX context with a post-AAD captured state.
 *
 * This function is an alternative to `br_eax_reset()`, that reuses a
 * previously captured state structure for lower per-message overhead.
 * The state should have been populated with `br_eax_capture_state()`
 * and then updated with `br_eax_get_aad_mac()`.
 *
 * After this function is called, message data MUST be injected. The
 * `br_eax_flip()` function MUST NOT be called. At least one byte of
 * message data MUST be provided with `br_eax_run()`; empty messages
 * are not supported with this reset mode.
 *
 * \param ctx     EAX context structure.
 * \param st      post-AAD captured state.
 * \param nonce   EAX nonce to use.
 * \param len     EAX nonce length (in bytes).
 */
void br_eax_reset_post_aad(br_eax_context *ctx, const br_eax_state *st,
	const void *nonce, size_t len);

/**
 * \brief Inject additional authenticated data into EAX.
 *
 * The provided data is injected into a running EAX computation. Additional
 * data must be injected _before_ the call to `br_eax_flip()`.
 * Additional data can be injected in several chunks of arbitrary length;
 * the total amount of additional authenticated data is unlimited.
 *
 * \param ctx    EAX context structure.
 * \param data   pointer to additional authenticated data.
 * \param len    length of additional authenticated data (in bytes).
 */
void br_eax_aad_inject(br_eax_context *ctx, const void *data, size_t len);

/**
 * \brief Finish injection of additional authenticated data into EAX.
 *
 * This function MUST be called before beginning the actual encryption
 * or decryption (with `br_eax_run()`), even if no additional authenticated
 * data was injected. No additional authenticated data may be injected
 * after this function call.
 *
 * \param ctx   EAX context structure.
 */
void br_eax_flip(br_eax_context *ctx);

/**
 * \brief Obtain a copy of the MAC on additional authenticated data.
 *
 * This function may be called only after `br_eax_flip()`; it copies the
 * AAD-specific MAC value into the provided state. The MAC value depends
 * on the secret key and the additional data itself, but not on the
 * nonce. The updated state `st` is meant to be used as parameter for a
 * further `br_eax_reset_post_aad()` call.
 *
 * \param ctx   EAX context structure.
 * \param st    captured state to update.
 */
static inline void
br_eax_get_aad_mac(const br_eax_context *ctx, br_eax_state *st)
{
	memcpy(st->st[1], ctx->head, sizeof ctx->head);
}

/**
 * \brief Encrypt or decrypt some data with EAX.
 *
 * Data encryption or decryption can be done after `br_eax_flip()`
 * has been called on the context. If `encrypt` is non-zero, then the
 * provided data shall be plaintext, and it is encrypted in place.
 * Otherwise, the data shall be ciphertext, and it is decrypted in place.
 *
 * Data may be provided in several chunks of arbitrary length.
 *
 * \param ctx       EAX context structure.
 * \param encrypt   non-zero for encryption, zero for decryption.
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 */
void br_eax_run(br_eax_context *ctx, int encrypt, void *data, size_t len);

/**
 * \brief Compute EAX authentication tag.
 *
 * Compute the EAX authentication tag. The tag is a 16-byte value which
 * is written in the provided `tag` buffer. This call terminates the
 * EAX run: no data may be processed with that EAX context afterwards,
 * until `br_eax_reset()` is called to initiate a new EAX run.
 *
 * The tag value must normally be sent along with the encrypted data.
 * When decrypting, the tag value must be recomputed and compared with
 * the received tag: if the two tag values differ, then either the tag
 * or the encrypted data was altered in transit. As an alternative to
 * this function, the `br_eax_check_tag()` function can be used to
 * compute and check the tag value.
 *
 * \param ctx   EAX context structure.
 * \param tag   destination buffer for the tag (16 bytes).
 */
void br_eax_get_tag(br_eax_context *ctx, void *tag);

/**
 * \brief Compute and check EAX authentication tag.
 *
 * This function is an alternative to `br_eax_get_tag()`, normally used
 * on the receiving end (i.e. when decrypting value). The tag value is
 * recomputed and compared with the provided tag value. If they match, 1
 * is returned; on mismatch, 0 is returned. A returned value of 0 means
 * that the data or the tag was altered in transit, normally leading to
 * wholesale rejection of the complete message.
 *
 * \param ctx   EAX context structure.
 * \param tag   tag value to compare with (16 bytes).
 * \return  1 on success (exact match of tag value), 0 otherwise.
 */
uint32_t br_eax_check_tag(br_eax_context *ctx, const void *tag);

/**
 * \brief Compute EAX authentication tag (with truncation).
 *
 * This function is similar to `br_eax_get_tag()`, except that it allows
 * the tag to be truncated to a smaller length. The intended tag length
 * is provided as `len` (in bytes); it MUST be no more than 16, but
 * it may be smaller. Note that decreasing tag length mechanically makes
 * forgeries easier; NIST SP 800-38D specifies that the tag length shall
 * lie between 12 and 16 bytes (inclusive), but may be truncated down to
 * 4 or 8 bytes, for specific applications that can tolerate it. It must
 * also be noted that successful forgeries leak information on the
 * authentication key, making subsequent forgeries easier. Therefore,
 * tag truncation, and in particular truncation to sizes lower than 12
 * bytes, shall be envisioned only with great care.
 *
 * The tag is written in the provided `tag` buffer. This call terminates
 * the EAX run: no data may be processed with that EAX context
 * afterwards, until `br_eax_reset()` is called to initiate a new EAX
 * run.
 *
 * The tag value must normally be sent along with the encrypted data.
 * When decrypting, the tag value must be recomputed and compared with
 * the received tag: if the two tag values differ, then either the tag
 * or the encrypted data was altered in transit. As an alternative to
 * this function, the `br_eax_check_tag_trunc()` function can be used to
 * compute and check the tag value.
 *
 * \param ctx   EAX context structure.
 * \param tag   destination buffer for the tag.
 * \param len   tag length (16 bytes or less).
 */
void br_eax_get_tag_trunc(br_eax_context *ctx, void *tag, size_t len);

/**
 * \brief Compute and check EAX authentication tag (with truncation).
 *
 * This function is an alternative to `br_eax_get_tag_trunc()`, normally used
 * on the receiving end (i.e. when decrypting value). The tag value is
 * recomputed and compared with the provided tag value. If they match, 1
 * is returned; on mismatch, 0 is returned. A returned value of 0 means
 * that the data or the tag was altered in transit, normally leading to
 * wholesale rejection of the complete message.
 *
 * Tag length MUST be 16 bytes or less. The normal EAX tag length is 16
 * bytes. See `br_check_tag_trunc()` for some discussion on the potential
 * perils of truncating authentication tags.
 *
 * \param ctx   EAX context structure.
 * \param tag   tag value to compare with.
 * \param len   tag length (in bytes).
 * \return  1 on success (exact match of tag value), 0 otherwise.
 */
uint32_t br_eax_check_tag_trunc(br_eax_context *ctx,
	const void *tag, size_t len);

/**
 * \brief Class instance for EAX.
 */
extern const br_aead_class br_eax_vtable;

/**
 * \brief Context structure for CCM.
 *
 * CCM is an AEAD mode that combines a block cipher in CTR mode with
 * CBC-MAC using the same block cipher and the same key, to provide
 * authenticated encryption:
 *
 *   - Any block cipher with 16-byte blocks can be used with CCM
 *     (technically, other block sizes are defined as well, but this
 *     is not implemented by these functions; shorter blocks also
 *     imply numerous security issues).
 *
 *   - The authentication tag length, and plaintext length, MUST be
 *     known when starting processing data. Plaintext and ciphertext
 *     can still be provided by chunks, but the total size must match
 *     the value provided upon initialisation.
 *
 *   - The nonce length is constrained between 7 and 13 bytes (inclusive).
 *     Furthermore, the plaintext length, when encoded, must fit over
 *     15-nonceLen bytes; thus, if the nonce has length 13 bytes, then
 *     the plaintext length cannot exceed 65535 bytes.
 *
 *   - Additional authenticated data length is practically unlimited
 *     (formal limit is at 2^64 bytes).
 *
 *   - The authentication tag has length 4 to 16 bytes (even values only).
 *
 * The CCM initialisation function receives as parameter an
 * _initialised_ block cipher implementation context, with the secret
 * key already set. A pointer to that context will be kept within the
 * CCM context structure. It is up to the caller to allocate and
 * initialise that block cipher context.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	const br_block_ctrcbc_class **bctx;
	unsigned char ctr[16];
	unsigned char cbcmac[16];
	unsigned char tagmask[16];
	unsigned char buf[16];
	size_t ptr;
	size_t tag_len;
#endif
} br_ccm_context;

/**
 * \brief Initialize a CCM context.
 *
 * A block cipher implementation, with its initialised context
 * structure, is provided. The block cipher MUST use 16-byte blocks in
 * CTR + CBC-MAC mode, and its secret key MUST have been already set in
 * the provided context. The parameters are linked in the CCM context.
 *
 * After this function has been called, the `br_ccm_reset()` function must
 * be called, to provide the nonce for CCM computation.
 *
 * \param ctx    CCM context structure.
 * \param bctx   block cipher context (already initialised with secret key).
 */
void br_ccm_init(br_ccm_context *ctx, const br_block_ctrcbc_class **bctx);

/**
 * \brief Reset a CCM context.
 *
 * This function resets an already initialised CCM context for a new
 * computation run. Implementations and keys are conserved. This function
 * can be called at any time; it cancels any ongoing CCM computation that
 * uses the provided context structure.
 *
 * The `aad_len` parameter contains the total length, in bytes, of the
 * additional authenticated data. It may be zero. That length MUST be
 * exact.
 *
 * The `data_len` parameter contains the total length, in bytes, of the
 * data that will be injected (plaintext or ciphertext). That length MUST
 * be exact. Moreover, that length MUST be less than 2^(8*(15-nonce_len)).
 *
 * The nonce length (`nonce_len`), in bytes, must be in the 7..13 range
 * (inclusive).
 *
 * The tag length (`tag_len`), in bytes, must be in the 4..16 range, and
 * be an even integer. Short tags mechanically allow for higher forgery
 * probabilities; hence, tag sizes smaller than 12 bytes shall be used only
 * with care.
 *
 * It is critical to CCM security that nonce values are not repeated for
 * the same encryption key. Random generation of nonces is not generally
 * recommended, due to the relatively small maximum nonce value.
 *
 * Returned value is 1 on success, 0 on error. An error is reported if
 * the tag or nonce length is out of range, or if the
 * plaintext/ciphertext length cannot be encoded with the specified
 * nonce length.
 *
 * \param ctx         CCM context structure.
 * \param nonce       CCM nonce to use.
 * \param nonce_len   CCM nonce length (in bytes, 7 to 13).
 * \param aad_len     additional authenticated data length (in bytes).
 * \param data_len    plaintext/ciphertext length (in bytes).
 * \param tag_len     tag length (in bytes).
 * \return  1 on success, 0 on error.
 */
int br_ccm_reset(br_ccm_context *ctx, const void *nonce, size_t nonce_len,
	uint64_t aad_len, uint64_t data_len, size_t tag_len);

/**
 * \brief Inject additional authenticated data into CCM.
 *
 * The provided data is injected into a running CCM computation. Additional
 * data must be injected _before_ the call to `br_ccm_flip()`.
 * Additional data can be injected in several chunks of arbitrary length,
 * but the total amount MUST exactly match the value which was provided
 * to `br_ccm_reset()`.
 *
 * \param ctx    CCM context structure.
 * \param data   pointer to additional authenticated data.
 * \param len    length of additional authenticated data (in bytes).
 */
void br_ccm_aad_inject(br_ccm_context *ctx, const void *data, size_t len);

/**
 * \brief Finish injection of additional authenticated data into CCM.
 *
 * This function MUST be called before beginning the actual encryption
 * or decryption (with `br_ccm_run()`), even if no additional authenticated
 * data was injected. No additional authenticated data may be injected
 * after this function call.
 *
 * \param ctx   CCM context structure.
 */
void br_ccm_flip(br_ccm_context *ctx);

/**
 * \brief Encrypt or decrypt some data with CCM.
 *
 * Data encryption or decryption can be done after `br_ccm_flip()`
 * has been called on the context. If `encrypt` is non-zero, then the
 * provided data shall be plaintext, and it is encrypted in place.
 * Otherwise, the data shall be ciphertext, and it is decrypted in place.
 *
 * Data may be provided in several chunks of arbitrary length, provided
 * that the total length exactly matches the length provided to the
 * `br_ccm_reset()` call.
 *
 * \param ctx       CCM context structure.
 * \param encrypt   non-zero for encryption, zero for decryption.
 * \param data      data to encrypt or decrypt.
 * \param len       data length (in bytes).
 */
void br_ccm_run(br_ccm_context *ctx, int encrypt, void *data, size_t len);

/**
 * \brief Compute CCM authentication tag.
 *
 * Compute the CCM authentication tag. This call terminates the CCM
 * run: all data must have been injected with `br_ccm_run()` (in zero,
 * one or more successive calls). After this function has been called,
 * no more data can br processed; a `br_ccm_reset()` call is required
 * to start a new message.
 *
 * The tag length was provided upon context initialisation (last call
 * to `br_ccm_reset()`); it is returned by this function.
 *
 * The tag value must normally be sent along with the encrypted data.
 * When decrypting, the tag value must be recomputed and compared with
 * the received tag: if the two tag values differ, then either the tag
 * or the encrypted data was altered in transit. As an alternative to
 * this function, the `br_ccm_check_tag()` function can be used to
 * compute and check the tag value.
 *
 * \param ctx   CCM context structure.
 * \param tag   destination buffer for the tag (up to 16 bytes).
 * \return  the tag length (in bytes).
 */
size_t br_ccm_get_tag(br_ccm_context *ctx, void *tag);

/**
 * \brief Compute and check CCM authentication tag.
 *
 * This function is an alternative to `br_ccm_get_tag()`, normally used
 * on the receiving end (i.e. when decrypting value). The tag value is
 * recomputed and compared with the provided tag value. If they match, 1
 * is returned; on mismatch, 0 is returned. A returned value of 0 means
 * that the data or the tag was altered in transit, normally leading to
 * wholesale rejection of the complete message.
 *
 * \param ctx   CCM context structure.
 * \param tag   tag value to compare with (up to 16 bytes).
 * \return  1 on success (exact match of tag value), 0 otherwise.
 */
uint32_t br_ccm_check_tag(br_ccm_context *ctx, const void *tag);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_RSA_H__
#define BR_BEARSSL_RSA_H__

#include <stddef.h>
#include <stdint.h>




#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_rsa.h
 *
 * # RSA
 *
 * This file documents the RSA implementations provided with BearSSL.
 * Note that the SSL engine accesses these implementations through a
 * configurable API, so it is possible to, for instance, run a SSL
 * server which uses a RSA engine which is not based on this code.
 *
 * ## Key Elements
 *
 * RSA public and private keys consist in lists of big integers. All
 * such integers are represented with big-endian unsigned notation:
 * first byte is the most significant, and the value is positive (so
 * there is no dedicated "sign bit"). Public and private key structures
 * thus contain, for each such integer, a pointer to the first value byte
 * (`unsigned char *`), and a length (`size_t`) which is the number of
 * relevant bytes. As a general rule, minimal-length encoding is not
 * enforced: values may have extra leading bytes of value 0.
 *
 * RSA public keys consist in two integers:
 *
 *   - the modulus (`n`);
 *   - the public exponent (`e`).
 *
 * RSA private keys, as defined in
 * [PKCS#1](https://tools.ietf.org/html/rfc3447), contain eight integers:
 *
 *   - the modulus (`n`);
 *   - the public exponent (`e`);
 *   - the private exponent (`d`);
 *   - the first prime factor (`p`);
 *   - the second prime factor (`q`);
 *   - the first reduced exponent (`dp`, which is `d` modulo `p-1`);
 *   - the second reduced exponent (`dq`, which is `d` modulo `q-1`);
 *   - the CRT coefficient (`iq`, the inverse of `q` modulo `p`).
 *
 * However, the implementations defined in BearSSL use only five of
 * these integers: `p`, `q`, `dp`, `dq` and `iq`.
 *
 * ## Security Features and Limitations
 *
 * The implementations contained in BearSSL have the following limitations
 * and features:
 *
 *   - They are constant-time. This means that the execution time and
 *     memory access pattern may depend on the _lengths_ of the private
 *     key components, but not on their value, nor on the value of
 *     the operand. Note that this property is not achieved through
 *     random masking, but "true" constant-time code.
 *
 *   - They support only private keys with two prime factors. RSA private
 *     keys with three or more prime factors are nominally supported, but
 *     rarely used; they may offer faster operations, at the expense of
 *     more code and potentially a reduction in security if there are
 *     "too many" prime factors.
 *
 *   - The public exponent may have arbitrary length. Of course, it is
 *     a good idea to keep public exponents small, so that public key
 *     operations are fast; but, contrary to some widely deployed
 *     implementations, BearSSL has no problem with public exponents
 *     longer than 32 bits.
 *
 *   - The two prime factors of the modulus need not have the same length
 *     (but severely imbalanced factor lengths might reduce security).
 *     Similarly, there is no requirement that the first factor (`p`)
 *     be greater than the second factor (`q`).
 *
 *   - Prime factors and modulus must be smaller than a compile-time limit.
 *     This is made necessary by the use of fixed-size stack buffers, and
 *     the limit has been adjusted to keep stack usage under 2 kB for the
 *     RSA operations. Currently, the maximum modulus size is 4096 bits,
 *     and the maximum prime factor size is 2080 bits.
 *
 *   - The RSA functions themselves do not enforce lower size limits,
 *     except that which is absolutely necessary for the operation to
 *     mathematically make sense (e.g. a PKCS#1 v1.5 signature with
 *     SHA-1 requires a modulus of at least 361 bits). It is up to users
 *     of this code to enforce size limitations when appropriate (e.g.
 *     the X.509 validation engine, by default, rejects RSA keys of
 *     less than 1017 bits).
 *
 *   - Within the size constraints expressed above, arbitrary bit lengths
 *     are supported. There is no requirement that prime factors or
 *     modulus have a size multiple of 8 or 16.
 *
 *   - When verifying PKCS#1 v1.5 signatures, both variants of the hash
 *     function identifying header (with and without the ASN.1 NULL) are
 *     supported. When producing such signatures, the variant with the
 *     ASN.1 NULL is used.
 *
 * ## Implementations
 *
 * Three RSA implementations are included:
 *
 *   - The **i32** implementation internally represents big integers
 *     as arrays of 32-bit integers. It is perfunctory and portable,
 *     but not very efficient.
 *
 *   - The **i31** implementation uses 32-bit integers, each containing
 *     31 bits worth of integer data. The i31 implementation is somewhat
 *     faster than the i32 implementation (the reduced integer size makes
 *     carry propagation easier) for a similar code footprint, but uses
 *     very slightly larger stack buffers (about 4% bigger).
 *
 *   - The **i62** implementation is similar to the i31 implementation,
 *     except that it internally leverages the 64x64->128 multiplication
 *     opcode. This implementation is available only on architectures
 *     where such an opcode exists. It is much faster than i31.
 *
 *   - The **i15** implementation uses 16-bit integers, each containing
 *     15 bits worth of integer data. Multiplication results fit on
 *     32 bits, so this won't use the "widening" multiplication routine
 *     on ARM Cortex M0/M0+, for much better performance and constant-time
 *     execution.
 */

/**
 * \brief RSA public key.
 *
 * The structure references the modulus and the public exponent. Both
 * integers use unsigned big-endian representation; extra leading bytes
 * of value 0 are allowed.
 */
typedef struct {
	/** \brief Modulus. */
	unsigned char *n;
	/** \brief Modulus length (in bytes). */
	size_t nlen;
	/** \brief Public exponent. */
	unsigned char *e;
	/** \brief Public exponent length (in bytes). */
	size_t elen;
} br_rsa_public_key;

/**
 * \brief RSA private key.
 *
 * The structure references the private factors, reduced private
 * exponents, and CRT coefficient. It also contains the bit length of
 * the modulus. The big integers use unsigned big-endian representation;
 * extra leading bytes of value 0 are allowed. However, the modulus bit
 * length (`n_bitlen`) MUST be exact.
 */
typedef struct {
	/** \brief Modulus bit length (in bits, exact value). */
	uint32_t n_bitlen;
	/** \brief First prime factor. */
	unsigned char *p;
	/** \brief First prime factor length (in bytes). */
	size_t plen;
	/** \brief Second prime factor. */
	unsigned char *q;
	/** \brief Second prime factor length (in bytes). */
	size_t qlen;
	/** \brief First reduced private exponent. */
	unsigned char *dp;
	/** \brief First reduced private exponent length (in bytes). */
	size_t dplen;
	/** \brief Second reduced private exponent. */
	unsigned char *dq;
	/** \brief Second reduced private exponent length (in bytes). */
	size_t dqlen;
	/** \brief CRT coefficient. */
	unsigned char *iq;
	/** \brief CRT coefficient length (in bytes). */
	size_t iqlen;
} br_rsa_private_key;

/**
 * \brief Type for a RSA public key engine.
 *
 * The public key engine performs the modular exponentiation of the
 * provided value with the public exponent. The value is modified in
 * place.
 *
 * The value length (`xlen`) is verified to have _exactly_ the same
 * length as the modulus (actual modulus length, without extra leading
 * zeros in the modulus representation in memory). If the length does
 * not match, then this function returns 0 and `x[]` is unmodified.
 * 
 * It `xlen` is correct, then `x[]` is modified. Returned value is 1
 * on success, 0 on error. Error conditions include an oversized `x[]`
 * (the array has the same length as the modulus, but the numerical value
 * is not lower than the modulus) and an invalid modulus (e.g. an even
 * integer). If an error is reported, then the new contents of `x[]` are
 * unspecified.
 *
 * \param x      operand to exponentiate.
 * \param xlen   length of the operand (in bytes).
 * \param pk     RSA public key.
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_rsa_public)(unsigned char *x, size_t xlen,
	const br_rsa_public_key *pk);

/**
 * \brief Type for a RSA signature verification engine (PKCS#1 v1.5).
 *
 * Parameters are:
 *
 *   - The signature itself. The provided array is NOT modified.
 *
 *   - The encoded OID for the hash function. The provided array must begin
 *     with a single byte that contains the length of the OID value (in
 *     bytes), followed by exactly that many bytes. This parameter may
 *     also be `NULL`, in which case the raw hash value should be used
 *     with the PKCS#1 v1.5 "type 1" padding (as used in SSL/TLS up
 *     to TLS-1.1, with a 36-byte hash value).
 *
 *   - The hash output length, in bytes.
 *
 *   - The public key.
 *
 *   - An output buffer for the hash value. The caller must still compare
 *     it with the hash of the data over which the signature is computed.
 *
 * **Constraints:**
 *
 *   - Hash length MUST be no more than 64 bytes.
 *
 *   - OID value length MUST be no more than 32 bytes (i.e. `hash_oid[0]`
 *     must have a value in the 0..32 range, inclusive).
 *
 * This function verifies that the signature length (`xlen`) matches the
 * modulus length (this function returns 0 on mismatch). If the modulus
 * size exceeds the maximum supported RSA size, then the function also
 * returns 0.
 *
 * Returned value is 1 on success, 0 on error.
 *
 * Implementations of this type need not be constant-time.
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash_len   expected hash value length (in bytes).
 * \param pk         RSA public key.
 * \param hash_out   output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_rsa_pkcs1_vrfy)(const unsigned char *x, size_t xlen,
	const unsigned char *hash_oid, size_t hash_len,
	const br_rsa_public_key *pk, unsigned char *hash_out);

/**
 * \brief Type for a RSA signature verification engine (PSS).
 *
 * Parameters are:
 *
 *   - The signature itself. The provided array is NOT modified.
 *
 *   - The hash function which was used to hash the message.
 *
 *   - The hash function to use with MGF1 within the PSS padding. This
 *     is not necessarily the same hash function as the one which was
 *     used to hash the signed message.
 *
 *   - The hashed message (as an array of bytes).
 *
 *   - The PSS salt length (in bytes).
 *
 *   - The public key.
 *
 * **Constraints:**
 *
 *   - Hash message length MUST be no more than 64 bytes.
 *
 * Note that, contrary to PKCS#1 v1.5 signature, the hash value of the
 * signed data cannot be extracted from the signature; it must be
 * provided to the verification function.
 *
 * This function verifies that the signature length (`xlen`) matches the
 * modulus length (this function returns 0 on mismatch). If the modulus
 * size exceeds the maximum supported RSA size, then the function also
 * returns 0.
 *
 * Returned value is 1 on success, 0 on error.
 *
 * Implementations of this type need not be constant-time.
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hf_data    hash function applied on the message.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hash value of the signed message.
 * \param salt_len   PSS salt length (in bytes).
 * \param pk         RSA public key.
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_rsa_pss_vrfy)(const unsigned char *x, size_t xlen,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1, 
	const void *hash, size_t salt_len, const br_rsa_public_key *pk);

/**
 * \brief Type for a RSA encryption engine (OAEP).
 *
 * Parameters are:
 *
 *   - A source of random bytes. The source must be already initialized.
 *
 *   - A hash function, used internally with the mask generation function
 *     (MGF1).
 *
 *   - A label. The `label` pointer may be `NULL` if `label_len` is zero
 *     (an empty label, which is the default in PKCS#1 v2.2).
 *
 *   - The public key.
 *
 *   - The destination buffer. Its maximum length (in bytes) is provided;
 *     if that length is lower than the public key length, then an error
 *     is reported.
 *
 *   - The source message.
 *
 * The encrypted message output has exactly the same length as the modulus
 * (mathematical length, in bytes, not counting extra leading zeros in the
 * modulus representation in the public key).
 *
 * The source message (`src`, length `src_len`) may overlap with the
 * destination buffer (`dst`, length `dst_max_len`).
 *
 * This function returns the actual encrypted message length, in bytes;
 * on error, zero is returned. An error is reported if the output buffer
 * is not large enough, or the public is invalid, or the public key
 * modulus exceeds the maximum supported RSA size.
 *
 * \param rnd           source of random bytes.
 * \param dig           hash function to use with MGF1.
 * \param label         label value (may be `NULL` if `label_len` is zero).
 * \param label_len     label length, in bytes.
 * \param pk            RSA public key.
 * \param dst           destination buffer.
 * \param dst_max_len   destination buffer length (maximum encrypted data size).
 * \param src           message to encrypt.
 * \param src_len       source message length (in bytes).
 * \return  encrypted message length (in bytes), or 0 on error.
 */
typedef size_t (*br_rsa_oaep_encrypt)(
	const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len,
	const br_rsa_public_key *pk,
	void *dst, size_t dst_max_len,
	const void *src, size_t src_len);

/**
 * \brief Type for a RSA private key engine.
 *
 * The `x[]` buffer is modified in place, and its length is inferred from
 * the modulus length (`x[]` is assumed to have a length of
 * `(sk->n_bitlen+7)/8` bytes).
 *
 * Returned value is 1 on success, 0 on error.
 *
 * \param x    operand to exponentiate.
 * \param sk   RSA private key.
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_rsa_private)(unsigned char *x,
	const br_rsa_private_key *sk);

/**
 * \brief Type for a RSA signature generation engine (PKCS#1 v1.5).
 *
 * Parameters are:
 *
 *   - The encoded OID for the hash function. The provided array must begin
 *     with a single byte that contains the length of the OID value (in
 *     bytes), followed by exactly that many bytes. This parameter may
 *     also be `NULL`, in which case the raw hash value should be used
 *     with the PKCS#1 v1.5 "type 1" padding (as used in SSL/TLS up
 *     to TLS-1.1, with a 36-byte hash value).
 *
 *   - The hash value computes over the data to sign (its length is
 *     expressed in bytes).
 *
 *   - The RSA private key.
 *
 *   - The output buffer, that receives the signature.
 *
 * Returned value is 1 on success, 0 on error. Error conditions include
 * a too small modulus for the provided hash OID and value, or some
 * invalid key parameters. The signature length is exactly
 * `(sk->n_bitlen+7)/8` bytes.
 *
 * This function is expected to be constant-time with regards to the
 * private key bytes (lengths of the modulus and the individual factors
 * may leak, though) and to the hashed data.
 *
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash       hash value.
 * \param hash_len   hash value length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the signature value.
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_rsa_pkcs1_sign)(const unsigned char *hash_oid,
	const unsigned char *hash, size_t hash_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief Type for a RSA signature generation engine (PSS).
 *
 * Parameters are:
 *
 *   - An initialized PRNG for salt generation. If the salt length is
 *     zero (`salt_len` parameter), then the PRNG is optional (this is
 *     not the typical case, as the security proof of RSA/PSS is
 *     tighter when a non-empty salt is used).
 *
 *   - The hash function which was used to hash the message.
 *
 *   - The hash function to use with MGF1 within the PSS padding. This
 *     is not necessarily the same function as the one used to hash the
 *     message.
 *
 *   - The hashed message.
 *
 *   - The salt length, in bytes.
 *
 *   - The RSA private key.
 *
 *   - The output buffer, that receives the signature.
 *
 * Returned value is 1 on success, 0 on error. Error conditions include
 * a too small modulus for the provided hash and salt lengths, or some
 * invalid key parameters. The signature length is exactly
 * `(sk->n_bitlen+7)/8` bytes.
 *
 * This function is expected to be constant-time with regards to the
 * private key bytes (lengths of the modulus and the individual factors
 * may leak, though) and to the hashed data.
 *
 * \param rng        PRNG for salt generation (`NULL` if `salt_len` is zero).
 * \param hf_data    hash function used to hash the signed data.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hashed message.
 * \param salt_len   salt length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the signature value.
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_rsa_pss_sign)(const br_prng_class **rng,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash_value, size_t salt_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief Encoded OID for SHA-1 (in RSA PKCS#1 signatures).
 */
#define BR_HASH_OID_SHA1     \
	((const unsigned char *)"\x05\x2B\x0E\x03\x02\x1A")

/**
 * \brief Encoded OID for SHA-224 (in RSA PKCS#1 signatures).
 */
#define BR_HASH_OID_SHA224   \
	((const unsigned char *)"\x09\x60\x86\x48\x01\x65\x03\x04\x02\x04")

/**
 * \brief Encoded OID for SHA-256 (in RSA PKCS#1 signatures).
 */
#define BR_HASH_OID_SHA256   \
	((const unsigned char *)"\x09\x60\x86\x48\x01\x65\x03\x04\x02\x01")

/**
 * \brief Encoded OID for SHA-384 (in RSA PKCS#1 signatures).
 */
#define BR_HASH_OID_SHA384   \
	((const unsigned char *)"\x09\x60\x86\x48\x01\x65\x03\x04\x02\x02")

/**
 * \brief Encoded OID for SHA-512 (in RSA PKCS#1 signatures).
 */
#define BR_HASH_OID_SHA512   \
	((const unsigned char *)"\x09\x60\x86\x48\x01\x65\x03\x04\x02\x03")

/**
 * \brief Type for a RSA decryption engine (OAEP).
 *
 * Parameters are:
 *
 *   - A hash function, used internally with the mask generation function
 *     (MGF1).
 *
 *   - A label. The `label` pointer may be `NULL` if `label_len` is zero
 *     (an empty label, which is the default in PKCS#1 v2.2).
 *
 *   - The private key.
 *
 *   - The source and destination buffer. The buffer initially contains
 *     the encrypted message; the buffer contents are altered, and the
 *     decrypted message is written at the start of that buffer
 *     (decrypted message is always shorter than the encrypted message).
 *
 * If decryption fails in any way, then `*len` is unmodified, and the
 * function returns 0. Otherwise, `*len` is set to the decrypted message
 * length, and 1 is returned. The implementation is responsible for
 * checking that the input message length matches the key modulus length,
 * and that the padding is correct.
 *
 * Implementations MUST use constant-time check of the validity of the
 * OAEP padding, at least until the leading byte and hash value have
 * been checked. Whether overall decryption worked, and the length of
 * the decrypted message, may leak.
 *
 * \param dig         hash function to use with MGF1.
 * \param label       label value (may be `NULL` if `label_len` is zero).
 * \param label_len   label length, in bytes.
 * \param sk          RSA private key.
 * \param data        input/output buffer.
 * \param len         encrypted/decrypted message length.
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_rsa_oaep_decrypt)(
	const br_hash_class *dig, const void *label, size_t label_len,
	const br_rsa_private_key *sk, void *data, size_t *len);

/*
 * RSA "i32" engine. Integers are internally represented as arrays of
 * 32-bit integers, and the core multiplication primitive is the
 * 32x32->64 multiplication.
 */

/**
 * \brief RSA public key engine "i32".
 *
 * \see br_rsa_public
 *
 * \param x      operand to exponentiate.
 * \param xlen   length of the operand (in bytes).
 * \param pk     RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i32_public(unsigned char *x, size_t xlen,
	const br_rsa_public_key *pk);

/**
 * \brief RSA signature verification engine "i32" (PKCS#1 v1.5 signatures).
 *
 * \see br_rsa_pkcs1_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash_len   expected hash value length (in bytes).
 * \param pk         RSA public key.
 * \param hash_out   output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i32_pkcs1_vrfy(const unsigned char *x, size_t xlen,
	const unsigned char *hash_oid, size_t hash_len,
	const br_rsa_public_key *pk, unsigned char *hash_out);

/**
 * \brief RSA signature verification engine "i32" (PSS signatures).
 *
 * \see br_rsa_pss_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hf_data    hash function applied on the message.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hash value of the signed message.
 * \param salt_len   PSS salt length (in bytes).
 * \param pk         RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i32_pss_vrfy(const unsigned char *x, size_t xlen,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1, 
	const void *hash, size_t salt_len, const br_rsa_public_key *pk);

/**
 * \brief RSA private key engine "i32".
 *
 * \see br_rsa_private
 *
 * \param x    operand to exponentiate.
 * \param sk   RSA private key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i32_private(unsigned char *x,
	const br_rsa_private_key *sk);

/**
 * \brief RSA signature generation engine "i32" (PKCS#1 v1.5 signatures).
 *
 * \see br_rsa_pkcs1_sign
 *
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash       hash value.
 * \param hash_len   hash value length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i32_pkcs1_sign(const unsigned char *hash_oid,
	const unsigned char *hash, size_t hash_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief RSA signature generation engine "i32" (PSS signatures).
 *
 * \see br_rsa_pss_sign
 *
 * \param rng        PRNG for salt generation (`NULL` if `salt_len` is zero).
 * \param hf_data    hash function used to hash the signed data.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hashed message.
 * \param salt_len   salt length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the signature value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i32_pss_sign(const br_prng_class **rng,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash_value, size_t salt_len,
	const br_rsa_private_key *sk, unsigned char *x);

/*
 * RSA "i31" engine. Similar to i32, but only 31 bits are used per 32-bit
 * word. This uses slightly more stack space (about 4% more) and code
 * space, but it quite faster.
 */

/**
 * \brief RSA public key engine "i31".
 *
 * \see br_rsa_public
 *
 * \param x      operand to exponentiate.
 * \param xlen   length of the operand (in bytes).
 * \param pk     RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i31_public(unsigned char *x, size_t xlen,
	const br_rsa_public_key *pk);

/**
 * \brief RSA signature verification engine "i31" (PKCS#1 v1.5 signatures).
 *
 * \see br_rsa_pkcs1_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash_len   expected hash value length (in bytes).
 * \param pk         RSA public key.
 * \param hash_out   output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i31_pkcs1_vrfy(const unsigned char *x, size_t xlen,
	const unsigned char *hash_oid, size_t hash_len,
	const br_rsa_public_key *pk, unsigned char *hash_out);

/**
 * \brief RSA signature verification engine "i31" (PSS signatures).
 *
 * \see br_rsa_pss_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hf_data    hash function applied on the message.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hash value of the signed message.
 * \param salt_len   PSS salt length (in bytes).
 * \param pk         RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i31_pss_vrfy(const unsigned char *x, size_t xlen,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1, 
	const void *hash, size_t salt_len, const br_rsa_public_key *pk);

/**
 * \brief RSA private key engine "i31".
 *
 * \see br_rsa_private
 *
 * \param x    operand to exponentiate.
 * \param sk   RSA private key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i31_private(unsigned char *x,
	const br_rsa_private_key *sk);

/**
 * \brief RSA signature generation engine "i31" (PKCS#1 v1.5 signatures).
 *
 * \see br_rsa_pkcs1_sign
 *
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash       hash value.
 * \param hash_len   hash value length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i31_pkcs1_sign(const unsigned char *hash_oid,
	const unsigned char *hash, size_t hash_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief RSA signature generation engine "i31" (PSS signatures).
 *
 * \see br_rsa_pss_sign
 *
 * \param rng        PRNG for salt generation (`NULL` if `salt_len` is zero).
 * \param hf_data    hash function used to hash the signed data.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hashed message.
 * \param salt_len   salt length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the signature value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i31_pss_sign(const br_prng_class **rng,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash_value, size_t salt_len,
	const br_rsa_private_key *sk, unsigned char *x);

/*
 * RSA "i62" engine. Similar to i31, but internal multiplication use
 * 64x64->128 multiplications. This is available only on architecture
 * that offer such an opcode.
 */

/**
 * \brief RSA public key engine "i62".
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_public_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_public
 *
 * \param x      operand to exponentiate.
 * \param xlen   length of the operand (in bytes).
 * \param pk     RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i62_public(unsigned char *x, size_t xlen,
	const br_rsa_public_key *pk);

/**
 * \brief RSA signature verification engine "i62" (PKCS#1 v1.5 signatures).
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_pkcs1_vrfy_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_pkcs1_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash_len   expected hash value length (in bytes).
 * \param pk         RSA public key.
 * \param hash_out   output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i62_pkcs1_vrfy(const unsigned char *x, size_t xlen,
	const unsigned char *hash_oid, size_t hash_len,
	const br_rsa_public_key *pk, unsigned char *hash_out);

/**
 * \brief RSA signature verification engine "i62" (PSS signatures).
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_pss_vrfy_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_pss_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hf_data    hash function applied on the message.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hash value of the signed message.
 * \param salt_len   PSS salt length (in bytes).
 * \param pk         RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i62_pss_vrfy(const unsigned char *x, size_t xlen,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1, 
	const void *hash, size_t salt_len, const br_rsa_public_key *pk);

/**
 * \brief RSA private key engine "i62".
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_private_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_private
 *
 * \param x    operand to exponentiate.
 * \param sk   RSA private key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i62_private(unsigned char *x,
	const br_rsa_private_key *sk);

/**
 * \brief RSA signature generation engine "i62" (PKCS#1 v1.5 signatures).
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_pkcs1_sign_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_pkcs1_sign
 *
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash       hash value.
 * \param hash_len   hash value length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i62_pkcs1_sign(const unsigned char *hash_oid,
	const unsigned char *hash, size_t hash_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief RSA signature generation engine "i62" (PSS signatures).
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_pss_sign_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_pss_sign
 *
 * \param rng        PRNG for salt generation (`NULL` if `salt_len` is zero).
 * \param hf_data    hash function used to hash the signed data.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hashed message.
 * \param salt_len   salt length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the signature value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i62_pss_sign(const br_prng_class **rng,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash_value, size_t salt_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief Get the RSA "i62" implementation (public key operations),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_public br_rsa_i62_public_get(void);

/**
 * \brief Get the RSA "i62" implementation (PKCS#1 v1.5 signature verification),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_pkcs1_vrfy br_rsa_i62_pkcs1_vrfy_get(void);

/**
 * \brief Get the RSA "i62" implementation (PSS signature verification),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_pss_vrfy br_rsa_i62_pss_vrfy_get(void);

/**
 * \brief Get the RSA "i62" implementation (private key operations),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_private br_rsa_i62_private_get(void);

/**
 * \brief Get the RSA "i62" implementation (PKCS#1 v1.5 signature generation),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_pkcs1_sign br_rsa_i62_pkcs1_sign_get(void);

/**
 * \brief Get the RSA "i62" implementation (PSS signature generation),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_pss_sign br_rsa_i62_pss_sign_get(void);

/**
 * \brief Get the RSA "i62" implementation (OAEP encryption),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_oaep_encrypt br_rsa_i62_oaep_encrypt_get(void);

/**
 * \brief Get the RSA "i62" implementation (OAEP decryption),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_oaep_decrypt br_rsa_i62_oaep_decrypt_get(void);

/*
 * RSA "i15" engine. Integers are represented as 15-bit integers, so
 * the code uses only 32-bit multiplication (no 64-bit result), which
 * is vastly faster (and constant-time) on the ARM Cortex M0/M0+.
 */

/**
 * \brief RSA public key engine "i15".
 *
 * \see br_rsa_public
 *
 * \param x      operand to exponentiate.
 * \param xlen   length of the operand (in bytes).
 * \param pk     RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i15_public(unsigned char *x, size_t xlen,
	const br_rsa_public_key *pk);

/**
 * \brief RSA signature verification engine "i15" (PKCS#1 v1.5 signatures).
 *
 * \see br_rsa_pkcs1_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash_len   expected hash value length (in bytes).
 * \param pk         RSA public key.
 * \param hash_out   output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i15_pkcs1_vrfy(const unsigned char *x, size_t xlen,
	const unsigned char *hash_oid, size_t hash_len,
	const br_rsa_public_key *pk, unsigned char *hash_out);

/**
 * \brief RSA signature verification engine "i15" (PSS signatures).
 *
 * \see br_rsa_pss_vrfy
 *
 * \param x          signature buffer.
 * \param xlen       signature length (in bytes).
 * \param hf_data    hash function applied on the message.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hash value of the signed message.
 * \param salt_len   PSS salt length (in bytes).
 * \param pk         RSA public key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i15_pss_vrfy(const unsigned char *x, size_t xlen,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1, 
	const void *hash, size_t salt_len, const br_rsa_public_key *pk);

/**
 * \brief RSA private key engine "i15".
 *
 * \see br_rsa_private
 *
 * \param x    operand to exponentiate.
 * \param sk   RSA private key.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i15_private(unsigned char *x,
	const br_rsa_private_key *sk);

/**
 * \brief RSA signature generation engine "i15" (PKCS#1 v1.5 signatures).
 *
 * \see br_rsa_pkcs1_sign
 *
 * \param hash_oid   encoded hash algorithm OID (or `NULL`).
 * \param hash       hash value.
 * \param hash_len   hash value length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the hash value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i15_pkcs1_sign(const unsigned char *hash_oid,
	const unsigned char *hash, size_t hash_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief RSA signature generation engine "i15" (PSS signatures).
 *
 * \see br_rsa_pss_sign
 *
 * \param rng        PRNG for salt generation (`NULL` if `salt_len` is zero).
 * \param hf_data    hash function used to hash the signed data.
 * \param hf_mgf1    hash function to use with MGF1.
 * \param hash       hashed message.
 * \param salt_len   salt length (in bytes).
 * \param sk         RSA private key.
 * \param x          output buffer for the signature value.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i15_pss_sign(const br_prng_class **rng,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash_value, size_t salt_len,
	const br_rsa_private_key *sk, unsigned char *x);

/**
 * \brief Get "default" RSA implementation (public-key operations).
 *
 * This returns the preferred implementation of RSA (public-key operations)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_public br_rsa_public_get_default(void);

/**
 * \brief Get "default" RSA implementation (private-key operations).
 *
 * This returns the preferred implementation of RSA (private-key operations)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_private br_rsa_private_get_default(void);

/**
 * \brief Get "default" RSA implementation (PKCS#1 v1.5 signature verification).
 *
 * This returns the preferred implementation of RSA (signature verification)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_pkcs1_vrfy br_rsa_pkcs1_vrfy_get_default(void);

/**
 * \brief Get "default" RSA implementation (PSS signature verification).
 *
 * This returns the preferred implementation of RSA (signature verification)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_pss_vrfy br_rsa_pss_vrfy_get_default(void);

/**
 * \brief Get "default" RSA implementation (PKCS#1 v1.5 signature generation).
 *
 * This returns the preferred implementation of RSA (signature generation)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_pkcs1_sign br_rsa_pkcs1_sign_get_default(void);

/**
 * \brief Get "default" RSA implementation (PSS signature generation).
 *
 * This returns the preferred implementation of RSA (signature generation)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_pss_sign br_rsa_pss_sign_get_default(void);

/**
 * \brief Get "default" RSA implementation (OAEP encryption).
 *
 * This returns the preferred implementation of RSA (OAEP encryption)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_oaep_encrypt br_rsa_oaep_encrypt_get_default(void);

/**
 * \brief Get "default" RSA implementation (OAEP decryption).
 *
 * This returns the preferred implementation of RSA (OAEP decryption)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_oaep_decrypt br_rsa_oaep_decrypt_get_default(void);

/**
 * \brief RSA decryption helper, for SSL/TLS.
 *
 * This function performs the RSA decryption for a RSA-based key exchange
 * in a SSL/TLS server. The provided RSA engine is used. The `data`
 * parameter points to the value to decrypt, of length `len` bytes. On
 * success, the 48-byte pre-master secret is copied into `data`, starting
 * at the first byte of that buffer; on error, the contents of `data`
 * become indeterminate.
 *
 * This function first checks that the provided value length (`len`) is
 * not lower than 59 bytes, and matches the RSA modulus length; if neither
 * of this property is met, then this function returns 0 and the buffer
 * is unmodified.
 *
 * Otherwise, decryption and then padding verification are performed, both
 * in constant-time. A decryption error, or a bad padding, or an
 * incorrect decrypted value length are reported with a returned value of
 * 0; on success, 1 is returned. The caller (SSL server engine) is supposed
 * to proceed with a random pre-master secret in case of error.
 *
 * \param core   RSA private key engine.
 * \param sk     RSA private key.
 * \param data   input/output buffer.
 * \param len    length (in bytes) of the data to decrypt.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_ssl_decrypt(br_rsa_private core, const br_rsa_private_key *sk,
	unsigned char *data, size_t len);

/**
 * \brief RSA encryption (OAEP) with the "i15" engine.
 *
 * \see br_rsa_oaep_encrypt
 *
 * \param rnd           source of random bytes.
 * \param dig           hash function to use with MGF1.
 * \param label         label value (may be `NULL` if `label_len` is zero).
 * \param label_len     label length, in bytes.
 * \param pk            RSA public key.
 * \param dst           destination buffer.
 * \param dst_max_len   destination buffer length (maximum encrypted data size).
 * \param src           message to encrypt.
 * \param src_len       source message length (in bytes).
 * \return  encrypted message length (in bytes), or 0 on error.
 */
size_t br_rsa_i15_oaep_encrypt(
	const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len,
	const br_rsa_public_key *pk,
	void *dst, size_t dst_max_len,
	const void *src, size_t src_len);

/**
 * \brief RSA decryption (OAEP) with the "i15" engine.
 *
 * \see br_rsa_oaep_decrypt
 *
 * \param dig         hash function to use with MGF1.
 * \param label       label value (may be `NULL` if `label_len` is zero).
 * \param label_len   label length, in bytes.
 * \param sk          RSA private key.
 * \param data        input/output buffer.
 * \param len         encrypted/decrypted message length.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i15_oaep_decrypt(
	const br_hash_class *dig, const void *label, size_t label_len,
	const br_rsa_private_key *sk, void *data, size_t *len);

/**
 * \brief RSA encryption (OAEP) with the "i31" engine.
 *
 * \see br_rsa_oaep_encrypt
 *
 * \param rnd           source of random bytes.
 * \param dig           hash function to use with MGF1.
 * \param label         label value (may be `NULL` if `label_len` is zero).
 * \param label_len     label length, in bytes.
 * \param pk            RSA public key.
 * \param dst           destination buffer.
 * \param dst_max_len   destination buffer length (maximum encrypted data size).
 * \param src           message to encrypt.
 * \param src_len       source message length (in bytes).
 * \return  encrypted message length (in bytes), or 0 on error.
 */
size_t br_rsa_i31_oaep_encrypt(
	const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len,
	const br_rsa_public_key *pk,
	void *dst, size_t dst_max_len,
	const void *src, size_t src_len);

/**
 * \brief RSA decryption (OAEP) with the "i31" engine.
 *
 * \see br_rsa_oaep_decrypt
 *
 * \param dig         hash function to use with MGF1.
 * \param label       label value (may be `NULL` if `label_len` is zero).
 * \param label_len   label length, in bytes.
 * \param sk          RSA private key.
 * \param data        input/output buffer.
 * \param len         encrypted/decrypted message length.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i31_oaep_decrypt(
	const br_hash_class *dig, const void *label, size_t label_len,
	const br_rsa_private_key *sk, void *data, size_t *len);

/**
 * \brief RSA encryption (OAEP) with the "i32" engine.
 *
 * \see br_rsa_oaep_encrypt
 *
 * \param rnd           source of random bytes.
 * \param dig           hash function to use with MGF1.
 * \param label         label value (may be `NULL` if `label_len` is zero).
 * \param label_len     label length, in bytes.
 * \param pk            RSA public key.
 * \param dst           destination buffer.
 * \param dst_max_len   destination buffer length (maximum encrypted data size).
 * \param src           message to encrypt.
 * \param src_len       source message length (in bytes).
 * \return  encrypted message length (in bytes), or 0 on error.
 */
size_t br_rsa_i32_oaep_encrypt(
	const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len,
	const br_rsa_public_key *pk,
	void *dst, size_t dst_max_len,
	const void *src, size_t src_len);

/**
 * \brief RSA decryption (OAEP) with the "i32" engine.
 *
 * \see br_rsa_oaep_decrypt
 *
 * \param dig         hash function to use with MGF1.
 * \param label       label value (may be `NULL` if `label_len` is zero).
 * \param label_len   label length, in bytes.
 * \param sk          RSA private key.
 * \param data        input/output buffer.
 * \param len         encrypted/decrypted message length.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i32_oaep_decrypt(
	const br_hash_class *dig, const void *label, size_t label_len,
	const br_rsa_private_key *sk, void *data, size_t *len);

/**
 * \brief RSA encryption (OAEP) with the "i62" engine.
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_oaep_encrypt_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_oaep_encrypt
 *
 * \param rnd           source of random bytes.
 * \param dig           hash function to use with MGF1.
 * \param label         label value (may be `NULL` if `label_len` is zero).
 * \param label_len     label length, in bytes.
 * \param pk            RSA public key.
 * \param dst           destination buffer.
 * \param dst_max_len   destination buffer length (maximum encrypted data size).
 * \param src           message to encrypt.
 * \param src_len       source message length (in bytes).
 * \return  encrypted message length (in bytes), or 0 on error.
 */
size_t br_rsa_i62_oaep_encrypt(
	const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len,
	const br_rsa_public_key *pk,
	void *dst, size_t dst_max_len,
	const void *src, size_t src_len);

/**
 * \brief RSA decryption (OAEP) with the "i62" engine.
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_oaep_decrypt_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_oaep_decrypt
 *
 * \param dig         hash function to use with MGF1.
 * \param label       label value (may be `NULL` if `label_len` is zero).
 * \param label_len   label length, in bytes.
 * \param sk          RSA private key.
 * \param data        input/output buffer.
 * \param len         encrypted/decrypted message length.
 * \return  1 on success, 0 on error.
 */
uint32_t br_rsa_i62_oaep_decrypt(
	const br_hash_class *dig, const void *label, size_t label_len,
	const br_rsa_private_key *sk, void *data, size_t *len);

/**
 * \brief Get buffer size to hold RSA private key elements.
 *
 * This macro returns the length (in bytes) of the buffer needed to
 * receive the elements of a RSA private key, as generated by one of
 * the `br_rsa_*_keygen()` functions. If the provided size is a constant
 * expression, then the whole macro evaluates to a constant expression.
 *
 * \param size   target key size (modulus size, in bits)
 * \return  the length of the private key buffer, in bytes.
 */
#define BR_RSA_KBUF_PRIV_SIZE(size)    (5 * (((size) + 15) >> 4))

/**
 * \brief Get buffer size to hold RSA public key elements.
 *
 * This macro returns the length (in bytes) of the buffer needed to
 * receive the elements of a RSA public key, as generated by one of
 * the `br_rsa_*_keygen()` functions. If the provided size is a constant
 * expression, then the whole macro evaluates to a constant expression.
 *
 * \param size   target key size (modulus size, in bits)
 * \return  the length of the public key buffer, in bytes.
 */
#define BR_RSA_KBUF_PUB_SIZE(size)     (4 + (((size) + 7) >> 3))

/**
 * \brief Type for RSA key pair generator implementation.
 *
 * This function generates a new RSA key pair whose modulus has bit
 * length `size` bits. The private key elements are written in the
 * `kbuf_priv` buffer, and pointer values and length fields to these
 * elements are populated in the provided private key structure `sk`.
 * Similarly, the public key elements are written in `kbuf_pub`, with
 * pointers and lengths set in `pk`.
 *
 * If `pk` is `NULL`, then `kbuf_pub` may be `NULL`, and only the
 * private key is set.
 *
 * If `pubexp` is not zero, then its value will be used as public
 * exponent. Valid RSA public exponent values are odd integers
 * greater than 1. If `pubexp` is zero, then the public exponent will
 * have value 3.
 *
 * The provided PRNG (`rng_ctx`) must have already been initialized
 * and seeded.
 *
 * Returned value is 1 on success, 0 on error. An error is reported
 * if the requested range is outside of the supported key sizes, or
 * if an invalid non-zero public exponent value is provided. Supported
 * range starts at 512 bits, and up to an implementation-defined
 * maximum (by default 4096 bits). Note that key sizes up to 768 bits
 * have been broken in practice, and sizes lower than 2048 bits are
 * usually considered to be weak and should not be used.
 *
 * \param rng_ctx     source PRNG context (already initialized)
 * \param sk          RSA private key structure (destination)
 * \param kbuf_priv   buffer for private key elements
 * \param pk          RSA public key structure (destination), or `NULL`
 * \param kbuf_pub    buffer for public key elements, or `NULL`
 * \param size        target RSA modulus size (in bits)
 * \param pubexp      public exponent to use, or zero
 * \return  1 on success, 0 on error (invalid parameters)
 */
typedef uint32_t (*br_rsa_keygen)(
	const br_prng_class **rng_ctx,
	br_rsa_private_key *sk, void *kbuf_priv,
	br_rsa_public_key *pk, void *kbuf_pub,
	unsigned size, uint32_t pubexp);

/**
 * \brief RSA key pair generation with the "i15" engine.
 *
 * \see br_rsa_keygen
 *
 * \param rng_ctx     source PRNG context (already initialized)
 * \param sk          RSA private key structure (destination)
 * \param kbuf_priv   buffer for private key elements
 * \param pk          RSA public key structure (destination), or `NULL`
 * \param kbuf_pub    buffer for public key elements, or `NULL`
 * \param size        target RSA modulus size (in bits)
 * \param pubexp      public exponent to use, or zero
 * \return  1 on success, 0 on error (invalid parameters)
 */
uint32_t br_rsa_i15_keygen(
	const br_prng_class **rng_ctx,
	br_rsa_private_key *sk, void *kbuf_priv,
	br_rsa_public_key *pk, void *kbuf_pub,
	unsigned size, uint32_t pubexp);

/**
 * \brief RSA key pair generation with the "i31" engine.
 *
 * \see br_rsa_keygen
 *
 * \param rng_ctx     source PRNG context (already initialized)
 * \param sk          RSA private key structure (destination)
 * \param kbuf_priv   buffer for private key elements
 * \param pk          RSA public key structure (destination), or `NULL`
 * \param kbuf_pub    buffer for public key elements, or `NULL`
 * \param size        target RSA modulus size (in bits)
 * \param pubexp      public exponent to use, or zero
 * \return  1 on success, 0 on error (invalid parameters)
 */
uint32_t br_rsa_i31_keygen(
	const br_prng_class **rng_ctx,
	br_rsa_private_key *sk, void *kbuf_priv,
	br_rsa_public_key *pk, void *kbuf_pub,
	unsigned size, uint32_t pubexp);

/**
 * \brief RSA key pair generation with the "i62" engine.
 *
 * This function is defined only on architecture that offer a 64x64->128
 * opcode. Use `br_rsa_i62_keygen_get()` to dynamically obtain a pointer
 * to that function.
 *
 * \see br_rsa_keygen
 *
 * \param rng_ctx     source PRNG context (already initialized)
 * \param sk          RSA private key structure (destination)
 * \param kbuf_priv   buffer for private key elements
 * \param pk          RSA public key structure (destination), or `NULL`
 * \param kbuf_pub    buffer for public key elements, or `NULL`
 * \param size        target RSA modulus size (in bits)
 * \param pubexp      public exponent to use, or zero
 * \return  1 on success, 0 on error (invalid parameters)
 */
uint32_t br_rsa_i62_keygen(
	const br_prng_class **rng_ctx,
	br_rsa_private_key *sk, void *kbuf_priv,
	br_rsa_public_key *pk, void *kbuf_pub,
	unsigned size, uint32_t pubexp);

/**
 * \brief Get the RSA "i62" implementation (key pair generation),
 * if available.
 *
 * \return  the implementation, or 0.
 */
br_rsa_keygen br_rsa_i62_keygen_get(void);

/**
 * \brief Get "default" RSA implementation (key pair generation).
 *
 * This returns the preferred implementation of RSA (key pair generation)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_keygen br_rsa_keygen_get_default(void);

/**
 * \brief Type for a modulus computing function.
 *
 * Such a function computes the public modulus from the private key. The
 * encoded modulus (unsigned big-endian) is written on `n`, and the size
 * (in bytes) is returned. If `n` is `NULL`, then the size is returned but
 * the modulus itself is not computed.
 *
 * If the key size exceeds an internal limit, 0 is returned.
 *
 * \param n    destination buffer (or `NULL`).
 * \param sk   RSA private key.
 * \return  the modulus length (in bytes), or 0.
 */
typedef size_t (*br_rsa_compute_modulus)(void *n, const br_rsa_private_key *sk);

/**
 * \brief Recompute RSA modulus ("i15" engine).
 *
 * \see br_rsa_compute_modulus
 *
 * \param n    destination buffer (or `NULL`).
 * \param sk   RSA private key.
 * \return  the modulus length (in bytes), or 0.
 */
size_t br_rsa_i15_compute_modulus(void *n, const br_rsa_private_key *sk);

/**
 * \brief Recompute RSA modulus ("i31" engine).
 *
 * \see br_rsa_compute_modulus
 *
 * \param n    destination buffer (or `NULL`).
 * \param sk   RSA private key.
 * \return  the modulus length (in bytes), or 0.
 */
size_t br_rsa_i31_compute_modulus(void *n, const br_rsa_private_key *sk);

/**
 * \brief Get "default" RSA implementation (recompute modulus).
 *
 * This returns the preferred implementation of RSA (recompute modulus)
 * on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_compute_modulus br_rsa_compute_modulus_get_default(void);

/**
 * \brief Type for a public exponent computing function.
 *
 * Such a function recomputes the public exponent from the private key.
 * 0 is returned if any of the following occurs:
 *
 *   - Either `p` or `q` is not equal to 3 modulo 4.
 *
 *   - The public exponent does not fit on 32 bits.
 *
 *   - An internal limit is exceeded.
 *
 *   - The private key is invalid in some way.
 *
 * For all private keys produced by the key generator functions
 * (`br_rsa_keygen` type), this function succeeds and returns the true
 * public exponent. The public exponent is always an odd integer greater
 * than 1.
 *
 * \return  the public exponent, or 0.
 */
typedef uint32_t (*br_rsa_compute_pubexp)(const br_rsa_private_key *sk);

/**
 * \brief Recompute RSA public exponent ("i15" engine).
 *
 * \see br_rsa_compute_pubexp
 *
 * \return  the public exponent, or 0.
 */
uint32_t br_rsa_i15_compute_pubexp(const br_rsa_private_key *sk);

/**
 * \brief Recompute RSA public exponent ("i31" engine).
 *
 * \see br_rsa_compute_pubexp
 *
 * \return  the public exponent, or 0.
 */
uint32_t br_rsa_i31_compute_pubexp(const br_rsa_private_key *sk);

/**
 * \brief Get "default" RSA implementation (recompute public exponent).
 *
 * This returns the preferred implementation of RSA (recompute public
 * exponent) on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_compute_pubexp br_rsa_compute_pubexp_get_default(void);

/**
 * \brief Type for a private exponent computing function.
 *
 * An RSA private key (`br_rsa_private_key`) contains two reduced
 * private exponents, which are sufficient to perform private key
 * operations. However, standard encoding formats for RSA private keys
 * require also a copy of the complete private exponent (non-reduced),
 * which this function recomputes.
 *
 * This function suceeds if all the following conditions hold:
 *
 *   - Both private factors `p` and `q` are equal to 3 modulo 4.
 *
 *   - The provided public exponent `pubexp` is correct, and, in particular,
 *     is odd, relatively prime to `p-1` and `q-1`, and greater than 1.
 *
 *   - No internal storage limit is exceeded.
 *
 * For all private keys produced by the key generator functions
 * (`br_rsa_keygen` type), this function succeeds. Note that the API
 * restricts the public exponent to a maximum size of 32 bits.
 *
 * The encoded private exponent is written in `d` (unsigned big-endian
 * convention), and the length (in bytes) is returned. If `d` is `NULL`,
 * then the exponent is not written anywhere, but the length is still
 * returned. On error, 0 is returned.
 *
 * Not all error conditions are detected when `d` is `NULL`; therefore, the
 * returned value shall be checked also when actually producing the value.
 *
 * \param d        destination buffer (or `NULL`).
 * \param sk       RSA private key.
 * \param pubexp   the public exponent.
 * \return  the private exponent length (in bytes), or 0.
 */
typedef size_t (*br_rsa_compute_privexp)(void *d,
	const br_rsa_private_key *sk, uint32_t pubexp);

/**
 * \brief Recompute RSA private exponent ("i15" engine).
 *
 * \see br_rsa_compute_privexp
 *
 * \param d        destination buffer (or `NULL`).
 * \param sk       RSA private key.
 * \param pubexp   the public exponent.
 * \return  the private exponent length (in bytes), or 0.
 */
size_t br_rsa_i15_compute_privexp(void *d,
	const br_rsa_private_key *sk, uint32_t pubexp);

/**
 * \brief Recompute RSA private exponent ("i31" engine).
 *
 * \see br_rsa_compute_privexp
 *
 * \param d        destination buffer (or `NULL`).
 * \param sk       RSA private key.
 * \param pubexp   the public exponent.
 * \return  the private exponent length (in bytes), or 0.
 */
size_t br_rsa_i31_compute_privexp(void *d,
	const br_rsa_private_key *sk, uint32_t pubexp);

/**
 * \brief Get "default" RSA implementation (recompute private exponent).
 *
 * This returns the preferred implementation of RSA (recompute private
 * exponent) on the current system.
 *
 * \return  the default implementation.
 */
br_rsa_compute_privexp br_rsa_compute_privexp_get_default(void);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_EC_H__
#define BR_BEARSSL_EC_H__

#include <stddef.h>
#include <stdint.h>



#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_ec.h
 *
 * # Elliptic Curves
 *
 * This file documents the EC implementations provided with BearSSL, and
 * ECDSA.
 *
 * ## Elliptic Curve API
 *
 * Only "named curves" are supported. Each EC implementation supports
 * one or several named curves, identified by symbolic identifiers.
 * These identifiers are small integers, that correspond to the values
 * registered by the
 * [IANA](http://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-8).
 *
 * Since all currently defined elliptic curve identifiers are in the 0..31
 * range, it is convenient to encode support of some curves in a 32-bit
 * word, such that bit x corresponds to curve of identifier x.
 *
 * An EC implementation is incarnated by a `br_ec_impl` instance, that
 * offers the following fields:
 *
 *   - `supported_curves`
 *
 *      A 32-bit word that documents the identifiers of the curves supported
 *      by this implementation.
 *
 *   - `generator()`
 *
 *      Callback method that returns a pointer to the conventional generator
 *      point for that curve.
 *
 *   - `order()`
 *
 *      Callback method that returns a pointer to the subgroup order for
 *      that curve. That value uses unsigned big-endian encoding.
 *
 *   - `xoff()`
 *
 *      Callback method that returns the offset and length of the X
 *      coordinate in an encoded point.
 *
 *   - `mul()`
 *
 *      Multiply a curve point with an integer.
 *
 *   - `mulgen()`
 *
 *      Multiply the curve generator with an integer. This may be faster
 *      than the generic `mul()`.
 *
 *   - `muladd()`
 *
 *      Multiply two curve points by two integers, and return the sum of
 *      the two products.
 *
 * All curve points are represented in uncompressed format. The `mul()`
 * and `muladd()` methods take care to validate that the provided points
 * are really part of the relevant curve subgroup.
 *
 * For all point multiplication functions, the following holds:
 *
 *   - Functions validate that the provided points are valid members
 *     of the relevant curve subgroup. An error is reported if that is
 *     not the case.
 *
 *   - Processing is constant-time, even if the point operands are not
 *     valid. This holds for both the source and resulting points, and
 *     the multipliers (integers). Only the byte length of the provided
 *     multiplier arrays (not their actual value length in bits) may
 *     leak through timing-based side channels.
 *
 *   - The multipliers (integers) MUST be lower than the subgroup order.
 *     If this property is not met, then the result is indeterminate,
 *     but an error value is not necessarily returned.
 * 
 *
 * ## ECDSA
 *
 * ECDSA signatures have two standard formats, called "raw" and "asn1".
 * Internally, such a signature is a pair of modular integers `(r,s)`.
 * The "raw" format is the concatenation of the unsigned big-endian
 * encodings of these two integers, possibly left-padded with zeros so
 * that they have the same encoded length. The "asn1" format is the
 * DER encoding of an ASN.1 structure that contains the two integer
 * values:
 *
 *     ECDSASignature ::= SEQUENCE {
 *         r   INTEGER,
 *         s   INTEGER
 *     }
 *
 * In general, in all of X.509 and SSL/TLS, the "asn1" format is used.
 * BearSSL offers ECDSA implementations for both formats; conversion
 * functions between the two formats are also provided. Conversion of a
 * "raw" format signature into "asn1" may enlarge a signature by no more
 * than 9 bytes for all supported curves; conversely, conversion of an
 * "asn1" signature to "raw" may expand the signature but the "raw"
 * length will never be more than twice the length of the "asn1" length
 * (and usually it will be shorter).
 *
 * Note that for a given signature, the "raw" format is not fully
 * deterministic, in that it does not enforce a minimal common length.
 */

/*
 * Standard curve ID. These ID are equal to the assigned numerical
 * identifiers assigned to these curves for TLS:
 *    http://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-8
 */

/** \brief Identifier for named curve sect163k1. */
#define BR_EC_sect163k1           1

/** \brief Identifier for named curve sect163r1. */
#define BR_EC_sect163r1           2

/** \brief Identifier for named curve sect163r2. */
#define BR_EC_sect163r2           3

/** \brief Identifier for named curve sect193r1. */
#define BR_EC_sect193r1           4

/** \brief Identifier for named curve sect193r2. */
#define BR_EC_sect193r2           5

/** \brief Identifier for named curve sect233k1. */
#define BR_EC_sect233k1           6

/** \brief Identifier for named curve sect233r1. */
#define BR_EC_sect233r1           7

/** \brief Identifier for named curve sect239k1. */
#define BR_EC_sect239k1           8

/** \brief Identifier for named curve sect283k1. */
#define BR_EC_sect283k1           9

/** \brief Identifier for named curve sect283r1. */
#define BR_EC_sect283r1          10

/** \brief Identifier for named curve sect409k1. */
#define BR_EC_sect409k1          11

/** \brief Identifier for named curve sect409r1. */
#define BR_EC_sect409r1          12

/** \brief Identifier for named curve sect571k1. */
#define BR_EC_sect571k1          13

/** \brief Identifier for named curve sect571r1. */
#define BR_EC_sect571r1          14

/** \brief Identifier for named curve secp160k1. */
#define BR_EC_secp160k1          15

/** \brief Identifier for named curve secp160r1. */
#define BR_EC_secp160r1          16

/** \brief Identifier for named curve secp160r2. */
#define BR_EC_secp160r2          17

/** \brief Identifier for named curve secp192k1. */
#define BR_EC_secp192k1          18

/** \brief Identifier for named curve secp192r1. */
#define BR_EC_secp192r1          19

/** \brief Identifier for named curve secp224k1. */
#define BR_EC_secp224k1          20

/** \brief Identifier for named curve secp224r1. */
#define BR_EC_secp224r1          21

/** \brief Identifier for named curve secp256k1. */
#define BR_EC_secp256k1          22

/** \brief Identifier for named curve secp256r1. */
#define BR_EC_secp256r1          23

/** \brief Identifier for named curve secp384r1. */
#define BR_EC_secp384r1          24

/** \brief Identifier for named curve secp521r1. */
#define BR_EC_secp521r1          25

/** \brief Identifier for named curve brainpoolP256r1. */
#define BR_EC_brainpoolP256r1    26

/** \brief Identifier for named curve brainpoolP384r1. */
#define BR_EC_brainpoolP384r1    27

/** \brief Identifier for named curve brainpoolP512r1. */
#define BR_EC_brainpoolP512r1    28

/** \brief Identifier for named curve Curve25519. */
#define BR_EC_curve25519         29

/** \brief Identifier for named curve Curve448. */
#define BR_EC_curve448           30

/**
 * \brief Structure for an EC public key.
 */
typedef struct {
	/** \brief Identifier for the curve used by this key. */
	int curve;
	/** \brief Public curve point (uncompressed format). */
	unsigned char *q;
	/** \brief Length of public curve point (in bytes). */
	size_t qlen;
} br_ec_public_key;

/**
 * \brief Structure for an EC private key.
 *
 * The private key is an integer modulo the curve subgroup order. The
 * encoding below tolerates extra leading zeros. In general, it is
 * recommended that the private key has the same length as the curve
 * subgroup order.
 */
typedef struct {
	/** \brief Identifier for the curve used by this key. */
	int curve;
	/** \brief Private key (integer, unsigned big-endian encoding). */
	unsigned char *x;
	/** \brief Private key length (in bytes). */
	size_t xlen;
} br_ec_private_key;

/**
 * \brief Type for an EC implementation.
 */
typedef struct {
	/**
	 * \brief Supported curves.
	 *
	 * This word is a bitfield: bit `x` is set if the curve of ID `x`
	 * is supported. E.g. an implementation supporting both NIST P-256
	 * (secp256r1, ID 23) and NIST P-384 (secp384r1, ID 24) will have
	 * value `0x01800000` in this field.
	 */
	uint32_t supported_curves;

	/**
	 * \brief Get the conventional generator.
	 *
	 * This function returns the conventional generator (encoded
	 * curve point) for the specified curve. This function MUST NOT
	 * be called if the curve is not supported.
	 *
	 * \param curve   curve identifier.
	 * \param len     receiver for the encoded generator length (in bytes).
	 * \return  the encoded generator.
	 */
	const unsigned char *(*generator)(int curve, size_t *len);

	/**
	 * \brief Get the subgroup order.
	 *
	 * This function returns the order of the subgroup generated by
	 * the conventional generator, for the specified curve. Unsigned
	 * big-endian encoding is used. This function MUST NOT be called
	 * if the curve is not supported.
	 *
	 * \param curve   curve identifier.
	 * \param len     receiver for the encoded order length (in bytes).
	 * \return  the encoded order.
	 */
	const unsigned char *(*order)(int curve, size_t *len);

	/**
	 * \brief Get the offset and length for the X coordinate.
	 *
	 * This function returns the offset and length (in bytes) of
	 * the X coordinate in an encoded non-zero point.
	 *
	 * \param curve   curve identifier.
	 * \param len     receiver for the X coordinate length (in bytes).
	 * \return  the offset for the X coordinate (in bytes).
	 */
	size_t (*xoff)(int curve, size_t *len);

	/**
	 * \brief Multiply a curve point by an integer.
	 *
	 * The source point is provided in array `G` (of size `Glen` bytes);
	 * the multiplication result is written over it. The multiplier
	 * `x` (of size `xlen` bytes) uses unsigned big-endian encoding.
	 *
	 * Rules:
	 *
	 *   - The specified curve MUST be supported.
	 *
	 *   - The source point must be a valid point on the relevant curve
	 *     subgroup (and not the "point at infinity" either). If this is
	 *     not the case, then this function returns an error (0).
	 *
	 *   - The multiplier integer MUST be non-zero and less than the
	 *     curve subgroup order. If this property does not hold, then
	 *     the result is indeterminate and an error code is not
	 *     guaranteed.
	 *
	 * Returned value is 1 on success, 0 on error. On error, the
	 * contents of `G` are indeterminate.
	 *
	 * \param G       point to multiply.
	 * \param Glen    length of the encoded point (in bytes).
	 * \param x       multiplier (unsigned big-endian).
	 * \param xlen    multiplier length (in bytes).
	 * \param curve   curve identifier.
	 * \return  1 on success, 0 on error.
	 */
	uint32_t (*mul)(unsigned char *G, size_t Glen,
		const unsigned char *x, size_t xlen, int curve);

	/**
	 * \brief Multiply the generator by an integer.
	 *
	 * The multiplier MUST be non-zero and less than the curve
	 * subgroup order. Results are indeterminate if this property
	 * does not hold.
	 *
	 * \param R       output buffer for the point.
	 * \param x       multiplier (unsigned big-endian).
	 * \param xlen    multiplier length (in bytes).
	 * \param curve   curve identifier.
	 * \return  encoded result point length (in bytes).
	 */
	size_t (*mulgen)(unsigned char *R,
		const unsigned char *x, size_t xlen, int curve);

	/**
	 * \brief Multiply two points by two integers and add the
	 * results.
	 *
	 * The point `x*A + y*B` is computed and written back in the `A`
	 * array.
	 *
	 * Rules:
	 *
	 *   - The specified curve MUST be supported.
	 *
	 *   - The source points (`A` and `B`)  must be valid points on
	 *     the relevant curve subgroup (and not the "point at
	 *     infinity" either). If this is not the case, then this
	 *     function returns an error (0).
	 *
	 *   - If the `B` pointer is `NULL`, then the conventional
	 *     subgroup generator is used. With some implementations,
	 *     this may be faster than providing a pointer to the
	 *     generator.
	 *
	 *   - The multiplier integers (`x` and `y`) MUST be non-zero
	 *     and less than the curve subgroup order. If either integer
	 *     is zero, then an error is reported, but if one of them is
	 *     not lower than the subgroup order, then the result is
	 *     indeterminate and an error code is not guaranteed.
	 *
	 *   - If the final result is the point at infinity, then an
	 *     error is returned.
	 *
	 * Returned value is 1 on success, 0 on error. On error, the
	 * contents of `A` are indeterminate.
	 *
	 * \param A       first point to multiply.
	 * \param B       second point to multiply (`NULL` for the generator).
	 * \param len     common length of the encoded points (in bytes).
	 * \param x       multiplier for `A` (unsigned big-endian).
	 * \param xlen    length of multiplier for `A` (in bytes).
	 * \param y       multiplier for `A` (unsigned big-endian).
	 * \param ylen    length of multiplier for `A` (in bytes).
	 * \param curve   curve identifier.
	 * \return  1 on success, 0 on error.
	 */
	uint32_t (*muladd)(unsigned char *A, const unsigned char *B, size_t len,
		const unsigned char *x, size_t xlen,
		const unsigned char *y, size_t ylen, int curve);
} br_ec_impl;

/**
 * \brief EC implementation "i31".
 *
 * This implementation internally uses generic code for modular integers,
 * with a representation as sequences of 31-bit words. It supports secp256r1,
 * secp384r1 and secp521r1 (aka NIST curves P-256, P-384 and P-521).
 */
extern const br_ec_impl br_ec_prime_i31;

/**
 * \brief EC implementation "i15".
 *
 * This implementation internally uses generic code for modular integers,
 * with a representation as sequences of 15-bit words. It supports secp256r1,
 * secp384r1 and secp521r1 (aka NIST curves P-256, P-384 and P-521).
 */
extern const br_ec_impl br_ec_prime_i15;

/**
 * \brief EC implementation "m15" for P-256.
 *
 * This implementation uses specialised code for curve secp256r1 (also
 * known as NIST P-256), with optional Karatsuba decomposition, and fast
 * modular reduction thanks to the field modulus special format. Only
 * 32-bit multiplications are used (with 32-bit results, not 64-bit).
 */
extern const br_ec_impl br_ec_p256_m15;

/**
 * \brief EC implementation "m31" for P-256.
 *
 * This implementation uses specialised code for curve secp256r1 (also
 * known as NIST P-256), relying on multiplications of 31-bit values
 * (MUL31).
 */
extern const br_ec_impl br_ec_p256_m31;

/**
 * \brief EC implementation "m62" (specialised code) for P-256.
 *
 * This implementation uses custom code relying on multiplication of
 * integers up to 64 bits, with a 128-bit result. This implementation is
 * defined only on platforms that offer the 64x64->128 multiplication
 * support; use `br_ec_p256_m62_get()` to dynamically obtain a pointer
 * to that implementation.
 */
extern const br_ec_impl br_ec_p256_m62;

/**
 * \brief Get the "m62" implementation of P-256, if available.
 *
 * \return  the implementation, or 0.
 */
const br_ec_impl *br_ec_p256_m62_get(void);

/**
 * \brief EC implementation "m64" (specialised code) for P-256.
 *
 * This implementation uses custom code relying on multiplication of
 * integers up to 64 bits, with a 128-bit result. This implementation is
 * defined only on platforms that offer the 64x64->128 multiplication
 * support; use `br_ec_p256_m64_get()` to dynamically obtain a pointer
 * to that implementation.
 */
extern const br_ec_impl br_ec_p256_m64;

/**
 * \brief Get the "m64" implementation of P-256, if available.
 *
 * \return  the implementation, or 0.
 */
const br_ec_impl *br_ec_p256_m64_get(void);

/**
 * \brief EC implementation "i15" (generic code) for Curve25519.
 *
 * This implementation uses the generic code for modular integers (with
 * 15-bit words) to support Curve25519. Due to the specificities of the
 * curve definition, the following applies:
 *
 *   - `muladd()` is not implemented (the function returns 0 systematically).
 *   - `order()` returns 2^255-1, since the point multiplication algorithm
 *     accepts any 32-bit integer as input (it clears the top bit and low
 *     three bits systematically).
 */
extern const br_ec_impl br_ec_c25519_i15;

/**
 * \brief EC implementation "i31" (generic code) for Curve25519.
 *
 * This implementation uses the generic code for modular integers (with
 * 31-bit words) to support Curve25519. Due to the specificities of the
 * curve definition, the following applies:
 *
 *   - `muladd()` is not implemented (the function returns 0 systematically).
 *   - `order()` returns 2^255-1, since the point multiplication algorithm
 *     accepts any 32-bit integer as input (it clears the top bit and low
 *     three bits systematically).
 */
extern const br_ec_impl br_ec_c25519_i31;

/**
 * \brief EC implementation "m15" (specialised code) for Curve25519.
 *
 * This implementation uses custom code relying on multiplication of
 * integers up to 15 bits. Due to the specificities of the curve
 * definition, the following applies:
 *
 *   - `muladd()` is not implemented (the function returns 0 systematically).
 *   - `order()` returns 2^255-1, since the point multiplication algorithm
 *     accepts any 32-bit integer as input (it clears the top bit and low
 *     three bits systematically).
 */
extern const br_ec_impl br_ec_c25519_m15;

/**
 * \brief EC implementation "m31" (specialised code) for Curve25519.
 *
 * This implementation uses custom code relying on multiplication of
 * integers up to 31 bits. Due to the specificities of the curve
 * definition, the following applies:
 *
 *   - `muladd()` is not implemented (the function returns 0 systematically).
 *   - `order()` returns 2^255-1, since the point multiplication algorithm
 *     accepts any 32-bit integer as input (it clears the top bit and low
 *     three bits systematically).
 */
extern const br_ec_impl br_ec_c25519_m31;

/**
 * \brief EC implementation "m62" (specialised code) for Curve25519.
 *
 * This implementation uses custom code relying on multiplication of
 * integers up to 62 bits, with a 124-bit result. This implementation is
 * defined only on platforms that offer the 64x64->128 multiplication
 * support; use `br_ec_c25519_m62_get()` to dynamically obtain a pointer
 * to that implementation. Due to the specificities of the curve
 * definition, the following applies:
 *
 *   - `muladd()` is not implemented (the function returns 0 systematically).
 *   - `order()` returns 2^255-1, since the point multiplication algorithm
 *     accepts any 32-bit integer as input (it clears the top bit and low
 *     three bits systematically).
 */
extern const br_ec_impl br_ec_c25519_m62;

/**
 * \brief Get the "m62" implementation of Curve25519, if available.
 *
 * \return  the implementation, or 0.
 */
const br_ec_impl *br_ec_c25519_m62_get(void);

/**
 * \brief EC implementation "m64" (specialised code) for Curve25519.
 *
 * This implementation uses custom code relying on multiplication of
 * integers up to 64 bits, with a 128-bit result. This implementation is
 * defined only on platforms that offer the 64x64->128 multiplication
 * support; use `br_ec_c25519_m64_get()` to dynamically obtain a pointer
 * to that implementation. Due to the specificities of the curve
 * definition, the following applies:
 *
 *   - `muladd()` is not implemented (the function returns 0 systematically).
 *   - `order()` returns 2^255-1, since the point multiplication algorithm
 *     accepts any 32-bit integer as input (it clears the top bit and low
 *     three bits systematically).
 */
extern const br_ec_impl br_ec_c25519_m64;

/**
 * \brief Get the "m64" implementation of Curve25519, if available.
 *
 * \return  the implementation, or 0.
 */
const br_ec_impl *br_ec_c25519_m64_get(void);

/**
 * \brief Aggregate EC implementation "m15".
 *
 * This implementation is a wrapper for:
 *
 *   - `br_ec_c25519_m15` for Curve25519
 *   - `br_ec_p256_m15` for NIST P-256
 *   - `br_ec_prime_i15` for other curves (NIST P-384 and NIST-P512)
 */
extern const br_ec_impl br_ec_all_m15;

/**
 * \brief Aggregate EC implementation "m31".
 *
 * This implementation is a wrapper for:
 *
 *   - `br_ec_c25519_m31` for Curve25519
 *   - `br_ec_p256_m31` for NIST P-256
 *   - `br_ec_prime_i31` for other curves (NIST P-384 and NIST-P512)
 */
extern const br_ec_impl br_ec_all_m31;

/**
 * \brief Get the "default" EC implementation for the current system.
 *
 * This returns a pointer to the preferred implementation on the
 * current system.
 *
 * \return  the default EC implementation.
 */
const br_ec_impl *br_ec_get_default(void);

/**
 * \brief Convert a signature from "raw" to "asn1".
 *
 * Conversion is done "in place" and the new length is returned.
 * Conversion may enlarge the signature, but by no more than 9 bytes at
 * most. On error, 0 is returned (error conditions include an odd raw
 * signature length, or an oversized integer).
 *
 * \param sig       signature to convert.
 * \param sig_len   signature length (in bytes).
 * \return  the new signature length, or 0 on error.
 */
size_t br_ecdsa_raw_to_asn1(void *sig, size_t sig_len);

/**
 * \brief Convert a signature from "asn1" to "raw".
 *
 * Conversion is done "in place" and the new length is returned.
 * Conversion may enlarge the signature, but the new signature length
 * will be less than twice the source length at most. On error, 0 is
 * returned (error conditions include an invalid ASN.1 structure or an
 * oversized integer).
 *
 * \param sig       signature to convert.
 * \param sig_len   signature length (in bytes).
 * \return  the new signature length, or 0 on error.
 */
size_t br_ecdsa_asn1_to_raw(void *sig, size_t sig_len);

/**
 * \brief Type for an ECDSA signer function.
 *
 * A pointer to the EC implementation is provided. The hash value is
 * assumed to have the length inferred from the designated hash function
 * class.
 *
 * Signature is written in the buffer pointed to by `sig`, and the length
 * (in bytes) is returned. On error, nothing is written in the buffer,
 * and 0 is returned. This function returns 0 if the specified curve is
 * not supported by the provided EC implementation.
 *
 * The signature format is either "raw" or "asn1", depending on the
 * implementation; maximum length is predictable from the implemented
 * curve:
 *
 * | curve      | raw | asn1 |
 * | :--------- | --: | ---: |
 * | NIST P-256 |  64 |   72 |
 * | NIST P-384 |  96 |  104 |
 * | NIST P-521 | 132 |  139 |
 *
 * \param impl         EC implementation to use.
 * \param hf           hash function used to process the data.
 * \param hash_value   signed data (hashed).
 * \param sk           EC private key.
 * \param sig          destination buffer.
 * \return  the signature length (in bytes), or 0 on error.
 */
typedef size_t (*br_ecdsa_sign)(const br_ec_impl *impl,
	const br_hash_class *hf, const void *hash_value,
	const br_ec_private_key *sk, void *sig);

/**
 * \brief Type for an ECDSA signature verification function.
 *
 * A pointer to the EC implementation is provided. The hashed value,
 * computed over the purportedly signed data, is also provided with
 * its length.
 *
 * The signature format is either "raw" or "asn1", depending on the
 * implementation.
 *
 * Returned value is 1 on success (valid signature), 0 on error. This
 * function returns 0 if the specified curve is not supported by the
 * provided EC implementation.
 *
 * \param impl       EC implementation to use.
 * \param hash       signed data (hashed).
 * \param hash_len   hash value length (in bytes).
 * \param pk         EC public key.
 * \param sig        signature.
 * \param sig_len    signature length (in bytes).
 * \return  1 on success, 0 on error.
 */
typedef uint32_t (*br_ecdsa_vrfy)(const br_ec_impl *impl,
	const void *hash, size_t hash_len,
	const br_ec_public_key *pk, const void *sig, size_t sig_len);

/**
 * \brief ECDSA signature generator, "i31" implementation, "asn1" format.
 *
 * \see br_ecdsa_sign()
 *
 * \param impl         EC implementation to use.
 * \param hf           hash function used to process the data.
 * \param hash_value   signed data (hashed).
 * \param sk           EC private key.
 * \param sig          destination buffer.
 * \return  the signature length (in bytes), or 0 on error.
 */
size_t br_ecdsa_i31_sign_asn1(const br_ec_impl *impl,
	const br_hash_class *hf, const void *hash_value,
	const br_ec_private_key *sk, void *sig);

/**
 * \brief ECDSA signature generator, "i31" implementation, "raw" format.
 *
 * \see br_ecdsa_sign()
 *
 * \param impl         EC implementation to use.
 * \param hf           hash function used to process the data.
 * \param hash_value   signed data (hashed).
 * \param sk           EC private key.
 * \param sig          destination buffer.
 * \return  the signature length (in bytes), or 0 on error.
 */
size_t br_ecdsa_i31_sign_raw(const br_ec_impl *impl,
	const br_hash_class *hf, const void *hash_value,
	const br_ec_private_key *sk, void *sig);

/**
 * \brief ECDSA signature verifier, "i31" implementation, "asn1" format.
 *
 * \see br_ecdsa_vrfy()
 *
 * \param impl       EC implementation to use.
 * \param hash       signed data (hashed).
 * \param hash_len   hash value length (in bytes).
 * \param pk         EC public key.
 * \param sig        signature.
 * \param sig_len    signature length (in bytes).
 * \return  1 on success, 0 on error.
 */
uint32_t br_ecdsa_i31_vrfy_asn1(const br_ec_impl *impl,
	const void *hash, size_t hash_len,
	const br_ec_public_key *pk, const void *sig, size_t sig_len);

/**
 * \brief ECDSA signature verifier, "i31" implementation, "raw" format.
 *
 * \see br_ecdsa_vrfy()
 *
 * \param impl       EC implementation to use.
 * \param hash       signed data (hashed).
 * \param hash_len   hash value length (in bytes).
 * \param pk         EC public key.
 * \param sig        signature.
 * \param sig_len    signature length (in bytes).
 * \return  1 on success, 0 on error.
 */
uint32_t br_ecdsa_i31_vrfy_raw(const br_ec_impl *impl,
	const void *hash, size_t hash_len,
	const br_ec_public_key *pk, const void *sig, size_t sig_len);

/**
 * \brief ECDSA signature generator, "i15" implementation, "asn1" format.
 *
 * \see br_ecdsa_sign()
 *
 * \param impl         EC implementation to use.
 * \param hf           hash function used to process the data.
 * \param hash_value   signed data (hashed).
 * \param sk           EC private key.
 * \param sig          destination buffer.
 * \return  the signature length (in bytes), or 0 on error.
 */
size_t br_ecdsa_i15_sign_asn1(const br_ec_impl *impl,
	const br_hash_class *hf, const void *hash_value,
	const br_ec_private_key *sk, void *sig);

/**
 * \brief ECDSA signature generator, "i15" implementation, "raw" format.
 *
 * \see br_ecdsa_sign()
 *
 * \param impl         EC implementation to use.
 * \param hf           hash function used to process the data.
 * \param hash_value   signed data (hashed).
 * \param sk           EC private key.
 * \param sig          destination buffer.
 * \return  the signature length (in bytes), or 0 on error.
 */
size_t br_ecdsa_i15_sign_raw(const br_ec_impl *impl,
	const br_hash_class *hf, const void *hash_value,
	const br_ec_private_key *sk, void *sig);

/**
 * \brief ECDSA signature verifier, "i15" implementation, "asn1" format.
 *
 * \see br_ecdsa_vrfy()
 *
 * \param impl       EC implementation to use.
 * \param hash       signed data (hashed).
 * \param hash_len   hash value length (in bytes).
 * \param pk         EC public key.
 * \param sig        signature.
 * \param sig_len    signature length (in bytes).
 * \return  1 on success, 0 on error.
 */
uint32_t br_ecdsa_i15_vrfy_asn1(const br_ec_impl *impl,
	const void *hash, size_t hash_len,
	const br_ec_public_key *pk, const void *sig, size_t sig_len);

/**
 * \brief ECDSA signature verifier, "i15" implementation, "raw" format.
 *
 * \see br_ecdsa_vrfy()
 *
 * \param impl       EC implementation to use.
 * \param hash       signed data (hashed).
 * \param hash_len   hash value length (in bytes).
 * \param pk         EC public key.
 * \param sig        signature.
 * \param sig_len    signature length (in bytes).
 * \return  1 on success, 0 on error.
 */
uint32_t br_ecdsa_i15_vrfy_raw(const br_ec_impl *impl,
	const void *hash, size_t hash_len,
	const br_ec_public_key *pk, const void *sig, size_t sig_len);

/**
 * \brief Get "default" ECDSA implementation (signer, asn1 format).
 *
 * This returns the preferred implementation of ECDSA signature generation
 * ("asn1" output format) on the current system.
 *
 * \return  the default implementation.
 */
br_ecdsa_sign br_ecdsa_sign_asn1_get_default(void);

/**
 * \brief Get "default" ECDSA implementation (signer, raw format).
 *
 * This returns the preferred implementation of ECDSA signature generation
 * ("raw" output format) on the current system.
 *
 * \return  the default implementation.
 */
br_ecdsa_sign br_ecdsa_sign_raw_get_default(void);

/**
 * \brief Get "default" ECDSA implementation (verifier, asn1 format).
 *
 * This returns the preferred implementation of ECDSA signature verification
 * ("asn1" output format) on the current system.
 *
 * \return  the default implementation.
 */
br_ecdsa_vrfy br_ecdsa_vrfy_asn1_get_default(void);

/**
 * \brief Get "default" ECDSA implementation (verifier, raw format).
 *
 * This returns the preferred implementation of ECDSA signature verification
 * ("raw" output format) on the current system.
 *
 * \return  the default implementation.
 */
br_ecdsa_vrfy br_ecdsa_vrfy_raw_get_default(void);

/**
 * \brief Maximum size for EC private key element buffer.
 *
 * This is the largest number of bytes that `br_ec_keygen()` may need or
 * ever return.
 */
#define BR_EC_KBUF_PRIV_MAX_SIZE   72

/**
 * \brief Maximum size for EC public key element buffer.
 *
 * This is the largest number of bytes that `br_ec_compute_public()` may
 * need or ever return.
 */
#define BR_EC_KBUF_PUB_MAX_SIZE    145

/**
 * \brief Generate a new EC private key.
 *
 * If the specified `curve` is not supported by the elliptic curve
 * implementation (`impl`), then this function returns zero.
 *
 * The `sk` structure fields are set to the new private key data. In
 * particular, `sk.x` is made to point to the provided key buffer (`kbuf`),
 * in which the actual private key data is written. That buffer is assumed
 * to be large enough. The `BR_EC_KBUF_PRIV_MAX_SIZE` defines the maximum
 * size for all supported curves.
 *
 * The number of bytes used in `kbuf` is returned. If `kbuf` is `NULL`, then
 * the private key is not actually generated, and `sk` may also be `NULL`;
 * the minimum length for `kbuf` is still computed and returned.
 *
 * If `sk` is `NULL` but `kbuf` is not `NULL`, then the private key is
 * still generated and stored in `kbuf`.
 *
 * \param rng_ctx   source PRNG context (already initialized).
 * \param impl      the elliptic curve implementation.
 * \param sk        the private key structure to fill, or `NULL`.
 * \param kbuf      the key element buffer, or `NULL`.
 * \param curve     the curve identifier.
 * \return  the key data length (in bytes), or zero.
 */
size_t br_ec_keygen(const br_prng_class **rng_ctx,
	const br_ec_impl *impl, br_ec_private_key *sk,
	void *kbuf, int curve);

/**
 * \brief Compute EC public key from EC private key.
 *
 * This function uses the provided elliptic curve implementation (`impl`)
 * to compute the public key corresponding to the private key held in `sk`.
 * The public key point is written into `kbuf`, which is then linked from
 * the `*pk` structure. The size of the public key point, i.e. the number
 * of bytes used in `kbuf`, is returned.
 *
 * If `kbuf` is `NULL`, then the public key point is NOT computed, and
 * the public key structure `*pk` is unmodified (`pk` may be `NULL` in
 * that case). The size of the public key point is still returned.
 *
 * If `pk` is `NULL` but `kbuf` is not `NULL`, then the public key
 * point is computed and stored in `kbuf`, and its size is returned.
 *
 * If the curve used by the private key is not supported by the curve
 * implementation, then this function returns zero.
 *
 * The private key MUST be valid. An off-range private key value is not
 * necessarily detected, and leads to unpredictable results.
 *
 * \param impl   the elliptic curve implementation.
 * \param pk     the public key structure to fill (or `NULL`).
 * \param kbuf   the public key point buffer (or `NULL`).
 * \param sk     the source private key.
 * \return  the public key point length (in bytes), or zero.
 */
size_t br_ec_compute_pub(const br_ec_impl *impl, br_ec_public_key *pk,
	void *kbuf, const br_ec_private_key *sk);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_SSL_H__
#define BR_BEARSSL_SSL_H__

#include <stddef.h>
#include <stdint.h>






/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_X509_H__
#define BR_BEARSSL_X509_H__

#include <stddef.h>
#include <stdint.h>





#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_x509.h
 *
 * # X.509 Certificate Chain Processing
 *
 * An X.509 processing engine receives an X.509 chain, chunk by chunk,
 * as received from a SSL/TLS client or server (the client receives the
 * server's certificate chain, and the server receives the client's
 * certificate chain if it requested a client certificate). The chain
 * is thus injected in the engine in SSL order (end-entity first).
 *
 * The engine's job is to return the public key to use for SSL/TLS.
 * How exactly that key is obtained and verified is entirely up to the
 * engine.
 *
 * **The "known key" engine** returns a public key which is already known
 * from out-of-band information (e.g. the client _remembers_ the key from
 * a previous connection, as in the usual SSH model). This is the simplest
 * engine since it simply ignores the chain, thereby avoiding the need
 * for any decoding logic.
 *
 * **The "minimal" engine** implements minimal X.509 decoding and chain
 * validation:
 *
 *   - The provided chain should validate "as is". There is no attempt
 *     at reordering, skipping or downloading extra certificates.
 *
 *   - X.509 v1, v2 and v3 certificates are supported.
 *
 *   - Trust anchors are a DN and a public key. Each anchor is either a
 *     "CA" anchor, or a non-CA.
 *
 *   - If the end-entity certificate matches a non-CA anchor (subject DN
 *     is equal to the non-CA name, and public key is also identical to
 *     the anchor key), then this is a _direct trust_ case and the
 *     remaining certificates are ignored.
 *
 *   - Unless direct trust is applied, the chain must be verifiable up to
 *     a certificate whose issuer DN matches the DN from a "CA" trust anchor,
 *     and whose signature is verifiable against that anchor's public key.
 *     Subsequent certificates in the chain are ignored.
 *
 *   - The engine verifies subject/issuer DN matching, and enforces
 *     processing of Basic Constraints and Key Usage extensions. The
 *     Authority Key Identifier, Subject Key Identifier, Issuer Alt Name,
 *     Subject Directory Attribute, CRL Distribution Points, Freshest CRL,
 *     Authority Info Access and Subject Info Access extensions are
 *     ignored. The Subject Alt Name is decoded for the end-entity
 *     certificate under some conditions (see below). Other extensions
 *     are ignored if non-critical, or imply chain rejection if critical.
 *
 *   - The Subject Alt Name extension is parsed for names of type `dNSName`
 *     when decoding the end-entity certificate, and only if there is a
 *     server name to match. If there is no SAN extension, then the
 *     Common Name from the subjectDN is used. That name matching is
 *     case-insensitive and honours a single starting wildcard (i.e. if
 *     the name in the certificate starts with "`*.`" then this matches
 *     any word as first element). Note: this name matching is performed
 *     also in the "direct trust" model.
 *
 *   - DN matching is byte-to-byte equality (a future version might
 *     include some limited processing for case-insensitive matching and
 *     whitespace normalisation).
 *
 *   - Successful validation produces a public key type but also a set
 *     of allowed usages (`BR_KEYTYPE_KEYX` and/or `BR_KEYTYPE_SIGN`).
 *     The caller is responsible for checking that the key type and
 *     usages are compatible with the expected values (e.g. with the
 *     selected cipher suite, when the client validates the server's
 *     certificate).
 *
 * **Important caveats:**
 *
 *   - The "minimal" engine does not check revocation status. The relevant
 *     extensions are ignored, and CRL or OCSP responses are not gathered
 *     or checked.
 *
 *   - The "minimal" engine does not currently support Name Constraints
 *     (some basic functionality to handle sub-domains may be added in a
 *     later version).
 *
 *   - The decoder is not "validating" in the sense that it won't reject
 *     some certificates with invalid field values when these fields are
 *     not actually processed.
 */

/*
 * X.509 error codes are in the 32..63 range.
 */

/** \brief X.509 status: validation was successful; this is not actually
    an error. */
#define BR_ERR_X509_OK                    32

/** \brief X.509 status: invalid value in an ASN.1 structure. */
#define BR_ERR_X509_INVALID_VALUE         33

/** \brief X.509 status: truncated certificate. */
#define BR_ERR_X509_TRUNCATED             34

/** \brief X.509 status: empty certificate chain (no certificate at all). */
#define BR_ERR_X509_EMPTY_CHAIN           35

/** \brief X.509 status: decoding error: inner element extends beyond
    outer element size. */
#define BR_ERR_X509_INNER_TRUNC           36

/** \brief X.509 status: decoding error: unsupported tag class (application
    or private). */
#define BR_ERR_X509_BAD_TAG_CLASS         37

/** \brief X.509 status: decoding error: unsupported tag value. */
#define BR_ERR_X509_BAD_TAG_VALUE         38

/** \brief X.509 status: decoding error: indefinite length. */
#define BR_ERR_X509_INDEFINITE_LENGTH     39

/** \brief X.509 status: decoding error: extraneous element. */
#define BR_ERR_X509_EXTRA_ELEMENT         40

/** \brief X.509 status: decoding error: unexpected element. */
#define BR_ERR_X509_UNEXPECTED            41

/** \brief X.509 status: decoding error: expected constructed element, but
    is primitive. */
#define BR_ERR_X509_NOT_CONSTRUCTED       42

/** \brief X.509 status: decoding error: expected primitive element, but
    is constructed. */
#define BR_ERR_X509_NOT_PRIMITIVE         43

/** \brief X.509 status: decoding error: BIT STRING length is not multiple
    of 8. */
#define BR_ERR_X509_PARTIAL_BYTE          44

/** \brief X.509 status: decoding error: BOOLEAN value has invalid length. */
#define BR_ERR_X509_BAD_BOOLEAN           45

/** \brief X.509 status: decoding error: value is off-limits. */
#define BR_ERR_X509_OVERFLOW              46

/** \brief X.509 status: invalid distinguished name. */
#define BR_ERR_X509_BAD_DN                47

/** \brief X.509 status: invalid date/time representation. */
#define BR_ERR_X509_BAD_TIME              48

/** \brief X.509 status: certificate contains unsupported features that
    cannot be ignored. */
#define BR_ERR_X509_UNSUPPORTED           49

/** \brief X.509 status: key or signature size exceeds internal limits. */
#define BR_ERR_X509_LIMIT_EXCEEDED        50

/** \brief X.509 status: key type does not match that which was expected. */
#define BR_ERR_X509_WRONG_KEY_TYPE        51

/** \brief X.509 status: signature is invalid. */
#define BR_ERR_X509_BAD_SIGNATURE         52

/** \brief X.509 status: validation time is unknown. */
#define BR_ERR_X509_TIME_UNKNOWN          53

/** \brief X.509 status: certificate is expired or not yet valid. */
#define BR_ERR_X509_EXPIRED               54

/** \brief X.509 status: issuer/subject DN mismatch in the chain. */
#define BR_ERR_X509_DN_MISMATCH           55

/** \brief X.509 status: expected server name was not found in the chain. */
#define BR_ERR_X509_BAD_SERVER_NAME       56

/** \brief X.509 status: unknown critical extension in certificate. */
#define BR_ERR_X509_CRITICAL_EXTENSION    57

/** \brief X.509 status: not a CA, or path length constraint violation */
#define BR_ERR_X509_NOT_CA                58

/** \brief X.509 status: Key Usage extension prohibits intended usage. */
#define BR_ERR_X509_FORBIDDEN_KEY_USAGE   59

/** \brief X.509 status: public key found in certificate is too small. */
#define BR_ERR_X509_WEAK_PUBLIC_KEY       60

/** \brief X.509 status: chain could not be linked to a trust anchor. */
#define BR_ERR_X509_NOT_TRUSTED           62

/**
 * \brief Aggregate structure for public keys.
 */
typedef struct {
	/** \brief Key type: `BR_KEYTYPE_RSA` or `BR_KEYTYPE_EC` */
	unsigned char key_type;
	/** \brief Actual public key. */
	union {
		/** \brief RSA public key. */
		br_rsa_public_key rsa;
		/** \brief EC public key. */
		br_ec_public_key ec;
	} key;
} br_x509_pkey;

/**
 * \brief Distinguished Name (X.500) structure.
 *
 * The DN is DER-encoded.
 */
typedef struct {
	/** \brief Encoded DN data. */
	unsigned char *data;
	/** \brief Encoded DN length (in bytes). */
	size_t len;
} br_x500_name;

/**
 * \brief Trust anchor structure.
 */
typedef struct {
	/** \brief Encoded DN (X.500 name). */
	br_x500_name dn;
	/** \brief Anchor flags (e.g. `BR_X509_TA_CA`). */
	unsigned flags;
	/** \brief Anchor public key. */
	br_x509_pkey pkey;
} br_x509_trust_anchor;

/**
 * \brief Trust anchor flag: CA.
 *
 * A "CA" anchor is deemed fit to verify signatures on certificates.
 * A "non-CA" anchor is accepted only for direct trust (server's
 * certificate name and key match the anchor).
 */
#define BR_X509_TA_CA        0x0001

/*
 * Key type: combination of a basic key type (low 4 bits) and some
 * optional flags.
 *
 * For a public key, the basic key type only is set.
 *
 * For an expected key type, the flags indicate the intended purpose(s)
 * for the key; the basic key type may be set to 0 to indicate that any
 * key type compatible with the indicated purpose is acceptable.
 */
/** \brief Key type: algorithm is RSA. */
#define BR_KEYTYPE_RSA    1
/** \brief Key type: algorithm is EC. */
#define BR_KEYTYPE_EC     2

/**
 * \brief Key type: usage is "key exchange".
 *
 * This value is combined (with bitwise OR) with the algorithm
 * (`BR_KEYTYPE_RSA` or `BR_KEYTYPE_EC`) when informing the X.509
 * validation engine that it should find a public key of that type,
 * fit for key exchanges (e.g. `TLS_RSA_*` and `TLS_ECDH_*` cipher
 * suites).
 */
#define BR_KEYTYPE_KEYX   0x10

/**
 * \brief Key type: usage is "signature".
 *
 * This value is combined (with bitwise OR) with the algorithm
 * (`BR_KEYTYPE_RSA` or `BR_KEYTYPE_EC`) when informing the X.509
 * validation engine that it should find a public key of that type,
 * fit for signatures (e.g. `TLS_ECDHE_*` cipher suites).
 */
#define BR_KEYTYPE_SIGN   0x20

/*
 * start_chain   Called when a new chain is started. If 'server_name'
 *               is not NULL and non-empty, then it is a name that
 *               should be looked for in the EE certificate (in the
 *               SAN extension as dNSName, or in the subjectDN's CN
 *               if there is no SAN extension).
 *               The caller ensures that the provided 'server_name'
 *               pointer remains valid throughout validation.
 *
 * start_cert    Begins a new certificate in the chain. The provided
 *               length is in bytes; this is the total certificate length.
 *
 * append        Get some additional bytes for the current certificate.
 *
 * end_cert      Ends the current certificate.
 *
 * end_chain     Called at the end of the chain. Returned value is
 *               0 on success, or a non-zero error code.
 *
 * get_pkey      Returns the EE certificate public key.
 *
 * For a complete chain, start_chain() and end_chain() are always
 * called. For each certificate, start_cert(), some append() calls, then
 * end_cert() are called, in that order. There may be no append() call
 * at all if the certificate is empty (which is not valid but may happen
 * if the peer sends exactly that).
 *
 * get_pkey() shall return a pointer to a structure that is valid as
 * long as a new chain is not started. This may be a sub-structure
 * within the context for the engine. This function MAY return a valid
 * pointer to a public key even in some cases of validation failure,
 * depending on the validation engine.
 */

/**
 * \brief Class type for an X.509 engine.
 *
 * A certificate chain validation uses a caller-allocated context, which
 * contains the running state for that validation. Methods are called
 * in due order:
 *
 *   - `start_chain()` is called at the start of the validation.
 *   - Certificates are processed one by one, in SSL order (end-entity
 *     comes first). For each certificate, the following methods are
 *     called:
 *
 *       - `start_cert()` at the beginning of the certificate.
 *       - `append()` is called zero, one or more times, to provide
 *         the certificate (possibly in chunks).
 *       - `end_cert()` at the end of the certificate.
 *
 *   - `end_chain()` is called when the last certificate in the chain
 *     was processed.
 *   - `get_pkey()` is called after chain processing, if the chain
 *     validation was successful.
 *
 * A context structure may be reused; the `start_chain()` method shall
 * ensure (re)initialisation.
 */
typedef struct br_x509_class_ br_x509_class;
struct br_x509_class_ {
	/**
	 * \brief X.509 context size, in bytes.
	 */
	size_t context_size;

	/**
	 * \brief Start a new chain.
	 *
	 * This method shall set the vtable (first field) of the context
	 * structure.
	 *
	 * The `server_name`, if not `NULL`, will be considered as a
	 * fully qualified domain name, to be matched against the `dNSName`
	 * elements of the end-entity certificate's SAN extension (if there
	 * is no SAN, then the Common Name from the subjectDN will be used).
	 * If `server_name` is `NULL` then no such matching is performed.
	 *
	 * \param ctx           validation context.
	 * \param server_name   server name to match (or `NULL`).
	 */
	void (*start_chain)(const br_x509_class **ctx,
		const char *server_name);

	/**
	 * \brief Start a new certificate.
	 *
	 * \param ctx      validation context.
	 * \param length   new certificate length (in bytes).
	 */
	void (*start_cert)(const br_x509_class **ctx, uint32_t length);

	/**
	 * \brief Receive some bytes for the current certificate.
	 *
	 * This function may be called several times in succession for
	 * a given certificate. The caller guarantees that for each
	 * call, `len` is not zero, and the sum of all chunk lengths
	 * for a certificate matches the total certificate length which
	 * was provided in the previous `start_cert()` call.
	 *
	 * If the new certificate is empty (no byte at all) then this
	 * function won't be called at all.
	 *
	 * \param ctx   validation context.
	 * \param buf   certificate data chunk.
	 * \param len   certificate data chunk length (in bytes).
	 */
	void (*append)(const br_x509_class **ctx,
		const unsigned char *buf, size_t len);

	/**
	 * \brief Finish the current certificate.
	 *
	 * This function is called when the end of the current certificate
	 * is reached.
	 *
	 * \param ctx   validation context.
	 */
	void (*end_cert)(const br_x509_class **ctx);

	/**
	 * \brief Finish the chain.
	 *
	 * This function is called at the end of the chain. It shall
	 * return either 0 if the validation was successful, or a
	 * non-zero error code. The `BR_ERR_X509_*` constants are
	 * error codes, though other values may be possible.
	 *
	 * \param ctx   validation context.
	 * \return  0 on success, or a non-zero error code.
	 */
	unsigned (*end_chain)(const br_x509_class **ctx);

	/**
	 * \brief Get the resulting end-entity public key.
	 *
	 * The decoded public key is returned. The returned pointer
	 * may be valid only as long as the context structure is
	 * unmodified, i.e. it may cease to be valid if the context
	 * is released or reused.
	 *
	 * This function _may_ return `NULL` if the validation failed.
	 * However, returning a public key does not mean that the
	 * validation was wholly successful; some engines may return
	 * a decoded public key even if the chain did not end on a
	 * trusted anchor.
	 *
	 * If validation succeeded and `usage` is not `NULL`, then
	 * `*usage` is filled with a combination of `BR_KEYTYPE_SIGN`
	 * and/or `BR_KEYTYPE_KEYX` that specifies the validated key
	 * usage types. It is the caller's responsibility to check
	 * that value against the intended use of the public key.
	 *
	 * \param ctx   validation context.
	 * \return  the end-entity public key, or `NULL`.
	 */
	const br_x509_pkey *(*get_pkey)(
		const br_x509_class *const *ctx, unsigned *usages);
};

/**
 * \brief The "known key" X.509 engine structure.
 *
 * The structure contents are opaque (they shall not be accessed directly),
 * except for the first field (the vtable).
 *
 * The "known key" engine returns an externally configured public key,
 * and totally ignores the certificate contents.
 */
typedef struct {
	/** \brief Reference to the context vtable. */
	const br_x509_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	br_x509_pkey pkey;
	unsigned usages;
#endif
} br_x509_knownkey_context;

/**
 * \brief Class instance for the "known key" X.509 engine.
 */
extern const br_x509_class br_x509_knownkey_vtable;

/**
 * \brief Initialize a "known key" X.509 engine with a known RSA public key.
 *
 * The `usages` parameter indicates the allowed key usages for that key
 * (`BR_KEYTYPE_KEYX` and/or `BR_KEYTYPE_SIGN`).
 *
 * The provided pointers are linked in, not copied, so they must remain
 * valid while the public key may be in usage.
 *
 * \param ctx      context to initialise.
 * \param pk       known public key.
 * \param usages   allowed key usages.
 */
void br_x509_knownkey_init_rsa(br_x509_knownkey_context *ctx,
	const br_rsa_public_key *pk, unsigned usages);

/**
 * \brief Initialize a "known key" X.509 engine with a known EC public key.
 *
 * The `usages` parameter indicates the allowed key usages for that key
 * (`BR_KEYTYPE_KEYX` and/or `BR_KEYTYPE_SIGN`).
 *
 * The provided pointers are linked in, not copied, so they must remain
 * valid while the public key may be in usage.
 *
 * \param ctx      context to initialise.
 * \param pk       known public key.
 * \param usages   allowed key usages.
 */
void br_x509_knownkey_init_ec(br_x509_knownkey_context *ctx,
	const br_ec_public_key *pk, unsigned usages);

#ifndef BR_DOXYGEN_IGNORE
/*
 * The minimal X.509 engine has some state buffers which must be large
 * enough to simultaneously accommodate:
 * -- the public key extracted from the current certificate;
 * -- the signature on the current certificate or on the previous
 *    certificate;
 * -- the public key extracted from the EE certificate.
 *
 * We store public key elements in their raw unsigned big-endian
 * encoding. We want to support up to RSA-4096 with a short (up to 64
 * bits) public exponent, thus a buffer for a public key must have
 * length at least 520 bytes. Similarly, a RSA-4096 signature has length
 * 512 bytes.
 *
 * Though RSA public exponents can formally be as large as the modulus
 * (mathematically, even larger exponents would work, but PKCS#1 forbids
 * them), exponents that do not fit on 32 bits are extremely rare,
 * notably because some widespread implementations (e.g. Microsoft's
 * CryptoAPI) don't support them. Moreover, large public exponent do not
 * seem to imply any tangible security benefit, and they increase the
 * cost of public key operations. The X.509 "minimal" engine will tolerate
 * public exponents of arbitrary size as long as the modulus and the
 * exponent can fit together in the dedicated buffer.
 *
 * EC public keys are shorter than RSA public keys; even with curve
 * NIST P-521 (the largest curve we care to support), a public key is
 * encoded over 133 bytes only.
 */
#define BR_X509_BUFSIZE_KEY   520
#define BR_X509_BUFSIZE_SIG   512
#endif

/**
 * \brief Type for receiving a name element.
 *
 * An array of such structures can be provided to the X.509 decoding
 * engines. If the specified elements are found in the certificate
 * subject DN or the SAN extension, then the name contents are copied
 * as zero-terminated strings into the buffer.
 *
 * The decoder converts TeletexString and BMPString to UTF8String, and
 * ensures that the resulting string is zero-terminated. If the string
 * does not fit in the provided buffer, then the copy is aborted and an
 * error is reported.
 */
typedef struct {
	/**
	 * \brief Element OID.
	 *
	 * For X.500 name elements (to be extracted from the subject DN),
	 * this is the encoded OID for the requested name element; the
	 * first byte shall contain the length of the DER-encoded OID
	 * value, followed by the OID value (for instance, OID 2.5.4.3,
	 * for id-at-commonName, will be `03 55 04 03`). This is
	 * equivalent to full DER encoding with the length but without
	 * the tag.
	 *
	 * For SAN name elements, the first byte (`oid[0]`) has value 0,
	 * followed by another byte that matches the expected GeneralName
	 * tag. Allowed second byte values are then:
	 *
	 *   - 1: `rfc822Name`
	 *
	 *   - 2: `dNSName`
	 *
	 *   - 6: `uniformResourceIdentifier`
	 *
	 *   - 0: `otherName`
	 *
	 * If first and second byte are 0, then this is a SAN element of
	 * type `otherName`; the `oid[]` array should then contain, right
	 * after the two bytes of value 0, an encoded OID (with the same
	 * conventions as for X.500 name elements). If a match is found
	 * for that OID, then the corresponding name element will be
	 * extracted, as long as it is a supported string type.
	 */
	const unsigned char *oid;

	/**
	 * \brief Destination buffer.
	 */
	char *buf;

	/**
	 * \brief Length (in bytes) of the destination buffer.
	 *
	 * The buffer MUST NOT be smaller than 1 byte.
	 */
	size_t len;

	/**
	 * \brief Decoding status.
	 *
	 * Status is 0 if the name element was not found, 1 if it was
	 * found and decoded, or -1 on error. Error conditions include
	 * an unrecognised encoding, an invalid encoding, or a string
	 * too large for the destination buffer.
	 */
	int status;

} br_name_element;

/**
 * \brief Callback for validity date checks.
 *
 * The function receives as parameter an arbitrary user-provided context,
 * and the notBefore and notAfter dates specified in an X.509 certificate,
 * both expressed as a number of days and a number of seconds:
 *
 *   - Days are counted in a proleptic Gregorian calendar since
 *     January 1st, 0 AD. Year "0 AD" is the one that preceded "1 AD";
 *     it is also traditionally known as "1 BC".
 *
 *   - Seconds are counted since midnight, from 0 to 86400 (a count of
 *     86400 is possible only if a leap second happened).
 *
 * Each date and time is understood in the UTC time zone. The "Unix
 * Epoch" (January 1st, 1970, 00:00 UTC) corresponds to days=719528 and
 * seconds=0; the "Windows Epoch" (January 1st, 1601, 00:00 UTC) is
 * days=584754, seconds=0.
 *
 * This function must return -1 if the current date is strictly before
 * the "notBefore" time, or +1 if the current date is strictly after the
 * "notAfter" time. If neither condition holds, then the function returns
 * 0, which means that the current date falls within the validity range of
 * the certificate. If the function returns a value distinct from -1, 0
 * and +1, then this is interpreted as an unavailability of the current
 * time, which normally ends the validation process with a
 * `BR_ERR_X509_TIME_UNKNOWN` error.
 *
 * During path validation, this callback will be invoked for each
 * considered X.509 certificate. Validation fails if any of the calls
 * returns a non-zero value.
 *
 * The context value is an abritrary pointer set by the caller when
 * configuring this callback.
 *
 * \param tctx                 context pointer.
 * \param not_before_days      notBefore date (days since Jan 1st, 0 AD).
 * \param not_before_seconds   notBefore time (seconds, at most 86400).
 * \param not_after_days       notAfter date (days since Jan 1st, 0 AD).
 * \param not_after_seconds    notAfter time (seconds, at most 86400).
 * \return  -1, 0 or +1.
 */
typedef int (*br_x509_time_check)(void *tctx,
	uint32_t not_before_days, uint32_t not_before_seconds,
	uint32_t not_after_days, uint32_t not_after_seconds);

/**
 * \brief The "minimal" X.509 engine structure.
 *
 * The structure contents are opaque (they shall not be accessed directly),
 * except for the first field (the vtable).
 *
 * The "minimal" engine performs a rudimentary but serviceable X.509 path
 * validation.
 */
typedef struct {
	const br_x509_class *vtable;

#ifndef BR_DOXYGEN_IGNORE
	/* Structure for returning the EE public key. */
	br_x509_pkey pkey;

	/* CPU for the T0 virtual machine. */
	struct {
		uint32_t *dp;
		uint32_t *rp;
		const unsigned char *ip;
	} cpu;
	uint32_t dp_stack[31];
	uint32_t rp_stack[31];
	int err;

	/* Server name to match with the SAN / CN of the EE certificate. */
	const char *server_name;

	/* Validated key usages. */
	unsigned char key_usages;

	/* Explicitly set date and time. */
	uint32_t days, seconds;

	/* Current certificate length (in bytes). Set to 0 when the
	   certificate has been fully processed. */
	uint32_t cert_length;

	/* Number of certificates processed so far in the current chain.
	   It is incremented at the end of the processing of a certificate,
	   so it is 0 for the EE. */
	uint32_t num_certs;

	/* Certificate data chunk. */
	const unsigned char *hbuf;
	size_t hlen;

	/* The pad serves as destination for various operations. */
	unsigned char pad[256];

	/* Buffer for EE public key data. */
	unsigned char ee_pkey_data[BR_X509_BUFSIZE_KEY];

	/* Buffer for currently decoded public key. */
	unsigned char pkey_data[BR_X509_BUFSIZE_KEY];

	/* Signature type: signer key type, offset to the hash
	   function OID (in the T0 data block) and hash function
	   output length (TBS hash length). */
	unsigned char cert_signer_key_type;
	uint16_t cert_sig_hash_oid;
	unsigned char cert_sig_hash_len;

	/* Current/last certificate signature. */
	unsigned char cert_sig[BR_X509_BUFSIZE_SIG];
	uint16_t cert_sig_len;

	/* Minimum RSA key length (difference in bytes from 128). */
	int16_t min_rsa_size;

	/* Configured trust anchors. */
	const br_x509_trust_anchor *trust_anchors;
	size_t trust_anchors_num;

	/*
	 * Multi-hasher for the TBS.
	 */
	unsigned char do_mhash;
	br_multihash_context mhash;
	unsigned char tbs_hash[64];

	/*
	 * Simple hasher for the subject/issuer DN.
	 */
	unsigned char do_dn_hash;
	const br_hash_class *dn_hash_impl;
	br_hash_compat_context dn_hash;
	unsigned char current_dn_hash[64];
	unsigned char next_dn_hash[64];
	unsigned char saved_dn_hash[64];

	/*
	 * Name elements to gather.
	 */
	br_name_element *name_elts;
	size_t num_name_elts;

	/*
	 * Callback function (and context) to get the current date.
	 */
	void *itime_ctx;
	br_x509_time_check itime;

	/*
	 * Public key cryptography implementations (signature verification).
	 */
	br_rsa_pkcs1_vrfy irsa;
	br_ecdsa_vrfy iecdsa;
	const br_ec_impl *iec;
#endif

} br_x509_minimal_context;

/**
 * \brief Class instance for the "minimal" X.509 engine.
 */
extern const br_x509_class br_x509_minimal_vtable;

/**
 * \brief Initialise a "minimal" X.509 engine.
 *
 * The `dn_hash_impl` parameter shall be a hash function internally used
 * to match X.500 names (subject/issuer DN, and anchor names). Any standard
 * hash function may be used, but a collision-resistant hash function is
 * advised.
 *
 * After initialization, some implementations for signature verification
 * (hash functions and signature algorithms) MUST be added.
 *
 * \param ctx                 context to initialise.
 * \param dn_hash_impl        hash function for DN comparisons.
 * \param trust_anchors       trust anchors.
 * \param trust_anchors_num   number of trust anchors.
 */
void br_x509_minimal_init(br_x509_minimal_context *ctx,
	const br_hash_class *dn_hash_impl,
	const br_x509_trust_anchor *trust_anchors, size_t trust_anchors_num);

/**
 * \brief Set a supported hash function in an X.509 "minimal" engine.
 *
 * Hash functions are used with signature verification algorithms.
 * Once initialised (with `br_x509_minimal_init()`), the context must
 * be configured with the hash functions it shall support for that
 * purpose. The hash function identifier MUST be one of the standard
 * hash function identifiers (1 to 6, for MD5, SHA-1, SHA-224, SHA-256,
 * SHA-384 and SHA-512).
 *
 * If `impl` is `NULL`, this _removes_ support for the designated
 * hash function.
 *
 * \param ctx    validation context.
 * \param id     hash function identifier (from 1 to 6).
 * \param impl   hash function implementation (or `NULL`).
 */
static inline void
br_x509_minimal_set_hash(br_x509_minimal_context *ctx,
	int id, const br_hash_class *impl)
{
	br_multihash_setimpl(&ctx->mhash, id, impl);
}

/**
 * \brief Set a RSA signature verification implementation in the X.509
 * "minimal" engine.
 *
 * Once initialised (with `br_x509_minimal_init()`), the context must
 * be configured with the signature verification implementations that
 * it is supposed to support. If `irsa` is `0`, then the RSA support
 * is disabled.
 *
 * \param ctx    validation context.
 * \param irsa   RSA signature verification implementation (or `0`).
 */
static inline void
br_x509_minimal_set_rsa(br_x509_minimal_context *ctx,
	br_rsa_pkcs1_vrfy irsa)
{
	ctx->irsa = irsa;
}

/**
 * \brief Set a ECDSA signature verification implementation in the X.509
 * "minimal" engine.
 *
 * Once initialised (with `br_x509_minimal_init()`), the context must
 * be configured with the signature verification implementations that
 * it is supposed to support.
 *
 * If `iecdsa` is `0`, then this call disables ECDSA support; in that
 * case, `iec` may be `NULL`. Otherwise, `iecdsa` MUST point to a function
 * that verifies ECDSA signatures with format "asn1", and it will use
 * `iec` as underlying elliptic curve support.
 *
 * \param ctx      validation context.
 * \param iec      elliptic curve implementation (or `NULL`).
 * \param iecdsa   ECDSA implementation (or `0`).
 */
static inline void
br_x509_minimal_set_ecdsa(br_x509_minimal_context *ctx,
	const br_ec_impl *iec, br_ecdsa_vrfy iecdsa)
{
	ctx->iecdsa = iecdsa;
	ctx->iec = iec;
}

/**
 * \brief Initialise a "minimal" X.509 engine with default algorithms.
 *
 * This function performs the same job as `br_x509_minimal_init()`, but
 * also sets implementations for RSA, ECDSA, and the standard hash
 * functions.
 *
 * \param ctx                 context to initialise.
 * \param trust_anchors       trust anchors.
 * \param trust_anchors_num   number of trust anchors.
 */
void br_x509_minimal_init_full(br_x509_minimal_context *ctx,
	const br_x509_trust_anchor *trust_anchors, size_t trust_anchors_num);

/**
 * \brief Set the validation time for the X.509 "minimal" engine.
 *
 * The validation time is set as two 32-bit integers, for days and
 * seconds since a fixed epoch:
 *
 *   - Days are counted in a proleptic Gregorian calendar since
 *     January 1st, 0 AD. Year "0 AD" is the one that preceded "1 AD";
 *     it is also traditionally known as "1 BC".
 *
 *   - Seconds are counted since midnight, from 0 to 86400 (a count of
 *     86400 is possible only if a leap second happened).
 *
 * The validation date and time is understood in the UTC time zone. The
 * "Unix Epoch" (January 1st, 1970, 00:00 UTC) corresponds to days=719528
 * and seconds=0; the "Windows Epoch" (January 1st, 1601, 00:00 UTC) is
 * days=584754, seconds=0.
 *
 * If the validation date and time are not explicitly set, but BearSSL
 * was compiled with support for the system clock on the underlying
 * platform, then the current time will automatically be used. Otherwise,
 * not setting the validation date and time implies a validation
 * failure (except in case of direct trust of the EE key).
 *
 * \param ctx       validation context.
 * \param days      days since January 1st, 0 AD (Gregorian calendar).
 * \param seconds   seconds since midnight (0 to 86400).
 */
static inline void
br_x509_minimal_set_time(br_x509_minimal_context *ctx,
	uint32_t days, uint32_t seconds)
{
	ctx->days = days;
	ctx->seconds = seconds;
	ctx->itime = 0;
}

/**
 * \brief Set the validity range callback function for the X.509
 * "minimal" engine.
 *
 * The provided function will be invoked to check whether the validation
 * date is within the validity range for a given X.509 certificate; a
 * call will be issued for each considered certificate. The provided
 * context pointer (itime_ctx) will be passed as first parameter to the
 * callback.
 *
 * \param tctx   context for callback invocation.
 * \param cb     callback function.
 */
static inline void
br_x509_minimal_set_time_callback(br_x509_minimal_context *ctx,
	void *itime_ctx, br_x509_time_check itime)
{
	ctx->itime_ctx = itime_ctx;
	ctx->itime = itime;
}

/**
 * \brief Set the minimal acceptable length for RSA keys (X.509 "minimal"
 * engine).
 *
 * The RSA key length is expressed in bytes. The default minimum key
 * length is 128 bytes, corresponding to 1017 bits. RSA keys shorter
 * than the configured length will be rejected, implying validation
 * failure. This setting applies to keys extracted from certificates
 * (both end-entity, and intermediate CA) but not to "CA" trust anchors.
 *
 * \param ctx           validation context.
 * \param byte_length   minimum RSA key length, **in bytes** (not bits).
 */
static inline void
br_x509_minimal_set_minrsa(br_x509_minimal_context *ctx, int byte_length)
{
	ctx->min_rsa_size = (int16_t)(byte_length - 128);
}

/**
 * \brief Set the name elements to gather.
 *
 * The provided array is linked in the context. The elements are
 * gathered from the EE certificate. If the same element type is
 * requested several times, then the relevant structures will be filled
 * in the order the matching values are encountered in the certificate.
 *
 * \param ctx        validation context.
 * \param elts       array of name element structures to fill.
 * \param num_elts   number of name element structures to fill.
 */
static inline void
br_x509_minimal_set_name_elements(br_x509_minimal_context *ctx,
	br_name_element *elts, size_t num_elts)
{
	ctx->name_elts = elts;
	ctx->num_name_elts = num_elts;
}

/**
 * \brief X.509 decoder context.
 *
 * This structure is _not_ for X.509 validation, but for extracting
 * names and public keys from encoded certificates. Intended usage is
 * to use (self-signed) certificates as trust anchors.
 *
 * Contents are opaque and shall not be accessed directly.
 */
typedef struct {

#ifndef BR_DOXYGEN_IGNORE
	/* Structure for returning the public key. */
	br_x509_pkey pkey;

	/* CPU for the T0 virtual machine. */
	struct {
		uint32_t *dp;
		uint32_t *rp;
		const unsigned char *ip;
	} cpu;
	uint32_t dp_stack[32];
	uint32_t rp_stack[32];
	int err;

	/* The pad serves as destination for various operations. */
	unsigned char pad[256];

	/* Flag set when decoding succeeds. */
	unsigned char decoded;

	/* Validity dates. */
	uint32_t notbefore_days, notbefore_seconds;
	uint32_t notafter_days, notafter_seconds;

	/* The "CA" flag. This is set to true if the certificate contains
	   a Basic Constraints extension that asserts CA status. */
	unsigned char isCA;

	/* DN processing: the subject DN is extracted and pushed to the
	   provided callback. */
	unsigned char copy_dn;
	void *append_dn_ctx;
	void (*append_dn)(void *ctx, const void *buf, size_t len);

	/* Certificate data chunk. */
	const unsigned char *hbuf;
	size_t hlen;

	/* Buffer for decoded public key. */
	unsigned char pkey_data[BR_X509_BUFSIZE_KEY];

	/* Type of key and hash function used in the certificate signature. */
	unsigned char signer_key_type;
	unsigned char signer_hash_id;
#endif

} br_x509_decoder_context;

/**
 * \brief Initialise an X.509 decoder context for processing a new
 * certificate.
 *
 * The `append_dn()` callback (with opaque context `append_dn_ctx`)
 * will be invoked to receive, chunk by chunk, the certificate's
 * subject DN. If `append_dn` is `0` then the subject DN will be
 * ignored.
 *
 * \param ctx             X.509 decoder context to initialise.
 * \param append_dn       DN receiver callback (or `0`).
 * \param append_dn_ctx   context for the DN receiver callback.
 */
void br_x509_decoder_init(br_x509_decoder_context *ctx,
	void (*append_dn)(void *ctx, const void *buf, size_t len),
	void *append_dn_ctx);

/**
 * \brief Push some certificate bytes into a decoder context.
 *
 * If `len` is non-zero, then that many bytes are pushed, from address
 * `data`, into the provided decoder context.
 *
 * \param ctx    X.509 decoder context.
 * \param data   certificate data chunk.
 * \param len    certificate data chunk length (in bytes).
 */
void br_x509_decoder_push(br_x509_decoder_context *ctx,
	const void *data, size_t len);

/**
 * \brief Obtain the decoded public key.
 *
 * Returned value is a pointer to a structure internal to the decoder
 * context; releasing or reusing the decoder context invalidates that
 * structure.
 *
 * If decoding was not finished, or failed, then `NULL` is returned.
 *
 * \param ctx   X.509 decoder context.
 * \return  the public key, or `NULL` on unfinished/error.
 */
static inline br_x509_pkey *
br_x509_decoder_get_pkey(br_x509_decoder_context *ctx)
{
	if (ctx->decoded && ctx->err == 0) {
		return &ctx->pkey;
	} else {
		return NULL;
	}
}

/**
 * \brief Get decoder error status.
 *
 * If no error was reported yet but the certificate decoding is not
 * finished, then the error code is `BR_ERR_X509_TRUNCATED`. If decoding
 * was successful, then 0 is returned.
 *
 * \param ctx   X.509 decoder context.
 * \return  0 on successful decoding, or a non-zero error code.
 */
static inline int
br_x509_decoder_last_error(br_x509_decoder_context *ctx)
{
	if (ctx->err != 0) {
		return ctx->err;
	}
	if (!ctx->decoded) {
		return BR_ERR_X509_TRUNCATED;
	}
	return 0;
}

/**
 * \brief Get the "isCA" flag from an X.509 decoder context.
 *
 * This flag is set if the decoded certificate claims to be a CA through
 * a Basic Constraints extension. This flag should not be read before
 * decoding completed successfully.
 *
 * \param ctx   X.509 decoder context.
 * \return  the "isCA" flag.
 */
static inline int
br_x509_decoder_isCA(br_x509_decoder_context *ctx)
{
	return ctx->isCA;
}

/**
 * \brief Get the issuing CA key type (type of algorithm used to sign the
 * decoded certificate).
 *
 * This is `BR_KEYTYPE_RSA` or `BR_KEYTYPE_EC`. The value 0 is returned
 * if the signature type was not recognised.
 *
 * \param ctx   X.509 decoder context.
 * \return  the issuing CA key type.
 */
static inline int
br_x509_decoder_get_signer_key_type(br_x509_decoder_context *ctx)
{
	return ctx->signer_key_type;
}

/**
 * \brief Get the identifier for the hash function used to sign the decoded
 * certificate.
 *
 * This is 0 if the hash function was not recognised.
 *
 * \param ctx   X.509 decoder context.
 * \return  the signature hash function identifier.
 */
static inline int
br_x509_decoder_get_signer_hash_id(br_x509_decoder_context *ctx)
{
	return ctx->signer_hash_id;
}

/**
 * \brief Type for an X.509 certificate (DER-encoded).
 */
typedef struct {
	/** \brief The DER-encoded certificate data. */
	unsigned char *data;
	/** \brief The DER-encoded certificate length (in bytes). */
	size_t data_len;
} br_x509_certificate;

/**
 * \brief Private key decoder context.
 *
 * The private key decoder recognises RSA and EC private keys, either in
 * their raw, DER-encoded format, or wrapped in an unencrypted PKCS#8
 * archive (again DER-encoded).
 *
 * Structure contents are opaque and shall not be accessed directly.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	/* Structure for returning the private key. */
	union {
		br_rsa_private_key rsa;
		br_ec_private_key ec;
	} key;

	/* CPU for the T0 virtual machine. */
	struct {
		uint32_t *dp;
		uint32_t *rp;
		const unsigned char *ip;
	} cpu;
	uint32_t dp_stack[32];
	uint32_t rp_stack[32];
	int err;

	/* Private key data chunk. */
	const unsigned char *hbuf;
	size_t hlen;

	/* The pad serves as destination for various operations. */
	unsigned char pad[256];

	/* Decoded key type; 0 until decoding is complete. */
	unsigned char key_type;

	/* Buffer for the private key elements. It shall be large enough
	   to accommodate all elements for a RSA-4096 private key (roughly
	   five 2048-bit integers, possibly a bit more). */
	unsigned char key_data[3 * BR_X509_BUFSIZE_SIG];
#endif
} br_skey_decoder_context;

/**
 * \brief Initialise a private key decoder context.
 *
 * \param ctx   key decoder context to initialise.
 */
void br_skey_decoder_init(br_skey_decoder_context *ctx);

/**
 * \brief Push some data bytes into a private key decoder context.
 *
 * If `len` is non-zero, then that many data bytes, starting at address
 * `data`, are pushed into the decoder.
 *
 * \param ctx    key decoder context.
 * \param data   private key data chunk.
 * \param len    private key data chunk length (in bytes).
 */
void br_skey_decoder_push(br_skey_decoder_context *ctx,
	const void *data, size_t len);

/**
 * \brief Get the decoding status for a private key.
 *
 * Decoding status is 0 on success, or a non-zero error code. If the
 * decoding is unfinished when this function is called, then the
 * status code `BR_ERR_X509_TRUNCATED` is returned.
 *
 * \param ctx   key decoder context.
 * \return  0 on successful decoding, or a non-zero error code.
 */
static inline int
br_skey_decoder_last_error(const br_skey_decoder_context *ctx)
{
	if (ctx->err != 0) {
		return ctx->err;
	}
	if (ctx->key_type == 0) {
		return BR_ERR_X509_TRUNCATED;
	}
	return 0;
}

/**
 * \brief Get the decoded private key type.
 *
 * Private key type is `BR_KEYTYPE_RSA` or `BR_KEYTYPE_EC`. If decoding is
 * not finished or failed, then 0 is returned.
 *
 * \param ctx   key decoder context.
 * \return  decoded private key type, or 0.
 */
static inline int
br_skey_decoder_key_type(const br_skey_decoder_context *ctx)
{
	if (ctx->err == 0) {
		return ctx->key_type;
	} else {
		return 0;
	}
}

/**
 * \brief Get the decoded RSA private key.
 *
 * This function returns `NULL` if the decoding failed, or is not
 * finished, or the key is not RSA. The returned pointer references
 * structures within the context that can become invalid if the context
 * is reused or released.
 *
 * \param ctx   key decoder context.
 * \return  decoded RSA private key, or `NULL`.
 */
static inline const br_rsa_private_key *
br_skey_decoder_get_rsa(const br_skey_decoder_context *ctx)
{
	if (ctx->err == 0 && ctx->key_type == BR_KEYTYPE_RSA) {
		return &ctx->key.rsa;
	} else {
		return NULL;
	}
}

/**
 * \brief Get the decoded EC private key.
 *
 * This function returns `NULL` if the decoding failed, or is not
 * finished, or the key is not EC. The returned pointer references
 * structures within the context that can become invalid if the context
 * is reused or released.
 *
 * \param ctx   key decoder context.
 * \return  decoded EC private key, or `NULL`.
 */
static inline const br_ec_private_key *
br_skey_decoder_get_ec(const br_skey_decoder_context *ctx)
{
	if (ctx->err == 0 && ctx->key_type == BR_KEYTYPE_EC) {
		return &ctx->key.ec;
	} else {
		return NULL;
	}
}

/**
 * \brief Encode an RSA private key (raw DER format).
 *
 * This function encodes the provided key into the "raw" format specified
 * in PKCS#1 (RFC 8017, Appendix C, type `RSAPrivateKey`), with DER
 * encoding rules.
 *
 * The key elements are:
 *
 *  - `sk`: the private key (`p`, `q`, `dp`, `dq` and `iq`)
 *
 *  - `pk`: the public key (`n` and `e`)
 *
 *  - `d` (size: `dlen` bytes): the private exponent
 *
 * The public key elements, and the private exponent `d`, can be
 * recomputed from the private key (see `br_rsa_compute_modulus()`,
 * `br_rsa_compute_pubexp()` and `br_rsa_compute_privexp()`).
 *
 * If `dest` is not `NULL`, then the encoded key is written at that
 * address, and the encoded length (in bytes) is returned. If `dest` is
 * `NULL`, then nothing is written, but the encoded length is still
 * computed and returned.
 *
 * \param dest   the destination buffer (or `NULL`).
 * \param sk     the RSA private key.
 * \param pk     the RSA public key.
 * \param d      the RSA private exponent.
 * \param dlen   the RSA private exponent length (in bytes).
 * \return  the encoded key length (in bytes).
 */
size_t br_encode_rsa_raw_der(void *dest, const br_rsa_private_key *sk,
	const br_rsa_public_key *pk, const void *d, size_t dlen);

/**
 * \brief Encode an RSA private key (PKCS#8 DER format).
 *
 * This function encodes the provided key into the PKCS#8 format
 * (RFC 5958, type `OneAsymmetricKey`). It wraps around the "raw DER"
 * format for the RSA key, as implemented by `br_encode_rsa_raw_der()`.
 *
 * The key elements are:
 *
 *  - `sk`: the private key (`p`, `q`, `dp`, `dq` and `iq`)
 *
 *  - `pk`: the public key (`n` and `e`)
 *
 *  - `d` (size: `dlen` bytes): the private exponent
 *
 * The public key elements, and the private exponent `d`, can be
 * recomputed from the private key (see `br_rsa_compute_modulus()`,
 * `br_rsa_compute_pubexp()` and `br_rsa_compute_privexp()`).
 *
 * If `dest` is not `NULL`, then the encoded key is written at that
 * address, and the encoded length (in bytes) is returned. If `dest` is
 * `NULL`, then nothing is written, but the encoded length is still
 * computed and returned.
 *
 * \param dest   the destination buffer (or `NULL`).
 * \param sk     the RSA private key.
 * \param pk     the RSA public key.
 * \param d      the RSA private exponent.
 * \param dlen   the RSA private exponent length (in bytes).
 * \return  the encoded key length (in bytes).
 */
size_t br_encode_rsa_pkcs8_der(void *dest, const br_rsa_private_key *sk,
	const br_rsa_public_key *pk, const void *d, size_t dlen);

/**
 * \brief Encode an EC private key (raw DER format).
 *
 * This function encodes the provided key into the "raw" format specified
 * in RFC 5915 (type `ECPrivateKey`), with DER encoding rules.
 *
 * The private key is provided in `sk`, the public key being `pk`. If
 * `pk` is `NULL`, then the encoded key will not include the public key
 * in its `publicKey` field (which is nominally optional).
 *
 * If `dest` is not `NULL`, then the encoded key is written at that
 * address, and the encoded length (in bytes) is returned. If `dest` is
 * `NULL`, then nothing is written, but the encoded length is still
 * computed and returned.
 *
 * If the key cannot be encoded (e.g. because there is no known OBJECT
 * IDENTIFIER for the used curve), then 0 is returned.
 *
 * \param dest   the destination buffer (or `NULL`).
 * \param sk     the EC private key.
 * \param pk     the EC public key (or `NULL`).
 * \return  the encoded key length (in bytes), or 0.
 */
size_t br_encode_ec_raw_der(void *dest,
	const br_ec_private_key *sk, const br_ec_public_key *pk);

/**
 * \brief Encode an EC private key (PKCS#8 DER format).
 *
 * This function encodes the provided key into the PKCS#8 format
 * (RFC 5958, type `OneAsymmetricKey`). The curve is identified
 * by an OID provided as parameters to the `privateKeyAlgorithm`
 * field. The private key value (contents of the `privateKey` field)
 * contains the DER encoding of the `ECPrivateKey` type defined in
 * RFC 5915, without the `parameters` field (since they would be
 * redundant with the information in `privateKeyAlgorithm`).
 *
 * The private key is provided in `sk`, the public key being `pk`. If
 * `pk` is not `NULL`, then the encoded public key is included in the
 * `publicKey` field of the private key value (but not in the `publicKey`
 * field of the PKCS#8 `OneAsymmetricKey` wrapper).
 *
 * If `dest` is not `NULL`, then the encoded key is written at that
 * address, and the encoded length (in bytes) is returned. If `dest` is
 * `NULL`, then nothing is written, but the encoded length is still
 * computed and returned.
 *
 * If the key cannot be encoded (e.g. because there is no known OBJECT
 * IDENTIFIER for the used curve), then 0 is returned.
 *
 * \param dest   the destination buffer (or `NULL`).
 * \param sk     the EC private key.
 * \param pk     the EC public key (or `NULL`).
 * \return  the encoded key length (in bytes), or 0.
 */
size_t br_encode_ec_pkcs8_der(void *dest,
	const br_ec_private_key *sk, const br_ec_public_key *pk);

/**
 * \brief PEM banner for RSA private key (raw).
 */
#define BR_ENCODE_PEM_RSA_RAW      "RSA PRIVATE KEY"

/**
 * \brief PEM banner for EC private key (raw).
 */
#define BR_ENCODE_PEM_EC_RAW       "EC PRIVATE KEY"

/**
 * \brief PEM banner for an RSA or EC private key in PKCS#8 format.
 */
#define BR_ENCODE_PEM_PKCS8        "PRIVATE KEY"

#ifdef __cplusplus
}
#endif

#endif


#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_ssl.h
 *
 * # SSL
 *
 * For an overview of the SSL/TLS API, see [the BearSSL Web
 * site](https://www.bearssl.org/api1.html).
 *
 * The `BR_TLS_*` constants correspond to the standard cipher suites and
 * their values in the [IANA
 * registry](http://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-4).
 *
 * The `BR_ALERT_*` constants are for standard TLS alert messages. When
 * a fatal alert message is sent of received, then the SSL engine context
 * status is set to the sum of that alert value (an integer in the 0..255
 * range) and a fixed offset (`BR_ERR_SEND_FATAL_ALERT` for a sent alert,
 * `BR_ERR_RECV_FATAL_ALERT` for a received alert).
 */

/** \brief Optimal input buffer size. */
#define BR_SSL_BUFSIZE_INPUT    (16384 + 325)

/** \brief Optimal output buffer size. */
#define BR_SSL_BUFSIZE_OUTPUT   (16384 + 85)

/** \brief Optimal buffer size for monodirectional engine
    (shared input/output buffer). */
#define BR_SSL_BUFSIZE_MONO     BR_SSL_BUFSIZE_INPUT

/** \brief Optimal buffer size for bidirectional engine
    (single buffer split into two separate input/output buffers). */
#define BR_SSL_BUFSIZE_BIDI     (BR_SSL_BUFSIZE_INPUT + BR_SSL_BUFSIZE_OUTPUT)

/*
 * Constants for known SSL/TLS protocol versions (SSL 3.0, TLS 1.0, TLS 1.1
 * and TLS 1.2). Note that though there is a constant for SSL 3.0, that
 * protocol version is not actually supported.
 */

/** \brief Protocol version: SSL 3.0 (unsupported). */
#define BR_SSL30   0x0300
/** \brief Protocol version: TLS 1.0. */
#define BR_TLS10   0x0301
/** \brief Protocol version: TLS 1.1. */
#define BR_TLS11   0x0302
/** \brief Protocol version: TLS 1.2. */
#define BR_TLS12   0x0303

/*
 * Error constants. They are used to report the reason why a context has
 * been marked as failed.
 *
 * Implementation note: SSL-level error codes should be in the 1..31
 * range. The 32..63 range is for certificate decoding and validation
 * errors. Received fatal alerts imply an error code in the 256..511 range.
 */

/** \brief SSL status: no error so far (0). */
#define BR_ERR_OK                      0

/** \brief SSL status: caller-provided parameter is incorrect. */
#define BR_ERR_BAD_PARAM               1

/** \brief SSL status: operation requested by the caller cannot be applied
    with the current context state (e.g. reading data while outgoing data
    is waiting to be sent). */
#define BR_ERR_BAD_STATE               2

/** \brief SSL status: incoming protocol or record version is unsupported. */
#define BR_ERR_UNSUPPORTED_VERSION     3

/** \brief SSL status: incoming record version does not match the expected
    version. */
#define BR_ERR_BAD_VERSION             4

/** \brief SSL status: incoming record length is invalid. */
#define BR_ERR_BAD_LENGTH              5

/** \brief SSL status: incoming record is too large to be processed, or
    buffer is too small for the handshake message to send. */
#define BR_ERR_TOO_LARGE               6

/** \brief SSL status: decryption found an invalid padding, or the record
    MAC is not correct. */
#define BR_ERR_BAD_MAC                 7

/** \brief SSL status: no initial entropy was provided, and none can be
    obtained from the OS. */
#define BR_ERR_NO_RANDOM               8

/** \brief SSL status: incoming record type is unknown. */
#define BR_ERR_UNKNOWN_TYPE            9

/** \brief SSL status: incoming record or message has wrong type with
    regards to the current engine state. */
#define BR_ERR_UNEXPECTED             10

/** \brief SSL status: ChangeCipherSpec message from the peer has invalid
    contents. */
#define BR_ERR_BAD_CCS                12

/** \brief SSL status: alert message from the peer has invalid contents
    (odd length). */
#define BR_ERR_BAD_ALERT              13

/** \brief SSL status: incoming handshake message decoding failed. */
#define BR_ERR_BAD_HANDSHAKE          14

/** \brief SSL status: ServerHello contains a session ID which is larger
    than 32 bytes. */
#define BR_ERR_OVERSIZED_ID           15

/** \brief SSL status: server wants to use a cipher suite that we did
    not claim to support. This is also reported if we tried to advertise
    a cipher suite that we do not support. */
#define BR_ERR_BAD_CIPHER_SUITE       16

/** \brief SSL status: server wants to use a compression that we did not
    claim to support. */
#define BR_ERR_BAD_COMPRESSION        17

/** \brief SSL status: server's max fragment length does not match
    client's. */
#define BR_ERR_BAD_FRAGLEN            18

/** \brief SSL status: secure renegotiation failed. */
#define BR_ERR_BAD_SECRENEG           19

/** \brief SSL status: server sent an extension type that we did not
    announce, or used the same extension type several times in a single
    ServerHello. */
#define BR_ERR_EXTRA_EXTENSION        20

/** \brief SSL status: invalid Server Name Indication contents (when
    used by the server, this extension shall be empty). */
#define BR_ERR_BAD_SNI                21

/** \brief SSL status: invalid ServerHelloDone from the server (length
    is not 0). */
#define BR_ERR_BAD_HELLO_DONE         22

/** \brief SSL status: internal limit exceeded (e.g. server's public key
    is too large). */
#define BR_ERR_LIMIT_EXCEEDED         23

/** \brief SSL status: Finished message from peer does not match the
    expected value. */
#define BR_ERR_BAD_FINISHED           24

/** \brief SSL status: session resumption attempt with distinct version
    or cipher suite. */
#define BR_ERR_RESUME_MISMATCH        25

/** \brief SSL status: unsupported or invalid algorithm (ECDHE curve,
    signature algorithm, hash function). */
#define BR_ERR_INVALID_ALGORITHM      26

/** \brief SSL status: invalid signature (on ServerKeyExchange from
    server, or in CertificateVerify from client). */
#define BR_ERR_BAD_SIGNATURE          27

/** \brief SSL status: peer's public key does not have the proper type
    or is not allowed for requested operation. */
#define BR_ERR_WRONG_KEY_USAGE        28

/** \brief SSL status: client did not send a certificate upon request,
    or the client certificate could not be validated. */
#define BR_ERR_NO_CLIENT_AUTH         29

/** \brief SSL status: I/O error or premature close on underlying
    transport stream. This error code is set only by the simplified
    I/O API ("br_sslio_*"). */
#define BR_ERR_IO                     31

/** \brief SSL status: base value for a received fatal alert.

    When a fatal alert is received from the peer, the alert value
    is added to this constant. */
#define BR_ERR_RECV_FATAL_ALERT      256

/** \brief SSL status: base value for a sent fatal alert.

    When a fatal alert is sent to the peer, the alert value is added
    to this constant. */
#define BR_ERR_SEND_FATAL_ALERT      512

/* ===================================================================== */

/**
 * \brief Decryption engine for SSL.
 *
 * When processing incoming records, the SSL engine will use a decryption
 * engine that uses a specific context structure, and has a set of
 * methods (a vtable) that follows this template.
 *
 * The decryption engine is responsible for applying decryption, verifying
 * MAC, and keeping track of the record sequence number.
 */
typedef struct br_sslrec_in_class_ br_sslrec_in_class;
struct br_sslrec_in_class_ {
	/**
	 * \brief Context size (in bytes).
	 */
	size_t context_size;

	/**
	 * \brief Test validity of the incoming record length.
	 *
	 * This function returns 1 if the announced length for an
	 * incoming record is valid, 0 otherwise,
	 *
	 * \param ctx          decryption engine context.
	 * \param record_len   incoming record length.
	 * \return  1 of a valid length, 0 otherwise.
	 */
	int (*check_length)(const br_sslrec_in_class *const *ctx,
		size_t record_len);

	/**
	 * \brief Decrypt the incoming record.
	 *
	 * This function may assume that the record length is valid
	 * (it has been previously tested with `check_length()`).
	 * Decryption is done in place; `*len` is updated with the
	 * cleartext length, and the address of the first plaintext
	 * byte is returned. If the record is correct but empty, then
	 * `*len` is set to 0 and a non-`NULL` pointer is returned.
	 *
	 * On decryption/MAC error, `NULL` is returned.
	 *
	 * \param ctx           decryption engine context.
	 * \param record_type   record type (23 for application data, etc).
	 * \param version       record version.
	 * \param payload       address of encrypted payload.
	 * \param len           pointer to payload length (updated).
	 * \return  pointer to plaintext, or `NULL` on error.
	 */
	unsigned char *(*decrypt)(const br_sslrec_in_class **ctx,
		int record_type, unsigned version,
		void *payload, size_t *len);
};

/**
 * \brief Encryption engine for SSL.
 *
 * When building outgoing records, the SSL engine will use an encryption
 * engine that uses a specific context structure, and has a set of
 * methods (a vtable) that follows this template.
 *
 * The encryption engine is responsible for applying encryption and MAC,
 * and keeping track of the record sequence number.
 */
typedef struct br_sslrec_out_class_ br_sslrec_out_class;
struct br_sslrec_out_class_ {
	/**
	 * \brief Context size (in bytes).
	 */
	size_t context_size;

	/**
	 * \brief Compute maximum plaintext sizes and offsets.
	 *
	 * When this function is called, the `*start` and `*end`
	 * values contain offsets designating the free area in the
	 * outgoing buffer for plaintext data; that free area is
	 * preceded by a 5-byte space which will receive the record
	 * header.
	 *
	 * The `max_plaintext()` function is responsible for adjusting
	 * both `*start` and `*end` to make room for any record-specific
	 * header, MAC, padding, and possible split.
	 *
	 * \param ctx     encryption engine context.
	 * \param start   pointer to start of plaintext offset (updated).
	 * \param end     pointer to start of plaintext offset (updated).
	 */
	void (*max_plaintext)(const br_sslrec_out_class *const *ctx,
		size_t *start, size_t *end);

	/**
	 * \brief Perform record encryption.
	 *
	 * This function encrypts the record. The plaintext address and
	 * length are provided. Returned value is the start of the
	 * encrypted record (or sequence of records, if a split was
	 * performed), _including_ the 5-byte header, and `*len` is
	 * adjusted to the total size of the record(s), there again
	 * including the header(s).
	 *
	 * \param ctx           decryption engine context.
	 * \param record_type   record type (23 for application data, etc).
	 * \param version       record version.
	 * \param plaintext     address of plaintext.
	 * \param len           pointer to plaintext length (updated).
	 * \return  pointer to start of built record.
	 */
	unsigned char *(*encrypt)(const br_sslrec_out_class **ctx,
		int record_type, unsigned version,
		void *plaintext, size_t *len);
};

/**
 * \brief Context for a no-encryption engine.
 *
 * The no-encryption engine processes outgoing records during the initial
 * handshake, before encryption is applied.
 */
typedef struct {
	/** \brief No-encryption engine vtable. */
	const br_sslrec_out_class *vtable;
} br_sslrec_out_clear_context;

/** \brief Static, constant vtable for the no-encryption engine. */
extern const br_sslrec_out_class br_sslrec_out_clear_vtable;

/* ===================================================================== */

/**
 * \brief Record decryption engine class, for CBC mode.
 *
 * This class type extends the decryption engine class with an
 * initialisation method that receives the parameters needed
 * for CBC processing: block cipher implementation, block cipher key,
 * HMAC parameters (hash function, key, MAC length), and IV. If the
 * IV is `NULL`, then a per-record IV will be used (TLS 1.1+).
 */
typedef struct br_sslrec_in_cbc_class_ br_sslrec_in_cbc_class;
struct br_sslrec_in_cbc_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_in_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param bc_impl       block cipher implementation (CBC decryption).
	 * \param bc_key        block cipher key.
	 * \param bc_key_len    block cipher key length (in bytes).
	 * \param dig_impl      hash function for HMAC.
	 * \param mac_key       HMAC key.
	 * \param mac_key_len   HMAC key length (in bytes).
	 * \param mac_out_len   HMAC output length (in bytes).
	 * \param iv            initial IV (or `NULL`).
	 */
	void (*init)(const br_sslrec_in_cbc_class **ctx,
		const br_block_cbcdec_class *bc_impl,
		const void *bc_key, size_t bc_key_len,
		const br_hash_class *dig_impl,
		const void *mac_key, size_t mac_key_len, size_t mac_out_len,
		const void *iv);
};

/**
 * \brief Record encryption engine class, for CBC mode.
 *
 * This class type extends the encryption engine class with an
 * initialisation method that receives the parameters needed
 * for CBC processing: block cipher implementation, block cipher key,
 * HMAC parameters (hash function, key, MAC length), and IV. If the
 * IV is `NULL`, then a per-record IV will be used (TLS 1.1+).
 */
typedef struct br_sslrec_out_cbc_class_ br_sslrec_out_cbc_class;
struct br_sslrec_out_cbc_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_out_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param bc_impl       block cipher implementation (CBC encryption).
	 * \param bc_key        block cipher key.
	 * \param bc_key_len    block cipher key length (in bytes).
	 * \param dig_impl      hash function for HMAC.
	 * \param mac_key       HMAC key.
	 * \param mac_key_len   HMAC key length (in bytes).
	 * \param mac_out_len   HMAC output length (in bytes).
	 * \param iv            initial IV (or `NULL`).
	 */
	void (*init)(const br_sslrec_out_cbc_class **ctx,
		const br_block_cbcenc_class *bc_impl,
		const void *bc_key, size_t bc_key_len,
		const br_hash_class *dig_impl,
		const void *mac_key, size_t mac_key_len, size_t mac_out_len,
		const void *iv);
};

/**
 * \brief Context structure for decrypting incoming records with
 * CBC + HMAC.
 *
 * The first field points to the vtable. The other fields are opaque
 * and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	const br_sslrec_in_cbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t seq;
	union {
		const br_block_cbcdec_class *vtable;
		br_aes_gen_cbcdec_keys aes;
		br_des_gen_cbcdec_keys des;
	} bc;
	br_hmac_key_context mac;
	size_t mac_len;
	unsigned char iv[16];
	int explicit_IV;
#endif
} br_sslrec_in_cbc_context;

/**
 * \brief Static, constant vtable for record decryption with CBC.
 */
extern const br_sslrec_in_cbc_class br_sslrec_in_cbc_vtable;

/**
 * \brief Context structure for encrypting outgoing records with
 * CBC + HMAC.
 *
 * The first field points to the vtable. The other fields are opaque
 * and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	const br_sslrec_out_cbc_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t seq;
	union {
		const br_block_cbcenc_class *vtable;
		br_aes_gen_cbcenc_keys aes;
		br_des_gen_cbcenc_keys des;
	} bc;
	br_hmac_key_context mac;
	size_t mac_len;
	unsigned char iv[16];
	int explicit_IV;
#endif
} br_sslrec_out_cbc_context;

/**
 * \brief Static, constant vtable for record encryption with CBC.
 */
extern const br_sslrec_out_cbc_class br_sslrec_out_cbc_vtable;

/* ===================================================================== */

/**
 * \brief Record decryption engine class, for GCM mode.
 *
 * This class type extends the decryption engine class with an
 * initialisation method that receives the parameters needed
 * for GCM processing: block cipher implementation, block cipher key,
 * GHASH implementation, and 4-byte IV.
 */
typedef struct br_sslrec_in_gcm_class_ br_sslrec_in_gcm_class;
struct br_sslrec_in_gcm_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_in_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param bc_impl       block cipher implementation (CTR).
	 * \param key           block cipher key.
	 * \param key_len       block cipher key length (in bytes).
	 * \param gh_impl       GHASH implementation.
	 * \param iv            static IV (4 bytes).
	 */
	void (*init)(const br_sslrec_in_gcm_class **ctx,
		const br_block_ctr_class *bc_impl,
		const void *key, size_t key_len,
		br_ghash gh_impl,
		const void *iv);
};

/**
 * \brief Record encryption engine class, for GCM mode.
 *
 * This class type extends the encryption engine class with an
 * initialisation method that receives the parameters needed
 * for GCM processing: block cipher implementation, block cipher key,
 * GHASH implementation, and 4-byte IV.
 */
typedef struct br_sslrec_out_gcm_class_ br_sslrec_out_gcm_class;
struct br_sslrec_out_gcm_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_out_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param bc_impl       block cipher implementation (CTR).
	 * \param key           block cipher key.
	 * \param key_len       block cipher key length (in bytes).
	 * \param gh_impl       GHASH implementation.
	 * \param iv            static IV (4 bytes).
	 */
	void (*init)(const br_sslrec_out_gcm_class **ctx,
		const br_block_ctr_class *bc_impl,
		const void *key, size_t key_len,
		br_ghash gh_impl,
		const void *iv);
};

/**
 * \brief Context structure for processing records with GCM.
 *
 * The same context structure is used for encrypting and decrypting.
 *
 * The first field points to the vtable. The other fields are opaque
 * and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	union {
		const void *gen;
		const br_sslrec_in_gcm_class *in;
		const br_sslrec_out_gcm_class *out;
	} vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t seq;
	union {
		const br_block_ctr_class *vtable;
		br_aes_gen_ctr_keys aes;
	} bc;
	br_ghash gh;
	unsigned char iv[4];
	unsigned char h[16];
#endif
} br_sslrec_gcm_context;

/**
 * \brief Static, constant vtable for record decryption with GCM.
 */
extern const br_sslrec_in_gcm_class br_sslrec_in_gcm_vtable;

/**
 * \brief Static, constant vtable for record encryption with GCM.
 */
extern const br_sslrec_out_gcm_class br_sslrec_out_gcm_vtable;

/* ===================================================================== */

/**
 * \brief Record decryption engine class, for ChaCha20+Poly1305.
 *
 * This class type extends the decryption engine class with an
 * initialisation method that receives the parameters needed
 * for ChaCha20+Poly1305 processing: ChaCha20 implementation,
 * Poly1305 implementation, key, and 12-byte IV.
 */
typedef struct br_sslrec_in_chapol_class_ br_sslrec_in_chapol_class;
struct br_sslrec_in_chapol_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_in_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param ichacha       ChaCha20 implementation.
	 * \param ipoly         Poly1305 implementation.
	 * \param key           secret key (32 bytes).
	 * \param iv            static IV (12 bytes).
	 */
	void (*init)(const br_sslrec_in_chapol_class **ctx,
		br_chacha20_run ichacha,
		br_poly1305_run ipoly,
		const void *key, const void *iv);
};

/**
 * \brief Record encryption engine class, for ChaCha20+Poly1305.
 *
 * This class type extends the encryption engine class with an
 * initialisation method that receives the parameters needed
 * for ChaCha20+Poly1305 processing: ChaCha20 implementation,
 * Poly1305 implementation, key, and 12-byte IV.
 */
typedef struct br_sslrec_out_chapol_class_ br_sslrec_out_chapol_class;
struct br_sslrec_out_chapol_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_out_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param ichacha       ChaCha20 implementation.
	 * \param ipoly         Poly1305 implementation.
	 * \param key           secret key (32 bytes).
	 * \param iv            static IV (12 bytes).
	 */
	void (*init)(const br_sslrec_out_chapol_class **ctx,
		br_chacha20_run ichacha,
		br_poly1305_run ipoly,
		const void *key, const void *iv);
};

/**
 * \brief Context structure for processing records with ChaCha20+Poly1305.
 *
 * The same context structure is used for encrypting and decrypting.
 *
 * The first field points to the vtable. The other fields are opaque
 * and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	union {
		const void *gen;
		const br_sslrec_in_chapol_class *in;
		const br_sslrec_out_chapol_class *out;
	} vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t seq;
	unsigned char key[32];
	unsigned char iv[12];
	br_chacha20_run ichacha;
	br_poly1305_run ipoly;
#endif
} br_sslrec_chapol_context;

/**
 * \brief Static, constant vtable for record decryption with ChaCha20+Poly1305.
 */
extern const br_sslrec_in_chapol_class br_sslrec_in_chapol_vtable;

/**
 * \brief Static, constant vtable for record encryption with ChaCha20+Poly1305.
 */
extern const br_sslrec_out_chapol_class br_sslrec_out_chapol_vtable;

/* ===================================================================== */

/**
 * \brief Record decryption engine class, for CCM mode.
 *
 * This class type extends the decryption engine class with an
 * initialisation method that receives the parameters needed
 * for CCM processing: block cipher implementation, block cipher key,
 * and 4-byte IV.
 */
typedef struct br_sslrec_in_ccm_class_ br_sslrec_in_ccm_class;
struct br_sslrec_in_ccm_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_in_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param bc_impl       block cipher implementation (CTR+CBC).
	 * \param key           block cipher key.
	 * \param key_len       block cipher key length (in bytes).
	 * \param iv            static IV (4 bytes).
	 * \param tag_len       tag length (in bytes)
	 */
	void (*init)(const br_sslrec_in_ccm_class **ctx,
		const br_block_ctrcbc_class *bc_impl,
		const void *key, size_t key_len,
		const void *iv, size_t tag_len);
};

/**
 * \brief Record encryption engine class, for CCM mode.
 *
 * This class type extends the encryption engine class with an
 * initialisation method that receives the parameters needed
 * for CCM processing: block cipher implementation, block cipher key,
 * and 4-byte IV.
 */
typedef struct br_sslrec_out_ccm_class_ br_sslrec_out_ccm_class;
struct br_sslrec_out_ccm_class_ {
	/**
	 * \brief Superclass, as first vtable field.
	 */
	br_sslrec_out_class inner;

	/**
	 * \brief Engine initialisation method.
	 *
	 * This method sets the vtable field in the context.
	 *
	 * \param ctx           context to initialise.
	 * \param bc_impl       block cipher implementation (CTR+CBC).
	 * \param key           block cipher key.
	 * \param key_len       block cipher key length (in bytes).
	 * \param iv            static IV (4 bytes).
	 * \param tag_len       tag length (in bytes)
	 */
	void (*init)(const br_sslrec_out_ccm_class **ctx,
		const br_block_ctrcbc_class *bc_impl,
		const void *key, size_t key_len,
		const void *iv, size_t tag_len);
};

/**
 * \brief Context structure for processing records with CCM.
 *
 * The same context structure is used for encrypting and decrypting.
 *
 * The first field points to the vtable. The other fields are opaque
 * and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	union {
		const void *gen;
		const br_sslrec_in_ccm_class *in;
		const br_sslrec_out_ccm_class *out;
	} vtable;
#ifndef BR_DOXYGEN_IGNORE
	uint64_t seq;
	union {
		const br_block_ctrcbc_class *vtable;
		br_aes_gen_ctrcbc_keys aes;
	} bc;
	unsigned char iv[4];
	size_t tag_len;
#endif
} br_sslrec_ccm_context;

/**
 * \brief Static, constant vtable for record decryption with CCM.
 */
extern const br_sslrec_in_ccm_class br_sslrec_in_ccm_vtable;

/**
 * \brief Static, constant vtable for record encryption with CCM.
 */
extern const br_sslrec_out_ccm_class br_sslrec_out_ccm_vtable;

/* ===================================================================== */

/**
 * \brief Type for session parameters, to be saved for session resumption.
 */
typedef struct {
	/** \brief Session ID buffer. */
	unsigned char session_id[32];
	/** \brief Session ID length (in bytes, at most 32). */
	unsigned char session_id_len;
	/** \brief Protocol version. */
	uint16_t version;
	/** \brief Cipher suite. */
	uint16_t cipher_suite;
	/** \brief Master secret. */
	unsigned char master_secret[48];
} br_ssl_session_parameters;

#ifndef BR_DOXYGEN_IGNORE
/*
 * Maximum number of cipher suites supported by a client or server.
 */
#define BR_MAX_CIPHER_SUITES   48
#endif

/**
 * \brief Context structure for SSL engine.
 *
 * This strucuture is common to the client and server; both the client
 * context (`br_ssl_client_context`) and the server context
 * (`br_ssl_server_context`) include a `br_ssl_engine_context` as their
 * first field.
 *
 * The engine context manages records, including alerts, closures, and
 * transitions to new encryption/MAC algorithms. Processing of handshake
 * records is delegated to externally provided code. This structure
 * should not be used directly.
 *
 * Structure contents are opaque and shall not be accessed directly.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	/*
	 * The error code. When non-zero, then the state is "failed" and
	 * no I/O may occur until reset.
	 */
	int err;

	/*
	 * Configured I/O buffers. They are either disjoint, or identical.
	 */
	unsigned char *ibuf, *obuf;
	size_t ibuf_len, obuf_len;

	/*
	 * Maximum fragment length applies to outgoing records; incoming
	 * records can be processed as long as they fit in the input
	 * buffer. It is guaranteed that incoming records at least as big
	 * as max_frag_len can be processed.
	 */
	uint16_t max_frag_len;
	unsigned char log_max_frag_len;
	unsigned char peer_log_max_frag_len;

	/*
	 * Buffering management registers.
	 */
	size_t ixa, ixb, ixc;
	size_t oxa, oxb, oxc;
	unsigned char iomode;
	unsigned char incrypt;

	/*
	 * Shutdown flag: when set to non-zero, incoming record bytes
	 * will not be accepted anymore. This is used after a close_notify
	 * has been received: afterwards, the engine no longer claims that
	 * it could receive bytes from the transport medium.
	 */
	unsigned char shutdown_recv;

	/*
	 * 'record_type_in' is set to the incoming record type when the
	 * record header has been received.
	 * 'record_type_out' is used to make the next outgoing record
	 * header when it is ready to go.
	 */
	unsigned char record_type_in, record_type_out;

	/*
	 * When a record is received, its version is extracted:
	 * -- if 'version_in' is 0, then it is set to the received version;
	 * -- otherwise, if the received version is not identical to
	 *    the 'version_in' contents, then a failure is reported.
	 *
	 * This implements the SSL requirement that all records shall
	 * use the negotiated protocol version, once decided (in the
	 * ServerHello). It is up to the handshake handler to adjust this
	 * field when necessary.
	 */
	uint16_t version_in;

	/*
	 * 'version_out' is used when the next outgoing record is ready
	 * to go.
	 */
	uint16_t version_out;

	/*
	 * Record handler contexts.
	 */
	union {
		const br_sslrec_in_class *vtable;
		br_sslrec_in_cbc_context cbc;
		br_sslrec_gcm_context gcm;
		br_sslrec_chapol_context chapol;
		br_sslrec_ccm_context ccm;
	} in;
	union {
		const br_sslrec_out_class *vtable;
		br_sslrec_out_clear_context clear;
		br_sslrec_out_cbc_context cbc;
		br_sslrec_gcm_context gcm;
		br_sslrec_chapol_context chapol;
		br_sslrec_ccm_context ccm;
	} out;

	/*
	 * The "application data" flag. Value:
	 *   0   handshake is in process, no application data acceptable
	 *   1   application data can be sent and received
	 *   2   closing, no application data can be sent, but some
	 *       can still be received (and discarded)
	 */
	unsigned char application_data;

	/*
	 * Context RNG.
	 *
	 *   rng_init_done is initially 0. It is set to 1 when the
	 *   basic structure of the RNG is set, and 2 when some
	 *   entropy has been pushed in. The value 2 marks the RNG
	 *   as "properly seeded".
	 *
	 *   rng_os_rand_done is initially 0. It is set to 1 when
	 *   some seeding from the OS or hardware has been attempted.
	 */
	br_hmac_drbg_context rng;
	int rng_init_done;
	int rng_os_rand_done;

	/*
	 * Supported minimum and maximum versions, and cipher suites.
	 */
	uint16_t version_min;
	uint16_t version_max;
	uint16_t suites_buf[BR_MAX_CIPHER_SUITES];
	unsigned char suites_num;

	/*
	 * For clients, the server name to send as a SNI extension. For
	 * servers, the name received in the SNI extension (if any).
	 */
	char server_name[256];

	/*
	 * "Security parameters". These are filled by the handshake
	 * handler, and used when switching encryption state.
	 */
	unsigned char client_random[32];
	unsigned char server_random[32];
	br_ssl_session_parameters session;

	/*
	 * ECDHE elements: curve and point from the peer. The server also
	 * uses that buffer for the point to send to the client.
	 */
	unsigned char ecdhe_curve;
	unsigned char ecdhe_point[133];
	unsigned char ecdhe_point_len;

	/*
	 * Secure renegotiation (RFC 5746): 'reneg' can be:
	 *   0   first handshake (server support is not known)
	 *   1   peer does not support secure renegotiation
	 *   2   peer supports secure renegotiation
	 *
	 * The saved_finished buffer contains the client and the
	 * server "Finished" values from the last handshake, in
	 * that order (12 bytes each).
	 */
	unsigned char reneg;
	unsigned char saved_finished[24];

	/*
	 * Behavioural flags.
	 */
	uint32_t flags;

	/*
	 * Context variables for the handshake processor. The 'pad' must
	 * be large enough to accommodate an RSA-encrypted pre-master
	 * secret, or an RSA signature; since we want to support up to
	 * RSA-4096, this means at least 512 bytes. (Other pad usages
	 * require its length to be at least 256.)
	 */
	struct {
		uint32_t *dp;
		uint32_t *rp;
		const unsigned char *ip;
	} cpu;
	uint32_t dp_stack[32];
	uint32_t rp_stack[32];
	unsigned char pad[512];
	unsigned char *hbuf_in, *hbuf_out, *saved_hbuf_out;
	size_t hlen_in, hlen_out;
	void (*hsrun)(void *ctx);

	/*
	 * The 'action' value communicates OOB information between the
	 * engine and the handshake processor.
	 *
	 * From the engine:
	 *   0  invocation triggered by I/O
	 *   1  invocation triggered by explicit close
	 *   2  invocation triggered by explicit renegotiation
	 */
	unsigned char action;

	/*
	 * State for alert messages. Value is either 0, or the value of
	 * the alert level byte (level is either 1 for warning, or 2 for
	 * fatal; we convert all other values to 'fatal').
	 */
	unsigned char alert;

	/*
	 * Closure flags. This flag is set when a close_notify has been
	 * received from the peer.
	 */
	unsigned char close_received;

	/*
	 * Multi-hasher for the handshake messages. The handshake handler
	 * is responsible for resetting it when appropriate.
	 */
	br_multihash_context mhash;

	/*
	 * Pointer to the X.509 engine. The engine is supposed to be
	 * already initialized. It is used to validate the peer's
	 * certificate.
	 */
	const br_x509_class **x509ctx;

	/*
	 * Certificate chain to send. This is used by both client and
	 * server, when they send their respective Certificate messages.
	 * If chain_len is 0, then chain may be NULL.
	 */
	const br_x509_certificate *chain;
	size_t chain_len;
	const unsigned char *cert_cur;
	size_t cert_len;

	/*
	 * List of supported protocol names (ALPN extension). If unset,
	 * (number of names is 0), then:
	 *  - the client sends no ALPN extension;
	 *  - the server ignores any incoming ALPN extension.
	 *
	 * Otherwise:
	 *  - the client sends an ALPN extension with all the names;
	 *  - the server selects the first protocol in its list that
	 *    the client also supports, or fails (fatal alert 120)
	 *    if the client sends an ALPN extension and there is no
	 *    match.
	 *
	 * The 'selected_protocol' field contains 1+n if the matching
	 * name has index n in the list (the value is 0 if no match was
	 * performed, e.g. the peer did not send an ALPN extension).
	 */
	const char **protocol_names;
	uint16_t protocol_names_num;
	uint16_t selected_protocol;

	/*
	 * Pointers to implementations; left to NULL for unsupported
	 * functions. For the raw hash functions, implementations are
	 * referenced from the multihasher (mhash field).
	 */
	br_tls_prf_impl prf10;
	br_tls_prf_impl prf_sha256;
	br_tls_prf_impl prf_sha384;
	const br_block_cbcenc_class *iaes_cbcenc;
	const br_block_cbcdec_class *iaes_cbcdec;
	const br_block_ctr_class *iaes_ctr;
	const br_block_ctrcbc_class *iaes_ctrcbc;
	const br_block_cbcenc_class *ides_cbcenc;
	const br_block_cbcdec_class *ides_cbcdec;
	br_ghash ighash;
	br_chacha20_run ichacha;
	br_poly1305_run ipoly;
	const br_sslrec_in_cbc_class *icbc_in;
	const br_sslrec_out_cbc_class *icbc_out;
	const br_sslrec_in_gcm_class *igcm_in;
	const br_sslrec_out_gcm_class *igcm_out;
	const br_sslrec_in_chapol_class *ichapol_in;
	const br_sslrec_out_chapol_class *ichapol_out;
	const br_sslrec_in_ccm_class *iccm_in;
	const br_sslrec_out_ccm_class *iccm_out;
	const br_ec_impl *iec;
	br_rsa_pkcs1_vrfy irsavrfy;
	br_ecdsa_vrfy iecdsa;
#endif
} br_ssl_engine_context;

/**
 * \brief Get currently defined engine behavioural flags.
 *
 * \param cc   SSL engine context.
 * \return  the flags.
 */
static inline uint32_t
br_ssl_engine_get_flags(br_ssl_engine_context *cc)
{
	return cc->flags;
}

/**
 * \brief Set all engine behavioural flags.
 *
 * \param cc      SSL engine context.
 * \param flags   new value for all flags.
 */
static inline void
br_ssl_engine_set_all_flags(br_ssl_engine_context *cc, uint32_t flags)
{
	cc->flags = flags;
}

/**
 * \brief Set some engine behavioural flags.
 *
 * The flags set in the `flags` parameter are set in the context; other
 * flags are untouched.
 *
 * \param cc      SSL engine context.
 * \param flags   additional set flags.
 */
static inline void
br_ssl_engine_add_flags(br_ssl_engine_context *cc, uint32_t flags)
{
	cc->flags |= flags;
}

/**
 * \brief Clear some engine behavioural flags.
 *
 * The flags set in the `flags` parameter are cleared from the context; other
 * flags are untouched.
 *
 * \param cc      SSL engine context.
 * \param flags   flags to remove.
 */
static inline void
br_ssl_engine_remove_flags(br_ssl_engine_context *cc, uint32_t flags)
{
	cc->flags &= ~flags;
}

/**
 * \brief Behavioural flag: enforce server preferences.
 *
 * If this flag is set, then the server will enforce its own cipher suite
 * preference order; otherwise, it follows the client preferences.
 */
#define BR_OPT_ENFORCE_SERVER_PREFERENCES      ((uint32_t)1 << 0)

/**
 * \brief Behavioural flag: disable renegotiation.
 *
 * If this flag is set, then renegotiations are rejected unconditionally:
 * they won't be honoured if asked for programmatically, and requests from
 * the peer are rejected.
 */
#define BR_OPT_NO_RENEGOTIATION                ((uint32_t)1 << 1)

/**
 * \brief Behavioural flag: tolerate lack of client authentication.
 *
 * If this flag is set in a server and the server requests a client
 * certificate, but the authentication fails (the client does not send
 * a certificate, or the client's certificate chain cannot be validated),
 * then the connection keeps on. Without this flag, a failed client
 * authentication terminates the connection.
 *
 * Notes:
 *
 *   - If the client's certificate can be validated and its public key is
 *     supported, then a wrong signature value terminates the connection
 *     regardless of that flag.
 *
 *   - If using full-static ECDH, then a failure to validate the client's
 *     certificate prevents the handshake from succeeding.
 */
#define BR_OPT_TOLERATE_NO_CLIENT_AUTH         ((uint32_t)1 << 2)

/**
 * \brief Behavioural flag: fail on application protocol mismatch.
 *
 * The ALPN extension ([RFC 7301](https://tools.ietf.org/html/rfc7301))
 * allows the client to send a list of application protocol names, and
 * the server to select one. A mismatch is one of the following occurrences:
 *
 *   - On the client: the client sends a list of names, the server
 *     responds with a protocol name which is _not_ part of the list of
 *     names sent by the client.
 *
 *   - On the server: the client sends a list of names, and the server
 *     is also configured with a list of names, but there is no common
 *     protocol name between the two lists.
 *
 * Normal behaviour in case of mismatch is to report no matching name
 * (`br_ssl_engine_get_selected_protocol()` returns `NULL`) and carry on.
 * If the flag is set, then a mismatch implies a protocol failure (if
 * the mismatch is detected by the server, it will send a fatal alert).
 *
 * Note: even with this flag, `br_ssl_engine_get_selected_protocol()`
 * may still return `NULL` if the client or the server does not send an
 * ALPN extension at all.
 */
#define BR_OPT_FAIL_ON_ALPN_MISMATCH           ((uint32_t)1 << 3)

/**
 * \brief Set the minimum and maximum supported protocol versions.
 *
 * The two provided versions MUST be supported by the implementation
 * (i.e. TLS 1.0, 1.1 and 1.2), and `version_max` MUST NOT be lower
 * than `version_min`.
 *
 * \param cc            SSL engine context.
 * \param version_min   minimum supported TLS version.
 * \param version_max   maximum supported TLS version.
 */
static inline void
br_ssl_engine_set_versions(br_ssl_engine_context *cc,
	unsigned version_min, unsigned version_max)
{
	cc->version_min = (uint16_t)version_min;
	cc->version_max = (uint16_t)version_max;
}

/**
 * \brief Set the list of cipher suites advertised by this context.
 *
 * The provided array is copied into the context. It is the caller
 * responsibility to ensure that all provided suites will be supported
 * by the context. The engine context has enough room to receive _all_
 * suites supported by the implementation. The provided array MUST NOT
 * contain duplicates.
 *
 * If the engine is for a client, the "signaling" pseudo-cipher suite
 * `TLS_FALLBACK_SCSV` can be added at the end of the list, if the
 * calling application is performing a voluntary downgrade (voluntary
 * downgrades are not recommended, but if such a downgrade is done, then
 * adding the fallback pseudo-suite is a good idea).
 *
 * \param cc           SSL engine context.
 * \param suites       cipher suites.
 * \param suites_num   number of cipher suites.
 */
void br_ssl_engine_set_suites(br_ssl_engine_context *cc,
	const uint16_t *suites, size_t suites_num);

/**
 * \brief Set the X.509 engine.
 *
 * The caller shall ensure that the X.509 engine is properly initialised.
 *
 * \param cc        SSL engine context.
 * \param x509ctx   X.509 certificate validation context.
 */
static inline void
br_ssl_engine_set_x509(br_ssl_engine_context *cc, const br_x509_class **x509ctx)
{
	cc->x509ctx = x509ctx;
}

/**
 * \brief Set the supported protocol names.
 *
 * Protocol names are part of the ALPN extension ([RFC
 * 7301](https://tools.ietf.org/html/rfc7301)). Each protocol name is a
 * character string, containing no more than 255 characters (256 with the
 * terminating zero). When names are set, then:
 *
 *   - The client will send an ALPN extension, containing the names. If
 *     the server responds with an ALPN extension, the client will verify
 *     that the response contains one of its name, and report that name
 *     through `br_ssl_engine_get_selected_protocol()`.
 *
 *   - The server will parse incoming ALPN extension (from clients), and
 *     try to find a common protocol; if none is found, the connection
 *     is aborted with a fatal alert. On match, a response ALPN extension
 *     is sent, and name is reported through
 *     `br_ssl_engine_get_selected_protocol()`.
 *
 * The provided array is linked in, and must remain valid while the
 * connection is live.
 *
 * Names MUST NOT be empty. Names MUST NOT be longer than 255 characters
 * (excluding the terminating 0).
 *
 * \param ctx     SSL engine context.
 * \param names   list of protocol names (zero-terminated).
 * \param num     number of protocol names (MUST be 1 or more).
 */
static inline void
br_ssl_engine_set_protocol_names(br_ssl_engine_context *ctx,
	const char **names, size_t num)
{
	ctx->protocol_names = names;
	ctx->protocol_names_num = (uint16_t)num;
}

/**
 * \brief Get the selected protocol.
 *
 * If this context was initialised with a non-empty list of protocol
 * names, and both client and server sent ALPN extensions during the
 * handshake, and a common name was found, then that name is returned.
 * Otherwise, `NULL` is returned.
 *
 * The returned pointer is one of the pointers provided to the context
 * with `br_ssl_engine_set_protocol_names()`.
 *
 * \return  the selected protocol, or `NULL`.
 */
static inline const char *
br_ssl_engine_get_selected_protocol(br_ssl_engine_context *ctx)
{
	unsigned k;

	k = ctx->selected_protocol;
	return (k == 0 || k == 0xFFFF) ? NULL : ctx->protocol_names[k - 1];
}

/**
 * \brief Set a hash function implementation (by ID).
 *
 * Hash functions set with this call will be used for SSL/TLS specific
 * usages, not X.509 certificate validation. Only "standard" hash functions
 * may be set (MD5, SHA-1, SHA-224, SHA-256, SHA-384, SHA-512). If `impl`
 * is `NULL`, then the hash function support is removed, not added.
 *
 * \param ctx    SSL engine context.
 * \param id     hash function identifier.
 * \param impl   hash function implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_hash(br_ssl_engine_context *ctx,
	int id, const br_hash_class *impl)
{
	br_multihash_setimpl(&ctx->mhash, id, impl);
}

/**
 * \brief Get a hash function implementation (by ID).
 *
 * This function retrieves a hash function implementation which was
 * set with `br_ssl_engine_set_hash()`.
 *
 * \param ctx   SSL engine context.
 * \param id    hash function identifier.
 * \return  the hash function implementation (or `NULL`).
 */
static inline const br_hash_class *
br_ssl_engine_get_hash(br_ssl_engine_context *ctx, int id)
{
	return br_multihash_getimpl(&ctx->mhash, id);
}

/**
 * \brief Set the PRF implementation (for TLS 1.0 and 1.1).
 *
 * This function sets (or removes, if `impl` is `NULL`) the implementation
 * for the PRF used in TLS 1.0 and 1.1.
 *
 * \param cc     SSL engine context.
 * \param impl   PRF implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_prf10(br_ssl_engine_context *cc, br_tls_prf_impl impl)
{
	cc->prf10 = impl;
}

/**
 * \brief Set the PRF implementation with SHA-256 (for TLS 1.2).
 *
 * This function sets (or removes, if `impl` is `NULL`) the implementation
 * for the SHA-256 variant of the PRF used in TLS 1.2.
 *
 * \param cc     SSL engine context.
 * \param impl   PRF implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_prf_sha256(br_ssl_engine_context *cc, br_tls_prf_impl impl)
{
	cc->prf_sha256 = impl;
}

/**
 * \brief Set the PRF implementation with SHA-384 (for TLS 1.2).
 *
 * This function sets (or removes, if `impl` is `NULL`) the implementation
 * for the SHA-384 variant of the PRF used in TLS 1.2.
 *
 * \param cc     SSL engine context.
 * \param impl   PRF implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_prf_sha384(br_ssl_engine_context *cc, br_tls_prf_impl impl)
{
	cc->prf_sha384 = impl;
}

/**
 * \brief Set the AES/CBC implementations.
 *
 * \param cc         SSL engine context.
 * \param impl_enc   AES/CBC encryption implementation (or `NULL`).
 * \param impl_dec   AES/CBC decryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_aes_cbc(br_ssl_engine_context *cc,
	const br_block_cbcenc_class *impl_enc,
	const br_block_cbcdec_class *impl_dec)
{
	cc->iaes_cbcenc = impl_enc;
	cc->iaes_cbcdec = impl_dec;
}

/**
 * \brief Set the "default" AES/CBC implementations.
 *
 * This function configures in the engine the AES implementations that
 * should provide best runtime performance on the local system, while
 * still being safe (in particular, constant-time). It also sets the
 * handlers for CBC records.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_aes_cbc(br_ssl_engine_context *cc);

/**
 * \brief Set the AES/CTR implementation.
 *
 * \param cc     SSL engine context.
 * \param impl   AES/CTR encryption/decryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_aes_ctr(br_ssl_engine_context *cc,
	const br_block_ctr_class *impl)
{
	cc->iaes_ctr = impl;
}

/**
 * \brief Set the "default" implementations for AES/GCM (AES/CTR + GHASH).
 *
 * This function configures in the engine the AES/CTR and GHASH
 * implementation that should provide best runtime performance on the local
 * system, while still being safe (in particular, constant-time). It also
 * sets the handlers for GCM records.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_aes_gcm(br_ssl_engine_context *cc);

/**
 * \brief Set the DES/CBC implementations.
 *
 * \param cc         SSL engine context.
 * \param impl_enc   DES/CBC encryption implementation (or `NULL`).
 * \param impl_dec   DES/CBC decryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_des_cbc(br_ssl_engine_context *cc,
	const br_block_cbcenc_class *impl_enc,
	const br_block_cbcdec_class *impl_dec)
{
	cc->ides_cbcenc = impl_enc;
	cc->ides_cbcdec = impl_dec;
}

/**
 * \brief Set the "default" DES/CBC implementations.
 *
 * This function configures in the engine the DES implementations that
 * should provide best runtime performance on the local system, while
 * still being safe (in particular, constant-time). It also sets the
 * handlers for CBC records.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_des_cbc(br_ssl_engine_context *cc);

/**
 * \brief Set the GHASH implementation (used in GCM mode).
 *
 * \param cc     SSL engine context.
 * \param impl   GHASH implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_ghash(br_ssl_engine_context *cc, br_ghash impl)
{
	cc->ighash = impl;
}

/**
 * \brief Set the ChaCha20 implementation.
 *
 * \param cc        SSL engine context.
 * \param ichacha   ChaCha20 implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_chacha20(br_ssl_engine_context *cc,
	br_chacha20_run ichacha)
{
	cc->ichacha = ichacha;
}

/**
 * \brief Set the Poly1305 implementation.
 *
 * \param cc      SSL engine context.
 * \param ipoly   Poly1305 implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_poly1305(br_ssl_engine_context *cc,
	br_poly1305_run ipoly)
{
	cc->ipoly = ipoly;
}

/**
 * \brief Set the "default" ChaCha20 and Poly1305 implementations.
 *
 * This function configures in the engine the ChaCha20 and Poly1305
 * implementations that should provide best runtime performance on the
 * local system, while still being safe (in particular, constant-time).
 * It also sets the handlers for ChaCha20+Poly1305 records.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_chapol(br_ssl_engine_context *cc);

/**
 * \brief Set the AES/CTR+CBC implementation.
 *
 * \param cc     SSL engine context.
 * \param impl   AES/CTR+CBC encryption/decryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_aes_ctrcbc(br_ssl_engine_context *cc,
	const br_block_ctrcbc_class *impl)
{
	cc->iaes_ctrcbc = impl;
}

/**
 * \brief Set the "default" implementations for AES/CCM.
 *
 * This function configures in the engine the AES/CTR+CBC
 * implementation that should provide best runtime performance on the local
 * system, while still being safe (in particular, constant-time). It also
 * sets the handlers for CCM records.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_aes_ccm(br_ssl_engine_context *cc);

/**
 * \brief Set the record encryption and decryption engines for CBC + HMAC.
 *
 * \param cc         SSL engine context.
 * \param impl_in    record CBC decryption implementation (or `NULL`).
 * \param impl_out   record CBC encryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_cbc(br_ssl_engine_context *cc,
	const br_sslrec_in_cbc_class *impl_in,
	const br_sslrec_out_cbc_class *impl_out)
{
	cc->icbc_in = impl_in;
	cc->icbc_out = impl_out;
}

/**
 * \brief Set the record encryption and decryption engines for GCM.
 *
 * \param cc         SSL engine context.
 * \param impl_in    record GCM decryption implementation (or `NULL`).
 * \param impl_out   record GCM encryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_gcm(br_ssl_engine_context *cc,
	const br_sslrec_in_gcm_class *impl_in,
	const br_sslrec_out_gcm_class *impl_out)
{
	cc->igcm_in = impl_in;
	cc->igcm_out = impl_out;
}

/**
 * \brief Set the record encryption and decryption engines for CCM.
 *
 * \param cc         SSL engine context.
 * \param impl_in    record CCM decryption implementation (or `NULL`).
 * \param impl_out   record CCM encryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_ccm(br_ssl_engine_context *cc,
	const br_sslrec_in_ccm_class *impl_in,
	const br_sslrec_out_ccm_class *impl_out)
{
	cc->iccm_in = impl_in;
	cc->iccm_out = impl_out;
}

/**
 * \brief Set the record encryption and decryption engines for
 * ChaCha20+Poly1305.
 *
 * \param cc         SSL engine context.
 * \param impl_in    record ChaCha20 decryption implementation (or `NULL`).
 * \param impl_out   record ChaCha20 encryption implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_chapol(br_ssl_engine_context *cc,
	const br_sslrec_in_chapol_class *impl_in,
	const br_sslrec_out_chapol_class *impl_out)
{
	cc->ichapol_in = impl_in;
	cc->ichapol_out = impl_out;
}

/**
 * \brief Set the EC implementation.
 *
 * The elliptic curve implementation will be used for ECDH and ECDHE
 * cipher suites, and for ECDSA support.
 *
 * \param cc    SSL engine context.
 * \param iec   EC implementation (or `NULL`).
 */
static inline void
br_ssl_engine_set_ec(br_ssl_engine_context *cc, const br_ec_impl *iec)
{
	cc->iec = iec;
}

/**
 * \brief Set the "default" EC implementation.
 *
 * This function sets the elliptic curve implementation for ECDH and
 * ECDHE cipher suites, and for ECDSA support. It selects the fastest
 * implementation on the current system.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_ec(br_ssl_engine_context *cc);

/**
 * \brief Get the EC implementation configured in the provided engine.
 *
 * \param cc   SSL engine context.
 * \return  the EC implementation.
 */
static inline const br_ec_impl *
br_ssl_engine_get_ec(br_ssl_engine_context *cc)
{
	return cc->iec;
}

/**
 * \brief Set the RSA signature verification implementation.
 *
 * On the client, this is used to verify the server's signature on its
 * ServerKeyExchange message (for ECDHE_RSA cipher suites). On the server,
 * this is used to verify the client's CertificateVerify message (if a
 * client certificate is requested, and that certificate contains a RSA key).
 *
 * \param cc         SSL engine context.
 * \param irsavrfy   RSA signature verification implementation.
 */
static inline void
br_ssl_engine_set_rsavrfy(br_ssl_engine_context *cc, br_rsa_pkcs1_vrfy irsavrfy)
{
	cc->irsavrfy = irsavrfy;
}

/**
 * \brief Set the "default" RSA implementation (signature verification).
 *
 * This function sets the RSA implementation (signature verification)
 * to the fastest implementation available on the current platform.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_rsavrfy(br_ssl_engine_context *cc);

/**
 * \brief Get the RSA implementation (signature verification) configured
 * in the provided engine.
 *
 * \param cc   SSL engine context.
 * \return  the RSA signature verification implementation.
 */
static inline br_rsa_pkcs1_vrfy
br_ssl_engine_get_rsavrfy(br_ssl_engine_context *cc)
{
	return cc->irsavrfy;
}

/*
 * \brief Set the ECDSA implementation (signature verification).
 *
 * On the client, this is used to verify the server's signature on its
 * ServerKeyExchange message (for ECDHE_ECDSA cipher suites). On the server,
 * this is used to verify the client's CertificateVerify message (if a
 * client certificate is requested, that certificate contains an EC key,
 * and full-static ECDH is not used).
 *
 * The ECDSA implementation will use the EC core implementation configured
 * in the engine context.
 *
 * \param cc       client context.
 * \param iecdsa   ECDSA verification implementation.
 */
static inline void
br_ssl_engine_set_ecdsa(br_ssl_engine_context *cc, br_ecdsa_vrfy iecdsa)
{
	cc->iecdsa = iecdsa;
}

/**
 * \brief Set the "default" ECDSA implementation (signature verification).
 *
 * This function sets the ECDSA implementation (signature verification)
 * to the fastest implementation available on the current platform. This
 * call also sets the elliptic curve implementation itself, there again
 * to the fastest EC implementation available.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_set_default_ecdsa(br_ssl_engine_context *cc);

/**
 * \brief Get the ECDSA implementation (signature verification) configured
 * in the provided engine.
 *
 * \param cc   SSL engine context.
 * \return  the ECDSA signature verification implementation.
 */
static inline br_ecdsa_vrfy
br_ssl_engine_get_ecdsa(br_ssl_engine_context *cc)
{
	return cc->iecdsa;
}

/**
 * \brief Set the I/O buffer for the SSL engine.
 *
 * Once this call has been made, `br_ssl_client_reset()` or
 * `br_ssl_server_reset()` MUST be called before using the context.
 *
 * The provided buffer will be used as long as the engine context is
 * used. The caller is responsible for keeping it available.
 *
 * If `bidi` is 0, then the engine will operate in half-duplex mode
 * (it won't be able to send data while there is unprocessed incoming
 * data in the buffer, and it won't be able to receive data while there
 * is unsent data in the buffer). The optimal buffer size in half-duplex
 * mode is `BR_SSL_BUFSIZE_MONO`; if the buffer is larger, then extra
 * bytes are ignored. If the buffer is smaller, then this limits the
 * capacity of the engine to support all allowed record sizes.
 *
 * If `bidi` is 1, then the engine will split the buffer into two
 * parts, for separate handling of outgoing and incoming data. This
 * enables full-duplex processing, but requires more RAM. The optimal
 * buffer size in full-duplex mode is `BR_SSL_BUFSIZE_BIDI`; if the
 * buffer is larger, then extra bytes are ignored. If the buffer is
 * smaller, then the split will favour the incoming part, so that
 * interoperability is maximised.
 *
 * \param cc          SSL engine context
 * \param iobuf       I/O buffer.
 * \param iobuf_len   I/O buffer length (in bytes).
 * \param bidi        non-zero for full-duplex mode.
 */
void br_ssl_engine_set_buffer(br_ssl_engine_context *cc,
	void *iobuf, size_t iobuf_len, int bidi);

/**
 * \brief Set the I/O buffers for the SSL engine.
 *
 * Once this call has been made, `br_ssl_client_reset()` or
 * `br_ssl_server_reset()` MUST be called before using the context.
 *
 * This function is similar to `br_ssl_engine_set_buffer()`, except
 * that it enforces full-duplex mode, and the two I/O buffers are
 * provided as separate chunks.
 *
 * The macros `BR_SSL_BUFSIZE_INPUT` and `BR_SSL_BUFSIZE_OUTPUT`
 * evaluate to the optimal (maximum) sizes for the input and output
 * buffer, respectively.
 *
 * \param cc         SSL engine context
 * \param ibuf       input buffer.
 * \param ibuf_len   input buffer length (in bytes).
 * \param obuf       output buffer.
 * \param obuf_len   output buffer length (in bytes).
 */
void br_ssl_engine_set_buffers_bidi(br_ssl_engine_context *cc,
	void *ibuf, size_t ibuf_len, void *obuf, size_t obuf_len);

/**
 * \brief Inject some "initial entropy" in the context.
 *
 * This entropy will be added to what can be obtained from the
 * underlying operating system, if that OS is supported.
 *
 * This function may be called several times; all injected entropy chunks
 * are cumulatively mixed.
 *
 * If entropy gathering from the OS is supported and compiled in, then this
 * step is optional. Otherwise, it is mandatory to inject randomness, and
 * the caller MUST take care to push (as one or several successive calls)
 * enough entropy to achieve cryptographic resistance (at least 80 bits,
 * preferably 128 or more). The engine will report an error if no entropy
 * was provided and none can be obtained from the OS.
 *
 * Take care that this function cannot assess the cryptographic quality of
 * the provided bytes.
 *
 * In all generality, "entropy" must here be considered to mean "that
 * which the attacker cannot predict". If your OS/architecture does not
 * have a suitable source of randomness, then you can make do with the
 * combination of a large enough secret value (possibly a copy of an
 * asymmetric private key that you also store on the system) AND a
 * non-repeating value (e.g. current time, provided that the local clock
 * cannot be reset or altered by the attacker).
 *
 * \param cc     SSL engine context.
 * \param data   extra entropy to inject.
 * \param len    length of the extra data (in bytes).
 */
void br_ssl_engine_inject_entropy(br_ssl_engine_context *cc,
	const void *data, size_t len);

/**
 * \brief Get the "server name" in this engine.
 *
 * For clients, this is the name provided with `br_ssl_client_reset()`;
 * for servers, this is the name received from the client as part of the
 * ClientHello message. If there is no such name (e.g. the client did
 * not send an SNI extension) then the returned string is empty
 * (returned pointer points to a byte of value 0).
 *
 * The returned pointer refers to a buffer inside the context, which may
 * be overwritten as part of normal SSL activity (even within the same
 * connection, if a renegotiation occurs).
 *
 * \param cc   SSL engine context.
 * \return  the server name (possibly empty).
 */
static inline const char *
br_ssl_engine_get_server_name(const br_ssl_engine_context *cc)
{
	return cc->server_name;
}

/**
 * \brief Get the protocol version.
 *
 * This function returns the protocol version that is used by the
 * engine. That value is set after sending (for a server) or receiving
 * (for a client) the ServerHello message.
 *
 * \param cc   SSL engine context.
 * \return  the protocol version.
 */
static inline unsigned
br_ssl_engine_get_version(const br_ssl_engine_context *cc)
{
	return cc->session.version;
}

/**
 * \brief Get a copy of the session parameters.
 *
 * The session parameters are filled during the handshake, so this
 * function shall not be called before completion of the handshake.
 * The initial handshake is completed when the context first allows
 * application data to be injected.
 *
 * This function copies the current session parameters into the provided
 * structure. Beware that the session parameters include the master
 * secret, which is sensitive data, to handle with great care.
 *
 * \param cc   SSL engine context.
 * \param pp   destination structure for the session parameters.
 */
static inline void
br_ssl_engine_get_session_parameters(const br_ssl_engine_context *cc,
	br_ssl_session_parameters *pp)
{
	memcpy(pp, &cc->session, sizeof *pp);
}

/**
 * \brief Set the session parameters to the provided values.
 *
 * This function is meant to be used in the client, before doing a new
 * handshake; a session resumption will be attempted with these
 * parameters. In the server, this function has no effect.
 *
 * \param cc   SSL engine context.
 * \param pp   source structure for the session parameters.
 */
static inline void
br_ssl_engine_set_session_parameters(br_ssl_engine_context *cc,
	const br_ssl_session_parameters *pp)
{
	memcpy(&cc->session, pp, sizeof *pp);
}

/**
 * \brief Get identifier for the curve used for key exchange.
 *
 * If the cipher suite uses ECDHE, then this function returns the
 * identifier for the curve used for transient parameters. This is
 * defined during the course of the handshake, when the ServerKeyExchange
 * is sent (on the server) or received (on the client). If the
 * cipher suite does not use ECDHE (e.g. static ECDH, or RSA key
 * exchange), then this value is indeterminate.
 *
 * @param cc   SSL engine context.
 * @return  the ECDHE curve identifier.
 */
static inline int
br_ssl_engine_get_ecdhe_curve(br_ssl_engine_context *cc)
{
	return cc->ecdhe_curve;
}

/**
 * \brief Get the current engine state.
 *
 * An SSL engine (client or server) has, at any time, a state which is
 * the combination of zero, one or more of these flags:
 *
 *   - `BR_SSL_CLOSED`
 *
 *     Engine is finished, no more I/O (until next reset).
 *
 *   - `BR_SSL_SENDREC`
 *
 *     Engine has some bytes to send to the peer.
 *
 *   - `BR_SSL_RECVREC`
 *
 *     Engine expects some bytes from the peer.
 *
 *   - `BR_SSL_SENDAPP`
 *
 *     Engine may receive application data to send (or flush).
 *
 *   - `BR_SSL_RECVAPP`
 *
 *     Engine has obtained some application data from the peer,
 *     that should be read by the caller.
 *
 * If no flag at all is set (state value is 0), then the engine is not
 * fully initialised yet.
 *
 * The `BR_SSL_CLOSED` flag is exclusive; when it is set, no other flag
 * is set. To distinguish between a normal closure and an error, use
 * `br_ssl_engine_last_error()`.
 *
 * Generally speaking, `BR_SSL_SENDREC` and `BR_SSL_SENDAPP` are mutually
 * exclusive: the input buffer, at any point, either accumulates
 * plaintext data, or contains an assembled record that is being sent.
 * Similarly, `BR_SSL_RECVREC` and `BR_SSL_RECVAPP` are mutually exclusive.
 * This may change in a future library version.
 *
 * \param cc   SSL engine context.
 * \return  the current engine state.
 */
unsigned br_ssl_engine_current_state(const br_ssl_engine_context *cc);

/** \brief SSL engine state: closed or failed. */
#define BR_SSL_CLOSED    0x0001
/** \brief SSL engine state: record data is ready to be sent to the peer. */
#define BR_SSL_SENDREC   0x0002
/** \brief SSL engine state: engine may receive records from the peer. */
#define BR_SSL_RECVREC   0x0004
/** \brief SSL engine state: engine may accept application data to send. */
#define BR_SSL_SENDAPP   0x0008
/** \brief SSL engine state: engine has received application data. */
#define BR_SSL_RECVAPP   0x0010

/**
 * \brief Get the engine error indicator.
 *
 * The error indicator is `BR_ERR_OK` (0) if no error was encountered
 * since the last call to `br_ssl_client_reset()` or
 * `br_ssl_server_reset()`. Other status values are "sticky": they
 * remain set, and prevent all I/O activity, until cleared. Only the
 * reset calls clear the error indicator.
 *
 * \param cc   SSL engine context.
 * \return  0, or a non-zero error code.
 */
static inline int
br_ssl_engine_last_error(const br_ssl_engine_context *cc)
{
	return cc->err;
}

/*
 * There are four I/O operations, each identified by a symbolic name:
 *
 *   sendapp   inject application data in the engine
 *   recvapp   retrieving application data from the engine
 *   sendrec   sending records on the transport medium
 *   recvrec   receiving records from the transport medium
 *
 * Terminology works thus: in a layered model where the SSL engine sits
 * between the application and the network, "send" designates operations
 * where bytes flow from application to network, and "recv" for the
 * reverse operation. Application data (the plaintext that is to be
 * conveyed through SSL) is "app", while encrypted records are "rec".
 * Note that from the SSL engine point of view, "sendapp" and "recvrec"
 * designate bytes that enter the engine ("inject" operation), while
 * "recvapp" and "sendrec" designate bytes that exit the engine
 * ("extract" operation).
 *
 * For the operation 'xxx', two functions are defined:
 *
 *   br_ssl_engine_xxx_buf
 *      Returns a pointer and length to the buffer to use for that
 *      operation. '*len' is set to the number of bytes that may be read
 *      from the buffer (extract operation) or written to the buffer
 *      (inject operation). If no byte may be exchanged for that operation
 *      at that point, then '*len' is set to zero, and NULL is returned.
 *      The engine state is unmodified by this call.
 *
 *   br_ssl_engine_xxx_ack
 *      Informs the engine that 'len' bytes have been read from the buffer
 *      (extract operation) or written to the buffer (inject operation).
 *      The 'len' value MUST NOT be zero. The 'len' value MUST NOT exceed
 *      that which was obtained from a preceding br_ssl_engine_xxx_buf()
 *      call.
 */

/**
 * \brief Get buffer for application data to send.
 *
 * If the engine is ready to accept application data to send to the
 * peer, then this call returns a pointer to the buffer where such
 * data shall be written, and its length is written in `*len`.
 * Otherwise, `*len` is set to 0 and `NULL` is returned.
 *
 * \param cc    SSL engine context.
 * \param len   receives the application data output buffer length, or 0.
 * \return  the application data output buffer, or `NULL`.
 */
unsigned char *br_ssl_engine_sendapp_buf(
	const br_ssl_engine_context *cc, size_t *len);

/**
 * \brief Inform the engine of some new application data.
 *
 * After writing `len` bytes in the buffer returned by
 * `br_ssl_engine_sendapp_buf()`, the application shall call this
 * function to trigger any relevant processing. The `len` parameter
 * MUST NOT be 0, and MUST NOT exceed the value obtained in the
 * `br_ssl_engine_sendapp_buf()` call.
 *
 * \param cc    SSL engine context.
 * \param len   number of bytes pushed (not zero).
 */
void br_ssl_engine_sendapp_ack(br_ssl_engine_context *cc, size_t len);

/**
 * \brief Get buffer for received application data.
 *
 * If the engine has received application data from the peer, then this
 * call returns a pointer to the buffer from where such data shall be
 * read, and its length is written in `*len`. Otherwise, `*len` is set
 * to 0 and `NULL` is returned.
 *
 * \param cc    SSL engine context.
 * \param len   receives the application data input buffer length, or 0.
 * \return  the application data input buffer, or `NULL`.
 */
unsigned char *br_ssl_engine_recvapp_buf(
	const br_ssl_engine_context *cc, size_t *len);

/**
 * \brief Acknowledge some received application data.
 *
 * After reading `len` bytes from the buffer returned by
 * `br_ssl_engine_recvapp_buf()`, the application shall call this
 * function to trigger any relevant processing. The `len` parameter
 * MUST NOT be 0, and MUST NOT exceed the value obtained in the
 * `br_ssl_engine_recvapp_buf()` call.
 *
 * \param cc    SSL engine context.
 * \param len   number of bytes read (not zero).
 */
void br_ssl_engine_recvapp_ack(br_ssl_engine_context *cc, size_t len);

/**
 * \brief Get buffer for record data to send.
 *
 * If the engine has prepared some records to send to the peer, then this
 * call returns a pointer to the buffer from where such data shall be
 * read, and its length is written in `*len`. Otherwise, `*len` is set
 * to 0 and `NULL` is returned.
 *
 * \param cc    SSL engine context.
 * \param len   receives the record data output buffer length, or 0.
 * \return  the record data output buffer, or `NULL`.
 */
unsigned char *br_ssl_engine_sendrec_buf(
	const br_ssl_engine_context *cc, size_t *len);

/**
 * \brief Acknowledge some sent record data.
 *
 * After reading `len` bytes from the buffer returned by
 * `br_ssl_engine_sendrec_buf()`, the application shall call this
 * function to trigger any relevant processing. The `len` parameter
 * MUST NOT be 0, and MUST NOT exceed the value obtained in the
 * `br_ssl_engine_sendrec_buf()` call.
 *
 * \param cc    SSL engine context.
 * \param len   number of bytes read (not zero).
 */
void br_ssl_engine_sendrec_ack(br_ssl_engine_context *cc, size_t len);

/**
 * \brief Get buffer for incoming records.
 *
 * If the engine is ready to accept records from the peer, then this
 * call returns a pointer to the buffer where such data shall be
 * written, and its length is written in `*len`. Otherwise, `*len` is
 * set to 0 and `NULL` is returned.
 *
 * \param cc    SSL engine context.
 * \param len   receives the record data input buffer length, or 0.
 * \return  the record data input buffer, or `NULL`.
 */
unsigned char *br_ssl_engine_recvrec_buf(
	const br_ssl_engine_context *cc, size_t *len);

/**
 * \brief Inform the engine of some new record data.
 *
 * After writing `len` bytes in the buffer returned by
 * `br_ssl_engine_recvrec_buf()`, the application shall call this
 * function to trigger any relevant processing. The `len` parameter
 * MUST NOT be 0, and MUST NOT exceed the value obtained in the
 * `br_ssl_engine_recvrec_buf()` call.
 *
 * \param cc    SSL engine context.
 * \param len   number of bytes pushed (not zero).
 */
void br_ssl_engine_recvrec_ack(br_ssl_engine_context *cc, size_t len);

/**
 * \brief Flush buffered application data.
 *
 * If some application data has been buffered in the engine, then wrap
 * it into a record and mark it for sending. If no application data has
 * been buffered but the engine would be ready to accept some, AND the
 * `force` parameter is non-zero, then an empty record is assembled and
 * marked for sending. In all other cases, this function does nothing.
 *
 * Empty records are technically legal, but not all existing SSL/TLS
 * implementations support them. Empty records can be useful as a
 * transparent "keep-alive" mechanism to maintain some low-level
 * network activity.
 *
 * \param cc      SSL engine context.
 * \param force   non-zero to force sending an empty record.
 */
void br_ssl_engine_flush(br_ssl_engine_context *cc, int force);

/**
 * \brief Initiate a closure.
 *
 * If, at that point, the context is open and in ready state, then a
 * `close_notify` alert is assembled and marked for sending; this
 * triggers the closure protocol. Otherwise, no such alert is assembled.
 *
 * \param cc   SSL engine context.
 */
void br_ssl_engine_close(br_ssl_engine_context *cc);

/**
 * \brief Initiate a renegotiation.
 *
 * If the engine is failed or closed, or if the peer is known not to
 * support secure renegotiation (RFC 5746), or if renegotiations have
 * been disabled with the `BR_OPT_NO_RENEGOTIATION` flag, or if there
 * is buffered incoming application data, then this function returns 0
 * and nothing else happens.
 *
 * Otherwise, this function returns 1, and a renegotiation attempt is
 * triggered (if a handshake is already ongoing at that point, then
 * no new handshake is triggered).
 *
 * \param cc   SSL engine context.
 * \return  1 on success, 0 on error.
 */
int br_ssl_engine_renegotiate(br_ssl_engine_context *cc);

/**
 * \brief Export key material from a connected SSL engine (RFC 5705).
 *
 * This calls compute a secret key of arbitrary length from the master
 * secret of a connected SSL engine. If the provided context is not
 * currently in "application data" state (initial handshake is not
 * finished, another handshake is ongoing, or the connection failed or
 * was closed), then this function returns 0. Otherwise, a secret key of
 * length `len` bytes is computed and written in the buffer pointed to
 * by `dst`, and 1 is returned.
 *
 * The computed key follows the specification described in RFC 5705.
 * That RFC includes two key computations, with and without a "context
 * value". If `context` is `NULL`, then the variant without context is
 * used; otherwise, the `context_len` bytes located at the address
 * pointed to by `context` are used in the computation. Note that it
 * is possible to have a "with context" key with a context length of
 * zero bytes, by setting `context` to a non-`NULL` value but
 * `context_len` to 0.
 *
 * When context bytes are used, the context length MUST NOT exceed
 * 65535 bytes.
 *
 * \param cc            SSL engine context.
 * \param dst           destination buffer for exported key.
 * \param len           exported key length (in bytes).
 * \param label         disambiguation label.
 * \param context       context value (or `NULL`).
 * \param context_len   context length (in bytes).
 * \return  1 on success, 0 on error.
 */
int br_ssl_key_export(br_ssl_engine_context *cc,
	void *dst, size_t len, const char *label,
	const void *context, size_t context_len);

/*
 * Pre-declaration for the SSL client context.
 */
typedef struct br_ssl_client_context_ br_ssl_client_context;

/**
 * \brief Type for the client certificate, if requested by the server.
 */
typedef struct {
	/**
	 * \brief Authentication type.
	 *
	 * This is either `BR_AUTH_RSA` (RSA signature), `BR_AUTH_ECDSA`
	 * (ECDSA signature), or `BR_AUTH_ECDH` (static ECDH key exchange).
	 */
	int auth_type;

	/**
	 * \brief Hash function for computing the CertificateVerify.
	 *
	 * This is the symbolic identifier for the hash function that
	 * will be used to produce the hash of handshake messages, to
	 * be signed into the CertificateVerify. For full static ECDH
	 * (client and server certificates are both EC in the same
	 * curve, and static ECDH is used), this value is set to -1.
	 *
	 * Take care that with TLS 1.0 and 1.1, that value MUST match
	 * the protocol requirements: value must be 0 (MD5+SHA-1) for
	 * a RSA signature, or 2 (SHA-1) for an ECDSA signature. Only
	 * TLS 1.2 allows for other hash functions.
	 */
	int hash_id;

	/**
	 * \brief Certificate chain to send to the server.
	 *
	 * This is an array of `br_x509_certificate` objects, each
	 * normally containing a DER-encoded certificate. The client
	 * code does not try to decode these elements. If there is no
	 * chain to send to the server, then this pointer shall be
	 * set to `NULL`.
	 */
	const br_x509_certificate *chain;

	/**
	 * \brief Certificate chain length (number of certificates).
	 *
	 * If there is no chain to send to the server, then this value
	 * shall be set to 0.
	 */
	size_t chain_len;

} br_ssl_client_certificate;

/*
 * Note: the constants below for signatures match the TLS constants.
 */

/** \brief Client authentication type: static ECDH. */
#define BR_AUTH_ECDH    0
/** \brief Client authentication type: RSA signature. */
#define BR_AUTH_RSA     1
/** \brief Client authentication type: ECDSA signature. */
#define BR_AUTH_ECDSA   3

/**
 * \brief Class type for a certificate handler (client side).
 *
 * A certificate handler selects a client certificate chain to send to
 * the server, upon explicit request from that server. It receives
 * the list of trust anchor DN from the server, and supported types
 * of certificates and signatures, and returns the chain to use. It
 * is also invoked to perform the corresponding private key operation
 * (a signature, or an ECDH computation).
 *
 * The SSL client engine will first push the trust anchor DN with
 * `start_name_list()`, `start_name()`, `append_name()`, `end_name()`
 * and `end_name_list()`. Then it will call `choose()`, to select the
 * actual chain (and signature/hash algorithms). Finally, it will call
 * either `do_sign()` or `do_keyx()`, depending on the algorithm choices.
 */
typedef struct br_ssl_client_certificate_class_ br_ssl_client_certificate_class;
struct br_ssl_client_certificate_class_ {
	/**
	 * \brief Context size (in bytes).
	 */
	size_t context_size;

	/**
	 * \brief Begin reception of a list of trust anchor names. This
	 * is called while parsing the incoming CertificateRequest.
	 *
	 * \param pctx   certificate handler context.
	 */
	void (*start_name_list)(const br_ssl_client_certificate_class **pctx);

	/**
	 * \brief Begin reception of a new trust anchor name.
	 *
	 * The total encoded name length is provided; it is less than
	 * 65535 bytes.
	 *
	 * \param pctx   certificate handler context.
	 * \param len    encoded name length (in bytes).
	 */
	void (*start_name)(const br_ssl_client_certificate_class **pctx,
		size_t len);

	/**
	 * \brief Receive some more bytes for the current trust anchor name.
	 *
	 * The provided reference (`data`) points to a transient buffer
	 * they may be reused as soon as this function returns. The chunk
	 * length (`len`) is never zero.
	 *
	 * \param pctx   certificate handler context.
	 * \param data   anchor name chunk.
	 * \param len    anchor name chunk length (in bytes).
	 */
	void (*append_name)(const br_ssl_client_certificate_class **pctx,
		const unsigned char *data, size_t len);

	/**
	 * \brief End current trust anchor name.
	 *
	 * This function is called when all the encoded anchor name data
	 * has been provided.
	 *
	 * \param pctx   certificate handler context.
	 */
	void (*end_name)(const br_ssl_client_certificate_class **pctx);

	/**
	 * \brief End list of trust anchor names.
	 *
	 * This function is called when all the anchor names in the
	 * CertificateRequest message have been obtained.
	 *
	 * \param pctx   certificate handler context.
	 */
	void (*end_name_list)(const br_ssl_client_certificate_class **pctx);

	/**
	 * \brief Select client certificate and algorithms.
	 *
	 * This callback function shall fill the provided `choices`
	 * structure with the selected algorithms and certificate chain.
	 * The `hash_id`, `chain` and `chain_len` fields must be set. If
	 * the client cannot or does not wish to send a certificate,
	 * then it shall set `chain` to `NULL` and `chain_len` to 0.
	 *
	 * The `auth_types` parameter describes the authentication types,
	 * signature algorithms and hash functions that are supported by
	 * both the client context and the server, and compatible with
	 * the current protocol version. This is a bit field with the
	 * following contents:
	 *
	 *   - If RSA signatures with hash function x are supported, then
	 *     bit x is set.
	 *
	 *   - If ECDSA signatures with hash function x are supported,
	 *     then bit 8+x is set.
	 *
	 *   - If static ECDH is supported, with a RSA-signed certificate,
	 *     then bit 16 is set.
	 *
	 *   - If static ECDH is supported, with an ECDSA-signed certificate,
	 *     then bit 17 is set.
	 *
	 * Notes:
	 *
	 *   - When using TLS 1.0 or 1.1, the hash function for RSA
	 *     signatures is always the special MD5+SHA-1 (id 0), and the
	 *     hash function for ECDSA signatures is always SHA-1 (id 2).
	 *
	 *   - When using TLS 1.2, the list of hash functions is trimmed
	 *     down to include only hash functions that the client context
	 *     can support. The actual server list can be obtained with
	 *     `br_ssl_client_get_server_hashes()`; that list may be used
	 *     to select the certificate chain to send to the server.
	 *
	 * \param pctx         certificate handler context.
	 * \param cc           SSL client context.
	 * \param auth_types   supported authentication types and algorithms.
	 * \param choices      destination structure for the policy choices.
	 */
	void (*choose)(const br_ssl_client_certificate_class **pctx,
		const br_ssl_client_context *cc, uint32_t auth_types,
		br_ssl_client_certificate *choices);

	/**
	 * \brief Perform key exchange (client part).
	 *
	 * This callback is invoked in case of a full static ECDH key
	 * exchange:
	 *
	 *   - the cipher suite uses `ECDH_RSA` or `ECDH_ECDSA`;
	 *
	 *   - the server requests a client certificate;
	 *
	 *   - the client has, and sends, a client certificate that
	 *     uses an EC key in the same curve as the server's key,
	 *     and chooses static ECDH (the `hash_id` field in the choice
	 *     structure was set to -1).
	 *
	 * In that situation, this callback is invoked to compute the
	 * client-side ECDH: the provided `data` (of length `*len` bytes)
	 * is the server's public key point (as decoded from its
	 * certificate), and the client shall multiply that point with
	 * its own private key, and write back the X coordinate of the
	 * resulting point in the same buffer, starting at offset 0.
	 * The `*len` value shall be modified to designate the actual
	 * length of the X coordinate.
	 *
	 * The callback must uphold the following:
	 *
	 *   - If the input array does not have the proper length for
	 *     an encoded curve point, then an error (0) shall be reported.
	 *
	 *   - If the input array has the proper length, then processing
	 *     MUST be constant-time, even if the data is not a valid
	 *     encoded point.
	 *
	 *   - This callback MUST check that the input point is valid.
	 *
	 * Returned value is 1 on success, 0 on error.
	 *
	 * \param pctx   certificate handler context.
	 * \param data   server public key point.
	 * \param len    public key point length / X coordinate length.
	 * \return  1 on success, 0 on error.
	 */
	uint32_t (*do_keyx)(const br_ssl_client_certificate_class **pctx,
		unsigned char *data, size_t *len);

	/**
	 * \brief Perform a signature (client authentication).
	 *
	 * This callback is invoked when a client certificate was sent,
	 * and static ECDH is not used. It shall compute a signature,
	 * using the client's private key, over the provided hash value
	 * (which is the hash of all previous handshake messages).
	 *
	 * On input, the hash value to sign is in `data`, of size
	 * `hv_len`; the involved hash function is identified by
	 * `hash_id`. The signature shall be computed and written
	 * back into `data`; the total size of that buffer is `len`
	 * bytes.
	 *
	 * This callback shall verify that the signature length does not
	 * exceed `len` bytes, and abstain from writing the signature if
	 * it does not fit.
	 *
	 * For RSA signatures, the `hash_id` may be 0, in which case
	 * this is the special header-less signature specified in TLS 1.0
	 * and 1.1, with a 36-byte hash value. Otherwise, normal PKCS#1
	 * v1.5 signatures shall be computed.
	 *
	 * For ECDSA signatures, the signature value shall use the ASN.1
	 * based encoding.
	 *
	 * Returned value is the signature length (in bytes), or 0 on error.
	 *
	 * \param pctx      certificate handler context.
	 * \param hash_id   hash function identifier.
	 * \param hv_len    hash value length (in bytes).
	 * \param data      input/output buffer (hash value, then signature).
	 * \param len       total buffer length (in bytes).
	 * \return  signature length (in bytes) on success, or 0 on error.
	 */
	size_t (*do_sign)(const br_ssl_client_certificate_class **pctx,
		int hash_id, size_t hv_len, unsigned char *data, size_t len);
};

/**
 * \brief A single-chain RSA client certificate handler.
 *
 * This handler uses a single certificate chain, with a RSA
 * signature. The list of trust anchor DN is ignored.
 *
 * Apart from the first field (vtable pointer), its contents are
 * opaque and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	const br_ssl_client_certificate_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	const br_x509_certificate *chain;
	size_t chain_len;
	const br_rsa_private_key *sk;
	br_rsa_pkcs1_sign irsasign;
#endif
} br_ssl_client_certificate_rsa_context;

/**
 * \brief A single-chain EC client certificate handler.
 *
 * This handler uses a single certificate chain, with a RSA
 * signature. The list of trust anchor DN is ignored.
 *
 * This handler may support both static ECDH, and ECDSA signatures
 * (either usage may be selectively disabled).
 *
 * Apart from the first field (vtable pointer), its contents are
 * opaque and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	const br_ssl_client_certificate_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	const br_x509_certificate *chain;
	size_t chain_len;
	const br_ec_private_key *sk;
	unsigned allowed_usages;
	unsigned issuer_key_type;
	const br_multihash_context *mhash;
	const br_ec_impl *iec;
	br_ecdsa_sign iecdsa;
#endif
} br_ssl_client_certificate_ec_context;

/**
 * \brief Context structure for a SSL client.
 *
 * The first field (called `eng`) is the SSL engine; all functions that
 * work on a `br_ssl_engine_context` structure shall take as parameter
 * a pointer to that field. The other structure fields are opaque and
 * must not be accessed directly.
 */
struct br_ssl_client_context_ {
	/**
	 * \brief The encapsulated engine context.
	 */
	br_ssl_engine_context eng;

#ifndef BR_DOXYGEN_IGNORE
	/*
	 * Minimum ClientHello length; padding with an extension (RFC
	 * 7685) is added if necessary to match at least that length.
	 * Such padding is nominally unnecessary, but it has been used
	 * to work around some server implementation bugs.
	 */
	uint16_t min_clienthello_len;

	/*
	 * Bit field for algoithms (hash + signature) supported by the
	 * server when requesting a client certificate.
	 */
	uint32_t hashes;

	/*
	 * Server's public key curve.
	 */
	int server_curve;

	/*
	 * Context for certificate handler.
	 */
	const br_ssl_client_certificate_class **client_auth_vtable;

	/*
	 * Client authentication type.
	 */
	unsigned char auth_type;

	/*
	 * Hash function to use for the client signature. This is 0xFF
	 * if static ECDH is used.
	 */
	unsigned char hash_id;

	/*
	 * For the core certificate handlers, thus avoiding (in most
	 * cases) the need for an externally provided policy context.
	 */
	union {
		const br_ssl_client_certificate_class *vtable;
		br_ssl_client_certificate_rsa_context single_rsa;
		br_ssl_client_certificate_ec_context single_ec;
	} client_auth;

	/*
	 * Implementations.
	 */
	br_rsa_public irsapub;
#endif
};

/**
 * \brief Get the hash functions and signature algorithms supported by
 * the server.
 *
 * This value is a bit field:
 *
 *   - If RSA (PKCS#1 v1.5) is supported with hash function of ID `x`,
 *     then bit `x` is set (hash function ID is 0 for the special MD5+SHA-1,
 *     or 2 to 6 for the SHA family).
 *
 *   - If ECDSA is supported with hash function of ID `x`, then bit `8+x`
 *     is set.
 *
 *   - Newer algorithms are symbolic 16-bit identifiers that do not
 *     represent signature algorithm and hash function separately. If
 *     the TLS-level identifier is `0x0800+x` for a `x` in the 0..15
 *     range, then bit `16+x` is set.
 *
 * "New algorithms" are currently defined only in draft documents, so
 * this support is subject to possible change. Right now (early 2017),
 * this maps ed25519 (EdDSA on Curve25519) to bit 23, and ed448 (EdDSA
 * on Curve448) to bit 24. If the identifiers on the wire change in
 * future document, then the decoding mechanism in BearSSL will be
 * amended to keep mapping ed25519 and ed448 on bits 23 and 24,
 * respectively. Mapping of other new algorithms (e.g. RSA/PSS) is not
 * guaranteed yet.
 *
 * \param cc   client context.
 * \return  the server-supported hash functions and signature algorithms.
 */
static inline uint32_t
br_ssl_client_get_server_hashes(const br_ssl_client_context *cc)
{
	return cc->hashes;
}

/**
 * \brief Get the server key curve.
 *
 * This function returns the ID for the curve used by the server's public
 * key. This is set when the server's certificate chain is processed;
 * this value is 0 if the server's key is not an EC key.
 *
 * \return  the server's public key curve ID, or 0.
 */
static inline int
br_ssl_client_get_server_curve(const br_ssl_client_context *cc)
{
	return cc->server_curve;
}

/*
 * Each br_ssl_client_init_xxx() function sets the list of supported
 * cipher suites and used implementations, as specified by the profile
 * name 'xxx'. Defined profile names are:
 *
 *    full    all supported versions and suites; constant-time implementations
 *    TODO: add other profiles
 */

/**
 * \brief SSL client profile: full.
 *
 * This function initialises the provided SSL client context with
 * all supported algorithms and cipher suites. It also initialises
 * a companion X.509 validation engine with all supported algorithms,
 * and the provided trust anchors; the X.509 engine will be used by
 * the client context to validate the server's certificate.
 *
 * \param cc                  client context to initialise.
 * \param xc                  X.509 validation context to initialise.
 * \param trust_anchors       trust anchors to use.
 * \param trust_anchors_num   number of trust anchors.
 */
void br_ssl_client_init_full(br_ssl_client_context *cc,
	br_x509_minimal_context *xc,
	const br_x509_trust_anchor *trust_anchors, size_t trust_anchors_num);

/**
 * \brief Clear the complete contents of a SSL client context.
 *
 * Everything is cleared, including the reference to the configured buffer,
 * implementations, cipher suites and state. This is a preparatory step
 * to assembling a custom profile.
 *
 * \param cc   client context to clear.
 */
void br_ssl_client_zero(br_ssl_client_context *cc);

/**
 * \brief Set an externally provided client certificate handler context.
 *
 * The handler's methods are invoked when the server requests a client
 * certificate.
 *
 * \param cc     client context.
 * \param pctx   certificate handler context (pointer to its vtable field).
 */
static inline void
br_ssl_client_set_client_certificate(br_ssl_client_context *cc,
	const br_ssl_client_certificate_class **pctx)
{
	cc->client_auth_vtable = pctx;
}

/**
 * \brief Set the RSA public-key operations implementation.
 *
 * This will be used to encrypt the pre-master secret with the server's
 * RSA public key (RSA-encryption cipher suites only).
 *
 * \param cc        client context.
 * \param irsapub   RSA public-key encryption implementation.
 */
static inline void
br_ssl_client_set_rsapub(br_ssl_client_context *cc, br_rsa_public irsapub)
{
	cc->irsapub = irsapub;
}

/**
 * \brief Set the "default" RSA implementation for public-key operations.
 *
 * This sets the RSA implementation in the client context (for encrypting
 * the pre-master secret, in `TLS_RSA_*` cipher suites) to the fastest
 * available on the current platform.
 *
 * \param cc   client context.
 */
void br_ssl_client_set_default_rsapub(br_ssl_client_context *cc);

/**
 * \brief Set the minimum ClientHello length (RFC 7685 padding).
 *
 * If this value is set and the ClientHello would be shorter, then
 * the Pad ClientHello extension will be added with enough padding bytes
 * to reach the target size. Because of the extension header, the resulting
 * size will sometimes be slightly more than `len` bytes if the target
 * size cannot be exactly met.
 *
 * The target length relates to the _contents_ of the ClientHello, not
 * counting its 4-byte header. For instance, if `len` is set to 512,
 * then the padding will bring the ClientHello size to 516 bytes with its
 * header, and 521 bytes when counting the 5-byte record header.
 *
 * \param cc    client context.
 * \param len   minimum ClientHello length (in bytes).
 */
static inline void
br_ssl_client_set_min_clienthello_len(br_ssl_client_context *cc, uint16_t len)
{
	cc->min_clienthello_len = len;
}

/**
 * \brief Prepare or reset a client context for a new connection.
 *
 * The `server_name` parameter is used to fill the SNI extension; the
 * X.509 "minimal" engine will also match that name against the server
 * names included in the server's certificate. If the parameter is
 * `NULL` then no SNI extension will be sent, and the X.509 "minimal"
 * engine (if used for server certificate validation) will not check
 * presence of any specific name in the received certificate.
 *
 * Therefore, setting the `server_name` to `NULL` shall be reserved
 * to cases where alternate or additional methods are used to ascertain
 * that the right server public key is used (e.g. a "known key" model).
 *
 * If `resume_session` is non-zero and the context was previously used
 * then the session parameters may be reused (depending on whether the
 * server previously sent a non-empty session ID, and accepts the session
 * resumption). The session parameters for session resumption can also
 * be set explicitly with `br_ssl_engine_set_session_parameters()`.
 *
 * On failure, the context is marked as failed, and this function
 * returns 0. A possible failure condition is when no initial entropy
 * was injected, and none could be obtained from the OS (either OS
 * randomness gathering is not supported, or it failed).
 *
 * \param cc               client context.
 * \param server_name      target server name, or `NULL`.
 * \param resume_session   non-zero to try session resumption.
 * \return  0 on failure, 1 on success.
 */
int br_ssl_client_reset(br_ssl_client_context *cc,
	const char *server_name, int resume_session);

/**
 * \brief Forget any session in the context.
 *
 * This means that the next handshake that uses this context will
 * necessarily be a full handshake (this applies both to new connections
 * and to renegotiations).
 *
 * \param cc   client context.
 */
static inline void
br_ssl_client_forget_session(br_ssl_client_context *cc)
{
	cc->eng.session.session_id_len = 0;
}

/**
 * \brief Set client certificate chain and key (single RSA case).
 *
 * This function sets a client certificate chain, that the client will
 * send to the server whenever a client certificate is requested. This
 * certificate uses an RSA public key; the corresponding private key is
 * invoked for authentication. Trust anchor names sent by the server are
 * ignored.
 *
 * The provided chain and private key are linked in the client context;
 * they must remain valid as long as they may be used, i.e. normally
 * for the duration of the connection, since they might be invoked
 * again upon renegotiations.
 *
 * \param cc          SSL client context.
 * \param chain       client certificate chain (SSL order: EE comes first).
 * \param chain_len   client chain length (number of certificates).
 * \param sk          client private key.
 * \param irsasign    RSA signature implementation (PKCS#1 v1.5).
 */
void br_ssl_client_set_single_rsa(br_ssl_client_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk, br_rsa_pkcs1_sign irsasign);

/*
 * \brief Set the client certificate chain and key (single EC case).
 *
 * This function sets a client certificate chain, that the client will
 * send to the server whenever a client certificate is requested. This
 * certificate uses an EC public key; the corresponding private key is
 * invoked for authentication. Trust anchor names sent by the server are
 * ignored.
 *
 * The provided chain and private key are linked in the client context;
 * they must remain valid as long as they may be used, i.e. normally
 * for the duration of the connection, since they might be invoked
 * again upon renegotiations.
 *
 * The `allowed_usages` is a combination of usages, namely
 * `BR_KEYTYPE_KEYX` and/or `BR_KEYTYPE_SIGN`. The `BR_KEYTYPE_KEYX`
 * value allows full static ECDH, while the `BR_KEYTYPE_SIGN` value
 * allows ECDSA signatures. If ECDSA signatures are used, then an ECDSA
 * signature implementation must be provided; otherwise, the `iecdsa`
 * parameter may be 0.
 *
 * The `cert_issuer_key_type` value is either `BR_KEYTYPE_RSA` or
 * `BR_KEYTYPE_EC`; it is the type of the public key used the the CA
 * that issued (signed) the client certificate. That value is used with
 * full static ECDH: support of the certificate by the server depends
 * on how the certificate was signed. (Note: when using TLS 1.2, this
 * parameter is ignored; but its value matters for TLS 1.0 and 1.1.)
 *
 * \param cc                     server context.
 * \param chain                  server certificate chain to send.
 * \param chain_len              chain length (number of certificates).
 * \param sk                     server private key (EC).
 * \param allowed_usages         allowed private key usages.
 * \param cert_issuer_key_type   issuing CA's key type.
 * \param iec                    EC core implementation.
 * \param iecdsa                 ECDSA signature implementation ("asn1" format).
 */
void br_ssl_client_set_single_ec(br_ssl_client_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_ec_private_key *sk, unsigned allowed_usages,
	unsigned cert_issuer_key_type,
	const br_ec_impl *iec, br_ecdsa_sign iecdsa);

/**
 * \brief Type for a "translated cipher suite", as an array of two
 * 16-bit integers.
 *
 * The first element is the cipher suite identifier (as used on the wire).
 * The second element is the concatenation of four 4-bit elements which
 * characterise the cipher suite contents. In most to least significant
 * order, these 4-bit elements are:
 *
 *   - Bits 12 to 15: key exchange + server key type
 *
 *     | val | symbolic constant        | suite type  | details                                          |
 *     | :-- | :----------------------- | :---------- | :----------------------------------------------- |
 *     |  0  | `BR_SSLKEYX_RSA`         | RSA         | RSA key exchange, key is RSA (encryption)        |
 *     |  1  | `BR_SSLKEYX_ECDHE_RSA`   | ECDHE_RSA   | ECDHE key exchange, key is RSA (signature)       |
 *     |  2  | `BR_SSLKEYX_ECDHE_ECDSA` | ECDHE_ECDSA | ECDHE key exchange, key is EC (signature)        |
 *     |  3  | `BR_SSLKEYX_ECDH_RSA`    | ECDH_RSA    | Key is EC (key exchange), cert signed with RSA   |
 *     |  4  | `BR_SSLKEYX_ECDH_ECDSA`  | ECDH_ECDSA  | Key is EC (key exchange), cert signed with ECDSA |
 *
 *   - Bits 8 to 11: symmetric encryption algorithm
 *
 *     | val | symbolic constant      | symmetric encryption | key strength (bits) |
 *     | :-- | :--------------------- | :------------------- | :------------------ |
 *     |  0  | `BR_SSLENC_3DES_CBC`   | 3DES/CBC             | 168                 |
 *     |  1  | `BR_SSLENC_AES128_CBC` | AES-128/CBC          | 128                 |
 *     |  2  | `BR_SSLENC_AES256_CBC` | AES-256/CBC          | 256                 |
 *     |  3  | `BR_SSLENC_AES128_GCM` | AES-128/GCM          | 128                 |
 *     |  4  | `BR_SSLENC_AES256_GCM` | AES-256/GCM          | 256                 |
 *     |  5  | `BR_SSLENC_CHACHA20`   | ChaCha20/Poly1305    | 256                 |
 *
 *   - Bits 4 to 7: MAC algorithm
 *
 *     | val | symbolic constant  | MAC type     | details                               |
 *     | :-- | :----------------- | :----------- | :------------------------------------ |
 *     |  0  | `BR_SSLMAC_AEAD`   | AEAD         | No dedicated MAC (encryption is AEAD) |
 *     |  2  | `BR_SSLMAC_SHA1`   | HMAC/SHA-1   | Value matches `br_sha1_ID`            |
 *     |  4  | `BR_SSLMAC_SHA256` | HMAC/SHA-256 | Value matches `br_sha256_ID`          |
 *     |  5  | `BR_SSLMAC_SHA384` | HMAC/SHA-384 | Value matches `br_sha384_ID`          |
 *
 *   - Bits 0 to 3: hash function for PRF when used with TLS-1.2
 *
 *     | val | symbolic constant  | hash function | details                              |
 *     | :-- | :----------------- | :------------ | :----------------------------------- |
 *     |  4  | `BR_SSLPRF_SHA256` | SHA-256       | Value matches `br_sha256_ID`         |
 *     |  5  | `BR_SSLPRF_SHA384` | SHA-384       | Value matches `br_sha384_ID`         |
 *
 * For instance, cipher suite `TLS_RSA_WITH_AES_128_GCM_SHA256` has
 * standard identifier 0x009C, and is translated to 0x0304, for, in
 * that order: RSA key exchange (0), AES-128/GCM (3), AEAD integrity (0),
 * SHA-256 in the TLS PRF (4).
 */
typedef uint16_t br_suite_translated[2];

#ifndef BR_DOXYGEN_IGNORE
/*
 * Constants are already documented in the br_suite_translated type.
 */

#define BR_SSLKEYX_RSA           0
#define BR_SSLKEYX_ECDHE_RSA     1
#define BR_SSLKEYX_ECDHE_ECDSA   2
#define BR_SSLKEYX_ECDH_RSA      3
#define BR_SSLKEYX_ECDH_ECDSA    4

#define BR_SSLENC_3DES_CBC       0
#define BR_SSLENC_AES128_CBC     1
#define BR_SSLENC_AES256_CBC     2
#define BR_SSLENC_AES128_GCM     3
#define BR_SSLENC_AES256_GCM     4
#define BR_SSLENC_CHACHA20       5

#define BR_SSLMAC_AEAD           0
#define BR_SSLMAC_SHA1           br_sha1_ID
#define BR_SSLMAC_SHA256         br_sha256_ID
#define BR_SSLMAC_SHA384         br_sha384_ID

#define BR_SSLPRF_SHA256         br_sha256_ID
#define BR_SSLPRF_SHA384         br_sha384_ID

#endif

/*
 * Pre-declaration for the SSL server context.
 */
typedef struct br_ssl_server_context_ br_ssl_server_context;

/**
 * \brief Type for the server policy choices, taken after analysis of
 * the client message (ClientHello).
 */
typedef struct {
	/**
	 * \brief Cipher suite to use with that client.
	 */
	uint16_t cipher_suite;

	/**
	 * \brief Hash function or algorithm for signing the ServerKeyExchange.
	 *
	 * This parameter is ignored for `TLS_RSA_*` and `TLS_ECDH_*`
	 * cipher suites; it is used only for `TLS_ECDHE_*` suites, in
	 * which the server _signs_ the ephemeral EC Diffie-Hellman
	 * parameters sent to the client.
	 *
	 * This identifier must be one of the following values:
	 *
	 *   - `0xFF00 + id`, where `id` is a hash function identifier
	 *     (0 for MD5+SHA-1, or 2 to 6 for one of the SHA functions);
	 *
	 *   - a full 16-bit identifier, lower than `0xFF00`.
	 *
	 * If the first option is used, then the SSL engine will
	 * compute the hash of the data that is to be signed, with the
	 * designated hash function. The `do_sign()` method will be
	 * invoked with that hash value provided in the the `data`
	 * buffer.
	 *
	 * If the second option is used, then the SSL engine will NOT
	 * compute a hash on the data; instead, it will provide the
	 * to-be-signed data itself in `data`, i.e. the concatenation of
	 * the client random, server random, and encoded ECDH
	 * parameters. Furthermore, with TLS-1.2 and later, the 16-bit
	 * identifier will be used "as is" in the protocol, in the
	 * SignatureAndHashAlgorithm; for instance, `0x0401` stands for
	 * RSA PKCS#1 v1.5 signature (the `01`) with SHA-256 as hash
	 * function (the `04`).
	 *
	 * Take care that with TLS 1.0 and 1.1, the hash function is
	 * constrainted by the protocol: RSA signature must use
	 * MD5+SHA-1 (so use `0xFF00`), while ECDSA must use SHA-1
	 * (`0xFF02`). Since TLS 1.0 and 1.1 don't include a
	 * SignatureAndHashAlgorithm field in their ServerKeyExchange
	 * messages, any value below `0xFF00` will be usable to send the
	 * raw ServerKeyExchange data to the `do_sign()` callback, but
	 * that callback must still follow the protocol requirements
	 * when generating the signature.
	 */
	unsigned algo_id;

	/**
	 * \brief Certificate chain to send to the client.
	 *
	 * This is an array of `br_x509_certificate` objects, each
	 * normally containing a DER-encoded certificate. The server
	 * code does not try to decode these elements.
	 */
	const br_x509_certificate *chain;

	/**
	 * \brief Certificate chain length (number of certificates).
	 */
	size_t chain_len;

} br_ssl_server_choices;

/**
 * \brief Class type for a policy handler (server side).
 *
 * A policy handler selects the policy parameters for a connection
 * (cipher suite and other algorithms, and certificate chain to send to
 * the client); it also performs the server-side computations involving
 * its permanent private key.
 *
 * The SSL server engine will invoke first `choose()`, once the
 * ClientHello message has been received, then either `do_keyx()`
 * `do_sign()`, depending on the cipher suite.
 */
typedef struct br_ssl_server_policy_class_ br_ssl_server_policy_class;
struct br_ssl_server_policy_class_ {
	/**
	 * \brief Context size (in bytes).
	 */
	size_t context_size;

	/**
	 * \brief Select algorithms and certificates for this connection.
	 *
	 * This callback function shall fill the provided `choices`
	 * structure with the policy choices for this connection. This
	 * entails selecting the cipher suite, hash function for signing
	 * the ServerKeyExchange (applicable only to ECDHE cipher suites),
	 * and certificate chain to send.
	 *
	 * The callback receives a pointer to the server context that
	 * contains the relevant data. In particular, the functions
	 * `br_ssl_server_get_client_suites()`,
	 * `br_ssl_server_get_client_hashes()` and
	 * `br_ssl_server_get_client_curves()` can be used to obtain
	 * the cipher suites, hash functions and elliptic curves
	 * supported by both the client and server, respectively. The
	 * `br_ssl_engine_get_version()` and `br_ssl_engine_get_server_name()`
	 * functions yield the protocol version and requested server name
	 * (SNI), respectively.
	 *
	 * This function may modify its context structure (`pctx`) in
	 * arbitrary ways to keep track of its own choices.
	 *
	 * This function shall return 1 if appropriate policy choices
	 * could be made, or 0 if this connection cannot be pursued.
	 *
	 * \param pctx      policy context.
	 * \param cc        SSL server context.
	 * \param choices   destination structure for the policy choices.
	 * \return  1 on success, 0 on error.
	 */
	int (*choose)(const br_ssl_server_policy_class **pctx,
		const br_ssl_server_context *cc,
		br_ssl_server_choices *choices);

	/**
	 * \brief Perform key exchange (server part).
	 *
	 * This callback is invoked to perform the server-side cryptographic
	 * operation for a key exchange that is not ECDHE. This callback
	 * uses the private key.
	 *
	 * **For RSA key exchange**, the provided `data` (of length `*len`
	 * bytes) shall be decrypted with the server's private key, and
	 * the 48-byte premaster secret copied back to the first 48 bytes
	 * of `data`.
	 *
	 *   - The caller makes sure that `*len` is at least 59 bytes.
	 *
	 *   - This callback MUST check that the provided length matches
	 *     that of the key modulus; it shall report an error otherwise.
	 *
	 *   - If the length matches that of the RSA key modulus, then
	 *     processing MUST be constant-time, even if decryption fails,
	 *     or the padding is incorrect, or the plaintext message length
	 *     is not exactly 48 bytes.
	 *
	 *   - This callback needs not check the two first bytes of the
	 *     obtained pre-master secret (the caller will do that).
	 *
	 *   - If an error is reported (0), then what the callback put
	 *     in the first 48 bytes of `data` is unimportant (the caller
	 *     will use random bytes instead).
	 *
	 * **For ECDH key exchange**, the provided `data` (of length `*len`
	 * bytes) is the elliptic curve point from the client. The
	 * callback shall multiply it with its private key, and store
	 * the resulting X coordinate in `data`, starting at offset 0,
	 * and set `*len` to the length of the X coordinate.
	 *
	 *   - If the input array does not have the proper length for
	 *     an encoded curve point, then an error (0) shall be reported.
	 *
	 *   - If the input array has the proper length, then processing
	 *     MUST be constant-time, even if the data is not a valid
	 *     encoded point.
	 *
	 *   - This callback MUST check that the input point is valid.
	 *
	 * Returned value is 1 on success, 0 on error.
	 *
	 * \param pctx   policy context.
	 * \param data   key exchange data from the client.
	 * \param len    key exchange data length (in bytes).
	 * \return  1 on success, 0 on error.
	 */
	uint32_t (*do_keyx)(const br_ssl_server_policy_class **pctx,
		unsigned char *data, size_t *len);

	/**
	 * \brief Perform a signature (for a ServerKeyExchange message).
	 *
	 * This callback function is invoked for ECDHE cipher suites. On
	 * input, the hash value or message to sign is in `data`, of
	 * size `hv_len`; the involved hash function or algorithm is
	 * identified by `algo_id`. The signature shall be computed and
	 * written back into `data`; the total size of that buffer is
	 * `len` bytes.
	 *
	 * This callback shall verify that the signature length does not
	 * exceed `len` bytes, and abstain from writing the signature if
	 * it does not fit.
	 *
	 * The `algo_id` value matches that which was written in the
	 * `choices` structures by the `choose()` callback. This will be
	 * one of the following:
	 *
	 *   - `0xFF00 + id` for a hash function identifier `id`. In
	 *     that case, the `data` buffer contains a hash value
	 *     already computed over the data that is to be signed,
	 *     of length `hv_len`. The `id` may be 0 to designate the
	 *     special MD5+SHA-1 concatenation (old-style RSA signing).
	 *
	 *   - Another value, lower than `0xFF00`. The `data` buffer
	 *     then contains the raw, non-hashed data to be signed
	 *     (concatenation of the client and server randoms and
	 *     ECDH parameters). The callback is responsible to apply
	 *     any relevant hashing as part of the signing process.
	 *
	 * Returned value is the signature length (in bytes), or 0 on error.
	 *
	 * \param pctx      policy context.
	 * \param algo_id   hash function / algorithm identifier.
	 * \param data      input/output buffer (message/hash, then signature).
	 * \param hv_len    hash value or message length (in bytes).
	 * \param len       total buffer length (in bytes).
	 * \return  signature length (in bytes) on success, or 0 on error.
	 */
	size_t (*do_sign)(const br_ssl_server_policy_class **pctx,
		unsigned algo_id,
		unsigned char *data, size_t hv_len, size_t len);
};

/**
 * \brief A single-chain RSA policy handler.
 *
 * This policy context uses a single certificate chain, and a RSA
 * private key. The context can be restricted to only signatures or
 * only key exchange.
 *
 * Apart from the first field (vtable pointer), its contents are
 * opaque and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	const br_ssl_server_policy_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	const br_x509_certificate *chain;
	size_t chain_len;
	const br_rsa_private_key *sk;
	unsigned allowed_usages;
	br_rsa_private irsacore;
	br_rsa_pkcs1_sign irsasign;
#endif
} br_ssl_server_policy_rsa_context;

/**
 * \brief A single-chain EC policy handler.
 *
 * This policy context uses a single certificate chain, and an EC
 * private key. The context can be restricted to only signatures or
 * only key exchange.
 *
 * Due to how TLS is defined, this context must be made aware whether
 * the server certificate was itself signed with RSA or ECDSA. The code
 * does not try to decode the certificate to obtain that information.
 *
 * Apart from the first field (vtable pointer), its contents are
 * opaque and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	const br_ssl_server_policy_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	const br_x509_certificate *chain;
	size_t chain_len;
	const br_ec_private_key *sk;
	unsigned allowed_usages;
	unsigned cert_issuer_key_type;
	const br_multihash_context *mhash;
	const br_ec_impl *iec;
	br_ecdsa_sign iecdsa;
#endif
} br_ssl_server_policy_ec_context;

/**
 * \brief Class type for a session parameter cache.
 *
 * Session parameters are saved in the cache with `save()`, and
 * retrieved with `load()`. The cache implementation can apply any
 * storage and eviction strategy that it sees fit. The SSL server
 * context that performs the request is provided, so that its
 * functionalities may be used by the implementation (e.g. hash
 * functions or random number generation).
 */
typedef struct br_ssl_session_cache_class_ br_ssl_session_cache_class;
struct br_ssl_session_cache_class_ {
	/**
	 * \brief Context size (in bytes).
	 */
	size_t context_size;

	/**
	 * \brief Record a session.
	 *
	 * This callback should record the provided session parameters.
	 * The `params` structure is transient, so its contents shall
	 * be copied into the cache. The session ID has been randomly
	 * generated and always has length exactly 32 bytes.
	 *
	 * \param ctx          session cache context.
	 * \param server_ctx   SSL server context.
	 * \param params       session parameters to save.
	 */
	void (*save)(const br_ssl_session_cache_class **ctx,
		br_ssl_server_context *server_ctx,
		const br_ssl_session_parameters *params);

	/**
	 * \brief Lookup a session in the cache.
	 *
	 * The session ID to lookup is in `params` and always has length
	 * exactly 32 bytes. If the session parameters are found in the
	 * cache, then the parameters shall be copied into the `params`
	 * structure. Returned value is 1 on successful lookup, 0
	 * otherwise.
	 *
	 * \param ctx          session cache context.
	 * \param server_ctx   SSL server context.
	 * \param params       destination for session parameters.
	 * \return  1 if found, 0 otherwise.
	 */
	int (*load)(const br_ssl_session_cache_class **ctx,
		br_ssl_server_context *server_ctx,
		br_ssl_session_parameters *params);
};

/**
 * \brief Context for a basic cache system.
 *
 * The system stores session parameters in a buffer provided at
 * initialisation time. Each entry uses exactly 100 bytes, and
 * buffer sizes up to 4294967295 bytes are supported.
 *
 * Entries are evicted with a LRU (Least Recently Used) policy. A
 * search tree is maintained to keep lookups fast even with large
 * caches.
 *
 * Apart from the first field (vtable pointer), the structure
 * contents are opaque and shall not be accessed directly.
 */
typedef struct {
	/** \brief Pointer to vtable. */
	const br_ssl_session_cache_class *vtable;
#ifndef BR_DOXYGEN_IGNORE
	unsigned char *store;
	size_t store_len, store_ptr;
	unsigned char index_key[32];
	const br_hash_class *hash;
	int init_done;
	uint32_t head, tail, root;
#endif
} br_ssl_session_cache_lru;

/**
 * \brief Initialise a LRU session cache with the provided storage space.
 *
 * The provided storage space must remain valid as long as the cache
 * is used. Arbitrary lengths are supported, up to 4294967295 bytes;
 * each entry uses up exactly 100 bytes.
 *
 * \param cc          session cache context.
 * \param store       storage space for cached entries.
 * \param store_len   storage space length (in bytes).
 */
void br_ssl_session_cache_lru_init(br_ssl_session_cache_lru *cc,
	unsigned char *store, size_t store_len);

/**
 * \brief Forget an entry in an LRU session cache.
 *
 * The session cache context must have been initialised. The entry
 * with the provided session ID (of exactly 32 bytes) is looked for
 * in the cache; if located, it is disabled.
 *
 * \param cc   session cache context.
 * \param id   session ID to forget.
 */
void br_ssl_session_cache_lru_forget(
	br_ssl_session_cache_lru *cc, const unsigned char *id);

/**
 * \brief Context structure for a SSL server.
 *
 * The first field (called `eng`) is the SSL engine; all functions that
 * work on a `br_ssl_engine_context` structure shall take as parameter
 * a pointer to that field. The other structure fields are opaque and
 * must not be accessed directly.
 */
struct br_ssl_server_context_ {
	/**
	 * \brief The encapsulated engine context.
	 */
	br_ssl_engine_context eng;

#ifndef BR_DOXYGEN_IGNORE
	/*
	 * Maximum version from the client.
	 */
	uint16_t client_max_version;

	/*
	 * Session cache.
	 */
	const br_ssl_session_cache_class **cache_vtable;

	/*
	 * Translated cipher suites supported by the client. The list
	 * is trimmed to include only the cipher suites that the
	 * server also supports; they are in the same order as in the
	 * client message.
	 */
	br_suite_translated client_suites[BR_MAX_CIPHER_SUITES];
	unsigned char client_suites_num;

	/*
	 * Hash functions supported by the client, with ECDSA and RSA
	 * (bit mask). For hash function with id 'x', set bit index is
	 * x for RSA, x+8 for ECDSA. For newer algorithms, with ID
	 * 0x08**, bit 16+k is set for algorithm 0x0800+k.
	 */
	uint32_t hashes;

	/*
	 * Curves supported by the client (bit mask, for named curves).
	 */
	uint32_t curves;

	/*
	 * Context for chain handler.
	 */
	const br_ssl_server_policy_class **policy_vtable;
	uint16_t sign_hash_id;

	/*
	 * For the core handlers, thus avoiding (in most cases) the
	 * need for an externally provided policy context.
	 */
	union {
		const br_ssl_server_policy_class *vtable;
		br_ssl_server_policy_rsa_context single_rsa;
		br_ssl_server_policy_ec_context single_ec;
	} chain_handler;

	/*
	 * Buffer for the ECDHE private key.
	 */
	unsigned char ecdhe_key[70];
	size_t ecdhe_key_len;

	/*
	 * Trust anchor names for client authentication. "ta_names" and
	 * "tas" cannot be both non-NULL.
	 */
	const br_x500_name *ta_names;
	const br_x509_trust_anchor *tas;
	size_t num_tas;
	size_t cur_dn_index;
	const unsigned char *cur_dn;
	size_t cur_dn_len;

	/*
	 * Buffer for the hash value computed over all handshake messages
	 * prior to CertificateVerify, and identifier for the hash function.
	 */
	unsigned char hash_CV[64];
	size_t hash_CV_len;
	int hash_CV_id;

	/*
	 * Server-specific implementations.
	 * (none for now)
	 */
#endif
};

/*
 * Each br_ssl_server_init_xxx() function sets the list of supported
 * cipher suites and used implementations, as specified by the profile
 * name 'xxx'. Defined profile names are:
 *
 *    full_rsa    all supported algorithm, server key type is RSA
 *    full_ec     all supported algorithm, server key type is EC
 *    TODO: add other profiles
 *
 * Naming scheme for "minimal" profiles: min123
 *
 * -- character 1: key exchange
 *      r = RSA
 *      e = ECDHE_RSA
 *      f = ECDHE_ECDSA
 *      u = ECDH_RSA
 *      v = ECDH_ECDSA
 * -- character 2: version / PRF
 *      0 = TLS 1.0 / 1.1 with MD5+SHA-1
 *      2 = TLS 1.2 with SHA-256
 *      3 = TLS 1.2 with SHA-384
 * -- character 3: encryption
 *      a = AES/CBC
 *      d = 3DES/CBC
 *      g = AES/GCM
 *      c = ChaCha20+Poly1305
 */

/**
 * \brief SSL server profile: full_rsa.
 *
 * This function initialises the provided SSL server context with
 * all supported algorithms and cipher suites that rely on a RSA
 * key pair.
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          RSA private key.
 */
void br_ssl_server_init_full_rsa(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk);

/**
 * \brief SSL server profile: full_ec.
 *
 * This function initialises the provided SSL server context with
 * all supported algorithms and cipher suites that rely on an EC
 * key pair.
 *
 * The key type of the CA that issued the server's certificate must
 * be provided, since it matters for ECDH cipher suites (ECDH_RSA
 * suites require a RSA-powered CA). The key type is either
 * `BR_KEYTYPE_RSA` or `BR_KEYTYPE_EC`.
 *
 * \param cc                     server context to initialise.
 * \param chain                  server certificate chain.
 * \param chain_len              chain length (number of certificates).
 * \param cert_issuer_key_type   certificate issuer's key type.
 * \param sk                     EC private key.
 */
void br_ssl_server_init_full_ec(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	unsigned cert_issuer_key_type, const br_ec_private_key *sk);

/**
 * \brief SSL server profile: minr2g.
 *
 * This profile uses only TLS_RSA_WITH_AES_128_GCM_SHA256. Server key is
 * RSA, and RSA key exchange is used (not forward secure, but uses little
 * CPU in the client).
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          RSA private key.
 */
void br_ssl_server_init_minr2g(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk);

/**
 * \brief SSL server profile: mine2g.
 *
 * This profile uses only TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256. Server key
 * is RSA, and ECDHE key exchange is used. This suite provides forward
 * security, with a higher CPU expense on the client, and a somewhat
 * larger code footprint (compared to "minr2g").
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          RSA private key.
 */
void br_ssl_server_init_mine2g(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk);

/**
 * \brief SSL server profile: minf2g.
 *
 * This profile uses only TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256.
 * Server key is EC, and ECDHE key exchange is used. This suite provides
 * forward security, with a higher CPU expense on the client and server
 * (by a factor of about 3 to 4), and a somewhat larger code footprint
 * (compared to "minu2g" and "minv2g").
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          EC private key.
 */
void br_ssl_server_init_minf2g(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_ec_private_key *sk);

/**
 * \brief SSL server profile: minu2g.
 *
 * This profile uses only TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256.
 * Server key is EC, and ECDH key exchange is used; the issuing CA used
 * a RSA key.
 *
 * The "minu2g" and "minv2g" profiles do not provide forward secrecy,
 * but are the lightest on the server (for CPU usage), and are rather
 * inexpensive on the client as well.
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          EC private key.
 */
void br_ssl_server_init_minu2g(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_ec_private_key *sk);

/**
 * \brief SSL server profile: minv2g.
 *
 * This profile uses only TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256.
 * Server key is EC, and ECDH key exchange is used; the issuing CA used
 * an EC key.
 *
 * The "minu2g" and "minv2g" profiles do not provide forward secrecy,
 * but are the lightest on the server (for CPU usage), and are rather
 * inexpensive on the client as well.
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          EC private key.
 */
void br_ssl_server_init_minv2g(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_ec_private_key *sk);

/**
 * \brief SSL server profile: mine2c.
 *
 * This profile uses only TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256.
 * Server key is RSA, and ECDHE key exchange is used. This suite
 * provides forward security.
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          RSA private key.
 */
void br_ssl_server_init_mine2c(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk);

/**
 * \brief SSL server profile: minf2c.
 *
 * This profile uses only TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256.
 * Server key is EC, and ECDHE key exchange is used. This suite provides
 * forward security.
 *
 * \param cc          server context to initialise.
 * \param chain       server certificate chain.
 * \param chain_len   certificate chain length (number of certificate).
 * \param sk          EC private key.
 */
void br_ssl_server_init_minf2c(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_ec_private_key *sk);

/**
 * \brief Get the supported client suites.
 *
 * This function shall be called only after the ClientHello has been
 * processed, typically from the policy engine. The returned array
 * contains the cipher suites that are supported by both the client
 * and the server; these suites are in client preference order, unless
 * the `BR_OPT_ENFORCE_SERVER_PREFERENCES` flag was set, in which case
 * they are in server preference order.
 *
 * The suites are _translated_, which means that each suite is given
 * as two 16-bit integers: the standard suite identifier, and its
 * translated version, broken down into its individual components,
 * as explained with the `br_suite_translated` type.
 *
 * The returned array is allocated in the context and will be rewritten
 * by each handshake.
 *
 * \param cc    server context.
 * \param num   receives the array size (number of suites).
 * \return  the translated common cipher suites, in preference order.
 */
static inline const br_suite_translated *
br_ssl_server_get_client_suites(const br_ssl_server_context *cc, size_t *num)
{
	*num = cc->client_suites_num;
	return cc->client_suites;
}

/**
 * \brief Get the hash functions and signature algorithms supported by
 * the client.
 *
 * This value is a bit field:
 *
 *   - If RSA (PKCS#1 v1.5) is supported with hash function of ID `x`,
 *     then bit `x` is set (hash function ID is 0 for the special MD5+SHA-1,
 *     or 2 to 6 for the SHA family).
 *
 *   - If ECDSA is supported with hash function of ID `x`, then bit `8+x`
 *     is set.
 *
 *   - Newer algorithms are symbolic 16-bit identifiers that do not
 *     represent signature algorithm and hash function separately. If
 *     the TLS-level identifier is `0x0800+x` for a `x` in the 0..15
 *     range, then bit `16+x` is set.
 *
 * "New algorithms" are currently defined only in draft documents, so
 * this support is subject to possible change. Right now (early 2017),
 * this maps ed25519 (EdDSA on Curve25519) to bit 23, and ed448 (EdDSA
 * on Curve448) to bit 24. If the identifiers on the wire change in
 * future document, then the decoding mechanism in BearSSL will be
 * amended to keep mapping ed25519 and ed448 on bits 23 and 24,
 * respectively. Mapping of other new algorithms (e.g. RSA/PSS) is not
 * guaranteed yet.
 *
 * \param cc   server context.
 * \return  the client-supported hash functions and signature algorithms.
 */
static inline uint32_t
br_ssl_server_get_client_hashes(const br_ssl_server_context *cc)
{
	return cc->hashes;
}

/**
 * \brief Get the elliptic curves supported by the client.
 *
 * This is a bit field (bit x is set if curve of ID x is supported).
 *
 * \param cc   server context.
 * \return  the client-supported elliptic curves.
 */
static inline uint32_t
br_ssl_server_get_client_curves(const br_ssl_server_context *cc)
{
	return cc->curves;
}

/**
 * \brief Clear the complete contents of a SSL server context.
 *
 * Everything is cleared, including the reference to the configured buffer,
 * implementations, cipher suites and state. This is a preparatory step
 * to assembling a custom profile.
 *
 * \param cc   server context to clear.
 */
void br_ssl_server_zero(br_ssl_server_context *cc);

/**
 * \brief Set an externally provided policy context.
 *
 * The policy context's methods are invoked to decide the cipher suite
 * and certificate chain, and to perform operations involving the server's
 * private key.
 *
 * \param cc     server context.
 * \param pctx   policy context (pointer to its vtable field).
 */
static inline void
br_ssl_server_set_policy(br_ssl_server_context *cc,
	const br_ssl_server_policy_class **pctx)
{
	cc->policy_vtable = pctx;
}

/**
 * \brief Set the server certificate chain and key (single RSA case).
 *
 * This function uses a policy context included in the server context.
 * It configures use of a single server certificate chain with a RSA
 * private key. The `allowed_usages` is a combination of usages, namely
 * `BR_KEYTYPE_KEYX` and/or `BR_KEYTYPE_SIGN`; this enables or disables
 * the corresponding cipher suites (i.e. `TLS_RSA_*` use the RSA key for
 * key exchange, while `TLS_ECDHE_RSA_*` use the RSA key for signatures).
 *
 * \param cc               server context.
 * \param chain            server certificate chain to send to the client.
 * \param chain_len        chain length (number of certificates).
 * \param sk               server private key (RSA).
 * \param allowed_usages   allowed private key usages.
 * \param irsacore         RSA core implementation.
 * \param irsasign         RSA signature implementation (PKCS#1 v1.5).
 */
void br_ssl_server_set_single_rsa(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_rsa_private_key *sk, unsigned allowed_usages,
	br_rsa_private irsacore, br_rsa_pkcs1_sign irsasign);

/**
 * \brief Set the server certificate chain and key (single EC case).
 *
 * This function uses a policy context included in the server context.
 * It configures use of a single server certificate chain with an EC
 * private key. The `allowed_usages` is a combination of usages, namely
 * `BR_KEYTYPE_KEYX` and/or `BR_KEYTYPE_SIGN`; this enables or disables
 * the corresponding cipher suites (i.e. `TLS_ECDH_*` use the EC key for
 * key exchange, while `TLS_ECDHE_ECDSA_*` use the EC key for signatures).
 *
 * In order to support `TLS_ECDH_*` cipher suites (non-ephemeral ECDH),
 * the algorithm type of the key used by the issuing CA to sign the
 * server's certificate must be provided, as `cert_issuer_key_type`
 * parameter (this value is either `BR_KEYTYPE_RSA` or `BR_KEYTYPE_EC`).
 *
 * \param cc                     server context.
 * \param chain                  server certificate chain to send.
 * \param chain_len              chain length (number of certificates).
 * \param sk                     server private key (EC).
 * \param allowed_usages         allowed private key usages.
 * \param cert_issuer_key_type   issuing CA's key type.
 * \param iec                    EC core implementation.
 * \param iecdsa                 ECDSA signature implementation ("asn1" format).
 */
void br_ssl_server_set_single_ec(br_ssl_server_context *cc,
	const br_x509_certificate *chain, size_t chain_len,
	const br_ec_private_key *sk, unsigned allowed_usages,
	unsigned cert_issuer_key_type,
	const br_ec_impl *iec, br_ecdsa_sign iecdsa);

/**
 * \brief Activate client certificate authentication.
 *
 * The trust anchor encoded X.500 names (DN) to send to the client are
 * provided. A client certificate will be requested and validated through
 * the X.509 validator configured in the SSL engine. If `num` is 0, then
 * client certificate authentication is disabled.
 *
 * If the client does not send a certificate, or on validation failure,
 * the handshake aborts. Unauthenticated clients can be tolerated by
 * setting the `BR_OPT_TOLERATE_NO_CLIENT_AUTH` flag.
 *
 * The provided array is linked in, not copied, so that pointer must
 * remain valid as long as anchor names may be used.
 *
 * \param cc         server context.
 * \param ta_names   encoded trust anchor names.
 * \param num        number of encoded trust anchor names.
 */
static inline void
br_ssl_server_set_trust_anchor_names(br_ssl_server_context *cc,
	const br_x500_name *ta_names, size_t num)
{
	cc->ta_names = ta_names;
	cc->tas = NULL;
	cc->num_tas = num;
}

/**
 * \brief Activate client certificate authentication.
 *
 * This is a variant for `br_ssl_server_set_trust_anchor_names()`: the
 * trust anchor names are provided not as an array of stand-alone names
 * (`br_x500_name` structures), but as an array of trust anchors
 * (`br_x509_trust_anchor` structures). The server engine itself will
 * only use the `dn` field of each trust anchor. This is meant to allow
 * defining a single array of trust anchors, to be used here and in the
 * X.509 validation engine itself.
 *
 * The provided array is linked in, not copied, so that pointer must
 * remain valid as long as anchor names may be used.
 *
 * \param cc    server context.
 * \param tas   trust anchors (only names are used).
 * \param num   number of trust anchors.
 */
static inline void
br_ssl_server_set_trust_anchor_names_alt(br_ssl_server_context *cc,
	const br_x509_trust_anchor *tas, size_t num)
{
	cc->ta_names = NULL;
	cc->tas = tas;
	cc->num_tas = num;
}

/**
 * \brief Configure the cache for session parameters.
 *
 * The cache context is provided as a pointer to its first field (vtable
 * pointer).
 *
 * \param cc       server context.
 * \param vtable   session cache context.
 */
static inline void
br_ssl_server_set_cache(br_ssl_server_context *cc,
	const br_ssl_session_cache_class **vtable)
{
	cc->cache_vtable = vtable;
}

/**
 * \brief Prepare or reset a server context for handling an incoming client.
 *
 * \param cc   server context.
 * \return  1 on success, 0 on error.
 */
int br_ssl_server_reset(br_ssl_server_context *cc);

/* ===================================================================== */

/*
 * Context for the simplified I/O context. The transport medium is accessed
 * through the low_read() and low_write() callback functions, each with
 * its own opaque context pointer.
 *
 *  low_read()    read some bytes, at most 'len' bytes, into data[]. The
 *                returned value is the number of read bytes, or -1 on error.
 *                The 'len' parameter is guaranteed never to exceed 20000,
 *                so the length always fits in an 'int' on all platforms.
 *
 *  low_write()   write up to 'len' bytes, to be read from data[]. The
 *                returned value is the number of written bytes, or -1 on
 *                error. The 'len' parameter is guaranteed never to exceed
 *                20000, so the length always fits in an 'int' on all
 *                parameters.
 *
 * A socket closure (if the transport medium is a socket) should be reported
 * as an error (-1). The callbacks shall endeavour to block until at least
 * one byte can be read or written; a callback returning 0 at times is
 * acceptable, but this normally leads to the callback being immediately
 * called again, so the callback should at least always try to block for
 * some time if no I/O can take place.
 *
 * The SSL engine naturally applies some buffering, so the callbacks need
 * not apply buffers of their own.
 */
/**
 * \brief Context structure for the simplified SSL I/O wrapper.
 *
 * This structure is initialised with `br_sslio_init()`. Its contents
 * are opaque and shall not be accessed directly.
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	br_ssl_engine_context *engine;
	int (*low_read)(void *read_context,
		unsigned char *data, size_t len);
	void *read_context;
	int (*low_write)(void *write_context,
		const unsigned char *data, size_t len);
	void *write_context;
#endif
} br_sslio_context;

/**
 * \brief Initialise a simplified I/O wrapper context.
 *
 * The simplified I/O wrapper offers a simpler read/write API for a SSL
 * engine (client or server), using the provided callback functions for
 * reading data from, or writing data to, the transport medium.
 *
 * The callback functions have the following semantics:
 *
 *   - Each callback receives an opaque context value (of type `void *`)
 *     that the callback may use arbitrarily (or possibly ignore).
 *
 *   - `low_read()` reads at least one byte, at most `len` bytes, from
 *     the transport medium. Read bytes shall be written in `data`.
 *
 *   - `low_write()` writes at least one byte, at most `len` bytes, unto
 *     the transport medium. The bytes to write are read from `data`.
 *
 *   - The `len` parameter is never zero, and is always lower than 20000.
 *
 *   - The number of processed bytes (read or written) is returned. Since
 *     that number is less than 20000, it always fits on an `int`.
 *
 *   - On error, the callbacks return -1. Reaching end-of-stream is an
 *     error. Errors are permanent: the SSL connection is terminated.
 *
 *   - Callbacks SHOULD NOT return 0. This is tolerated, as long as
 *     callbacks endeavour to block for some non-negligible amount of
 *     time until at least one byte can be sent or received (if a
 *     callback returns 0, then the wrapper invokes it again
 *     immediately).
 *
 *   - Callbacks MAY return as soon as at least one byte is processed;
 *     they MAY also insist on reading or writing _all_ requested bytes.
 *     Since SSL is a self-terminated protocol (each record has a length
 *     header), this does not change semantics.
 *
 *   - Callbacks need not apply any buffering (for performance) since SSL
 *     itself uses buffers.
 *
 * \param ctx             wrapper context to initialise.
 * \param engine          SSL engine to wrap.
 * \param low_read        callback for reading data from the transport.
 * \param read_context    context pointer for `low_read()`.
 * \param low_write       callback for writing data on the transport.
 * \param write_context   context pointer for `low_write()`.
 */
void br_sslio_init(br_sslio_context *ctx,
	br_ssl_engine_context *engine,
	int (*low_read)(void *read_context,
		unsigned char *data, size_t len),
	void *read_context,
	int (*low_write)(void *write_context,
		const unsigned char *data, size_t len),
	void *write_context);

/**
 * \brief Read some application data from a SSL connection.
 *
 * If `len` is zero, then this function returns 0 immediately. In
 * all other cases, it never returns 0.
 *
 * This call returns only when at least one byte has been obtained.
 * Returned value is the number of bytes read, or -1 on error. The
 * number of bytes always fits on an 'int' (data from a single SSL/TLS
 * record is returned).
 *
 * On error or SSL closure, this function returns -1. The caller should
 * inspect the error status on the SSL engine to distinguish between
 * normal closure and error.
 *
 * \param cc    SSL wrapper context.
 * \param dst   destination buffer for application data.
 * \param len   maximum number of bytes to obtain.
 * \return  number of bytes obtained, or -1 on error.
 */
int br_sslio_read(br_sslio_context *cc, void *dst, size_t len);

/**
 * \brief Read application data from a SSL connection.
 *
 * This calls returns only when _all_ requested `len` bytes are read,
 * or an error is reached. Returned value is 0 on success, -1 on error.
 * A normal (verified) SSL closure before that many bytes are obtained
 * is reported as an error by this function.
 *
 * \param cc    SSL wrapper context.
 * \param dst   destination buffer for application data.
 * \param len   number of bytes to obtain.
 * \return  0 on success, or -1 on error.
 */
int br_sslio_read_all(br_sslio_context *cc, void *dst, size_t len);

/**
 * \brief Write some application data unto a SSL connection.
 *
 * If `len` is zero, then this function returns 0 immediately. In
 * all other cases, it never returns 0.
 *
 * This call returns only when at least one byte has been written.
 * Returned value is the number of bytes written, or -1 on error. The
 * number of bytes always fits on an 'int' (less than 20000).
 *
 * On error or SSL closure, this function returns -1. The caller should
 * inspect the error status on the SSL engine to distinguish between
 * normal closure and error.
 *
 * **Important:** SSL is buffered; a "written" byte is a byte that was
 * injected into the wrapped SSL engine, but this does not necessarily mean
 * that it has been scheduled for sending. Use `br_sslio_flush()` to
 * ensure that all pending data has been sent to the transport medium.
 *
 * \param cc    SSL wrapper context.
 * \param src   source buffer for application data.
 * \param len   maximum number of bytes to write.
 * \return  number of bytes written, or -1 on error.
 */
int br_sslio_write(br_sslio_context *cc, const void *src, size_t len);

/**
 * \brief Write application data unto a SSL connection.
 *
 * This calls returns only when _all_ requested `len` bytes have been
 * written, or an error is reached. Returned value is 0 on success, -1
 * on error. A normal (verified) SSL closure before that many bytes are
 * written is reported as an error by this function.
 *
 * **Important:** SSL is buffered; a "written" byte is a byte that was
 * injected into the wrapped SSL engine, but this does not necessarily mean
 * that it has been scheduled for sending. Use `br_sslio_flush()` to
 * ensure that all pending data has been sent to the transport medium.
 *
 * \param cc    SSL wrapper context.
 * \param src   source buffer for application data.
 * \param len   number of bytes to write.
 * \return  0 on success, or -1 on error.
 */
int br_sslio_write_all(br_sslio_context *cc, const void *src, size_t len);

/**
 * \brief Flush pending data.
 *
 * This call makes sure that any buffered application data in the
 * provided context (including the wrapped SSL engine) has been sent
 * to the transport medium (i.e. accepted by the `low_write()` callback
 * method). If there is no such pending data, then this function does
 * nothing (and returns a success, i.e. 0).
 *
 * If the underlying transport medium has its own buffers, then it is
 * up to the caller to ensure the corresponding flushing.
 *
 * Returned value is 0 on success, -1 on error.
 *
 * \param cc    SSL wrapper context.
 * \return  0 on success, or -1 on error.
 */
int br_sslio_flush(br_sslio_context *cc);

/**
 * \brief Close the SSL connection.
 *
 * This call runs the SSL closure protocol (sending a `close_notify`,
 * receiving the response `close_notify`). When it returns, the SSL
 * connection is finished. It is still up to the caller to manage the
 * possible transport-level termination, if applicable (alternatively,
 * the underlying transport stream may be reused for non-SSL messages).
 *
 * Returned value is 0 on success, -1 on error. A failure by the peer
 * to process the complete closure protocol (i.e. sending back the
 * `close_notify`) is an error.
 *
 * \param cc    SSL wrapper context.
 * \return  0 on success, or -1 on error.
 */
int br_sslio_close(br_sslio_context *cc);

/* ===================================================================== */

/*
 * Symbolic constants for cipher suites.
 */

/* From RFC 5246 */
#define BR_TLS_NULL_WITH_NULL_NULL                   0x0000
#define BR_TLS_RSA_WITH_NULL_MD5                     0x0001
#define BR_TLS_RSA_WITH_NULL_SHA                     0x0002
#define BR_TLS_RSA_WITH_NULL_SHA256                  0x003B
#define BR_TLS_RSA_WITH_RC4_128_MD5                  0x0004
#define BR_TLS_RSA_WITH_RC4_128_SHA                  0x0005
#define BR_TLS_RSA_WITH_3DES_EDE_CBC_SHA             0x000A
#define BR_TLS_RSA_WITH_AES_128_CBC_SHA              0x002F
#define BR_TLS_RSA_WITH_AES_256_CBC_SHA              0x0035
#define BR_TLS_RSA_WITH_AES_128_CBC_SHA256           0x003C
#define BR_TLS_RSA_WITH_AES_256_CBC_SHA256           0x003D
#define BR_TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA          0x000D
#define BR_TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA          0x0010
#define BR_TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA         0x0013
#define BR_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA         0x0016
#define BR_TLS_DH_DSS_WITH_AES_128_CBC_SHA           0x0030
#define BR_TLS_DH_RSA_WITH_AES_128_CBC_SHA           0x0031
#define BR_TLS_DHE_DSS_WITH_AES_128_CBC_SHA          0x0032
#define BR_TLS_DHE_RSA_WITH_AES_128_CBC_SHA          0x0033
#define BR_TLS_DH_DSS_WITH_AES_256_CBC_SHA           0x0036
#define BR_TLS_DH_RSA_WITH_AES_256_CBC_SHA           0x0037
#define BR_TLS_DHE_DSS_WITH_AES_256_CBC_SHA          0x0038
#define BR_TLS_DHE_RSA_WITH_AES_256_CBC_SHA          0x0039
#define BR_TLS_DH_DSS_WITH_AES_128_CBC_SHA256        0x003E
#define BR_TLS_DH_RSA_WITH_AES_128_CBC_SHA256        0x003F
#define BR_TLS_DHE_DSS_WITH_AES_128_CBC_SHA256       0x0040
#define BR_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256       0x0067
#define BR_TLS_DH_DSS_WITH_AES_256_CBC_SHA256        0x0068
#define BR_TLS_DH_RSA_WITH_AES_256_CBC_SHA256        0x0069
#define BR_TLS_DHE_DSS_WITH_AES_256_CBC_SHA256       0x006A
#define BR_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256       0x006B
#define BR_TLS_DH_anon_WITH_RC4_128_MD5              0x0018
#define BR_TLS_DH_anon_WITH_3DES_EDE_CBC_SHA         0x001B
#define BR_TLS_DH_anon_WITH_AES_128_CBC_SHA          0x0034
#define BR_TLS_DH_anon_WITH_AES_256_CBC_SHA          0x003A
#define BR_TLS_DH_anon_WITH_AES_128_CBC_SHA256       0x006C
#define BR_TLS_DH_anon_WITH_AES_256_CBC_SHA256       0x006D

/* From RFC 4492 */
#define BR_TLS_ECDH_ECDSA_WITH_NULL_SHA              0xC001
#define BR_TLS_ECDH_ECDSA_WITH_RC4_128_SHA           0xC002
#define BR_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA      0xC003
#define BR_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA       0xC004
#define BR_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA       0xC005
#define BR_TLS_ECDHE_ECDSA_WITH_NULL_SHA             0xC006
#define BR_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA          0xC007
#define BR_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA     0xC008
#define BR_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA      0xC009
#define BR_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA      0xC00A
#define BR_TLS_ECDH_RSA_WITH_NULL_SHA                0xC00B
#define BR_TLS_ECDH_RSA_WITH_RC4_128_SHA             0xC00C
#define BR_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA        0xC00D
#define BR_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA         0xC00E
#define BR_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA         0xC00F
#define BR_TLS_ECDHE_RSA_WITH_NULL_SHA               0xC010
#define BR_TLS_ECDHE_RSA_WITH_RC4_128_SHA            0xC011
#define BR_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA       0xC012
#define BR_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA        0xC013
#define BR_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA        0xC014
#define BR_TLS_ECDH_anon_WITH_NULL_SHA               0xC015
#define BR_TLS_ECDH_anon_WITH_RC4_128_SHA            0xC016
#define BR_TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA       0xC017
#define BR_TLS_ECDH_anon_WITH_AES_128_CBC_SHA        0xC018
#define BR_TLS_ECDH_anon_WITH_AES_256_CBC_SHA        0xC019

/* From RFC 5288 */
#define BR_TLS_RSA_WITH_AES_128_GCM_SHA256           0x009C
#define BR_TLS_RSA_WITH_AES_256_GCM_SHA384           0x009D
#define BR_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256       0x009E
#define BR_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384       0x009F
#define BR_TLS_DH_RSA_WITH_AES_128_GCM_SHA256        0x00A0
#define BR_TLS_DH_RSA_WITH_AES_256_GCM_SHA384        0x00A1
#define BR_TLS_DHE_DSS_WITH_AES_128_GCM_SHA256       0x00A2
#define BR_TLS_DHE_DSS_WITH_AES_256_GCM_SHA384       0x00A3
#define BR_TLS_DH_DSS_WITH_AES_128_GCM_SHA256        0x00A4
#define BR_TLS_DH_DSS_WITH_AES_256_GCM_SHA384        0x00A5
#define BR_TLS_DH_anon_WITH_AES_128_GCM_SHA256       0x00A6
#define BR_TLS_DH_anon_WITH_AES_256_GCM_SHA384       0x00A7

/* From RFC 5289 */
#define BR_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256   0xC023
#define BR_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384   0xC024
#define BR_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256    0xC025
#define BR_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384    0xC026
#define BR_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256     0xC027
#define BR_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384     0xC028
#define BR_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256      0xC029
#define BR_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384      0xC02A
#define BR_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256   0xC02B
#define BR_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384   0xC02C
#define BR_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256    0xC02D
#define BR_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384    0xC02E
#define BR_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256     0xC02F
#define BR_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384     0xC030
#define BR_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256      0xC031
#define BR_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384      0xC032

/* From RFC 6655 and 7251 */
#define BR_TLS_RSA_WITH_AES_128_CCM                  0xC09C
#define BR_TLS_RSA_WITH_AES_256_CCM                  0xC09D
#define BR_TLS_RSA_WITH_AES_128_CCM_8                0xC0A0
#define BR_TLS_RSA_WITH_AES_256_CCM_8                0xC0A1
#define BR_TLS_ECDHE_ECDSA_WITH_AES_128_CCM          0xC0AC
#define BR_TLS_ECDHE_ECDSA_WITH_AES_256_CCM          0xC0AD
#define BR_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8        0xC0AE
#define BR_TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8        0xC0AF

/* From RFC 7905 */
#define BR_TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256     0xCCA8
#define BR_TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256   0xCCA9
#define BR_TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256       0xCCAA
#define BR_TLS_PSK_WITH_CHACHA20_POLY1305_SHA256           0xCCAB
#define BR_TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256     0xCCAC
#define BR_TLS_DHE_PSK_WITH_CHACHA20_POLY1305_SHA256       0xCCAD
#define BR_TLS_RSA_PSK_WITH_CHACHA20_POLY1305_SHA256       0xCCAE

/* From RFC 7507 */
#define BR_TLS_FALLBACK_SCSV                         0x5600

/*
 * Symbolic constants for alerts.
 */
#define BR_ALERT_CLOSE_NOTIFY                0
#define BR_ALERT_UNEXPECTED_MESSAGE         10
#define BR_ALERT_BAD_RECORD_MAC             20
#define BR_ALERT_RECORD_OVERFLOW            22
#define BR_ALERT_DECOMPRESSION_FAILURE      30
#define BR_ALERT_HANDSHAKE_FAILURE          40
#define BR_ALERT_BAD_CERTIFICATE            42
#define BR_ALERT_UNSUPPORTED_CERTIFICATE    43
#define BR_ALERT_CERTIFICATE_REVOKED        44
#define BR_ALERT_CERTIFICATE_EXPIRED        45
#define BR_ALERT_CERTIFICATE_UNKNOWN        46
#define BR_ALERT_ILLEGAL_PARAMETER          47
#define BR_ALERT_UNKNOWN_CA                 48
#define BR_ALERT_ACCESS_DENIED              49
#define BR_ALERT_DECODE_ERROR               50
#define BR_ALERT_DECRYPT_ERROR              51
#define BR_ALERT_PROTOCOL_VERSION           70
#define BR_ALERT_INSUFFICIENT_SECURITY      71
#define BR_ALERT_INTERNAL_ERROR             80
#define BR_ALERT_USER_CANCELED              90
#define BR_ALERT_NO_RENEGOTIATION          100
#define BR_ALERT_UNSUPPORTED_EXTENSION     110
#define BR_ALERT_NO_APPLICATION_PROTOCOL   120

#ifdef __cplusplus
}
#endif

#endif


/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BR_BEARSSL_PEM_H__
#define BR_BEARSSL_PEM_H__

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file bearssl_pem.h
 *
 * # PEM Support
 *
 * PEM is a traditional encoding layer use to store binary objects (in
 * particular X.509 certificates, and private keys) in text files. While
 * the acronym comes from an old, defunct standard ("Privacy Enhanced
 * Mail"), the format has been reused, with some variations, by many
 * systems, and is a _de facto_ standard, even though it is not, actually,
 * specified in all clarity anywhere.
 *
 * ## Format Details
 *
 * BearSSL contains a generic, streamed PEM decoder, which handles the
 * following format:
 *
 *   - The input source (a sequence of bytes) is assumed to be the
 *     encoding of a text file in an ASCII-compatible charset. This
 *     includes ISO-8859-1, Windows-1252, and UTF-8 encodings. Each
 *     line ends on a newline character (U+000A LINE FEED). The
 *     U+000D CARRIAGE RETURN characters are ignored, so the code
 *     accepts both Windows-style and Unix-style line endings.
 *
 *   - Each object begins with a banner that occurs at the start of
 *     a line; the first banner characters are "`-----BEGIN `" (five
 *     dashes, the word "BEGIN", and a space). The banner matching is
 *     not case-sensitive.
 *
 *   - The _object name_ consists in the characters that follow the
 *     banner start sequence, up to the end of the line, but without
 *     trailing dashes (in "normal" PEM, there are five trailing
 *     dashes, but this implementation is not picky about these dashes).
 *     The BearSSL decoder normalises the name characters to uppercase
 *     (for ASCII letters only) and accepts names up to 127 characters.
 *
 *   - The object ends with a banner that again occurs at the start of
 *     a line, and starts with "`-----END `" (again case-insensitive).
 *
 *   - Between that start and end banner, only Base64 data shall occur.
 *     Base64 converts each sequence of three bytes into four
 *     characters; the four characters are ASCII letters, digits, "`+`"
 *     or "`-`" signs, and one or two "`=`" signs may occur in the last
 *     quartet. Whitespace is ignored (whitespace is any ASCII character
 *     of code 32 or less, so control characters are whitespace) and
 *     lines may have arbitrary length; the only restriction is that the
 *     four characters of a quartet must appear on the same line (no
 *     line break inside a quartet).
 *
 *   - A single file may contain more than one PEM object. Bytes that
 *     occur between objects are ignored.
 *
 *
 * ## PEM Decoder API
 *
 * The PEM decoder offers a state-machine API. The caller allocates a
 * decoder context, then injects source bytes. Source bytes are pushed
 * with `br_pem_decoder_push()`. The decoder stops accepting bytes when
 * it reaches an "event", which is either the start of an object, the
 * end of an object, or a decoding error within an object.
 *
 * The `br_pem_decoder_event()` function is used to obtain the current
 * event; it also clears it, thus allowing the decoder to accept more
 * bytes. When a object start event is raised, the decoder context
 * offers the found object name (normalised to ASCII uppercase).
 *
 * When an object is reached, the caller must set an appropriate callback
 * function, which will receive (by chunks) the decoded object data.
 *
 * Since the decoder context makes no dynamic allocation, it requires
 * no explicit deallocation.
 */

/**
 * \brief PEM decoder context.
 *
 * Contents are opaque (they should not be accessed directly).
 */
typedef struct {
#ifndef BR_DOXYGEN_IGNORE
	/* CPU for the T0 virtual machine. */
	struct {
		uint32_t *dp;
		uint32_t *rp;
		const unsigned char *ip;
	} cpu;
	uint32_t dp_stack[32];
	uint32_t rp_stack[32];
	int err;

	const unsigned char *hbuf;
	size_t hlen;

	void (*dest)(void *dest_ctx, const void *src, size_t len);
	void *dest_ctx;

	unsigned char event;
	char name[128];
	unsigned char buf[255];
	size_t ptr;
#endif
} br_pem_decoder_context;

/**
 * \brief Initialise a PEM decoder structure.
 *
 * \param ctx   decoder context to initialise.
 */
void br_pem_decoder_init(br_pem_decoder_context *ctx);

/**
 * \brief Push some bytes into the decoder.
 *
 * Returned value is the number of bytes actually consumed; this may be
 * less than the number of provided bytes if an event is raised. When an
 * event is raised, it must be read (with `br_pem_decoder_event()`);
 * until the event is read, this function will return 0.
 *
 * \param ctx    decoder context.
 * \param data   new data bytes.
 * \param len    number of new data bytes.
 * \return  the number of bytes actually received (may be less than `len`).
 */
size_t br_pem_decoder_push(br_pem_decoder_context *ctx,
	const void *data, size_t len);

/**
 * \brief Set the receiver for decoded data.
 *
 * When an object is entered, the provided function (with opaque context
 * pointer) will be called repeatedly with successive chunks of decoded
 * data for that object. If `dest` is set to 0, then decoded data is
 * simply ignored. The receiver can be set at any time, but, in practice,
 * it should be called immediately after receiving a "start of object"
 * event.
 *
 * \param ctx        decoder context.
 * \param dest       callback for receiving decoded data.
 * \param dest_ctx   opaque context pointer for the `dest` callback.
 */
static inline void
br_pem_decoder_setdest(br_pem_decoder_context *ctx,
	void (*dest)(void *dest_ctx, const void *src, size_t len),
	void *dest_ctx)
{
	ctx->dest = dest;
	ctx->dest_ctx = dest_ctx;
}

/**
 * \brief Get the last event.
 *
 * If an event was raised, then this function returns the event value, and
 * also clears it, thereby allowing the decoder to proceed. If no event
 * was raised since the last call to `br_pem_decoder_event()`, then this
 * function returns 0.
 *
 * \param ctx   decoder context.
 * \return  the raised event, or 0.
 */
int br_pem_decoder_event(br_pem_decoder_context *ctx);

/**
 * \brief Event: start of object.
 *
 * This event is raised when the start of a new object has been detected.
 * The object name (normalised to uppercase) can be accessed with
 * `br_pem_decoder_name()`.
 */
#define BR_PEM_BEGIN_OBJ   1

/**
 * \brief Event: end of object.
 *
 * This event is raised when the end of the current object is reached
 * (normally, i.e. with no decoding error).
 */
#define BR_PEM_END_OBJ     2

/**
 * \brief Event: decoding error.
 *
 * This event is raised when decoding fails within an object.
 * This formally closes the current object and brings the decoder back
 * to the "out of any object" state. The offending line in the source
 * is consumed.
 */
#define BR_PEM_ERROR       3

/**
 * \brief Get the name of the encountered object.
 *
 * The encountered object name is defined only when the "start of object"
 * event is raised. That name is normalised to uppercase (for ASCII letters
 * only) and does not include trailing dashes.
 *
 * \param ctx   decoder context.
 * \return  the current object name.
 */
static inline const char *
br_pem_decoder_name(br_pem_decoder_context *ctx)
{
	return ctx->name;
}

/**
 * \brief Encode an object in PEM.
 *
 * This function encodes the provided binary object (`data`, of length `len`
 * bytes) into PEM. The `banner` text will be included in the header and
 * footer (e.g. use `"CERTIFICATE"` to get a `"BEGIN CERTIFICATE"` header).
 *
 * The length (in characters) of the PEM output is returned; that length
 * does NOT include the terminating zero, that this function nevertheless
 * adds. If using the returned value for allocation purposes, the allocated
 * buffer size MUST be at least one byte larger than the returned size.
 *
 * If `dest` is `NULL`, then the encoding does not happen; however, the
 * length of the encoded object is still computed and returned.
 *
 * The `data` pointer may be `NULL` only if `len` is zero (when encoding
 * an object of length zero, which is not very useful), or when `dest`
 * is `NULL` (in that case, source data bytes are ignored).
 *
 * Some `flags` can be specified to alter the encoding behaviour:
 *
 *   - If `BR_PEM_LINE64` is set, then line-breaking will occur after
 *     every 64 characters of output, instead of the default of 76.
 *
 *   - If `BR_PEM_CRLF` is set, then end-of-line sequence will use
 *     CR+LF instead of a single LF.
 *
 * The `data` and `dest` buffers may overlap, in which case the source
 * binary data is destroyed in the process. Note that the PEM-encoded output
 * is always larger than the source binary.
 *
 * \param dest     the destination buffer (or `NULL`).
 * \param data     the source buffer (can be `NULL` in some cases).
 * \param len      the source length (in bytes).
 * \param banner   the PEM banner expression.
 * \param flags    the behavioural flags.
 * \return  the PEM object length (in characters), EXCLUDING the final zero.
 */
size_t br_pem_encode(void *dest, const void *data, size_t len,
	const char *banner, unsigned flags);

/**
 * \brief PEM encoding flag: split lines at 64 characters.
 */
#define BR_PEM_LINE64   0x0001

/**
 * \brief PEM encoding flag: use CR+LF line endings.
 */
#define BR_PEM_CRLF     0x0002

#ifdef __cplusplus
}
#endif

#endif


#ifdef __cplusplus
extern "C" {
#endif

/** \brief Type for a configuration option.
 *
 * A "configuration option" is a value that is selected when the BearSSL
 * library itself is compiled. Most options are boolean; their value is
 * then either 1 (option is enabled) or 0 (option is disabled). Some
 * values have other integer values. Option names correspond to macro
 * names. Some of the options can be explicitly set in the internal
 * `"config.h"` file.
 */
typedef struct {
	/** \brief Configurable option name. */
	const char *name;
	/** \brief Configurable option value. */
	long value;
} br_config_option;

/** \brief Get configuration report.
 *
 * This function returns compiled configuration options, each as a
 * 'long' value. Names match internal macro names, in particular those
 * that can be set in the `"config.h"` inner file. For boolean options,
 * the numerical value is 1 if enabled, 0 if disabled. For maximum
 * key sizes, values are expressed in bits.
 *
 * The returned array is terminated by an entry whose `name` is `NULL`.
 *
 * \return  the configuration report.
 */
const br_config_option *br_get_config(void);

/* ======================================================================= */

/** \brief Version feature: support for time callback. */
#define BR_FEATURE_X509_TIME_CALLBACK   1

#ifdef __cplusplus
}
#endif

#endif


/*
 * On MSVC, disable the warning about applying unary minus on an
 * unsigned type: it is standard, we do it all the time, and for
 * good reasons.
 */
#if _MSC_VER
#pragma warning( disable : 4146 )
#endif

/*
 * Maximum size for a RSA modulus (in bits). Allocated stack buffers
 * depend on that size, so this value should be kept small. Currently,
 * 2048-bit RSA keys offer adequate security, and should still do so for
 * the next few decades; however, a number of widespread PKI have
 * already set their root keys to RSA-4096, so we should be able to
 * process such keys.
 *
 * This value MUST be a multiple of 64. This value MUST NOT exceed 47666
 * (some computations in RSA key generation rely on the factor size being
 * no more than 23833 bits). RSA key sizes beyond 3072 bits don't make a
 * lot of sense anyway.
 */
#define BR_MAX_RSA_SIZE   4096

/*
 * Minimum size for a RSA modulus (in bits); this value is used only to
 * filter out invalid parameters for key pair generation. Normally,
 * applications should not use RSA keys smaller than 2048 bits; but some
 * specific cases might need shorter keys, for legacy or research
 * purposes.
 */
#define BR_MIN_RSA_SIZE   512

/*
 * Maximum size for a RSA factor (in bits). This is for RSA private-key
 * operations. Default is to support factors up to a bit more than half
 * the maximum modulus size.
 *
 * This value MUST be a multiple of 32.
 */
#define BR_MAX_RSA_FACTOR   ((BR_MAX_RSA_SIZE + 64) >> 1)

/*
 * Maximum size for an EC curve (modulus or order), in bits. Size of
 * stack buffers depends on that parameter. This size MUST be a multiple
 * of 8 (so that decoding an integer with that many bytes does not
 * overflow).
 */
#define BR_MAX_EC_SIZE   528

/*
 * Some macros to recognize the current architecture. Right now, we are
 * interested into automatically recognizing architecture with efficient
 * 64-bit types so that we may automatically use implementations that
 * use 64-bit registers in that case. Future versions may detect, e.g.,
 * availability of SSE2 intrinsics.
 *
 * If 'unsigned long' is a 64-bit type, then we assume that 64-bit types
 * are efficient. Otherwise, we rely on macros that depend on compiler,
 * OS and architecture. In any case, failure to detect the architecture
 * as 64-bit means that the 32-bit code will be used, and that code
 * works also on 64-bit architectures (the 64-bit code may simply be
 * more efficient).
 *
 * The test on 'unsigned long' should already catch most cases, the one
 * notable exception being Windows code where 'unsigned long' is kept to
 * 32-bit for compatibility with all the legacy code that liberally uses
 * the 'DWORD' type for 32-bit values.
 *
 * Macro names are taken from: http://nadeausoftware.com/articles/2012/02/c_c_tip_how_detect_processor_type_using_compiler_predefined_macros
 */
#ifndef BR_64
#if ((ULONG_MAX >> 31) >> 31) == 3
#define BR_64   1
#elif defined(__ia64) || defined(__itanium__) || defined(_M_IA64)
#define BR_64   1
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) \
	|| defined(__64BIT__) || defined(_LP64) || defined(__LP64__)
#define BR_64   1
#elif defined(__sparc64__)
#define BR_64   1
#elif defined(__x86_64__) || defined(_M_X64)
#define BR_64   1
#elif defined(__aarch64__) || defined(_M_ARM64)
#define BR_64   1
#elif defined(__mips64)
#define BR_64   1
#endif
#endif

/*
 * Set BR_LOMUL on platforms where it makes sense.
 */
#ifndef BR_LOMUL
#if BR_ARMEL_CORTEXM_GCC
#define BR_LOMUL   1
#endif
#endif

/*
 * Architecture detection.
 */
#ifndef BR_i386
#if __i386__ || _M_IX86
#define BR_i386   1
#endif
#endif

#ifndef BR_amd64
#if __x86_64__ || _M_X64
#define BR_amd64   1
#endif
#endif

/*
 * Compiler brand and version.
 *
 * Implementations that use intrinsics need to detect the compiler type
 * and version because some specific actions may be needed to activate
 * the corresponding opcodes, both for header inclusion, and when using
 * them in a function.
 *
 * BR_GCC, BR_CLANG and BR_MSC will be set to 1 for, respectively, GCC,
 * Clang and MS Visual C. For each of them, sub-macros will be defined
 * for versions; each sub-macro is set whenever the compiler version is
 * at least as recent as the one corresponding to the macro.
 */

/*
 * GCC thresholds are on versions 4.4 to 4.9 and 5.0.
 */
#ifndef BR_GCC
#if __GNUC__ && !__clang__
#define BR_GCC   1

#if __GNUC__ > 4
#define BR_GCC_5_0   1
#elif __GNUC__ == 4 && __GNUC_MINOR__ >= 9
#define BR_GCC_4_9   1
#elif __GNUC__ == 4 && __GNUC_MINOR__ >= 8
#define BR_GCC_4_8   1
#elif __GNUC__ == 4 && __GNUC_MINOR__ >= 7
#define BR_GCC_4_7   1
#elif __GNUC__ == 4 && __GNUC_MINOR__ >= 6
#define BR_GCC_4_6   1
#elif __GNUC__ == 4 && __GNUC_MINOR__ >= 5
#define BR_GCC_4_5   1
#elif __GNUC__ == 4 && __GNUC_MINOR__ >= 4
#define BR_GCC_4_4   1
#endif

#if BR_GCC_5_0
#define BR_GCC_4_9   1
#endif
#if BR_GCC_4_9
#define BR_GCC_4_8   1
#endif
#if BR_GCC_4_8
#define BR_GCC_4_7   1
#endif
#if BR_GCC_4_7
#define BR_GCC_4_6   1
#endif
#if BR_GCC_4_6
#define BR_GCC_4_5   1
#endif
#if BR_GCC_4_5
#define BR_GCC_4_4   1
#endif

#endif
#endif

/*
 * Clang thresholds are on versions 3.7.0 and 3.8.0.
 */
#ifndef BR_CLANG
#if __clang__
#define BR_CLANG   1

#if __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 8)
#define BR_CLANG_3_8   1
#elif __clang_major__ == 3 && __clang_minor__ >= 7
#define BR_CLANG_3_7   1
#endif

#if BR_CLANG_3_8
#define BR_CLANG_3_7   1
#endif

#endif
#endif

/*
 * MS Visual C thresholds are on Visual Studio 2005 to 2015.
 */
#ifndef BR_MSC
#if _MSC_VER
#define BR_MSC   1

#if _MSC_VER >= 1900
#define BR_MSC_2015   1
#elif _MSC_VER >= 1800
#define BR_MSC_2013   1
#elif _MSC_VER >= 1700
#define BR_MSC_2012   1
#elif _MSC_VER >= 1600
#define BR_MSC_2010   1
#elif _MSC_VER >= 1500
#define BR_MSC_2008   1
#elif _MSC_VER >= 1400
#define BR_MSC_2005   1
#endif

#if BR_MSC_2015
#define BR_MSC_2013   1
#endif
#if BR_MSC_2013
#define BR_MSC_2012   1
#endif
#if BR_MSC_2012
#define BR_MSC_2010   1
#endif
#if BR_MSC_2010
#define BR_MSC_2008   1
#endif
#if BR_MSC_2008
#define BR_MSC_2005   1
#endif

#endif
#endif

/*
 * GCC 4.4+ and Clang 3.7+ allow tagging specific functions with a
 * 'target' attribute that activates support for specific opcodes.
 */
#if BR_GCC_4_4 || BR_CLANG_3_7
#define BR_TARGET(x)   __attribute__((target(x)))
#else
#define BR_TARGET(x)
#endif

/*
 * AES-NI intrinsics are available on x86 (32-bit and 64-bit) with
 * GCC 4.8+, Clang 3.7+ and MSC 2012+.
 */
#ifndef BR_AES_X86NI
#if (BR_i386 || BR_amd64) && (BR_GCC_4_8 || BR_CLANG_3_7 || BR_MSC_2012)
#define BR_AES_X86NI   1
#endif
#endif

/*
 * SSE2 intrinsics are available on x86 (32-bit and 64-bit) with
 * GCC 4.4+, Clang 3.7+ and MSC 2005+.
 */
#ifndef BR_SSE2
#if (BR_i386 || BR_amd64) && (BR_GCC_4_4 || BR_CLANG_3_7 || BR_MSC_2005)
#define BR_SSE2   1
#endif
#endif

/*
 * RDRAND intrinsics are available on x86 (32-bit and 64-bit) with
 * GCC 4.6+, Clang 3.7+ and MSC 2012+.
 */
#ifndef BR_RDRAND
#if (BR_i386 || BR_amd64) && (BR_GCC_4_6 || BR_CLANG_3_7 || BR_MSC_2012)
#define BR_RDRAND   1
#endif
#endif

/*
 * Determine type of OS for random number generation. Macro names and
 * values are documented on:
 *    https://sourceforge.net/p/predef/wiki/OperatingSystems/
 *
 * Win32's CryptGenRandom() should be available on Windows systems.
 *
 * /dev/urandom should work on all Unix-like systems (including macOS X).
 *
 * getentropy() is present on Linux (Glibc 2.25+), FreeBSD (12.0+) and
 * OpenBSD (5.6+). For OpenBSD, there does not seem to be easy to use
 * macros to test the minimum version, so we just assume that it is
 * recent enough (last version without getentropy() has gone out of
 * support in May 2015).
 *
 * Ideally we should use getentropy() on macOS (10.12+) too, but I don't
 * know how to test the exact OS version with preprocessor macros.
 *
 * TODO: enrich the list of detected system.
 */

#ifndef BR_USE_URANDOM
#if defined _AIX \
	|| defined __ANDROID__ \
	|| defined __FreeBSD__ \
	|| defined __NetBSD__ \
	|| defined __OpenBSD__ \
	|| defined __DragonFly__ \
	|| defined __linux__ \
	|| (defined __sun && (defined __SVR4 || defined __svr4__)) \
	|| (defined __APPLE__ && defined __MACH__)
#define BR_USE_URANDOM   1
#endif
#endif

#ifndef BR_USE_GETENTROPY
#if (defined __linux__ \
	&& (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 25))) \
	|| (defined __FreeBSD__ && __FreeBSD__ >= 12) \
	|| defined __OpenBSD__
#define BR_USE_GETENTROPY   1
#endif
#endif

#ifndef BR_USE_WIN32_RAND
#if defined _WIN32 || defined _WIN64
#define BR_USE_WIN32_RAND   1
#endif
#endif

/*
 * POWER8 crypto support. We rely on compiler macros for the
 * architecture, since we do not have a reliable, simple way to detect
 * the required support at runtime (we could try running an opcode, and
 * trapping the exception or signal on illegal instruction, but this
 * induces some non-trivial OS dependencies that we would prefer to
 * avoid if possible).
 */
#ifndef BR_POWER8
#if __GNUC__ && ((_ARCH_PWR8 || _ARCH_PPC) && __CRYPTO__)
#define BR_POWER8   1
#endif
#endif

/*
 * Detect endinanness on POWER8.
 */
#if BR_POWER8
#if defined BR_POWER8_LE
#undef BR_POWER8_BE
#if BR_POWER8_LE
#define BR_POWER8_BE   0
#else
#define BR_POWER8_BE   1
#endif
#elif defined BR_POWER8_BE
#undef BR_POWER8_LE
#if BR_POWER8_BE
#define BR_POWER8_LE   0
#else
#define BR_POWER8_LE   1
#endif
#else
#if __LITTLE_ENDIAN__
#define BR_POWER8_LE   1
#define BR_POWER8_BE   0
#else
#define BR_POWER8_LE   0
#define BR_POWER8_BE   1
#endif
#endif
#endif

/*
 * Detect support for 128-bit integers.
 */
#if !defined BR_INT128 && !defined BR_UMUL128
#ifdef __SIZEOF_INT128__
#define BR_INT128    1
#elif _M_X64
#define BR_UMUL128   1
#endif
#endif

/*
 * Detect support for unaligned accesses with known endianness.
 *
 *  x86 (both 32-bit and 64-bit) is little-endian and allows unaligned
 *  accesses.
 *
 *  POWER/PowerPC allows unaligned accesses when big-endian. POWER8 and
 *  later also allow unaligned accesses when little-endian.
 */
#if !defined BR_LE_UNALIGNED && !defined BR_BE_UNALIGNED

#if __i386 || __i386__ || __x86_64__ || _M_IX86 || _M_X64
#define BR_LE_UNALIGNED   1
#elif BR_POWER8_BE
#define BR_BE_UNALIGNED   1
#elif BR_POWER8_LE
#define BR_LE_UNALIGNED   1
#elif (__powerpc__ || __powerpc64__ || _M_PPC || _ARCH_PPC || _ARCH_PPC64) \
	&& __BIG_ENDIAN__
#define BR_BE_UNALIGNED   1
#endif

#endif

/*
 * Detect support for an OS-provided time source.
 */

#ifndef BR_USE_UNIX_TIME
#if defined __unix__ || defined __linux__ \
	|| defined _POSIX_SOURCE || defined _POSIX_C_SOURCE \
	|| (defined __APPLE__ && defined __MACH__)
#define BR_USE_UNIX_TIME   1
#endif
#endif

#ifndef BR_USE_WIN32_TIME
#if defined _WIN32 || defined _WIN64
#define BR_USE_WIN32_TIME   1
#endif
#endif

/* ==================================================================== */
/*
 * Encoding/decoding functions.
 *
 * 32-bit and 64-bit decoding, both little-endian and big-endian, is
 * implemented with the inline functions below.
 *
 * When allowed by some compile-time options (autodetected or provided),
 * optimised code is used, to perform direct memory access when the
 * underlying architecture supports it, both for endianness and
 * alignment. This, however, may trigger strict aliasing issues; the
 * code below uses unions to perform (supposedly) safe type punning.
 * Since the C aliasing rules are relatively complex and were amended,
 * or at least re-explained with different phrasing, in all successive
 * versions of the C standard, it is always a bit risky to bet that any
 * specific version of a C compiler got it right, for some notion of
 * "right".
 */

typedef union {
	uint16_t u;
	unsigned char b[sizeof(uint16_t)];
} br_union_u16;

typedef union {
	uint32_t u;
	unsigned char b[sizeof(uint32_t)];
} br_union_u32;

typedef union {
	uint64_t u;
	unsigned char b[sizeof(uint64_t)];
} br_union_u64;

static inline void
br_enc16le(void *dst, unsigned x)
{
#if BR_LE_UNALIGNED
	((br_union_u16 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = (unsigned char*)dst;
	buf[0] = (unsigned char)x;
	buf[1] = (unsigned char)(x >> 8);
#endif
}

static inline void
br_enc16be(void *dst, unsigned x)
{
#if BR_BE_UNALIGNED
	((br_union_u16 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = (unsigned char*)dst;
	buf[0] = (unsigned char)(x >> 8);
	buf[1] = (unsigned char)x;
#endif
}

static inline unsigned
br_dec16le(const void *src)
{
#if BR_LE_UNALIGNED
	return ((const br_union_u16 *)src)->u;
#else
	const unsigned char *buf;

	buf = (const unsigned char*)src;
	return (unsigned)buf[0] | ((unsigned)buf[1] << 8);
#endif
}

static inline unsigned
br_dec16be(const void *src)
{
#if BR_BE_UNALIGNED
	return ((const br_union_u16 *)src)->u;
#else
	const unsigned char *buf;

	buf = (const unsigned char*)src;
	return ((unsigned)buf[0] << 8) | (unsigned)buf[1];
#endif
}

static inline void
br_enc32le(void *dst, uint32_t x)
{
#if BR_LE_UNALIGNED
	((br_union_u32 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = (unsigned char*)dst;
	buf[0] = (unsigned char)x;
	buf[1] = (unsigned char)(x >> 8);
	buf[2] = (unsigned char)(x >> 16);
	buf[3] = (unsigned char)(x >> 24);
#endif
}

static inline void
br_enc32be(void *dst, uint32_t x)
{
#if BR_BE_UNALIGNED
	((br_union_u32 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = (unsigned char*)dst;
	buf[0] = (unsigned char)(x >> 24);
	buf[1] = (unsigned char)(x >> 16);
	buf[2] = (unsigned char)(x >> 8);
	buf[3] = (unsigned char)x;
#endif
}

static inline uint32_t
br_dec32le(const void *src)
{
#if BR_LE_UNALIGNED
	return ((const br_union_u32 *)src)->u;
#else
	const unsigned char *buf;

	buf = (const unsigned char*)src;
	return (uint32_t)buf[0]
		| ((uint32_t)buf[1] << 8)
		| ((uint32_t)buf[2] << 16)
		| ((uint32_t)buf[3] << 24);
#endif
}

static inline uint32_t
br_dec32be(const void *src)
{
#if BR_BE_UNALIGNED
	return ((const br_union_u32 *)src)->u;
#else
	const unsigned char *buf;

	buf = (const unsigned char*)src;
	return ((uint32_t)buf[0] << 24)
		| ((uint32_t)buf[1] << 16)
		| ((uint32_t)buf[2] << 8)
		| (uint32_t)buf[3];
#endif
}

static inline void
br_enc64le(void *dst, uint64_t x)
{
#if BR_LE_UNALIGNED
	((br_union_u64 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = (unsigned char*)dst;
	br_enc32le(buf, (uint32_t)x);
	br_enc32le(buf + 4, (uint32_t)(x >> 32));
#endif
}

static inline void
br_enc64be(void *dst, uint64_t x)
{
#if BR_BE_UNALIGNED
	((br_union_u64 *)dst)->u = x;
#else
	unsigned char *buf;

	buf = (unsigned char*)dst;
	br_enc32be(buf, (uint32_t)(x >> 32));
	br_enc32be(buf + 4, (uint32_t)x);
#endif
}

static inline uint64_t
br_dec64le(const void *src)
{
#if BR_LE_UNALIGNED
	return ((const br_union_u64 *)src)->u;
#else
	const unsigned char *buf;

	buf = (const unsigned char*)src;
	return (uint64_t)br_dec32le(buf)
		| ((uint64_t)br_dec32le(buf + 4) << 32);
#endif
}

static inline uint64_t
br_dec64be(const void *src)
{
#if BR_BE_UNALIGNED
	return ((const br_union_u64 *)src)->u;
#else
	const unsigned char *buf;

	buf = (const unsigned char*)src;
	return ((uint64_t)br_dec32be(buf) << 32)
		| (uint64_t)br_dec32be(buf + 4);
#endif
}

/*
 * Range decoding and encoding (for several successive values).
 */
void br_range_dec16le(uint16_t *v, size_t num, const void *src);
void br_range_dec16be(uint16_t *v, size_t num, const void *src);
void br_range_enc16le(void *dst, const uint16_t *v, size_t num);
void br_range_enc16be(void *dst, const uint16_t *v, size_t num);

void br_range_dec32le(uint32_t *v, size_t num, const void *src);
void br_range_dec32be(uint32_t *v, size_t num, const void *src);
void br_range_enc32le(void *dst, const uint32_t *v, size_t num);
void br_range_enc32be(void *dst, const uint32_t *v, size_t num);

void br_range_dec64le(uint64_t *v, size_t num, const void *src);
void br_range_dec64be(uint64_t *v, size_t num, const void *src);
void br_range_enc64le(void *dst, const uint64_t *v, size_t num);
void br_range_enc64be(void *dst, const uint64_t *v, size_t num);

/*
 * Byte-swap a 32-bit integer.
 */
static inline uint32_t
br_swap32(uint32_t x)
{
	x = ((x & (uint32_t)0x00FF00FF) << 8)
		| ((x >> 8) & (uint32_t)0x00FF00FF);
	return (x << 16) | (x >> 16);
}

/* ==================================================================== */
/*
 * Support code for hash functions.
 */

/*
 * IV for MD5, SHA-1, SHA-224 and SHA-256.
 */
extern const uint32_t br_md5_IV[];
extern const uint32_t br_sha1_IV[];
extern const uint32_t br_sha224_IV[];
extern const uint32_t br_sha256_IV[];

/*
 * Round functions for MD5, SHA-1, SHA-224 and SHA-256 (SHA-224 and
 * SHA-256 use the same round function).
 */
void br_md5_round(const unsigned char *buf, uint32_t *val);
void br_sha1_round(const unsigned char *buf, uint32_t *val);
void br_sha2small_round(const unsigned char *buf, uint32_t *val);

/*
 * The core function for the TLS PRF. It computes
 * P_hash(secret, label + seed), and XORs the result into the dst buffer.
 */
void br_tls_phash(void *dst, size_t len,
	const br_hash_class *dig,
	const void *secret, size_t secret_len, const char *label,
	size_t seed_num, const br_tls_prf_seed_chunk *seed);

/*
 * Copy all configured hash implementations from a multihash context
 * to another.
 */
static inline void
br_multihash_copyimpl(br_multihash_context *dst,
	const br_multihash_context *src)
{
	memcpy((void *)dst->impl, src->impl, sizeof src->impl);
}

/* ==================================================================== */
/*
 * Constant-time primitives. These functions manipulate 32-bit values in
 * order to provide constant-time comparisons and multiplexers.
 *
 * Boolean values (the "ctl" bits) MUST have value 0 or 1.
 *
 * Implementation notes:
 * =====================
 *
 * The uintN_t types are unsigned and with width exactly N bits; the C
 * standard guarantees that computations are performed modulo 2^N, and
 * there can be no overflow. Negation (unary '-') works on unsigned types
 * as well.
 *
 * The intN_t types are guaranteed to have width exactly N bits, with no
 * padding bit, and using two's complement representation. Casting
 * intN_t to uintN_t really is conversion modulo 2^N. Beware that intN_t
 * types, being signed, trigger implementation-defined behaviour on
 * overflow (including raising some signal): with GCC, while modular
 * arithmetics are usually applied, the optimizer may assume that
 * overflows don't occur (unless the -fwrapv command-line option is
 * added); Clang has the additional -ftrapv option to explicitly trap on
 * integer overflow or underflow.
 */

/*
 * Negate a boolean.
 */
static inline uint32_t
NOT(uint32_t ctl)
{
	return ctl ^ 1;
}

/*
 * Multiplexer: returns x if ctl == 1, y if ctl == 0.
 */
static inline uint32_t
MUX(uint32_t ctl, uint32_t x, uint32_t y)
{
	return y ^ (-ctl & (x ^ y));
}

/*
 * Equality check: returns 1 if x == y, 0 otherwise.
 */
static inline uint32_t
EQ(uint32_t x, uint32_t y)
{
	uint32_t q;

	q = x ^ y;
	return NOT((q | -q) >> 31);
}

/*
 * Inequality check: returns 1 if x != y, 0 otherwise.
 */
static inline uint32_t
NEQ(uint32_t x, uint32_t y)
{
	uint32_t q;

	q = x ^ y;
	return (q | -q) >> 31;
}

/*
 * Comparison: returns 1 if x > y, 0 otherwise.
 */
static inline uint32_t
GT(uint32_t x, uint32_t y)
{
	/*
	 * If both x < 2^31 and x < 2^31, then y-x will have its high
	 * bit set if x > y, cleared otherwise.
	 *
	 * If either x >= 2^31 or y >= 2^31 (but not both), then the
	 * result is the high bit of x.
	 *
	 * If both x >= 2^31 and y >= 2^31, then we can virtually
	 * subtract 2^31 from both, and we are back to the first case.
	 * Since (y-2^31)-(x-2^31) = y-x, the subtraction is already
	 * fine.
	 */
	uint32_t z;

	z = y - x;
	return (z ^ ((x ^ y) & (x ^ z))) >> 31;
}

/*
 * Other comparisons (greater-or-equal, lower-than, lower-or-equal).
 */
#define GE(x, y)   NOT(GT(y, x))
#define LT(x, y)   GT(y, x)
#define LE(x, y)   NOT(GT(x, y))

/*
 * General comparison: returned value is -1, 0 or 1, depending on
 * whether x is lower than, equal to, or greater than y.
 */
static inline int32_t
CMP(uint32_t x, uint32_t y)
{
	return (int32_t)GT(x, y) | -(int32_t)GT(y, x);
}

/*
 * Returns 1 if x == 0, 0 otherwise. Take care that the operand is signed.
 */
static inline uint32_t
EQ0(int32_t x)
{
	uint32_t q;

	q = (uint32_t)x;
	return ~(q | -q) >> 31;
}

/*
 * Returns 1 if x > 0, 0 otherwise. Take care that the operand is signed.
 */
static inline uint32_t
GT0(int32_t x)
{
	/*
	 * High bit of -x is 0 if x == 0, but 1 if x > 0.
	 */
	uint32_t q;

	q = (uint32_t)x;
	return (~q & -q) >> 31;
}

/*
 * Returns 1 if x >= 0, 0 otherwise. Take care that the operand is signed.
 */
static inline uint32_t
GE0(int32_t x)
{
	return ~(uint32_t)x >> 31;
}

/*
 * Returns 1 if x < 0, 0 otherwise. Take care that the operand is signed.
 */
static inline uint32_t
LT0(int32_t x)
{
	return (uint32_t)x >> 31;
}

/*
 * Returns 1 if x <= 0, 0 otherwise. Take care that the operand is signed.
 */
static inline uint32_t
LE0(int32_t x)
{
	uint32_t q;

	/*
	 * ~-x has its high bit set if and only if -x is nonnegative (as
	 * a signed int), i.e. x is in the -(2^31-1) to 0 range. We must
	 * do an OR with x itself to account for x = -2^31.
	 */
	q = (uint32_t)x;
	return (q | ~-q) >> 31;
}

/*
 * Conditional copy: src[] is copied into dst[] if and only if ctl is 1.
 * dst[] and src[] may overlap completely (but not partially).
 */
void br_ccopy(uint32_t ctl, void *dst, const void *src, size_t len);

#define CCOPY   br_ccopy

/*
 * Compute the bit length of a 32-bit integer. Returned value is between 0
 * and 32 (inclusive).
 */
static inline uint32_t
BIT_LENGTH(uint32_t x)
{
	uint32_t k, c;

	k = NEQ(x, 0);
	c = GT(x, 0xFFFF); x = MUX(c, x >> 16, x); k += c << 4;
	c = GT(x, 0x00FF); x = MUX(c, x >>  8, x); k += c << 3;
	c = GT(x, 0x000F); x = MUX(c, x >>  4, x); k += c << 2;
	c = GT(x, 0x0003); x = MUX(c, x >>  2, x); k += c << 1;
	k += GT(x, 0x0001);
	return k;
}

/*
 * Compute the minimum of x and y.
 */
static inline uint32_t
MIN(uint32_t x, uint32_t y)
{
	return MUX(GT(x, y), y, x);
}

/*
 * Compute the maximum of x and y.
 */
static inline uint32_t
MAX(uint32_t x, uint32_t y)
{
	return MUX(GT(x, y), x, y);
}

/*
 * Multiply two 32-bit integers, with a 64-bit result. This default
 * implementation assumes that the basic multiplication operator
 * yields constant-time code.
 */
#define MUL(x, y)   ((uint64_t)(x) * (uint64_t)(y))

#if BR_CT_MUL31

/*
 * Alternate implementation of MUL31, that will be constant-time on some
 * (old) platforms where the default MUL31 is not. Unfortunately, it is
 * also substantially slower, and yields larger code, on more modern
 * platforms, which is why it is deactivated by default.
 *
 * MUL31_lo() must do some extra work because on some platforms, the
 * _signed_ multiplication may return early if the top bits are 1.
 * Simply truncating (casting) the output of MUL31() would not be
 * sufficient, because the compiler may notice that we keep only the low
 * word, and then replace automatically the unsigned multiplication with
 * a signed multiplication opcode.
 */
#define MUL31(x, y)   ((uint64_t)((x) | (uint32_t)0x80000000) \
                       * (uint64_t)((y) | (uint32_t)0x80000000) \
                       - ((uint64_t)(x) << 31) - ((uint64_t)(y) << 31) \
                       - ((uint64_t)1 << 62))
static inline uint32_t
MUL31_lo(uint32_t x, uint32_t y)
{
	uint32_t xl, xh;
	uint32_t yl, yh;

	xl = (x & 0xFFFF) | (uint32_t)0x80000000;
	xh = (x >> 16) | (uint32_t)0x80000000;
	yl = (y & 0xFFFF) | (uint32_t)0x80000000;
	yh = (y >> 16) | (uint32_t)0x80000000;
	return (xl * yl + ((xl * yh + xh * yl) << 16)) & (uint32_t)0x7FFFFFFF;
}

#else

/*
 * Multiply two 31-bit integers, with a 62-bit result. This default
 * implementation assumes that the basic multiplication operator
 * yields constant-time code.
 * The MUL31_lo() macro returns only the low 31 bits of the product.
 */
#define MUL31(x, y)     ((uint64_t)(x) * (uint64_t)(y))
#define MUL31_lo(x, y)  (((uint32_t)(x) * (uint32_t)(y)) & (uint32_t)0x7FFFFFFF)

#endif

/*
 * Multiply two words together; the sum of the lengths of the two
 * operands must not exceed 31 (for instance, one operand may use 16
 * bits if the other fits on 15). If BR_CT_MUL15 is non-zero, then the
 * macro will contain some extra operations that help in making the
 * operation constant-time on some platforms, where the basic 32-bit
 * multiplication is not constant-time.
 */
#if BR_CT_MUL15
#define MUL15(x, y)   (((uint32_t)(x) | (uint32_t)0x80000000) \
                       * ((uint32_t)(y) | (uint32_t)0x80000000) \
		       & (uint32_t)0x7FFFFFFF)
#else
#define MUL15(x, y)   ((uint32_t)(x) * (uint32_t)(y))
#endif

/*
 * Arithmetic right shift (sign bit is copied). What happens when
 * right-shifting a negative value is _implementation-defined_, so it
 * does not trigger undefined behaviour, but it is still up to each
 * compiler to define (and document) what it does. Most/all compilers
 * will do an arithmetic shift, the sign bit being used to fill the
 * holes; this is a native operation on the underlying CPU, and it would
 * make little sense for the compiler to do otherwise. GCC explicitly
 * documents that it follows that convention.
 *
 * Still, if BR_NO_ARITH_SHIFT is defined (and non-zero), then an
 * alternate version will be used, that does not rely on such
 * implementation-defined behaviour. Unfortunately, it is also slower
 * and yields bigger code, which is why it is deactivated by default.
 */
#if BR_NO_ARITH_SHIFT
#define ARSH(x, n)   (((uint32_t)(x) >> (n)) \
                      | ((-((uint32_t)(x) >> 31)) << (32 - (n))))
#else
#define ARSH(x, n)   ((*(int32_t *)&(x)) >> (n))
#endif

/*
 * Constant-time division. The dividend hi:lo is divided by the
 * divisor d; the quotient is returned and the remainder is written
 * in *r. If hi == d, then the quotient does not fit on 32 bits;
 * returned value is thus truncated. If hi > d, returned values are
 * indeterminate.
 */
uint32_t br_divrem(uint32_t hi, uint32_t lo, uint32_t d, uint32_t *r);

/*
 * Wrapper for br_divrem(); the remainder is returned, and the quotient
 * is discarded.
 */
static inline uint32_t
br_rem(uint32_t hi, uint32_t lo, uint32_t d)
{
	uint32_t r;

	br_divrem(hi, lo, d, &r);
	return r;
}

/*
 * Wrapper for br_divrem(); the quotient is returned, and the remainder
 * is discarded.
 */
static inline uint32_t
br_div(uint32_t hi, uint32_t lo, uint32_t d)
{
	uint32_t r;

	return br_divrem(hi, lo, d, &r);
}

/* ==================================================================== */

/*
 * Integers 'i32'
 * --------------
 *
 * The 'i32' functions implement computations on big integers using
 * an internal representation as an array of 32-bit integers. For
 * an array x[]:
 *  -- x[0] contains the "announced bit length" of the integer
 *  -- x[1], x[2]... contain the value in little-endian order (x[1]
 *     contains the least significant 32 bits)
 *
 * Multiplications rely on the elementary 32x32->64 multiplication.
 *
 * The announced bit length specifies the number of bits that are
 * significant in the subsequent 32-bit words. Unused bits in the
 * last (most significant) word are set to 0; subsequent words are
 * uninitialized and need not exist at all.
 *
 * The execution time and memory access patterns of all computations
 * depend on the announced bit length, but not on the actual word
 * values. For modular integers, the announced bit length of any integer
 * modulo n is equal to the actual bit length of n; thus, computations
 * on modular integers are "constant-time" (only the modulus length may
 * leak).
 */

/*
 * Compute the actual bit length of an integer. The argument x should
 * point to the first (least significant) value word of the integer.
 * The len 'xlen' contains the number of 32-bit words to access.
 *
 * CT: value or length of x does not leak.
 */
uint32_t br_i32_bit_length(uint32_t *x, size_t xlen);

/*
 * Decode an integer from its big-endian unsigned representation. The
 * "true" bit length of the integer is computed, but all words of x[]
 * corresponding to the full 'len' bytes of the source are set.
 *
 * CT: value or length of x does not leak.
 */
void br_i32_decode(uint32_t *x, const void *src, size_t len);

/*
 * Decode an integer from its big-endian unsigned representation. The
 * integer MUST be lower than m[]; the announced bit length written in
 * x[] will be equal to that of m[]. All 'len' bytes from the source are
 * read.
 *
 * Returned value is 1 if the decode value fits within the modulus, 0
 * otherwise. In the latter case, the x[] buffer will be set to 0 (but
 * still with the announced bit length of m[]).
 *
 * CT: value or length of x does not leak. Memory access pattern depends
 * only of 'len' and the announced bit length of m. Whether x fits or
 * not does not leak either.
 */
uint32_t br_i32_decode_mod(uint32_t *x,
	const void *src, size_t len, const uint32_t *m);

/*
 * Reduce an integer (a[]) modulo another (m[]). The result is written
 * in x[] and its announced bit length is set to be equal to that of m[].
 *
 * x[] MUST be distinct from a[] and m[].
 *
 * CT: only announced bit lengths leak, not values of x, a or m.
 */
void br_i32_reduce(uint32_t *x, const uint32_t *a, const uint32_t *m);

/*
 * Decode an integer from its big-endian unsigned representation, and
 * reduce it modulo the provided modulus m[]. The announced bit length
 * of the result is set to be equal to that of the modulus.
 *
 * x[] MUST be distinct from m[].
 */
void br_i32_decode_reduce(uint32_t *x,
	const void *src, size_t len, const uint32_t *m);

/*
 * Encode an integer into its big-endian unsigned representation. The
 * output length in bytes is provided (parameter 'len'); if the length
 * is too short then the integer is appropriately truncated; if it is
 * too long then the extra bytes are set to 0.
 */
void br_i32_encode(void *dst, size_t len, const uint32_t *x);

/*
 * Multiply x[] by 2^32 and then add integer z, modulo m[]. This
 * function assumes that x[] and m[] have the same announced bit
 * length, and the announced bit length of m[] matches its true
 * bit length.
 *
 * x[] and m[] MUST be distinct arrays.
 *
 * CT: only the common announced bit length of x and m leaks, not
 * the values of x, z or m.
 */
void br_i32_muladd_small(uint32_t *x, uint32_t z, const uint32_t *m);

/*
 * Extract one word from an integer. The offset is counted in bits.
 * The word MUST entirely fit within the word elements corresponding
 * to the announced bit length of a[].
 */
static inline uint32_t
br_i32_word(const uint32_t *a, uint32_t off)
{
	size_t u;
	unsigned j;

	u = (size_t)(off >> 5) + 1;
	j = (unsigned)off & 31;
	if (j == 0) {
		return a[u];
	} else {
		return (a[u] >> j) | (a[u + 1] << (32 - j));
	}
}

/*
 * Test whether an integer is zero.
 */
uint32_t br_i32_iszero(const uint32_t *x);

/*
 * Add b[] to a[] and return the carry (0 or 1). If ctl is 0, then a[]
 * is unmodified, but the carry is still computed and returned. The
 * arrays a[] and b[] MUST have the same announced bit length.
 *
 * a[] and b[] MAY be the same array, but partial overlap is not allowed.
 */
uint32_t br_i32_add(uint32_t *a, const uint32_t *b, uint32_t ctl);

/*
 * Subtract b[] from a[] and return the carry (0 or 1). If ctl is 0,
 * then a[] is unmodified, but the carry is still computed and returned.
 * The arrays a[] and b[] MUST have the same announced bit length.
 *
 * a[] and b[] MAY be the same array, but partial overlap is not allowed.
 */
uint32_t br_i32_sub(uint32_t *a, const uint32_t *b, uint32_t ctl);

/*
 * Compute d+a*b, result in d. The initial announced bit length of d[]
 * MUST match that of a[]. The d[] array MUST be large enough to
 * accommodate the full result, plus (possibly) an extra word. The
 * resulting announced bit length of d[] will be the sum of the announced
 * bit lengths of a[] and b[] (therefore, it may be larger than the actual
 * bit length of the numerical result).
 *
 * a[] and b[] may be the same array. d[] must be disjoint from both a[]
 * and b[].
 */
void br_i32_mulacc(uint32_t *d, const uint32_t *a, const uint32_t *b);

/*
 * Zeroize an integer. The announced bit length is set to the provided
 * value, and the corresponding words are set to 0.
 */
static inline void
br_i32_zero(uint32_t *x, uint32_t bit_len)
{
	*x ++ = bit_len;
	memset(x, 0, ((bit_len + 31) >> 5) * sizeof *x);
}

/*
 * Compute -(1/x) mod 2^32. If x is even, then this function returns 0.
 */
uint32_t br_i32_ninv32(uint32_t x);

/*
 * Convert a modular integer to Montgomery representation. The integer x[]
 * MUST be lower than m[], but with the same announced bit length.
 */
void br_i32_to_monty(uint32_t *x, const uint32_t *m);

/*
 * Convert a modular integer back from Montgomery representation. The
 * integer x[] MUST be lower than m[], but with the same announced bit
 * length. The "m0i" parameter is equal to -(1/m0) mod 2^32, where m0 is
 * the least significant value word of m[] (this works only if m[] is
 * an odd integer).
 */
void br_i32_from_monty(uint32_t *x, const uint32_t *m, uint32_t m0i);

/*
 * Compute a modular Montgomery multiplication. d[] is filled with the
 * value of x*y/R modulo m[] (where R is the Montgomery factor). The
 * array d[] MUST be distinct from x[], y[] and m[]. x[] and y[] MUST be
 * numerically lower than m[]. x[] and y[] MAY be the same array. The
 * "m0i" parameter is equal to -(1/m0) mod 2^32, where m0 is the least
 * significant value word of m[] (this works only if m[] is an odd
 * integer).
 */
void br_i32_montymul(uint32_t *d, const uint32_t *x, const uint32_t *y,
	const uint32_t *m, uint32_t m0i);

/*
 * Compute a modular exponentiation. x[] MUST be an integer modulo m[]
 * (same announced bit length, lower value). m[] MUST be odd. The
 * exponent is in big-endian unsigned notation, over 'elen' bytes. The
 * "m0i" parameter is equal to -(1/m0) mod 2^32, where m0 is the least
 * significant value word of m[] (this works only if m[] is an odd
 * integer). The t1[] and t2[] parameters must be temporary arrays,
 * each large enough to accommodate an integer with the same size as m[].
 */
void br_i32_modpow(uint32_t *x, const unsigned char *e, size_t elen,
	const uint32_t *m, uint32_t m0i, uint32_t *t1, uint32_t *t2);

/* ==================================================================== */

/*
 * Integers 'i31'
 * --------------
 *
 * The 'i31' functions implement computations on big integers using
 * an internal representation as an array of 32-bit integers. For
 * an array x[]:
 *  -- x[0] encodes the array length and the "announced bit length"
 *     of the integer: namely, if the announced bit length is k,
 *     then x[0] = ((k / 31) << 5) + (k % 31).
 *  -- x[1], x[2]... contain the value in little-endian order, 31
 *     bits per word (x[1] contains the least significant 31 bits).
 *     The upper bit of each word is 0.
 *
 * Multiplications rely on the elementary 32x32->64 multiplication.
 *
 * The announced bit length specifies the number of bits that are
 * significant in the subsequent 32-bit words. Unused bits in the
 * last (most significant) word are set to 0; subsequent words are
 * uninitialized and need not exist at all.
 *
 * The execution time and memory access patterns of all computations
 * depend on the announced bit length, but not on the actual word
 * values. For modular integers, the announced bit length of any integer
 * modulo n is equal to the actual bit length of n; thus, computations
 * on modular integers are "constant-time" (only the modulus length may
 * leak).
 */

/*
 * Test whether an integer is zero.
 */
uint32_t br_i31_iszero(const uint32_t *x);

/*
 * Add b[] to a[] and return the carry (0 or 1). If ctl is 0, then a[]
 * is unmodified, but the carry is still computed and returned. The
 * arrays a[] and b[] MUST have the same announced bit length.
 *
 * a[] and b[] MAY be the same array, but partial overlap is not allowed.
 */
uint32_t br_i31_add(uint32_t *a, const uint32_t *b, uint32_t ctl);

/*
 * Subtract b[] from a[] and return the carry (0 or 1). If ctl is 0,
 * then a[] is unmodified, but the carry is still computed and returned.
 * The arrays a[] and b[] MUST have the same announced bit length.
 *
 * a[] and b[] MAY be the same array, but partial overlap is not allowed.
 */
uint32_t br_i31_sub(uint32_t *a, const uint32_t *b, uint32_t ctl);

/*
 * Compute the ENCODED actual bit length of an integer. The argument x
 * should point to the first (least significant) value word of the
 * integer. The len 'xlen' contains the number of 32-bit words to
 * access. The upper bit of each value word MUST be 0.
 * Returned value is ((k / 31) << 5) + (k % 31) if the bit length is k.
 *
 * CT: value or length of x does not leak.
 */
uint32_t br_i31_bit_length(uint32_t *x, size_t xlen);

/*
 * Decode an integer from its big-endian unsigned representation. The
 * "true" bit length of the integer is computed and set in the encoded
 * announced bit length (x[0]), but all words of x[] corresponding to
 * the full 'len' bytes of the source are set.
 *
 * CT: value or length of x does not leak.
 */
void br_i31_decode(uint32_t *x, const void *src, size_t len);

/*
 * Decode an integer from its big-endian unsigned representation. The
 * integer MUST be lower than m[]; the (encoded) announced bit length
 * written in x[] will be equal to that of m[]. All 'len' bytes from the
 * source are read.
 *
 * Returned value is 1 if the decode value fits within the modulus, 0
 * otherwise. In the latter case, the x[] buffer will be set to 0 (but
 * still with the announced bit length of m[]).
 *
 * CT: value or length of x does not leak. Memory access pattern depends
 * only of 'len' and the announced bit length of m. Whether x fits or
 * not does not leak either.
 */
uint32_t br_i31_decode_mod(uint32_t *x,
	const void *src, size_t len, const uint32_t *m);

/*
 * Zeroize an integer. The announced bit length is set to the provided
 * value, and the corresponding words are set to 0. The ENCODED bit length
 * is expected here.
 */
static inline void
br_i31_zero(uint32_t *x, uint32_t bit_len)
{
	*x ++ = bit_len;
	memset(x, 0, ((bit_len + 31) >> 5) * sizeof *x);
}

/*
 * Right-shift an integer. The shift amount must be lower than 31
 * bits.
 */
void br_i31_rshift(uint32_t *x, int count);

/*
 * Reduce an integer (a[]) modulo another (m[]). The result is written
 * in x[] and its announced bit length is set to be equal to that of m[].
 *
 * x[] MUST be distinct from a[] and m[].
 *
 * CT: only announced bit lengths leak, not values of x, a or m.
 */
void br_i31_reduce(uint32_t *x, const uint32_t *a, const uint32_t *m);

/*
 * Decode an integer from its big-endian unsigned representation, and
 * reduce it modulo the provided modulus m[]. The announced bit length
 * of the result is set to be equal to that of the modulus.
 *
 * x[] MUST be distinct from m[].
 */
void br_i31_decode_reduce(uint32_t *x,
	const void *src, size_t len, const uint32_t *m);

/*
 * Multiply x[] by 2^31 and then add integer z, modulo m[]. This
 * function assumes that x[] and m[] have the same announced bit
 * length, the announced bit length of m[] matches its true
 * bit length.
 *
 * x[] and m[] MUST be distinct arrays. z MUST fit in 31 bits (upper
 * bit set to 0).
 *
 * CT: only the common announced bit length of x and m leaks, not
 * the values of x, z or m.
 */
void br_i31_muladd_small(uint32_t *x, uint32_t z, const uint32_t *m);

/*
 * Encode an integer into its big-endian unsigned representation. The
 * output length in bytes is provided (parameter 'len'); if the length
 * is too short then the integer is appropriately truncated; if it is
 * too long then the extra bytes are set to 0.
 */
void br_i31_encode(void *dst, size_t len, const uint32_t *x);

/*
 * Compute -(1/x) mod 2^31. If x is even, then this function returns 0.
 */
uint32_t br_i31_ninv31(uint32_t x);

/*
 * Compute a modular Montgomery multiplication. d[] is filled with the
 * value of x*y/R modulo m[] (where R is the Montgomery factor). The
 * array d[] MUST be distinct from x[], y[] and m[]. x[] and y[] MUST be
 * numerically lower than m[]. x[] and y[] MAY be the same array. The
 * "m0i" parameter is equal to -(1/m0) mod 2^31, where m0 is the least
 * significant value word of m[] (this works only if m[] is an odd
 * integer).
 */
void br_i31_montymul(uint32_t *d, const uint32_t *x, const uint32_t *y,
	const uint32_t *m, uint32_t m0i);

/*
 * Convert a modular integer to Montgomery representation. The integer x[]
 * MUST be lower than m[], but with the same announced bit length.
 */
void br_i31_to_monty(uint32_t *x, const uint32_t *m);

/*
 * Convert a modular integer back from Montgomery representation. The
 * integer x[] MUST be lower than m[], but with the same announced bit
 * length. The "m0i" parameter is equal to -(1/m0) mod 2^32, where m0 is
 * the least significant value word of m[] (this works only if m[] is
 * an odd integer).
 */
void br_i31_from_monty(uint32_t *x, const uint32_t *m, uint32_t m0i);

/*
 * Compute a modular exponentiation. x[] MUST be an integer modulo m[]
 * (same announced bit length, lower value). m[] MUST be odd. The
 * exponent is in big-endian unsigned notation, over 'elen' bytes. The
 * "m0i" parameter is equal to -(1/m0) mod 2^31, where m0 is the least
 * significant value word of m[] (this works only if m[] is an odd
 * integer). The t1[] and t2[] parameters must be temporary arrays,
 * each large enough to accommodate an integer with the same size as m[].
 */
void br_i31_modpow(uint32_t *x, const unsigned char *e, size_t elen,
	const uint32_t *m, uint32_t m0i, uint32_t *t1, uint32_t *t2);

/*
 * Compute a modular exponentiation. x[] MUST be an integer modulo m[]
 * (same announced bit length, lower value). m[] MUST be odd. The
 * exponent is in big-endian unsigned notation, over 'elen' bytes. The
 * "m0i" parameter is equal to -(1/m0) mod 2^31, where m0 is the least
 * significant value word of m[] (this works only if m[] is an odd
 * integer). The tmp[] array is used for temporaries, and has size
 * 'twlen' words; it must be large enough to accommodate at least two
 * temporary values with the same size as m[] (including the leading
 * "bit length" word). If there is room for more temporaries, then this
 * function may use the extra room for window-based optimisation,
 * resulting in faster computations.
 *
 * Returned value is 1 on success, 0 on error. An error is reported if
 * the provided tmp[] array is too short.
 */
uint32_t br_i31_modpow_opt(uint32_t *x, const unsigned char *e, size_t elen,
	const uint32_t *m, uint32_t m0i, uint32_t *tmp, size_t twlen);

/*
 * Compute d+a*b, result in d. The initial announced bit length of d[]
 * MUST match that of a[]. The d[] array MUST be large enough to
 * accommodate the full result, plus (possibly) an extra word. The
 * resulting announced bit length of d[] will be the sum of the announced
 * bit lengths of a[] and b[] (therefore, it may be larger than the actual
 * bit length of the numerical result).
 *
 * a[] and b[] may be the same array. d[] must be disjoint from both a[]
 * and b[].
 */
void br_i31_mulacc(uint32_t *d, const uint32_t *a, const uint32_t *b);

/*
 * Compute x/y mod m, result in x. Values x and y must be between 0 and
 * m-1, and have the same announced bit length as m. Modulus m must be
 * odd. The "m0i" parameter is equal to -1/m mod 2^31. The array 't'
 * must point to a temporary area that can hold at least three integers
 * of the size of m.
 *
 * m may not overlap x and y. x and y may overlap each other (this can
 * be useful to test whether a value is invertible modulo m). t must be
 * disjoint from all other arrays.
 *
 * Returned value is 1 on success, 0 otherwise. Success is attained if
 * y is invertible modulo m.
 */
uint32_t br_i31_moddiv(uint32_t *x, const uint32_t *y,
	const uint32_t *m, uint32_t m0i, uint32_t *t);

/* ==================================================================== */

/*
 * FIXME: document "i15" functions.
 */

static inline void
br_i15_zero(uint16_t *x, uint16_t bit_len)
{
	*x ++ = bit_len;
	memset(x, 0, ((bit_len + 15) >> 4) * sizeof *x);
}

uint32_t br_i15_iszero(const uint16_t *x);

uint16_t br_i15_ninv15(uint16_t x);

uint32_t br_i15_add(uint16_t *a, const uint16_t *b, uint32_t ctl);

uint32_t br_i15_sub(uint16_t *a, const uint16_t *b, uint32_t ctl);

void br_i15_muladd_small(uint16_t *x, uint16_t z, const uint16_t *m);

void br_i15_montymul(uint16_t *d, const uint16_t *x, const uint16_t *y,
	const uint16_t *m, uint16_t m0i);

void br_i15_to_monty(uint16_t *x, const uint16_t *m);

void br_i15_modpow(uint16_t *x, const unsigned char *e, size_t elen,
	const uint16_t *m, uint16_t m0i, uint16_t *t1, uint16_t *t2);

uint32_t br_i15_modpow_opt(uint16_t *x, const unsigned char *e, size_t elen,
	const uint16_t *m, uint16_t m0i, uint16_t *tmp, size_t twlen);

void br_i15_encode(void *dst, size_t len, const uint16_t *x);

uint32_t br_i15_decode_mod(uint16_t *x,
	const void *src, size_t len, const uint16_t *m);

void br_i15_rshift(uint16_t *x, int count);

uint32_t br_i15_bit_length(uint16_t *x, size_t xlen);

void br_i15_decode(uint16_t *x, const void *src, size_t len);

void br_i15_from_monty(uint16_t *x, const uint16_t *m, uint16_t m0i);

void br_i15_decode_reduce(uint16_t *x,
	const void *src, size_t len, const uint16_t *m);

void br_i15_reduce(uint16_t *x, const uint16_t *a, const uint16_t *m);

void br_i15_mulacc(uint16_t *d, const uint16_t *a, const uint16_t *b);

uint32_t br_i15_moddiv(uint16_t *x, const uint16_t *y,
	const uint16_t *m, uint16_t m0i, uint16_t *t);

/*
 * Variant of br_i31_modpow_opt() that internally uses 64x64->128
 * multiplications. It expects the same parameters as br_i31_modpow_opt(),
 * except that the temporaries should be 64-bit integers, not 32-bit
 * integers.
 */
uint32_t br_i62_modpow_opt(uint32_t *x31, const unsigned char *e, size_t elen,
	const uint32_t *m31, uint32_t m0i31, uint64_t *tmp, size_t twlen);

/*
 * Type for a function with the same API as br_i31_modpow_opt() (some
 * implementations of this type may have stricter alignment requirements
 * on the temporaries).
 */
typedef uint32_t (*br_i31_modpow_opt_type)(uint32_t *x,
	const unsigned char *e, size_t elen,
	const uint32_t *m, uint32_t m0i, uint32_t *tmp, size_t twlen);

/*
 * Wrapper for br_i62_modpow_opt() that uses the same type as
 * br_i31_modpow_opt(); however, it requires its 'tmp' argument to the
 * 64-bit aligned.
 */
uint32_t br_i62_modpow_opt_as_i31(uint32_t *x,
	const unsigned char *e, size_t elen,
	const uint32_t *m, uint32_t m0i, uint32_t *tmp, size_t twlen);

/* ==================================================================== */

static inline size_t
br_digest_size(const br_hash_class *digest_class)
{
	return (size_t)(digest_class->desc >> BR_HASHDESC_OUT_OFF)
		& BR_HASHDESC_OUT_MASK;
}

/*
 * Get the output size (in bytes) of a hash function.
 */
size_t br_digest_size_by_ID(int digest_id);

/*
 * Get the OID (encoded OBJECT IDENTIFIER value, without tag and length)
 * for a hash function. If digest_id is not a supported digest identifier
 * (in particular if it is equal to 0, i.e. br_md5sha1_ID), then NULL is
 * returned and *len is set to 0.
 */
const unsigned char *br_digest_OID(int digest_id, size_t *len);

/* ==================================================================== */
/*
 * DES support functions.
 */

/*
 * Apply DES Initial Permutation.
 */
void br_des_do_IP(uint32_t *xl, uint32_t *xr);

/*
 * Apply DES Final Permutation (inverse of IP).
 */
void br_des_do_invIP(uint32_t *xl, uint32_t *xr);

/*
 * Key schedule unit: for a DES key (8 bytes), compute 16 subkeys. Each
 * subkey is two 28-bit words represented as two 32-bit words; the PC-2
 * bit extration is NOT applied.
 */
void br_des_keysched_unit(uint32_t *skey, const void *key);

/*
 * Reversal of 16 DES sub-keys (for decryption).
 */
void br_des_rev_skey(uint32_t *skey);

/*
 * DES/3DES key schedule for 'des_tab' (encryption direction). Returned
 * value is the number of rounds.
 */
unsigned br_des_tab_keysched(uint32_t *skey, const void *key, size_t key_len);

/*
 * DES/3DES key schedule for 'des_ct' (encryption direction). Returned
 * value is the number of rounds.
 */
unsigned br_des_ct_keysched(uint32_t *skey, const void *key, size_t key_len);

/*
 * DES/3DES subkey decompression (from the compressed bitsliced subkeys).
 */
void br_des_ct_skey_expand(uint32_t *sk_exp,
	unsigned num_rounds, const uint32_t *skey);

/*
 * DES/3DES block encryption/decryption ('des_tab').
 */
void br_des_tab_process_block(unsigned num_rounds,
	const uint32_t *skey, void *block);

/*
 * DES/3DES block encryption/decryption ('des_ct').
 */
void br_des_ct_process_block(unsigned num_rounds,
	const uint32_t *skey, void *block);

/* ==================================================================== */
/*
 * AES support functions.
 */

/*
 * The AES S-box (256-byte table).
 */
extern const unsigned char br_aes_S[];

/*
 * AES key schedule. skey[] is filled with n+1 128-bit subkeys, where n
 * is the number of rounds (10 to 14, depending on key size). The number
 * of rounds is returned. If the key size is invalid (not 16, 24 or 32),
 * then 0 is returned.
 *
 * This implementation uses a 256-byte table and is NOT constant-time.
 */
unsigned br_aes_keysched(uint32_t *skey, const void *key, size_t key_len);

/*
 * AES key schedule for decryption ('aes_big' implementation).
 */
unsigned br_aes_big_keysched_inv(uint32_t *skey,
	const void *key, size_t key_len);

/*
 * AES block encryption with the 'aes_big' implementation (fast, but
 * not constant-time). This function encrypts a single block "in place".
 */
void br_aes_big_encrypt(unsigned num_rounds, const uint32_t *skey, void *data);

/*
 * AES block decryption with the 'aes_big' implementation (fast, but
 * not constant-time). This function decrypts a single block "in place".
 */
void br_aes_big_decrypt(unsigned num_rounds, const uint32_t *skey, void *data);

/*
 * AES block encryption with the 'aes_small' implementation (small, but
 * slow and not constant-time). This function encrypts a single block
 * "in place".
 */
void br_aes_small_encrypt(unsigned num_rounds,
	const uint32_t *skey, void *data);

/*
 * AES block decryption with the 'aes_small' implementation (small, but
 * slow and not constant-time). This function decrypts a single block
 * "in place".
 */
void br_aes_small_decrypt(unsigned num_rounds,
	const uint32_t *skey, void *data);

/*
 * The constant-time implementation is "bitsliced": the 128-bit state is
 * split over eight 32-bit words q* in the following way:
 *
 * -- Input block consists in 16 bytes:
 *    a00 a10 a20 a30 a01 a11 a21 a31 a02 a12 a22 a32 a03 a13 a23 a33
 * In the terminology of FIPS 197, this is a 4x4 matrix which is read
 * column by column.
 *
 * -- Each byte is split into eight bits which are distributed over the
 * eight words, at the same rank. Thus, for a byte x at rank k, bit 0
 * (least significant) of x will be at rank k in q0 (if that bit is b,
 * then it contributes "b << k" to the value of q0), bit 1 of x will be
 * at rank k in q1, and so on.
 *
 * -- Ranks given to bits are in "row order" and are either all even, or
 * all odd. Two independent AES states are thus interleaved, one using
 * the even ranks, the other the odd ranks. Row order means:
 *    a00 a01 a02 a03 a10 a11 a12 a13 a20 a21 a22 a23 a30 a31 a32 a33
 *
 * Converting input bytes from two AES blocks to bitslice representation
 * is done in the following way:
 * -- Decode first block into the four words q0 q2 q4 q6, in that order,
 * using little-endian convention.
 * -- Decode second block into the four words q1 q3 q5 q7, in that order,
 * using little-endian convention.
 * -- Call br_aes_ct_ortho().
 *
 * Converting back to bytes is done by using the reverse operations. Note
 * that br_aes_ct_ortho() is its own inverse.
 */

/*
 * Perform bytewise orthogonalization of eight 32-bit words. Bytes
 * of q0..q7 are spread over all words: for a byte x that occurs
 * at rank i in q[j] (byte x uses bits 8*i to 8*i+7 in q[j]), the bit
 * of rank k in x (0 <= k <= 7) goes to q[k] at rank 8*i+j.
 *
 * This operation is an involution.
 */
void br_aes_ct_ortho(uint32_t *q);

/*
 * The AES S-box, as a bitsliced constant-time version. The input array
 * consists in eight 32-bit words; 32 S-box instances are computed in
 * parallel. Bits 0 to 7 of each S-box input (bit 0 is least significant)
 * are spread over the words 0 to 7, at the same rank.
 */
void br_aes_ct_bitslice_Sbox(uint32_t *q);

/*
 * Like br_aes_bitslice_Sbox(), but for the inverse S-box.
 */
void br_aes_ct_bitslice_invSbox(uint32_t *q);

/*
 * Compute AES encryption on bitsliced data. Since input is stored on
 * eight 32-bit words, two block encryptions are actually performed
 * in parallel.
 */
void br_aes_ct_bitslice_encrypt(unsigned num_rounds,
	const uint32_t *skey, uint32_t *q);

/*
 * Compute AES decryption on bitsliced data. Since input is stored on
 * eight 32-bit words, two block decryptions are actually performed
 * in parallel.
 */
void br_aes_ct_bitslice_decrypt(unsigned num_rounds,
	const uint32_t *skey, uint32_t *q);

/*
 * AES key schedule, constant-time version. skey[] is filled with n+1
 * 128-bit subkeys, where n is the number of rounds (10 to 14, depending
 * on key size). The number of rounds is returned. If the key size is
 * invalid (not 16, 24 or 32), then 0 is returned.
 */
unsigned br_aes_ct_keysched(uint32_t *comp_skey,
	const void *key, size_t key_len);

/*
 * Expand AES subkeys as produced by br_aes_ct_keysched(), into
 * a larger array suitable for br_aes_ct_bitslice_encrypt() and
 * br_aes_ct_bitslice_decrypt().
 */
void br_aes_ct_skey_expand(uint32_t *skey,
	unsigned num_rounds, const uint32_t *comp_skey);

/*
 * For the ct64 implementation, the same bitslicing technique is used,
 * but four instances are interleaved. First instance uses bits 0, 4,
 * 8, 12,... of each word; second instance uses bits 1, 5, 9, 13,...
 * and so on.
 */

/*
 * Perform bytewise orthogonalization of eight 64-bit words. Bytes
 * of q0..q7 are spread over all words: for a byte x that occurs
 * at rank i in q[j] (byte x uses bits 8*i to 8*i+7 in q[j]), the bit
 * of rank k in x (0 <= k <= 7) goes to q[k] at rank 8*i+j.
 *
 * This operation is an involution.
 */
void br_aes_ct64_ortho(uint64_t *q);

/*
 * Interleave bytes for an AES input block. If input bytes are
 * denoted 0123456789ABCDEF, and have been decoded with little-endian
 * convention (w[0] contains 0123, with '3' being most significant;
 * w[1] contains 4567, and so on), then output word q0 will be
 * set to 08192A3B (again little-endian convention) and q1 will
 * be set to 4C5D6E7F.
 */
void br_aes_ct64_interleave_in(uint64_t *q0, uint64_t *q1, const uint32_t *w);

/*
 * Perform the opposite of br_aes_ct64_interleave_in().
 */
void br_aes_ct64_interleave_out(uint32_t *w, uint64_t q0, uint64_t q1);

/*
 * The AES S-box, as a bitsliced constant-time version. The input array
 * consists in eight 64-bit words; 64 S-box instances are computed in
 * parallel. Bits 0 to 7 of each S-box input (bit 0 is least significant)
 * are spread over the words 0 to 7, at the same rank.
 */
void br_aes_ct64_bitslice_Sbox(uint64_t *q);

/*
 * Like br_aes_bitslice_Sbox(), but for the inverse S-box.
 */
void br_aes_ct64_bitslice_invSbox(uint64_t *q);

/*
 * Compute AES encryption on bitsliced data. Since input is stored on
 * eight 64-bit words, four block encryptions are actually performed
 * in parallel.
 */
void br_aes_ct64_bitslice_encrypt(unsigned num_rounds,
	const uint64_t *skey, uint64_t *q);

/*
 * Compute AES decryption on bitsliced data. Since input is stored on
 * eight 64-bit words, four block decryptions are actually performed
 * in parallel.
 */
void br_aes_ct64_bitslice_decrypt(unsigned num_rounds,
	const uint64_t *skey, uint64_t *q);

/*
 * AES key schedule, constant-time version. skey[] is filled with n+1
 * 128-bit subkeys, where n is the number of rounds (10 to 14, depending
 * on key size). The number of rounds is returned. If the key size is
 * invalid (not 16, 24 or 32), then 0 is returned.
 */
unsigned br_aes_ct64_keysched(uint64_t *comp_skey,
	const void *key, size_t key_len);

/*
 * Expand AES subkeys as produced by br_aes_ct64_keysched(), into
 * a larger array suitable for br_aes_ct64_bitslice_encrypt() and
 * br_aes_ct64_bitslice_decrypt().
 */
void br_aes_ct64_skey_expand(uint64_t *skey,
	unsigned num_rounds, const uint64_t *comp_skey);

/*
 * Test support for AES-NI opcodes.
 */
int br_aes_x86ni_supported(void);

/*
 * AES key schedule, using x86 AES-NI instructions. This yields the
 * subkeys in the encryption direction. Number of rounds is returned.
 * Key size MUST be 16, 24 or 32 bytes; otherwise, 0 is returned.
 */
unsigned br_aes_x86ni_keysched_enc(unsigned char *skni,
	const void *key, size_t len);

/*
 * AES key schedule, using x86 AES-NI instructions. This yields the
 * subkeys in the decryption direction. Number of rounds is returned.
 * Key size MUST be 16, 24 or 32 bytes; otherwise, 0 is returned.
 */
unsigned br_aes_x86ni_keysched_dec(unsigned char *skni,
	const void *key, size_t len);

/*
 * Test support for AES POWER8 opcodes.
 */
int br_aes_pwr8_supported(void);

/*
 * AES key schedule, using POWER8 instructions. This yields the
 * subkeys in the encryption direction. Number of rounds is returned.
 * Key size MUST be 16, 24 or 32 bytes; otherwise, 0 is returned.
 */
unsigned br_aes_pwr8_keysched(unsigned char *skni,
	const void *key, size_t len);

/* ==================================================================== */
/*
 * RSA.
 */

/*
 * Apply proper PKCS#1 v1.5 padding (for signatures). 'hash_oid' is
 * the encoded hash function OID, or NULL.
 */
uint32_t br_rsa_pkcs1_sig_pad(const unsigned char *hash_oid,
	const unsigned char *hash, size_t hash_len,
	uint32_t n_bitlen, unsigned char *x);

/*
 * Check PKCS#1 v1.5 padding (for signatures). 'hash_oid' is the encoded
 * hash function OID, or NULL. The provided 'sig' value is _after_ the
 * modular exponentiation, i.e. it should be the padded hash. On
 * success, the hashed message is extracted.
 */
uint32_t br_rsa_pkcs1_sig_unpad(const unsigned char *sig, size_t sig_len,
	const unsigned char *hash_oid, size_t hash_len,
	unsigned char *hash_out);

/*
 * Apply proper PSS padding. The 'x' buffer is output only: it
 * receives the value that is to be exponentiated.
 */
uint32_t br_rsa_pss_sig_pad(const br_prng_class **rng,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash, size_t salt_len,
	uint32_t n_bitlen, unsigned char *x);

/*
 * Check PSS padding. The provided value is the one _after_
 * the modular exponentiation; it is modified by this function.
 * This function infers the signature length from the public key
 * size, i.e. it assumes that this has already been verified (as
 * part of the exponentiation).
 */
uint32_t br_rsa_pss_sig_unpad(
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash, size_t salt_len,
	const br_rsa_public_key *pk, unsigned char *x);

/*
 * Apply OAEP padding. Returned value is the actual padded string length,
 * or zero on error.
 */
size_t br_rsa_oaep_pad(const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len, const br_rsa_public_key *pk,
	void *dst, size_t dst_nax_len, const void *src, size_t src_len);

/*
 * Unravel and check OAEP padding. If the padding is correct, then 1 is
 * returned, '*len' is adjusted to the length of the message, and the
 * data is moved to the start of the 'data' buffer. If the padding is
 * incorrect, then 0 is returned and '*len' is untouched. Either way,
 * the complete buffer contents are altered.
 */
uint32_t br_rsa_oaep_unpad(const br_hash_class *dig,
	const void *label, size_t label_len, void *data, size_t *len);

/*
 * Compute MGF1 for a given seed, and XOR the output into the provided
 * buffer.
 */
void br_mgf1_xor(void *data, size_t len,
	const br_hash_class *dig, const void *seed, size_t seed_len);

/*
 * Inner function for RSA key generation; used by the "i31" and "i62"
 * implementations.
 */
uint32_t br_rsa_i31_keygen_inner(const br_prng_class **rng,
	br_rsa_private_key *sk, void *kbuf_priv,
	br_rsa_public_key *pk, void *kbuf_pub,
	unsigned size, uint32_t pubexp, br_i31_modpow_opt_type mp31);

/* ==================================================================== */
/*
 * Elliptic curves.
 */

/*
 * Type for generic EC parameters: curve order (unsigned big-endian
 * encoding) and encoded conventional generator.
 */
typedef struct {
	int curve;
	const unsigned char *order;
	size_t order_len;
	const unsigned char *generator;
	size_t generator_len;
} br_ec_curve_def;

extern const br_ec_curve_def br_secp256r1;
extern const br_ec_curve_def br_secp384r1;
extern const br_ec_curve_def br_secp521r1;

/*
 * For Curve25519, the advertised "order" really is 2^255-1, since the
 * point multipliction function really works over arbitrary 255-bit
 * scalars. This value is only meant as a hint for ECDH key generation;
 * only ECDSA uses the exact curve order, and ECDSA is not used with
 * that specific curve.
 */
extern const br_ec_curve_def br_curve25519;

/*
 * Decode some bytes as an i31 integer, with truncation (corresponding
 * to the 'bits2int' operation in RFC 6979). The target ENCODED bit
 * length is provided as last parameter. The resulting value will have
 * this declared bit length, and consists the big-endian unsigned decoding
 * of exactly that many bits in the source (capped at the source length).
 */
void br_ecdsa_i31_bits2int(uint32_t *x,
	const void *src, size_t len, uint32_t ebitlen);

/*
 * Decode some bytes as an i15 integer, with truncation (corresponding
 * to the 'bits2int' operation in RFC 6979). The target ENCODED bit
 * length is provided as last parameter. The resulting value will have
 * this declared bit length, and consists the big-endian unsigned decoding
 * of exactly that many bits in the source (capped at the source length).
 */
void br_ecdsa_i15_bits2int(uint16_t *x,
	const void *src, size_t len, uint32_t ebitlen);

/* ==================================================================== */
/*
 * ASN.1 support functions.
 */

/*
 * A br_asn1_uint structure contains encoding information about an
 * INTEGER nonnegative value: pointer to the integer contents (unsigned
 * big-endian representation), length of the integer contents,
 * and length of the encoded value. The data shall have minimal length:
 *  - If the integer value is zero, then 'len' must be zero.
 *  - If the integer value is not zero, then data[0] must be non-zero.
 *
 * Under these conditions, 'asn1len' is necessarily equal to either len
 * or len+1.
 */
typedef struct {
	const unsigned char *data;
	size_t len;
	size_t asn1len;
} br_asn1_uint;

/*
 * Given an encoded integer (unsigned big-endian, with possible leading
 * bytes of value 0), returned the "prepared INTEGER" structure.
 */
br_asn1_uint br_asn1_uint_prepare(const void *xdata, size_t xlen);

/*
 * Encode an ASN.1 length. The length of the encoded length is returned.
 * If 'dest' is NULL, then no encoding is performed, but the length of
 * the encoded length is still computed and returned.
 */
size_t br_asn1_encode_length(void *dest, size_t len);

/*
 * Convenient macro for computing lengths of lengths.
 */
#define len_of_len(len)   br_asn1_encode_length(NULL, len)

/*
 * Encode a (prepared) ASN.1 INTEGER. The encoded length is returned.
 * If 'dest' is NULL, then no encoding is performed, but the length of
 * the encoded integer is still computed and returned.
 */
size_t br_asn1_encode_uint(void *dest, br_asn1_uint pp);

/*
 * Get the OID that identifies an elliptic curve. Returned value is
 * the DER-encoded OID, with the length (always one byte) but without
 * the tag. Thus, the first byte of the returned buffer contains the
 * number of subsequent bytes in the value. If the curve is not
 * recognised, NULL is returned.
 */
const unsigned char *br_get_curve_OID(int curve);

/*
 * Inner function for EC private key encoding. This is equivalent to
 * the API function br_encode_ec_raw_der(), except for an extra
 * parameter: if 'include_curve_oid' is zero, then the curve OID is
 * _not_ included in the output blob (this is for PKCS#8 support).
 */
size_t br_encode_ec_raw_der_inner(void *dest,
	const br_ec_private_key *sk, const br_ec_public_key *pk,
	int include_curve_oid);

/* ==================================================================== */
/*
 * SSL/TLS support functions.
 */

/*
 * Record types.
 */
#define BR_SSL_CHANGE_CIPHER_SPEC    20
#define BR_SSL_ALERT                 21
#define BR_SSL_HANDSHAKE             22
#define BR_SSL_APPLICATION_DATA      23

/*
 * Handshake message types.
 */
#define BR_SSL_HELLO_REQUEST          0
#define BR_SSL_CLIENT_HELLO           1
#define BR_SSL_SERVER_HELLO           2
#define BR_SSL_CERTIFICATE           11
#define BR_SSL_SERVER_KEY_EXCHANGE   12
#define BR_SSL_CERTIFICATE_REQUEST   13
#define BR_SSL_SERVER_HELLO_DONE     14
#define BR_SSL_CERTIFICATE_VERIFY    15
#define BR_SSL_CLIENT_KEY_EXCHANGE   16
#define BR_SSL_FINISHED              20

/*
 * Alert levels.
 */
#define BR_LEVEL_WARNING   1
#define BR_LEVEL_FATAL     2

/*
 * Low-level I/O state.
 */
#define BR_IO_FAILED   0
#define BR_IO_IN       1
#define BR_IO_OUT      2
#define BR_IO_INOUT    3

/*
 * Mark a SSL engine as failed. The provided error code is recorded if
 * the engine was not already marked as failed. If 'err' is 0, then the
 * engine is marked as closed (without error).
 */
void br_ssl_engine_fail(br_ssl_engine_context *cc, int err);

/*
 * Test whether the engine is closed (normally or as a failure).
 */
static inline int
br_ssl_engine_closed(const br_ssl_engine_context *cc)
{
	return cc->iomode == BR_IO_FAILED;
}

/*
 * Configure a new maximum fragment length. If possible, the maximum
 * length for outgoing records is immediately adjusted (if there are
 * not already too many buffered bytes for that).
 */
void br_ssl_engine_new_max_frag_len(
	br_ssl_engine_context *rc, unsigned max_frag_len);

/*
 * Test whether the current incoming record has been fully received
 * or not. This functions returns 0 only if a complete record header
 * has been received, but some of the (possibly encrypted) payload
 * has not yet been obtained.
 */
int br_ssl_engine_recvrec_finished(const br_ssl_engine_context *rc);

/*
 * Flush the current record (if not empty). This is meant to be called
 * from the handshake processor only.
 */
void br_ssl_engine_flush_record(br_ssl_engine_context *cc);

/*
 * Test whether there is some accumulated payload to send.
 */
static inline int
br_ssl_engine_has_pld_to_send(const br_ssl_engine_context *rc)
{
	return rc->oxa != rc->oxb && rc->oxa != rc->oxc;
}

/*
 * Initialize RNG in engine. Returned value is 1 on success, 0 on error.
 * This function will try to use the OS-provided RNG, if available. If
 * there is no OS-provided RNG, or if it failed, and no entropy was
 * injected by the caller, then a failure will be reported. On error,
 * the context error code is set.
 */
int br_ssl_engine_init_rand(br_ssl_engine_context *cc);

/*
 * Reset the handshake-related parts of the engine.
 */
void br_ssl_engine_hs_reset(br_ssl_engine_context *cc,
	void (*hsinit)(void *), void (*hsrun)(void *));

/*
 * Get the PRF to use for this context, for the provided PRF hash
 * function ID.
 */
br_tls_prf_impl br_ssl_engine_get_PRF(br_ssl_engine_context *cc, int prf_id);

/*
 * Consume the provided pre-master secret and compute the corresponding
 * master secret. The 'prf_id' is the ID of the hash function to use
 * with the TLS 1.2 PRF (ignored if the version is TLS 1.0 or 1.1).
 */
void br_ssl_engine_compute_master(br_ssl_engine_context *cc,
	int prf_id, const void *pms, size_t len);

/*
 * Switch to CBC decryption for incoming records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF (ignored if not TLS 1.2+)
 *    mac_id           id of hash function for HMAC
 *    bc_impl          block cipher implementation (CBC decryption)
 *    cipher_key_len   block cipher key length (in bytes)
 */
void br_ssl_engine_switch_cbc_in(br_ssl_engine_context *cc,
	int is_client, int prf_id, int mac_id,
	const br_block_cbcdec_class *bc_impl, size_t cipher_key_len);

/*
 * Switch to CBC encryption for outgoing records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF (ignored if not TLS 1.2+)
 *    mac_id           id of hash function for HMAC
 *    bc_impl          block cipher implementation (CBC encryption)
 *    cipher_key_len   block cipher key length (in bytes)
 */
void br_ssl_engine_switch_cbc_out(br_ssl_engine_context *cc,
	int is_client, int prf_id, int mac_id,
	const br_block_cbcenc_class *bc_impl, size_t cipher_key_len);

/*
 * Switch to GCM decryption for incoming records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF
 *    bc_impl          block cipher implementation (CTR)
 *    cipher_key_len   block cipher key length (in bytes)
 */
void br_ssl_engine_switch_gcm_in(br_ssl_engine_context *cc,
	int is_client, int prf_id,
	const br_block_ctr_class *bc_impl, size_t cipher_key_len);

/*
 * Switch to GCM encryption for outgoing records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF
 *    bc_impl          block cipher implementation (CTR)
 *    cipher_key_len   block cipher key length (in bytes)
 */
void br_ssl_engine_switch_gcm_out(br_ssl_engine_context *cc,
	int is_client, int prf_id,
	const br_block_ctr_class *bc_impl, size_t cipher_key_len);

/*
 * Switch to ChaCha20+Poly1305 decryption for incoming records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF
 */
void br_ssl_engine_switch_chapol_in(br_ssl_engine_context *cc,
	int is_client, int prf_id);

/*
 * Switch to ChaCha20+Poly1305 encryption for outgoing records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF
 */
void br_ssl_engine_switch_chapol_out(br_ssl_engine_context *cc,
	int is_client, int prf_id);

/*
 * Switch to CCM decryption for incoming records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF
 *    bc_impl          block cipher implementation (CTR+CBC)
 *    cipher_key_len   block cipher key length (in bytes)
 *    tag_len          tag length (in bytes)
 */
void br_ssl_engine_switch_ccm_in(br_ssl_engine_context *cc,
	int is_client, int prf_id,
	const br_block_ctrcbc_class *bc_impl,
	size_t cipher_key_len, size_t tag_len);

/*
 * Switch to GCM encryption for outgoing records.
 *    cc               the engine context
 *    is_client        non-zero for a client, zero for a server
 *    prf_id           id of hash function for PRF
 *    bc_impl          block cipher implementation (CTR+CBC)
 *    cipher_key_len   block cipher key length (in bytes)
 *    tag_len          tag length (in bytes)
 */
void br_ssl_engine_switch_ccm_out(br_ssl_engine_context *cc,
	int is_client, int prf_id,
	const br_block_ctrcbc_class *bc_impl,
	size_t cipher_key_len, size_t tag_len);

/*
 * Calls to T0-generated code.
 */
void br_ssl_hs_client_init_main(void *ctx);
void br_ssl_hs_client_run(void *ctx);
void br_ssl_hs_server_init_main(void *ctx);
void br_ssl_hs_server_run(void *ctx);

/*
 * Get the hash function to use for signatures, given a bit mask of
 * supported hash functions. This implements a strict choice order
 * (namely SHA-256, SHA-384, SHA-512, SHA-224, SHA-1). If the mask
 * does not document support of any of these hash functions, then this
 * functions returns 0.
 */
int br_ssl_choose_hash(unsigned bf);

/* ==================================================================== */

/*
 * PowerPC / POWER assembly stuff. The special BR_POWER_ASM_MACROS macro
 * must be defined before including this file; this is done by source
 * files that use some inline assembly for PowerPC / POWER machines.
 */

#if BR_POWER_ASM_MACROS

#define lxvw4x(xt, ra, rb)        lxvw4x_(xt, ra, rb)
#define stxvw4x(xt, ra, rb)       stxvw4x_(xt, ra, rb)

#define bdnz(foo)                 bdnz_(foo)
#define bdz(foo)                  bdz_(foo)
#define beq(foo)                  beq_(foo)

#define li(rx, value)             li_(rx, value)
#define addi(rx, ra, imm)         addi_(rx, ra, imm)
#define cmpldi(rx, imm)           cmpldi_(rx, imm)
#define mtctr(rx)                 mtctr_(rx)
#define vspltb(vrt, vrb, uim)     vspltb_(vrt, vrb, uim)
#define vspltw(vrt, vrb, uim)     vspltw_(vrt, vrb, uim)
#define vspltisb(vrt, imm)        vspltisb_(vrt, imm)
#define vspltisw(vrt, imm)        vspltisw_(vrt, imm)
#define vrlw(vrt, vra, vrb)       vrlw_(vrt, vra, vrb)
#define vsbox(vrt, vra)           vsbox_(vrt, vra)
#define vxor(vrt, vra, vrb)       vxor_(vrt, vra, vrb)
#define vand(vrt, vra, vrb)       vand_(vrt, vra, vrb)
#define vsro(vrt, vra, vrb)       vsro_(vrt, vra, vrb)
#define vsl(vrt, vra, vrb)        vsl_(vrt, vra, vrb)
#define vsldoi(vt, va, vb, sh)    vsldoi_(vt, va, vb, sh)
#define vsr(vrt, vra, vrb)        vsr_(vrt, vra, vrb)
#define vaddcuw(vrt, vra, vrb)    vaddcuw_(vrt, vra, vrb)
#define vadduwm(vrt, vra, vrb)    vadduwm_(vrt, vra, vrb)
#define vsububm(vrt, vra, vrb)    vsububm_(vrt, vra, vrb)
#define vsubuwm(vrt, vra, vrb)    vsubuwm_(vrt, vra, vrb)
#define vsrw(vrt, vra, vrb)       vsrw_(vrt, vra, vrb)
#define vcipher(vt, va, vb)       vcipher_(vt, va, vb)
#define vcipherlast(vt, va, vb)   vcipherlast_(vt, va, vb)
#define vncipher(vt, va, vb)      vncipher_(vt, va, vb)
#define vncipherlast(vt, va, vb)  vncipherlast_(vt, va, vb)
#define vperm(vt, va, vb, vc)     vperm_(vt, va, vb, vc)
#define vpmsumd(vt, va, vb)       vpmsumd_(vt, va, vb)
#define xxpermdi(vt, va, vb, d)   xxpermdi_(vt, va, vb, d)

#define lxvw4x_(xt, ra, rb)       "\tlxvw4x\t" #xt "," #ra "," #rb "\n"
#define stxvw4x_(xt, ra, rb)      "\tstxvw4x\t" #xt "," #ra "," #rb "\n"

#define label(foo)                #foo "%=:\n"
#define bdnz_(foo)                "\tbdnz\t" #foo "%=\n"
#define bdz_(foo)                 "\tbdz\t" #foo "%=\n"
#define beq_(foo)                 "\tbeq\t" #foo "%=\n"

#define li_(rx, value)            "\tli\t" #rx "," #value "\n"
#define addi_(rx, ra, imm)        "\taddi\t" #rx "," #ra "," #imm "\n"
#define cmpldi_(rx, imm)          "\tcmpldi\t" #rx "," #imm "\n"
#define mtctr_(rx)                "\tmtctr\t" #rx "\n"
#define vspltb_(vrt, vrb, uim)    "\tvspltb\t" #vrt "," #vrb "," #uim "\n"
#define vspltw_(vrt, vrb, uim)    "\tvspltw\t" #vrt "," #vrb "," #uim "\n"
#define vspltisb_(vrt, imm)       "\tvspltisb\t" #vrt "," #imm "\n"
#define vspltisw_(vrt, imm)       "\tvspltisw\t" #vrt "," #imm "\n"
#define vrlw_(vrt, vra, vrb)      "\tvrlw\t" #vrt "," #vra "," #vrb "\n"
#define vsbox_(vrt, vra)          "\tvsbox\t" #vrt "," #vra "\n"
#define vxor_(vrt, vra, vrb)      "\tvxor\t" #vrt "," #vra "," #vrb "\n"
#define vand_(vrt, vra, vrb)      "\tvand\t" #vrt "," #vra "," #vrb "\n"
#define vsro_(vrt, vra, vrb)      "\tvsro\t" #vrt "," #vra "," #vrb "\n"
#define vsl_(vrt, vra, vrb)       "\tvsl\t" #vrt "," #vra "," #vrb "\n"
#define vsldoi_(vt, va, vb, sh)   "\tvsldoi\t" #vt "," #va "," #vb "," #sh "\n"
#define vsr_(vrt, vra, vrb)       "\tvsr\t" #vrt "," #vra "," #vrb "\n"
#define vaddcuw_(vrt, vra, vrb)   "\tvaddcuw\t" #vrt "," #vra "," #vrb "\n"
#define vadduwm_(vrt, vra, vrb)   "\tvadduwm\t" #vrt "," #vra "," #vrb "\n"
#define vsububm_(vrt, vra, vrb)   "\tvsububm\t" #vrt "," #vra "," #vrb "\n"
#define vsubuwm_(vrt, vra, vrb)   "\tvsubuwm\t" #vrt "," #vra "," #vrb "\n"
#define vsrw_(vrt, vra, vrb)      "\tvsrw\t" #vrt "," #vra "," #vrb "\n"
#define vcipher_(vt, va, vb)      "\tvcipher\t" #vt "," #va "," #vb "\n"
#define vcipherlast_(vt, va, vb)  "\tvcipherlast\t" #vt "," #va "," #vb "\n"
#define vncipher_(vt, va, vb)     "\tvncipher\t" #vt "," #va "," #vb "\n"
#define vncipherlast_(vt, va, vb) "\tvncipherlast\t" #vt "," #va "," #vb "\n"
#define vperm_(vt, va, vb, vc)    "\tvperm\t" #vt "," #va "," #vb "," #vc "\n"
#define vpmsumd_(vt, va, vb)      "\tvpmsumd\t" #vt "," #va "," #vb "\n"
#define xxpermdi_(vt, va, vb, d)  "\txxpermdi\t" #vt "," #va "," #vb "," #d "\n"

#endif

/* ==================================================================== */
/*
 * Special "activate intrinsics" code, needed for some compiler versions.
 * This is defined at the end of this file, so that it won't impact any
 * of the inline functions defined previously; and it is controlled by
 * a specific macro defined in the caller code.
 *
 * Calling code conventions:
 *
 *  - Caller must define BR_ENABLE_INTRINSICS before including "inner.h".
 *  - Functions that use intrinsics must be enclosed in an "enabled"
 *    region (between BR_TARGETS_X86_UP and BR_TARGETS_X86_DOWN).
 *  - Functions that use intrinsics must be tagged with the appropriate
 *    BR_TARGET().
 */

#if BR_ENABLE_INTRINSICS && (BR_GCC_4_4 || BR_CLANG_3_7 || BR_MSC_2005)

/*
 * x86 intrinsics (both 32-bit and 64-bit).
 */
#if BR_i386 || BR_amd64

/*
 * On GCC before version 5.0, we need to use the pragma to enable the
 * target options globally, because the 'target' function attribute
 * appears to be unreliable. Before 4.6 we must also avoid the
 * push_options / pop_options mechanism, because it tends to trigger
 * some internal compiler errors.
 */
#if BR_GCC && !BR_GCC_5_0
#if BR_GCC_4_6
#define BR_TARGETS_X86_UP \
	_Pragma("GCC push_options") \
	_Pragma("GCC target(\"sse2,ssse3,sse4.1,aes,pclmul,rdrnd\")")
#define BR_TARGETS_X86_DOWN \
	_Pragma("GCC pop_options")
#else
#define BR_TARGETS_X86_UP \
	_Pragma("GCC target(\"sse2,ssse3,sse4.1,aes,pclmul\")")
#define BR_TARGETS_X86_DOWN
#endif
#pragma GCC diagnostic ignored "-Wpsabi"
#endif

#if BR_CLANG && !BR_CLANG_3_8
#undef __SSE2__
#undef __SSE3__
#undef __SSSE3__
#undef __SSE4_1__
#undef __AES__
#undef __PCLMUL__
#undef __RDRND__
#define __SSE2__     1
#define __SSE3__     1
#define __SSSE3__    1
#define __SSE4_1__   1
#define __AES__      1
#define __PCLMUL__   1
#define __RDRND__    1
#endif

#ifndef BR_TARGETS_X86_UP
#define BR_TARGETS_X86_UP
#endif
#ifndef BR_TARGETS_X86_DOWN
#define BR_TARGETS_X86_DOWN
#endif

#if BR_GCC || BR_CLANG
BR_TARGETS_X86_UP
#include <x86intrin.h>
#include <cpuid.h>
#define br_bswap32   __builtin_bswap32
BR_TARGETS_X86_DOWN
#endif

#if BR_MSC
#include <stdlib.h>
#include <intrin.h>
#include <immintrin.h>
#define br_bswap32   __src_inner_hbyteswap_ulong
#endif

static inline int
br_cpuid(uint32_t mask_eax, uint32_t mask_ebx,
	uint32_t mask_ecx, uint32_t mask_edx)
{
#if BR_GCC || BR_CLANG
	unsigned eax, ebx, ecx, edx;

	if (__get_cpuid(1, &eax, &ebx, &ecx, &edx)) {
		if ((eax & mask_eax) == mask_eax
			&& (ebx & mask_ebx) == mask_ebx
			&& (ecx & mask_ecx) == mask_ecx
			&& (edx & mask_edx) == mask_edx)
		{
			return 1;
		}
	}
#elif BR_MSC
	int info[4];

	__cpuid(info, 1);
	if (((uint32_t)info[0] & mask_eax) == mask_eax
		&& ((uint32_t)info[1] & mask_ebx) == mask_ebx
		&& ((uint32_t)info[2] & mask_ecx) == mask_ecx
		&& ((uint32_t)info[3] & mask_edx) == mask_edx)
	{
		return 1;
	}
#endif
	return 0;
}

#endif

#endif

/* ==================================================================== */

#endif
