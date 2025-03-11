#include <iostream>
#include <thread>
#include <chrono>

#include "lsl_cpp.h"


const char *channels[] = {"rand", "cnt"};

int main(int argc, char *argv[])
{
  std::cout << argv[0] << '\n';
  std::string name, type;
  name = argc>1 ? argv[1] : "demo_data";
  type = argc>2 ? argv[2] : "type_none";
  int n_channels = 2;
  unsigned int samplingrate = argc > 4 ? std::stoul(argv[4]) : 100;
  unsigned int max_buffered = argc > 5 ? std::stoul(argv[5]) : 360;

  try {

    // make a new stream_info (100 Hz)
    lsl::stream_info info(name,
                          type,
                          n_channels,
                          samplingrate,
                          lsl::cf_float32,
                          std::string(name) += type);

    // add some description fields
    info.desc().append_child_value("manufacturer", "LSL");
    lsl::xml_element chns = info.desc().append_child("channels");
    for (int k = 0; k < n_channels; k++)
      chns.append_child("channel")
	.append_child_value("label",
			    k < 2
			    ? channels[k]
			    : "Chan-" + std::to_string(k + 1))
	.append_child_value("unit", "microvolts")
	.append_child_value("type", type);

    // make stream outlet
    lsl::stream_outlet outlet(info, 0, max_buffered);

    // variable for the data sample
    float sample[2]={}; //(n_channels, 0.0);

    unsigned int sample_dur_us = 1000000 / (samplingrate > 0 ? samplingrate : 100);
    auto t_start = std::chrono::high_resolution_clock::now();
    auto next_sample_time = t_start;
    //
    auto cnt = 0;
    for (unsigned t = 0;; t++) {
      // Create data for the channels.

      sample[0] = (float)((rand() % 1500) / 500.0 - 1.5);

      sample[1] = (float) cnt;
      cnt++;
      if (cnt == 1024)
	cnt = 0;

      // Wait until the next expected sample time.
      next_sample_time += std::chrono::microseconds(sample_dur_us);
      std::this_thread::sleep_until(next_sample_time);
      
      // send the sample
      outlet.push_sample(sample);

      std::cout << sample[0] << "\t" << sample[n_channels-1] << std::endl;

    }
  } catch (std::exception& e) {
    std::cerr << "Got an exception: " << e.what() << std::endl;
  }
	  
  return 0;
}
