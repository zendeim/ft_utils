// bench.c
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stddef.h>
#include <string.h>

// -----------------------------------------------------------------------------
// Main configuration + entry point
// -----------------------------------------------------------------------------

// Adjust these to control benchmark sizes.
#define PERM_N      10u   // will generate 9! = 362,880 permutations per run
#define PERM_RUNS   1u

#define COMB_N      30u  // choose k from n = 30 choose 5 ~ 142,506 per run
#define COMB_K      5u
#define COMB_RUNS   20u

// -----------------------------------------------------------------------------
// Your functions – provided in another translation unit.
// -----------------------------------------------------------------------------
bool next_perm(size_t *perm, size_t perm_size, size_t max_size);
bool next_comb(size_t *comb, size_t comb_size, size_t max_size);
#define LUT_MAX 64u  // must be >= max_size used in tests

// -----------------------------------------------------------------------------
// Reference algorithms
// -----------------------------------------------------------------------------

// Classic lexicographic next_permutation (like std::next_permutation)
// Expects perm to hold a permutation, typically starting from 0..perm_size-1.
// max_size is ignored here, but kept for a compatible signature.
// static bool next_perm_ref(size_t *perm, size_t perm_size, size_t max_size)
// {
//     (void)max_size;
//     if (perm_size < 2)
//         return false;

//     // 1) Find rightmost i such that perm[i - 1] < perm[i]
//     size_t i = perm_size - 1;
//     while (i > 0 && perm[i - 1] >= perm[i])
//         --i;

//     if (i == 0)
//         return false; // last permutation already

//     // 2) Find rightmost element greater than perm[i - 1]
//     size_t j = perm_size - 1;
//     while (perm[j] <= perm[i - 1])
//         --j;

//     // 3) Swap them
//     size_t tmp = perm[i - 1];
//     perm[i - 1] = perm[j];
//     perm[j] = tmp;

//     // 4) Reverse suffix [i, end)
//     size_t k = perm_size - 1;
//     while (i < k)
//     {
//         tmp = perm[i];
//         perm[i] = perm[k];
//         perm[k] = tmp;
//         ++i;
//         --k;
//     }
//     return true;
// }

static bool next_perm_ref(size_t *perm, size_t perm_size, size_t max_size)
{
    if (perm_size == 0 || perm_size > max_size)
        return false;
    if (max_size > LUT_MAX)
        return false; // or handle error as you prefer

    // Try to increment from the rightmost position.
    // For each position `pos`, we:
    //   1) Mark numbers used in the prefix [0..pos-1].
    //   2) Find the next larger unused number for perm[pos].
    //   3) Fill the suffix [pos+1..perm_size) with the smallest unused numbers.
    for (size_t pos = perm_size; pos-- > 0; )
    {
        bool used[LUT_MAX];
        for (size_t i = 0; i < max_size; ++i)
            used[i] = false;

        // Mark prefix values as used
        for (size_t i = 0; i < pos; ++i)
            used[perm[i]] = true;

        size_t current = perm[pos];

        // Look for next candidate > current that is not used
        for (size_t candidate = current + 1; candidate < max_size; ++candidate)
        {
            if (!used[candidate])
            {
                perm[pos] = candidate;
                used[candidate] = true;

                // Fill suffix with smallest unused values
                size_t idx = pos + 1;
                for (size_t v = 0; v < max_size && idx < perm_size; ++v)
                {
                    if (!used[v])
                    {
                        perm[idx] = v;
                        ++idx;
                    }
                }

                return true;
            }
        }
        // No candidate at this pos; move left and try again
    }

    // No position could be incremented => last permutation
    return false;
}

// static bool next_perm_ref_rec(size_t *perm,
//                               size_t  perm_size,
//                               size_t  max_size,
//                               size_t  pos)
// {
//     bool used[LUT_MAX];

//     /* 1) Try to increment position `pos` while keeping prefix fixed. */

//     /* Mark values used in prefix [0..pos-1]. */
//     for (size_t i = 0; i < max_size; ++i)
//         used[i] = false;
//     for (size_t i = 0; i < pos; ++i)
//         used[perm[i]] = true;

//     size_t current = perm[pos];

//     /* Look for next larger unused value for this position. */
//     for (size_t v = current + 1; v < max_size; ++v) {
//         if (!used[v]) {
//             perm[pos] = v;
//             used[v] = true;

//             /* Fill suffix [pos+1 .. perm_size) with smallest unused values. */
//             size_t idx = pos + 1;
//             for (size_t val = 0; val < max_size && idx < perm_size; ++val) {
//                 if (!used[val]) {
//                     perm[idx] = val;
//                     ++idx;
//                 }
//             }
//             return true;
//         }
//     }

