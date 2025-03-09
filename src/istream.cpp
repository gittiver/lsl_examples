#include <iostream>
#include <string>

#include <lsl_cpp.h>

int main(int argc, char *argv[])
{
  // Look for streams
  std::vector<lsl::stream_info> streamInfo =
      lsl::resolve_stream("name",  // property (name, type,
                                   // //source_id, desc/manufacture
			  "demo_data", // value the property should have
			  1, // minimum number of streams
			  100 //lsl::FOREVER  // timeout
			  );
  std::cout << "Found " << streamInfo.size() << " streams\n";
  if( streamInfo.size() == 0 ) {
    std::cerr << "No streams found. Exiting.\n";
    return -1;
  }
  size_t channelCount = streamInfo[0].channel_count();
  std::cout << "Channel Count: " << channelCount << std::endl;

  // Create an inlet to receive data
  lsl::stream_inlet streamInlet(streamInfo[0]);

  // Buffer to hold the received sample data
  std::vector<double> sample(channelCount);

  while (true) {
    // Pull a sample from the inlet
    streamInlet.pull_sample(sample);

    // Print the received sample
    std::cout << "Received sample: ";
    for (const auto &val : sample) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
