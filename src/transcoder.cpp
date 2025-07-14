#include "../include/transcoder.h"
#include "builder.hpp"
#include "bmf/sdk/json_param.h"
#include <fmt/format.h> 

Transcoder::Transcoder(const std::string& input_path, const std::string& output_path,
                       const std::string& video_codec, int video_bitrate,
                       int width, int height)
    : input_path_(input_path), output_path_(output_path),
      video_codec_(video_codec), video_bitrate_(video_bitrate),
      width_(width), height_(height) {}

bool Transcoder::run() {
    try {
        // 创建BMF处理图
        auto graph = bmf::builder::Graph(bmf::builder::NormalMode);

        // 解码节点配置
        nlohmann::json decode_params = {{"input_path", input_path_}};
        auto decoder = graph.Decode(bmf_sdk::JsonParam(decode_params));

        // 调整分辨率
        auto video_stream = decoder["video"].FFMpegFilter(
            {}, "scale", fmt::format("{}:{}", width_, height_)
        );

        // 指定编码、码率、分辨率
        nlohmann::json encode_params = {
            {"output_path", output_path_},
            {"video_params", {
                {"codec", video_codec_},
                {"bit_rate", video_bitrate_},
                {"width", width_},
                {"height", height_}
            }},
            
            {"audio_params", {
                {"codec", "aac"},
                {"bit_rate", 1280000},
                {"sample_rate", 44100},
                {"channels", 1} 
            }}
        };

        std::cout << "编码器参数: " << encode_params.dump(2) << std::endl;

        // 编码输出
        graph.Encode(video_stream, decoder["audio"], bmf_sdk::JsonParam(encode_params));

        // 运行
        graph.Run();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "转码失败: " << e.what() << std::endl;
        return false;
    }
}