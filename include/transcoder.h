#ifndef TRANSCODER_H
#define TRANSCODER_H

#include <string>
#include "bmf/sdk/bmf.h"
#include "nlohmann/json.hpp"

class Transcoder {
public:
    Transcoder(const std::string& input_path, const std::string& output_path,
               const std::string& video_codec, int video_bitrate,
               int width, int height);
    
    bool run(); 

private:
    std::string input_path_;
    std::string output_path_;
    std::string video_codec_;
    int video_bitrate_;
    int width_;
    int height_;
};

#endif // TRANSCODER_H