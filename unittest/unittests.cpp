#include <gtest/gtest.h>

#include "../src/my_time_t.h"
#include "../src/CompClub.h"

TEST(my_time_t_test, constructor_default) {
    EXPECT_NO_THROW(my_time_t t);
}

TEST(my_time_t_test, constructor_unsigned_normal) {
    my_time_t t(23u,55u);
    EXPECT_EQ(t.get_str(), "23:55");
}

TEST(my_time_t_test, constructor_unsigned_normal2) {
    
    EXPECT_NO_THROW(my_time_t t(23,55));
}

TEST(my_time_t_test, constructor_unsigned_overflow1) {
    my_time_t t(55,55);
    EXPECT_EQ(t.get_str(), "07:55");
}

TEST(my_time_t_test, constructor_unsigned_overflow2) {
    my_time_t t(55,165);
    EXPECT_EQ(t.get_str(), "09:45");
}

TEST(my_time_t_test, constructor_unsigned_overflow3) {
    my_time_t t(55,-165);
    EXPECT_EQ(t.get_str(), "04:15");
}

TEST(my_time_t_test, constructor_copy) {
    my_time_t t(7,25);
    my_time_t t2(t);
    EXPECT_EQ(t.get_str(), t2.get_str());
}

TEST(my_time_t_test, get_round_up) {
    my_time_t t(7,25);
    EXPECT_EQ(t.get_round_up(), 8);
}
TEST(my_time_t_test, get_round_up2) {
    my_time_t t(7,0);
    EXPECT_EQ(t.get_round_up(), 7);
}

TEST(my_time_t_test, set_time_ui) {
    my_time_t t;
    t.set_time(7,25);
    EXPECT_EQ(t.get_str(), "07:25");
}

TEST(my_time_t_test, set_time_str_normal) {
    my_time_t t;
    t.set_time("7:25");
    EXPECT_EQ(t.get_str(), "07:25");
}

TEST(my_time_t_test, set_time_str_failure) {
    my_time_t t;
    EXPECT_ANY_THROW( t.set_time("7esagrfsrwthg"));
}

TEST(my_time_t_test, op_assigment) {
    my_time_t t(7,25);
    my_time_t t2;
    t2 = t;
    EXPECT_EQ(t.get_str(), t2.get_str());
}

TEST(my_time_t_test, op_less) {
    my_time_t t(7,25);
    my_time_t t2(23,45);
    EXPECT_EQ(t < t2, true);
    EXPECT_EQ(t2 < t, false);
}

TEST(my_time_t_test, op_greater) {
    my_time_t t(7,25);
    my_time_t t2(23,45);
    EXPECT_EQ(t > t2, false);
    EXPECT_EQ(t2 > t, true);
}

TEST(my_time_t_test, op_sum) {
    my_time_t t(7,25);
    my_time_t t2(23,45);
    EXPECT_EQ((t + t2).get_str(), "07:10");
}

TEST(my_time_t_test, op_sub) {
    my_time_t t(7,25);
    my_time_t t2(23,45);
    EXPECT_EQ((t2 - t).get_str(), "16:20");
}

// TEST(my_time_t_test, op_sub2) {
//     my_time_t t(7,25);
//     my_time_t t2(23,45);
//     EXPECT_EQ((t - t2).get_str(), "16:20");
// }

TEST(comp_club, normal_run) {
    ComputerClub club{std::string("datasets/input.txt")};
    club.start();
}

TEST(comp_club, format_exception) {
   ComputerClub club{std::string("datasets/input_failed.txt")};
   
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
