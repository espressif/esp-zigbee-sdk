/*
 * sais.c for sais-lite
 * Copyright (c) 2008-2010 Yuta Mori All Rights Reserved.
 * Copyright (c) 2019, Erik Moqvist (Python wrapper).
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <Python.h>

#ifndef UCHAR_SIZE
#    define UCHAR_SIZE 256
#endif

#ifndef MINBUCKETSIZE
#    define MINBUCKETSIZE 256
#endif

#define SAIS_LMSSORT2_LIMIT 0x3fffffff

#define SAIS_MYMALLOC(_num, _type) ((_type *)malloc((_num) * sizeof(_type)))
#define SAIS_MYFREE(_ptr, _num, _type) free((_ptr))
#define chr(_a) (cs == sizeof(int32_t)          \
                 ? ((int32_t *)t_p)[(_a)]       \
                 : ((uint8_t *)t_p)[(_a)])

/* find the start or end of each bucket */
static void get_counts(const void *t_p,
                       int32_t *c_p,
                       int32_t n,
                       int32_t k,
                       int32_t cs)
{
    int32_t i;

    for (i = 0; i < k; ++i) {
        c_p[i] = 0;
    }

    for (i = 0; i < n; ++i) {
        ++c_p[chr(i)];
    }
}

static void get_buckets(const int32_t *c_p,
                        int32_t *b_p,
                        int32_t k,
                        int32_t end)
{
    int32_t i;
    int32_t sum;

    sum = 0;

    if (end) {
        for (i = 0; i < k; ++i) {
            sum += c_p[i];
            b_p[i] = sum;
        }
    } else {
        for (i = 0; i < k; ++i) {
            sum += c_p[i];
            b_p[i] = sum - c_p[i];
        }
    }
}

/* sort all type LMS suffixes */
static void lms_sort_1(const void *t_p,
                       int32_t *sa_p,
                       int32_t *c_p,
                       int32_t *b_p,
                       int32_t n,
                       int32_t k,
                       int32_t cs)
{
    int32_t *b2_p;
    int32_t i;
    int32_t j;
    int32_t c0;
    int32_t c1;

    /* compute SAl */
    if (c_p == b_p) {
        get_counts(t_p, c_p, n, k, cs);
    }

    get_buckets(c_p, b_p, k, 0); /* find starts of buckets */
    j = n - 1;
    b2_p = sa_p + b_p[c1 = chr(j)];
    --j;
    *b2_p++ = (chr(j) < c1) ? ~j : j;

    for (i = 0; i < n; ++i) {
        if (0 < (j = sa_p[i])) {
            assert(chr(j) >= chr(j + 1));

            if ((c0 = chr(j)) != c1) {
                b_p[c1] = (int32_t)(b2_p - sa_p);
                b2_p = sa_p + b_p[c1 = c0];
            }

            assert(i < (b2_p - sa_p));
            --j;
            *b2_p++ = (chr(j) < c1) ? ~j : j;
            sa_p[i] = 0;
        } else if (j < 0) {
            sa_p[i] = ~j;
        }
    }

    /* compute SAs */
    if (c_p == b_p) {
        get_counts(t_p, c_p, n, k, cs);
    }

    get_buckets(c_p, b_p, k, 1); /* find ends of buckets */

    for (i = n - 1, b2_p = sa_p + b_p[c1 = 0]; 0 <= i; --i) {
        if (0 < (j = sa_p[i])) {
            assert(chr(j) <= chr(j + 1));

            if ((c0 = chr(j)) != c1) {
                b_p[c1] = (int32_t)(b2_p - sa_p);
                b2_p = sa_p + b_p[c1 = c0];
            }

            assert((b2_p - sa_p) <= i);
            --j;
            *--b2_p = (chr(j) > c1) ? ~(j + 1) : j;
            sa_p[i] = 0;
        }
    }
}

