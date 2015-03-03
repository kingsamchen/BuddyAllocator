
#include "gtest\gtest.h"

#include <algorithm>
#include <initializer_list>
#include <vector>

#include "bin_manager.h"
#include "buddy_util.h"

namespace {

template<typename T>
bool VerifyVector(const std::vector<T>& v, std::initializer_list<T> val_list)
{
    if (v.size() != val_list.size()) {
        return false;
    }

    // Error C4996 received if we were using std::equal.
    auto iv = v.begin();
    auto il = val_list.begin();
    for (; iv != v.end() && il != val_list.end(); ++iv, ++il) {
        if (*iv != *il) return false;
    }

    return true;
}

}   // namespace

TEST(BuddyUtilTest, IsPowerOf2)
{
    size_t power_of_2[] {1, 2, 4, 8, 16};
    size_t not_power_of_2[] {0, 3, 5, 6, 7, 9, 10, 11, 12, 14};

    for (auto ele : power_of_2) {
        EXPECT_TRUE(buddy_util::IsPowerOf2(ele)) << ele << " failed";
    }

    for (auto ele : not_power_of_2) {
        EXPECT_FALSE(buddy_util::IsPowerOf2(ele)) << ele << " failed";
    }
}

// ----------------------------------------------------------------------------------

class BinManagerTest : public ::testing::Test {
protected:
    size_t get_total_slot_count(const BinManager& bin_manager)
    {
        return bin_manager.total_slot_count_;
    }

    const std::vector<size_t>& get_maximum_slot(const BinManager& bin_manager)
    {
        return bin_manager.maximum_slot_;
    }
};

TEST_F(BinManagerTest, Construction)
{
    {
        BinManager bm(1);
        ASSERT_EQ(get_total_slot_count(bm), 1);
        EXPECT_TRUE(VerifyVector<size_t>(get_maximum_slot(bm), {1}));
    }
    {
        BinManager bm(4);
        ASSERT_EQ(get_total_slot_count(bm), 4);
        EXPECT_TRUE(VerifyVector<size_t>(get_maximum_slot(bm), {4,2,2,1,1,1,1}));
    }

    // TODO: test two exceptions with bm(0) and bm(7)
}

// ----------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}