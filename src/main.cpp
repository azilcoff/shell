#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <climits>
#include <linux/limits.h>

static std::string line{};
static char path[PATH_MAX] = {0};
static char hostname[HOST_NAME_MAX] = {0};
static passwd* user_data = NULL;


static bool refresh_shell_data();
static bool exec_line();

int main()
{
  while(true)
  {
    if (!refresh_shell_data())
    {
      return 1;
    }
    std::cout << user_data->pw_name << "@" << hostname << " " << path << "~> ";
    std::getline(std::cin, line);
    if (!exec_line())
    {
      return 0;
    }
  }
}

static bool refresh_shell_data()
{
  user_data = getpwuid(getuid());
  if (user_data == NULL)
  {
    std::cerr << "Error: getpwuid" << std::endl;
    return false;
  }
  if (gethostname(hostname, HOST_NAME_MAX) == -1)
  {
    std::cerr << "Error: gethostname" << std::endl;
    return false;
  }
  if (getcwd(path, PATH_MAX) == NULL)
  {
    std::cerr << "Error: getcwd" << std::endl;
    return false;
  }
  return true;
}

static bool exec_line()
{
  if (line == "exit")
  {
    return false;
  }
  return true;
}