static int32_t lms_postproc_1(const void *t_p,
                              int32_t *sa_p,
                              int32_t n,
                              int32_t m,
                              int32_t cs)
{
    int32_t i;
    int32_t j;
    int32_t p;
    int32_t q;
    int32_t plen;
    int32_t qlen;
    int32_t name;
    int32_t c0;
    int32_t c1;
    int32_t diff;

    /* compact all the sorted substrings into the first m items of SA
       2*m must be not larger than n (proveable) */
    assert(0 < n);

    for (i = 0; (p = sa_p[i]) < 0; ++i) {
        sa_p[i] = ~p;
        assert((i + 1) < n);
    }

    if (i < m) {
        for (j = i, ++i;; ++i) {
            assert(i < n);

            if ((p = sa_p[i]) < 0) {
                sa_p[j++] = ~p;
                sa_p[i] = 0;

                if (j == m) {
                    break;
                }
            }
        }
    }

    /* store the length of all substrings */
    i = n - 1;
    j = n - 1;
    c0 = chr(n - 1);

    do {
        c1 = c0;
    } while ((0 <= --i) && ((c0 = chr(i)) >= c1));

    while (0 <= i) {
        do {
            c1 = c0;
        } while ((0 <= --i) && ((c0 = chr(i)) <= c1));

        if (0 <= i) {
            sa_p[m + ((i + 1) >> 1)] = j - i; j = i + 1;

            do {
                c1 = c0;
            } while ((0 <= --i) && ((c0 = chr(i)) >= c1));
        }
    }

    /* find the lexicographic names of all substrings */
    for (i = 0, name = 0, q = n, qlen = 0; i < m; ++i) {
        p = sa_p[i], plen = sa_p[m + (p >> 1)], diff = 1;

        if ((plen == qlen) && ((q + plen) < n)) {
            for (j = 0; (j < plen) && (chr(p + j) == chr(q + j)); ++j);

            if (j == plen) {
                diff = 0;
            }
        }

        if (diff != 0) {
            ++name;
            q = p;
            qlen = plen;
        }

        sa_p[m + (p >> 1)] = name;
    }

    return (name);
}

static void lms_sort_2(const void *t_p,
                       int32_t *sa_p,
                       int32_t *c_p,
                       int32_t *b_p,
                       int32_t *d_p,
                       int32_t n,
                       int32_t k,
                       int32_t cs)
{
    int32_t *b2_p;
    int32_t i;
    int32_t j;
    int32_t t;
    int32_t d;
    int32_t c0;
    int32_t c1;

    assert(c_p != b_p);

    /* compute SAl */
    get_buckets(c_p, b_p, k, 0); /* find starts of buckets */
    j = n - 1;
    b2_p = sa_p + b_p[c1 = chr(j)];
    --j;
    t = (chr(j) < c1);
    j += n;
    *b2_p++ = (t & 1) ? ~j : j;

    for (i = 0, d = 0; i < n; ++i) {
        if (0 < (j = sa_p[i])) {
            if (n <= j) {
                d += 1;
                j -= n;
            }

            assert(chr(j) >= chr(j + 1));

            if ((c0 = chr(j)) != c1) {
                b_p[c1] = (int32_t)(b2_p - sa_p);
                b2_p = sa_p + b_p[c1 = c0];
            }

            assert(i < (b2_p - sa_p));
            --j;
            t = c0; t = (t << 1) | (chr(j) < c1);

            if (d_p[t] != d) {
                j += n;
                d_p[t] = d;
            }

            *b2_p++ = (t & 1) ? ~j : j;
            sa_p[i] = 0;
        } else if (j < 0) {
            sa_p[i] = ~j;
        }
    }

    for (i = n - 1; 0 <= i; --i) {
        if (0 < sa_p[i]) {
            if (sa_p[i] < n) {
                sa_p[i] += n;

                for (j = i - 1; sa_p[j] < n; --j);

                sa_p[j] -= n;
                i = j;
            }
        }
    }

    /* compute SAs */
    get_buckets(c_p, b_p, k, 1); /* find ends of buckets */

    for (i = n - 1, d += 1, b2_p = sa_p + b_p[c1 = 0]; 0 <= i; --i) {
        if (0 < (j = sa_p[i])) {
            if (n <= j) {
                d += 1;
                j -= n;
            }

            assert(chr(j) <= chr(j + 1));

            if ((c0 = chr(j)) != c1) {
                b_p[c1] = (int32_t)(b2_p - sa_p);
                b2_p = sa_p + b_p[c1 = c0];
            }

            assert((b2_p - sa_p) <= i);
            --j;
            t = c0;
            t = (t << 1) | (chr(j) > c1);

            if (d_p[t] != d) {
                j += n;
                d_p[t] = d;
            }

            *--b2_p = (t & 1) ? ~(j + 1) : j;
            sa_p[i] = 0;
        }
    }
}

