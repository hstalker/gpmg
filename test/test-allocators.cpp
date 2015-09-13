#include <cstdlib>
#include <cstdio>
#include "gpmg/allocators.hpp"
#include "gpmg/misc.hpp"
#include "gpmg/testing.hpp"

using namespace std;
using namespace gpmg;

int main(int argc, char* argv[]) {
    UNUSED(argc)
    UNUSED(argv)

    auto basic = BasicAllocator();
    const size_t regionSize = 100;
    auto regionMemory = static_cast<char*>(malloc(regionSize));
    auto region = RegionAllocator(regionMemory, regionSize);
    auto mallocator = MallocAllocator();
    auto fallback =
        FallbackAllocator<RegionAllocator, MallocAllocator>(region, mallocator);

    // Basic tests
    CHECK(basic.allocate(10) == nullptr,
          "Testing basic allocator always returns nullptr upon allocate.")

    // Region tests
    CHECK(region.allocate(1) != nullptr,
          "Testing region allocator successfully allocates size < regionSize.")
    CHECK(region.allocate(regionSize + 4) == nullptr,
          "Testing region allocator fails to allocate size > regionSize")

    // Mallocator tests
    CHECK(mallocator.allocate(1), "Testing mallocator successfully allocates.")

    // Fallback tests
    CHECK(fallback.allocate(20) != nullptr,
          "Testing fallback allocator successfully allocates inside main "
          "region.");
    CHECK(
        fallback.allocate(120) != nullptr,
        "Testing fallback allocator successfully allocates with the fallback.");

    fallback.deallocate(fallback.allocate(1));

    free(regionMemory);
    return FAILED_TEST_RESULTS();
}
