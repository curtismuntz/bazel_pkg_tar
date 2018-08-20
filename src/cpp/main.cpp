#include <boost/program_options.hpp>
#include <iostream>
#include <string>

namespace {

namespace po = boost::program_options;

void PrintUsage(const po::options_description &options_description) noexcept {
  std::cout << "Usage:\n"
            << "  "
            << options_description << std::endl;
}

}  // namespace

int main(int argc, const char *argv[]) {
  auto descriptive_variable = std::string{""};

  auto options_description = po::options_description{};
  options_description.add_options()("help,h", "Display this help message")
      ("descriptive_variable,d", po::value<std::string>(&descriptive_variable));

    auto args = po::variables_map{};
    po::store(po::parse_command_line(argc, argv, options_description), args);
    if (args.count("help")) {
      PrintUsage(options_description);
      return 0;
    }

    po::notify(args);
    
    std::cout << descriptive_variable << std::endl;

  return 0;
}