static int32_t lms_postproc_2(int32_t *sa_p,
                              int32_t n,
                              int32_t m)
{
    int32_t i;
    int32_t j;
    int32_t d;
    int32_t name;

    /* compact all the sorted LMS substrings into the first m items of SA */
    assert(0 < n);

    for (i = 0, name = 0; (j = sa_p[i]) < 0; ++i) {
        j = ~j;

        if (n <= j) {
            name += 1;
        }

        sa_p[i] = j;
        assert((i + 1) < n);
    }

    if (i < m) {
        for (d = i, ++i;; ++i) {
            assert(i < n);

            if ((j = sa_p[i]) < 0) {
                j = ~j;

                if (n <= j) {
                    name += 1;
                }

                sa_p[d++] = j;
                sa_p[i] = 0;

                if (d == m) {
                    break;
                }
            }
        }
    }

    if (name < m) {
        /* store the lexicographic names */
        for (i = m - 1, d = name + 1; 0 <= i; --i) {
            if (n <= (j = sa_p[i])) {
                j -= n;
                --d;
            }

            sa_p[m + (j >> 1)] = d;
        }
    } else {
        /* unset flags */
        for (i = 0; i < m; ++i) {
            if (n <= (j = sa_p[i])) {
                j -= n;
                sa_p[i] = j;
            }
        }
    }

    return (name);
}

/* compute SA and BWT */
static void induce_sa(const void *t_p,
                      int32_t *sa_p,
                      int32_t *c_p,
                      int32_t *b_p,
                      int32_t n,
                      int32_t k,
                      int32_t cs)
{
    int32_t *b;
    int32_t i;
    int32_t j;
    int32_t c0;
    int32_t c1;

    /* compute SAl */
    if (c_p == b_p) {
        get_counts(t_p, c_p, n, k, cs);
    }

    get_buckets(c_p, b_p, k, 0); /* find starts of buckets */
    j = n - 1;
    b = sa_p + b_p[c1 = chr(j)];
    *b++ = ((0 < j) && (chr(j - 1) < c1)) ? ~j : j;

    for (i = 0; i < n; ++i) {
        j = sa_p[i];
        sa_p[i] = ~j;

        if (0 < j) {
            --j;
            assert(chr(j) >= chr(j + 1));

            if ((c0 = chr(j)) != c1) {
                b_p[c1] = (int32_t)(b - sa_p);
                b = sa_p + b_p[c1 = c0];
            }

            assert(i < (b - sa_p));
            *b++ = ((0 < j) && (chr(j - 1) < c1)) ? ~j : j;
        }
    }

    /* compute SAs */
    if (c_p == b_p) {
        get_counts(t_p, c_p, n, k, cs);
    }

    get_buckets(c_p, b_p, k, 1); /* find ends of buckets */

    for (i = n - 1, b = sa_p + b_p[c1 = 0]; 0 <= i; --i) {
        if (0 < (j = sa_p[i])) {
            --j;
            assert(chr(j) <= chr(j + 1));

            if ((c0 = chr(j)) != c1) {
                b_p[c1] = (int32_t)(b - sa_p);
                b = sa_p + b_p[c1 = c0];
            }

            assert((b - sa_p) <= i);
            *--b = ((j == 0) || (chr(j - 1) > c1)) ? ~j : j;
        } else {
            sa_p[i] = ~j;
        }
    }
}

