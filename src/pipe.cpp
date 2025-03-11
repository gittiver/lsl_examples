#include <iostream>
#include <string>
#include <array>

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

  // make a new output stream  (100 Hz)
  lsl::stream_info info("demo_data_avg",
			"type",
			channelCount,
			streamInfo[0].nominal_srate(),
			lsl::cf_float32,
			"demo_data_avg_type");

  // add some description fields
  info.desc().append_child_value("manufacturer", "LSL");
  lsl::xml_element chns = info.desc().append_child("channels");
  for (int k = 0; k < channelCount; k++)
    chns.append_child("channel")
      .append_child_value("label", "Chan-" + std::to_string(k + 1))
      .append_child_value("unit", "microvolts")
      .append_child_value("type", "avg");

  // make stream outlet
  // make a new outlet
  lsl::stream_outlet outlet(info, 0);

  // Buffer to hold the received sample data
  std::vector<double> sample(channelCount);
  double timestamp;

  std::vector<double> sum(channelCount);
  std::vector<double> avg(channelCount);
  
  std::array<double,10> last_values;

  size_t samplecount=0;
  while (true) {
    // Pull a sample from the inlet
    timestamp = streamInlet.pull_sample(sample);
    samplecount++;
    for (size_t i = 0; i< channelCount;i++) {
      sum[i] += sample[i];
      avg[i] = sum[i]/ samplecount;
    }
    outlet.push_sample(avg, timestamp);
    std::cout << timestamp << ';' << avg[0] << std::endl;
    
  }
  return 0;
}
