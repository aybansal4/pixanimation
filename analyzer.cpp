#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/timestamp.h>
    #include <libavutil/avutil.h>
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    AVFormatContext *pFormatContext = nullptr;
    if (avformat_open_input(&pFormatContext, filename, nullptr, nullptr) != 0) {
        std::cerr << "Could not open file " << filename << std::endl;
        return -1;
    }

    // Retrieve stream information
    if (avformat_find_stream_info(pFormatContext, nullptr) < 0) {
        std::cerr << "Could not find stream information" << std::endl;
        // Clean up context on failure
        avformat_close_input(&pFormatContext);
        return -1;
    }

    std::cout << "Opened file: " << filename << std::endl;

    // Convert duration from AV_TIME_BASE units to seconds for a readable output
    double duration_seconds = (double)pFormatContext->duration / AV_TIME_BASE;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Duration: " << duration_seconds << " seconds" << std::endl;
    std::cout << "Number of streams: " << pFormatContext->nb_streams << std::endl;

    // Iterate over streams
    for (unsigned int i = 0; i < pFormatContext->nb_streams; i++) {
        AVCodecParameters *pCodecParameters = pFormatContext->streams[i]->codecpar;

const char* codec_type_str = av_get_media_type_string(pCodecParameters->codec_type);
        if (codec_type_str == nullptr) {
            codec_type_str = "Unknown type";
        }

        std::cout << "Stream " << i << ": "
                  << codec_type_str
                  << " codec, ID: " << pCodecParameters->codec_id;

        if (pCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            std::cout << " (" << pCodecParameters->width << "x" << pCodecParameters->height << ")";
        }
        std::cout << std::endl;
    }

    // Clean up
    avformat_close_input(&pFormatContext);

    std::cout << "Closed file and finished." << std::endl;

    return 0;
}