/* find the suffix array SA of T[0..n-1] in {0..255}^n */
static int32_t sais_main(const void *t_p,
                         int32_t *sa_p,
                         int32_t fs,
                         int32_t n,
                         int32_t k,
                         int32_t cs)
{
    int32_t *c_p;
    int32_t *b_p;
    int32_t *d_p;
    int32_t *ra_p;
    int32_t *b;
    int32_t i;
    int32_t j;
    int32_t m;
    int32_t p;
    int32_t q;
    int32_t t;
    int32_t name;
    int32_t newfs;
    int32_t c0;
    int32_t c1;
    unsigned int flags;

    assert((t_p != NULL) && (sa_p != NULL));
    assert((0 <= fs) && (0 < n) && (1 <= k));

    if (k <= MINBUCKETSIZE) {
        if ((c_p = SAIS_MYMALLOC(k, int32_t)) == NULL) {
            return -2;
        }

        if (k <= fs) {
            b_p = sa_p + (n + fs - k);
            flags = 1;
        } else {
            if ((b_p = SAIS_MYMALLOC(k, int32_t)) == NULL) {
                SAIS_MYFREE(c_p, k, int32_t);

                return (-2);
            }

            flags = 3;
        }
    } else if (k <= fs) {
        c_p = sa_p + (n + fs - k);

        if (k <= (fs - k)) {
            b_p = c_p - k;
            flags = 0;
        } else if (k <= (MINBUCKETSIZE * 4)) {
            if ((b_p = SAIS_MYMALLOC(k, int32_t)) == NULL) {
                return (-2);
            }

            flags = 2;
        } else {
            b_p = c_p;
            flags = 8;
        }
    } else {
        if ((c_p = b_p = SAIS_MYMALLOC(k, int32_t)) == NULL) {
            return (-2);
        }

        flags = 4 | 8;
    }

    if ((n <= SAIS_LMSSORT2_LIMIT) && (2 <= (n / k))) {
        if (flags & 1) {
            flags |= ((k * 2) <= (fs - k)) ? 32 : 16;
        } else if ((flags == 0) && ((k * 2) <= (fs - k * 2))) {
            flags |= 32;
        }
    }

    /* stage 1: reduce the problem by at least 1/2
       sort all the LMS-substrings */
    get_counts(t_p, c_p, n, k, cs);
    get_buckets(c_p, b_p, k, 1); /* find ends of buckets */

    for (i = 0; i < n; ++i) {
        sa_p[i] = 0;
    }

    b = &t;
    i = n - 1;
    j = n;
    m = 0;
    c0 = chr(n - 1);

    do {
        c1 = c0;
    } while ((0 <= --i) && ((c0 = chr(i)) >= c1));

    while (0 <= i) {
        do {
            c1 = c0;
        } while ((0 <= --i) && ((c0 = chr(i)) <= c1));

        if (0 <= i) {
            *b = j;
            b = sa_p + --b_p[c1];
            j = i;
            ++m;

            do {
                c1 = c0;
            } while ((0 <= --i) && ((c0 = chr(i)) >= c1));
        }
    }

    if (1 < m) {
        if (flags & (16 | 32)) {
            if (flags & 16) {
                if ((d_p = SAIS_MYMALLOC(k * 2, int32_t)) == NULL) {
                    if (flags & (1 | 4)) {
                        SAIS_MYFREE(c_p, k, int32_t);
                    }

                    if (flags & 2) {
                        SAIS_MYFREE(b_p, k, int32_t);
                    }

                    return (-2);
                }
            } else {
                d_p = b_p - k * 2;
            }

            assert((j + 1) < n);
            ++b_p[chr(j + 1)];

            for (i = 0, j = 0; i < k; ++i) {
                j += c_p[i];

                if (b_p[i] != j) {
                    assert(sa_p[b_p[i]] != 0);
                    sa_p[b_p[i]] += n;
                }

                d_p[i] = d_p[i + k] = 0;
            }

            lms_sort_2(t_p, sa_p, c_p, b_p, d_p, n, k, cs);
            name = lms_postproc_2(sa_p, n, m);

            if (flags & 16) {
                SAIS_MYFREE(d_p, k * 2, int32_t);
            }
        } else {
            lms_sort_1(t_p, sa_p, c_p, b_p, n, k, cs);
            name = lms_postproc_1(t_p, sa_p, n, m, cs);
        }
    } else if (m == 1) {
        *b = j + 1;
        name = 1;
    } else {
        name = 0;
    }

    /* stage 2: solve the reduced problem
       recurse if names are not yet unique */
    if (name < m) {
        if (flags & 4) {
            SAIS_MYFREE(c_p, k, int32_t);
        }

        if (flags & 2) {
            SAIS_MYFREE(b_p, k, int32_t);
        }

        newfs = (n + fs) - (m * 2);

        if ((flags & (1 | 4 | 8)) == 0) {
            if ((k + name) <= newfs) {
                newfs -= k;
            } else {
                flags |= 8;
            }
        }

        assert((n >> 1) <= (newfs + m));
        ra_p = sa_p + m + newfs;

        for (i = m + (n >> 1) - 1, j = m - 1; m <= i; --i) {
            if (sa_p[i] != 0) {
                ra_p[j--] = sa_p[i] - 1;
            }
        }

        if (sais_main(ra_p, sa_p, newfs, m, name, sizeof(int32_t)) != 0) {
            if (flags & 1) {
                SAIS_MYFREE(c_p, k, int32_t);
            }

            return (-2);
        }

        i = n - 1;
        j = m - 1;
        c0 = chr(n - 1);

        do {
            c1 = c0;
        } while ((0 <= --i) && ((c0 = chr(i)) >= c1));

        while (0 <= i) {
            do {
                c1 = c0;
            } while ((0 <= --i) && ((c0 = chr(i)) <= c1));

            if (0 <= i) {
                ra_p[j--] = i + 1;

                do {
                    c1 = c0;
                } while ((0 <= --i) && ((c0 = chr(i)) >= c1));
            }
        }

        for (i = 0; i < m; ++i) {
            sa_p[i] = ra_p[sa_p[i]];
        }

        if (flags & 4) {
            if ((c_p = b_p = SAIS_MYMALLOC(k, int32_t)) == NULL) {
                return (-2);
            }
        }

        if (flags & 2) {
            if ((b_p = SAIS_MYMALLOC(k, int32_t)) == NULL) {
                if (flags & 1) {
                    SAIS_MYFREE(c_p, k, int32_t);
                }

                return (-2);
            }
        }
    }

    /* stage 3: induce the result for the original problem */
    if (flags & 8) {
        get_counts(t_p, c_p, n, k, cs);
    }

    /* put all left-most S characters into their buckets */
    if (1 < m) {
        get_buckets(c_p, b_p, k, 1); /* find ends of buckets */
        i = m - 1;
        j = n;
        p = sa_p[m - 1];
        c1 = chr(p);

        do {
            q = b_p[c0 = c1];

            while (q < j) {
                sa_p[--j] = 0;
            }

            do {
                sa_p[--j] = p;

                if (--i < 0) {
                    break;
                }

                p = sa_p[i];
            } while ((c1 = chr(p)) == c0);
        } while (0 <= i);

        while (0 < j) {
            sa_p[--j] = 0;
        }
    }

    induce_sa(t_p, sa_p, c_p, b_p, n, k, cs);

    if (flags & (1 | 4)) {
        SAIS_MYFREE(c_p, k, int32_t);
    }

    if (flags & 2) {
        SAIS_MYFREE(b_p, k, int32_t);
    }

    return (0);
}

int32_t sais(const uint8_t *t_p, int32_t *sa_p, int32_t n)
{
    if ((t_p == NULL) || (sa_p == NULL) || (n < 0)) {
        return (-1);
    }

    if (n <= 1) {
        if (n == 1) {
            sa_p[0] = 0;
        }

        return (0);
    }

    return (sais_main(t_p, sa_p, 0, n, UCHAR_SIZE, sizeof(uint8_t)));
}
