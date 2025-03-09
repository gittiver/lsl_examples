#include <iostream>
#include <thread>

#include "lsl_cpp.h"

int main(int argc, char *argv[])
{
  try {

    // make a new stream_info (irregular rate)
    lsl::stream_info markers("demo_markers", //name,
			     "Markers", // content_type
			     1, //n_channels
			     lsl::IRREGULAR_RATE,
			     lsl::cf_string,
			     "demo_markers_id");

    // add some description fields
    markers.desc().append_child_value("manufacturer", "LSL");
    lsl::xml_element chns = markers.desc().append_child("markers");
    chns.append_child("channel")
      .append_child_value("label", "Demo events");
  
    // make stream outlet
    lsl::stream_outlet outlet(markers, 0);

    // variable for the sample
    std::array<std::string,1> sample{"event"};
    std::string input;
    while (true) {
      // wait for word input
      std::cin >> input;
      // take timestamp as early as possible
      auto t = lsl::local_clock();
      sample[0] = "event:" + input;

      // send the sample
      outlet.push_sample(sample.data(),t);
      std::cout << sample[0] << std::endl;
    }
  } catch (std::exception& e) {
    std::cerr << "Got an exception: " << e.what() << std::endl;
  }
	  
  return 0;
}
