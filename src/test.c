#include "lib.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>

const char easy_target[] = "submit:function(){}caca";
const char medium_target[] =
    "asdfasdfasdfasdfssssssubmikzxcvsubmit:function(){}"
    "asjdhkfjakhsdfjkhasdjflhasdjfhsjfjhsubmisadklfj;asdjkfjasd;sub";
const char hard_target[] =
    "asdfasdfasdfasdfssssssubmikzxcvsubmit:function(){}"
    "asjdhkfjakhsdfjkhasdjflhasdjfhsjfjhsubmisadklfj;asdjkfjasd;sub";

// Very small test helpers
int failed = 0;
#define TEST(name) void name()
#define RUN_TEST(name)                                                         \
  printf("\n\033[1m%s\n\033[0m", #name);                                       \
  name()
#define ASSERT(expr)                                                           \
  if (!(expr)) {                                                               \
    failed = 1;                                                                \
    printf("\033[0;31mFAIL: %s\n\033[0m", #expr);                              \
  } else {                                                                     \
    printf("\033[0;32mPASS: %s\n\033[0m", #expr);                              \
  }
#define ASSERT_STR_EQ(str1, str2)                                              \
  if (!str_cmp(str1, str2)) {                                                  \
    failed = 1;                                                                \
    printf("\033[0;31mFAIL: != \n\033[0m");                                    \
  } else {                                                                     \
    printf("\033[0;32mPASS: %s == %s\n\033[0m", str1, str2);                   \
  }
// End of test helpers

TEST(test_add) {
  // ASSERT_STR_EQ(read_file("texts/easy.txt")
  // ASSERT(add(1, 2) == 3);
  // ASSERT(add(0, 0) == 0);
  // ASSERT(add(-1, -1) == -2);
}

TEST(test_string_assert) {
  ASSERT_STR_EQ(read_file("texts/easy.txt"), easy_target);
  // printf("%s \n", easy);
}
TEST(test_removing_stuff_from_function) {
  // char *easy_txt = read_file("texts/easy.txt");
  // char *medium_txt = read_file("texts/medium.txt");
  char *hard_txt = read_file("texts/hard.txt");
  FILE *expected_hard = fopen("output/expected.txt", "w");
  FILE *have_hard = fopen("output/have.txt", "w");
  // if (!easy_txt || !medium_txt) {
  //   return;
  // }
  char *pivot = "submit:function()";
  // char *result_easy =
  //     remove_content_from_this_char_to_this_char_after_this_substring(
  //         easy_txt, pivot, '{', '}');
  // char *result_medium =
  //     remove_content_from_this_char_to_this_char_after_this_substring(
  //         medium_txt, pivot, '{', '}');
  char *result_hard =
      remove_content_from_this_char_to_this_char_after_this_substring(
          hard_txt, pivot, '{', '}');
  char *hard_target = read_file("texts/hard_result.txt");
  // ASSERT_STR_EQ(result_easy, easy_target);
  // ASSERT_STR_EQ(result_medium, medium_target);
  // ASSERT_STR_EQ(result_hard, hard_target);
  fputs(result_hard, have_hard);
  printf("%d \n", strlen(hard_target));
  printf("%d \n", strlen(result_hard));
  printf("%s\n", result_hard);
  // fprintf(expected_hard, hard_target);
  //
  // fclose(have_hard);
  fclose(expected_hard);
}

int main() {
  // Add a `RUN_TEST` line for each test function
  // RUN_TEST(test_add);
  RUN_TEST(test_removing_stuff_from_function);
  return failed;
}