//     /* 2) Cannot increment at this position: recursively advance the prefix. */

//     if (pos == 0)
//         return false;  /* no more permutations */

//     if (!next_perm_ref_rec(perm, perm_size, max_size, pos - 1))
//         return false;

//     /* 3) Prefix [0..pos-1] has been advanced; rebuild suffix from `pos`. */

//     for (size_t i = 0; i < max_size; ++i)
//         used[i] = false;
//     for (size_t i = 0; i < pos; ++i)
//         used[perm[i]] = true;

//     size_t idx = pos;
//     for (size_t val = 0; val < max_size && idx < perm_size; ++val) {
//         if (!used[val]) {
//             perm[idx] = val;
//             ++idx;
//         }
//     }
//     return true;
// }

// static bool next_perm_ref(size_t *perm, size_t perm_size, size_t max_size)
// {
//     if (perm_size == 0 || perm_size > max_size || max_size > LUT_MAX)
//         return false;

//     /* Start recursion from the last position. */
//     return next_perm_ref_rec(perm, perm_size, max_size, perm_size - 1);
// }

// Classic "next combination in lexicographic order"
// comb_size = k, max_size = n, elements are indices in [0, n).
// Assumes comb is strictly increasing and starts as [0,1,...,k-1].
static bool next_comb_ref(size_t *comb, size_t comb_size, size_t max_size)
{
    if (comb_size == 0 || comb_size > max_size)
        return false;

    size_t i = comb_size - 1;
    while (1)
    {
        // The maximum allowed value at position i is max_size - (comb_size - i)
        if (comb[i] < max_size - (comb_size - i))
        {
            comb[i]++;
            for (size_t j = i + 1; j < comb_size; ++j)
                comb[j] = comb[j - 1] + 1;
            return true;
        }
        if (i == 0)
            break;
        --i;
    }
    return false; // last combination already
}

// -----------------------------------------------------------------------------
// Benchmark utilities
// -----------------------------------------------------------------------------

#define LUT_MAX 64u  // your next_perm uses lut[64]

// Returns seconds
static double clock_seconds(clock_t start, clock_t end)
{
    return (double)(end - start) / (double)CLOCKS_PER_SEC;
}

// Type aliases for function pointers
typedef bool (*perm_fn_t)(size_t *perm, size_t perm_size, size_t max_size);
typedef bool (*comb_fn_t)(size_t *comb, size_t comb_size, size_t max_size);

// Benchmark all permutations of size n (with max_size = n).
// runs: how many times to iterate over the full permutation space.
static double benchmark_perm(perm_fn_t fn,
                             const char *label,
                             size_t perm_size,
                             size_t runs,
                             size_t *out_iterations)
{
    if (perm_size > LUT_MAX)
    {
        fprintf(stderr, "perm_size (%zu) > LUT_MAX (%u) – adjust LUT or perm_size.\n",
                perm_size, LUT_MAX);
        if (out_iterations) *out_iterations = 0;
        return 0.0;
    }

    size_t total_calls = 0;
    clock_t t0 = clock();

    for (size_t r = 0; r < runs; ++r)
    {
        size_t perm[LUT_MAX];
        for (size_t i = 0; i < perm_size; ++i)
            perm[i] = i; // start from identity permutation

        while (fn(perm, perm_size, perm_size))
            total_calls++;
    }

    clock_t t1 = clock();
    double seconds = clock_seconds(t0, t1);

    if (out_iterations)
        *out_iterations = total_calls;

    printf("Perm %-10s: %12zu transitions, time = %8.4f s (runs=%zu)\n",
           label, total_calls, seconds, runs);

    return seconds;
}

// Benchmark all combinations of size comb_size (k) from [0..max_size) (n).
static double benchmark_comb(comb_fn_t fn,
                             const char *label,
                             size_t comb_size,
                             size_t max_size,
                             size_t runs,
                             size_t *out_iterations)
{
    size_t total_calls = 0;
    clock_t t0 = clock();

    for (size_t r = 0; r < runs; ++r)
    {
        size_t comb[LUT_MAX]; // LUT_MAX is generous here; combinations don't use it
        if (max_size > LUT_MAX)
        {
            fprintf(stderr, "max_size (%zu) > LUT_MAX (%u) – increase LUT_MAX for combinations.\n",
                    max_size, LUT_MAX);
            if (out_iterations) *out_iterations = 0;
            return 0.0;
        }

        // Start with [0,1,...,k-1]
        for (size_t i = 0; i < comb_size; ++i)
            comb[i] = i;

        while (fn(comb, comb_size, max_size))
            total_calls++;
    }

    clock_t t1 = clock();
    double seconds = clock_seconds(t0, t1);

    if (out_iterations)
        *out_iterations = total_calls;

    printf("Comb %-10s: %12zu transitions, time = %8.4f s (runs=%zu)\n",
           label, total_calls, seconds, runs);

    return seconds;
}

