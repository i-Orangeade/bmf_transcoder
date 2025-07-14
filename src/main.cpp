#include "../include/transcoder.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "用法: " << argv[0] 
                  << "./bmf_transcoder <输入文件> <输出文件> <视频编码> <视频码率(kbps)> <宽度> <高度>\n";
        return -1;
    }

    std::string input_path = argv[1];
    std::string output_path = argv[2];
    std::string video_codec = argv[3];
    int bitrate_kbps = std::stoi(argv[4]); 
    int video_bitrate = bitrate_kbps * 1000;
    int width = std::stoi(argv[5]);
    int height = std::stoi(argv[6]);

    // 执行转码
    Transcoder transcoder(input_path, output_path, video_codec, video_bitrate, width, height);
    return transcoder.run() ? 0 : -1;
}