#include <gtest/gtest.h>

#include "../src/CompClub.h"
#include "../src/my_time_t.h"

TEST(my_time_t_test, constructor_default) { EXPECT_NO_THROW(my_time_t t); }

TEST(my_time_t_test, constructor_unsigned_normal) {
  my_time_t t(23u, 55u);
  EXPECT_EQ(t.get_str(), "23:55");
}

TEST(my_time_t_test, constructor_unsigned_normal2) {
  EXPECT_NO_THROW(my_time_t t(23, 55));
}

TEST(my_time_t_test, constructor_unsigned_overflow1) {
  my_time_t t(55, 55);
  EXPECT_EQ(t.get_str(), "07:55");
}

TEST(my_time_t_test, constructor_unsigned_overflow2) {
  my_time_t t(55, 165);
  EXPECT_EQ(t.get_str(), "09:45");
}

TEST(my_time_t_test, constructor_unsigned_overflow3) {
  my_time_t t(55, -165);
  EXPECT_EQ(t.get_str(), "04:15");
}

TEST(my_time_t_test, constructor_copy) {
  my_time_t t(7, 25);
  my_time_t t2(t);
  EXPECT_EQ(t.get_str(), t2.get_str());
}

TEST(my_time_t_test, get_round_up) {
  my_time_t t(7, 25);
  EXPECT_EQ(t.get_round_up(), 8);
}
TEST(my_time_t_test, get_round_up2) {
  my_time_t t(7, 0);
  EXPECT_EQ(t.get_round_up(), 7);
}

TEST(my_time_t_test, set_time_ui) {
  my_time_t t;
  t.set_time(7, 25);
  EXPECT_EQ(t.get_str(), "07:25");
}

TEST(my_time_t_test, set_time_str_normal) {
  my_time_t t;
  t.set_time("7:25");
  EXPECT_EQ(t.get_str(), "07:25");
}

TEST(my_time_t_test, set_time_str_failure) {
  my_time_t t;
  EXPECT_ANY_THROW(t.set_time("7esagrfsrwthg"));
}

TEST(my_time_t_test, op_assigment) {
  my_time_t t(7, 25);
  my_time_t t2;
  t2 = t;
  EXPECT_EQ(t.get_str(), t2.get_str());
}

TEST(my_time_t_test, op_less) {
  my_time_t t(7, 25);
  my_time_t t2(23, 45);
  EXPECT_EQ(t < t2, true);
  EXPECT_EQ(t2 < t, false);
}

TEST(my_time_t_test, op_greater) {
  my_time_t t(7, 25);
  my_time_t t2(23, 45);
  EXPECT_EQ(t > t2, false);
  EXPECT_EQ(t2 > t, true);
}

TEST(my_time_t_test, op_sum) {
  my_time_t t(7, 25);
  my_time_t t2(23, 45);
  EXPECT_EQ((t + t2).get_str(), "07:10");
}

TEST(my_time_t_test, op_sub) {
  my_time_t t(7, 25);
  my_time_t t2(23, 45);
  EXPECT_EQ((t2 - t).get_str(), "16:20");
}

TEST(comp_club_IO, virtuals_covearage_tweak) {
  class mock : public ComputerClubIO {
   public:
    mock(std::string path) : ComputerClubIO(path){};
    void run() {
      parse_initial_values();
      Event tmp("", my_time_t(23, 55), OK);
      update_state(tmp);
      print_workday_summary();
      print_open_summary();
    }
  };
  mock a{std::string("datasets/input.txt")};
  EXPECT_NO_THROW(a.run());
}

TEST(comp_club, TZ_expected_output) {
  std::stringstream buffer;
  std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
  ComputerClub club{std::string("datasets/input.txt")};
  club.start();
  std::cout.rdbuf(oldCoutBuffer);

  EXPECT_EQ(
      buffer.str(),
      "09:00\n08:48 1 client1\n08:48 13 NotOpenYet\n09:41 1 client1\n09:48 1 "
      "client2\n09:52 3 client1\n09:52 13 ICanWaitNoLonger!\n09:54 2 client1 "
      "1\n10:25 2 client2 2\n10:58 1 client3\n10:59 2 client3 3\n11:30 1 "
      "client4\n11:35 2 client4 2\n11:35 13 PlaceIsBusy\n11:45 3 "
      "client4\n12:33 4 client1\n12:33 12 client4 1\n12:43 4 client2\n15:52 4 "
      "client4\n19:00 11 client3\n19:00\n1 70 05:58\n2 30 02:18\n3 90 08:01\n");
}

TEST(comp_club, normal_run) {
  ComputerClub club{std::string("datasets/input.txt")};
  club.start();
}

TEST(comp_club, normal_run2) {
  ComputerClub club{std::string("datasets/input2.txt")};
  club.start();
}

TEST(comp_club, normal_run3) {
  ComputerClub club{std::string("datasets/input3.txt")};
  club.start();
}

TEST(comp_club, normal_run4) {
  ComputerClub club{std::string("datasets/input4.txt")};
  club.start();
}

TEST(comp_club, normal_run5) {
  ComputerClub club{std::string("datasets/input5.txt")};
  club.start();
}

TEST(comp_club, normal_run6) {
  ComputerClub club{std::string("datasets/input6.txt")};
  club.start();
}

TEST(comp_club, format_exception) {
  ComputerClub club{std::string("datasets/input_failed.txt")};
  EXPECT_ANY_THROW(club.start());
}

TEST(comp_club, format_exception2) {
  ComputerClub club{std::string("datasets/input_failed2.txt")};
  EXPECT_ANY_THROW(club.start());
}

TEST(comp_club, format_initial_data_exception) {
  EXPECT_ANY_THROW(
      ComputerClub club{std::string("datasets/input_failed3.txt")});
}

TEST(comp_club, format_initial_data_exception2) {
  EXPECT_ANY_THROW(
      ComputerClub club{std::string("datasets/input_failed4.txt")});
}

TEST(comp_club, format_initial_data_exception3) {
  EXPECT_ANY_THROW(
      ComputerClub club{std::string("datasets/input_failed5.txt")});
}

TEST(comp_club, format_exception_what) {
  ComputerClub club{std::string("datasets/input_failed2.txt")};
  try {
    club.start();
  } catch (const CompClubException& e) {
    EXPECT_EQ(strcmp(e.what(), "parsing error"), 0);
    std::cerr << e.what() << '\n';
  }
}

TEST(comp_club, filename_err) {
  EXPECT_ANY_THROW(ComputerClub club{std::string("sgfsertherh")});
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