// Optional: quick correctness check that your permutation
// sequence matches the reference sequence, for one full run.
static bool check_perm_sequence(size_t perm_size)
{
    if (perm_size > LUT_MAX)
        return false;

    size_t p_user[LUT_MAX];
    size_t p_ref[LUT_MAX];

    for (size_t i = 0; i < perm_size; ++i)
    {
        p_user[i] = i;
        p_ref[i] = i;
    }

    while (1)
    {
        bool ok = true;
        for (size_t i = 0; i < perm_size; ++i)
        {
            if (p_user[i] != p_ref[i])
            {
                ok = false;
                break;
            }
        }
        if (!ok)
        {
            fprintf(stderr, "Permutation mismatch detected.\n");
            return false;
        }

        bool u = next_perm(p_user, perm_size, perm_size);
        bool r = next_perm_ref(p_ref, perm_size, perm_size);

        if (u != r)
        {
            fprintf(stderr, "Permutation termination mismatch (user=%d, ref=%d).\n",
                    (int)u, (int)r);
            return false;
        }
        if (!u) // both false => finished
            break;
    }
    return true;
}

// Optional: quick correctness check for combinations.
static bool check_comb_sequence(size_t comb_size, size_t max_size)
{
    if (max_size > LUT_MAX)
        return false;

    size_t c_user[LUT_MAX];
    size_t c_ref[LUT_MAX];

    for (size_t i = 0; i < comb_size; ++i)
    {
        c_user[i] = i;
        c_ref[i] = i;
    }

    while (1)
    {
        bool ok = true;
        for (size_t i = 0; i < comb_size; ++i)
        {
            if (c_user[i] != c_ref[i])
            {
                ok = false;
                break;
            }
        }
        if (!ok)
        {
            fprintf(stderr, "Combination mismatch detected.\n");
            return false;
        }

        bool u = next_comb(c_user, comb_size, max_size);
        bool r = next_comb_ref(c_ref, comb_size, max_size);

        if (u != r)
        {
            fprintf(stderr, "Combination termination mismatch (user=%d, ref=%d).\n",
                    (int)u, (int)r);
            return false;
        }
        if (!u)
            break;
    }
    return true;
}

int main(void)
{
    printf("=== next_perm benchmark ===\n");
    if (!check_perm_sequence(PERM_N))
    {
        fprintf(stderr, "Permutation sequence check FAILED – aborting benchmarks.\n");
        return 1;
    }

    size_t perm_calls_ref = 0;
    size_t perm_calls_user = 0;
    double t_perm_ref = benchmark_perm(next_perm_ref, "reference",
                                       PERM_N, PERM_RUNS, &perm_calls_ref);
    double t_perm_user = benchmark_perm(next_perm, "user",
                                        PERM_N, PERM_RUNS, &perm_calls_user);

    if (perm_calls_ref != perm_calls_user)
    {
        fprintf(stderr, "Warning: perm call counts differ (ref=%zu, user=%zu).\n",
                perm_calls_ref, perm_calls_user);
    }
    printf("Permutation speed ratio (user / ref): %.3f\n\n",
           t_perm_user / t_perm_ref);

    printf("=== next_comb benchmark ===\n");
    if (!check_comb_sequence(COMB_K, COMB_N))
    {
        fprintf(stderr, "Combination sequence check FAILED – aborting benchmarks.\n");
        return 1;
    }

    size_t comb_calls_ref = 0;
    size_t comb_calls_user = 0;
    double t_comb_ref = benchmark_comb(next_comb_ref, "reference",
                                       COMB_K, COMB_N, COMB_RUNS, &comb_calls_ref);
    double t_comb_user = benchmark_comb(next_comb, "user",
                                        COMB_K, COMB_N, COMB_RUNS, &comb_calls_user);

    if (comb_calls_ref != comb_calls_user)
    {
        fprintf(stderr, "Warning: comb call counts differ (ref=%zu, user=%zu).\n",
                comb_calls_ref, comb_calls_user);
    }
    printf("Combination speed ratio (user / ref): %.3f\n",
           t_comb_user / t_comb_ref);

    return 0;
}
